// clientseerverconsoleapp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "server.h"
#include "client.h"

int main(int argc, char* argv[])
{
    try
    {
        const std::string usage = "Usage:\nutility server\nor\nutility client <text_to_send>\n";
        if (argc < 2) { std::cerr << usage; return 1; }

        const short port = 7777;

        if (argv[1] == std::string("server"))
        {
            run_server(port);
        } 
        else if (argv[1] == std::string("client"))
        {
            if (argc < 3) { std::cerr << usage; return 1; }
            return run_client(argv[2], "127.0.0.1", port);
        }
        else 
        {
            std::cerr << usage;
            return 2;
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;

}
