#!/bin/bash
if [ "$#" -ne 1 ]; then
  echo "Usage: $0 Max Limit"
  exit 1
fi
COUNTER=$1
LOOP_EXIT=1
QTYPE='r'

for (( i=1; i<=COUNTER; i=i*2 ))
do
	cp In-Memory-Spatial-DB rect_$i
	chmod +x rect_$i
	./rect_$i $i $QTYPE $LOOP_EXIT> rect_out_$i 2>&1 &
done