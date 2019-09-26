#include "../include/LobbyManager.hpp"

int LobbyManager::numinstantiated = 0;

void LobbyManager::initializeID()
{
    while(!user_ID.empty())             user_ID.pop();
    for(int i = 0 ; i < MAXUSERS; i++)  user_ID.push(i);
    many = 0;
}

Body LobbyManager::LoginUser(Body user)
{
    Body login = database_.use(user);
    if(login._code == MessageHeader::LOGIN_SUCCESS){
        // 사용자가 MAXUSERS명 인 경우, 혹은 이미 로그인 되어있는 사용자인 경우 FAIL
        if(many == MAXUSERS || find(user_, user_+many, User(login)) != user_+many){
            login._code = MessageHeader::LOGIN_FAIL;
            return login;
        }

        // 로그인한 User에게 고유한 번호를 부여
        int user_Number = user_ID.front();
        user_ID.pop();
        login._uniqueUserID = user_Number;
        user_[user_Number] = User(login);
        many++;
    }
    
    return login;
}

void LobbyManager::LogoutUser(User oldUser)
{
    Body oldBody = oldUser.getBody();
    user_[oldUser.getUniqueUserID()] = User();
    user_ID.push(oldBody._uniqueUserID);

    oldBody._code = MessageHeader::CHANGE_STATUS;
    database_.use(oldBody);
}

Body LobbyManager::setReady(Body user)
{
    bool found = false;
    for(int i = 0; i < MAXGAMES; i++){
        if(ready_[i].game_end && ready_[i].players < MAXPLAYERS){
            user._uniqueGameID = i;
            user._playerNumber = ready_[i].players++;
            ready_[i].player[user._playerNumber] = user;
            if(ready_[i].players == MAXPLAYERS){
                ready_[i].game_end = false;
                gamemanager_.startGame(i, ready_[i]);
            }
            found = true;
            break;
        }
    }

    if(!found)
        user._code = MessageHeader::LOGIN_FAIL;

    return user;
}

Body LobbyManager::changeStatus(Body user)
{
    Body save = database_.use(user);
    if(save._code == MessageHeader::CHANGE_SUCCESS)
        user_[save._uniqueUserID].setPlayerStatus(save._player_stat);

    return save;
}