# Server Programming

## Structure

![structure](./img/structure.png)

+ __NetworkServer__ : Client와의 UDP 동기화 통신을 담당. Receive된 Body의 MessageHeader를 확인한다.
+ __LobbyManager__ : 현재 Login한 User들을 관리.
+ __GameManager__ : 현재 진행되고 있는 게임의 방을 관리.
+ __Database__ : MySQL Server와의 연동을 담당.

## Libraries

### Boost

![boost](./img/boost.png)

[Boost](https://www.boost.org/) provides free peer-reviewed portable C++ source libraries.

We emphasize libraries that work well with the C++ Standard Library. Boost libraries are intended to be widely useful, and usable across a broad spectrum of applications. The Boost license encourages both commercial and non-commercial use.

We aim to establish "existing practice" and provide reference implementations so that Boost libraries are suitable for eventual standardization. Ten Boost libraries are included in the C++ Standards Committee's Library Technical Report (TR1) and in the new C++11 Standard. C++11 also includes several more Boost libraries in addition to those from TR1. More Boost libraries are proposed for standardization in C++17.

통신에 패킷에 포함 될 Body에는 **MessageHeader**가 있다. Server의 NetworkListener는 MessageHeader로 Client의 요청을 구분하여 그 요청을 처리할 수 있는 클래스로 패킷을 전달한다.

```c++
enum class MessageHeader
{
    // Sign in, to LobbyManager
    LOGIN_REQUEST       = 1,
    LOGIN_FAIL          = 2,

    // Sign up, to LobbyManager
    REGISTER_USERID     = 3,
    REGISTER_FAIL       = 4,

    // Change Character, to LobbyManager
    CHANGE_STATUS       = 5,

    // Game, to GameManager
    READY               = 6,
    GAME_START          = 7,
    GAME                = 8,
    GAME_END            = 9,
};
```

![flowchart](./img/flowchart.png)

### MySQL

![mysql](./img/mysql.png)

The [MySQL™ software](https://dev.mysql.com/) delivers a very fast, multithreaded, multi-user, and robust SQL (Structured Query Language) database server. MySQL Server is intended for mission-critical, heavy-load production systems as well as for embedding into mass-deployed software. Oracle is a registered trademark of Oracle Corporation and/or its affiliates. MySQL is a trademark of Oracle Corporation and/or its affiliates, and shall not be used by Customer without Oracle's express written authorization. Other names may be trademarks of their respective owners.

The MySQL software is Dual Licensed. Users can choose to use the MySQL software as an Open Source product under the terms of [the GNU General Public License](http://www.fsf.org/licenses/) or can purchase a standard commercial license from Oracle. See [MySQL License Page](http://www.mysql.com/company/legal/licensing/) for more information on our licensing policies.

유저의 데이터를 저장할 Database는 MySQL로 생성. Body Structure와 동기화가 되도록 하여야하며 테이블은 다음과 같다.

![database](./img/dbSet.png)

## Execute

```shell
$./bin/main
```
