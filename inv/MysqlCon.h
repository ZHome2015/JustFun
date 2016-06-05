#pragma once
#ifndef MYSQLCON_H_
#define MYSQLCON_H_
#include<stdio.h>
#include<winsock.h>
#include"mysql.h"
#include<Windows.h>
#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "libmysql.lib")

class MysqlCon
{
public:
	MYSQL mysql; //mysql ����
	MYSQL_FIELD *fd; // �ֶ�������
	char field[32][32]; // ���ֶ�����ά����
	MYSQL_RES *res; // �����е�һ����ѯ�����
	MYSQL_ROW column; //һ�������ݵ����Ͱ�ȫ(type-safe)�ı�ʾ����ʾ�����е���  
//char query[150];
	MysqlCon() {}
	MysqlCon(char *service, char *USER, char *passwd, char *dbname, int port);
	~MysqlCon();
	bool ConnectDB(char *service, char *USER, char *passwd, char *dbname, int port);//�������ݿ�
	void FreeConnect();//�ͷ����ݿ�
	MYSQL_RES* QueryDB(char* query);//ִ�з�����䣬��ȡ�������ݷ���������
	bool DealData(char* query); // ��������
	bool ChangeUserDB(char* user, char *passwd, char*dbname);// �ı��û������ݿ�
	bool DealBinary(char * sql, unsigned int n); // ��������Ƶ�
};



#endif

