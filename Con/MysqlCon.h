#pragma once
#ifndef MYSQLCON_H_
#define MYSQLCON_H_
#include<stdio.h>
#include<winsock.h>
#include"mysql.h"
#include<Windows.h>
#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "libmysql.lib")

extern MYSQL mysql; //mysql ����
extern MYSQL_FIELD *fd; // �ֶ�������
extern char field[32][32]; // ���ֶ�����ά����
extern MYSQL_RES *res; // �����е�һ����ѯ�����
extern MYSQL_ROW column; //һ�������ݵ����Ͱ�ȫ(type-safe)�ı�ʾ����ʾ�����е���  
//char query[150];

bool ConnectDB(char *service, char *USER, char *passwd, char *dbname, int port);
void FreeConnect();
MYSQL_RES* QueryDB(char* query);
bool DealData(char* query);
bool ChangeUserDB(char* user, char *passwd, char*dbname);
#endif

