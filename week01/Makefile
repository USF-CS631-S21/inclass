# PROGS is a make variable, like a shell variable
PROGS = hello data args

# Makefiles consist of rules:
#
# target : dependencies
#     action
#
# Note that you need an actual TAB character to indent the action

# You need a top-level rule. In this case "all" is a pseudo target.
# We don't actually generate a file called "all".

all : $(PROGS)

# We could write rules like the following:
#
#hello : hello.c
#	gcc -o hello hello.c
#
#hello : hello.c
#	gcc -o $@ $<


# Pattern rules make it easy to apply a rule to a set of targets.
# $@ is the target name
# $< is the first dependency name

% : %.c
	gcc -g -o $@ $<

# Here is another pseudo target that allows us to clean up any
# generated files.
clean :
	rm -f $(PROGS) *~

