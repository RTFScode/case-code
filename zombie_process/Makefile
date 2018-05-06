CC=gcc
# -Wall : all types of the alarm information
# -g 	: gdb debugging information
# -O2	: code optimization
CFLAG=-Wall -g -O2
LIB=-lpthread
ALL=zombp
OBJECT=zombp.o

# $@	: the target file
# $^	: prerequisites,
# $<	: the first of $^
$(ALL):$(OBJECT)
	$(CC) $(CFLAG) $(LIB) $^ -o $@

# automatic compilation rules
%.o:%.c
	$(CC) $(CFLAG) -c $^ -o $@

# the pseudo target
.PHONY:
	clean
clean:
	-rm -rf $(OBJECT) $(ALL) 
