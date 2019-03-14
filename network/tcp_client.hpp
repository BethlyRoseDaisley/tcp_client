#ifndef _MUDUO_TCP_CLIENT_HH
#define _MUDUO_TCP_CLIENT_HH

#include <memory>

#include "tcp_client_interface.hpp"
#include "TcpClient.hpp"

namespace muduo {

extern std::unique_ptr<EventLoop> active_event_loop;

class tcp_client : public net::tcp_client_interface {
public:
  //! ctor
  tcp_client(void);
  //! dtor
  ~tcp_client(void) = default;

  //! copy ctor
  tcp_client(const tcp_client_interface&) = delete;
  //! assignment operator
  tcp_client& operator=(const tcp_client_interface&) = delete;  

public:

  //!
  //! start the tcp client
  //!
  //! \param addr host to be connected to
  //! \param port port to be connected to
  //! \param timeout_msecs max time to connect in ms
  //!
  virtual void connect(const std::string& addr, std::uint32_t port, std::uint32_t timeout_msecs = 0);

  //!
  //! stop the tcp client
  //!
  //! \param wait_for_removal when sets to true, disconnect blocks until the underlying TCP client has been effectively removed from the io_service and that all the underlying callbacks have completed.
  //!
  virtual void disconnect(bool wait_for_removal = false);

  //!
  //! \return whether the client is currently connected or not
  //!
  virtual bool is_connected(void) const;

public:
  void set_on_message_callback(const on_message_callback_t& cb);

public:

  void sync_write(write_request& request);

private:

  void on_connection(const TcpConnectionPtr& );

  void on_message(const TcpConnectionPtr& , Buffer*, ssize_t );

  //!
  //!muduo net tcp_client
  //!
  std::unique_ptr<Net::TcpClient> m_client;

  TcpConnectionPtr m_connection;

  on_message_callback_t m_msg_cb;
};

}

#endif