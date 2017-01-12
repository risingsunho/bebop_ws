#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int64.h>
#include <math.h>


/* #define MAX_SPEED 0.1
#define FULL_TURN_SPEED 0.03
#define F_NORMAL_SPEED 0.07
#define FOLLOWER_BOUND 0.015 */ //일렬

#define MAX_SPEED 0.15
#define FULL_TURN_SPEED 0.03
#define F_NORMAL_SPEED 0.11
#define FOLLOWER_BOUND 0.017 //플로킹

using namespace std;

ros::Publisher takeoff_pub;
//ros::Publisher land_pub;
ros::Publisher flattrim_pub;
ros::Publisher move_pub;
ros::Publisher Bebopmoved_pub;

geometry_msgs::Twist comm;
geometry_msgs::Vector3 direction;

std_msgs::Empty val;

double cdist=0;
double pdist=0;
bool takeoffflag=true;
double yaw=0;

std_msgs::Int64 moved;

void velCallback(std_msgs::Float64 vel)
{
	yaw=vel.data;	  
	cdist=sqrt(direction.x*direction.x+direction.y*direction.y);
	
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
	if(cdist<FOLLOWER_BOUND)
	{
		flattrim_pub.publish(val);
		comm.linear.x=0;//MAX_SPEED;
				comm.linear.y=0;
				comm.linear.z=0;
				comm.angular.z=(yaw/45);
	}
	else
	{
		if(pdist > 0.02)//cdist>pdist) //멀어지는 경우
		{
			if(yaw>=-45 && yaw<=45) //비슷한 방향에서 뒤쳐짐
			{
			//	ROS_INFO("movemove1");
				comm.linear.x=MAX_SPEED;
				comm.linear.y=0;
				comm.linear.z=0;
				comm.angular.z=(yaw/45);	
			}
			else 
			{
			//	ROS_INFO("movemove2");
				comm.linear.x=FULL_TURN_SPEED; //최저 선회속도
				comm.linear.y=0;
				comm.linear.z=0;
				comm.angular.z=(yaw/22.5);	
			}			
		}
		else //가까워 지는 경우
		{
			if(yaw>=-45 && yaw<=45) //비슷한 방향에서 가까워짐
			{
				//ROS_INFO("movemove3");
				comm.linear.x=F_NORMAL_SPEED;
				comm.linear.y=0;
				comm.linear.z=0;
				comm.angular.z=(yaw/45);	
			}
			else 
			{
				//ROS_INFO("movemove4");
				comm.linear.x=FULL_TURN_SPEED; //최저 선회속도
				comm.linear.y=0;
				comm.linear.z=0;
				comm.angular.z=(yaw/22.5);	
			}
		}
	}
	if(pdist!=0)// && moved.data==2)
	{
		move_pub.publish(comm);
		moved.data=3;
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

