# Branch:
   execute_process(COMMAND "/usr/bin/git" branch 1.9
     RESULT_VARIABLE hadbranch ERROR_VARIABLE error
     WORKING_DIRECTORY /home/crodriguez/Desktop/monkeybrushplusplus)
   if(NOT hadbranch)
     execute_process(COMMAND "/usr/bin/git" push origin 1.9
      WORKING_DIRECTORY "/home/crodriguez/Desktop/monkeybrushplusplus")
   endif()
   set(TAG_BRANCH 1.9)

   # Create or move tag
   execute_process(
     COMMAND "/usr/bin/git" tag -f 1.9.2 
     COMMAND "/usr/bin/git" push --tags
     RESULT_VARIABLE notdone WORKING_DIRECTORY "/home/crodriguez/Desktop/monkeybrushplusplus")
   if(notdone)
     message(FATAL_ERROR
        "Error creating tag 1.9.2 on branch ")
   endif()