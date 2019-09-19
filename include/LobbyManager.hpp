/**
 *  include/LobbyManager.hpp
 *      로그인한 User들, 정보 저장 & 관리
 * 
 *  User LoginUser(User newUser);
 *  User getUser(int uniqueUserID);
 *  void LogoutUser(User oldUser);  
*/
#ifndef LobbyManager_HPP
#define LobbyManager_HPP

#include "User.hpp"
#include "Database.hpp"
#include "GameManager.hpp"
#include <queue>
#include <set>
#include <assert.h>
#include <algorithm>

class LobbyManager
{
private:
    User                user_[100];
    std::queue<int>     user_ID;
    int                 many;

    std::vector<int>    ready_players;
    
    Database&           database_;
    GameManager&        game_;
    static int          numinstantiated;

    void initializeID();

public:

    LobbyManager(Database &database, GameManager &gamemanager)
    :database_(database), game_(gamemanager), many(0)
    {
        assert(numinstantiated < 1);
        numinstantiated++;

        initializeID();
    }

    Body LoginUser(Body user);
    void LogoutUser(User user);
    Body setReady(Body user);

    Body changeStatus(Body user);
};

#endif