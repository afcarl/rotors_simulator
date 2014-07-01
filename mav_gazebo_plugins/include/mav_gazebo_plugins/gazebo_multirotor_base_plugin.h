//==============================================================================
// Copyright (c) 2014, Fadri Furrer <ffurrer@gmail.com>
// All rights reserved.
//
// ASL 2.0
//==============================================================================

#include <string>
#include <ros/ros.h>
#include <mav_msgs/MotorSpeed.h>

#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <gazebo/common/Plugin.hh>


namespace gazebo
{
  /// \brief This plugin is used to create rosbag files in within gazebo.
  class GazeboMultirotorBasePlugin : public ModelPlugin
  {
    typedef std::map<const unsigned int, const physics::JointPtr> MotorNumberToJointMap;
    typedef std::pair<const unsigned int, const physics::JointPtr> MotorNumberToJointPair;
    public:
      /// \brief Constructor
      GazeboMultirotorBasePlugin();
      /// \brief Destructor
      virtual ~GazeboMultirotorBasePlugin();

    protected:
      /// \brief Load the plugin.
      /// \param[in] _model Pointer to the model that loaded this plugin.
      /// \param[in] _sdf SDF element that describes the plugin.
      void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf);

      /// \brief Called when the world is updated.
      /// \param[in] _info Update timing information.
      void OnUpdate(const common::UpdateInfo& /*_info*/);

    private:
      /// \brief The connections.
      event::ConnectionPtr update_connection_;

      /// \brief Pointer to the world.
      physics::WorldPtr world_;

      /// \brief Pointer to the model.
      physics::ModelPtr model_;

      /// \brief Pointer to the link.
      physics::LinkPtr link_;

      physics::Link_V child_links_;

      MotorNumberToJointMap motor_joints_;

      std::string namespace_;
      std::string motor_pub_topic_;
      std::string frame_id_;
      std::string link_name_;
      double rotor_velocity_slowdown_sim_;

      ros::Publisher motor_pub_;
      ros::NodeHandle *node_handle_;
  };
}
