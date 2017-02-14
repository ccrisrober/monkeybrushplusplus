
include("/home/crodriguez/Desktop/monkeybrushplusplus/CMake/GitExternal.cmake")
execute_process(COMMAND "/usr/bin/git" fetch origin -q
  WORKING_DIRECTORY "/home/crodriguez/Desktop/monkeybrushplusplus/CMake/common")
execute_process(
  COMMAND "/usr/bin/git" show-ref --hash=7 refs/remotes/origin/master
  OUTPUT_VARIABLE newref OUTPUT_STRIP_TRAILING_WHITESPACE
  WORKING_DIRECTORY "/home/crodriguez/Desktop/monkeybrushplusplus/CMake/common")
if(newref)
  file(APPEND /home/crodriguez/Desktop/monkeybrushplusplus/.gitexternals "# CMake/common https://github.com/Eyescale/CMake.git ${newref}\n")
  git_external(CMake/common https://github.com/Eyescale/CMake.git ${newref})
else()
  file(APPEND /home/crodriguez/Desktop/monkeybrushplusplus/.gitexternals "# CMake/common https://github.com/Eyescale/CMake.git dd94e50
")
endif()