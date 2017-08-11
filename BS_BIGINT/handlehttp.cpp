/*************************************************************************
    > File Name: handlehttp.cpp
    > Author: Actually
    > Created Time: Fri 28 Jul 2017 10:43:20 AM CST
 ************************************************************************/

#include "handlehttp.h"
#include "calc.h"
#include "mystring.h"


void gethttpcommand(const char *sHTTPMsg, char *command) //从http请求中读出GET后面的命令行
{
	int i;
	int istart = 0;
	int iend = 0;
	for (i = 0; i < strlen(sHTTPMsg); i++)
	{
		if ((sHTTPMsg[i] == ' ') && (istart == 0))
		{
			istart = i + 2;
		} else
		{
			if (sHTTPMsg[i] == ' ')
			{
				iend = i;
				break;
			}
		}
	}
	strncpy(command, &sHTTPMsg[istart], (iend - istart));
}

size_t make_http_content(char *command, char **buf) //根据get提供的文件名，生成静态http reponse消息内容
{
	char *contentbuf = NULL;
	size_t icontentlen = 0;

	if (command[0] == 0) //GET请求后面为空，得到默认页面内容图
	{
		icontentlen = getfilecontent("./html/index.html", &contentbuf);
	} else
	{
		/*		
		if (strncmp(command, EXEC, strlen(EXEC)) == 0) //GET请求后面为s?wd=
		{
			char query[1024];
			memset(query, 0, sizeof(query));
			httpstr2stdstr(&command[strlen(EXEC)], query); //得到s?wd=字符串后面的转义字符内容
			icontentlen = getdynamicccontent(query, &contentbuf);
		} else
		{
			icontentlen = getfilecontent(command, &contentbuf);//动态设置http请求内容,query为条件，buf为动态内容
		}
		*/
		if (strcmp(command, "favicon.ico") == 0)
		{
			icontentlen = getfilecontent(command, &contentbuf);	
		}
		else{
			vector<string> vec;
			char tok[] = "=&=&=";
			char stdstr[1024];
			printf("%s\n", command);
			memset(stdstr, 0, 1024);
			httpstr2stdstr(command, stdstr);
			printf("%s\n", stdstr);
				
			int size = splitStr(stdstr, tok, vec);
			const char *bt1 = vec.at(1).c_str();	
			const char *op = vec.at(3).c_str();
			const char *bt2 = vec.at(5).c_str();
	
			char *result = BigInt_calc(bt1, bt2, op);
		
			contentbuf = (char *)malloc(BUFSIZE);
			memset(contentbuf, 0, BUFSIZE);
			char *buf = NULL;
			getfilecontent("./html/result.html", &buf);
			sprintf(contentbuf, buf, bt1, op, bt2, result);
			icontentlen = strlen(contentbuf) + 1;
			if (buf)
			{
				free(buf);
				buf = NULL;
			}
			if (result)
			{
				free(result);
				result = NULL;
			}
		}
	}

	if (icontentlen > 0)
	{
		char headbuf[1024];
		memset(headbuf, 0, sizeof(headbuf));
		sprintf(headbuf, HEAD, getfiletype(command), icontentlen); //设置消息头
		size_t iheadlen = strlen(headbuf);//得到消息头长度
		size_t itaillen = strlen(TAIL);//得到消息尾长度
		size_t isumlen = iheadlen + icontentlen + itaillen;//得到消息总长度
		*buf = (char *)malloc(isumlen);//根据消息总长度，动态分配内存
		char *tmp = *buf;
		memcpy(tmp, headbuf, iheadlen); //安装消息头
		memcpy(&tmp[iheadlen], contentbuf, icontentlen); //安装消息体
		memcpy(&tmp[iheadlen + icontentlen], TAIL, itaillen); //安装消息尾
		printf("headbuf:\n%s", headbuf);
		//printf("\n%s", contentbuf);
		if (contentbuf)
		{
			free(contentbuf);
			contentbuf = NULL;		
		}
		return isumlen;//返回消息总长度
	} else
	{
		return 0;
	}
}

//////////////////////////////辅助函数实现////////////////////////////////////////////////////
const char* getfiletype(const char *filename) //根据扩展名返回文件类型描述
{
	////////////得到文件扩展名///////////////////
	int len = strlen(filename);
	int i;
	char sExt[32];
	memset(sExt, 0, sizeof(sExt));
	for (i = 0; i < len; i++)
	{
		if (filename[i] == '.')
		{
			strncpy(sExt, &filename[i + 1], sizeof(sExt));
			break;
		}
	}

	////////根据扩展名返回相应描述///////////////////

	if (strncmp(sExt, "bmp", 3) == 0)
		return "image/bmp";

	if (strncmp(sExt, "gif", 3) == 0)
		return "image/gif";

	if (strncmp(sExt, "ico", 3) == 0)
		return "image/x-icon";

	if (strncmp(sExt, "jpg", 3) == 0)
		return "image/jpeg";

	if (strncmp(sExt, "avi", 3) == 0)
		return "video/avi";

	if (strncmp(sExt, "css", 3) == 0)
		return "text/css";

	if (strncmp(sExt, "dll", 3) == 0)
		return "application/x-msdownload";

	if (strncmp(sExt, "exe", 3) == 0)
		return "application/x-msdownload";

	if (strncmp(sExt, "dtd", 3) == 0)
		return "text/xml";

	if (strncmp(sExt, "mp3", 3) == 0)
		return "audio/mp3";

	if (strncmp(sExt, "mpg", 3) == 0)
		return "video/mpg";

	if (strncmp(sExt, "png", 3) == 0)
		return "image/png";

	if (strncmp(sExt, "ppt", 3) == 0)
		return "application/vnd.ms-powerpoint";

	if (strncmp(sExt, "xls", 3) == 0)
		return "application/vnd.ms-excel";

	if (strncmp(sExt, "doc", 3) == 0)
		return "application/msword";

	if (strncmp(sExt, "mp4", 3) == 0)
		return "video/mpeg4";

	if (strncmp(sExt, "ppt", 3) == 0)
		return "application/x-ppt";

	if (strncmp(sExt, "wma", 3) == 0)
		return "audio/x-ms-wma";

	if (strncmp(sExt, "wmv", 3) == 0)
		return "video/x-ms-wmv";
	
	if (strncmp(sExt, "rar", 3) == 0)
		return "application/x-rar-compressed";
	
	if (strncmp(sExt, "zip", 3) == 0)
		return "application/zip";

	return "text/html";
}
int hex2dec(const char hex) //将16进制的字符转化为十进制的整数，例如：'a'转化为整数10,‘B’转化为整数11
{
	switch (hex)
	{
	case '0':
		return 0;
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	case 'a':
		return 10;
	case 'A':
		return 10;
	case 'b':
		return 11;
	case 'B':
		return 11;
	case 'c':
		return 12;
	case 'C':
		return 12;
	case 'd':
		return 13;
	case 'D':
		return 13;
	case 'e':
		return 14;
	case 'E':
		return 14;
	case 'f':
		return 15;
	case 'F':
		return 15;
	default:
		return -1;
	}
}

//将两位16进制的字符串转化为十进制的unsigned char，例如：'10'转化为16,‘1A'转化为17
unsigned char hexstr2dec(const char *hex) 
{
	return hex2dec(hex[0]) * 16 + hex2dec(hex[1]);
}

//将HTTP GET请求中的转义符号转化为标准字符,注意，空格被转义为'+'号
void httpstr2stdstr(const char *httpstr, char *stdstr)
{
	int index = 0;
	int i;
	for (i = 0; i < strlen(httpstr); i++)
	{
		if (httpstr[i] == '%')
		{
			stdstr[index] = hexstr2dec(&httpstr[i + 1]);
			i += 2;
		} else
		{
			stdstr[index] = httpstr[i];
		}
		index++;
	}
}
size_t getfilecontent(const char *filename, char **buf) //得到文件内容
{
	struct stat t;
	memset(&t, 0, sizeof(t));
	FILE *fd = fopen(filename, "rb");//从只读方式打开参数filename指定的文件
	if (fd != NULL)
	{
		stat(filename, &t);
		*buf = (char *)malloc(t.st_size);//根据文件大小，动态分配内存buf
		fread(*buf, t.st_size, 1, fd);//将文件读取到buf
		fclose(fd);
		return t.st_size;
	} else
	{
		printf("open %s failed %s\n", filename, strerror(errno));
		return 0;
	}
}



