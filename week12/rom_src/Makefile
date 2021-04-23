HEXFILES = 0_quadratic_s.hex 1_quadratic_s.hex \
           2_max3_s.hex 3_max3_s.hex

AS = as
OBJDUMP = objdump

%.o: %.s
	${AS} -o $@ $<

%.hex: %.o
	${OBJDUMP} -d $< | python3 makerom3.py > $@	

all : ${HEXFILES}
	
clean:
	rm -rf ${HEXFILES}

