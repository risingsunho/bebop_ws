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
bool takeoffflag=true;
bool flagin=true;
int cnt = 0;
double yaw=0;
void velCallback(std_msgs::Float64 vel)
{
	yaw=vel.data;
}
void velCallbackDirection(geometry_msgs::Vector3 vec)
{
	direction=vec;	
	speed=sqrt(direction.x*direction.x+direction.y*direction.y);
	if(direction.x !=0 && direction.y!=0 && speed<10)
	{
		
		//ROS_INFO("%f",speed);
		
			comm.linear.x=0.07;//speed;
			comm.linear.y=0;
			comm.linear.z=0;
			//comm.linear.z=direction.z;
	
		yaw=(yaw/45);
		comm.angular.z=yaw;
		if(takeoffflag)
		{
			takeoff_pub.publish(val);
			takeoffflag=false;
		}
		else if(!takeoffflag && !flagin)
		{
			ROS_INFO("1");
			move_pub.publish(comm);
		}
		if(flagin){
		if(cnt > 6)
		{
			 flagin= false;
			 cnt=0;
		 }
			//ROS_INFO("%d",cnt);
			cnt++;
		}
		if(speed<0.02 && speed!=0)
		{
			flattrim_pub.publish(val);
			//flagin=true;		
		}
		else
		{
			//flagin=false;
		}
	}
}
int main(int argc, char **argv)
{
	ros::init(argc, argv, "BebopController");
	
	ros::NodeHandle nh_;
	ros::Subscriber sub = nh_.subscribe("/error", 1, velCallback);
	ros::Subscriber sub_directionVector = nh_.subscribe("/dirvector", 1, velCallbackDirection);
	move_pub=nh_.advertise<geometry_msgs::Twist>("/bebop/cmd_vel",1);	
	takeoff_pub = nh_.advertise<std_msgs::Empty>("/bebop/takeoff", 1); 
	flattrim_pub = nh_.advertise<std_msgs::Empty>("/bebop/flattrim", 1);
	direction.x=0;
	direction.y=0;
	//ros::Rate loop_rate(1);	
	
	ros::spin();
	return 0;
	
}

