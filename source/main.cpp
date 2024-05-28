// Library {fmt}
#include <fmt/format.h>

// Custom modules
#include "server.hpp"
using namespace kc;

int main()
{
    Server server(4444);
    server.onPacket([](const Server::Packet& packet)
    {
        static int number = 0;
        fmt::print("Packet #{}: Engine RPM: {:.0f}\n", number++, packet.rpm);
    });
    server.start();
}
