.PHONY : all clean check
.ONESHELL:

CHECK_PATCH=./checkpatch.pl --no-tree

all : testVersion testOffset testHistory

%.o : %.c
	gcc -g -Wall -c $<

testVersion : testVersion.o version.o
	gcc -g -Wall $^ -o $@

testOffset : testOffset.o history.o commit.o version.o
	gcc -g -Wall $^ -o $@

testHistory : testHistory.o list.h history.o version.o commit.o
	gcc -g -Wall $^ -o $@

check : 
	for f in *.c *.h ; do
		$(CHECK_PATCH) -f $$f
	done

clean :
	rm -rf *.o *~ testVersion testOffset testHistory
