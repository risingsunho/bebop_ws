#include <ros/ros.h>
#include "sensor_msgs/NavSatFix.h"
#include <stdio.h>
#include <std_msgs/Empty.h>




using namespace std;
std_msgs::Empty val;
ros::Publisher pub;
sensor_msgs::NavSatFix targetGPS;
ros::Publisher takeoff_pub;
ros::Publisher land_pub;
int main(int argc, char **argv)
{
	ros::init(argc, argv, "Agent");
	ros::NodeHandle nh_;	
	char c;
	pub = nh_.advertise<sensor_msgs::NavSatFix>("/target", 1);
	takeoff_pub = nh_.advertise<std_msgs::Empty>("/bebop/takeoff", 1); 
	land_pub = nh_.advertise<std_msgs::Empty>("/bebop/land", 1);
	ros::Rate loop_rate(10);
	
	while(ros::ok())
	{		
		cin>>c;
		if(c=='b')
		{
			targetGPS.longitude=126.8663735;
			targetGPS.latitude=37.6008091667;
			pub.publish(targetGPS);
		}
		else if(c=='a')
		{
			targetGPS.longitude=126.866548;
			targetGPS.latitude=37.6007645;
			pub.publish(targetGPS);
		}
		else if(c=='c')
		{
			targetGPS.longitude=126.866227;
			targetGPS.latitude=37.6008698333;
			pub.publish(targetGPS);
		}
		else if(c=='d')
		{
			targetGPS.longitude=126.86612667;
			targetGPS.latitude=37.6006375;
			pub.publish(targetGPS);
		}
		else if(c=='t')
		{
			 takeoff_pub.publish(val);
		}
		else if(c=='g')
		{
			land_pub.publish(val);
		}
		else if(c=='e')
		{
			targetGPS.longitude=126.866327;
			targetGPS.latitude=37.600585;
			pub.publish(targetGPS);
		}
		else if(c=='x')
		{
			break;
		}
		
		ros::spinOnce();
		loop_rate.sleep();
	}
	ros::spin();
	return 0;	
}


