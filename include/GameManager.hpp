/**
 *  include/GameManager.hpp
 *      게임들을 관리하는 class, 하나의 게임에는 6명의 player 참여.
 *      Player들의 Data를 Update, 전송
*/
#ifndef GameManager_HPP
#define GameManager_HPP

#include <iostream>
#include <queue>
#include <vector>
#include <assert.h>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <sys/types.h>
#include <sys/shm.h>

#include "User.hpp"
#define SHARED_MEMORY_KEY   1234
#define MAXPLAYERS          2
#define MAXGAMES            10

using boost::asio::ip::udp;

struct game{
    User                player[MAXPLAYERS];
    int                 ready = 0;
    bool                dead[MAXPLAYERS] = { false, };
    std::vector<int>    rank;
    bool                game_end = false;
};

class GameManager
{
private:
    game                game_[MAXGAMES];
    std::queue<int>     gameID;
    std::queue<User>    update_;

    static int          numinstantiated;

    void    initializeID();

public:
    GameManager();

    int     getGameID();

    int     startGame(User player_);
    bool    waitPlayers(Body player_);
    void    playGame(Body player_, Body send_Body[]);
    Body    endGame(Body player_);
    Body    getPlayer(int gameid_, int playerNum_);
};

#endif