/*************************************************************************
    > File Name: handlehttp.h
    > Author: Actually
    > Created Time: Fri 28 Jul 2017 10:43:11 AM CST
 ************************************************************************/

#ifndef HANDLEHTTP_H
#define HANDLEHTTP_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <errno.h>
#include <string.h>

#include <sys/stat.h>

//8192是8k
#define BUFSIZE 8192

#define HEAD "HTTP/1.0 200 OK\n\
Content-Type: %s\n\
Transfer-Encoding: chunked\n\
Connection: Keep-Alive\n\
Accept-Ranges:bytes\n\
Content-Length:%lu\n\n"

#define TAIL "\n\n"

void gethttpcommand(const char *sHTTPMsg, char *command); 	//从http请求中读出GET后面的命令行
size_t make_http_content(char *command, char **buf);	//根据get提供的文件名，生成静态http reponse消息内容


//辅助函数
const char* getfiletype(const char *filename); 	         //根据扩展名返回文件类型描述
size_t getfilecontent(const char *filename, char **buf); //得到文件内容
unsigned char hexstr2dec(const char *hex);	       //将两位16进制的字符串转化为十进制的unsigned char，例如：'10'转化为16,‘1A'转化为17
void httpstr2stdstr(const char *httpstr, char *stdstr);//将HTTP GET请求中的转义符号转化为标准字符,注意，空格被转义为'+'号
int hex2dec(const char hex);			       //将16进制的字符转化为十进制的整数，例如：'a'转化为整数10,‘B’转化为整数11


#endif  /*HANDLEHTTP_H*/
