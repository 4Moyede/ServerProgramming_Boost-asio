#include "../include/GameManager.hpp"

int GameManager::numinstantiated = 0;

GameManager::GameManager()
{
    assert(numinstantiated < 1);
    numinstantiated++;

    initializeID();
}

void GameManager::initializeID()
{
    while(!gameID.empty())          
        gameID.pop();

    for(int i = 0; i < MAXGAMES; i++)
        gameID.push(i);
}

int GameManager::startGame(User user)
{
    int ready_ = game_[user.getUniqueGameID()].ready++;

    user.setPlayerNumber(ready_);
    game_[user.getUniqueGameID()].player[ready_] = user;

    return ready_;
}

bool GameManager::waitPlayers(Body player_)
{
    std::cout << player_._uniqueUserID << " Check Player : " << game_[player_._uniqueGameID].ready << "\n";
    if(game_[player_._uniqueGameID].ready < MAXPLAYERS)
        return true;
    else
        return false;
}

void GameManager::playGame(Body player_, Body send_Body[])
{
    if(player_._curHP == 0 && !game_[player_._uniqueGameID].dead[player_._playerNumber]){
        game_[player_._uniqueGameID].rank.push_back(player_._uniqueUserID);
        game_[player_._uniqueGameID].dead[player_._playerNumber] = true;
        std::cout << "Player " << player_._playerNumber << " dead..\n";
    }

    game_[player_._uniqueGameID].player[player_._playerNumber].setBody(player_);
    for(int i = 0; i < MAXPLAYERS; i++){
        send_Body[i] = game_[player_._uniqueGameID].player[i].getBody();
        if(game_[player_._uniqueGameID].dead[player_._playerNumber])
            send_Body[i]._keyboard = KEYBOARD::NONE;
    }

    if(game_[player_._uniqueGameID].rank.size() == MAXPLAYERS - 1){
        for(int i = 0; i < MAXPLAYERS; i++)
            send_Body[i]._code = MessageHeader::GAME_END;
    }
}

Body GameManager::endGame(Body body)
{
    if(!game_[body._uniqueGameID].game_end)
    {
        gameID.push(body._uniqueGameID);
        game_[body._uniqueGameID].game_end = true;
    }
    body._uniqueGameID = -1;
    body._code = MessageHeader::NONE;

    return body;
}

int GameManager::getGameID()
{
    int id_ = gameID.front();
    gameID.pop();

    return id_;
}

Body GameManager::getPlayer(int gameid_, int playerNum_)
{
    return game_[gameid_].player[playerNum_].getBody();
}