#!/bin/bash

#Usado para calcular o tempo de execução dos arquivos;
#Para o correto funcionamento o arquivo executado deve retornar apenas o tempo final em (seg),
#no caso o fractalpar1, fractal e fractapar2


#testes que serão executados
#param 1 - width
#param 2 - frames

threads=( 2 4 6 8 )
width=( 256 512 )
frames=( 32 64 128 )

#width=( 256 )
#frames=( 32 )
timeSeq=()

for thread in "${threads[@]}"
do
    echo "--- THREADS -> $thread --- " >> teste.txt
    for i in "${width[@]}"
    do

    	for j in "${frames[@]}"
        do
            #mosta a execução atual
            time="$i $j "

            #tempo do sequencial
            timeSeq=$(./fractal/fractal $i $j)
            time="$time Seq: $timeSeq "

            timeFractalpar2=$(./fractalpar2 $i $j $thread)
            time="$time Fractalpar2: $timeFractalpar2 "

            #speedup sequencial / fractapar1
            speedup=`echo $timeSeq / $timeFractalpar2 | bc -l`
            time="$time Speedup: $speedup "

            #$proc=4
            eficiencia=`echo $speedup / $thread | bc -l`
            eficiencia=`echo $eficiencia*100 | bc | sed 's/[.].*//'`

            time="$time Eficiência: $eficiencia% "

            echo "$time" >> teste.txt
            #$time >> teste.txt
    	    #./fractalpar1 $i $j >> teste.txt
        done


    done
done
#./fractalpar1 512 32