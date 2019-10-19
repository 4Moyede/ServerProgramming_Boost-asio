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
#include <sys/types.h>
#include <boost/bind.hpp>
#include <boost/array.hpp>

#include "User.hpp"
#include "Body.hpp"

#include "Game.hpp"

using boost::asio::ip::udp;

class GameManager
{
private:
    Game                game_[MAXGAMES];
    static int          numinstantiated;
    
public:
    GameManager();

    void    startGame(int gameID, Game game);
    void    playGame(Game game);
    
    void    handle_receive(Game &game, const boost::system::error_code& error, std::size_t bytecounnt);
    void    handle_send(Game &game, const boost::system::error_code& error, std::size_t bytecounnt);
    
    void    endGame(int gameID);

    Body    getPlayer(int gameid_, int playerNum_);
};

#endif