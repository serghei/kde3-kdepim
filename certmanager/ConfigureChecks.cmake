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

# get MAX_CMD_LENGTH
message( STATUS "Checking for maximum argument length" )
execute_process(
  COMMAND getconf ARG_MAX
  OUTPUT_VARIABLE MAX_CMD_LENGTH
  RESULT_VARIABLE _result
  OUTPUT_STRIP_TRAILING_WHITESPACE )
if( _result )
  kde_message_fatal( "Unable to run getconf!\n MAX_CMD_LENGTH cannot be determined." )
endif()
math( EXPR MAX_CMD_LENGTH "(${MAX_CMD_LENGTH} / 4) * 3" )
# Work around a 64 bit bug in the CMake math function above
if( NOT MAX_CMD_LENGTH )
  execute_process(
    COMMAND getconf ARG_MAX
    OUTPUT_VARIABLE MAX_CMD_LENGTH
    RESULT_VARIABLE _result
    OUTPUT_STRIP_TRAILING_WHITESPACE )
endif()
message( STATUS "  found ${MAX_CMD_LENGTH}" )
set( MAX_CMD_LENGTH ${MAX_CMD_LENGTH} CACHE INTERNAL "" FORCE )
