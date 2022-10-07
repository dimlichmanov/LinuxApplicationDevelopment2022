GENERATES = prog README liboutput_static.a README-a prog-a liboutput.so *.obj *-so emp* sing* mult*
TRASH = *.o *~ o.*
CC = cc
.DEFAULT_GOAL = README
#.DEFAULT_GOAL = README-a
#.DEFAULT_GOAL = README-so

all:    README prog

prog:	const.o fun.o prog.o
	$(LINK.c) -L. $^ -o $@

prog-a: prog.o liboutput_static.a
	$(LINK.c) -L. $< -loutput_static -o $@

prog-so: prog.o liboutput.so
	$(LINK.c) -L. $< -loutput -o $@

test: test-single test-multiple test-empty
	make clean


test-empty:
	make clean
	make prog
	./prog 2> emp
	make clean_trash
	make prog-a
	./prog-a 2> emp-a
	make clean_trash
	make prog-so
	LD_LIBRARY_PATH=`pwd` ./prog-so 2> emp-so
	cmp emp emp-a # ОШИБКА СДЕЛАНА СПЕЦИАЛЬНО, ИМЯ ФАЙЛА ВЫВОДИТСЯ В STDERR !!!
	сmp emp-so emp


test-single:
	make clean
	make prog
	./prog cheburek 1> sing
	make clean_trash
	make prog-a
	./prog-a cheburek 1> sing-a
	make clean_trash
	make prog-so
	LD_LIBRARY_PATH=`pwd` ./prog-so cheburek 1> sing-so
	cmp sing sing-a
	cmp sing-so sing

test-multiple:
	make clean
	make prog
	./prog lol kek 500 cheburek 1> mult
	make clean_trash
	make prog-a
	./prog-a lol kek 500 cheburek 1> mult-a
	make clean_trash
	make prog-so
	LD_LIBRARY_PATH=`pwd` ./prog-so lol kek 500 cheburek 1> mult-so
	cmp mult mult-a
	cmp mult-so mult

README: prog
	./$< 2> $@

README-a: prog-a
	./$< 2> $@

README-so: prog-so
	LD_LIBRARY_PATH=`pwd` ./$< 2> $@

liboutput_static.a: fun.o const.o
	ar -rcs $@ $^

liboutput.so: CFLAGS=-fPIC
liboutput.so: fun.o const.o
	$(CC) -shared $^ -o $@

clean:
	rm -rf $(TRASH) $(GENERATES)

clean_trash:
	rm -rf $(TRASH)

