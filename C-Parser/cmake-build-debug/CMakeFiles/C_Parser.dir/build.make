# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.2.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = G:\Code\Compiler\C-Parser

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = G:\Code\Compiler\C-Parser\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/C_Parser.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/C_Parser.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/C_Parser.dir/flags.make

CMakeFiles/C_Parser.dir/main.cpp.obj: CMakeFiles/C_Parser.dir/flags.make
CMakeFiles/C_Parser.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=G:\Code\Compiler\C-Parser\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/C_Parser.dir/main.cpp.obj"
	C:\MinGW\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\C_Parser.dir\main.cpp.obj -c G:\Code\Compiler\C-Parser\main.cpp

CMakeFiles/C_Parser.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/C_Parser.dir/main.cpp.i"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E G:\Code\Compiler\C-Parser\main.cpp > CMakeFiles\C_Parser.dir\main.cpp.i

CMakeFiles/C_Parser.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/C_Parser.dir/main.cpp.s"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S G:\Code\Compiler\C-Parser\main.cpp -o CMakeFiles\C_Parser.dir\main.cpp.s

CMakeFiles/C_Parser.dir/scan.cpp.obj: CMakeFiles/C_Parser.dir/flags.make
CMakeFiles/C_Parser.dir/scan.cpp.obj: ../scan.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=G:\Code\Compiler\C-Parser\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/C_Parser.dir/scan.cpp.obj"
	C:\MinGW\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\C_Parser.dir\scan.cpp.obj -c G:\Code\Compiler\C-Parser\scan.cpp

CMakeFiles/C_Parser.dir/scan.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/C_Parser.dir/scan.cpp.i"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E G:\Code\Compiler\C-Parser\scan.cpp > CMakeFiles\C_Parser.dir\scan.cpp.i

CMakeFiles/C_Parser.dir/scan.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/C_Parser.dir/scan.cpp.s"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S G:\Code\Compiler\C-Parser\scan.cpp -o CMakeFiles\C_Parser.dir\scan.cpp.s

CMakeFiles/C_Parser.dir/semanteme.cpp.obj: CMakeFiles/C_Parser.dir/flags.make
CMakeFiles/C_Parser.dir/semanteme.cpp.obj: ../semanteme.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=G:\Code\Compiler\C-Parser\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/C_Parser.dir/semanteme.cpp.obj"
	C:\MinGW\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\C_Parser.dir\semanteme.cpp.obj -c G:\Code\Compiler\C-Parser\semanteme.cpp

CMakeFiles/C_Parser.dir/semanteme.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/C_Parser.dir/semanteme.cpp.i"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E G:\Code\Compiler\C-Parser\semanteme.cpp > CMakeFiles\C_Parser.dir\semanteme.cpp.i

CMakeFiles/C_Parser.dir/semanteme.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/C_Parser.dir/semanteme.cpp.s"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S G:\Code\Compiler\C-Parser\semanteme.cpp -o CMakeFiles\C_Parser.dir\semanteme.cpp.s

# Object files for target C_Parser
C_Parser_OBJECTS = \
"CMakeFiles/C_Parser.dir/main.cpp.obj" \
"CMakeFiles/C_Parser.dir/scan.cpp.obj" \
"CMakeFiles/C_Parser.dir/semanteme.cpp.obj"

# External object files for target C_Parser
C_Parser_EXTERNAL_OBJECTS =

C_Parser.exe: CMakeFiles/C_Parser.dir/main.cpp.obj
C_Parser.exe: CMakeFiles/C_Parser.dir/scan.cpp.obj
C_Parser.exe: CMakeFiles/C_Parser.dir/semanteme.cpp.obj
C_Parser.exe: CMakeFiles/C_Parser.dir/build.make
C_Parser.exe: CMakeFiles/C_Parser.dir/linklibs.rsp
C_Parser.exe: CMakeFiles/C_Parser.dir/objects1.rsp
C_Parser.exe: CMakeFiles/C_Parser.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=G:\Code\Compiler\C-Parser\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable C_Parser.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\C_Parser.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/C_Parser.dir/build: C_Parser.exe

.PHONY : CMakeFiles/C_Parser.dir/build

CMakeFiles/C_Parser.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\C_Parser.dir\cmake_clean.cmake
.PHONY : CMakeFiles/C_Parser.dir/clean

CMakeFiles/C_Parser.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" G:\Code\Compiler\C-Parser G:\Code\Compiler\C-Parser G:\Code\Compiler\C-Parser\cmake-build-debug G:\Code\Compiler\C-Parser\cmake-build-debug G:\Code\Compiler\C-Parser\cmake-build-debug\CMakeFiles\C_Parser.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/C_Parser.dir/depend

