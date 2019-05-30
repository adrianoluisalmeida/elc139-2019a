
#/bin/bash

ARGC=$#    
MAX_ARGS=1

tests () {
	file="sr_bcast"
	start=0
	end=30
	time_finish=0
	
	for (( i = $start; i < $end; i++ )) 
	do
		smpirun -np $1 -hostfile cluster_hostfile.txt -platform cluster_crossbar.xml ./sr_bcast --cfg=smpi/host-speed:10000000 -std=gnu++11 >> out-$1.txt

		tempo=`sed -n '$p' out-$1.txt`
		time_finish=`echo $tempo + $time_finish | bc`
	done

	media_sr_bcast=$(echo $time_finish/$end | bc -l)
	echo "media: " $media_sr_bcast
}

if [ $ARGC -ne $MAX_ARGS ]; then 
    echo -e "Uso: $0 <num_processos> \n">&2
else
    
    tests $1
fi