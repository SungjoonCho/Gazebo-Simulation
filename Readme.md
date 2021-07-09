## Gazebo simulation with multicamera (publish rgb, depth image for 3D reconstruction) 

* world : Laboratory
* Gazebo + ROS(melodic)
* After installing n Realsense cameras to obtain rgb, depth, and ir frames for each camera, publish them all to different topics -> 3D reconstruction planned

<p align="center">
  <img width="800" height="500" src="https://user-images.githubusercontent.com/80872528/119465879-0eb26280-bd7f-11eb-8f15-3c75bfa9a932.png">
</p>


## Building plugin

Download Mesh model 
* Download files from http://data.nvision2.eecs.yorku.ca/3DGEMS/, move them to .gazebo/models

Builing plugin and modifying 
<pre>
  $ mkdir build_plugin
  $ cd build_plugin
  $ git clone https://github.com/pal-robotics/realsense_gazebo_plugin.git
  $ cd realsense_gazebo_plugin
  $ mkdir build
  $ cd build
  $ cmake ../
  $ make
</pre>

* If necessary, modify the source codes of plugin_build/realsense_gazebo_plugin/src and rebuild
* Go to the plugin file location ($ cd devel/lib) upon modification & build completion
* Move built-in plugin files(Or you can modify the plugin request path in the urdf code of model)
<pre>
$ sudo cp librealsense_gazebo_gazebo_plugin.so /usr/lib/x86_64-linux-gnu/gazebo-9/plugins/
</pre>

## Execute
<pre>
* terminal 1
  $ roscore

* terminal 2
  $ mkdir -p catkin_ws/src
  $ cd catkin_ws/src
  Download gazebo_sim_multicamera directory
  $ cd ..
  $ catkin_make
  $ source ./devel/setup.bash
  $ roslaunch realsense_lab lab_world.launch
</pre>

Force quit
<pre>
$ killall gzserver gzclient
</pre>

## Configuration

World
* world_env.world : world file 

Model
* Drag & Drop model from insert tab in menu
* When editing the world file, if it is not saved by **save as**, open the file with sudo.

Plugin
* RealSensePlugin.cpp, gazebo_ros_realsense.cpp both required.

RealSensePlugin.cpp
* Parsing camera parameters tag from model urdf to set parameter value and publish topic
* After creating a SensorManager in Get Cameras Renderers part, it acquires each camera frame with **sensor** tag and **name** attribute in urdf

Description

  1. Run lab_world.launch
     * Put the world you want to call in the **value** attribute in the **include** tag
     * Write **true** in the required argument (verbose -> help to detect errors)
     
     * Input the camera model xacro you want to call with param
     * **spawn_model** python script node - Put model on gazebo
     
     
   2. Call multi_simulation.xacro      
      * Input camera's xyz, rpy, prefix (set by each camera alias)
      * A total of 3 cameras have been used. If necessary, you can add n cameras by using the above information.
      * Call realsense.macro.xacro(including sensor attribute, plugin)
      
   3. realsense.macro.xacro
      * Include camera properties and information, receive prefix
      * Be sure to include above prefix number in the name attribute of sensor and plugin
      - It not, the same image will be published.
     
## Rviz 
<pre>
$ rosrun rviz rviz
</pre>

<p align="center">
  <img width="800" height="500" src="https://user-images.githubusercontent.com/80872528/119466531-aa43d300-bd7f-11eb-8c38-dd6412a49259.png">
</p>

## Rostopic
<pre>
$ rostopic list
</pre>

<pre>
/clock
/gazebo/link_states
/gazebo/model_states
/gazebo/parameter_descriptions
/gazebo/parameter_updates
/gazebo/set_link_state
/gazebo/set_model_state
/joint_states
/realsense1r200/realsense1/color/camera_info
/realsense1r200/realsense1/color/image
/realsense1r200/realsense1/color/image/compressed
/realsense1r200/realsense1/color/image/compressed/parameter_descriptions
/realsense1r200/realsense1/color/image/compressed/parameter_updates
/realsense1r200/realsense1/color/image/compressedDepth
/realsense1r200/realsense1/color/image/compressedDepth/parameter_descriptions
/realsense1r200/realsense1/color/image/compressedDepth/parameter_updates
/realsense1r200/realsense1/color/image/theora
/realsense1r200/realsense1/color/image/theora/parameter_descriptions
/realsense1r200/realsense1/color/image/theora/parameter_updates
/realsense1r200/realsense1/depth/camera_info
/realsense1r200/realsense1/depth/image
/realsense1r200/realsense1/depth/image/compressed
/realsense1r200/realsense1/depth/image/compressed/parameter_descriptions
/realsense1r200/realsense1/depth/image/compressed/parameter_updates
/realsense1r200/realsense1/depth/image/compressedDepth
/realsense1r200/realsense1/depth/image/compressedDepth/parameter_descriptions
/realsense1r200/realsense1/depth/image/compressedDepth/parameter_updates
/realsense1r200/realsense1/depth/image/theora
/realsense1r200/realsense1/depth/image/theora/parameter_descriptions
/realsense1r200/realsense1/depth/image/theora/parameter_updates
/realsense1r200/realsense1/ir1/camera_info
/realsense1r200/realsense1/ir1/image
/realsense1r200/realsense1/ir1/image/compressed
/realsense1r200/realsense1/ir1/image/compressed/parameter_descriptions
/realsense1r200/realsense1/ir1/image/compressed/parameter_updates
/realsense1r200/realsense1/ir1/image/compressedDepth
/realsense1r200/realsense1/ir1/image/compressedDepth/parameter_descriptions
/realsense1r200/realsense1/ir1/image/compressedDepth/parameter_updates
/realsense1r200/realsense1/ir1/image/theora
/realsense1r200/realsense1/ir1/image/theora/parameter_descriptions
/realsense1r200/realsense1/ir1/image/theora/parameter_updates
/realsense1r200/realsense1/ir2/camera_info
/realsense1r200/realsense1/ir2/image
/realsense1r200/realsense1/ir2/image/compressed
/realsense1r200/realsense1/ir2/image/compressed/parameter_descriptions
/realsense1r200/realsense1/ir2/image/compressed/parameter_updates
/realsense1r200/realsense1/ir2/image/compressedDepth
/realsense1r200/realsense1/ir2/image/compressedDepth/parameter_descriptions
/realsense1r200/realsense1/ir2/image/compressedDepth/parameter_updates
/realsense1r200/realsense1/ir2/image/theora
/realsense1r200/realsense1/ir2/image/theora/parameter_descriptions
/realsense1r200/realsense1/ir2/image/theora/parameter_updates
..
/realsense2r200/realsense2/..
..
/realsense3r200/realsense3/..
</pre>

## Reference
* https://github.com/IntelRealSense/realsense-ros
* https://github.com/SyrianSpock/realsense_gazebo_plugin - origin
* https://github.com/pal-robotics/realsense_gazebo_plugin - upgraded for D435

---

## Pointcloud on Gazebo

<img src="https://user-images.githubusercontent.com/80872528/115204849-e8702600-a133-11eb-84a5-a6a3813ff9a9.png"> </img>


I located each point of Pointcloud in pcd file on Gazebo to see as 3D and 

know whether there is a conflict with points and a robot, moving around in gazebo world.

First, you have to customize your own plugin. There’s no plugin that make pointcloud on gazebo.

It will help you to get pointcloud file(.pcd) from local then insert spheres for each point on gazebo. 

One sphere will be a one point. Each point has x,y,z pose values.

Second, make your own world and insert plugin that you customized before. 

When you simulate your world, the connected plugin will make huge point cloud but it will take a long time for computer.

### Plugin & CmakeLists.txt
<pre>
1. Make your project directory $mkdir -p gazebo_plugin_tutorial/src
2. $ cd gazebo_plugin_tutorial/src
3. Cutomize your plugin code. (In this project, use my gazebo_sim_pointcloud/PointcloudGazebo_pcd.cpp code)
4. Make CMakeLists.txt file(Use my file in github.)
5. Make new directory for building project $ mkdir build $ cd build
6. Compile and build the code $ cmake../ $make
7. Plugin done. You can see libPointcloudGazebo_pcd.so file in build directory.
</pre>

## World
<pre>
8. Then, you have to make your own world to simulate point cloud. 
   Make new world file MyPointcloud_pcd.world.(Use my file in github.)
9. You have to connect plugin file in world file.
</pre>

## Simulate on gazebo
<pre>
10. In terminal2, change directory to project directory and type 
    (If you write below command in bashrc, it's very convenient. $gedit ~/.bashrc)
    export GAZEBO_PLUGIN_PATH=$HOME/gazebo_plugin_tutorial/build:$GAZEBO_PLUGIN_PATH
11. These will make you to access plugin what you customized. 
12. Simulate $gazebo --verbose MyPointcloud_pcd.world
13. “--verbose” helps you know progress. If there are errors, it means something wrong. 
    You have to fix it for correct simulation.
 
    It takes few time for inserting spheres(mean each points in point clouds).
</pre>


## Reference
* pcd file :<https://github.com/PointCloudLibrary/data/tree/master/tutorials>
* writing plugin : <http://gazebosim.org/tutorials?tut=plugins_hello_world&cat=write_plugin>


