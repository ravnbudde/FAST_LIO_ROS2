#include <csignal>
#include <memory>

#include <rclcpp/rclcpp.hpp>

#include "fast_lio/laser_mapping_node.hpp"

void SigHandle(int sig);

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);

    signal(SIGINT, SigHandle);

    rclcpp::NodeOptions options;
    options.use_intra_process_comms(true);

    auto node = std::make_shared<fast_lio::LaserMappingNode>(options);
    rclcpp::spin(node);

    if (rclcpp::ok())
    {
        rclcpp::shutdown();
    }

    return 0;
}
