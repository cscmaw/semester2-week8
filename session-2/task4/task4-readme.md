# Task 4: Creating a project Makefile

## Code and basic Makefile

The code has been organised into project `src/` and `include/` folders.

The `Makefile` provided assumes files are all in the same folder.

## Step 1 - source code and header files

C-files in the `src/` folder include header files that are in a different location.

Relative to the source code the header files are in the `../include/` folder.

Modify the source code files to `#include` header files from the correct location.

## Step 2 - Makefile

The `Makefile` is in the top level folder and all the files that are used or produced are in a lower level folder. 

We have to modify occurences of each filename in the `Makfile` with the appropriate location

- Source code (.c) files should be `src/*.c`
- Header (.h) files should be `include/*.h`
- Object (.o) files should be `obj/*.o`
- Executable file should be `bin/student`

Once you have made the modifications test the `make` command.

Test the executable in the `bin/` folder.

Test `make clean`.

## Step 3 - extension - a more generic Makefile

The file `Make2` contains a more generic Makefile structure
- This avoids having to make multiple changes across the Makefile
- Folder and file definition is provided at the top
- Build commands are completely generic

We can test this Makefile using the `make -f` command which allows Makefile naming.

`make -f Make2`

You should verify that the code builds as before.

`make -f Make2 clean` will tidy up.
