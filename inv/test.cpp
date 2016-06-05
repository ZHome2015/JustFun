//#include<iostream>
//#include<ctime>
//#include<vector>
//using namespace std;
////struct Node
////{
////	int a;
////	Node*next;
////};
////
////void init(Node *head)
////{
////	head->next = NULL;
////	Node* p = head;
////	p->next = NULL;
////	for (int i = 0; i < 5; i++)
////	{
////		Node* q = new Node();
////		p->next = q;
////		q->a = i;
////		q->next = NULL;
////		p = p->next;
////	}
////	p->next = NULL;
////}
////
////void deleteNode(Node*head)
////{
////	while(head->next!=NULL)
////	{	
////		Node* temp = head;
////		head = head->next;
////		delete temp;
////
////	}
////}
////struct List
////{
////	int a;
////	char s[3];
////	//double t;
////};
////int main()
////{
////	List b[2];
////	b[0].s[0] = 'c';
////	b[0].s[1] = 'h';
////	b[0].s[2] = 'q';
////	b[1].s[0] = 'a';
////	b[1].s[1] = 'b';
////	b[1].s[2] = 'c';
////	//int b[] = { 0,1 ,2,5,3,4 };
////	vector<List> a(b, b + 2);
////	vector<List>::iterator vi,vi2;
////	for (vi = a.begin(); vi != a.end(); vi++)
////		cout << (*vi).s[0] << (*vi).s[1] << (*vi).s[2];
////	char *p =  (char*)&a[0];
////	int len = sizeof(a);
////	cout << endl;
////	//for (int i = 0; i < len; i++)
////	//{
////	//	cout << (int)*p << " ";
////	//	++p;
////	//}
////	List *q = (List*)p;
////	vector<List> m (q, q + 2);
////
////	for (vi2 = m.begin(); vi2 != m.end(); vi2++)
////		cout << (*vi2).s[0] << (*vi2).s[1] << (*vi2).s[2];
////	//List arr[2];
////	//arr[0].s[0] = 'c';
////	//arr[0].s[1] = 'h';
////	//arr[0].s[2] = 'q';
////	//arr[1].s[0] = 'a';
////	//arr[1].s[1] = 'b';
////	//arr[1].s[2] = 'c';
////	//char *p = (char*)arr;
////	//int len = sizeof(arr);
////	//for (int i = 0; i < len; i++)
////	//{
////	//	cout << (int)*p << " ";
////	//	++p;
////	//}
////	//cout << endl;
////	//for (int i = 0; i < len; i++)
////	//	p--;
////	//List* m = (List*)p;
////	//for (int i = 0; i < 2; i++)
////	//{
////	//	cout << m[i].s[0] << m[i].s[1] << m[i].s[2] << " ";
////	//}
////	//time_t start, end, time;
////	//start = clock();
////	//end = start + 1000;
////	//end = clock();
////	//time = end - start;
////	//cout << time << endl;
////	/*
////	Node*head = new Node();
////	init(head);
////	Node*m[5];
////	int i = 0;
////	while (head->next!= NULL)
////	{
////		head = head->next;
////		m[i] = head;
////		cout << head->a << " ";
////		i++;
////	}
////
////	int* t = reinterpret_cast<int*> (*m);
////	cout << *t << " ";
////	
////	deleteNode(head);*/
////}
//struct P
//{
//	int a;
//	P&operator=(const P&n)
//	{
//		a = n.a;
//		return *this;
//	}
//};
//
//void merge(const vector<P> a, const vector<P>b, vector<P>& m)
//{
//	/*m.resize(a.size() + b.size());
//	vector<P>::const_iterator ai, bi;
//	vector<P>::iterator mi;
//	for (ai = a.begin(), bi = b.begin(), mi = m.begin(); mi != m.end(); mi++)
//	{
//		if (ai == a.end())
//		{
//			(*mi) = (*bi);
//			bi++;
//		}
//		else if (bi == b.end())
//		{
//			(*mi) = (*ai);
//			ai++;
//		}
//		else if ((*ai).a > (*bi).a)
//		{
//			(*mi) = (*bi);
//			bi++;
//		}
//		else
//		{
//			(*mi) = (*ai);
//			ai++;
//		}
//	}*/
//
//	vector<P> result;
//	result.resize(15);
//	vector<P>::iterator ri;
//	vector<P>::const_iterator ai, bi;
//	for (ai = a.begin(), bi = b.begin(), ri = result.begin(); ri != result.end(); ri++)
//	{
//
//		if (ai == a.end() && bi == b.end()) break;
//		else if (ai == a.end())
//		{
//			(*ri) = (*bi);
//			bi++;
//		}
//		else if (bi == b.end())
//		{
//			(*ri) = (*ai);
//			ai++;
//		}
//		else if ((*ai).a > (*bi).a) /*记得改类型！！！！*/
//		{
//			(*ri) = (*ai);
//			ai++;
//		}
//		else
//		{
//			(*ri) = (*bi);
//			bi++;
//		}
//	}
//	m = result;
//}
//
//int main()
//{
//	P a[5] = { 10,9,7,5,3 };
//	P b[] = { 11,8,6,4,2,1};
//	vector<P> a1(a, a + 5);
//	vector<P> b1(b, b + 5);
//	vector<P> m;
//	merge(a1, b1, m);
//	vector<P>::iterator mi;
//	for (mi = m.begin(); mi != m.end(); mi++)
//		cout << (*mi).a << " ";
//}