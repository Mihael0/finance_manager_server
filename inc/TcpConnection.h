//
// Created by mihael on 3/18/25.
//

#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <string>

class TcpConnection: public boost::enable_shared_from_this<TcpConnection>
{
  public:
    typedef boost::shared_ptr<TcpConnection> tcpPointer_t;

    static tcpPointer_t create(boost::asio::io_context& io_context){
      return tcpPointer_t(new TcpConnection(io_context));
    }
    boost::asio::ip::tcp::socket& socket(){return _socket;}

    void start() {
        _message = "HTTP/1.1 200 OK\r\n"
                   "Content-Type: text/html\r\n"
                   "Connection: close\r\n"
                   "Content-Length: 13\r\n"
                   "\r\n"
                   "Hello, world!";

        async_write(_socket, boost::asio::buffer(_message),
            boost::bind(&TcpConnection::_HandleWrite, shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
      }

  private:
    boost::asio::ip::tcp::socket _socket;
    std::string _message;

  TcpConnection(boost::asio::io_context& io_context)
  : _socket(io_context)
  {
  }

  void _HandleWrite(const boost::system::error_code& /*error*/,
      size_t /*bytes_transferred*/)
  {
  }
};


#endif //TCPCONNECTION_H
