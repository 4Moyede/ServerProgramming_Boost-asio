#include "../include/LobbyManager.hpp"

int LobbyManager::numinstantiated = 0;

void LobbyManager::initializeID()
{
    while(!user_ID.empty())         user_ID.pop();
    for(int i = 0 ; i < 100; i++)   user_ID.push(i);
    many = 0;
}

Body LobbyManager::LoginUser(User newUser)
{
    if(std::strcmp(user_[newUser.getUniqueUserID()].getID(), newUser.getID()) == 0 || many == MAXUSERS){
        newUser.setMessageHeader(MessageHeader::LOGIN_FAIL);
        return newUser.getBody();
    }

    int user_Number = user_ID.front();
    user_ID.pop();

    newUser.setUniqueUserID(user_Number);
    user_[user_Number] = newUser;
    many++;

    return user_[user_Number].getBody();
}

void LobbyManager::LogoutUser(User oldUser)
{
    Body oldBody = oldUser.getBody();
    user_[oldUser.getUniqueUserID()] = User();
    user_ID.push(oldBody._uniqueUserID);
}

Body LobbyManager::setReady(Body user)
{
    if(user_[user._uniqueUserID].getHeader() != MessageHeader::GAME_START){
        if(user_[user._uniqueUserID].getHeader() != MessageHeader::READY){
            user_[user._uniqueUserID].setMessageHeader(MessageHeader::READY);
            ready_players.push_back(user._uniqueUserID);

            if(ready_players.size() == MAXPLAYERS){
                int gameID = game_.getGameID();
                for(int i = 0; i < MAXPLAYERS; i++){
                    user_[ready_players[i]].setMessageHeader(MessageHeader::GAME_START);
                    user_[ready_players[i]].setUniqueGameID(gameID);
                }
                ready_players.clear();
                user_[user._uniqueUserID].setHPFull();
                int playerNum = game_.startGame(user_[user._uniqueUserID]);
                user_[user._uniqueUserID].setPlayerNumber(playerNum);
                std::cout << playerNum << " player added\n";
            }
        }
    }
    else{
        user_[user._uniqueUserID].setHPFull();
        int playerNum = game_.startGame(user_[user._uniqueUserID]);
        user_[user._uniqueUserID].setPlayerNumber(playerNum);
        std::cout << playerNum << " player added\n";
    }
    return user_[user._uniqueUserID].getBody();
}

Body LobbyManager::changeStatus(Body user)
{
    user_[user._uniqueUserID].setBody(user);
    return user_[user._uniqueUserID].getBody();
}