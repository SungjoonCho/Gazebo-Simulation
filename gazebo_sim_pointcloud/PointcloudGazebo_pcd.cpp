#include <ignition/math/Pose3.hh>
#include <functional>
#include "gazebo/common/Plugin.hh"
#include "gazebo/msgs/msgs.hh"
#include "gazebo/physics/World.hh"
#include "gazebo/transport/Node.hh"
#include "gazebo/gazebo.hh"
#include <ros/ros.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <iostream>

template<typename ... Args>
std::string format_string(const std::string& format, Args ... args)
{
  size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1;
  std::unique_ptr<char[]> buffer(new char[size]);
  snprintf(buffer.get(), size, format.c_str(), args ...);
  return std::string(buffer.get(), buffer.get() + size - 1);
}

namespace gazebo
{
  class PointcloudGazebo : public WorldPlugin  
  {

    private: transport::NodePtr node;
    private: transport::PublisherPtr factoryPub;
    private: ros::Subscriber sub;
    private: event::ConnectionPtr updateConnection;
    private: physics::WorldPtr my_world;
      
    public: void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf) override
    {

      pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_dst (new pcl::PointCloud<pcl::PointXYZ>);

      my_world = _world;
      
      // Create a new transport node
      this->node = transport::NodePtr(new transport::Node());

      // Initialize the node with the world name
      this->node->Init(my_world->Name());

      if (!ros::isInitialized())
      {
        int argc = 0;
        char **argv = NULL;
        ros::init(argc, argv, "gazebo_client",
            ros::init_options::NoSigintHandler);
      }

      std::cout << "Ros init complete\n";
      
      //* load the file
        if (pcl::io::loadPCDFile<pcl::PointXYZ> ("room_scan1.pcd", *cloud_dst) == -1) 
        {
          PCL_ERROR ("Couldn't read file test_pcd.pcd \n");
          return ;
        }


        std::cout << "Loaded "
                  << cloud_dst->width * cloud_dst->height
                  << " data points from test_pcd.pcd with the following fields: "
                  << std::endl;


        int cnt = 0; // counting point 
        
        for (const auto& point: *cloud_dst){

            sdf::SDF sphereSDF;
            std::string text;

            // made collision of models 0, if it is not 0 and if two sphere poses so similar, they will move their pose to avoid each other.
            text = format_string(
            "<sdf version ='1.6'>\
                <model name ='sphere %d'>\
                    <pose>%.4f %.4f %.4f 0 0 0</pose>\
                    <link name ='link'>\
                        <pose>0 0 0 0 0 0</pose>\
                        <collision name ='collision'>\
                            <geometry>\
                                <sphere><radius>0</radius></sphere>\
                            </geometry>\
                        </collision>\
                        <visual name ='visual'>\
                            <geometry>\
                                <sphere><radius>0.1</radius></sphere>\
                            </geometry>\
                        </visual>\
                        <gravity>0</gravity>\
                    </link>\
                </model>\
            </sdf>", cnt,point.x/5,point.y/5,point.z/5);  // to make point density higher, modify more than 5
            sphereSDF.SetFromString(text);

            // insert each point in gazebo
            my_world->InsertModelSDF(sphereSDF); 

            cnt++;
            
            // let you know progress
            if(cnt%100 == 0){
                std::cout << cnt << "completed\n"; 
            }
        }

        std::cout << "insert complete\n";
      
    }
        
  };
  GZ_REGISTER_WORLD_PLUGIN(PointcloudGazebo);
}  // namespace gazebo
