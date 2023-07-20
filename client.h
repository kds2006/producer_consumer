#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

using boost::asio::ip::udp;

class sender
{
public:
    sender(const std::string& host, const short port, const std::string& prfx) :
        resolver(io_context),
        endpoints(resolver.resolve(udp::v4(), host, std::to_string(port))),
        s(io_context, udp::endpoint(udp::v4(), 0)),
        t(io_context),
        preffix(prfx)
    {}

    bool is_valid() { return !endpoints.empty(); }

    void send_msg(const boost::system::error_code& e, boost::asio::steady_timer *t=nullptr)
    {
        if (e || !is_valid()) return;

        full_msg = preffix + suffix + std::to_string(num++);
        s.send_to(boost::asio::buffer(full_msg.data(), full_msg.length()), endpoints.begin()->endpoint());

        if (t)
        {
            t->expires_at(t->expiry() + boost::asio::chrono::seconds(2));
            t->async_wait(boost::bind(&sender::send_msg, this, boost::asio::placeholders::error, t));
        }
    }

    void send_msg_timed() 
    {
        if (!is_valid()) return;

        t.expires_after(boost::asio::chrono::seconds(2));
        t.async_wait(boost::bind(&sender::send_msg, this, boost::asio::placeholders::error, &t));
    }

    void run() { io_context.run(); }

private:
    boost::asio::io_context io_context;
    udp::resolver resolver;
    udp::resolver::results_type endpoints;
    udp::socket s;
    boost::asio::steady_timer t;

    const std::string preffix;
    const std::string suffix{ "#" };
    int num = 1;
    std::string full_msg;
};

int run_client(const std::string& msg, const std::string& host, const short port)
{
    try
    {
        sender snd(host, port, msg);
        snd.send_msg(boost::system::error_code{});
        snd.send_msg_timed();
        snd.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}