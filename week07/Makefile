PROGS = fdiv mallocavoid analyze armemu
OBJS = add2_s.o

CFLAGS = -g

# Pattern rules to avoid explicit rules

%.o : %.c
	gcc ${CFLAGS} -c -o $@ $<

%.o : %.s
	as ${CFLAGS} -o $@ $<

all : ${PROGS}

analyze : analyze.c ${OBJS}

armemu : armemu.c ${OBJS}

clean :
	rm -rf ${PROGS} ${OBJS}
