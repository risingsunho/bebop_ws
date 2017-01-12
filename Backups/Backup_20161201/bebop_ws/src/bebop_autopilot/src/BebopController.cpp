#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Float64.h>
#include <math.h>

using namespace std;

ros::Publisher takeoff_pub;
ros::Publisher takeoff_pub1;
ros::Publisher takeoff_pub2;
ros::Publisher flattrim_pub;
ros::Publisher move_pub;



geometry_msgs::Twist comm;
geometry_msgs::Vector3 direction;

std_msgs::Empty val;
double speed=0;
bool flag=true;
void velCallback(std_msgs::Float64 vel)
{
	speed=sqrt(direction.x*direction.x+direction.y*direction.y);
	//ROS_INFO("%f",speed);
	if(speed<0.05)
	{
		comm.linear.x=speed+0.1;
	}
	else
	{
		comm.linear.x=speed/2;
		comm.linear.y=0;
		comm.linear.z=0;
		//comm.linear.z=direction.z;
	}
	//ROS_INFO("%f",vel.data);
	vel.data=(vel.data/45);
	//ROS_INFO("%f",speed);
	comm.angular.z=vel.data;
	if(flag)
	{
		takeoff_pub.publish(val);
		flag=false;
	}
	if(!flag)
	{
		move_pub.publish(comm);
	}
	/*if(speed<0.03&& speed!=0)
	{
		flattrim_pub.publish(val);
	} */  
}
void velCallbackDirection(geometry_msgs::Vector3 vec)
{
	direction=vec;	
}
int main(int argc, char **argv)
{
	ros::init(argc, argv, "BebopController");
	
	ros::NodeHandle nh_;
	ros::Subscriber sub = nh_.subscribe("/error", 10, velCallback);
	ros::Subscriber sub_directionVector = nh_.subscribe("/dirvector", 1, velCallbackDirection);
	move_pub=nh_.advertise<geometry_msgs::Twist>("/bebop/cmd_vel",1);	
	takeoff_pub = nh_.advertise<std_msgs::Empty>("/bebop/takeoff", 1); 
	flattrim_pub = nh_.advertise<std_msgs::Empty>("/bebop/flattrim", 1);
	//ros::Rate loop_rate(1);	
	
	ros::spin();
	return 0;
	
}

