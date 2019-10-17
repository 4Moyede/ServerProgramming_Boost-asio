#include "../include/LobbyManager.hpp"

int LobbyManager::numinstantiated = 0;

void LobbyManager::initializeID()
{
    while(!user_ID.empty())             user_ID.pop();
    for(int i = 0 ; i < MAXUSERS; i++)  user_ID.push(i);

    while(!game_ID.empty())             game_ID.pop();
    for(int i = 0 ; i < MAXGAMES; i++)  game_ID.push(i);

    many = 0;
    ready_.game_ID = game_ID.front();
}

Body LobbyManager::LoginUser(Body user, udp::endpoint ep)
{
    // 사용자가 MAXUSERS명 인 경우, 혹은 이미 로그인 되어있는 사용자인 경우 FAIL
    if(many == MAXUSERS){
        user._code = MessageHeader::LOGIN_FAIL;
        return user;
    }

    Body login = database_.use(user);
    if(login._code == MessageHeader::LOGIN_SUCCESS){
        // 로그인한 User에게 고유한 번호를 부여
        login._uniqueUserID = user_ID.front();
        user_ID.pop();
        user_[login._uniqueUserID] = User(login, ep);
        many++;
    }
    
    return login;
}

void LobbyManager::LogoutUser(User oldUser)
{
    Body oldBody = oldUser.getBody();
    user_[oldUser.getUniqueUserID()] = User();
    user_ID.push(oldBody._uniqueUserID);

    oldBody._code = MessageHeader::LOGOUT_REQUEST;
    database_.use(oldBody);
}

Body LobbyManager::setReady(Body user)
{
    if(game_ID.empty())
        user._code = MessageHeader::READY_FAIL;
    else{
        user = ready_.ready(user_[user._uniqueUserID]);

        if(ready_.isFull()){
            gamemanager_.startGame(ready_.game_ID, ready_);
            ready_.init(game_ID.front());
            game_ID.pop();
        }
    }
    
    return user;
}

Body LobbyManager::changeStatus(Body user)
{
    Body save = database_.use(user);
    if(save._code == MessageHeader::CHANGE_SUCCESS)
        user_[save._uniqueUserID].setPlayerStatus(save._player_stat);

    return save;
}

Body LobbyManager::logout(Body user)
{
    Body logout = database_.use(user);
    return logout;
}