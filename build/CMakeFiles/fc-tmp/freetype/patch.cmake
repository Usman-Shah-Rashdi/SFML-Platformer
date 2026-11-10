cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

message(VERBOSE "Executing patch step for freetype")

block(SCOPE_FOR VARIABLES)

execute_process(
  WORKING_DIRECTORY "D:/projects collection/platformer/build/_deps/freetype-src"
  COMMAND_ERROR_IS_FATAL LAST
  COMMAND  [====[C:/mingw64/bin/cmake.exe]====] [====[-DFREETYPE_DIR=D:/projects collection/platformer/build/_deps/freetype-src]====] [====[-P]====] [====[D:/projects collection/platformer/libs/SFML/tools/freetype/PatchFreetype.cmake]====]
)

endblock()
