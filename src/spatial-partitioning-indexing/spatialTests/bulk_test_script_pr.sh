#!/bin/bash
if [ "$#" -ne 1 ]; then
  echo "Usage: $0 Max Limit"
  exit 1
fi
COUNTER=$1
for (( i=1; i<=COUNTER; i=i*2 ))
do  
	cp a.out a.out_$i
	chmod +x a.out_$i
	./a.out_$i $i > output_$i 2>&1
done