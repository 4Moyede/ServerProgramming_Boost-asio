#include "../include/Database.hpp"

int Database::numinstantiated = 0;

// 동일한 ID, PW가 있는지 확인, 없을 경우 Sign Up
void Database::registerUser(char* _ID, char* _PW)
{
	char query[100];
	strcpy(resultBody._ID, _ID);
	strcpy(resultBody._PW, _PW);

	sprintf(query, "SELECT ID, PASSWORD FROM player_Data WHERE ID = \'%s\' AND PASSWORD = \'%s\';", _ID, _PW);
	runQuery(query);
	if(fetchRow() == SUCCESS){
		cout << "Register Fail...\n";
		strcpy(resultBody._player_stat, "None");
		resultBody._code = MessageHeader::REGISTER_FAIL;
	}
	else{
		mysql_free_result(res);
		sprintf(query, "INSERT INTO player_Data(ID, PASSWORD, player_stat) VALUES (\"%s\", \"%s\", \"Basic\");", _ID, _PW);
		if(!mysql_query(conn, query)){
			cout << "Register Success!\n";
			strcpy(resultBody._player_stat, "Basic");
			resultBody._code = MessageHeader::REGISTER_USERID;
		}
	}
}

// ID, PW가 일치하는 User가 있는지 확인, 있을 경우 그 튜플에 있는 데이터 return
void Database::loginUser(char *_ID, char* _PW)
{
	char query[100];

	sprintf(query, "SELECT * FROM player_Data WHERE ID = \'%s\' AND PASSWORD = \'%s\';", _ID, _PW);
	runQuery(query);
	if(fetchRow() == SUCCESS)
		cout << "Login Success\n";
	else{
		cout << "Login Fail\n";
		strcpy(resultBody._ID, _ID);
		strcpy(resultBody._PW, _PW);
		strcpy(resultBody._player_stat, "None");
		resultBody._code = MessageHeader::LOGIN_FAIL;
	}
}

// Parameter로 입력된 Data, Database에 Upload
void Database::saveUser(Body _player)
{	
	char query[350];
	
	sprintf(query, "UPDATE player_Data SET player_stat = \"%s\" WHERE ID = \"%s\" AND PASSWORD = \"%s\";", _player._player_stat,_player._ID, _player._PW);
	mysql_free_result(res);
	if(!mysql_query(conn, query))
		cout << "Register Success!\n";
}

// resultBody 초기화
void Database::resultClear(){
	resultBody = Body();
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
		if (!row)
		{
			// MySQL Fetch failed
			return FAIL;
		}
		else
		{
			if(resultBody._code == MessageHeader::REGISTER_USERID)
				return SUCCESS;
			
			resultBody._code = MessageHeader::LOGIN_REQUEST;
			strcpy(resultBody._ID, row[1]);
			strcpy(resultBody._PW, row[2]);
			strcpy(resultBody._player_stat, row[3]);
			return SUCCESS;
		}
	}
	// MySQL Query Result Null
	return FAIL;
}

// 디비 연결
int Database::connectDB(void) 
{
	char *server = "127.0.0.1";
	char *user = "GM";
	char *password = "gameMaster1!";
	char *database = "Game_Players";

	mysql_init(&mysql);
	conn = mysql_real_connect(&mysql, server, user, password, database, 3306, (char *)NULL, 0);
	if (!conn)
	{
		// MySQL connect fail
		return FAIL;
	}
	return SUCCESS;
}

// 디비 연결 해제
void Database::closeDB(void)
{
	if (res)
		mysql_free_result(res);
	mysql_close(conn);
}