PROGS = fdiv mallocavoid analyze
OBJS = add2_s.o

CFLAGS = -g

# Pattern rules to avoid explicit rules

%.o : %.c
	gcc ${CFLAGS} -c -o $@ $<

%.o : %.s
	as ${CFLAGS} -o $@ $<

all : ${PROGS}

analyze : analyze.c ${OBJS}
	gcc ${CFLAGS} -o $@ $< ${OBJS}

clean :
	rm -rf ${PROGS} ${OBJS}
