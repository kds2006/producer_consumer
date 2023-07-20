# producer_consumer
The client/server implements producer/consumer interaction via boost library.
Run utility.cpp w/o parameters to see how to use.

Pros of the implemented solution:
1) It is simple in implementation, boost/asio;
2) It is cross-platform solution, thanks to the use of the boost library;
3) boost::asio is stable network library w/ great implementation of asynchrony;
4) socket, it is a scalable solution and can be used in network communication;
5) Listening to all incoming on port is the best implementation of "1 to many" topology;
6) Thanks to sockets we have the implementation of singlethon from box;
7) Thanks to sockets the number of clients is unlimited.
