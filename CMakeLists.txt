cmake_minimum_required(VERSION 2.8.3)
project(visual_coslam)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  geometry_msgs
  image_transport
  cv_bridge
  ar_track_alvar
  message_generation
  tf
)

find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)
find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)
set(CUSTOM_OPENCV_DIR "/home/jacob/opencv-2.4.10.1/install")
find_package(OpenCV REQUIRED PATHS ${CUSTOM_OPENCV_DIR} NO_DEFAULT_PATH)
#find_package(Hiredis REQUIRED)
find_package(VisualSLAM REQUIRED)
#set(VisualSLAM_INCLUDE_DIRS /usr/local/include/VisualSLAM)
#set(VisualSLAM_LIBRARIES /usr/local/lib/libVisualSLAM.a)
find_package(CG REQUIRED)
find_package(wxWidgets 3.0 EXACT COMPONENTS core base gl REQUIRED)
message(WARNING "JACOB ${wxWidgets_LIBRARIES} ${wxWidgets_USE_FILE} ${wxWidgets_INCLUDE_DIRS}")
## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend tag for "message_generation"
##   * add a build_depend and a run_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependency has been pulled in
##     but can be declared for certainty nonetheless:
##     * add a run_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

## Generate messages in the 'msg' folder
add_message_files(
  DIRECTORY msg
  FILES
  features.msg
)
generate_messages(DEPENDENCIES std_msgs)

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

## To declare and build dynamic reconfigure parameters within this
## package, follow these steps:
## * In the file package.xml:
##   * add a build_depend and a run_depend tag for "dynamic_reconfigure"
## * In this file (CMakeLists.txt):
##   * add "dynamic_reconfigure" to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * uncomment the "generate_dynamic_reconfigure_options" section below
##     and list every .cfg file to be processed

## Generate dynamic reconfigure parameters in the 'cfg' folder
# generate_dynamic_reconfigure_options(
#   cfg/DynReconf1.cfg
#   cfg/DynReconf2.cfg
# )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES visual_coslam
#  CATKIN_DEPENDS cv_bridge geometry_msgs image_transport roscpp
#  DEPENDS system_lib
)

###########
## Build ##
###########


## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
#TODO change put headers in 'include' directory
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIRS}
  ${GLUT_INCLUDE_DIRS}
  ${GLEW_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${VisualSLAM_INCLUDE_DIRS}
  #${HIREDIS_INCLUDE_DIRS}
  ${CG_INCLUDE_DIRS}
  include
  #${wxWidgets_INCLUDE_DIRS}
)
include_directories("${VisualSLAM_INCLUDE_DIRS}/VisualSLAM/")

include("${wxWidgets_USE_FILE}")

add_definitions(-DV3DLIB_GPGPU_ENABLE_CG -DV3DLIB_ENABLE_GPGPU )

## Declare a C++ library
# add_library(visual_coslam
#   src/${PROJECT_NAME}/visual_coslam.cpp
# )

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(visual_coslam ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Set source files
set(COSLAM_APP
  src/app/APP_OfflineMain_Reloc.cpp
  src/app/APP_OfflineMain.cpp
  src/app/APP_USBCamMain.cpp
  src/app/APP_ROSMain.cpp
  src/app/APP_ROSMain_features.cpp
  src/app/SL_CoSLAM.cpp
  src/app/SL_CoSLAMBA.cpp
  src/app/SL_CoSLAMRobustBA.cpp
  src/app/SL_GlobParam.cpp
  src/app/SL_InitMap.cpp
  src/app/SL_InterCamPoseEstimator.cpp
  src/app/SL_MergeCameraGroup.cpp
  src/app/SL_NewMapPointsInterCam.cpp
  src/app/SL_Relocalization.cpp
  src/app/SL_SingleSLAM.cpp
  #src/redis/cbredisclient.cpp
  src/redis/PosVelKF.cpp
)

set(COSLAM_GUI
  src/gui/CoSLAMThread.cpp
  src/gui/GLHelper.cpp
  src/gui/GLImagePane.cpp
  src/gui/GLImageWnd.cpp
  src/gui/GLScenePane.cpp
  src/gui/GLScenePaneHelper.cpp
  src/gui/GLSceneWnd.cpp
  src/gui/GLTrackballPane.cpp
  src/gui/MainDialog.cpp
  src/gui/MyApp.cpp
  src/gui/trackball.cpp
)

set(COSLAM_SLAM
  src/slam/SL_Camera.cpp
  src/slam/SL_CoSLAMHelper.cpp
  src/slam/SL_FeatureMatching.cpp
  src/slam/SL_FeaturePoint.cpp
  src/slam/SL_FeaturePoints.cpp
  src/slam/SL_GlobalPoseEstimation.cpp
  src/slam/SL_InitMapHelper.cpp
  src/slam/SL_IntraCamPose.cpp
  src/slam/SL_IntraCamPoseEstimator.cpp
  src/slam/SL_KeyPoseList.cpp
  src/slam/SL_MapPoint.cpp
  src/slam/SL_MapPointList.cpp
  src/slam/SL_NCCBlock.cpp
  src/slam/SL_SLAMHelper.cpp
  src/slam/SL_SolvePnP.cpp
)

set(COSLAM_TRACKING
  src/tracking/BriefExtractor.cpp
  src/tracking/SL_Track2D.cpp
  src/tracking/CoSL_FeatureTracker.cpp
  src/tracking/CVKLTTracker.cpp
  src/tracking/GPUKLT.cpp
  include/CGKLT/v3d_gpubase.cpp
  include/CGKLT/v3d_gpuflow.cpp
  include/CGKLT/v3d_gpuklt.cpp
  include/CGKLT/v3d_gpupyramid.cpp
  include/CGKLT/v3d_gpuundistort.cpp
  include/CGKLT/v3d_image.cpp
)

set(COSLAM_VIDEO_READER
  src/video_reader/VR_AVIReader.cpp
  src/video_reader/VR_ROSReader.cpp
  src/video_reader/VR_USBCamReader.cpp
)

## Set library dependencies
set(COSLAM_LIB
	lapack
	blas
	swscale
	avformat
	avutil
	avcodec
	GL
	GLEW
  #CgGL
	glut 
	GLU
)

## Declare a C++ executable
add_executable(visual_coslam
  ${COSLAM_APP}
  ${COSLAM_GUI}
  ${COSLAM_SLAM}
  ${COSLAM_TRACKING}
  ${COSLAM_VIDEO_READER}									
)

### Add cmake target dependencies of the executable
### same as for the library above
## add_dependencies(visual_coslam ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#
### Specify libraries to link a library or executable target against
target_link_libraries(visual_coslam
  ${catkin_LIBRARIES}
  ${VisualSLAM_LIBRARY}
  #${VisualSLAM_LIBRARIES}
  #${OpenCV_LIBS}
  ${OpenCV_LIBRARIES}
  ${CG_LIBRARIES}
  ${CG_GL_LIBRARIES}
  #${HIREDIS_LIBRARIES}
  ${COSLAM_LIB}
  ${wxWidgets_LIBRARIES}
)

add_executable(feature_receiver src/feature_receiver.cpp)
target_link_libraries(feature_receiver
  ${catkin_LIBRARIES}
)

add_executable(video_receiver src/video_receiver.cpp)
target_link_libraries(video_receiver
  ${catkin_LIBRARIES}
)

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS visual_coslam visual_coslam_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_visual_coslam.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
