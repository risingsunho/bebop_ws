#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int64.h>
#include <math.h>

using namespace std;

ros::Publisher takeoff_pub;
ros::Publisher land_pub;
ros::Publisher flattrim_pub;
ros::Publisher move_pub;

geometry_msgs::Twist comm;
geometry_msgs::Vector3 direction;

std_msgs::Empty val;
double speed=0;
bool flag=true;
int mode=0;


void velCallback(std_msgs::Float64 vel)
{
	if(mode==4)
	{
		takeoff_pub.publish(val);
	}
	else if(mode==5)
	{
		land_pub.publish(val);
	}
	else if(mode==6)
	{
		flattrim_pub.publish(val);
	}
	else
	{
		speed=sqrt(direction.x*direction.x+direction.y*direction.y);
		vel.data=(vel.data/45);
		comm.angular.z=vel.data;
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
		move_pub.publish(comm);
	}	
}
void velCallbackDirection(geometry_msgs::Vector3 vec)
{
	direction=vec;	
}
void cmd_mode(std_msgs::Int64 m) //Set the DesiredGPS value along with mode value
{    	
	mode=m.data;		
}
int main(int argc, char **argv)
{
	ros::init(argc, argv, "BebopController_follower");
	
	ros::NodeHandle nh_;
	ros::Subscriber sub = nh_.subscribe("/error1", 10, velCallback);
	ros::Subscriber sub_directionVector = nh_.subscribe("/dirvector1", 1, velCallbackDirection);
	ros::Subscriber sub_mode = nh_.subscribe("/bebop/cmd_mode", 1, cmd_mode);
	
	move_pub=nh_.advertise<geometry_msgs::Twist>("/bebop1/cmd_vel",1);	
	flattrim_pub = nh_.advertise<std_msgs::Empty>("/bebop1/flattrim", 1);
	takeoff_pub = nh_.advertise<std_msgs::Empty>("/bebop1/takeoff", 1);
	land_pub = nh_.advertise<std_msgs::Empty>("/bebop1/land", 1);
	
	ros::spin();
	return 0;
	
}

