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
        Body recv_Body = recv_buffer_.front();
        Body send_Body[MAXPLAYERS];
        cout << "\n";
        printBody(recv_Body);

        if(recv_Body._code == MessageHeader::LOGIN_REQUEST){
            cout << "Recv Login Request from " << recv_Body._uniqueUserID << "\n";
            send_Body[0] = database_.use(recv_Body);

            if(send_Body[0]._code != MessageHeader::LOGIN_FAIL){
                User new_User(send_Body[0]);
                send_Body[0] = lobbymanager_.LoginUser(new_User);
            }
        }
        else if(recv_Body._code == MessageHeader::REGISTER_USERID){
            cout << "Recv Register Request from " << recv_Body._uniqueUserID << "\n";
            send_Body[0] = database_.use(recv_Body);
        }
        else if(recv_Body._code == MessageHeader::READY){
            cout << "Recv Ready from " << recv_Body._uniqueUserID << "\n";
            send_Body[0] = lobbymanager_.setReady(recv_Body);
        }
        else if(recv_Body._code == MessageHeader::GAME_START){
            cout << "Recv Game Start from " << recv_Body._uniqueUserID << "\n";
            send_Body[0]._curHP = send_Body[0]._maxHP;
            send_Body[0] = recv_Body;
        }
        else if(recv_Body._code == MessageHeader::GAME){
            cout << "Recv Game from " << recv_Body._uniqueUserID << "\n";
            gamemanager_.playGame(recv_Body, send_Body);
        }
        else if(recv_Body._code == MessageHeader::CHANGE_STATUS){
            cout << "Recv Change Status from " << recv_Body._uniqueUserID << "\n";
            send_Body[0] = lobbymanager_.changeStatus(recv_Body);
        }

        try{
            if(send_Body[0]._code != MessageHeader::GAME){
                if(send_Body[0]._code == MessageHeader::GAME_START){
                    if(!gamemanager_.waitPlayers(send_Body[0]))
                        send_Body[0]._code = MessageHeader::GAME;
                }
                boost::array<Body, 1> send_buffer_ = { send_Body[0] };
                cout << "Send " << int(send_Body[0]._code) << " to " << send_Body[0]._uniqueUserID << "\n";
                socket_.send_to(boost::asio::buffer(send_buffer_), remote_endpoint_);
            }
            else{
                cout << "Send " << int(send_Body[0]._code) << " to " << send_Body[0]._uniqueUserID << "\n";
                for(int i = 0; i < MAXPLAYERS; i++){
                    cout << "Send " << i << "\n";
                    printBody(send_Body[i]);
                }
                boost::array<Body, MAXPLAYERS> send_buffer_;
                for(int i = 0; i < MAXPLAYERS; i++)
                    send_buffer_[i] = send_Body[i];
                socket_.send_to(boost::asio::buffer(send_buffer_), remote_endpoint_);
            }
        }
        catch(std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }

        std::cout << "\nRestart_receive";
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