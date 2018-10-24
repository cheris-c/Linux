/*
 * mymysql.h
 *
 *  Created on: 2013年12月27日
 *      Author: zhujy
 */
#ifndef MYMYSQL_H_
#define MYMYSQL_H_


int sql_connect(const char *Hostname, const char *User, const char *Password, const char *DBName);
int sql_disconnect();
int query_result(const char *name, char **buf);


#endif /* MYMYSQL_H_ */
