cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

message(VERBOSE "Executing patch step for harfbuzz")

block(SCOPE_FOR VARIABLES)

execute_process(
  WORKING_DIRECTORY "D:/projects collection/platformer/build/_deps/harfbuzz-src"
  COMMAND_ERROR_IS_FATAL LAST
  COMMAND  [====[C:/mingw64/bin/cmake.exe]====] [====[-DHARFBUZZ_DIR=D:/projects collection/platformer/build/_deps/harfbuzz-src]====] [====[-P]====] [====[D:/projects collection/platformer/libs/SFML/tools/harfbuzz/PatchHarfBuzz.cmake]====]
)

endblock()
