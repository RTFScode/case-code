CC=gcc
CFLAG=-w -g -O2
ALL=client
OBJ=client.o

$(ALL):$(OBJ)
	$(CC) $(CFLAG) $^ -o $@

%.o:%.c
	$(CC) $(CFLAG) -c $^ -o $@

clean:
	-rm -rf $(OBJ) $(ALL)