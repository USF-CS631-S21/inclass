PROG = lab04
OBJS = max3_c.o max3_s.o find_max_c.o find_max_s.o\
       fib_rec_c.o fib_rec_s.o stolower_c.o stolower_s.o\
       fib_rec2_s.o
HEADERS = 

CFLAGS = -g

# Pattern rules to avoid explicit rules

%.o : %.c ${HEADERS}
	gcc ${CFLAGS} -c -o $@ $<

%.o : %.s
	as ${CFLAGS} -o $@ $<

all : ${PROG}

${PROG} : ${PROG}.c ${HEADERS} ${OBJS}
	gcc ${CFLAGS} -o $@ $< ${OBJS}

clean :
	rm -rf ${PROG} ${OBJS}
