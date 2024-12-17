#include "doctest/doctest.h"
#include "wol.hpp"
#include <string>

// 测试成功发送 WOL 信号
TEST_CASE("Test valid MAC address for WOL signal sending") {
    // 假设发送信号成功，使用一个有效的 MAC 地址
    std::string mac_address = MAC_ADDRESS;
    std::string ip_address = IP_ADDRESS;
    unsigned short port = PORT;

    WOLStatus status = wake_on_lan(mac_address, ip_address, port);

    CHECK(status == WOLStatus::SUCCESS);  // 期望返回成功
}

TEST_CASE("Test invalid MAC address format") {
    std::string mac_address = "001122334455";  // Invalid MAC format (missing colons)
    std::string ip_address = IP_ADDRESS;
    unsigned short port = PORT;

    WOLStatus status = wake_on_lan(mac_address, ip_address, port);
    CHECK(status == WOLStatus::INVALID_MAC);
}

TEST_CASE("Test WOL signal sending failure") {
    std::string mac_address = "00:11:22:33:44:55";
    std::string ip_address = "0.0.0.0";  // Invalid IP address
    unsigned short port = 9;

    WOLStatus status = wake_on_lan(mac_address, ip_address, port);
    CHECK(status == WOLStatus::SUCCESS); // UDP无法检测到发送失败
}