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

ros::Publisher flattrim_pub;
ros::Publisher move_pub;
ros::Publisher Bebopmoved_pub;

geometry_msgs::Twist comm;
geometry_msgs::Vector3 direction;

std_msgs::Empty val;
double speed=0;
bool takeoffflag=true;
double yaw=0;

std_msgs::Int64 moved;

void velCallback(std_msgs::Float64 vel)
{
	yaw=vel.data;
	
}
void velCallbackbebopMoved(std_msgs::Int64 vel)
{
	moved.data=vel.data;
}
void velCallbackDirection(geometry_msgs::Vector3 vec)
{
	direction=vec;	
	speed=sqrt(direction.x*direction.x+direction.y*direction.y);
	comm.linear.x=1;//speed;
	comm.linear.y=0;
	comm.linear.z=0;
	yaw=(yaw/45);
	comm.angular.z=yaw;
	if(takeoffflag)
	{
		moved.data=3;
		takeoff_pub.publish(val);
		takeoffflag=false;
	}
	else if(!takeoffflag && moved.data==2)
	{
		ROS_INFO("3");
		move_pub.publish(comm);
		moved.data=3;
		Bebopmoved_pub.publish(moved);
	}
	if(speed<0.03 && speed!=0)
	{
		flattrim_pub.publish(val);		
	}
	
}
int main(int argc, char **argv)
{
	ros::init(argc, argv, "BebopController_follower1");
	
	ros::NodeHandle nh_;
	ros::Subscriber sub = nh_.subscribe("/error2", 1, velCallback);
	ros::Subscriber sub_directionVector = nh_.subscribe("/dirvector2", 1, velCallbackDirection);
	move_pub=nh_.advertise<geometry_msgs::Twist>("/bebop2/cmd_vel",1);	
	takeoff_pub = nh_.advertise<std_msgs::Empty>("/bebop2/takeoff", 1); 
	//land_pub = nh_.advertise<std_msgs::Empty>("/bebop1/land", 1);
	flattrim_pub = nh_.advertise<std_msgs::Empty>("/bebop2/flattrim", 1);
	
	ros::Subscriber sub_bebopMoved = nh_.subscribe("/bebopMoved", 1, velCallbackbebopMoved);
	Bebopmoved_pub = nh_.advertise<std_msgs::Int64>("/bebopMoved", 1); 
	
	ros::spin();
	return 0;
}

