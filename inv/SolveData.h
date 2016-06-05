#pragma once
#ifndef SOLVEDATA_H_
#define SOLVEDATA_H_
#include"MysqlCon.h"
#include<cstring>
#include <stdlib.h>
#include<iostream>
#include<vector>
#include<string>
using namespace std;

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
 
class SolveData
{

public:
	SolveData(){}
	SolveData(char *service, char *USER, char *passwd, char *dbname, int port)
	{
		_mc.ConnectDB(service, USER, passwd, dbname, port);
	}

	// 连接数据库
	void ConnectMysql(char *service, char *USER, char *passwd, char *dbname, int port)
	{
		_mc.ConnectDB(service, USER, passwd, dbname, port);
	}

	~SolveData() { }

	vector<invertNode>  selFromInvtable(char* token);//从倒排表取出token的item
	void GetData_Solve();//从数据库将update=1数据取出，并且将update置0，处理data
	int tableCount(char *table);// 数表里面有多少行
	void SaveData(char* token, vector<invertNode>& item);	//保存数据到数据库
	

//protected:
public:
	vector<invertNode> charToVector(char *p, int n);// 把char*变回vector 

	// 序列化存入数据库 
	void inserthelp(const vector<invertNode>& a1, char* token);
	void updatehelp(const vector<invertNode>& a1, char* token);

	vector<invertNode> Merge50(const vector<invertNode> &a, const vector<invertNode>& b);// 归并算法，找出词频为前50个的词 
	
	/***********************这个先不管它暂时没用****************************/
	//int buffer( int ni, const int& count);	//每次取出一个buffer的结果集,buffer从ni开始，count为表里的长度,返回buffer到哪里
	//bool comparisonhelp(char*token);//比对助手！！！God！！！好烦这东西好烦好烦
	/***********************这个先不管它暂时没用****************************/
	
	void Comparison(char*token, const vector<invertNode>&a);// 比对,更新
	void buildTo50(vector<invertNode>&item);// 如果新保存vector里面的东西不满50个，则（docID = 0，tokenFreq = 0，index = 0）填满


private:
	MysqlCon _mc;
	MYSQL_RES *buffres;
	//MYSQL_ROW buffcol;
};


#endif