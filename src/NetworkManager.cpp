//
// Created by mihael on 3/17/25.
//

#include <iostream>
#include <NetworkManager.h>

using tcp = boost::asio::ip::tcp;

NetworkManager::NetworkManager()
    :_acceptor(_io, tcp::endpoint(tcp::v4(), 8080))
{
    if (!_acceptor.is_open()) {
        std::cout << "Failed to open acceptor." << std::endl;
        return;
    }
    _StartAccept();
    std::cout << "Server running on port 8080..." << std::endl;
}

boost::asio::io_context& NetworkManager::GetIOContext(void) {
    return _io;
}