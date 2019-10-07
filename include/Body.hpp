/**
 *  include/Body.hpp
 *      Player의 데이터를 가지고 있는 struct
 *      Body structure로 네트워크 송수신에 이용되는 buffer 구성
*/
#ifndef Body_HPP
#define Body_HPP

#include "const.hpp"

struct Body
{
    MessageHeader   _code = MessageHeader::NONE;

    char            _ID[100];
    char            _PW[100];

    KEYBOARD        _keyboard = KEYBOARD::NONE;
    char             _player_stat[50] = "None";

    int             _uniqueGameID = -1;
    int             _uniqueUserID = -1;
    int             _playerNumber = -1;

    int             _x = 0;
    int             _y = 0;

    int             _maxHP = 100;
    int             _curHP = 0;
};

#endif