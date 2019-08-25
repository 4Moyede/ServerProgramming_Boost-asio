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
    LOGIN_FAIL          = 2,
    
	REGISTER_USERID     = 3,
    REGISTER_FAIL       = 4,

    CHANGE_STATUS       = 5,

    READY               = 6,
	GAME_START			= 7,
	GAME 				= 8,
	GAME_END	        = 9,

	RANK_ONE			= 10,
	RANK_TWO			= 11,
	RANK_THREE			= 12,
	RANK_FOUR			= 13,
	RANK_FIVE			= 14,
	RANK_SIX			= 15
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