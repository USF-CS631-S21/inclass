PROG = project03
OBJS = matches_c.o matches_s.o mergesort_c.o mergesort_s.o
HEADERS = 

CFLAGS = -g

# Pattern rules to avoid explicit rules
%.o : %.c ${HEADERS}
	gcc ${CFLAGS} -c -o $@ $<

%.o : %.s
	as -o $@ $<

all : ${PROG}

${PROG} : ${PROG}.c ${HEADERS} ${OBJS}
	gcc ${CFLAGS} -o $@ $< ${OBJS}

clean :
	rm -rf ${PROG} ${OBJS}
