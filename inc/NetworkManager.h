//
// Created by mihael on 3/17/25.
//

#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H
#include <boost/bind/bind.hpp>
#include "TcpConnection.h"

class NetworkManager {
    using tcp = boost::asio::ip::tcp;
public:
    NetworkManager();
    boost::asio::io_context& GetIOContext(void);
private:
    boost::asio::io_context _io;
    tcp::acceptor _acceptor;
    /*
     * @brief Creates a socket and initiates an async accept operation waiting for a new connection.
     */
    void _StartAccept(void) {
        TcpConnection::tcpPointer_t newConnection = TcpConnection::create(_io);

        _acceptor.async_accept(newConnection->socket(),boost::bind(&NetworkManager::_HandleAccept,
            this, newConnection, boost::asio::placeholders::error()));
    }
    /*
     * @brief This function is called after _StartAccept. It services the client request and
     * prepares to initiate the next accept operation through calling start_accept().
     */
    void _HandleAccept(TcpConnection:: tcpPointer_t newConnection, const boost::system::error_code& error) {
        if (!error) {
            newConnection->start();
        }
        _StartAccept();
    }
};


#endif //NETWORKMANAGER_H
