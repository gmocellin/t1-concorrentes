#! /bin/bash

# for each matrix file
for test_file in $(ls ../matrizes)
do

	total_time_single=0
	total_time_multi=0

	# ten times to have an average
	for((i=0 ;i<10;i++))
	do
		(/usr/bin/time -f "\n%e" make normal < ../matrizes/$test_file) 2>> ../matrizes/tmp-$test_file 1>> ../matrizes/result-$test_file
		total_time_single=$(python -c "print ($total_time_single + $(tail -n 1 ../matrizes/tmp-$test_file))")


	done

	echo ../matrizes/$test_file
	echo Average Singlethreaded Time: $(python -c "print (\"%.3f\" % ($total_time_single/10))")
	echo 

	#rm ../matrizes/tmp-$test_file
done
