/**
 *  include/Database.hpp
 *      Database와 연결
 * 
 *   void registerUser(char* _ID, char* _PW);
 *   void loginUser(char *_ID, char* _PW);
 *   void saveUser(Body _player);
 *   Body getResult();
*/
#ifndef Database_HPP
#define Database_HPP

#include <mysql/mysql.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <assert.h>
#include <string.h>
using namespace std;

#include "const.hpp"
#include "Body.hpp"

#define SUCCESS     0
#define FAIL        -1

class Database
{
public:
    Database()
    {
        assert(numinstantiated < 1);
        numinstantiated++;

        if (connectDB() != SUCCESS)
          cout << mysql_error(&mysql) << endl;

        resultClear();
    }

    ~Database()
    {
        closeDB();
    }   

    int connectDB(void);

    void registerUser(char* _ID, char* _PW);
    void loginUser(char *_ID, char* _PW);
    void saveUser(Body _player);
    
    Body getResult() { return resultBody; }

private:
    MYSQL_RES   *res;           //쿼리문에 대한 result값을 받는 위치변수
    MYSQL_ROW   row;            //쿼리문에 대한 실제 데이터값이 들어있는 변수
    MYSQL       *conn, mysql;   //mysql과의 커넥션을 잡는데 지속적으로 사용되는 변수 

    static int  numinstantiated;

    Body        resultBody;
    void        resultClear();

    int runQuery(char *query);  // query문 실행
    int fetchRow(void);         // 결과값, 변수 row에 저장
    void closeDB(void);
    
};

#endif