cl=client
CFLAGS=-D DEBUG

all: client

client : $(cl).c server_list.h message.h
	gcc $(cl).c -o $(cl) ${CFLAGS}

clean: 
	rm $(cl)
