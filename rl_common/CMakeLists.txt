cmake_minimum_required(VERSION 2.8.3)
project(rl_common)

find_package(catkin REQUIRED COMPONENTS roscpp)
include_directories(include ${catkin_INCLUDE_DIRS})

catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES rl_common
  CATKIN_DEPENDS roscpp
#  DEPENDS
)

## Mark cpp header files for installation
install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
)

