#include"MysqlCon.h"
#include<iostream>
using namespace std;
MysqlCon::MysqlCon(char *service, char *USER, char *passwd, char *dbname, int port)
{
	ConnectDB(service, USER,passwd, dbname, port);
}
MysqlCon::~MysqlCon()
{
	FreeConnect();
}
bool MysqlCon::ConnectDB(char *host,char* USER, char* passwd, char* dbname, int port) //�������ݿ�
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

void MysqlCon::FreeConnect() //�ͷ����ݿ�
{
	mysql_free_result(res);
	mysql_close(&mysql);
}

//���ݿ����

MYSQL_RES* MysqlCon::QueryDB(char* query) //ִ�з�����䣬��ȡ�������ݷ���������
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

bool MysqlCon::DealData(char* query)  // ��������
{
	mysql_query(&mysql, "SET NAMES UTF8" );
	if ((mysql_query(&mysql, query)))
	{
		printf("Deal Failed:%s\n", mysql_error(&mysql));
		return false;
	}
	else return true;
}

bool MysqlCon::DealBinary(char * sql, unsigned int n) // ��������Ƶ�
{
	mysql_query(&mysql, "SET NAMES UTF8");
	if (mysql_real_query(&mysql, sql, n))
	{
		printf("Failed in dealing binary:%s\n", mysql_error(&mysql));
		return false;
	}
	return true;
}

bool MysqlCon::ChangeUserDB(char* user, char *passwd, char*dbname) // �ı��û������ݿ�
{
	if (mysql_change_user(&mysql, user, passwd, dbname))
	{
		printf("Failed to change user. Error:%s\n", mysql_error(&mysql));
		return false;
	}
	else
		return true;
}