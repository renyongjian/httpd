#include<stdio.h>
#include<string.h>

#define MAX_RECV_BUFF_LEN 1024

#ifdef DEBUG
#define debug( format, args... )do {fprintf(stderr,  "DEBUG >>> %s->%s()->line.%d : " format "\n", __FILE__, __FUNCTION__, __LINE__, ##args);}while(0)
#endif

int get_line(int socket,char *buff)
{
	debug("get_line ...");
	strcpy(buff,"GET /voip/SIP_Account1.asp");
	debug("get_line end");

	return 0;
}

/*reply 404*/
int reply_not_found(int socket)
{
	debug("reply_not_found ...");
	debug("reply_not_found end");
	return 0;
}

/*reply 500*/
int reply_internal_server(int socket)
{
	debug("reply_internal_server ...");
	debug("reply_internal_server end");
	return 0;
}

int serve_file(int socket,char *path)
{
	debug("serve_file ...");
	debug("serve_file end");
	return 0;
}


int execute_cgi(int socket,char *path,char *method,char *query)
{
	debug("execute_cgi ...");
	debug("execute_cgi end");
	return 0;
}


int accept_request(int socket)
{
	char buff[MAX_RECV_BUFF_LEN]="";
	int need_do_cgi = 0;
	char *data_str = NULL;
	char *query = NULL;
	char *path = NULL;
	char *method = NULL;

	get_line(socket,buff);

	/*ignore spaces in buff*/
	data_str = buff;
	while(data_str && *data_str == ' ') data_str++;

	debug("data_str=%s",data_str);
	/*post or get recved*/
	if(strcasestr(data_str,"post")==NULL  && strcasestr(data_str,"get")==NULL)
	{
		reply_not_found(socket);
		return -1;
	}

	/*if "POST" recved,do cgi*/
	if (strcasestr(data_str,"post"))
	{
		method = "POST";
		need_do_cgi=1;
	}

	/*if GET recved*/
	if (strcasestr(data_str,"get"))
	{
		method = "GET";
		query = strstr(data_str,"?");
		if (query != NULL)
		{
			query++;
			debug("query=%s",query);
			need_do_cgi=1;
		}
		else
		{
			/*get file path*/
			path = strstr(data_str,"/");
			debug("path=%s",path);
		}
	}

	/*if found query,do cgi*/
	/*if can't excute,reply 503*/
	if(need_do_cgi)
	{
		if(execute_cgi(socket,path,method,query) < 0)
		{
			reply_internal_server(socket);
			return -1;
		}
	}
	else
	{
		if(serve_file(socket,path))
		{
			reply_not_found(socket);
			return -1;
		}
	}

	return 0;
}


int main(int argc, const char *argv[])
{
	int socket = 666;
	accept_request(socket);
	return 0;
}
