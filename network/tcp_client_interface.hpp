#ifndef _TCP_CLIENT_INTERFACE_HH
#define _TCP_CLIENT_INTERFACE_HH

#include <vector>
#include <functional>

namespace net{

class tcp_client_interface{
public:
  //! ctor
  tcp_client_interface(void) = default;
  //! dtor
  virtual ~tcp_client_interface(void) = default;

  //! copy ctor
  tcp_client_interface(const tcp_client_interface&) = delete;
  //! assignment operator
  tcp_client_interface& operator=(const tcp_client_interface&) = delete;

public:
  //!
  //! structure to store write requests information
  //!
  struct write_request {
    //!
    //! bytes to write
    //!
    std::vector<char> buffer;

    //!
    //! callback to be called on operation completion
    //!
    //async_write_callback_t async_write_callback;
  };

public:
  //!
  //! start the tcp client
  //!
  //! \param addr host to be connected to
  //! \param port port to be connected to
  //! \param timeout_msecs max time to connect in ms
  //!
  virtual void connect(const std::string& addr, std::uint32_t port, std::uint32_t timeout_msecs = 0) = 0;

  //!
  //! stop the tcp client
  //!
  //! \param wait_for_removal when sets to true, disconnect blocks until the underlying TCP client has been effectively removed from the io_service and that all the underlying callbacks have completed.
  //!
  virtual void disconnect(bool wait_for_removal = false) = 0;

  //!
  //! \return whether the client is currently connected or not
  //!
  virtual bool is_connected(void) const = 0;

public:

  typedef std::function<void(const char*, std::size_t)> on_message_callback_t;

public:
  virtual void set_on_message_callback(const on_message_callback_t& cb) = 0;

public:
  virtual void sync_write(write_request& request) = 0;

public:


};

}


#endif