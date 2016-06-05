#include"MysqlCon.h"
#include"SolveData.h"
#include<cstring>
#include <stdlib.h>
#include<iostream>
#include<vector>
using namespace std;

//�����ݿ⽫update=1����ȡ�������ҽ�update��0������data
void SolveData:: GetData_Solve()
{

	char * query = "select pageID,text from tbname where update_ = 1";  // ȡ��update_Ϊ1������
	mysql_free_result(_mc.res);
	_mc.res = _mc.QueryDB(query);
	while (_mc.column = mysql_fetch_row(_mc.res))
	{
		//�ܻ�����,
		/*_mc.column[0] �� pageID
		_mc.column[1] ��text */
	}
	query = "update tbname set update_ =  0 where update_ = 1";  //ȡ������ֱ������
	_mc.DealData(query);
}



// ��char*���vector 
vector<invertNode> SolveData::charToVector(char *p, int n)
{
	invertNode *temp = (invertNode*)p;
	vector<invertNode> q(temp, temp + n);
	return q;
}

// ���л��������ݿ� 
void SolveData::inserthelp( const vector<invertNode>& a1, char* token)
{
	//mysql_free_result(_mc.res);
	char sql[300], *end;
	sprintf_s(sql, 300, "insert into invtable(token, item) values ('%s',", token);  /********Ҫ�ı�����******/
	end = sql + strlen(sql);
	*end++ = '\'';
	end += mysql_real_escape_string(&_mc.mysql, end, (char*)&a1[0], sizeof(a1));
	*end++ = '\'';
	*end++ = ')';
	_mc.DealBinary(sql, (unsigned int)(end - sql));
}

void SolveData::updatehelp(const vector<invertNode>& a1, char* token)
{
	//mysql_free_result(_mc.res);
	char sql[300] = "update invtable set item = '";
	char * end;
	end = sql + strlen(sql);
	end += mysql_real_escape_string(&_mc.mysql, end, (char*)&a1[0], sizeof(a1));
	*end++ = '\'';
	char * p = " where token = '";
	strcat_s(sql, strlen(sql) + strlen(p) + 1, p);
	strcat_s(sql, strlen(sql) + strlen(token) + 1, token);
	end = sql + strlen(sql);
	*end++ = '\'';
	_mc.DealBinary(sql, (unsigned int)(end - sql));
}


// �鲢�㷨���ҳ���ƵΪǰ50���Ĵ� /*******�ǵø�����********/
vector<invertNode> SolveData::Merge50(const vector<invertNode> &a, const vector<invertNode>& b)
{
	vector<invertNode> result;
	result.resize(50);
	vector<invertNode>::iterator ri;
	vector<invertNode>::const_iterator ai, bi;
	for (ai = a.begin(), bi = b.begin(), ri = result.begin(); ri != result.end(); ri++)
	{
		if (ai == a.end() && bi == b.end()) break;
		else if (ai == a.end())
		{
			(*ri) = (*bi);
			bi++;
		}
		else if (bi == b.end())
		{
			(*ri) = (*ai);
			ai++;
		}
		else if ((*ai).tokenFreq > (*bi).tokenFreq) /*�ǵø����ͣ�������*/
		{
			(*ri) = (*ai);
			ai++;
		}
		else if ((*ai).tokenFreq == (*bi).tokenFreq)
		{
			if ((*ai).docId == (*bi).docId)
			{
				(*ri) = (*bi);
				ai++;
				bi++;
			}
			else
			{
				(*ri) = (*bi);
				ri++;
				(*ri) = (*ai);
				ai++;
				bi++;
			}
		}
		else
		{
			(*ri) = (*bi);
			bi++;
		}
	}
	return result;
}

// ���������ж����� /**********�ǵø�����***********/
int SolveData::tableCount( char *table)
{
	//mysql_free_result(_mc.res);
	char *sql = "select count(0) from ";
	size_t len = strlen(sql) + strlen(table) + 1;
	char* query = (char*)malloc(len);
	sprintf_s(query, len, "%s%s", sql, table);
	_mc.res = _mc.QueryDB(query);
	_mc.column = mysql_fetch_row(_mc.res);
	int count = atoi(_mc.column[0]);
	return count;
}


/***********************����Ȳ�������ʱû��****************************/
////ÿ��ȡ��һ��buffer�Ľ����,buffer��ni��ʼ��countΪ����ĳ���,���� buffer������
//int SolveData::buffer(int ni, const int& count)
//{
//	char query[85];
//	const int n = 50;// �ǵø�
//	ni += n;
//	if (ni > count)
//		ni = count;
//	//sprintf_s(query, 85 ,"select token from invtable where tokenID between %d and %d", ni - n, ni);  //�ǵø�
//	sprintf_s(query, 85, "select token from invtable where tokenID between %d and %d", ni - n, ni);  //�ǵø�
//	buffres = _mc.QueryDB(query);
//	return ni;
//}
//
////�ȶ����֣�����God�������÷��ⶫ���÷��÷�
//bool SolveData::comparisonhelp(char*token)
//{
//	while (buffcol = mysql_fetch_row(buffres))
//		if (strcmp(buffcol[0], token) == 0)
//			return true;
//	return false;
//
//}
/***********************����Ȳ�������ʱû��****************************/

// �ȶ�
void SolveData::Comparison(char*token, const vector<invertNode>&a)
{
	char * sql = "select item from invtable where token = '";
	size_t len = strlen(sql) + strlen(token) + 2;
	char* query = (char*)malloc(len);
	sprintf_s(query, len, "%s%s'", sql, token);
//	mysql_free_result(_mc.res);
	_mc.res = _mc.QueryDB(query);
	_mc.column = mysql_fetch_row(_mc.res);
	char *p = _mc.column[0];
	const int n = 50; //����
	vector<invertNode> temp =	Merge50(charToVector(p, n), a);
	updatehelp(temp, token);
}

// ����±���vector����Ķ�������50����������
void SolveData::buildTo50(vector<invertNode>&item)
{
	//if (item.size() >= 50) return;
	if (item.size() >= 10) return;
	invertNode temp(0, 0, 0);
	//for (int i = item.size(); i <= 50; i++)
	for (int i = item.size(); i <= 10; i++)
		item.push_back(temp);
}

void SolveData::SaveData(char* token, vector<invertNode>& item)
{
	char query[85];
	//sprintf_s(query, 85 ,"select token from invtable where tokenID between %d and %d", ni - n, ni);  //�ǵø�
	sprintf_s(query, 85, "select item from invtable where token = '%s'",token);  
	buffres = _mc.QueryDB(query);
	if (mysql_affected_rows(&_mc.mysql) == 0)
	{
		buildTo50(item);
		inserthelp(item, token);
	}
	else
	{
		Comparison(token, item);
	}
	
}


vector<invertNode> SolveData::selFromInvtable(char* token)//�ӵ��ű�ȡ��token��item
{
	char* sql = "select item from invtable where token = '";  //�ǵø�
	size_t len = strlen(sql) + strlen(token) + 2;
	char* query = (char*)malloc(len);
	sprintf_s(query, len, "%s%s'", sql, token);
	mysql_free_result(_mc.res);
	_mc.res = _mc.QueryDB(query);
	_mc.column = mysql_fetch_row(_mc.res);
	char *p = _mc.column[0];
	const int n = 50; //����
	return charToVector(p, n);
}
