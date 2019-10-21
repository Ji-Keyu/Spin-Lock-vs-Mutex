#!/bin/bash

if [[ -e lab2b_list.csv ]]; then
	rm lab2b_list.csv
fi

touch lab2b_list.csv

file=lab2b_list.csv

	./lab2_list --threads=1 --iterations=1000 --sync=m >> $file
	./lab2_list --threads=2 --iterations=1000 --sync=m >> $file
	./lab2_list --threads=4 --iterations=1000 --sync=m >> $file
	./lab2_list --threads=8 --iterations=1000 --sync=m >> $file
	./lab2_list --threads=12 --iterations=1000 --sync=m >> $file
	./lab2_list --threads=16 --iterations=1000 --sync=m >> $file
	./lab2_list --threads=24 --iterations=1000 --sync=m >> $file

	./lab2_list --threads=1 --iterations=1000 --sync=s >> $file
	./lab2_list --threads=2 --iterations=1000 --sync=s >> $file
	./lab2_list --threads=4 --iterations=1000 --sync=s >> $file
	./lab2_list --threads=8 --iterations=1000 --sync=s >> $file
	./lab2_list --threads=12 --iterations=1000 --sync=s >> $file
	./lab2_list --threads=16 --iterations=1000 --sync=s >> $file
	./lab2_list --threads=24 --iterations=1000 --sync=s >> $file

	./lab2_list --threads=1 --iterations=1 --yield=id --list=4 >> $file
	./lab2_list --threads=1 --iterations=2 --yield=id --list=4 >> $file
	./lab2_list --threads=1 --iterations=4 --yield=id --list=4 >> $file
	./lab2_list --threads=1 --iterations=8 --yield=id --list=4 >> $file
	./lab2_list --threads=1 --iterations=16 --yield=id --list=4 >> $file
	./lab2_list --threads=4 --iterations=1 --yield=id --list=4 >> $file
	./lab2_list --threads=4 --iterations=2 --yield=id --list=4 >> $file
	./lab2_list --threads=4 --iterations=4 --yield=id --list=4 >> $file
	./lab2_list --threads=4 --iterations=8 --yield=id --list=4 >> $file
	./lab2_list --threads=4 --iterations=16 --yield=id --list=4 >> $file
	./lab2_list --threads=8 --iterations=1 --yield=id --list=4 >> $file
	./lab2_list --threads=8 --iterations=2 --yield=id --list=4 >> $file
	./lab2_list --threads=8 --iterations=4 --yield=id --list=4 >> $file
	./lab2_list --threads=8 --iterations=8 --yield=id --list=4 >> $file
	./lab2_list --threads=8 --iterations=16 --yield=id --list=4 >> $file
	./lab2_list --threads=12 --iterations=1 --yield=id --list=4 >> $file
	./lab2_list --threads=12 --iterations=2 --yield=id --list=4 >> $file
	./lab2_list --threads=12 --iterations=4 --yield=id --list=4 >> $file
	./lab2_list --threads=12 --iterations=8 --yield=id --list=4 >> $file
	./lab2_list --threads=12 --iterations=16 --yield=id --list=4 >> $file
	./lab2_list --threads=16 --iterations=1 --yield=id --list=4 >> $file
	./lab2_list --threads=16 --iterations=2 --yield=id --list=4 >> $file
	./lab2_list --threads=16 --iterations=4 --yield=id --list=4 >> $file
	./lab2_list --threads=16 --iterations=8 --yield=id --list=4 >> $file
	./lab2_list --threads=16 --iterations=16 --yield=id --list=4 >> $file

	./lab2_list --threads=1 --iterations=10 --yield=id --list=4 --sync=m >> $file
	./lab2_list --threads=1 --iterations=20 --yield=id --list=4 --sync=m >> $file
	./lab2_list --threads=1 --iterations=40 --yield=id --list=4 --sync=m >> $file
	./lab2_list --threads=1 --iterations=80 --yield=id --list=4 --sync=m >> $file
	./lab2_list --threads=4 --iterations=10 --yield=id --list=4 --sync=m >> $file
	./lab2_list --threads=4 --iterations=20 --yield=id --list=4 --sync=m >> $file
	./lab2_list --threads=4 --iterations=40 --yield=id --list=4 --sync=m >> $file
	./lab2_list --threads=4 --iterations=80 --yield=id --list=4 --sync=m >> $file
	./lab2_list --threads=8 --iterations=10 --yield=id --list=4 --sync=m >> $file
	./lab2_list --threads=8 --iterations=20 --yield=id --list=4 --sync=m >> $file
	./lab2_list --threads=8 --iterations=40 --yield=id --list=4 --sync=m >> $file
	./lab2_list --threads=8 --iterations=80 --yield=id --list=4 --sync=m >> $file
	./lab2_list --threads=12 --iterations=10 --yield=id --list=4 --sync=m >> $file
	./lab2_list --threads=12 --iterations=20 --yield=id --list=4 --sync=m >> $file
	./lab2_list --threads=12 --iterations=40 --yield=id --list=4 --sync=m >> $file
	./lab2_list --threads=12 --iterations=80 --yield=id --list=4 --sync=m >> $file
	./lab2_list --threads=12 --iterations=16 --yield=id --list=4 --sync=m >> $file
	./lab2_list --threads=16 --iterations=10 --yield=id --list=4 --sync=m >> $file
	./lab2_list --threads=16 --iterations=20 --yield=id --list=4 --sync=m >> $file
	./lab2_list --threads=16 --iterations=40 --yield=id --list=4 --sync=m >> $file
	./lab2_list --threads=16 --iterations=80 --yield=id --list=4 --sync=m >> $file

	./lab2_list --threads=1 --iterations=10 --yield=id --list=4 --sync=s >> $file
	./lab2_list --threads=1 --iterations=20 --yield=id --list=4 --sync=s >> $file
	./lab2_list --threads=1 --iterations=40 --yield=id --list=4 --sync=s >> $file
	./lab2_list --threads=1 --iterations=80 --yield=id --list=4 --sync=s >> $file
	./lab2_list --threads=4 --iterations=10 --yield=id --list=4 --sync=s >> $file
	./lab2_list --threads=4 --iterations=20 --yield=id --list=4 --sync=s >> $file
	./lab2_list --threads=4 --iterations=40 --yield=id --list=4 --sync=s >> $file
	./lab2_list --threads=4 --iterations=80 --yield=id --list=4 --sync=s >> $file
	./lab2_list --threads=8 --iterations=10 --yield=id --list=4 --sync=s >> $file
	./lab2_list --threads=8 --iterations=20 --yield=id --list=4 --sync=s >> $file
	./lab2_list --threads=8 --iterations=40 --yield=id --list=4 --sync=s >> $file
	./lab2_list --threads=8 --iterations=80 --yield=id --list=4 --sync=s >> $file
	./lab2_list --threads=12 --iterations=10 --yield=id --list=4 --sync=s >> $file
	./lab2_list --threads=12 --iterations=20 --yield=id --list=4 --sync=s >> $file
	./lab2_list --threads=12 --iterations=40 --yield=id --list=4 --sync=s >> $file
	./lab2_list --threads=12 --iterations=80 --yield=id --list=4 --sync=s >> $file
	./lab2_list --threads=12 --iterations=16 --yield=id --list=4 --sync=s >> $file
	./lab2_list --threads=16 --iterations=10 --yield=id --list=4 --sync=s >> $file
	./lab2_list --threads=16 --iterations=20 --yield=id --list=4 --sync=s >> $file
	./lab2_list --threads=16 --iterations=40 --yield=id --list=4 --sync=s >> $file
	./lab2_list --threads=16 --iterations=80 --yield=id --list=4 --sync=s >> $file

	./lab2_list --threads=1 --iterations=1000 --list=4 --sync=m >> $file
	./lab2_list --threads=1 --iterations=1000 --list=8 --sync=m >> $file
	./lab2_list --threads=1 --iterations=1000 --list=16 --sync=m >> $file
	#./lab2_list --threads=2 --iterations=1000 --list=1 --sync=m >> $file
	./lab2_list --threads=2 --iterations=1000 --list=4 --sync=m >> $file
	./lab2_list --threads=2 --iterations=1000 --list=8 --sync=m >> $file
	./lab2_list --threads=2 --iterations=1000 --list=16 --sync=m >> $file
	#./lab2_list --threads=4 --iterations=1000 --list=1 --sync=m >> $file
	./lab2_list --threads=4 --iterations=1000 --list=4 --sync=m >> $file
	./lab2_list --threads=4 --iterations=1000 --list=8 --sync=m >> $file
	./lab2_list --threads=4 --iterations=1000 --list=16 --sync=m >> $file
	#./lab2_list --threads=8 --iterations=1000 --list=1 --sync=m >> $file
	./lab2_list --threads=8 --iterations=1000 --list=4 --sync=m >> $file
	./lab2_list --threads=8 --iterations=1000 --list=8 --sync=m >> $file
	./lab2_list --threads=8 --iterations=1000 --list=16 --sync=m >> $file
	#./lab2_list --threads=12 --iterations=1000 --list=1 --sync=m >> $file
	./lab2_list --threads=12 --iterations=1000 --list=4 --sync=m >> $file
	./lab2_list --threads=12 --iterations=1000 --list=8 --sync=m >> $file
	./lab2_list --threads=12 --iterations=1000 --list=16 --sync=m >> $file

	./lab2_list --threads=1 --iterations=1000 --list=4 --sync=s >> $file
	./lab2_list --threads=1 --iterations=1000 --list=8 --sync=s >> $file
	./lab2_list --threads=1 --iterations=1000 --list=16 --sync=s >> $file
	#./lab2_list --threads=2 --iterations=1000 --list=1 --sync=s >> $file
	./lab2_list --threads=2 --iterations=1000 --list=4 --sync=s >> $file
	./lab2_list --threads=2 --iterations=1000 --list=8 --sync=s >> $file
	./lab2_list --threads=2 --iterations=1000 --list=16 --sync=s >> $file
	#./lab2_list --threads=4 --iterations=1000 --list=1 --sync=s >> $file
	./lab2_list --threads=4 --iterations=1000 --list=4 --sync=s >> $file
	./lab2_list --threads=4 --iterations=1000 --list=8 --sync=s >> $file
	./lab2_list --threads=4 --iterations=1000 --list=16 --sync=s >> $file
	#./lab2_list --threads=8 --iterations=1000 --list=1 --sync=s >> $file
	./lab2_list --threads=8 --iterations=1000 --list=4 --sync=s >> $file
	./lab2_list --threads=8 --iterations=1000 --list=8 --sync=s >> $file
	./lab2_list --threads=8 --iterations=1000 --list=16 --sync=s >> $file
	#./lab2_list --threads=12 --iterations=1000 --list=1 --sync=s >> $file
	./lab2_list --threads=12 --iterations=1000 --list=4 --sync=s >> $file
	./lab2_list --threads=12 --iterations=1000 --list=8 --sync=s >> $file
	./lab2_list --threads=12 --iterations=1000 --list=16 --sync=s >> $file