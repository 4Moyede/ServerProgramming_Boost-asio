
#ifndef GAME_HPP
#define GAME_HPP

#include "const.hpp"
#include "User.hpp"

struct Game
{
    int                 game_ID = -1;
    User                player[MAXPLAYERS];
    int                 players = 0;
    bool                dead[MAXPLAYERS] = { false, };
    bool                game_end = true;
};

#endif