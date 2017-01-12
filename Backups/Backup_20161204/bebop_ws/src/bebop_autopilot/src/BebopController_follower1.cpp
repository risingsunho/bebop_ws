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
bool flagin=false;
int cnt = 0;

void velCallback(std_msgs::Float64 vel)
{
	speed=sqrt(direction.x*direction.x+direction.y*direction.y);
	
	if(speed<0.05)
	{
		comm.linear.x=speed+0.1;
	}
	else
	{
		comm.linear.x=speed*0.8;
		comm.linear.y=0;
		comm.linear.z=0;
		//comm.linear.z=direction.z;
	}
	
	vel.data=(vel.data/45);
	comm.angular.z=vel.data*1.3;
	if(flag)
	{
		takeoff_pub.publish(val);
		flag=false;
	}
	/*if(flagin){
		if(cnt > 2)
		{
			 flagin= false;
			 cnt=0;
		 }
		 //ROS_INFO("%d",cnt);
		 cnt++;
	} */
	if(!flag && !flagin)
	{
		move_pub.publish(comm);
	}
	/*if(speed<0.04&& speed!=0)
	{
		//ROS_INFO("In");
		//flattrim_pub.publish(val);
		flagin=true;
		
	}   */
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
	ros::spin();
	return 0;
}

