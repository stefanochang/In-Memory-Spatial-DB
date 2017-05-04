#!/bin/bash
if [ "$#" -ne 1 ]; then
  echo "Usage: $0 Max Limit"
  exit 1
fi
COUNTER=$1
LOOP_EXIT=1
QTYPE='p'
for (( i=1; i<=COUNTER; i=i*2 ))
do
	cp In-Memory-Spatial-DB point_$i
	chmod +x point_$i
	./point_$i $i $QTYPE $LOOP_EXIT> point_out_$i 2>&1 &
done