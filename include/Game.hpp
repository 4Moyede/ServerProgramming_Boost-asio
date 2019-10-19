
#ifndef GAME_HPP
#define GAME_HPP

#include <boost/array.hpp>
#include "const.hpp"
#include "User.hpp"

class Game
{
private:
    int             game_ID;
    User            player[MAXPLAYERS];
    int             number_of;

public:
    Game();

    bool            isGameOver();
    bool            isFull()                        { return number_of == MAXPLAYERS ? true : false; }

    Body            ready(User user);

    int             getGame_ID()                    { return game_ID; }
    User            getPlayer(int i)                { return player[i]; }
    Body            getBody(int i)                  { return player[i].getBody(); }
    udp::endpoint   getAddress(int i)               { return player[i].getAddress(); }
    int             getNumberOf()                   { return number_of; }

    void            setGameID(int gameid)           { game_ID = gameid; }
    void            updatePlayerInfo();
    void            setNumberOf(int number)         { number_of = number; }

    boost::array<Body, 1>           recv_body;
    boost::array<Body, MAXPLAYERS>  send_body;
};

#endif