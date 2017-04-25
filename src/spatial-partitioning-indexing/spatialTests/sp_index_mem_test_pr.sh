#!/bin/bash
if [ "$#" -ne 1 ]; then
  echo "Usage: $0 Max Limit"
  exit 1
fi
COUNTER=$1
for (( i=1; i<=COUNTER; i=i*2 ))
do  
	cp In-Memory-Spatial-DB spind_$i
	chmod +x spind_$i
	./sp_ind_$i $i > sp_ind_output_$i 2>&1 &
done