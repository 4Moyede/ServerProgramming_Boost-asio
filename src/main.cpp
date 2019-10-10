/**
 *  main.cpp
 *      main cpp file of server
 * 
 *  TODO
 *      Lobby Player Manage: Game에 입장 시, Game Room Manager에 저장하고 Room Number 지정
 *      Game Room Manage : 일정한 시간에 계속 6명의 Player Data 수신 및 전송
 *      Change User character status : Lobby의 배열에서 변경, Logout시, Database에 저장
*/

#include "../include/Database.hpp"
#include "../include/NetworkListener.hpp"
#include "../include/LobbyManager.hpp"
#include "../include/GameManager.hpp"

using boost::asio::ip::udp;

int main()
{
    std::cout << "Server Started!\n";
    
    try
    {
        boost::asio::io_service io_service;
    
        Database        database;
        GameManager     gamemanager;
        LobbyManager    lobbymanager(database, gamemanager);
        NetworkListener network(io_service, PORT, database, lobbymanager, gamemanager);

        while(true){
            io_service.poll();
        }
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "Server is shutdown!" << std::endl;
    
    return 0;
}