#!/bin/bash

declare -a qTypes
declare -a sizes
declare -a orders

#declaring all needed parameters
sizes=(50000 100000 150000 200000 250000 300000 350000 400000 450000 500000)
orders=(OrdC OrdD Ale)
qTypes=(QC QM3 QPE QI1 QI5 QI10 QNR)

#creating output folder
if [ -d out ]; then
    rm -r out
fi

mkdir out

for qType in "${qTypes[@]}"
do
    for order in "${orders[@]}"
    do
        for size in "${sizes[@]}"
        do
            ../trab.exe $qType $order $size >> out/${qType}.out
        done
    done
done