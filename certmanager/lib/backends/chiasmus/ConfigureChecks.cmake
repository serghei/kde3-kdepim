#################################################
#
#  (C) 2010-2012 Serghei Amelian
#  serghei (DOT) amelian (AT) gmail.com
#
#  Improvements and feedback are welcome
#
#  This file is released under GPL >= 2
#
#################################################

include( CheckCSourceCompiles )

check_c_source_compiles("
    union { int one; const char * two } foo = { .two = \"Hello\" };
    int main() { return 0; }"
  HAVE_C99_INITIALIZERS )
