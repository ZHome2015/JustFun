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
	int docId;//�ĵ����
	int tokenFreq;//�ĵ�Ƶ��
	vector<int> pos;//�ĵ����ֵ�λ��	

	invertNode() {
		docId = 0;
		tokenFreq = 0;
		vector<int>pos(MAXPOSSIZE, 0);//����pos��ʼ��

	}
	invertNode(int _docId, int _tokenFreq, int _index) {
		//vector������  ͬΪvectorֱ�� = ����
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

	// �������ݿ�
	void ConnectMysql(char *service, char *USER, char *passwd, char *dbname, int port)
	{
		_mc.ConnectDB(service, USER, passwd, dbname, port);
	}

	~SolveData() { }

	vector<invertNode>  selFromInvtable(char* token);//�ӵ��ű�ȡ��token��item
	void GetData_Solve();//�����ݿ⽫update=1����ȡ�������ҽ�update��0������data
	int tableCount(char *table);// ���������ж�����
	void SaveData(char* token, vector<invertNode>& item);	//�������ݵ����ݿ�
	

//protected:
public:
	vector<invertNode> charToVector(char *p, int n);// ��char*���vector 

	// ���л��������ݿ� 
	void inserthelp(const vector<invertNode>& a1, char* token);
	void updatehelp(const vector<invertNode>& a1, char* token);

	vector<invertNode> Merge50(const vector<invertNode> &a, const vector<invertNode>& b);// �鲢�㷨���ҳ���ƵΪǰ50���Ĵ� 
	
	/***********************����Ȳ�������ʱû��****************************/
	//int buffer( int ni, const int& count);	//ÿ��ȡ��һ��buffer�Ľ����,buffer��ni��ʼ��countΪ����ĳ���,����buffer������
	//bool comparisonhelp(char*token);//�ȶ����֣�����God�������÷��ⶫ���÷��÷�
	/***********************����Ȳ�������ʱû��****************************/
	
	void Comparison(char*token, const vector<invertNode>&a);// �ȶ�,����
	void buildTo50(vector<invertNode>&item);// ����±���vector����Ķ�������50������docID = 0��tokenFreq = 0��index = 0������


private:
	MysqlCon _mc;
	MYSQL_RES *buffres;
	//MYSQL_ROW buffcol;
};


#endif