// -*- c-basic-offset: 2 -*-

#include "kfoldertree.h"
#include <klocale.h>
#include <kio/global.h>
#include <kiconloader.h>
#include <kdebug.h>
#include <kstringhandler.h>
#include <qpainter.h>
#include <qapplication.h>
#include <qheader.h>
#include <qstyle.h>

//-----------------------------------------------------------------------------
KFolderTreeItem::KFolderTreeItem(KFolderTree *parent, const QString &label,
                                 Protocol protocol, Type type)
    : KListViewItem(parent, label), mProtocol(protocol), mType(type),
      mUnread(-1), mTotal(0), mSize(0), mFolderIsCloseToQuota(false)
{
}

//-----------------------------------------------------------------------------
KFolderTreeItem::KFolderTreeItem(KFolderTreeItem *parent,
                                 const QString &label, Protocol protocol, Type type,
                                 int unread, int total)
    : KListViewItem(parent, label), mProtocol(protocol), mType(type),
      mUnread(unread), mTotal(total), mSize(0), mFolderIsCloseToQuota(false)
{
}

//-----------------------------------------------------------------------------
int KFolderTreeItem::protocolSortingKey() const
{
    // protocol dependant sorting order:
    // local < imap < news < search < other
    switch(mProtocol)
    {
        case Local:
            return 1;
        case CachedImap:
        case Imap:
            return 2;
        case News:
            return 3;
        case Search:
            return 4;
        default:
            return 42;
    }
}

//-----------------------------------------------------------------------------
int KFolderTreeItem::typeSortingKey() const
{
    // type dependant sorting order:
    // inbox < outbox < sent-mail < trash < drafts
    // < calendar < contacts < notes < tasks
    // < normal folders
    switch(mType)
    {
        case Inbox:
            return 1;
        case Outbox:
            return 2;
        case SentMail:
            return 3;
        case Trash:
            return 4;
        case Drafts:
            return 5;
        case Templates:
            return 6;
        case Calendar:
            return 7;
        case Contacts:
            return 8;
        case Notes:
            return 9;
        case Tasks:
            return 10;
        default:
            return 42;
    }
}

//-----------------------------------------------------------------------------
int KFolderTreeItem::compare(QListViewItem *i, int col, bool) const
{
    KFolderTreeItem *other = static_cast<KFolderTreeItem *>(i);

    if(col == 0)
    {
        // sort by folder

        // local root-folder
        if(depth() == 0 && mProtocol == NONE)
            return -1;
        if(other->depth() == 0 && other->protocol() == NONE)
            return 1;

        // first compare by protocol
        int thisKey = protocolSortingKey();
        int thatKey = other->protocolSortingKey();
        if(thisKey < thatKey)
            return -1;
        if(thisKey > thatKey)
            return 1;

        // then compare by type
        thisKey = typeSortingKey();
        thatKey = other->typeSortingKey();
        if(thisKey < thatKey)
            return -1;
        if(thisKey > thatKey)
            return 1;

        // and finally compare by name
        return text(0).localeAwareCompare(other->text(0));
    }
    else
    {
        // sort by unread or total-column
        Q_INT64 a = 0, b = 0;
        if(col == static_cast<KFolderTree *>(listView())->unreadIndex())
        {
            a = mUnread;
            b = other->unreadCount();
        }
        else if(col == static_cast<KFolderTree *>(listView())->totalIndex())
        {
            a = mTotal;
            b = other->totalCount();
        }
        else if(col == static_cast<KFolderTree *>(listView())->sizeIndex())
        {
            a = mSize;
            b = other->folderSize();
        }

        if(a == b)
            return 0;
        else
            return (a < b ? -1 : 1);
    }
}

//-----------------------------------------------------------------------------
void KFolderTreeItem::setUnreadCount(int aUnread)
{
    if(aUnread < 0) return;

    mUnread = aUnread;

    QString unread = QString::null;
    if(mUnread == 0)
        unread = "- ";
    else
    {
        unread.setNum(mUnread);
        unread += " ";
    }

    setText(static_cast<KFolderTree *>(listView())->unreadIndex(),
            unread);
}

//-----------------------------------------------------------------------------
void KFolderTreeItem::setTotalCount(int aTotal)
{
    if(aTotal < 0) return;

    mTotal = aTotal;

    QString total = QString::null;
    if(mTotal == 0)
        total = "- ";
    else
    {
        total.setNum(mTotal);
        total += " ";
    }

    setText(static_cast<KFolderTree *>(listView())->totalIndex(),
            total);
}

//-----------------------------------------------------------------------------
void KFolderTreeItem::setFolderSize(Q_INT64 aSize)
{
    if(aSize < 0) return;     // we need to update even if nothing changed, kids ...

    mSize = aSize;

    QString size;
    if(mType != Root)
    {
        if(mSize == 0 && (childCount() == 0 || isOpen()))
            size = "- ";
        else
            size = KIO::convertSize(mSize);
    }
    if(childCount() > 0 && !isOpen())
    {
        Q_INT64 recursiveSize = recursiveFolderSize();
        if(recursiveSize != mSize)
        {
            if(mType != Root)
                size += QString::fromLatin1(" + %1").arg(KIO::convertSize(recursiveSize - mSize));
            else
                size = KIO::convertSize(recursiveSize);
        }
    }
    size += " ";

    setText(static_cast<KFolderTree *>(listView())->sizeIndex(), size);
}

//-----------------------------------------------------------------------------
Q_INT64 KFolderTreeItem::recursiveFolderSize() const
{
    Q_INT64 size = mSize;

    for(QListViewItem *item = firstChild() ;
            item ; item = item->nextSibling())
    {
        size += static_cast<KFolderTreeItem *>(item)->recursiveFolderSize();
    }
    return size;
}



//-----------------------------------------------------------------------------
int KFolderTreeItem::countUnreadRecursive()
{
    int count = (mUnread > 0) ? mUnread : 0;

    for(QListViewItem *item = firstChild() ;
            item ; item = item->nextSibling())
    {
        count += static_cast<KFolderTreeItem *>(item)->countUnreadRecursive();
    }

    return count;
}

//-----------------------------------------------------------------------------
void KFolderTreeItem::paintCell(QPainter *p, const QColorGroup &cg,
                                int column, int width, int align)
{
    KFolderTree *ft = static_cast<KFolderTree *>(listView());

    const int unreadRecursiveCount = countUnreadRecursive();
    const int unreadCount = (mUnread > 0) ? mUnread : 0;


    // use a special color for folders which are close to their quota
    QColorGroup mycg = cg;
    if((column == 0 || column == ft->sizeIndex()) && folderIsCloseToQuota())
    {
        mycg.setColor(QColorGroup::Text, ft->paintInfo().colCloseToQuota);
    }

    // use a bold-font for the folder- and the unread-columns
    if((column == 0 || column == ft->unreadIndex())
            && (unreadCount > 0
                || (!isOpen() && unreadRecursiveCount > 0)))
    {
        QFont f = p->font();
        f.setWeight(QFont::Bold);
        p->setFont(f);
    }


    // most cells can be handled by KListView::paintCell, we only need to
    // deal with the folder column if the unread column is not shown

    /* The below is exceedingly silly, but Ingo insists that the unread
     * count that is shown in parenthesis after the folder name must
     * be configurable in color. That means that paintCell needs to do
     * two painting passes which flickers. Since that flicker is not
     * needed when there is the unread column, special case that. */
    if(ft->isUnreadActive() || column != 0)
    {
        KListViewItem::paintCell(p, mycg, column, width, align);
    }
    else
    {
        QListView *lv = listView();
        QString oldText = text(column);

        // set an empty text so that we can have our own implementation (see further down)
        // but still benefit from KListView::paintCell
        setText(column, "");

        KListViewItem::paintCell(p, mycg, column, width, align);

        const QPixmap *icon = pixmap(column);
        int marg = lv ? lv->itemMargin() : 1;
        int r = marg;

        setText(column, oldText);
        if(isSelected())
            p->setPen(mycg.highlightedText());
        else
            p->setPen(mycg.color(QColorGroup::Text));

        if(icon)
        {
            r += icon->width() + marg;
        }
        QString t = text(column);
        if(t.isEmpty())
            return;

        // draw the unread-count if the unread-column is not active
        QString unread;

        if(unreadCount > 0 || (!isOpen() && unreadRecursiveCount > 0))
        {
            if(isOpen())
                unread = " (" + QString::number(unreadCount) + ")";
            else if(unreadRecursiveCount == unreadCount || mType == Root)
                unread = " (" + QString::number(unreadRecursiveCount) + ")";
            else
                unread = " (" + QString::number(unreadCount) + " + " +
                         QString::number(unreadRecursiveCount - unreadCount) + ")";
        }

        // check if the text needs to be squeezed
        QFontMetrics fm(p->fontMetrics());
        int unreadWidth = fm.width(unread);
        if(fm.width(t) + marg + r + unreadWidth > width)
            t = squeezeFolderName(t, fm, width - marg - r - unreadWidth);

        QRect br;
        p->drawText(r, 0, width - marg - r, height(),
                    align | AlignVCenter, t, -1, &br);

        if(!unread.isEmpty())
        {
            if(!isSelected())
                p->setPen(ft->paintInfo().colUnread);
            p->drawText(br.right(), 0, width - marg - br.right(), height(),
                        align | AlignVCenter, unread);
        }
    }
}


QString KFolderTreeItem::squeezeFolderName(const QString &text,
        const QFontMetrics &fm,
        uint width) const
{
    return KStringHandler::rPixelSqueeze(text, fm, width);
}

bool KFolderTreeItem::folderIsCloseToQuota() const
{
    return mFolderIsCloseToQuota;
}

void KFolderTreeItem::setFolderIsCloseToQuota(bool v)
{
    if(mFolderIsCloseToQuota != v)
    {
        mFolderIsCloseToQuota = v;
        repaint();
    }
}


//=============================================================================


KFolderTree::KFolderTree(QWidget *parent, const char *name)
    : KListView(parent, name), mUnreadIndex(-1), mTotalIndex(-1), mSizeIndex(-1)
{
    // GUI-options
    setStyleDependantFrameWidth();
    setAcceptDrops(true);
    setDropVisualizer(false);
    setAllColumnsShowFocus(true);
    setShowSortIndicator(true);
    setUpdatesEnabled(true);
    setItemsRenameable(false);
    setRootIsDecorated(true);
    setSelectionModeExt(Extended);
    setAlternateBackground(QColor());
#if KDE_IS_VERSION( 3, 3, 90 )
    setShadeSortColumn(false);
#endif
    setFullWidth(true);
    disableAutoSelection();
    setColumnWidth(0, 120);   //reasonable default size

    disconnect(header(), SIGNAL(sizeChange(int, int, int)));
    connect(header(), SIGNAL(sizeChange(int, int, int)),
            SLOT(slotSizeChanged(int, int, int)));
}

//-----------------------------------------------------------------------------
void KFolderTree::setStyleDependantFrameWidth()
{
    // set the width of the frame to a reasonable value for the current GUI style
    int frameWidth;
    if(style().isA("KeramikStyle"))
        frameWidth = style().pixelMetric(QStyle::PM_DefaultFrameWidth) - 1;
    else
        frameWidth = style().pixelMetric(QStyle::PM_DefaultFrameWidth);
    if(frameWidth < 0)
        frameWidth = 0;
    if(frameWidth != lineWidth())
        setLineWidth(frameWidth);
}

//-----------------------------------------------------------------------------
void KFolderTree::styleChange(QStyle &oldStyle)
{
    setStyleDependantFrameWidth();
    KListView::styleChange(oldStyle);
}

//-----------------------------------------------------------------------------
void KFolderTree::drawContentsOffset(QPainter *p, int ox, int oy,
                                     int cx, int cy, int cw, int ch)
{
    bool oldUpdatesEnabled = isUpdatesEnabled();
    setUpdatesEnabled(false);
    KListView::drawContentsOffset(p, ox, oy, cx, cy, cw, ch);
    setUpdatesEnabled(oldUpdatesEnabled);
}

//-----------------------------------------------------------------------------
void KFolderTree::contentsMousePressEvent(QMouseEvent *e)
{
    setSelectionModeExt(Single);
    KListView::contentsMousePressEvent(e);
}

//-----------------------------------------------------------------------------
void KFolderTree::contentsMouseReleaseEvent(QMouseEvent *e)
{
    KListView::contentsMouseReleaseEvent(e);
    setSelectionModeExt(Extended);
}

//-----------------------------------------------------------------------------
void KFolderTree::addAcceptableDropMimetype(const char *mimeType, bool outsideOk)
{
    int oldSize = mAcceptableDropMimetypes.size();
    mAcceptableDropMimetypes.resize(oldSize + 1);
    mAcceptOutside.resize(oldSize + 1);

    mAcceptableDropMimetypes.at(oldSize) =  mimeType;
    mAcceptOutside.setBit(oldSize, outsideOk);
}

//-----------------------------------------------------------------------------
bool KFolderTree::acceptDrag(QDropEvent *event) const
{
    QListViewItem *item = itemAt(contentsToViewport(event->pos()));

    for(uint i = 0; i < mAcceptableDropMimetypes.size(); i++)
    {
        if(event->provides(mAcceptableDropMimetypes[i]))
        {
            if(item)
                return (static_cast<KFolderTreeItem *>(item))->acceptDrag(event);
            else
                return mAcceptOutside[i];
        }
    }
    return false;
}

//-----------------------------------------------------------------------------
void KFolderTree::addUnreadColumn(const QString &name, int width)
{
    mUnreadIndex = addColumn(name, width);
    setColumnAlignment(mUnreadIndex, qApp->reverseLayout() ? Qt::AlignLeft : Qt::AlignRight);
    header()->adjustHeaderSize();
}

//-----------------------------------------------------------------------------
void KFolderTree::addTotalColumn(const QString &name, int width)
{
    mTotalIndex = addColumn(name, width);
    setColumnAlignment(mTotalIndex, qApp->reverseLayout() ? Qt::AlignLeft : Qt::AlignRight);
    header()->adjustHeaderSize();
}

//-----------------------------------------------------------------------------
void KFolderTree::removeUnreadColumn()
{
    if(!isUnreadActive()) return;
    removeColumn(mUnreadIndex);
    if(isTotalActive() && mTotalIndex > mUnreadIndex)
        mTotalIndex--;
    if(isSizeActive() && mSizeIndex > mUnreadIndex)
        mSizeIndex--;

    mUnreadIndex = -1;
    header()->adjustHeaderSize();
}

//-----------------------------------------------------------------------------
void KFolderTree::removeTotalColumn()
{
    if(!isTotalActive()) return;
    removeColumn(mTotalIndex);
    if(isUnreadActive() && mTotalIndex < mUnreadIndex)
        mUnreadIndex--;
    if(isSizeActive() && mTotalIndex < mSizeIndex)
        mSizeIndex--;
    mTotalIndex = -1;
    header()->adjustHeaderSize();
}

//-----------------------------------------------------------------------------
void KFolderTree::addSizeColumn(const QString &name, int width)
{
    mSizeIndex = addColumn(name, width);
    setColumnAlignment(mSizeIndex, qApp->reverseLayout() ? Qt::AlignLeft : Qt::AlignRight);
    header()->adjustHeaderSize();
}

//-----------------------------------------------------------------------------
void KFolderTree::removeSizeColumn()
{
    if(!isSizeActive()) return;
    removeColumn(mSizeIndex);
    if(isUnreadActive() && mSizeIndex < mUnreadIndex)
        mUnreadIndex--;
    if(isTotalActive() && mSizeIndex < mTotalIndex)
        mTotalIndex--;
    mSizeIndex = -1;
    header()->adjustHeaderSize();
}


//-----------------------------------------------------------------------------
void KFolderTree::setFullWidth(bool fullWidth)
{
    if(fullWidth)
        header()->setStretchEnabled(true, 0);
}

//-----------------------------------------------------------------------------
void KFolderTree::slotSizeChanged(int section, int, int newSize)
{
    viewport()->repaint(
        header()->sectionPos(section), 0, newSize, visibleHeight(), false);
}

#include "kfoldertree.moc"
