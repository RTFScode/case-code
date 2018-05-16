CC=gcc
CFLAG=-w -g -O2
ALL=server
OBJ=server.o

$(ALL):$(OBJ)
	$(CC) $(CFLAG) $^ -o $@

%.o:%.c
	$(CC) $(CFLAG) -c $^ -o $@

clean:
	-rm -rf $(OBJ) $(ALL)