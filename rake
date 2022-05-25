#!/bin/bash

probs="0.00 0.05 0.10 0.15 0.20 0.25 0.30 0.35 0.40 0.45 0.50 0.55 0.60 0.65 0.70 0.75 0.80 0.85 0.90 0.95 1.00"

for i in $probs ; do
	echo -n $i
	echo -n '|'
	files=($1/$i-*)
	grep 'identified patient zero' "${files[@]}" | wc -l | head -c -1
	echo -n '|'
	grep 'did not identify patient zero' "${files[@]}" | wc -l | head -c -1
	echo -n '|'
	grep 'only [01] infected generated' "${files[@]}" | wc -l | head -c -1
	echo -n '|'
	grep -h 'match at distance:' "${files[@]}" | awk -F ':' '{ sum += $2 } END { if (NR > 0) print sum / NR }' | head -c -1
	echo -n '|'
	grep -h 'match at distance:' "${files[@]}" | awk -F ':' 'BEGIN{a= 0} {if ($2>0+a) a=0+$2} END {print a}' | head -c -1
	echo
done
