#include"MysqlCon.h"
#include"SolveData1.h"
#include<cstring>
#include <stdlib.h>
#include<iostream>
#include<vector>
using namespace std;

//从数据库将update=1数据取出，并且将update置0，处理data
void SolveData1::GetData_Solve()
{

	char * query = "select pageID,text from tbname where update_ = 1";  // 取出update_为1的数据
	mysql_free_result(_mc.res);
	_mc.res = _mc.QueryDB(query);
	//printf("number of dataline returned: %Id\n", mysql_affected_rows(&_mc.mysql));
	//for (int i = 0; _mc.fd = mysql_fetch_field(_mc.res); i++)
	//	strcpy_s(_mc.field[i], _mc.fd->name);  // 获取字段名字
	//int row = mysql_num_fields(_mc.res); // 获取列数
	//for (int i = 0; i < row; i++)   // 打印字段名
	//	printf("%10s\t", _mc.field[i]);
	//printf("\n");
	//while (_mc.column = mysql_fetch_row(_mc.res)) //打印
	//{
	//	for (int i = 0; i < row; i++)
	//		printf("%s\t", _mc.column[i]);
	//	printf("\n");
	//}
	while (_mc.column = mysql_fetch_row(_mc.res))
	{
		//杰华调用,
		/*_mc.column[0] 是 pageID
		_mc.column[1] 是text */
	}
	query = "update tbname set update_ =  0 where update_ = 1";  //取完数据直接置零
	_mc.DealData(query);
}



// 把char*变回vector /****记得改类型******/
vector<List> SolveData1::charToVector(char *p, int n)
{
	List *temp = (List*)p;
	vector<List> q(temp, temp + n);
	return q;
}

// 序列化存入数据库 ，/****记得改类型！！******/
void SolveData1::inserthelp(const vector<List>& a1, char* token)
{
	//mysql_free_result(_mc.res);
	char sql[300], *end;
	sprintf_s(sql, 300, "insert into t2(token, item) values ('%s',", token);  /********要改表名。******/
	end = sql + strlen(sql);
	*end++ = '\'';
	end += mysql_real_escape_string(&_mc.mysql, end, (char*)&a1[0], sizeof(a1));
	*end++ = '\'';
	*end++ = ')';
	_mc.DealBinary(sql, (unsigned int)(end - sql));
}

void SolveData1::updatehelp(const vector<List>& a1, char* token)
{
	//mysql_free_result(_mc.res);
	char sql[300] = "update t2 set item = '";
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


// 归并算法，找出词频为前50个的词 /*******记得改类型********/
vector<List> SolveData1::Merge50(const vector<List> &a, const vector<List>& b)
{
	vector<List> result;
	//result.resize(50);
	result.resize(7);
	vector<List>::iterator ri;
	vector<List>::const_iterator ai, bi;
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
		else if ((*ai).a > (*bi).a) /*记得改类型！！！！*/
		{
			(*ri) = (*ai);
			ai++;
		}
		else if ((*ai).a == (*bi).a)
		{
			(*ri) = (*bi);
			ai++;
			bi++;
		}
		else
		{
			(*ri) = (*bi);
			bi++;
		}
	}
	return result;
}

// 数表里面有多少行 /**********记得改类型***********/
int SolveData1::tableCount(char *table)
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

//每次取出一个buffer的结果集,buffer从ni开始，count为表里的长度,返回 buffer到哪里
int SolveData1::buffer(int ni, const int& count)
{
	char query[85];
	const int n = 7;// 记得改
	ni += n;
	if (ni > count)
		ni = count;
	//sprintf_s(query, 85 ,"select token from invtable where tokenID between %d and %d", ni - n, ni);  //记得改
	sprintf_s(query, 85, "select token from t2 where tokenID between %d and %d", ni - n, ni);  //记得改
	buffres = _mc.QueryDB(query);
	return ni;
}

//比对助手！！！God！！！好烦这东西好烦好烦
bool SolveData1::comparisonhelp(char*token)
{
	while (buffcol = mysql_fetch_row(buffres))
		if (strcmp(buffcol[0], token) == 0)
			return true;
	return false;

}

// 比对
void SolveData1::Comparison(char*token, const vector<List>&a)
{
	char * sql = "select item from t2 where token = '";
	size_t len = strlen(sql) + strlen(token) + 2;
	char* query = (char*)malloc(len);
	sprintf_s(query, len, "%s%s'", sql, token);
	//	mysql_free_result(_mc.res);
	_mc.res = _mc.QueryDB(query);
	_mc.column = mysql_fetch_row(_mc.res);
	char *p = _mc.column[0];
	const int n = 7; //个数
	vector<List> temp = Merge50(charToVector(p, n), a);
	updatehelp(temp, token);
}

// 如果新保存vector里面的东西不满50个，则
void SolveData1::buildTo50(vector<List>&item)
{
	//if (item.size() >= 50) return;
	if (item.size() >= 10) return;
	List a[] = { 0 };
	//for (int i = item.size(); i <= 50; i++)
	for (int i = item.size(); i <= 10; i++)
		item.push_back(a[0]);
}

void SolveData1::SaveData(char* token, vector<List>& item)
{
	char query[85];
	//sprintf_s(query, 85 ,"select token from invtable where tokenID between %d and %d", ni - n, ni);  //记得改
	sprintf_s(query, 85, "select item from t2 where token = '%s'", token);  //记得改
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


vector<List> SolveData1::selFromInvtable(char* token)//从倒排表取出token的item
{
	char* sql = "select item from t2 where token = '";  //记得改
	size_t len = strlen(sql) + strlen(token) + 2;
	char* query = (char*)malloc(len);
	sprintf_s(query, len, "%s%s'", sql, token);
	mysql_free_result(_mc.res);
	_mc.res = _mc.QueryDB(query);
	_mc.column = mysql_fetch_row(_mc.res);
	char *p = _mc.column[0];
	const int n = 7; //个数
	return charToVector(p, n);
}


int main()
{
	const int n = 7;
	List a[] = { 13,12,10,9,7,5,1 };
	List b[] = { 19,15,11,7,6,4,2 };

	List d[] = { 11,7,6,4,2 };
	vector<List> a1(a, a + 7);
	vector<List> b1(b, b + 7);
	vector<List> d1(d, d + 5);
	SolveData1 mc("localhost", "root", "may1024", "gitsoo", 3306);
	/*SolveData1 kc;
	kc.ConnectMysql("localhost", "root", "may1024", "smallu", 3306);*/
	//mc.inserthelp(a1, "abb");
	//mc.inserthelp(a1, "bbb");
	//mc.inserthelp(a1, "cbb");
	//mc.inserthelp(a1, "ebb");
	//mc.inserthelp(a1, "fbb");
	//mc.inserthelp(a1, "gbb");
	//mc.inserthelp(a1, "hbb");
	//mc.inserthelp(a1, "ibb");
	//mc.inserthelp(a1, "jbb");
	//mc.inserthelp(a1, "kbb");
	//mc.inserthelp(a1, "lbb");
	//mc.inserthelp(a1, "mnn");
	//mc.updatehelp(b1, "mnn");
	//mc.GetData_Solve();//从数据库将update=1数据取出，并且将update置0，处理data
	/*vector<List> q = mc.selFromInvtable("mnn");
	for (int i = 0; i < q.size(); i++)
	{
	cout << q[i].a << " ";
	}*/

	//	vector<List> q1 = mc.Merge50(a1, b1);
	//	vector<List> q = mc.Merge50(b1, b1);
	//	for (int i = 0; i < q.size(); i++)
	//	{
	//		cout << q[i].a << " ";
	//	}
	/*
	vector<List> q = mc.Merge50(a1, d1);
	for (int i = 0; i < q.size(); i++)
	{
	cout << q[i].a << " ";
	}*/

	/*mc.Comparison("ibb", b1);
	vector<List> q = mc.selFromInvtable("ibb");
	for (int i = 0; i < q.size(); i++)
	{
	cout << q[i].a << " ";
	}*/

	//cout << mc.tableCount("t2");// 数表里面有多少行 /**********记得改类型***********/
	//List t[] = { 1,2,5 };
	//vector<List> t1(t, t + 3);
	//mc.buildTo50(t1);// 如果新保存vector里面的东西不满50个，则
	//for (int i = 0; i < t1.size(); i++)
	//{
	//	cout << t1[i].a << " ";
	//}
	//int i = 0, count = mc.tableCount("t2");
	//cout << count << endl;
	//while (i < count)
	//{
	//	i = mc.buffer(i, count);	//每次取出一个buffer的结果集,buffer从ni开始，count为表里的长度,返回buffer到哪里
	//	cout << i << endl;
	//	mc.SaveData("cbb", a1);	//保存数据到数据库

	//	mc.SaveData("ibb", a1);
	//	mc.SaveData("hbb", d1);
	//	mc.SaveData("tbb", a1);	//保存数据到数据库
	//	mc.SaveData("ybb", d1);
	//	vector<List> q = mc.selFromInvtable("ybb");
	//	for (int i = 0; i < q.size(); i++)
	//	{
	//		cout << q[i].a << " ";
	//	}
	//}
	//vector<List> q = mc.selFromInvtable("ybb");
	//for (int i = 0; i < q.size(); i++)
	//{
	//	cout << q[i].a << " ";
	//}
	////vector<List> q = mc.Merge50(a1,d1);// 归并算法，找出词频为前50个的词 /*******记得改类型********/
	////for (int i = 0; i < q.size(); i++)
	////{
	////	cout << q[i].a << " ";
	////}
	////vector<List> q =mc.Merge50(a1, b1);
	////for (int i = 0; i < q.size(); i++)
	////{
	////	cout << q[i].a << " ";
	////}
}

