## Gazebo simulation with multicamera (publish rgb, depth image for 3D reconstruction) 

* world : 랩실
* gazebo + ros 이용
* Realsense camera n대 달아 각 카메라별로 rgb, depth, ir frame 얻은 후 모두 다른 topic으로 publish -> 3D reconstruction 예정 

<p align="center">
  <img width="800" height="500" src="https://user-images.githubusercontent.com/80872528/119465879-0eb26280-bd7f-11eb-8f15-3c75bfa9a932.png">
</p>


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

world 파일 수정시 save as 해서 저장 안되면 sudo 붙여서 파일 열고 저장해보기
</Pre>


* Plugin
<pre>
RealSensePlugin.cpp, gazebo_ros_realsense.cpp 모두 필수

RealSensePlugin.cpp
model urdf 내의 Camera parameters tag 파싱하여 파라미터 값, publish 토픽 설정
Get Cameras Renderers 부분에서 SensorManager 만든 후 urdf 내의 sensor tag, name attribute로 각 카메라 프레임 획득
</pre>

* description
<pre>
  1. roslaunch로 lab_world.launch 호출
     include 태그 안의 value attribute에 부르고자 하는 world 넣기
     필요 argument에 true 기입 (verbose -> error 검출하는데 도움)
     
     param에 부르고자 하는 카메라 모델 xacro 입력 (multi_simulation.xacro 호출함)
     spawn_model python script node로 gazebo에 모델 띄우기
     
     multi_simulation.xacro 호출
     
   2. multi_simulation.xacro      
      여기서 카메라의 xyz, rpy, prefix(각 카메라 별명으로 설정) 입력
      카메라 총 3대 입력하였으며 필요시 위 정보 기입하여 n대 추가 가능
      realsense.macro.xacro(상세 플러그인, 속성 포함한 파일) 호출
      
   3. realsense.macro.xacro
      카메라의 속성 및 정보 입력, prefix 받아와 sensor와 plugin의 name attribute에 꼭 포함시켜 주기 
      - 안 해줄 경우 plugin 파일에서는 Sensormanager가 model 내부 각 tag들의 name atrribute로 
        영상 frame을 분별하고 publish하도록 만들어져 있기 때문에 topic이 다르더라도 동일한 영상 publish 
      
      plugin 태그 안에 파싱할 Camera parameters 입력, 위와 마찬가지로 topic name은 카메라마다, rgbd영상마다 달라야하므로 prefix 가져와 입력되도록 하기.
</pre>


## Rviz 

$ rosrun rviz rviz

<p align="center">
  <img width="800" height="500" src="https://user-images.githubusercontent.com/80872528/119466531-aa43d300-bd7f-11eb-8c38-dd6412a49259.png">
</p>

### Rostopic

$ rostopic list

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
/realsense2r200/realsense2/color/camera_info
/realsense2r200/realsense2/color/image
/realsense2r200/realsense2/color/image/compressed
/realsense2r200/realsense2/color/image/compressed/parameter_descriptions
/realsense2r200/realsense2/color/image/compressed/parameter_updates
/realsense2r200/realsense2/color/image/compressedDepth
/realsense2r200/realsense2/color/image/compressedDepth/parameter_descriptions
/realsense2r200/realsense2/color/image/compressedDepth/parameter_updates
/realsense2r200/realsense2/color/image/theora
/realsense2r200/realsense2/color/image/theora/parameter_descriptions
/realsense2r200/realsense2/color/image/theora/parameter_updates
/realsense2r200/realsense2/depth/camera_info
/realsense2r200/realsense2/depth/image
/realsense2r200/realsense2/depth/image/compressed
/realsense2r200/realsense2/depth/image/compressed/parameter_descriptions
/realsense2r200/realsense2/depth/image/compressed/parameter_updates
/realsense2r200/realsense2/depth/image/compressedDepth
/realsense2r200/realsense2/depth/image/compressedDepth/parameter_descriptions
/realsense2r200/realsense2/depth/image/compressedDepth/parameter_updates
/realsense2r200/realsense2/depth/image/theora
/realsense2r200/realsense2/depth/image/theora/parameter_descriptions
/realsense2r200/realsense2/depth/image/theora/parameter_updates
/realsense2r200/realsense2/ir1/camera_info
/realsense2r200/realsense2/ir1/image
/realsense2r200/realsense2/ir1/image/compressed
/realsense2r200/realsense2/ir1/image/compressed/parameter_descriptions
/realsense2r200/realsense2/ir1/image/compressed/parameter_updates
/realsense2r200/realsense2/ir1/image/compressedDepth
/realsense2r200/realsense2/ir1/image/compressedDepth/parameter_descriptions
/realsense2r200/realsense2/ir1/image/compressedDepth/parameter_updates
/realsense2r200/realsense2/ir1/image/theora
/realsense2r200/realsense2/ir1/image/theora/parameter_descriptions
/realsense2r200/realsense2/ir1/image/theora/parameter_updates
/realsense2r200/realsense2/ir2/camera_info
/realsense2r200/realsense2/ir2/image
/realsense2r200/realsense2/ir2/image/compressed
/realsense2r200/realsense2/ir2/image/compressed/parameter_descriptions
/realsense2r200/realsense2/ir2/image/compressed/parameter_updates
/realsense2r200/realsense2/ir2/image/compressedDepth
/realsense2r200/realsense2/ir2/image/compressedDepth/parameter_descriptions
/realsense2r200/realsense2/ir2/image/compressedDepth/parameter_updates
/realsense2r200/realsense2/ir2/image/theora
/realsense2r200/realsense2/ir2/image/theora/parameter_descriptions
/realsense2r200/realsense2/ir2/image/theora/parameter_updates
/realsense3r200/realsense3/color/camera_info
/realsense3r200/realsense3/color/image
/realsense3r200/realsense3/color/image/compressed
/realsense3r200/realsense3/color/image/compressed/parameter_descriptions
/realsense3r200/realsense3/color/image/compressed/parameter_updates
/realsense3r200/realsense3/color/image/compressedDepth
/realsense3r200/realsense3/color/image/compressedDepth/parameter_descriptions
/realsense3r200/realsense3/color/image/compressedDepth/parameter_updates
/realsense3r200/realsense3/color/image/theora
/realsense3r200/realsense3/color/image/theora/parameter_descriptions
/realsense3r200/realsense3/color/image/theora/parameter_updates
/realsense3r200/realsense3/depth/camera_info
/realsense3r200/realsense3/depth/image
/realsense3r200/realsense3/depth/image/compressed
/realsense3r200/realsense3/depth/image/compressed/parameter_descriptions
/realsense3r200/realsense3/depth/image/compressed/parameter_updates
/realsense3r200/realsense3/depth/image/compressedDepth
/realsense3r200/realsense3/depth/image/compressedDepth/parameter_descriptions
/realsense3r200/realsense3/depth/image/compressedDepth/parameter_updates
/realsense3r200/realsense3/depth/image/theora
/realsense3r200/realsense3/depth/image/theora/parameter_descriptions
/realsense3r200/realsense3/depth/image/theora/parameter_updates
/realsense3r200/realsense3/ir1/camera_info
/realsense3r200/realsense3/ir1/image
/realsense3r200/realsense3/ir1/image/compressed
/realsense3r200/realsense3/ir1/image/compressed/parameter_descriptions
/realsense3r200/realsense3/ir1/image/compressed/parameter_updates
/realsense3r200/realsense3/ir1/image/compressedDepth
/realsense3r200/realsense3/ir1/image/compressedDepth/parameter_descriptions
/realsense3r200/realsense3/ir1/image/compressedDepth/parameter_updates
/realsense3r200/realsense3/ir1/image/theora
/realsense3r200/realsense3/ir1/image/theora/parameter_descriptions
/realsense3r200/realsense3/ir1/image/theora/parameter_updates
/realsense3r200/realsense3/ir2/camera_info
/realsense3r200/realsense3/ir2/image
/realsense3r200/realsense3/ir2/image/compressed
/realsense3r200/realsense3/ir2/image/compressed/parameter_descriptions
/realsense3r200/realsense3/ir2/image/compressed/parameter_updates
/realsense3r200/realsense3/ir2/image/compressedDepth
/realsense3r200/realsense3/ir2/image/compressedDepth/parameter_descriptions
/realsense3r200/realsense3/ir2/image/compressedDepth/parameter_updates
/realsense3r200/realsense3/ir2/image/theora
/realsense3r200/realsense3/ir2/image/theora/parameter_descriptions
/realsense3r200/realsense3/ir2/image/theora/parameter_updates
/rosout
/rosout_agg
/tf
/tf_static
</pre>

## 참고

https://github.com/IntelRealSense/realsense-ros

https://github.com/SyrianSpock/realsense_gazebo_plugin - origin 

https://github.com/pal-robotics/realsense_gazebo_plugin - upgraded for D435
