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
    int game_id = player_._uniqueGameID;
    int player_num = player_._playerNumber;

    if(!player_._curHP)
        game_[game_id].updatePlayerInfo(player_);

    for(int idx = 0; idx < MAXPLAYERS; idx++)
        send_Body[idx] = getPlayer(game_id, player_num);
}

void GameManager::endGame(int gameID)
{
    game_[gameID] = Game();
}

Body GameManager::getPlayer(int gameid_, int playerNum_)
{
    return game_[gameid_].player[playerNum_].getBody();
}