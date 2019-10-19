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
    pid_t pid = fork();

    if(pid == 0){
        playGame(game);
    }
}

void GameManager::playGame(Game game)
{
    boost::asio::io_service io;
    udp::socket so(io, udp::endpoint(udp::v4(), PORT));

    while(game.isGameOver())
    {
        udp::endpoint recv_ep;
        so.async_receive_from(boost::asio::buffer(game.recv_body),  recv_ep, 
                                boost::bind(&GameManager::handle_receive, this, game,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred) );
        so.async_send_to(boost::asio::buffer(game.send_body), recv_ep,
                                boost::bind(&GameManager::handle_send, this, game,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred) );
        io.poll();
    }

    endGame(game.getGame_ID());
}

void GameManager::endGame(int gameID)
{
    game_[gameID] = Game();
}

Body GameManager::getPlayer(int gameid_, int playerNum_)
{
    return game_[gameid_].getPlayer(playerNum_).getBody();
}

void GameManager::handle_receive(Game &game, const boost::system::error_code& error, std::size_t bytecounnt)
{
    game.updatePlayerInfo();
}

void GameManager::handle_send(Game &game, const boost::system::error_code& error, std::size_t bytecounnt)
{

}