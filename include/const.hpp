/**
 *  include/const.hpp
 *      서버에 사용하는 const variable
*/
#ifndef Consts_HPP
#define Consts_HPP

#include <arpa/inet.h>

const static uint16_t SHARED_MEMORY_KEY		= 1234;

const static uint16_t PORT					= 7232;
const static uint16_t MAXUSERS				= 100;
const static uint16_t MAXPLAYERS			= 2;
const static uint16_t MAXGAMES				= 10;

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
	READY_FAIL			= 11,
	GAME_START			= 12,
	GAME 				= 13,

	RANK_ONE			= 14,
	RANK_TWO			= 15,
	RANK_THREE			= 16,
	RANK_FOUR			= 17,
	RANK_FIVE			= 18,
	RANK_SIX			= 19
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