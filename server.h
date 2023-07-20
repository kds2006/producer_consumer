#pragma once

#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

enum { max_length = 1024 };

void run_server(unsigned short port)
{
    boost::asio::io_context io_context;
    udp::socket sock(io_context, udp::endpoint(udp::v4(), port));
    for (;;)
    {
        char data[max_length];
        udp::endpoint sender_endpoint;
        size_t length = sock.receive_from(boost::asio::buffer(data, max_length), sender_endpoint);
        if (length > 0) {
            std::cout << std::string(data, length) << std::endl;
        }
    }
}
