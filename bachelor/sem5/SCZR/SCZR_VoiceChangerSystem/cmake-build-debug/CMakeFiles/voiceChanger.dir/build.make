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
include CMakeFiles/voiceChanger.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/voiceChanger.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/voiceChanger.dir/flags.make

CMakeFiles/voiceChanger.dir/src/VoiceChanger/voiceChanger.cpp.o: CMakeFiles/voiceChanger.dir/flags.make
CMakeFiles/voiceChanger.dir/src/VoiceChanger/voiceChanger.cpp.o: ../src/VoiceChanger/voiceChanger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/demongo/EITI/SCZR/repo/SCZR_VoiceChangerSystem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/voiceChanger.dir/src/VoiceChanger/voiceChanger.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/voiceChanger.dir/src/VoiceChanger/voiceChanger.cpp.o -c /home/demongo/EITI/SCZR/repo/SCZR_VoiceChangerSystem/src/VoiceChanger/voiceChanger.cpp

CMakeFiles/voiceChanger.dir/src/VoiceChanger/voiceChanger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/voiceChanger.dir/src/VoiceChanger/voiceChanger.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/demongo/EITI/SCZR/repo/SCZR_VoiceChangerSystem/src/VoiceChanger/voiceChanger.cpp > CMakeFiles/voiceChanger.dir/src/VoiceChanger/voiceChanger.cpp.i

CMakeFiles/voiceChanger.dir/src/VoiceChanger/voiceChanger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/voiceChanger.dir/src/VoiceChanger/voiceChanger.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/demongo/EITI/SCZR/repo/SCZR_VoiceChangerSystem/src/VoiceChanger/voiceChanger.cpp -o CMakeFiles/voiceChanger.dir/src/VoiceChanger/voiceChanger.cpp.s

CMakeFiles/voiceChanger.dir/src/alsa.cpp.o: CMakeFiles/voiceChanger.dir/flags.make
CMakeFiles/voiceChanger.dir/src/alsa.cpp.o: ../src/alsa.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/demongo/EITI/SCZR/repo/SCZR_VoiceChangerSystem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/voiceChanger.dir/src/alsa.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/voiceChanger.dir/src/alsa.cpp.o -c /home/demongo/EITI/SCZR/repo/SCZR_VoiceChangerSystem/src/alsa.cpp

CMakeFiles/voiceChanger.dir/src/alsa.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/voiceChanger.dir/src/alsa.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/demongo/EITI/SCZR/repo/SCZR_VoiceChangerSystem/src/alsa.cpp > CMakeFiles/voiceChanger.dir/src/alsa.cpp.i

CMakeFiles/voiceChanger.dir/src/alsa.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/voiceChanger.dir/src/alsa.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/demongo/EITI/SCZR/repo/SCZR_VoiceChangerSystem/src/alsa.cpp -o CMakeFiles/voiceChanger.dir/src/alsa.cpp.s

# Object files for target voiceChanger
voiceChanger_OBJECTS = \
"CMakeFiles/voiceChanger.dir/src/VoiceChanger/voiceChanger.cpp.o" \
"CMakeFiles/voiceChanger.dir/src/alsa.cpp.o"

# External object files for target voiceChanger
voiceChanger_EXTERNAL_OBJECTS =

voiceChanger: CMakeFiles/voiceChanger.dir/src/VoiceChanger/voiceChanger.cpp.o
voiceChanger: CMakeFiles/voiceChanger.dir/src/alsa.cpp.o
voiceChanger: CMakeFiles/voiceChanger.dir/build.make
voiceChanger: CMakeFiles/voiceChanger.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/demongo/EITI/SCZR/repo/SCZR_VoiceChangerSystem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable voiceChanger"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/voiceChanger.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/voiceChanger.dir/build: voiceChanger

.PHONY : CMakeFiles/voiceChanger.dir/build

CMakeFiles/voiceChanger.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/voiceChanger.dir/cmake_clean.cmake
.PHONY : CMakeFiles/voiceChanger.dir/clean

CMakeFiles/voiceChanger.dir/depend:
	cd /home/demongo/EITI/SCZR/repo/SCZR_VoiceChangerSystem/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/demongo/EITI/SCZR/repo/SCZR_VoiceChangerSystem /home/demongo/EITI/SCZR/repo/SCZR_VoiceChangerSystem /home/demongo/EITI/SCZR/repo/SCZR_VoiceChangerSystem/cmake-build-debug /home/demongo/EITI/SCZR/repo/SCZR_VoiceChangerSystem/cmake-build-debug /home/demongo/EITI/SCZR/repo/SCZR_VoiceChangerSystem/cmake-build-debug/CMakeFiles/voiceChanger.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/voiceChanger.dir/depend
