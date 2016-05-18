// libkcal
#cmakedefine USE_LIBICAL_0_46 1

// ktnef
#cmakedefine HAVE_INTTYPES_H 1
#cmakedefine HAVE_STDINT_H 1
#cmakedefine SIZEOF_UNSIGNED_LONG_LONG @SIZEOF_UNSIGNED_LONG_LONG@
#cmakedefine SIZEOF_UNSIGNED_LONG @SIZEOF_UNSIGNED_LONG@
#cmakedefine SIZEOF_UINT64_T @SIZEOF_UINT64_T@

// libkdepim, kmail
#cmakedefine KDEPIM_NEW_DISTRLISTS 1

// libkdemanager, certmanager
#cmakedefine HAVE_GPGME_0_4_BRANCH 1

// certmanager
#cmakedefine MAX_CMD_LENGTH @MAX_CMD_LENGTH@
#cmakedefine HAVE_C99_INITIALIZERS 1

// kioslaves
#cmakedefine HAVE_LIBSASL2 1

// kmail
#cmakedefine HAVE_STLNAMESPACE 1
#cmakedefine STD_NAMESPACE_PREFIX @STD_NAMESPACE_PREFIX@

// kaddressbook
#cmakedefine KDEPIM_NEW_DISTRLISTS 1

// kandy
#cmakedefine HAVE_LOCKDEV 1

// mimelib
#ifdef __cplusplus
extern "C" {
#endif
unsigned long strlcpy(char*, const char*, unsigned long);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#endif
unsigned long strlcat(char*, const char*, unsigned long);
#ifdef __cplusplus
}
#endif
