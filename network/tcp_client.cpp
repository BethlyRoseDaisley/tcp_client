
#include "tcp_client.hpp"
#include "EventLoop.hpp"
#include "EventLoopThread.hpp"

using namespace muduo;

static EventLoopThread static_event_loop;
std::unique_ptr<EventLoop> muduo::active_event_loop = std::unique_ptr<EventLoop>(static_event_loop.startLoop());

tcp_client::tcp_client()
{

}

void tcp_client::connect(const std::string& addr, std::uint32_t port, std::uint32_t timeout_msecs)
{

  m_client = std::unique_ptr<Net::TcpClient>(new Net::TcpClient(active_event_loop.get(), InetAddress(addr, port)));
  m_client->start();

}

void tcp_client::disconnect(bool wait_for_removal)
{
  m_client->disconnect();
}

bool tcp_client::is_connected() const
{
  return m_client->isConnected();
}

