#include <ros/ros.h>
#include "sensor_msgs/NavSatFix.h"
#include <queue>

using namespace std;

queue<sensor_msgs::NavSatFix> Queue;
sensor_msgs::NavSatFix CurrentGPS;

sensor_msgs::NavSatFix AverageGPS(queue<sensor_msgs::NavSatFix> q)
{
	float longavr;
	float latavr;
	sensor_msgs::NavSatFix gps;
	for(int i=0;i<q.size();i++)
	{
		longavr=longavr+q.front().longitude;
	}
	for(int i=0;i<q.size();i++)
	{
		latavr=latavr+q.front().latitude;
	}
	gps.longitude=longavr/q.size();
	gps.latitude=latavr/q.size();
	return gps;
}
void velCallback(sensor_msgs::NavSatFix vel) //현재 gps값 수신
{		
	if(Queue.size()!=3)
	{
		Queue.push(vel);
	}
	else
	{
		CurrentGPS=AverageGPS(Queue);
		ROS_INFO("Longitude : %f", CurrentGPS.longitude);  		
		ROS_INFO("Latitude : %f", CurrentGPS.latitude);  		
		Queue.pop();			
	}
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "test");
	ros::NodeHandle nh_;
	ros::Subscriber sub_target = nh_.subscribe("/bebop/fix", 1, velCallback);
	ros::spin();
	return 0;	
}



