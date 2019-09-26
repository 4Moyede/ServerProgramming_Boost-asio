#include "../include/GameManager.hpp"

int GameManager::numinstantiated = 0;

GameManager::GameManager()
{
    assert(numinstantiated < 1);
    numinstantiated++;
}

void GameManager::startGame(int gameID, Game game)
{
    game_[gameID] = game;
}

void GameManager::playGame(Body player_, Body send_Body[])
{

}

Body GameManager::endGame(Body body)
{

}


Body GameManager::getPlayer(int gameid_, int playerNum_)
{
    return game_[gameid_].player[playerNum_].getBody();
}