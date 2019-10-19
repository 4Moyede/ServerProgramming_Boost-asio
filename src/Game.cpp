#include "../include/Game.hpp"

Game::Game()
{
    game_ID = -1;
    for(int i = 0; i < MAXPLAYERS; i++){
        player[i] = User();
    }
    number_of = 0;
}

bool Game::isGameOver()
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

Body Game::ready(User user)
{
    user.setUniqueGameID(game_ID);
    user.setPlayerNumber(number_of);
    user.setMessageHeader(MessageHeader::READY_SUCCESS);
    
    player[number_of] = user;
    number_of++;

    return user.getBody();
}

void Game::updatePlayerInfo()
{
    int num = recv_body.front()._playerNumber;

    player[num].setBody(recv_body.front());
    send_body[num] = player[num].getBody();
}