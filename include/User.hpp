/**
 *  include/User.hpp
 *      Login 한 User의 데이터
 *          Body, IP, Port
 * 
 *  Body getBody();
 *  boost::asio::ip::address getIP();
 *  short getPort();
 * 
 *  void setBody(Body _body);
 *  void setMessageHeader(MessageHeader _message);
 *  void setUniqueGameID(int _id);
 *  void setUniqueUserID(int _id);
*/
#ifndef User_HPP
#define User_HPP

#include <boost/asio/ip/address.hpp>

#include "Body.hpp"

class User{

private:
    Body                        _player_data;

public:
    User(Body player = Body())
        : _player_data(player) { }

    Body            getBody() { return _player_data; }
    char*           getID() { return _player_data._ID; }
    int             getUniqueUserID() { return _player_data._uniqueUserID; }
    int             getUniqueGameID() { return _player_data._uniqueGameID; }
    MessageHeader   getHeader() { return _player_data._code; }
    int             getCurHP() { return _player_data._curHP; }

    void            setBody(Body _body) { _player_data = _body; }
    void            setMessageHeader(MessageHeader _message) { _player_data._code = _message; }
    void            setUniqueGameID(int _id) { _player_data._uniqueGameID = _id; }
    void            setUniqueUserID(int _id) { _player_data._uniqueUserID = _id; }
    void            setPlayerNumber(int _num) { _player_data._playerNumber = _num; }
    void            setHPFull() { _player_data._curHP = _player_data._maxHP; }
    void            setPlayerStatus(char *status) { strcmp(_player_data._player_stat, status); }

    bool            operator==(User another){ return strcmp(this->getBody()._ID, another.getBody()._ID) == 0? true : false; }
};

#endif