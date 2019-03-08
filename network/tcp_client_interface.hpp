#ifndef _TCP_CLIENT_INTERFACE_HH
#define _TCP_CLIENT_INTERFACE_HH

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


};

}


#endif