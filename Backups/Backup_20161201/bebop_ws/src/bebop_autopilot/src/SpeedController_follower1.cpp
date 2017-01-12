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
#define ZeropointX 126.865995
#define ZeropointY 37.6005335
#define longtolatscale 0.7939642835
#define lattolongscale 1.2595025
#define costheta  0.95105651629515357211643933337938
#define sintheta 0.30901699437494742410229341718282

#define latscaleFactor 1779.359430
//#define latscaleFactor 295.657863855986


using namespace std;

ros::Publisher land_pub;

ros::Publisher pub_dirv;
sensor_msgs::NavSatFix DesiredGPS;
sensor_msgs::NavSatFix CurrentGPS;

geometry_msgs::Vector3 DesiredPosition;
geometry_msgs::Vector3 CurrentPosition;
geometry_msgs::Vector3 DirectionVector;
std_msgs::Empty val;

sensor_msgs::NavSatFix D;
sensor_msgs::NavSatFix A;
sensor_msgs::NavSatFix C;
sensor_msgs::NavSatFix B;
//sensor_msgs::NavSatFix GPSs;

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
    
	/*Longitude = Longitude*lattolongscale; 
	Longitude = Longitude + ZeropointX;
	Latitude = Latitude + ZeropointY;*/
	////////gps값으로 변환/////
	
	return plot;

}

void velCallback(sensor_msgs::NavSatFix vel) //현재 gps값 수신
{
		CurrentPosition=GPStoRotatedPlot(vel); 
		DesiredPosition=GPStoRotatedPlot(DesiredGPS);   
		DirectionVector.x=(DesiredPosition.x-CurrentPosition.x)*latscaleFactor;
		DirectionVector.y=(DesiredPosition.y-CurrentPosition.y)*latscaleFactor;  
        DirectionVector.z=(DesiredGPS.altitude-vel.altitude);
		
		pub_dirv.publish(DirectionVector);		
  
}
void targetCallback(sensor_msgs::NavSatFix vel) //목표 gps값
{    	
	DesiredGPS=vel;		
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "SpeedController_follower1");
	ros::NodeHandle nh_;	
	
	ros::Subscriber sub = nh_.subscribe("/bebop2/fix", 1, velCallback);
	ros::Subscriber sub_target = nh_.subscribe("/bebop1/fix", 1, targetCallback);
	land_pub = nh_.advertise<std_msgs::Empty>("/bebop2/reset", 1);	
	pub_dirv=nh_.advertise<geometry_msgs::Vector3>("/dirvector2", 1);
	
	ros::spin();
	return 0;	
}


