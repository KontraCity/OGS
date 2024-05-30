#pragma once

// STL modules
#include <iostream>
#include <sstream>

// Boost libraries
#define _WIN32_WINNT 0x0601
#include <boost/asio.hpp>

// Custom modules
#include "server.hpp"
#include "utility.hpp"

namespace kc {

/* Namespace aliases and imports */
namespace asio = boost::asio;

namespace Sinks
{
    /// @brief Engine Vitals Monitoring System sink
    /// @param packet Received packet
    void EVMS(const Server::Packet& packet);
}

} // namespace kc
