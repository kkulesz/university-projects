# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/demongo/Clion/clion-2019.1.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/demongo/Clion/clion-2019.1.2/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/demongo/EITI/SCZR/repo/SCZR_VoiceChangerSystem

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/demongo/EITI/SCZR/repo/SCZR_VoiceChangerSystem/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/supplier.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/supplier.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/supplier.dir/flags.make

CMakeFiles/supplier.dir/src/Supplier/supplier.cpp.o: CMakeFiles/supplier.dir/flags.make
CMakeFiles/supplier.dir/src/Supplier/supplier.cpp.o: ../src/Supplier/supplier.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/demongo/EITI/SCZR/repo/SCZR_VoiceChangerSystem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/supplier.dir/src/Supplier/supplier.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/supplier.dir/src/Supplier/supplier.cpp.o -c /home/demongo/EITI/SCZR/repo/SCZR_VoiceChangerSystem/src/Supplier/supplier.cpp

CMakeFiles/supplier.dir/src/Supplier/supplier.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/supplier.dir/src/Supplier/supplier.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/demongo/EITI/SCZR/repo/SCZR_VoiceChangerSystem/src/Supplier/supplier.cpp > CMakeFiles/supplier.dir/src/Supplier/supplier.cpp.i

CMakeFiles/supplier.dir/src/Supplier/supplier.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/supplier.dir/src/Supplier/supplier.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/demongo/EITI/SCZR/repo/SCZR_VoiceChangerSystem/src/Supplier/supplier.cpp -o CMakeFiles/supplier.dir/src/Supplier/supplier.cpp.s

CMakeFiles/supplier.dir/src/alsa.cpp.o: CMakeFiles/supplier.dir/flags.make
CMakeFiles/supplier.dir/src/alsa.cpp.o: ../src/alsa.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/demongo/EITI/SCZR/repo/SCZR_VoiceChangerSystem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/supplier.dir/src/alsa.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/supplier.dir/src/alsa.cpp.o -c /home/demongo/EITI/SCZR/repo/SCZR_VoiceChangerSystem/src/alsa.cpp

CMakeFiles/supplier.dir/src/alsa.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/supplier.dir/src/alsa.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/demongo/EITI/SCZR/repo/SCZR_VoiceChangerSystem/src/alsa.cpp > CMakeFiles/supplier.dir/src/alsa.cpp.i

CMakeFiles/supplier.dir/src/alsa.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/supplier.dir/src/alsa.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/demongo/EITI/SCZR/repo/SCZR_VoiceChangerSystem/src/alsa.cpp -o CMakeFiles/supplier.dir/src/alsa.cpp.s

# Object files for target supplier
supplier_OBJECTS = \
"CMakeFiles/supplier.dir/src/Supplier/supplier.cpp.o" \
"CMakeFiles/supplier.dir/src/alsa.cpp.o"

# External object files for target supplier
supplier_EXTERNAL_OBJECTS =

supplier: CMakeFiles/supplier.dir/src/Supplier/supplier.cpp.o
supplier: CMakeFiles/supplier.dir/src/alsa.cpp.o
supplier: CMakeFiles/supplier.dir/build.make
supplier: CMakeFiles/supplier.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/demongo/EITI/SCZR/repo/SCZR_VoiceChangerSystem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable supplier"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/supplier.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/supplier.dir/build: supplier

.PHONY : CMakeFiles/supplier.dir/build

CMakeFiles/supplier.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/supplier.dir/cmake_clean.cmake
.PHONY : CMakeFiles/supplier.dir/clean

CMakeFiles/supplier.dir/depend:
	cd /home/demongo/EITI/SCZR/repo/SCZR_VoiceChangerSystem/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/demongo/EITI/SCZR/repo/SCZR_VoiceChangerSystem /home/demongo/EITI/SCZR/repo/SCZR_VoiceChangerSystem /home/demongo/EITI/SCZR/repo/SCZR_VoiceChangerSystem/cmake-build-debug /home/demongo/EITI/SCZR/repo/SCZR_VoiceChangerSystem/cmake-build-debug /home/demongo/EITI/SCZR/repo/SCZR_VoiceChangerSystem/cmake-build-debug/CMakeFiles/supplier.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/supplier.dir/depend

