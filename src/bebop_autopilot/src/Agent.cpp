#include <ros/ros.h>
#include "sensor_msgs/NavSatFix.h"
#include "geometry_msgs/Vector3.h"
#include <math.h>
#include <std_msgs/Empty.h>
#include <queue>
#include <nav_msgs/Odometry.h>
#include <tf/transform_datatypes.h>


#define PI 3.14159265358979323846
#define THETA 19.3373375
#define ZeropointX 126.866125
#define ZeropointY 37.597643 //////연병장 0
//#define ZeropointX 126.865995
//#define ZeropointY 37.6005335
//#define ZeropointX 126.865059
//#define ZeropointY 37.600084 //풋살장
#define longtolatscale 0.7939642835
#define lattolongscale 1.2595025
#define costheta  0.95105651629515357211643933337938
#define sintheta 0.30901699437494742410229341718282
#define latscaleFactor 1779.359430

#define A_longitude 123

#define LEADER_BND 0.036
#define LEADER_OUT_BND 0.055


using namespace std;

ros::Publisher pub;
ros::Publisher land_pub;
ros::Publisher land_pub1;

sensor_msgs::NavSatFix WP[8];
sensor_msgs::NavSatFix currentGPS;

geometry_msgs::Vector3 currentdirectionVector;
geometry_msgs::Vector3 nextdirectionVector;


std_msgs::Empty val;

queue<sensor_msgs::NavSatFix> Queue;

geometry_msgs::Vector3 DirectionVector;

int mode=5;
double cyaw=0;

bool firsttime = true;

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
double VectorToYaw(geometry_msgs::Vector3 vec) //방향벡터->YAW
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

void velCallbackOdom(const nav_msgs::Odometry::ConstPtr& vel) //5번
{
	geometry_msgs::Quaternion quat;
	geometry_msgs::Vector3 direction;
	quat.x=vel->pose.pose.orientation.x;
    quat.y=vel->pose.pose.orientation.y;
    quat.z=vel->pose.pose.orientation.z;
    quat.w=vel->pose.pose.orientation.w;
    
    direction=ToEulerianAngle(quat);  //odom수신 & 각도계로 변환
    direction.z=-(direction.z*(180/PI));  //odom수신 값 scaling
    
    cyaw=direction.z;   
}
	
void velCallbackGPS(sensor_msgs::NavSatFix vel) //1번
{
	currentGPS=vel;
}

geometry_msgs::Vector3 MakeDirectionVector(sensor_msgs::NavSatFix desiredGPS)
{
	geometry_msgs::Vector3 CurrentPosition;
	geometry_msgs::Vector3 DesiredPosition;
	geometry_msgs::Vector3 DirectionVector;
	
	CurrentPosition=GPStoRotatedPlot(currentGPS); 
	DesiredPosition=GPStoRotatedPlot(desiredGPS);   
	
	DirectionVector.x=(DesiredPosition.x-CurrentPosition.x)*latscaleFactor;
	DirectionVector.y=(DesiredPosition.y-CurrentPosition.y)*latscaleFactor;  
	
	return DirectionVector;
}
void setmode()
{
	double dist=0;
	double cdirectionyaw=0;
	double ndirectionyaw=0;
	
	double csetpointyaw=0;
	double nsetpointyaw=0;
	
	if(currentGPS.longitude!=500 && currentGPS.latitude!=500)
	{
		currentdirectionVector=MakeDirectionVector(WP[mode]); //현재 WP와의 방향벡터
		nextdirectionVector=MakeDirectionVector(WP[mode+1]); //다음 WP와의 방향벡터  //3번
		
		cdirectionyaw=VectorToYaw(currentdirectionVector);
		ndirectionyaw=VectorToYaw(nextdirectionVector); // 4번 목표 yaw계산
		
		if(cdirectionyaw<0)
		{
			cdirectionyaw=360-abs(cdirectionyaw);
		}
		if(cyaw<0)
		{
			cyaw=360-abs(cyaw);
		}
		if(ndirectionyaw<0)
		{
			cdirectionyaw=360-abs(cdirectionyaw);
		}
		//ROS_INFO("cdirectionyaw : %f", cdirectionyaw);
		//ROS_INFO("ndirectionyaw : %f", ndirectionyaw);
		//ROS_INFO("cyaw : %f", cyaw);
		
		csetpointyaw=cyaw-cdirectionyaw;
		nsetpointyaw=cyaw-ndirectionyaw;				
		
		dist=sqrt(currentdirectionVector.x*currentdirectionVector.x+currentdirectionVector.y*currentdirectionVector.y);
		
		
		if(dist<LEADER_BND)
		{
			//mode=mode+1;
			if(mode == 5) mode = 2;
			else mode = 5;						
		}
		else
		{ 
			if(dist<LEADER_OUT_BND)
			{
				if(mode == 5) mode = 2;
			else mode = 5;	
				/*if(abs(csetpointyaw)>(nsetpointyaw))
				{
					//mode=mode+1;
				}*/
			}
		}
		//if(mode>7)	{ mode=0; }
		
		pub.publish(WP[mode]);
		ROS_INFO("%d", mode);
	}
	
}
int main(int argc, char **argv)
{
	ros::init(argc, argv, "Agent");
	ros::NodeHandle nh_;	
	
	pub = nh_.advertise<sensor_msgs::NavSatFix>("/target", 1);
	ros::Subscriber subOdom = nh_.subscribe("/bebop/odom", 1, velCallbackOdom);
	ros::Subscriber sub = nh_.subscribe("/bebop/fix", 1, velCallbackGPS);
	
	WP[0].longitude = 126.86599;
	WP[0].latitude = 37.600252;
	
	WP[1].longitude = 126.866061;
	WP[1].latitude = 37.600238;
	
	WP[2].longitude = 126.866083;
	WP[2].latitude = 37.600274;
	
	WP[3].longitude = 126.866074;
	WP[3].latitude = 37.600329;
	
	WP[4].longitude = 126.86599;
	WP[4].latitude = 37.600348;
	
	WP[5].longitude = 126.86593;
	WP[5].latitude = 37.600340;
	
	WP[6].longitude = 126.86589;
	WP[6].latitude = 37.600303;
	
	WP[7].longitude = 126.865925;
	WP[7].latitude = 37.600283;
	
	WP[8].longitude = 126.86599;
	WP[8].latitude = 37.600252;
	
	ros::Rate loop_rate(15);
	while(ros::ok())
	{
		setmode();
		ros::spinOnce();
		loop_rate.sleep();
	}
	ros::spin();
	return 0;	
}
