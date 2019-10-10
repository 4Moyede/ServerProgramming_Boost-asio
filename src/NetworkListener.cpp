#include "../include/NetworkListener.hpp"

int NetworkListener::numinstantiated = 0;

void NetworkListener::start_receive()
{
    socket_.async_receive_from(boost::asio::buffer(recv_buffer_), remote_endpoint_, 
                                boost::bind(&NetworkListener::handle_receive, this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred)
                                            );
}

void NetworkListener::handle_receive(const boost::system::error_code& error, std::size_t bytecounnt)
{
    if (!error || error == boost::asio::error::message_size)
    {
        Body recv_ = recv_buffer_.front();
        Body send_[MAXPLAYERS];
        std::cout << "\n";
        printBody(recv_);

        if(recv_._code == MessageHeader::LOGIN_REQUEST){
            std::cout << "Recv Login Request from " << recv_._uniqueUserID << "\n";
            send_[0] = lobbymanager_.LoginUser(recv_);
        }
        else if(recv_._code == MessageHeader::REGISTER_USERID){
            std::cout << "Recv Register Request from " << recv_._uniqueUserID << "\n";
            send_[0] = database_.use(recv_);
        }
        else if(recv_._code == MessageHeader::READY){
            std::cout << "Recv Ready from " << recv_._uniqueUserID << "\n";
            send_[0] = lobbymanager_.setReady(recv_);
        }
        else if(recv_._code == MessageHeader::GAME){
            std::cout << "Recv Game from " << recv_._uniqueUserID << "\n";
            gamemanager_.playGame(recv_, send_);
        }
        else if(recv_._code == MessageHeader::CHANGE_STATUS){
            std::cout << "Recv Change Status from " << recv_._uniqueUserID << "\n";
            send_[0] = lobbymanager_.changeStatus(recv_);
        }

        start_receive();
    }
}

void NetworkListener::handle_send(const boost::system::error_code& error, std::size_t bytecount)
{

}

void NetworkListener::printBody(Body body_)
{
    std::cout << "Code    : " << int(body_._code) << "\n";
    std::cout << "ID      : " << body_._ID << "\n";
    std::cout << "User ID : " << body_._uniqueUserID << "\n";
    std::cout << "Game ID : " << body_._uniqueGameID << "\n";
    std::cout << "Input   : " << int(body_._keyboard) << "\n";
    std::cout << "Player  : " << body_._playerNumber << "\n";;
    std::cout << "State   : " << body_._player_stat << "\n";;
    std::cout << "MaxHP   : " << body_._maxHP << "\n";
    std::cout << "CurHP   : " << body_._curHP << "\n";
}