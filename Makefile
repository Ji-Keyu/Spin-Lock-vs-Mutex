#NAME: Keyu Ji
#EMAIL: g.jikeyu@gmail.com
#ID: 704966744

CC = gcc
CFLAGS = -Wall -Wextra -g3 -std=gnu11 -lprofiler
LIBS = -pthread


build: lab2_list

lab2_list: lab2_list.c SortedList.c SortedList.h
	$(CC) $(CFLAGS) -o $@ $(LIBS) lab2_list.c SortedList.c

dist: lab2b-704966744.tar.gz
sources = Makefile SortedList.h SortedList.c lab2_list.c README plot_list.sh lab2b_list.csv lab2_list.gp lab2b_1.png lab2b_2.png lab2b_3.png lab2b_4.png lab2b_5.png profile.out
lab2b-704966744.tar.gz: $(sources)
	tar -cvzf $@ $(sources)

lab2b_list.csv: lab2_list
	make tests

lab2b_1.png lab2b_2.png lab2b_3.png lab2b_4.png lab2b_5.png: lab2b_list.csv
	make graphs

tests: lab2_list
	-./plot_list.sh 2> /dev/null

graphs: lab2b_list.csv
	./lab2_list.gp

profile.out: lab2_list
	make profile

profile: lab2_list
	-rm -f raw.gperf 
	LD_PRELOAD=/usr/local/cs/gperftools-2.7/lib/libprofiler.so CPUPROFILE=./raw.gperf ./lab2_list --threads=12 --iterations=1000 --sync=s
	pprof --text ./lab2_list ./raw.gperf > profile.out
	pprof --list=t_func ./lab2_list ./raw.gperf >> profile.out
	-rm -f raw.gperf

clean:
	rm -f lab2_list *.tar.gz