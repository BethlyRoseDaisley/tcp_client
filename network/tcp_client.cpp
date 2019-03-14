
#include "tcp_client.hpp"
#include "EventLoop.hpp"
#include "EventLoopThread.hpp"
#include "TcpConnection.hpp"

using namespace muduo;

static EventLoopThread static_event_loop;
std::unique_ptr<EventLoop> muduo::active_event_loop = std::unique_ptr<EventLoop>(static_event_loop.startLoop());

tcp_client::tcp_client()
{

}

void tcp_client::connect(const std::string& addr, std::uint32_t port, std::uint32_t timeout_msecs)
{

  m_client = std::unique_ptr<Net::TcpClient>(new Net::TcpClient(active_event_loop.get(), InetAddress(addr, port)));

  m_client->setConnectionCallBack(std::bind(&muduo::tcp_client::on_connection, this, std::placeholders::_1));
  m_client->setMessageCallBack(std::bind(&muduo::tcp_client::on_message, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
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


void tcp_client::sync_write(write_request& request)
{
  m_connection->send(request.buffer);
}

void tcp_client::on_connection(const TcpConnectionPtr& conn)
{
  m_connection = conn;
}

void tcp_client::set_on_message_callback(const on_message_callback_t& cb)
{
  m_msg_cb = cb;
}

void tcp_client::on_message(const TcpConnectionPtr& p, Buffer* b, ssize_t l)
{
  if(m_msg_cb){
    m_msg_cb(b->peek(), l);
    b->retrieve(l);
  }
}