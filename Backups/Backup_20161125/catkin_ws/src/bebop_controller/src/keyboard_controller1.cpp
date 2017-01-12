
#include <ros/ros.h>
//#include <turtlesim/Velocity.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <signal.h>
#include <termios.h>
#include <stdio.h>
 
#define KEYCODE_R_arrow 0x43 
#define KEYCODE_L_arrow 0x44
#define KEYCODE_U_arrow 0x41
#define KEYCODE_D_arrow 0x42
#define KEYCODE_Q 0x71

#define KEYCODE_SPACE 0x20
#define KEYCODE_W  0x77
#define KEYCODE_S  0x73
#define KEYCODE_A  0x61
#define KEYCODE_D  0x64
#define KEYCODE_T  0x74
#define KEYCODE_G  0x67

class BebopController
{
public:
  BebopController();
  void keyLoop();

private: 
  ros::NodeHandle nh_;
  double linear_, angular_, l_scale_, a_scale_;
  ros::Publisher vel_pub_;  
  ros::Publisher takeoff_pub;
  ros::Publisher land_pub;
  ros::Publisher move_pub;
};

BebopController::BebopController():
  linear_(0),
  angular_(0),
  l_scale_(2.0),
  a_scale_(2.0)
{
  nh_.param("scale_angular", a_scale_, a_scale_);
  nh_.param("scale_linear", l_scale_, l_scale_);
 
  //vel_pub_ = nh_.advertise<turtlesim::Velocity>("turtle1/command_velocity", 1);
  takeoff_pub = nh_.advertise<std_msgs::Empty>("/bebop1/takeoff", 1);
  land_pub = nh_.advertise<std_msgs::Empty>("/bebop1/land", 1);
  move_pub=nh_.advertise<geometry_msgs::Twist>("/bebop1/cmd_vel",1);
}
 
int kfd = 0;
struct termios cooked, raw;

void quit(int sig)
{
  tcsetattr(kfd, TCSANOW, &cooked);
  ros::shutdown();
  exit(0);
}

 
int main(int argc, char** argv)
{
  ros::init(argc, argv, "keyboard_controller1");
  BebopController contorller;

  signal(SIGINT,quit);

  contorller.keyLoop();
  
  return(0);
}

 
void BebopController::keyLoop()
{
  char c;
  bool dirty=false;

  // get the console in raw mode                                                              
  tcgetattr(kfd, &cooked);
  memcpy(&raw, &cooked, sizeof(struct termios));
  raw.c_lflag &=~ (ICANON | ECHO);
  // Setting a new line, then end of file                         
  raw.c_cc[VEOL] = 1;
  raw.c_cc[VEOF] = 2;
  tcsetattr(kfd, TCSANOW, &raw);

  puts("Reading from keyboard");
  puts("---------------------------");
  puts("Use arrow keys to move the turtle.");


  for(;;)
  {
    // get the next event from the keyboard  
    if(read(kfd, &c, 1) < 0)
    {
      perror("read():");
      exit(-1);
    }
 
    linear_=angular_=0;
//    printf("value: 0x%02X\n", c); //키코드확인
    geometry_msgs::Twist vel;
    std_msgs::Empty val;
    bool flg=true;
    switch(c)
    {
      
      case KEYCODE_L_arrow:
        ROS_DEBUG("LEFT");
        linear_ = 1.0;
        dirty = true;
        vel.linear.y = l_scale_*linear_;
        
        break;
      case KEYCODE_R_arrow:
        ROS_DEBUG("RIGHT");
        linear_= -1.0;
        dirty = true;
        vel.linear.y = l_scale_*linear_;
        break;
      case KEYCODE_U_arrow:
        ROS_DEBUG("forward");
        linear_ = 1.0;
        dirty = true;
        flg=false;
        vel.linear.x = l_scale_*linear_;
        break;
      case KEYCODE_D_arrow:
        ROS_DEBUG("backward");
        linear_ = -1.0;
        dirty = true;
        vel.linear.x = l_scale_*linear_;
        break;
      case KEYCODE_W:
        ROS_DEBUG("up");
        linear_ = 1.0;
        dirty = true;
        vel.linear.z = l_scale_*linear_;
        break;
      case KEYCODE_S:
        ROS_DEBUG("down");
        linear_ = -1.0;
        dirty = true;
        vel.linear.z = l_scale_*linear_;
        break;
      case KEYCODE_D:
        ROS_DEBUG("clockwise");
        angular_ = 1.0;
        dirty = true;
        vel.angular.z = l_scale_*angular_;
        break;
      case KEYCODE_A:
        ROS_DEBUG("countclockwise");
        angular_ = -1.0;
        dirty = true;
        vel.angular.z = l_scale_*angular_;
        break;
      case KEYCODE_T:
        ROS_DEBUG("takeoff");
        takeoff_pub.publish(val);  
        break;
      case KEYCODE_G:
        ROS_DEBUG("land");

        land_pub.publish(val);  
        break;
        
    }
   

    
   // vel.angular.x = a_scale_*angular_;
   // vel.linear.x = l_scale_*linear_;
    if(dirty ==true)
    {
      move_pub.publish(vel);    
      dirty=false;
    }
  }
 
 
  return;
}
