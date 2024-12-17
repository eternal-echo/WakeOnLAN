// wol/cli.cpp
#include <boost/program_options.hpp>
#include "wol.hpp"
#include <iostream>

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
    try {
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help,h", "Produce help message")
            ("mac,m", po::value<std::string>(), "MAC address to wake up (format: xx:xx:xx:xx:xx:xx)")
            ("ip,i", po::value<std::string>()->default_value("255.255.255.255"), "Broadcast IP address (default: 255.255.255.255)")
            ("port,p", po::value<unsigned short>()->default_value(9), "UDP port (default: 9)");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << desc << std::endl;
            return 0;
        }

        if (!vm.count("mac")) {
            std::cerr << "MAC address is required.\n";
            return 1;
        }

        std::string mac_address = vm["mac"].as<std::string>();
        std::string ip_address = vm["ip"].as<std::string>();
        unsigned short port = vm["port"].as<unsigned short>();

        // 调用 WOL 发送函数并根据返回值输出信息
        WOLStatus status = wake_on_lan(mac_address, ip_address, port);

        switch (status) {
            case WOLStatus::SUCCESS:
                std::cout << "WOL signal sent to MAC address " << mac_address << " at IP " << ip_address << ":" << port << std::endl;
                break;
            case WOLStatus::INVALID_MAC:
                std::cerr << "Invalid MAC address format.\n";
                break;
            case WOLStatus::SEND_FAILED:
                std::cerr << "Failed to send WOL signal.\n";
                break;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
