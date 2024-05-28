#pragma once

// STL modules
#include <mutex>
#include <vector>
#include <functional>

// Boost libraries
#define _WIN32_WINNT 0x0601
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind/bind.hpp>

namespace kc {

/* Namespace aliases and imports */
namespace asio = boost::asio;

class Server
{
public:
    /*
    *   Generic OutGauge packet.
    *   BeamNG documentation: https://documentation.beamng.com/modding/protocols/#outgauge-udp-protocol
    */
    struct Packet
    {
        unsigned int time;
        char car[4];
        unsigned short flags;   
        char gear;
        char plid;
        float speed;
        float rpm;
        float turbo;
        float engTemp;
        float fuel;
        float oilPressure;
        float oilTemp;
        unsigned int dashLights;
        unsigned int showLights;
        float throttle;
        float brake;
        float clutch;
        char display1[16];
        char display2[16];
        int id;
    };

    // Function called when a packet is received
    using CallbackFunction = std::function<void(const Packet&)>;

private:
    asio::io_service m_service;
    asio::ip::udp::socket m_socket;
    asio::ip::udp::endpoint m_endpoint;
    boost::array<uint8_t, sizeof(Packet)> m_buffer;
    std::mutex m_mutex;
    std::vector<CallbackFunction> m_callbacks;

private:
    /// @brief Start receiving data
    void startReceiving();

    /// @brief Handle received packet
    /// @param error Error code
    /// @param bytesTransferred Count of bytes transferred
    void handlePacket(const boost::system::error_code& error, std::size_t bytesTransferred);

public:
    /// @brief Initialize the server
    /// @param port Listen port number
    Server(uint16_t port);

    /// @brief Start the server
    void start();

    /// @brief Add packet receive callback
    /// @param callback The callback to add
    void onPacket(const CallbackFunction& callback);

    /// @brief Reset packet receive callbacks
    void resetOnPacket();
};

} // namespace kc
