#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Float64.h>
#include <math.h>

using namespace std;

ros::Publisher takeoff_pub;
//ros::Publisher land_pub;
ros::Publisher flattrim_pub;
ros::Publisher move_pub;

geometry_msgs::Twist comm;
geometry_msgs::Vector3 direction;

std_msgs::Empty val;
double speed=0;
bool flag=true;
void velCallback(std_msgs::Float64 vel)
{	
	vel.data=(vel.data/45);
	comm.angular.z=vel.data;   
}
void velCallbackDirection(geometry_msgs::Vector3 vec)
{
	direction=vec;	
}
int main(int argc, char **argv)
{
	ros::init(argc, argv, "BebopController_follower1");
	
	ros::NodeHandle nh_;
	ros::Subscriber sub = nh_.subscribe("/error2", 10, velCallback);
	ros::Subscriber sub_directionVector = nh_.subscribe("/dirvector2", 1, velCallbackDirection);
	move_pub=nh_.advertise<geometry_msgs::Twist>("/bebop2/cmd_vel",1);	
	takeoff_pub = nh_.advertise<std_msgs::Empty>("/bebop2/takeoff", 1); 
	//land_pub = nh_.advertise<std_msgs::Empty>("/bebop1/land", 1);
	flattrim_pub = nh_.advertise<std_msgs::Empty>("/bebop2/flattrim", 1);
	ros::Rate loop_rate(5);	
	
	while(ros::ok())
	{
		speed=sqrt(direction.x*direction.x+direction.y*direction.y);
		if(speed<0.5)
		{
			comm.linear.x=speed+0.3;
		}
		else
		{
			comm.linear.x=speed;
			comm.linear.y=0;
			comm.linear.z=0;
			//comm.linear.z=direction.z;
		}
		if(flag)
		{
			takeoff_pub.publish(val);
			flag=false;
		}
		if(!flag)
		{
			move_pub.publish(comm);
			ROS_INFO("ddd");
		}
		if(speed<0.03&& speed!=0)
		{
			flattrim_pub.publish(val);
		}
		ros::spinOnce();
		loop_rate.sleep();			
	}
	
	return 0;	
}

