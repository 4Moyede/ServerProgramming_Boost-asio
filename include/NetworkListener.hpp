/**
 *  include/NetworkListener.hpp
 *      Network의 Listener
 *      Client로 부터 receive하거나, client에게 send하는 class
*/
#ifndef NetworkListener_HPP
#define NetworkListener_HPP

#include <iostream>
#include <assert.h>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "Body.hpp"
#include "User.hpp"
#include "Database.hpp"
#include "LobbyManager.hpp"
#include "GameManager.hpp"

using boost::asio::ip::udp;

class NetworkListener
{

private:
    void start_receive();
    void handle_receive(const boost::system::error_code& error, std::size_t bytecounnt);
    void start_send();
    void handle_send(const boost::system::error_code& error, std::size_t bytecount);

    Database&            database_;
    LobbyManager&        lobbymanager_;
    GameManager&         gamemanager_;

    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    boost::array<Body, 1> recv_buffer_;
    boost::array<Body, 1> send_buffer_;

    static int numinstantiated;

    void printBody(Body body_);

public:
    NetworkListener(boost::asio::io_service &io_service, int port, Database &database, LobbyManager &lobbymanager, GameManager &gamemanager):
        socket_(io_service, udp::endpoint(udp::v4(), port)),
        database_(database), lobbymanager_(lobbymanager), gamemanager_(gamemanager)
    {
        assert(numinstantiated < 1);
        numinstantiated++;

        start_receive();
    }

    ~NetworkListener() { }
};

#endif