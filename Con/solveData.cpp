#include"MysqlCon.h"

//�����ݿ⽫update=1����ȡ�������ҽ�update��0������data
void GetData_Solve()
{
	char * query = "select pageID,text from tbname where update_ = 1";  // ȡ��update_Ϊ1������
	res = QueryDB(query);
	printf("number of dataline returned: %Id\n", mysql_affected_rows(&mysql));
	for (int i = 0; fd = mysql_fetch_field(res); i++)
		strcpy_s(field[i], fd->name);  // ��ȡ�ֶ�����
	int row = mysql_num_fields(res); // ��ȡ����
	for (int i = 0; i < row; i++)   // ��ӡ�ֶ���
		printf("%10s\t", field[i]);
	printf("\n");
	while (column = mysql_fetch_row(res)) //��ӡ
	{
		for (int i = 0; i < row; i++)
			printf("%s\t", column[i]);
		printf("\n");
	}
	query = "update tbname set update_ = 0 where update_ = 1";  //ȡ������ֱ�����㣬������ʱ��˵
	DealData(query);
	mysql_free_result(res);
}

int main()
{
	ConnectDB("localhost", "root", "may1024", "gitsoo", 3306);
	GetData_Solve();
	FreeConnect();
}

