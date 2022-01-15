#!/bin/bash

EXE="../src/proj"
INPUT="tree"
OUTPUT="output.txt"

write_to_file() {
	./randGeneoTree "$1" 0.5 > "$INPUT"
}

touch "$OUTPUT"

for size in $(seq 1 5000 100001); do
	sum_times=0

	for round in $(seq 0 4); do
		write_to_file "$size"
		time=$({ time -p "$EXE" < "$INPUT"; } 2>&1 | grep "real" | awk '{print $2}')
		sum_times=$(echo "scale=3; ${sum_times} + ${time}" | bc -l)
	done

	average=$(echo "scale=3; ${sum_times} / 5" | bc -l)

	echo "$size $average" >> "$OUTPUT"
	echo "Finished benchmark for size "$size""
done
