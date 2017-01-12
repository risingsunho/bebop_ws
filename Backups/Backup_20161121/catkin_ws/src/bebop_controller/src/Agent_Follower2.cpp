#include <ros/ros.h>
#include "sensor_msgs/NavSatFix.h"
#include "geometry_msgs/Vector3.h"
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


using namespace std;

ros::Publisher pub;
ros::Publisher land_pub;
ros::Publisher land_pub1;
sensor_msgs::NavSatFix A;
sensor_msgs::NavSatFix B;
sensor_msgs::NavSatFix C;
sensor_msgs::NavSatFix D;
sensor_msgs::NavSatFix AD;
sensor_msgs::NavSatFix currentGPS;
std_msgs::Empty val;

int mode=1;
double turnFactor=0.05;
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
	
	return plot;
}
double calDirvec(sensor_msgs::NavSatFix curGPS,sensor_msgs::NavSatFix tarGPS)
{
	geometry_msgs::Vector3 myPlot;
	geometry_msgs::Vector3 targetPlot;
	geometry_msgs::Vector3 direction;
	double speed=0;
	
	myPlot=GPStoRotatedPlot(curGPS);
	targetPlot=GPStoRotatedPlot(tarGPS);
	direction.x=(targetPlot.x-myPlot.x)*latscaleFactor;
	direction.y=(targetPlot.y-myPlot.y)*latscaleFactor;
	speed=sqrt(direction.x*direction.x+direction.y*direction.y);
	
	return speed;
	
}
void setmode()
{
	double speed=0;
	if(mode==1)
	{		
		speed=calDirvec(currentGPS,A);
		if(speed<turnFactor)
		{
			mode=2;
		}
	}
	else if(mode==2)
	{
		speed=calDirvec(currentGPS,AD);
		if(speed<turnFactor)
		{
			mode=3;
		}
	}
	else if(mode==3)
	{
		speed=calDirvec(currentGPS,D);
		if(speed<turnFactor)
		{
			mode=4;
		}
	}
	else if(mode==4)
	{
		speed=calDirvec(currentGPS,C);
		if(speed<turnFactor)
		{
			mode=5;
		}
	}
	else if(mode==5)
	{
		speed=calDirvec(currentGPS,B);
		if(speed<turnFactor)
		{
			mode=6;
		}
	}
}
void velCallback(sensor_msgs::NavSatFix vel) //현재 gps값 수신
{
	currentGPS=vel;
}
int main(int argc, char **argv)
{
	ros::init(argc, argv, "Agent");
	ros::NodeHandle nh_;	
	A.longitude=126.8662775;
	A.latitude=37.6008541;
	A.altitude=20;
	
	B.longitude=126.8668518333;
	B.latitude=37.6007626666;
	B.altitude=20;
	
	C.longitude=126.866381167;
	C.latitude=37.6008393333;
	C.altitude=20;
	
	D.longitude=126.8663275;
	D.latitude=37.600813833;
	D.altitude=20;
	
	AD.longitude=126.866213667;
	AD.latitude=37.6007631667;
	AD.altitude=20;
	
	
	pub = nh_.advertise<sensor_msgs::NavSatFix>("/target", 1);
	ros::Subscriber sub = nh_.subscribe("/bebop/fix", 1, velCallback);
	ros::Rate loop_rate(10);
	land_pub = nh_.advertise<std_msgs::Empty>("/bebop/land", 1); 
	land_pub1 = nh_.advertise<std_msgs::Empty>("/bebop1/land", 1); 
	while(ros::ok())
	{
		setmode();
		if(mode==1)
		{			
			pub.publish(A);
		}
		else if(mode==2)
		{			
			pub.publish(AD);
		}	
		else if(mode==3)
		{			
			pub.publish(D);
		}
		else if(mode=4)
		{			
			pub.publish(C);
		}
		else if(mode=5)
		{			
			pub.publish(B);
		}
		else if(mode=6)
		{
			land_pub.publish(val);
			land_pub1.publish(val);
		}
		ROS_INFO("mode : %d",mode);
		ros::spinOnce();
		loop_rate.sleep();
	}
	ros::spin();
	return 0;	
}


