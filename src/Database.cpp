#include "../include/Database.hpp"

int Database::numinstantiated = 0;

Body Database::use(Body _user)
{
	Body resultBody;
	switch (_user._code)
	{
	case MessageHeader::LOGIN_REQUEST:
		resultBody = loginUser(_user);
		break;
	case MessageHeader::REGISTER_USERID:
		resultBody = registerUser(_user);
		break;
	case MessageHeader::CHANGE_STATUS:
		resultBody = saveUser(_user);
	case MessageHeader::LOGOUT_REQUEST:
		resultBody = logout(_user);
	default:
		break;
	}

	return resultBody;
}

// 동일한 ID, PW가 있는지 확인, 없을 경우 Sign Up
Body Database::registerUser(Body _player)
{
	char query[300];

	sprintf(query, "SELECT ID FROM %s WHERE ID = \'%s\';", table, _player._ID);
	runQuery(query);
	if(fetchRow() == SUCCESS){
		std::cout << "Register Fail : ID is already Exist\n";
		_player._code = MessageHeader::REGISTER_FAIL;
	}
	else{
		sprintf(query, "INSERT INTO %s (ID, PASSWORD, player_stat) VALUES (\"%s\", \"%s\", \"Basic\");", table, _player._ID, _player._PW);
		if(runQuery(query) == SUCCESS){
			std::cout << "Register Success!\n";
			strcpy(_player._player_stat, "Basic");
			_player._code = MessageHeader::REGISTER_SUCCESS;
		}
		else{
			std::cout << "Register Fail : Database Error\n";
			_player._code = MessageHeader::REGISTER_FAIL;
		}
	}

	return _player;
}

// ID, PW가 일치하는 User가 있는지 확인, 있을 경우 그 튜플에 있는 데이터 return
Body Database::loginUser(Body _player)
{
	char query[300];
	sprintf(query, "SELECT * FROM %s WHERE ID = \'%s\' AND PASSWORD = \'%s\';", table, _player._ID, _player._PW);
	runQuery(query);
	if(fetchRow() == SUCCESS){
		if(!strcmp(row[4], "0")){
			strcpy(_player._player_stat, row[3]);
			sprintf(query, "UPDATE %s SET LOGIN = 1 WHERE ID = \'%s\' AND PASSWORD = \'%s\';", table, _player._ID, _player._PW);
			if(runQuery(query) == SUCCESS){
				std::cout << "Login Success\n";
				_player._code = MessageHeader::LOGIN_SUCCESS;
			}
		}
		else{
			std::cout << "Login Fail: Already Login\n";
			_player._code = MessageHeader::LOGIN_FAIL;
		}
	}
	else{
		std::cout << "Login Fail: check ID, PW\n";
		_player._code = MessageHeader::LOGIN_FAIL;
	}

	return _player;
}

// Parameter로 입력된 Data, Database에 Upload
Body Database::saveUser(Body _player)
{	
	char query[350];
	sprintf(query, "UPDATE %s SET player_stat = \'%s\' WHERE ID = \'%s\' AND PASSWORD = \'%s\';", table, _player._player_stat,_player._ID, _player._PW);

	if(runQuery(query) == SUCCESS){
		std::cout << "Change Success!\n";
		_player._code = MessageHeader::CHANGE_SUCCESS;
	}
	else{
		std::cout << "Change Failed...\n";
		_player._code = MessageHeader::CHANGE_FAIL;
	}

	return _player;
}

Body Database::logout(Body _player)
{
	char query[350];
	sprintf(query, "UPDATE %s SET player_stat = \'%s\', LOGIN = 0 WHERE ID = \'%s\' AND PASSWORD = \'%s\';", table, _player._player_stat,_player._ID, _player._PW);

	if(runQuery(query) == SUCCESS){
		std::cout << "Log Out Success!\n";
		_player._code = MessageHeader::CHANGE_SUCCESS;
	}
	else{
		std::cout << "Log Out fail...\n";
		_player._code = MessageHeader::CHANGE_FAIL;
	}

	return _player;
}

// 쿼리 실행
int Database::runQuery(char *query)
{
	mysql_free_result(res);
	if (mysql_query(conn, query))
	{
		// MySQL Query Excute failed
		return FAIL;
	}

	res = mysql_store_result(conn);
	return SUCCESS;
}

// 로우 조회
int Database::fetchRow(void)
{
	if (res)
	{
		row = mysql_fetch_row(res);
		if (!row){ // MySQL Fetch failed
			return FAIL;
		}
		else{
			return SUCCESS;
		}
	}
	// MySQL Query Result Null
	return FAIL;
}

// 디비 연결
int Database::connectDB(void) 
{
	mysql_init(&mysql);
	conn = mysql_real_connect(&mysql, server, user, password, database, 3306, (char *)NULL, 0);

	if (!conn)// MySQL connect fail
		return FAIL;
	else
		return SUCCESS;
}

// 디비 연결 해제
void Database::closeDB(void)
{
	if (res)
		mysql_free_result(res);
	mysql_close(conn);
}