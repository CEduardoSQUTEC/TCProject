# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\Jean Paul\CLionProjects\TCProject"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\Jean Paul\CLionProjects\TCProject\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Teo_Py.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Teo_Py.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Teo_Py.dir/flags.make

CMakeFiles/Teo_Py.dir/main.cpp.obj: CMakeFiles/Teo_Py.dir/flags.make
CMakeFiles/Teo_Py.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Jean Paul\CLionProjects\TCProject\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Teo_Py.dir/main.cpp.obj"
	C:\PROGRA~2\mingw32\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Teo_Py.dir\main.cpp.obj -c "C:\Users\Jean Paul\CLionProjects\TCProject\main.cpp"

CMakeFiles/Teo_Py.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Teo_Py.dir/main.cpp.i"
	C:\PROGRA~2\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Jean Paul\CLionProjects\TCProject\main.cpp" > CMakeFiles\Teo_Py.dir\main.cpp.i

CMakeFiles/Teo_Py.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Teo_Py.dir/main.cpp.s"
	C:\PROGRA~2\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Jean Paul\CLionProjects\TCProject\main.cpp" -o CMakeFiles\Teo_Py.dir\main.cpp.s

CMakeFiles/Teo_Py.dir/AFD.cpp.obj: CMakeFiles/Teo_Py.dir/flags.make
CMakeFiles/Teo_Py.dir/AFD.cpp.obj: ../AFD.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Jean Paul\CLionProjects\TCProject\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Teo_Py.dir/AFD.cpp.obj"
	C:\PROGRA~2\mingw32\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Teo_Py.dir\AFD.cpp.obj -c "C:\Users\Jean Paul\CLionProjects\TCProject\AFD.cpp"

CMakeFiles/Teo_Py.dir/AFD.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Teo_Py.dir/AFD.cpp.i"
	C:\PROGRA~2\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Jean Paul\CLionProjects\TCProject\AFD.cpp" > CMakeFiles\Teo_Py.dir\AFD.cpp.i

CMakeFiles/Teo_Py.dir/AFD.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Teo_Py.dir/AFD.cpp.s"
	C:\PROGRA~2\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Jean Paul\CLionProjects\TCProject\AFD.cpp" -o CMakeFiles\Teo_Py.dir\AFD.cpp.s

# Object files for target Teo_Py
Teo_Py_OBJECTS = \
"CMakeFiles/Teo_Py.dir/main.cpp.obj" \
"CMakeFiles/Teo_Py.dir/AFD.cpp.obj"

# External object files for target Teo_Py
Teo_Py_EXTERNAL_OBJECTS =

Teo_Py.exe: CMakeFiles/Teo_Py.dir/main.cpp.obj
Teo_Py.exe: CMakeFiles/Teo_Py.dir/AFD.cpp.obj
Teo_Py.exe: CMakeFiles/Teo_Py.dir/build.make
Teo_Py.exe: CMakeFiles/Teo_Py.dir/linklibs.rsp
Teo_Py.exe: CMakeFiles/Teo_Py.dir/objects1.rsp
Teo_Py.exe: CMakeFiles/Teo_Py.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\Jean Paul\CLionProjects\TCProject\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Teo_Py.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Teo_Py.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Teo_Py.dir/build: Teo_Py.exe

.PHONY : CMakeFiles/Teo_Py.dir/build

CMakeFiles/Teo_Py.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Teo_Py.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Teo_Py.dir/clean

CMakeFiles/Teo_Py.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\Jean Paul\CLionProjects\TCProject" "C:\Users\Jean Paul\CLionProjects\TCProject" "C:\Users\Jean Paul\CLionProjects\TCProject\cmake-build-debug" "C:\Users\Jean Paul\CLionProjects\TCProject\cmake-build-debug" "C:\Users\Jean Paul\CLionProjects\TCProject\cmake-build-debug\CMakeFiles\Teo_Py.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Teo_Py.dir/depend

