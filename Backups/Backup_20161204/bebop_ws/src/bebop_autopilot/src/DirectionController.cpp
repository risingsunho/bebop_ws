#include <ros/ros.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Vector3.h>
#include <math.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_datatypes.h>
#include "std_msgs/Float64.h"


#define PI 3.14159265358979323846264338
using namespace std;

ros::Publisher pub_setpoint;


geometry_msgs::Quaternion quat;
geometry_msgs::Vector3 direction;	
double directionVectorYAW;
std_msgs::Float64 stateYaw;
std_msgs::Float64 setpointYaw;
geometry_msgs::Vector3 ToEulerianAngle(geometry_msgs::Quaternion quat)
{
	tf::Quaternion q(quat.x, quat.y, quat.z, quat.w);
	tf::Matrix3x3 m(q);
    double roll, pitch, yaw;
    m.getRPY(roll, pitch, yaw);
    geometry_msgs::Vector3 ans;
    ans.x=roll;
    ans.y=pitch;
    ans.z=yaw;   

    return ans;
}
double VectorToYaw(geometry_msgs::Vector3 vec)
{
	double theta;
	geometry_msgs::Vector3 north;
	north.x=0;
	north.y=1;
	north.z=0;
	double vel=(vec.x*north.x+vec.y*north.y)/(sqrt(north.x*north.x+north.y*north.y)*sqrt(vec.x*vec.x+vec.y*vec.y));
	vel=acos(vel);
	vel=vel*(180/PI);
	if(vec.x<0)
	{
		return -vel;
	}
	else
	{
		return vel;
	}
	
}


void velCallback(const nav_msgs::Odometry::ConstPtr& vel)
{
	double theta;
	quat.x=vel->pose.pose.orientation.x;
    quat.y=vel->pose.pose.orientation.y;
    quat.z=vel->pose.pose.orientation.z;
    quat.w=vel->pose.pose.orientation.w;
    
    direction=ToEulerianAngle(quat);
    direction.z=-(direction.z*(180/PI));
    
    
	//direction.x=(direction.x*(180/PI));
	//direction.y=(direction.y*(180/PI));
	
    
    stateYaw.data=direction.z;
    setpointYaw.data=directionVectorYAW;
   	
   	///////////방향,크기결정 : 절대값 차이 구하고 방향 결정해주기////////
   	   	
   	theta=stateYaw.data-setpointYaw.data;
   	//ROS_INFO("State_Yaw : %f",stateYaw.data);
    //ROS_INFO("Setpoint_Yaw : %f",setpointYaw.data);

   	if(theta>=180)
   	{		
		setpointYaw.data=abs(stateYaw.data)-abs(setpointYaw.data);		
		if(setpointYaw.data>=180) // 절대값의 차이가 180보다 클때는 그대로
		{
			
			pub_setpoint.publish(setpointYaw);
		}
		else //절대값의 차이가 작을때는 절대값의 차이대로
		{
			//ROS_INFO("Here!!!!!!");
			setpointYaw.data=theta;
			pub_setpoint.publish(setpointYaw);
		}
		
	}
	else
	{
		setpointYaw.data=stateYaw.data-setpointYaw.data;		
		pub_setpoint.publish(setpointYaw);
	}
	
    
}
void velCallbackDirection(geometry_msgs::Vector3 vec)
{
	directionVectorYAW=VectorToYaw(vec);
	//ROS_INFO("Dirvector's yaw : %f",directionVectorYAW);
}
int main(int argc, char **argv)
{
	
	ros::init(argc, argv, "DirectionController");    
    ros::NodeHandle nh_;
    
    ros::Subscriber sub = nh_.subscribe("/bebop/odom", 1, velCallback);
    ros::Subscriber sub_direction = nh_.subscribe("/dirvector", 1, velCallbackDirection);
    pub_setpoint=nh_.advertise<std_msgs::Float64>("/error", 1);
    
    
    
    ros::spin();
	
	return 0;	
}



