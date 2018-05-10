CC=gcc
CFLAG=-w -g -O2
LIB=-lpthread
OBJECT=sync.o
ALL=sync
$(ALL):$(OBJECT)
	$(CC) $(CFLAG) -o $@ $^ $(LIB)

%.o:%.c
	$(CC) $(CFLAG) -c -o $@ $^

.PYTHON:
	clean
clean:
	-rm -rf $(OBJECT) $(ALL)
