#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include "sensor_msgs/NavSatFix.h"
#include <math.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Int64.h>

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

sensor_msgs::NavSatFix bebopGPS;
sensor_msgs::NavSatFix bebop1GPS;
sensor_msgs::NavSatFix myGPS;
sensor_msgs::NavSatFix AgentGPS;


geometry_msgs::Vector3 LeaderVector;


sensor_msgs::NavSatFix DesiredGPS;
sensor_msgs::NavSatFix CurrentGPS;

geometry_msgs::Vector3 DesiredPosition;
geometry_msgs::Vector3 CurrentPosition;
geometry_msgs::Vector3 DirectionVector;

float_t cohfactor=0.2;
float_t sepfactor=0.3;
float_t arrfactor=0.5;


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
    
	/*Longitude = Longitude*lattolongscale; 
	Longitude = Longitude + ZeropointX;
	Latitude = Latitude + ZeropointY;*/
	////////gps값으로 변환/////
	
	return plot;

}
geometry_msgs::Vector3 Subvector(geometry_msgs::Vector3 des, geometry_msgs::Vector3 cur)
{
	geometry_msgs::Vector3 tempdir;   
	tempdir.x=(des.x-cur.x)*latscaleFactor;
	tempdir.y=(des.y-cur.y)*latscaleFactor;  
	//tempdir.z=(DesiredGPS.altitude-myGPS.altitude);	
	return tempdir;
}
void Flocking()
{
	
	geometry_msgs::Vector3 CohVector;
	geometry_msgs::Vector3 SepVector;
	
	
	geometry_msgs::Vector3 center;
	geometry_msgs::Vector3 bebopplot;
	geometry_msgs::Vector3 bebop1plot;
	geometry_msgs::Vector3 bebop2plot;
	
	
	
	bebopplot=GPStoRotatedPlot(bebopGPS);
	bebop1plot=GPStoRotatedPlot(bebop1GPS);
	bebop2plot=GPStoRotatedPlot(myGPS);
	
	center.x=(bebopplot.x+bebop1plot.x+bebop2plot.x)/3;
	center.y=(bebopplot.y+bebop1plot.y+bebop2plot.y)/3;
	
	SepVector.x=Subvector(bebop1plot,center).x+Subvector(bebop2plot,center).x;
	SepVector.y=Subvector(bebop1plot,center).y+Subvector(bebop1plot,center).y;
	
	CohVector.x=Subvector(center,bebop1plot).x+Subvector(center,bebop2plot).x;
	CohVector.y=Subvector(center,bebop1plot).y+Subvector(center,bebop2plot).y;
	
	DirectionVector.x=arrfactor*LeaderVector.x+cohfactor*CohVector.x+sepfactor*SepVector.x;
	DirectionVector.y=arrfactor*LeaderVector.y+cohfactor*CohVector.y+sepfactor*SepVector.y;
	
	
	pub_dirv.publish(DirectionVector);
	
}
void velCallback(sensor_msgs::NavSatFix vel) //bebop's GPS Value
{
	bebopGPS=vel;
}
void velCallback1(sensor_msgs::NavSatFix vel) //1's GPS Value
{
	bebop1GPS=vel;
}
void velCallback2(sensor_msgs::NavSatFix vel) //2's GPS Value
{
	myGPS=vel;
	Flocking();
}
void targetCallback(sensor_msgs::NavSatFix vel) //목표 gps값
{    	
	AgentGPS=vel;	
}
void leaderdir(geometry_msgs::Vector3 vel) //목표 gps값
{    	
	LeaderVector=vel;	
}


int main(int argc, char **argv)
{
	ros::init(argc, argv, "SpeedController_follower1");///////////////////////////////////////////
	ros::NodeHandle nh_;	
	
	ros::Subscriber sub = nh_.subscribe("/bebop/fix", 1, velCallback);
	ros::Subscriber sub1 = nh_.subscribe("/bebop1/fix", 1, velCallback1);
	ros::Subscriber sub2 = nh_.subscribe("/bebop2/fix", 1, velCallback2);
	
	ros::Subscriber sub_target = nh_.subscribe("/target", 1, targetCallback);

	ros::Subscriber sub_leader_dir = nh_.subscribe("/dirvector", 1, leaderdir);
	pub_dirv=nh_.advertise<geometry_msgs::Vector3>("/dirvector2", 1);
	
	ros::spin();
	return 0;	
}


