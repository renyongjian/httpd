obj = httpd.c 
CC = gcc
MUTILIB=./libmutils/libmutils.a
LIBS= $(MUTILIB) -lssl -lcrypto 
INCLUDE= libmutils
CFLAGS= -DDEBUG  -g 
link:
	gcc  $(CFLAGS) $(obj) -o httpd
clean:
	rm httpd;
install:
	echo "nothing to be done"
