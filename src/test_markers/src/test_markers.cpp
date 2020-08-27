#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

ros::Publisher marker_pub;

// initial position and oppacity for markers
float pickUp_x = -1.2;
float pickUp_y = -6.8;
float dropOff_x = -6.8;
float dropOff_y =  1.2;
float oppacity_on = 1.0;
float oppacity_off = 0.0;

// Setup marker 
bool markerSetup (float position_x, float position_y, float oppacity){

        visualization_msgs::Marker marker;

        marker.header.frame_id = "/odom";
        marker.header.stamp = ros::Time::now();

        marker.ns = "cube";
        marker.id = 0;

        marker.type = visualization_msgs::Marker::CUBE;

        marker.action = visualization_msgs::Marker::ADD;	

        marker.pose.position.x = position_x;
        marker.pose.position.y = position_y;
        marker.pose.position.z = 0;
        marker.pose.orientation.x = 0.0;
        marker.pose.orientation.y = 0.0;
        marker.pose.orientation.z = 0.0;
        marker.pose.orientation.w = 1.0;

        marker.scale.x = 0.5;
        marker.scale.y = 0.5;
        marker.scale.z = 0.5;

        marker.color.r = 0.0f;
        marker.color.g = 1.0f;
        marker.color.b = 0.0f;
        marker.color.a = oppacity;

        marker.lifetime = ros::Duration();

        // Publish 
        while (marker_pub.getNumSubscribers() < 1)
        {
           if (!ros::ok())
           {
              return 0;
           }
         ROS_WARN_ONCE("Please create a subscriber to the marker");
         sleep(1);
        }
        marker_pub.publish(marker);

   return true;

}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "add_markers");

    ros::NodeHandle n;
    ros::Rate r(1);

    marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 2);
    
    markerSetup(pickUp_x, pickUp_y,oppacity_on);
    sleep(5); 
    markerSetup(pickUp_x, pickUp_y,oppacity_off);
    sleep(5);
    markerSetup(dropOff_x, dropOff_y,oppacity_on);

    ros:: spin();
    return 0;
}
