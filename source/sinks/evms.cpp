#include "sinks/evms.hpp"

namespace kc {

void Sinks::EVMS(const Server::Packet& packet)
{
    static asio::io_service service;
    static asio::serial_port serial(service);
    static bool initialized = false;
    if (!initialized)
    {
        try
        {
            serial.open("COM4");
        }
        catch (const boost::system::system_error&)
        {
            std::cerr << "EVMS sink: couldn't open COM port\n";
            return;
        }

        serial.set_option(boost::asio::serial_port_base::baud_rate(115200));
        serial.set_option(boost::asio::serial_port::flow_control(boost::asio::serial_port::flow_control::none));
        serial.set_option(boost::asio::serial_port::parity(boost::asio::serial_port::parity::none));
        serial.set_option(boost::asio::serial_port::stop_bits(boost::asio::serial_port::stop_bits::one));
        serial.set_option(boost::asio::serial_port::character_size(boost::asio::serial_port::character_size(8)));
        initialized = true;
    }

    static float previousValue = -1;
    float currentValue = static_cast<float>(Utility::Round(packet.oilTemp, 2));
    if (previousValue == -1)
        Utility::Sleep(0.5);  // Let ESP initialize
    else if (previousValue == currentValue)
        return;
    previousValue = currentValue;

    try
    {
        std::stringstream buffer;
        buffer << currentValue << '\n';
        asio::write(serial, asio::buffer(buffer.str()));
    }
    catch (const boost::system::system_error&)
    {
        std::cerr << "EVMS sink: connection lost\n";
        serial.close();
        previousValue = -1;
        initialized = false;
    }
}

} // namespace kc
