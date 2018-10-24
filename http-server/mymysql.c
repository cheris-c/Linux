/*
 * mymysql.cpp
 *
 *  Created on: 2014年5月27日
 *      Author: zhujy
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <mysql.h>

MYSQL *connection, mysql;

void sql_init() //初始化mysql
{
	connection = NULL;
	mysql_init(&mysql);
}

//连接到mysql数据库
int sql_connect(const char *Hostname, const char *User, const char *Password,
		const char *DBName)
{
	sql_init();
	connection = mysql_real_connect(&mysql, Hostname, User, Password, DBName, 0,
			0, 0);

	if (connection == NULL)
	{
		printf("%s\n", mysql_error(&mysql));
		return -1;
	}
	
	mysql_query(connection, "set names utf8");//设置字符集为utf8格式
	return 0;
}

//断开数据库连接
int sql_disconnect() //断开数据库连接
{
	if (connection)
	{
		mysql_close(connection);
		connection = NULL;
	}
	return 0;
}

void addurl(const char *url, const char *name, const char *description,
		char **buf)	//向动态消息体中添加一个url链接
{
	char content[1024];
	memset(content, 0, sizeof(content));
	sprintf(content, "<a href=\"http://%s\">%s</a></br>%s%s</br></br>", url,
			name, name, description);	//格式化字符串

	if (*buf != NULL)	//addurl函数已经调用过了，所以buf的值不等于NULL
	{
		int buflen = strlen(*buf);	//得到buf中字符串的长度
		int contentlen = strlen(content);	//得到conntent中字符串的长度
		int sumlen = buflen + contentlen;	//得到buf中字符串和content中字符串的长度之和
		char *tmp = malloc(sumlen + 1);	//分配一个新的临时缓冲区tmp，大小为buf + context
		memset(tmp, 0, sumlen + 1);
		strncpy(tmp, *buf, buflen);	//将buf中的字符串拷贝到tmp
		strncpy(&tmp[buflen], content, contentlen);	//将content中的字符串追加到tmp后面
		free(*buf);	//释放buf之前的内存
		*buf = tmp;	//将buf指向tmp的内存区域
	} else	//第一次调用addurl函数
	{
		int contentlen = strlen(content);	//得到content中字符串的长度
		*buf = malloc(contentlen + 1);	//根据content中字符串的长度动态分配内存空间buf
		memset(*buf, 0, contentlen + 1);
		strncpy(*buf, content, contentlen);	//将content中字符串拷贝到buf
	}
}

//以name为参数，执行“select url, name, description from baidu where name like” SQL语句
int query_result(const char *name, char **buf)
{
	int res = -1;
	char sSQL[1024];
	memset(sSQL, 0, sizeof(sSQL));
	sprintf(sSQL,
			"select url, name, description from baidu where name like '%%%s%%'",
			name);
	printf("%s\n", sSQL);
	int state = mysql_query(connection, sSQL);
	if (state != 0)
	{
		printf("%s\n", mysql_error(&mysql));
		return res;	//执行失败，返回-1
	}
	
	MYSQL_RES *result = mysql_store_result(connection);	//得到查询结果
	if (result == (MYSQL_RES *) NULL)
	{
		printf("%s\n", mysql_error(&mysql));
		return res;	//执行失败，返回-1
	} 	
	
	char sURL[1024];
	char sName[1024];
	char sDesc[1024];
	
	MYSQL_ROW sqlRow;
	while(1)
	{
		sqlRow = mysql_fetch_row(result);
		if (sqlRow == NULL)
			break;
		
		memset(sURL, 0, sizeof(sURL));
		memset(sName, 0, sizeof(sName));
		memset(sDesc, 0, sizeof(sDesc));
		strcpy(sURL, (const char *)sqlRow[0]);//得到url字段值
		strcpy(sName, (const char *)sqlRow[1]);//得到name字段值
		strcpy(sDesc, (const char *)sqlRow[2]);//得到description字段值
		addurl(sURL, sName, sDesc, buf);//调用addurl，将查询到的行记录转化为HTML形式的字符串
		res++;
	}
	mysql_free_result(result);
	return res;
	
}


