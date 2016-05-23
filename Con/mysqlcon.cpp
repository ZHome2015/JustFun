#include"MysqlCon.h"
#include<iostream>
using namespace std;
MYSQL mysql; //mysql ����
MYSQL_FIELD *fd; // �ֶ�������
char field[32][32]; // ���ֶ�����ά����
MYSQL_RES *res; // �����е�һ����ѯ�����
MYSQL_ROW column; //һ�������ݵ����Ͱ�ȫ(type-safe)�ı�ʾ����ʾ�����е���  
bool ConnectDB(char *host,char* USER, char* passwd, char* dbname, int port) //�������ݿ�
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

void FreeConnect() //�ͷ����ݿ�
{
	mysql_free_result(res);
	mysql_close(&mysql);
}

//���ݿ����

MYSQL_RES* QueryDB(char* query) //ִ�з�����䣬��ȡ�������ݷ���������
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

bool DealData(char* query)  // ��������
{
	mysql_query(&mysql, "SET NAMES UTF8" );
	if ((mysql_query(&mysql, query)))
	{
		printf("Deal Failed:%s\n", mysql_error(&mysql));
		return false;
	}
	else return true;
}

bool ChangeUserDB(char* user, char *passwd, char*dbname) // �ı��û������ݿ�
{
	if (mysql_change_user(&mysql, user, passwd, dbname))
	{
		printf("Failed to change user. Error:%s\n", mysql_error(&mysql));
		return false;
	}
	else
		return true;
}