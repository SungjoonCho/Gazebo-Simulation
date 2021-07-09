
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
1. Make your project directory $mkdir gazebo_plugin_tutorial
2. $ cd gazebo_plugin_tutorial
3. Cutomize your plugin code. (In this project, use my PointcloudGazebo_pcd.cpp code)
4. Make CMakeLists.txt file(Use my file in github.)
5. Make new directory for building project $ mkdir build $ cd build
6. Compile and build the code $ cmake../ $make
7. Plugin done. You can see libPointcloudGazebo_pcd.so file in build directory.
</pre>

### World
<pre>
8. Then, you have to make your own world to simulate point cloud. 
   Make new world file MyPointcloud_pcd.world.(Use my file in github.)
9. You have to connect plugin file in world file.
</pre>

### Simulate on gazebo
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


- Reference

pcd file :<https://github.com/PointCloudLibrary/data/tree/master/tutorials>

writing plugin : <http://gazebosim.org/tutorials?tut=plugins_hello_world&cat=write_plugin>

