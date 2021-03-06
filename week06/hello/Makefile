PROG = hello_s
OBJS = hello_s.o find_max_s.o
HEADERS = 

CFLAGS = -g

# Pattern rules to avoid explicit rules

%.o : %.c ${HEADERS}
	gcc ${CFLAGS} -c -o $@ $<

%.o : %.s
	as ${CFLAGS} -o $@ $<

all : ${PROG}

${PROG} : ${HEADERS} ${OBJS}
	gcc ${CFLAGS} -o $@ ${OBJS}

clean :
	rm -rf ${PROG} ${OBJS}
