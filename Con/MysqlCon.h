#pragma once
#ifndef MYSQLCON_H_
#define MYSQLCON_H_
#include<stdio.h>
#include<winsock.h>
#include"mysql.h"
#include<Windows.h>
#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "libmysql.lib")

extern MYSQL mysql; //mysql 连接
extern MYSQL_FIELD *fd; // 字段列数组
extern char field[32][32]; // 存字段名二维数组
extern MYSQL_RES *res; // 返回行的一个查询结果集
extern MYSQL_ROW column; //一个行数据的类型安全(type-safe)的表示，表示数据行的列  
//char query[150];

bool ConnectDB(char *service, char *USER, char *passwd, char *dbname, int port);
void FreeConnect();
MYSQL_RES* QueryDB(char* query);
bool DealData(char* query);
bool ChangeUserDB(char* user, char *passwd, char*dbname);
#endif

