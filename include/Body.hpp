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
    MessageHeader   _code;

    char            _ID[100];
    char            _PW[100];

    KEYBOARD        _keyboard;
    char             _player_stat[50];

    int             _uniqueGameID;
    int             _uniqueUserID;
    int             _playerNumber;

    int             _x;
    int             _y;

    int             _maxHP;
    int             _curHP;
};

#endif