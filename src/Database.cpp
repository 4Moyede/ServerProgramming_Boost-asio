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
	default:
		break;
	}

	return resultBody;
}

// 동일한 ID, PW가 있는지 확인, 없을 경우 Sign Up
Body Database::registerUser(Body _player)
{
	char query[300];

	sprintf(query, "SELECT ID FROM \'%s\' WHERE ID = \'%s\';", table, _player._ID);
	runQuery(query);
	if(fetchRow() == SUCCESS){
		std::cout << "Register Fail...\n";
		_player._code = MessageHeader::REGISTER_FAIL;
	}
	else{
		sprintf(query, "INSERT INTO \'%s\'(ID, PASSWORD, player_stat) VALUES (\"%s\", \"%s\", \"Basic\");", table, _player._ID, _player._PW);
		runQuery(query);
		if(fetchRow()){
			std::cout << "Register Success!\n";
			strcpy(_player._player_stat, "Basic");
			_player._code = MessageHeader::REGISTER_SUCCESS;
		}
		else{
			std::cout << "Register Fail...\n";
			_player._code = MessageHeader::REGISTER_FAIL;
		}
	}

	return _player;
}

// ID, PW가 일치하는 User가 있는지 확인, 있을 경우 그 튜플에 있는 데이터 return
Body Database::loginUser(Body _player)
{
	char query[300];
	sprintf(query, "SELECT * FROM \'%s\' WHERE ID = \'%s\' AND PASSWORD = \'%s\';", table, _player._ID, _player._PW);
	runQuery(query);
	if(fetchRow() == SUCCESS){
		if(!row[4]){
			std::cout << "Login Success\n";
			strcpy(_player._player_stat, row[3]);
			_player._code = MessageHeader::LOGIN_SUCCESS;
			sprintf(query, "UPDATE \'%s\' SET LOGIN = true WHERE ID = \'%s\' AND PASSWORD = \'%s\';", table, _player._ID, _player._PW);
			runQuery(query);
		}
		else{
			std::cout << "Login Fail\n";
			_player._code = MessageHeader::LOGIN_FAIL;
		}
	}
	else{
		std::cout << "Login Fail\n";
		_player._code = MessageHeader::LOGIN_FAIL;
	}

	return _player;
}

// Parameter로 입력된 Data, Database에 Upload
Body Database::saveUser(Body _player)
{	
	char query[350];
	if(_player._code == MessageHeader::CHANGE_STATUS)
		sprintf(query, "UPDATE \'%s\' SET player_stat = \"%s\" WHERE ID = \"%s\" AND PASSWORD = \"%s\";", table, _player._player_stat,_player._ID, _player._PW);
	else if(_player._code == MessageHeader::LOGOUT_REQUEST)
		sprintf(query, "UPDATE \'%s\' SET player_stat = \"%s\" AND LOGIN = false WHERE ID = \"%s\" AND PASSWORD = \"%s\";", table, _player._player_stat,_player._ID, _player._PW);
	runQuery(query);
	
	if(fetchRow()){
		std::cout << "Change Success!\n";
		_player._code = MessageHeader::CHANGE_SUCCESS;
	}
	else{
		std::cout << "Change Failed...\n";
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
	return fetchRow();
}

// 로우 조회
int Database::fetchRow(void)
{
	if (res)
	{
		row = mysql_fetch_row(res);
		if (!row) // MySQL Fetch failed
			return FAIL;
		else
			return SUCCESS;
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