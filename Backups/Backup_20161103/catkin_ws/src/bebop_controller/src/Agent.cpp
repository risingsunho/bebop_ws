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
			targetGPS.longitude=126.865838833;
			targetGPS.latitude=37.6002191667;
			
			pub.publish(targetGPS);
		}
		else if(c=='a')
		{
			targetGPS.longitude=126.86593;
			targetGPS.latitude=37.6003871667;
			
			pub.publish(targetGPS);
		}
		else if(c=='c')
		{
			targetGPS.longitude=126.8661175;
			targetGPS.latitude=37.6001461667;
			
			pub.publish(targetGPS);
		}
		else if(c=='d')
		{
			targetGPS.longitude=126.8661815;
			targetGPS.latitude=37.6003271667;
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
			targetGPS.longitude=126.8664005;
			targetGPS.latitude=37.600671;
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


