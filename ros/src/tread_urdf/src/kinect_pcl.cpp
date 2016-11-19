#include <ros/ros.h>
#include <math.h>   
#include <geometry_msgs/Quaternion.h>
#include <pcl_ros/point_cloud.h>
#include <pcl_ros/transforms.h>

// Define Point Cloud type
typedef pcl::PointCloud<pcl::PointXYZ> PointCloud;

bool transform_status;
PointCloud fixed_cloud;
Eigen::Matrix4f kinect_fix_trans;

/**
 * Call back function used to transfrom the original point cloud so that it appears correctly on Gazebo.
 * The point cloud needs to be rotated 90 degrees about the Z and Y axis to show properly.
 */
void kinect_Fix_Pcl_Callback(const PointCloud::ConstPtr& kinect_pcl)
{
    PointCloud temp_cloud;
    tf::Quaternion rotate_axis(0.0f, 1.0f, 0.0f, M_PI);
    // Create transform matrix based on Rotation Matrix. Refernce: https://en.wikipedia.org/wiki/Rotation_matrix
    kinect_fix_trans = Eigen::Matrix4f::Identity();
    // Set matrix for transform about Z axis 90 degrees. NOTE: (row, col)
    float theta = -M_PI/2;
    kinect_fix_trans (0,0) = cos(theta);
    kinect_fix_trans (0,1) = -sin(theta);
    kinect_fix_trans (1,0) = sin(theta);
    kinect_fix_trans (1,1) = cos(theta);
    // Transform pcl about Z axis
    pcl::transformPointCloud(*kinect_pcl, temp_cloud, kinect_fix_trans);

    // Setup transform about Y axis 90 degrees
    kinect_fix_trans = Eigen::Matrix4f::Identity();
    kinect_fix_trans (0,0) = cos(theta);
    kinect_fix_trans (0,2) = -sin(theta);
    kinect_fix_trans (2,0) = sin(theta);
    kinect_fix_trans (2,2) = cos(theta);
    pcl::transformPointCloud(temp_cloud, fixed_cloud, kinect_fix_trans);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "kinect_pcl_fix_node");
    ros::NodeHandle nh;
    ros::Rate rate(2);

    // Subscribe to kinect points
    ros::Subscriber kinect_points = nh.subscribe<PointCloud>("/kinect/depth/points", 1, kinect_Fix_Pcl_Callback);

    // Advertise transformed point cloud
    ros::Publisher pub_Fixed_Cloud = nh.advertise<PointCloud>("/fixed_kinect/points",1);

    while(nh.ok())
    {
        // Set the frame
        fixed_cloud.header.frame_id = "base_link";
        fixed_cloud.header.stamp = ros::Time::now().toNSec();
        
        // Publish Transformed cloud 
        pub_Fixed_Cloud.publish(fixed_cloud);

        ros::Duration(0.05).sleep();
        ros::spinOnce();
    }

}
