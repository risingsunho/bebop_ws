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
	geometry_msgs::Vector3 boundary;
	boundary=GPStoRotatedPlot(vel);
	//ROS_INFO("%f",DesiredGPS.longitude);
	//ROS_INFO("%f",DesiredGPS.latitude);
	if(vel.altitude>25)
	{
		land_pub.publish(val); //비상착륙
	}
	if((boundary.x>0 && boundary.x<=1.5) &&(boundary.y>0 && boundary.y<=1))//////////GF 안에 있다면
	{
		CurrentPosition=GPStoRotatedPlot(vel); 
		DesiredPosition=GPStoRotatedPlot(DesiredGPS);   
		DirectionVector.x=(DesiredPosition.x-CurrentPosition.x)*latscaleFactor;
		DirectionVector.y=(DesiredPosition.y-CurrentPosition.y)*latscaleFactor;  
        DirectionVector.z=(DesiredGPS.altitude-vel.altitude);
		// ROS_INFO("dirvector.x : %f", DirectionVector.x);
		//ROS_INFO("dirvector.y : %f", DirectionVector.y);
		
		pub_dirv.publish(DirectionVector);		
	}	
   /////GF밖이라면
    else
    {
		land_pub.publish(val);
	}  
}
void targetCallback(sensor_msgs::NavSatFix vel) //목표 gps값
{    	
	DesiredGPS=vel;		
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "SpeedController_follower");
	ros::NodeHandle nh_;	
	
	ros::Subscriber sub = nh_.subscribe("/bebop1/fix", 1, velCallback);
	ros::Subscriber sub_target = nh_.subscribe("/bebop/fix", 1, targetCallback);
	land_pub = nh_.advertise<std_msgs::Empty>("/bebop1/reset", 1);	
	pub_dirv=nh_.advertise<geometry_msgs::Vector3>("/dirvector1", 1);
	
	ros::spin();
	return 0;	
}


