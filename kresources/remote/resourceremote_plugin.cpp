/*
    This file is part of libkcal.

    Copyright (c) 2003 Cornelius Schumacher <schumacher@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "resourceremoteconfig.h"
#include "resourceremote.h"

#include <kglobal.h>
#include <klocale.h>

using namespace KCal;

typedef KRES::PluginFactory<ResourceRemote, ResourceRemoteConfig> RemoteFactory;
// FIXME: Use K_EXPORT_COMPONENT_FACTORY( kcal_remote, RemoteFactory ); here
// Problem: How do I insert the catalogue???
extern "C" {
    void *init_kcal_remote()
    {
        KGlobal::locale()->insertCatalogue("libkcal");
        KGlobal::locale()->insertCatalogue("kres_remote");
        return new RemoteFactory;
    }
}
