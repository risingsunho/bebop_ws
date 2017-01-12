#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include "sensor_msgs/NavSatFix.h"
#include <math.h>
#include <std_msgs/Empty.h>

#define PI 3.14159265358979323846
#define THETA 19.3373375
#define ZeropointX 126.865909
#define ZeropointY 37.600243
#define longtolatscale 0.7939642835
#define lattolongscale 1.2595025
#define costheta  0.95105651629515357211643933337938
#define sintheta 0.30901699437494742410229341718282

#define latscaleFactor 1779.359430
//#define latscaleFactor 295.657863855986


using namespace std;

ros::Publisher pub_dirv;
sensor_msgs::NavSatFix DesiredGPS;
sensor_msgs::NavSatFix CurrentGPS;

geometry_msgs::Vector3 DesiredPosition;
geometry_msgs::Vector3 CurrentPosition;
geometry_msgs::Vector3 DirectionVector;
std_msgs::Empty val;

geometry_msgs::Vector3 GPStoRotatedPlot(sensor_msgs::NavSatFix GPSvel) //GPS->좌표계 변환
{
	double X = 0;
	double Y = 0;
	double Longitude; 
	double Latitude; 
    geometry_msgs::Vector3 plot;

	X = (GPSvel.longitude - ZeropointX)*longtolatscale; 
	Y = (GPSvel.latitude - ZeropointY);  //-> 위도,경도 1:1로 x,y축에 대입

	//////////////////////X,Y값에 대해 좌표계 스케일링해야함


	plot.x = (X*costheta - Y*sintheta);
	plot.y = (X*sintheta + Y*costheta); //회전
    
	Longitude = plot.x*lattolongscale; 
	Longitude = plot.x + ZeropointX;
	Latitude = plot.y + ZeropointY;
	////////gps값으로 변환/////
	ROS_INFO("Longitude : %f",Longitude);
	ROS_INFO("Latitude : %f",Latitude);
	
	return plot;

}


int main(int argc, char **argv)
{
	ros::init(argc, argv, "test");
	
	DesiredGPS.longitude=126.865928;
	DesiredGPS.latitude=37.6004005;	
	DesiredPosition=GPStoRotatedPlot(DesiredGPS); 
	ROS_INFO("plot X : %f",DesiredPosition.x*1779.359430);
	ROS_INFO("plot Y : %f",DesiredPosition.y*1779.359430);
	ros::spin();
	return 0;	
}


