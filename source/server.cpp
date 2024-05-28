#include "server.hpp"

namespace kc {

void Server::startReceiving()
{
    m_socket.async_receive_from(
        boost::asio::buffer(m_buffer),
        m_endpoint,
        boost::bind(&Server::handlePacket, this, boost::placeholders::_1, boost::placeholders::_2)
    );
}

void Server::handlePacket(const boost::system::error_code& error, std::size_t bytesTransferred)
{
    if (!error)
    {   
        std::lock_guard<std::mutex> lock(m_mutex);
        Packet* receivedPacket = reinterpret_cast<Packet*>(m_buffer.data());
        for (const CallbackFunction& callback : m_callbacks)
            callback(*receivedPacket);
    }

    startReceiving();
}

Server::Server(uint16_t port)
    : m_service()
    , m_socket(m_service, asio::ip::udp::endpoint(asio::ip::udp::v6(), port))
    , m_buffer({})
{}

void Server::start()
{
    startReceiving();
    m_service.run();
}

void Server::onPacket(const CallbackFunction& callback)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_callbacks.push_back(callback);
}

void Server::resetOnPacket()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_callbacks.clear();
}

} // namespace kc
