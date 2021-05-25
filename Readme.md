## Gazebo simulation with multicamera (publish rgb, depth image for 3D reconstruction) (ongoing)

* world : 랩실
* gazebo + ros 이용
* Realsense camera n대 달아 각 카메라별로 rgb, depth, ir frame 얻은 후 모두 다른 topic으로 publish -> 3D reconstruction 예정 

## Execute

* Mesh model 다운로드

  http://data.nvision2.eecs.yorku.ca/3DGEMS/ 에서 mesh 파일 다운받아 .gazebo/models로 이동

Plugin 파일 다운로드 & 별도 수정 필요시 빌드 과정
<pre>
  mkdir build_plugin
  cd build_plugin
  git clone https://github.com/pal-robotics/realsense_gazebo_plugin.git
  cd realsense_gazebo_plugin
  mkdir build
  cd build
  cmake ../
  make

* 필요시 plugin_build/realsense_gazebo_plugin/src의 소스코드들 수정하여 다시 빌드
* 수정 & 빌드 완료시 플러그인 파일 위치로 이동
  cd devel/lib

* 빌드된 플러그인 파일 옮기기(model urdf 코드에서 plugin 요청 경로 수정해도 됨)
  sudo cp librealsense_gazebo_gazebo_plugin.so /usr/lib/x86_64-linux-gnu/gazebo-9/plugins/
</pre>

Ros 환경 구성
<pre>
* terminal 1
  roscore

* terminal 2
  mkdir catkin_ws
  cd catkin_ws
  git clone https://github.com/SungjoonCho/gazebo_sim_multicamera.git
  mv gazebo_sim_multicamera src
  catkin_make
  source ./devel/setup.bash
  roslaunch realsense_lab lab_world.launch
</pre>

강제 종료
<pre>
killall gzserver gzclient
</pre>

## 상세 구성

* World
<pre>
world_env.world : world file 

http://data.nvision2.eecs.yorku.ca/3DGEMS/ 에서 mesh 파일 다운받아 .gazebo/models로 이동

gazebo - insert 탭에서 필요한 model insert
</Pre>


* Plugin
<pre>
</pre>

* description
<pre>
  1. roslaunch로 lab_world.launch 호출
     include 태그 안의 value attribute에 부르고자 하는 world 넣기
     필요 argument에 true 기입 (verbose -> error 검출하는데 도움)
     
     param에 부르고자 하는 카메라 모델 xacro 입력 (multi_simulation.xacro 호출함)
     spawn_model python script node로 gazebo에 모델 띄우기
     
   2. multi_simulation.xacro
      카메라 xacro(상세 플러그인, 속성 포함한 파일) 호출
      여기서 카메라의 xyz, rpy 입력
</pre>

## Plugin

realsense_gazebo_plugin-master > build 에서 cmake../ , make 로 빌드 => build > devel > lib에 librealsense_gazebo_plugin.so 플러그인 파일 생성

librealsense_gazebo_plugin.so => src > gazebo_ros_realsense.cpp, RealSensePlugin.cpp로 생성

/usr/lib/x86_64-linux-gnu/gazebo-9/plugins로 옮기기

## Model

/home/jskimlab/.gazebo/models/realsense_camera에 위치

model sdf의 plugin 태그에서 위의 플러그인 불러주기




## 실행

단순 실행시 - $project1/world    gazebo --verbose -s libgazebo_ros_api_plugin.so world_env.world (ros init 위해)

재실행시 - killall gzserver, sudo killall gzserver

새로운 모델 추가시 - $project1/world     sudo gazebo --verbose world_env.world 

## Rviz 

$ rosrun rviz rviz

### Rostopic

$ rostopic list





## 기타 사항

plugin 및 기타 path : /usr/lib/x86_64-linux-gnu/gazebo-9/plugins

## 참고

https://github.com/SyrianSpock/realsense_gazebo_plugin - origin 

https://github.com/pal-robotics/realsense_gazebo_plugin - upgraded for D435

openni 참고하기


