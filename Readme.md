## Gazebo simulation with multicamera (publish rgb, depth image for reconstruction) (ongoing)

Realsense D435 model 이용 

D435
L515
azure kinect
예정

### Plugin

realsense_gazebo_plugin-master > build 에서 cmake../ , make 로 빌드 => build > devel > lib에 librealsense_gazebo_plugin.so 플러그인 파일 생성

librealsense_gazebo_plugin.so => src > gazebo_ros_realsense.cpp, RealSensePlugin.cpp로 생성

 /usr/lib/x86_64-linux-gnu/cmake/gazebo/plugins로 옮기기

### Model

/home/jskimlab/.gazebo/models/realsense_camera에 위치

model sdf의 plugin 태그에서 위의 플러그인 불러주기

### World

world_env.world : world file 

world file에서 카메라 모델 직접 삽입(Insert - realsense camera)

### 실행

단순 실행시 - $project1/world    gazebo --verbose -s libgazebo_ros_api_plugin.so world_env.world (ros init 위해)

재실행시 - killall gzserver, sudo killall gzserver

새로운 모델 추가시 - $project1/world     sudo gazebo --verbose world_env.world 

### Rviz 

$ rosrun rviz rviz

### Rostopic

$ rostopic list


### 문제

카메라 여러 대 추가 불가능 - 토픽 겹침(현재 1대 publish는 됨)

해결 어떻게 할지 - 1. roslaunch로 multiple camera 진행하는 다른 예제 찾아보기, 2. 설마 플러그인 다 개별로 만들어야 되나?

libgazebo_ros_api_plugin.so(ros구동위해) 안 부르고 ros node initialize 어떻게 할지

model sdf plugin 내부 태그 수정할지?


### 기타 사항

plugin 및 기타 path : /usr/lib/x86_64-linux-gnu/gazebo-9/plugins

### 참고

https://github.com/SyrianSpock/realsense_gazebo_plugin - origin 

https://github.com/pal-robotics/realsense_gazebo_plugin - upgraded for D435

openni 참고하기


