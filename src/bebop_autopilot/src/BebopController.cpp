#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int64.h>
#include <math.h>

#define LEADER_ACC_SPEED 0.1
#define LEADER_DCC_SPEED 0.05
#define FULL_TURN_SPEED 0.01
using namespace std;

ros::Publisher takeoff_pub;
ros::Publisher takeoff_pub1;
ros::Publisher takeoff_pub2;
ros::Publisher flattrim_pub;
ros::Publisher move_pub;
ros::Publisher Bebopmoved_pub;



geometry_msgs::Twist comm;
geometry_msgs::Vector3 direction;

std_msgs::Empty val;
double speed=0;
bool takeoffflag=true;

double yaw=0;
double cdist=0;
double pdist=0;

std_msgs::Int64 moved;

void velCallback(std_msgs::Float64 vel)
{
	yaw=vel.data;	  
	cdist=sqrt(direction.x*direction.x+direction.y*direction.y);
	ROS_INFO("%f",cdist);
	ROS_INFO("%f",pdist);
	/*if(takeoffflag)
	{
		moved.data=3;
		takeoff_pub.publish(val);
		takeoffflag=false;
	}
	else if(!takeoffflag && moved.data==1)
	{
		ROS_INFO("2");
		move_pub.publish(comm);
		moved.data=2;
		Bebopmoved_pub.publish(moved);
	}*/
	if(cdist>pdist) //멀어지는 경우
	{
		if(yaw>=-30 && yaw<=30) //비슷한 방향에서 뒤쳐짐
		{
			comm.linear.x=direction.y;//LEADER_ACC_SPEED;
			comm.linear.y=0;
			comm.linear.z=direction.x;
			comm.angular.z=(yaw/45);	
		}
		else 
		{
			comm.linear.x=direction.y;//FULL_TURN_SPEED; //최저 선회속도
			comm.linear.y=0;
			comm.linear.z=direction.x;
			comm.angular.z=(yaw/45);	
		}			
	}
	else //가까워 지는 경우
	{
		if(yaw>=-30 && yaw<=30) //비슷한 방향에서 가까워짐
		{
			comm.linear.x=direction.y;//LEADER_DCC_SPEED;
			comm.linear.y=direction.x;
			comm.linear.z=0;
			comm.angular.z=(yaw/45);	
		}
		else 
		{
			comm.linear.x=direction.y;//FULL_TURN_SPEED; //최저 선회속도
			comm.linear.y=direction.x;
			comm.linear.z=0;
			comm.angular.z=(yaw/45);	
		}
	}
	if(pdist!=0)// && moved.data==3)
	{
		//ROS_INFO("1");
		move_pub.publish(comm);
		moved.data=1;
		Bebopmoved_pub.publish(moved);
	}
	pdist=cdist;
	
}
void velCallbackbebopMoved(std_msgs::Int64 vel)
{
	moved.data=vel.data;
}
void velCallbackDirection(geometry_msgs::Vector3 vec)
{
	direction=vec;	
}
int main(int argc, char **argv)
{
	ros::init(argc, argv, "BebopController");
	
	ros::NodeHandle nh_;
	ros::Subscriber sub = nh_.subscribe("/error", 1, velCallback);
	ros::Subscriber sub_directionVector = nh_.subscribe("/dirvector", 1, velCallbackDirection);
	
	ros::Subscriber sub_bebopMoved = nh_.subscribe("/bebopMoved", 1, velCallbackbebopMoved);
	
	move_pub=nh_.advertise<geometry_msgs::Twist>("/bebop/cmd_vel",1);	
	takeoff_pub = nh_.advertise<std_msgs::Empty>("/bebop/takeoff", 1); 
	flattrim_pub = nh_.advertise<std_msgs::Empty>("/bebop/flattrim", 1);
	moved.data=3;
	Bebopmoved_pub = nh_.advertise<std_msgs::Int64>("/bebopMoved", 1); 
	//ros::Rate loop_rate(1);	
	
	ros::spin();
	return 0;
	
}

