#include"MysqlCon.h"
#include<iostream>
using namespace std;
MYSQL mysql; //mysql 连接
MYSQL_FIELD *fd; // 字段列数组
char field[32][32]; // 存字段名二维数组
MYSQL_RES *res; // 返回行的一个查询结果集
MYSQL_ROW column; //一个行数据的类型安全(type-safe)的表示，表示数据行的列  
bool ConnectDB(char *host,char* USER, char* passwd, char* dbname, int port) //连接数据库
{
	mysql_init(&mysql);
	if (!(mysql_real_connect(&mysql, host, USER, passwd, dbname, port, 0, NULL)))
	{
		printf("Error Connecting to Database:%s\n", mysql_error(&mysql));
		return false;
	}
	else
	{
		printf("Connecting...");
		return true;
	}
}

void FreeConnect() //释放数据库
{
	mysql_free_result(res);
	mysql_close(&mysql);
}

//数据库操作

MYSQL_RES* QueryDB(char* query) //执行访问语句，将取出的数据放入结果集中
{
	mysql_query(&mysql, "SET NAMES UTF8");
	if (mysql_query(&mysql, query))
	{
		printf("Query Failed:%s\n", mysql_error(&mysql));
		return NULL;
	}
	else
	{
		if (!(res = mysql_store_result(&mysql)))
		{
			printf("Couldn't get result:%s", mysql_error(&mysql));
			return false;
		}
		else
		{
			return res;
		}
	}
	return NULL;
}

bool DealData(char* query)  // 处理数据
{
	mysql_query(&mysql, "SET NAMES UTF8" );
	if ((mysql_query(&mysql, query)))
	{
		printf("Deal Failed:%s\n", mysql_error(&mysql));
		return false;
	}
	else return true;
}

bool ChangeUserDB(char* user, char *passwd, char*dbname) // 改变用户和数据库
{
	if (mysql_change_user(&mysql, user, passwd, dbname))
	{
		printf("Failed to change user. Error:%s\n", mysql_error(&mysql));
		return false;
	}
	else
		return true;
}