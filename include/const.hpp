/**
 *  include/const.hpp
 *      서버에 사용하는 const variable
*/
#ifndef Consts_HPP
#define Consts_HPP

#include <arpa/inet.h>

const static uint16_t PORT                 = 7232;
const static uint16_t MAXUSERS             = 100;

enum class MessageHeader : uint16_t
{ 
    NONE                = 0,
    
	LOGIN_REQUEST       = 1,
	LOGIN_SUCCESS		= 2,
    LOGIN_FAIL          = 3,
    
	REGISTER_USERID     = 4,
	REGISTER_SUCCESS	= 5,
    REGISTER_FAIL       = 6,

    CHANGE_STATUS       = 7,
	CHANGE_SUCCESS		= 8,
	CHANGE_FAIL			= 9,

    READY               = 10,
	GAME_START			= 11,
	GAME 				= 12,

	RANK_ONE			= 13,
	RANK_TWO			= 14,
	RANK_THREE			= 15,
	RANK_FOUR			= 16,
	RANK_FIVE			= 17,
	RANK_SIX			= 18
};

enum class KEYBOARD : uint16_t
{
	NONE 				= 0,
	KEY_ATTACK 			= 'X',
	KEY_SKILL1 			= 'A',
	KEY_SKILL2 			= 'S',
	KEY_SKILL3 			= 'D',
	KEY_JUMP 			= 0x20, // VK_SPACE
	KEY_DASH 			= 'C',
	KEY_RETURN 			= 'Z', // not use... maybe
	KEY_MENU 			= 0x1B, // not use... maybe
	KEY_OBJECT_USE 		= 0x26 // VK_UP
};

#endif