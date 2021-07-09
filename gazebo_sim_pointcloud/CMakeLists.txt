cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(gazebo_plugin_tutorial)

find_package(gazebo REQUIRED)
find_package(catkin REQUIRED COMPONENTS std_msgs roscpp pcl_conversions pcl_ros)
find_package(ignition-transport4 REQUIRED)
# find_package(PCL 1.2 REQUIRED)

include_directories(${GAZEBO_INCLUDE_DIRS})
include_directories(${catkin_INCLUDE_DIRS})
include_directories(${roscpp_INCLUDE_DIRS})
include_directories(${std_msgs_INCLUDE_DIRS})
include_directories(${PCL_INCLUDE_DIRS})

link_directories(${GAZEBO_LIBRARY_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")


add_definitions(${PCL_DEFINITIONS})
add_library(PointcloudGazebo_pcd SHARED PointcloudGazebo_pcd.cpp)

target_link_libraries(
  PointcloudGazebo_pcd
  ${GAZEBO_LIBRARIES}
  ${catkin_LIBRARIES}
  ${roscpp_LIBRARIES}
  ${PCL_LIBRARIES}
  ignition-transport4::ignition-transport4
)


if (${gazebo_VERSION_MAJOR} LESS 6)
  include(FindBoost)
  find_package(Boost ${MIN_BOOST_VERSION} REQUIRED system filesystem regex)
  target_link_libraries(PointcloudGazebo_pcd ${GAZEBO_LIBRARIES} ${Boost_LIBRARIES})
else()
  target_link_libraries(PointcloudGazebo_pcd ${GAZEBO_LIBRARIES})
endif()
