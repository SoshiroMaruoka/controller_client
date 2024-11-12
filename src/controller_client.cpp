#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Int32MultiArray.h>

#include <std_msgs/UInt8MultiArray.h>

geometry_msgs::Twist cmd_vel;
geometry_msgs::Twist manipulator_vel;

std_msgs::Bool emg_switch;
std_msgs::Bool manipulator_valid;
std_msgs::Bool uvg_catch;
std_msgs::Bool start_routine;

std_msgs::Int32 mode_switch;
std_msgs::Int32 button;

std_msgs::Int32MultiArray all_buttons;

//std_msgs::UInt8MultiArray fcontact;

void cmd_vel_callback(const sensor_msgs::Joy& joy_msg)
{
  cmd_vel.linear.x =joy_msg.axes[4];
  cmd_vel.angular.z =joy_msg.axes[3];
} 

void manipulator_vel_callback(const sensor_msgs::Joy& joy_msg)
{
  manipulator_vel.linear.x = joy_msg.axes[1];
  manipulator_vel.linear.y = joy_msg.axes[0]; 
  manipulator_vel.linear.z = (joy_msg.axes[2]-1)/2 + (-joy_msg.axes[5]+1)/2;
}

void share_button_callback(const sensor_msgs::Joy& joy_msg)
{
  if(joy_msg.buttons.size()>0)
  {
    button.data = joy_msg.buttons[8];
  }
}

void emg_callback(const sensor_msgs::Joy& joy_msg)
{
  if(emg_switch.data == true)
  {
    if(joy_msg.buttons[3] == true)
    {
      emg_switch.data = false;
    }
  }
  else if(emg_switch.data == false)
  {
    if(joy_msg.buttons[1] == true)
    {
      emg_switch.data = true;
    }
  }
}

void manipulator_valid_callback(const sensor_msgs::Joy& joy_msg)
{
  manipulator_valid.data = joy_msg.buttons[4];
}

void catch_callback(const sensor_msgs::Joy& joy_msg)
{
  if(uvg_catch.data == true)
  {
    if(joy_msg.buttons[0] == true)
    {
      uvg_catch.data = false;
    }
  }
  else if(uvg_catch.data == false)
  {
    if(joy_msg.buttons[2] == true)
    {
      uvg_catch.data = true;
    }
  }
}

void routine_callback(const sensor_msgs::Joy& joy_msg)
{
  start_routine.data = joy_msg.buttons[11];
}

void mode_callback(const sensor_msgs::Joy& joy_msg)
{
  mode_switch.data = joy_msg.buttons[5] ? 1 : 0;
}

void all_buttons_callback(const sensor_msgs::Joy& joy_msg)
{
  if(joy_msg.buttons.size()>0)
  {
    all_buttons.data = joy_msg.buttons;
  }
}

/*void fcontact_callback(const controllertwist::ContactsStamped& contact_msg)
{
  //fcontact.data = contact_msg.contacts;
  q1.push(contact_msg);
 if(q1.size() > 40){
   fcontact.data =q1.front().contacts;
    q1.pop();
 }

}*/



int main(int argc, char** argv)
{
  ros::init(argc, argv, "controller_client");
  ros::NodeHandle nh;

  ros::Publisher cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/controller_client/cmd_vel", 200);
  ros::Publisher manipulator_vel_pub = nh.advertise<geometry_msgs::Twist>("/controller_client/manipulator_vel", 200);

  ros::Publisher emg_pub  = nh.advertise<std_msgs::Bool>("/controller_client/emg_switch",10);
  ros::Publisher manipulator_valid_pub  = nh.advertise<std_msgs::Bool>("/controller_client/manipulator_valid",10);
  ros::Publisher uvg_catch_pub  = nh.advertise<std_msgs::Bool>("/controller_client/uvg_catch",10);
  ros::Publisher start_routine_pub  = nh.advertise<std_msgs::Bool>("/controller_client/start_routine",10);

  ros::Publisher share_button_pub = nh.advertise<std_msgs::Int32>("/controller_client/share_button", 200);
  ros::Publisher mode_pub = nh.advertise<std_msgs::Int32>("/controller_client/mode_switch", 200);

  ros::Publisher all_buttons_pub = nh.advertise<std_msgs::Int32MultiArray>("/controller_client/all_buttons", 200);
  //ros::Publisher fcontact_pub = nh.advertise<std_msgs::UInt8MultiArray>("fcontact", 100);

  ros::Subscriber cmd_vel_sub = nh.subscribe("joy", 10, cmd_vel_callback);
  ros::Subscriber manipulator_vel_sub = nh.subscribe("joy", 10, manipulator_vel_callback);

  ros::Subscriber emg_sub = nh.subscribe("joy", 10, emg_callback);
  ros::Subscriber manipulator_valid_sub = nh.subscribe("joy", 10, manipulator_valid_callback);
  ros::Subscriber catch_sub = nh.subscribe("joy", 10, catch_callback);
  ros::Subscriber start_routine_sub = nh.subscribe("joy", 10, routine_callback);

  ros::Subscriber share_button_sub = nh.subscribe("joy", 10, share_button_callback);
  ros::Subscriber mode_sub = nh.subscribe("joy", 10, mode_callback);

  ros::Subscriber all_buttons_sub = nh.subscribe("joy", 10, all_buttons_callback);
  //ros::Subscriber fcontact_sub = nh.subscribe("foot_contacts", 10, fcontact_callback);

  ros::Rate loop_rate(10);

  while (ros::ok())
  {
    cmd_vel_pub.publish(cmd_vel);
    manipulator_vel_pub.publish(manipulator_vel);

    emg_pub.publish(emg_switch);
    manipulator_valid_pub.publish(manipulator_valid);
    uvg_catch_pub.publish(uvg_catch);
    start_routine_pub.publish(start_routine);

    share_button_pub.publish(button);
    mode_pub.publish(mode_switch);

    all_buttons_pub.publish(all_buttons);
    //fcontact_pub.publish(fcontact);    
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
