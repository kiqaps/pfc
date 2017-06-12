#!/bin/bash

for i in {1..2}
do
	if [ "$i" == 1 ]; then
		./bin/showg -p$i -a ./grafos/graph2.g6 | ./bin/fix_input 2 | ./bin/PFC > ./resultados/2vertices.txt 2> erros.txt
	else
		./bin/showg -p$i -a ./grafos/graph2.g6 | ./bin/fix_input 2 | ./bin/PFC >> ./resultados/2vertices.txt 2>> erros.txt
	fi
done

for i in {1..4}
do
	if [ "$i" == 1 ]; then
		./bin/showg -p$i -a ./grafos/graph2.g6 | ./bin/fix_input 3 | ./bin/PFC > ./resultados/4vertices.txt 2> erros.txt
	else
		./bin/showg -p$i -a ./grafos/graph2.g6 | ./bin/fix_input 3 | ./bin/PFC >> ./resultados/4vertices.txt 2>> erros.txt
	fi
done
