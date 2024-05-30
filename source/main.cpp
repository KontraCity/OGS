// Library {fmt}
#include <fmt/format.h>

// Custom modules
#include "sinks/evms.hpp"
#include "server.hpp"
using namespace kc;

int main()
{
    Server server(4444);
    server.onPacket(&Sinks::EVMS);
    server.start();
}
