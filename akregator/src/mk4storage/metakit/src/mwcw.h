// mwcw.h --
// $Id: mwcw.h 403187 2005-04-04 20:17:07Z osterfeld $
// This is part of Metakit, see http://www.equi4.com/metakit/

/** @file
 * Configuration header for Metrowerks CodeWarrior
 */

#define q4_MWCW 1

/////////////////////////////////////////////////////////////////////////////

#if q4_68K
#if !__option(IEEEdoubles)
#error Cannot build Metakit with 10-byte doubles
#endif
#endif

#if __option(bool)
#define q4_BOOL 1
  // undo previous defaults, because q4_BOOL is not set early enough
#undef false
#undef true
#undef bool
#endif

#undef _MSC_VER

#pragma export on

/////////////////////////////////////////////////////////////////////////////
