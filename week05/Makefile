PROGS = main endian
PROG = main
OBJS = sum_array_c.o sum_array_s.o sum_array2_s.o
HEADERS = 

CFLAGS = -g

# Pattern rules to avoid explicit rules

%.o : %.c ${HEADERS}
	gcc ${CFLAGS} -c -o $@ $<

%.o : %.s
	as -o $@ $<

all : ${PROGS}

${PROG} : ${PROG}.c ${HEADERS} ${OBJS}
	gcc ${CFLAGS} -o $@ $< ${OBJS}

endian : endian.c
	gcc ${CFLAGS} -o $@ $<

clean :
	rm -rf ${PROGS} ${OBJS}
