#include <errno.h>
#include <thread>
#include <strings.h>
#include <poll.h>
#include <fstream>
#include <functional>
#include "EventLoop.hpp"
#include "Channel.hpp"
#include "Poller.hpp"
#include "Logger.hpp"
#include "Connector.hpp"
#include "SocketHelp.hpp"
#include "InetAddress.hpp"
#include "TcpClient.hpp"
#include "TcpConnection.hpp"
#include "Buffer.hpp"
#include "EventLoopThread.hpp"
#include "Connector.hpp"
#include "tcp_client_interface.hpp"
#include "tcp_client.hpp"

EventLoop* g_loop;

void print(const char* buffer, std::size_t len)
{
  printf("on message : %s\n", buffer, len);
}

int main()
{

  LOG_INFO << "main start";
  /*ThreadPool threadPool;
  g_threadPool = &threadPool;
  threadPool.start();

  threadPool.addTask(std::bind(domainToIpTask, &image));*/

  //std::this_thread::sleep_for(std::chrono::seconds(2));

  std::unique_ptr<net::tcp_client_interface> tcp_client = std::unique_ptr<muduo::tcp_client>(new muduo::tcp_client);
  tcp_client->connect("127.0.0.1", 8008);

  tcp_client->set_on_message_callback(print);

  sleep(1);

  std::string buffer = "123456789";

  net::tcp_client_interface::write_request request = {std::vector<char>{buffer.begin(), buffer.end()}};

  tcp_client->sync_write(request);

  getchar();

  return 0;
}
