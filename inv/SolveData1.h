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

class SolveData1
{

public:
	SolveData1() {}
	SolveData1(char *service, char *USER, char *passwd, char *dbname, int port)
	{
		_mc.ConnectDB(service, USER, passwd, dbname, port);
	}

	// �������ݿ�
	void ConnectMysql(char *service, char *USER, char *passwd, char *dbname, int port)
	{
		_mc.ConnectDB(service, USER, passwd, dbname, port);
	}

	~SolveData1() { }

	vector<List>  selFromInvtable(char* token);//�ӵ��ű�ȡ��token��item
	void GetData_Solve();//�����ݿ⽫update=1����ȡ�������ҽ�update��0������data
	int tableCount(char *table);// ���������ж����� /**********�ǵø�����***********/
	void SaveData(char* token, vector<List>& item);	//�������ݵ����ݿ�


													//protected:
public:
	vector<List> charToVector(char *p, int n);// ��char*���vector /****�ǵø�����******/

											  // ���л��������ݿ� ��/****�ǵø����ͣ���******/
	void inserthelp(const vector<List>& a1, char* token);
	void updatehelp(const vector<List>& a1, char* token);

	vector<List> Merge50(const vector<List> &a, const vector<List>& b);// �鲢�㷨���ҳ���ƵΪǰ50���Ĵ� /*******�ǵø�����********/
	int buffer(int ni, const int& count);	//ÿ��ȡ��һ��buffer�Ľ����,buffer��ni��ʼ��countΪ����ĳ���,����buffer������
	bool comparisonhelp(char*token);//�ȶ����֣�����God�������÷��ⶫ���÷��÷�
	void Comparison(char*token, const vector<List>&a);// �ȶ�
	void buildTo50(vector<List>&item);// ����±���vector����Ķ�������50������


private:
	MysqlCon _mc;
	MYSQL_RES *buffres;
	MYSQL_ROW buffcol;
};


#endif