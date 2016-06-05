#pragma once
#ifndef SOLVEDATA1_H_
#define SOLVEDATA1_H_
#include"MysqlCon.h"
#include<cstring>
#include <stdlib.h>
#include<iostream>
#include<vector>
#include<string>
using namespace std;
struct List
{
	int a;
};
const int MAXPOSSIZE = 10;
class invertNode {
public:
	int docId;//文档编号
	int tokenFreq;//文档频率
	vector<int> pos;//文档出现的位置	

	invertNode() {
		docId = 0;
		tokenFreq = 0;
		vector<int>pos(MAXPOSSIZE, 0);//对于pos初始化

	}
	invertNode(int _docId, int _tokenFreq, int _index) {
		//vector做参数  同为vector直接 = 即可
		docId = _docId;
		tokenFreq = _tokenFreq;
		pos.push_back(_index);

	}

	void tokenToNode(int docId, vector<string> str);
};

class SolveData1
{

public:
	SolveData1() {}
	SolveData1(char *service, char *USER, char *passwd, char *dbname, int port)
	{
		_mc.ConnectDB(service, USER, passwd, dbname, port);
	}

	// 连接数据库
	void ConnectMysql(char *service, char *USER, char *passwd, char *dbname, int port)
	{
		_mc.ConnectDB(service, USER, passwd, dbname, port);
	}

	~SolveData1() { }

	vector<List>  selFromInvtable(char* token);//从倒排表取出token的item
	void GetData_Solve();//从数据库将update=1数据取出，并且将update置0，处理data
	int tableCount(char *table);// 数表里面有多少行 /**********记得改类型***********/
	void SaveData(char* token, vector<List>& item);	//保存数据到数据库


													//protected:
public:
	vector<List> charToVector(char *p, int n);// 把char*变回vector /****记得改类型******/

											  // 序列化存入数据库 ，/****记得改类型！！******/
	void inserthelp(const vector<List>& a1, char* token);
	void updatehelp(const vector<List>& a1, char* token);

	vector<List> Merge50(const vector<List> &a, const vector<List>& b);// 归并算法，找出词频为前50个的词 /*******记得改类型********/
	int buffer(int ni, const int& count);	//每次取出一个buffer的结果集,buffer从ni开始，count为表里的长度,返回buffer到哪里
	bool comparisonhelp(char*token);//比对助手！！！God！！！好烦这东西好烦好烦
	void Comparison(char*token, const vector<List>&a);// 比对
	void buildTo50(vector<List>&item);// 如果新保存vector里面的东西不满50个，则


private:
	MysqlCon _mc;
	MYSQL_RES *buffres;
	MYSQL_ROW buffcol;
};


#endif