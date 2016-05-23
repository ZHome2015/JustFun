#include"MysqlCon.h"

//从数据库将update=1数据取出，并且将update置0，处理data
void GetData_Solve()
{
	char * query = "select pageID,text from tbname where update_ = 1";  // 取出update_为1的数据
	res = QueryDB(query);
	printf("number of dataline returned: %Id\n", mysql_affected_rows(&mysql));
	for (int i = 0; fd = mysql_fetch_field(res); i++)
		strcpy_s(field[i], fd->name);  // 获取字段名字
	int row = mysql_num_fields(res); // 获取列数
	for (int i = 0; i < row; i++)   // 打印字段名
		printf("%10s\t", field[i]);
	printf("\n");
	while (column = mysql_fetch_row(res)) //打印
	{
		for (int i = 0; i < row; i++)
			printf("%s\t", column[i]);
		printf("\n");
	}
	query = "update tbname set update_ = 0 where update_ = 1";  //取完数据直接置零，其他到时再说
	DealData(query);
	mysql_free_result(res);
}

int main()
{
	ConnectDB("localhost", "root", "may1024", "gitsoo", 3306);
	GetData_Solve();
	FreeConnect();
}

