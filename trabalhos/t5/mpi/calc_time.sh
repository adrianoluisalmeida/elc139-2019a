
#/bin/bash

ARGC=$#    
MAX_ARGS=3 

tests () {
	file="mpi_dotprod"
	start=0
	end=30
	time_finish=0
	
	for (( i = $start; i < $end; i++ )) 
	do
		mpiexec --oversubscribe -np $1 mpi_dotprod $2 $3 >> out-$1-$2-$3.txt
		tempo=`sed -n '$p' out-$1-$2-$3.txt`
		time_finish=`echo $tempo + $time_finish | bc`
	done

	media_mpi_dotprod=$(echo $time_finish/$end | bc -l)
	echo "media: " $media_mpi_dotprod

    speedup=`echo $seq / $media_mpi_dotprod | bc -l`
    time="Speedup: $speedup "
    echo "$seq" 
    echo "$time" 
}

if [ $ARGC -ne $MAX_ARGS ]; then 
    echo -e "Uso: $0 <num_processos> <worksize> <repetitions>\n">&2
else

    seqWorksize=`echo $2*8 | bc -l`
    seq=$(mpiexec --oversubscribe -np 1 mpi_dotprod $seqWorksize $3)
    
    tests $1 $2 $3 $seq
fi