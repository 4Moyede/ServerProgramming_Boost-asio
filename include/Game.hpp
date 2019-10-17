
#ifndef GAME_HPP
#define GAME_HPP

#include "const.hpp"
#include "User.hpp"

struct Game
{
    int                 game_ID = -1;
    User                player[MAXPLAYERS];
    int                 number_of = 0;
    bool                dead[MAXPLAYERS] = { false, };
    bool                game_end = true;

    bool isFull()
    {
        return number_of == MAXPLAYERS ? true : false;
    }

    bool isGameOver()
    {
        bool over = true;
        for(int i = 0; i < MAXPLAYERS; i++)
        {
            if(player[i].getCurHP())
            {
                over = false;
                break;
            }
        }
        return over;
    }

    Body ready(User user)
    {
        user.setUniqueGameID(game_ID);
        user.setPlayerNumber(number_of);
        user.setMessageHeader(MessageHeader::READY_SUCCESS);
        
        player[number_of] = user;
        number_of++;

        return user.getBody();
    }

    void init(int id)
    {
        game_ID = id;
        for(int i = 0; i < MAXPLAYERS; i++){
            player[i] = User();
            dead[i] = false;
        }
        number_of = 0;
        game_end = true;
    }

    void updatePlayerInfo(Body player_)
    {
        player[player_._playerNumber].setBody(player_);
    }
    
};

#endif