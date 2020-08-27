#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>
#include <nav_msgs/Odometry.h>

geometry_msgs::Pose pickUp;
geometry_msgs::Pose dropOff;
visualization_msgs::Marker marker;
visualization_msgs::Marker dropoffMARKER;
ros::Publisher marker_pub;
bool is_preparing = true;


void handleCallback(const nav_msgs::Odometry::ConstPtr& msg){

    const bool isPickingUp = (abs(pickUp.position.x - msg->pose.pose.position.x) + abs(pickUp.position.y - msg->pose.pose.position.y)) < 1;
    const bool isDroppingOff = (abs(dropOff.position.x - msg->pose.pose.position.x) + abs(dropOff.position.y - msg->pose.pose.position.y)) < 2;

    if(is_preparing){
        marker_pub.publish(marker);
     }

    if(isPickingUp){
        is_preparing = false;
        sleep(5);
        marker.action = visualization_msgs::Marker::DELETE;
        marker_pub.publish(marker);

    } else if(isDroppingOff){
        sleep(5);
        dropoffMARKER.action = visualization_msgs::Marker::ADD;
        marker_pub.publish(dropoffMARKER);
    }
}


int main( int argc, char** argv )
{

    ros::init(argc, argv, "add_markers");
    ros::NodeHandle n;
    ros::Rate r(1);

    marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

    pickUp.position.x = -1.2;
    pickUp.position.y = -6.8;
    dropOff.position.x = -6.8;
    dropOff.position.y = -2.6;

    ros::Subscriber marker_sub = n.subscribe("/odom",1000,handleCallback);

    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    marker.ns = "add_markers";
    marker.id = 0;
    marker.type = visualization_msgs::Marker::CUBE;

    marker.action = visualization_msgs::Marker::ADD;
    marker.scale.x = 0.5;
    marker.scale.y = 0.5;
    marker.scale.z = 0.5;
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;
    marker.lifetime = ros::Duration();

    marker.pose.position.x = pickUp.position.x;
    marker.pose.position.y = pickUp.position.y;

    dropoffMARKER = marker;
    dropoffMARKER.id = 1;
    dropoffMARKER.pose.position.x = dropOff.position.x;
    dropoffMARKER.pose.position.y = dropOff.position.y;


    //std::cout << "MAIN" << std::endl;
    marker_pub.publish(marker);


    while(ros::ok()){
        ros::spinOnce();
        r.sleep();
    }

}
