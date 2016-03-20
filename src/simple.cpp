#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>

geometry_msgs::Twist v; 

ros::Publisher twist_pub;

void sonarcallback(const std_msgs::Float32ConstPtr &m)
{
    std::cout << "Recebi! " << std::endl;
    if (m->data >0)
    {
        v.linear.x = 0;
        v.angular.z = 0;
    }
    else
    {
        v.linear.x = 1;
        v.angular.z = 0;
    }
    
    twist_pub.publish(v);
    
}


int main (int argc, char **argv)
{
    
    ros::init(argc, argv, "simple_avidance");
    
    ros::NodeHandle nh;
    
    ros::Subscriber sub = nh.subscribe("/vrep/vehicle/frontSonar", 1, sonarcallback);
    
    twist_pub = nh.advertise<geometry_msgs::Twist> ("obstacle/twist", 1);
    
    ros::spin();
    
    
    
}