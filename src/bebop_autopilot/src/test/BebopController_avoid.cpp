#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int64.h>
#include <math.h>

#define LEADER_ACC_SPEED 0.13
#define LEADER_DCC_SPEED 0.1
#define FULL_TURN_SPEED 0.01
using namespace std;

ros::Publisher takeoff_pub;
ros::Publisher takeoff_pub1;
ros::Publisher takeoff_pub2;
ros::Publisher flattrim_pub;
ros::Publisher move_pub;
ros::Publisher avoid_end_pub;



geometry_msgs::Twist comm;
geometry_msgs::Vector3 direction;

std_msgs::Empty val;
double speed=0;
bool takeoffflag=true;
bool abcd=true;
std_msgs::Bool avoid;
std_msgs::Bool avoid_topic;

int cnt=0;

double yaw=0;
double cdist=0;
double pdist=0;

std_msgs::Int64 moved;

void velCallback(std_msgs::Float64 vel)
{
	
	yaw=vel.data;	  
	cdist=sqrt(direction.x*direction.x+direction.y*direction.y);
	if(takeoffflag)
	{
		takeoff_pub.publish(val);
		takeoffflag=false;
	}
	if(avoid.data) //피해야할 때
	{
		ROS_INFO("avoid");
		if(cnt==5)
		{
			avoid.data=false;
			cnt=0;
			avoid_topic.data=true;
			avoid_end_pub.publish(avoid_topic);
		}
		else
		{
			comm.linear.x=0.1;
			comm.linear.y=-0.3;
			comm.linear.z=0;//또는 -1
			comm.angular.z=-0.6;//(yaw/45);
			avoid_topic.data=false;
			avoid_end_pub.publish(avoid_topic);
			cnt++;
		}		
	}
	else //평상시
	{
		ROS_INFO("not avoid");
		if(cdist>pdist) //멀어지는 경우
		{
			if(yaw>=-30 && yaw<=30) //비슷한 방향에서 뒤쳐짐
			{
				comm.linear.x=LEADER_ACC_SPEED;
				comm.linear.y=0;
				comm.linear.z=0;
				comm.angular.z=(yaw/45);	
			}
			else 
			{
				comm.linear.x=FULL_TURN_SPEED; //최저 선회속도
				comm.linear.y=0;
				comm.linear.z=0;
				comm.angular.z=(yaw/45);	
			}			
		}
		else //가까워 지는 경우
		{
			if(yaw>=-30 && yaw<=30) //비슷한 방향에서 가까워짐
			{
				comm.linear.x=LEADER_DCC_SPEED;
				comm.linear.y=0;
				comm.linear.z=0;
				comm.angular.z=(yaw/45);	
			}
			else 
			{
				comm.linear.x=FULL_TURN_SPEED; //최저 선회속도
				comm.linear.y=0;
				comm.linear.z=0;
				comm.angular.z=(yaw/45);	
			}
		}
	}
	
	if(pdist!=0 && !takeoffflag)
	{		
		move_pub.publish(comm);
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
void avoidCallback(std_msgs::Bool flag)
{
	avoid.data=flag.data;
}
int main(int argc, char **argv)
{
	ros::init(argc, argv, "BebopController_avoid");
	
	ros::NodeHandle nh_;
	ros::Subscriber sub = nh_.subscribe("/error", 1, velCallback);
	ros::Subscriber sub_directionVector = nh_.subscribe("/dirvector", 1, velCallbackDirection);
	
	ros::Subscriber sub_avoid = nh_.subscribe("/obstacle_recognizer/avoidance_command", 1, avoidCallback);
	avoid_end_pub=nh_.advertise<std_msgs::Bool>("/bebop_autopilot/recognize_command",1);
	
	move_pub=nh_.advertise<geometry_msgs::Twist>("/bebop/cmd_vel",1);	
	takeoff_pub = nh_.advertise<std_msgs::Empty>("/bebop/takeoff", 1); 
	flattrim_pub = nh_.advertise<std_msgs::Empty>("/bebop/flattrim", 1);
	
	avoid.data=false;
	//ros::Rate loop_rate(1);		
	ros::spin();
	return 0;
	
}

