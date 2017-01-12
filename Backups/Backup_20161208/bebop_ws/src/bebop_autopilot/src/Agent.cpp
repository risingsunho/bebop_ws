#include <ros/ros.h>
#include "sensor_msgs/NavSatFix.h"
#include "geometry_msgs/Vector3.h"
#include <math.h>
#include <std_msgs/Empty.h>

#define PI 3.14159265358979323846
#define THETA 19.3373375
//#define ZeropointX 126.866125
//#define ZeropointY 37.597643 //////연병장 0
//#define ZeropointX 126.865995
//#define ZeropointY 37.6005335
#define ZeropointX 126.865059
#define ZeropointY 37.600084 //풋살장
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

geometry_msgs::Vector3 direction;
int mode=1;
double turnFactor=0.04;
bool firsttime = true;
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
	speed=sqrt(direction.x*direction.x+direction.y*direction.y);
	if(mode==1 && speed !=0)
	{		
		if(speed<turnFactor)
		{
			pub.publish(B);
			mode=2;
		}
		else pub.publish(A);
			
	}
	else if(mode==2&&speed !=0)
	{		
		if(speed<turnFactor)
		{
			pub.publish(C);
			mode=2;
		}
		else pub.publish(B);
	}
	else if(mode==3&&speed !=0)
	{		
		if(speed<turnFactor)
		{
			pub.publish(D);			
			mode=4;
		}
		else
		{
			pub.publish(C);
		}
		
	}
	else if(mode==4&&speed !=0)
	{
		
		if(speed<turnFactor)
		{
			//pub.publish(AD);
			mode=1;
		}
		else pub.publish(D);
	}
	else if(mode==5&&speed !=0)
	{
		if(speed<turnFactor)
		{
			mode=6;
		}
	}
	else{
		
	}
	ROS_INFO("%d",mode);
}
void velCallback(sensor_msgs::NavSatFix vel) //현재 gps값 수신
{
	currentGPS=vel;
	
}
void velCallbackDirection(geometry_msgs::Vector3 vec)
{
	direction=vec;	
	if(firsttime)
	{
		pub.publish(A);
		firsttime = false;
	}
	else	setmode();
	
}
int main(int argc, char **argv)
{
	ros::init(argc, argv, "Agent");
	ros::NodeHandle nh_;	
	
	
	B.longitude=126.865912;
	B.latitude=37.6003015;
	B.altitude=20;
	
	A.longitude=126.866043;
	A.latitude=37.600299;
	A.altitude=20;
	
	C.longitude=126.865818167;
	C.latitude=37.6002353333;
	C.altitude=20;
	
	D.longitude=126.865818167;
	D.latitude=37.6002353333;
	D.altitude=20;
	
	AD.longitude=126.865818167;
	AD.latitude=37.6002353333;
	AD.altitude=20;
	
	
	
	
	/*A.longitude=126.866238167;
	A.latitude=37.600881;
	A.altitude=20;
	
	B.longitude=126.866161;
	B.latitude=37.600759;
	B.altitude=20;
	
	C.longitude=126.8662891;
	C.latitude=37.6007555;
	C.altitude=20;
	
	D.longitude=126.866352833;
	D.latitude=37.6008286667;
	D.altitude=20;
	
	AD.longitude=126.866352833;
	AD.latitude=37.600828667;
	AD.altitude=20;*/
	
	
	pub = nh_.advertise<sensor_msgs::NavSatFix>("/target", 1);
	ros::Subscriber sub = nh_.subscribe("/bebop/fix", 1, velCallback);
	ros::Subscriber sub_directionVector = nh_.subscribe("/dirvector", 1, velCallbackDirection);
	ros::Rate loop_rate(5);
	
	/*while(ros::ok())
	{
		setmode();
		ros::spinOnce();
		loop_rate.sleep();
	}*/
	ros::spin();
	return 0;	
}


