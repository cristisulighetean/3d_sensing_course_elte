# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.23.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.23.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/cristiansulighetean/Documents/eit_master/budapest/3d_sensing_sensor_fusion/practice/01_naive_stereo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/cristiansulighetean/Documents/eit_master/budapest/3d_sensing_sensor_fusion/practice/01_naive_stereo/build

# Include any dependencies generated for this target.
include CMakeFiles/OpenCV_naive_stereo.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/OpenCV_naive_stereo.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/OpenCV_naive_stereo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OpenCV_naive_stereo.dir/flags.make

CMakeFiles/OpenCV_naive_stereo.dir/src/main.cpp.o: CMakeFiles/OpenCV_naive_stereo.dir/flags.make
CMakeFiles/OpenCV_naive_stereo.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/OpenCV_naive_stereo.dir/src/main.cpp.o: CMakeFiles/OpenCV_naive_stereo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cristiansulighetean/Documents/eit_master/budapest/3d_sensing_sensor_fusion/practice/01_naive_stereo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/OpenCV_naive_stereo.dir/src/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OpenCV_naive_stereo.dir/src/main.cpp.o -MF CMakeFiles/OpenCV_naive_stereo.dir/src/main.cpp.o.d -o CMakeFiles/OpenCV_naive_stereo.dir/src/main.cpp.o -c /Users/cristiansulighetean/Documents/eit_master/budapest/3d_sensing_sensor_fusion/practice/01_naive_stereo/src/main.cpp

CMakeFiles/OpenCV_naive_stereo.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpenCV_naive_stereo.dir/src/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cristiansulighetean/Documents/eit_master/budapest/3d_sensing_sensor_fusion/practice/01_naive_stereo/src/main.cpp > CMakeFiles/OpenCV_naive_stereo.dir/src/main.cpp.i

CMakeFiles/OpenCV_naive_stereo.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpenCV_naive_stereo.dir/src/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cristiansulighetean/Documents/eit_master/budapest/3d_sensing_sensor_fusion/practice/01_naive_stereo/src/main.cpp -o CMakeFiles/OpenCV_naive_stereo.dir/src/main.cpp.s

# Object files for target OpenCV_naive_stereo
OpenCV_naive_stereo_OBJECTS = \
"CMakeFiles/OpenCV_naive_stereo.dir/src/main.cpp.o"

# External object files for target OpenCV_naive_stereo
OpenCV_naive_stereo_EXTERNAL_OBJECTS =

OpenCV_naive_stereo: CMakeFiles/OpenCV_naive_stereo.dir/src/main.cpp.o
OpenCV_naive_stereo: CMakeFiles/OpenCV_naive_stereo.dir/build.make
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_gapi.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_stitching.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_alphamat.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_aruco.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_barcode.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_bgsegm.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_bioinspired.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_ccalib.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_dnn_objdetect.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_dnn_superres.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_dpm.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_face.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_freetype.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_fuzzy.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_hfs.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_img_hash.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_intensity_transform.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_line_descriptor.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_mcc.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_quality.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_rapid.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_reg.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_rgbd.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_saliency.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_sfm.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_stereo.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_structured_light.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_superres.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_surface_matching.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_tracking.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_videostab.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_viz.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_wechat_qrcode.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_xfeatures2d.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_xobjdetect.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_xphoto.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_shape.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_highgui.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_datasets.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_plot.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_text.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_ml.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_phase_unwrapping.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_optflow.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_ximgproc.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_video.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_videoio.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_imgcodecs.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_objdetect.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_calib3d.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_dnn.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_features2d.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_flann.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_photo.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_imgproc.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libopencv_core.4.6.0.dylib
OpenCV_naive_stereo: /opt/homebrew/lib/libomp.dylib
OpenCV_naive_stereo: CMakeFiles/OpenCV_naive_stereo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/cristiansulighetean/Documents/eit_master/budapest/3d_sensing_sensor_fusion/practice/01_naive_stereo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable OpenCV_naive_stereo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OpenCV_naive_stereo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OpenCV_naive_stereo.dir/build: OpenCV_naive_stereo
.PHONY : CMakeFiles/OpenCV_naive_stereo.dir/build

CMakeFiles/OpenCV_naive_stereo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OpenCV_naive_stereo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OpenCV_naive_stereo.dir/clean

CMakeFiles/OpenCV_naive_stereo.dir/depend:
	cd /Users/cristiansulighetean/Documents/eit_master/budapest/3d_sensing_sensor_fusion/practice/01_naive_stereo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/cristiansulighetean/Documents/eit_master/budapest/3d_sensing_sensor_fusion/practice/01_naive_stereo /Users/cristiansulighetean/Documents/eit_master/budapest/3d_sensing_sensor_fusion/practice/01_naive_stereo /Users/cristiansulighetean/Documents/eit_master/budapest/3d_sensing_sensor_fusion/practice/01_naive_stereo/build /Users/cristiansulighetean/Documents/eit_master/budapest/3d_sensing_sensor_fusion/practice/01_naive_stereo/build /Users/cristiansulighetean/Documents/eit_master/budapest/3d_sensing_sensor_fusion/practice/01_naive_stereo/build/CMakeFiles/OpenCV_naive_stereo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OpenCV_naive_stereo.dir/depend

