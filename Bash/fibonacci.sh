#! /bin/bash
let NUM_1=1
let NUM_2=1
read -p "please enter a number(>2):" NUM
echo $NUM_1;
while [ $NUM_2 -lt $NUM ];do
    echo $NUM_2;
    NUM_3=$((NUM_1+NUM_2));
    NUM_1=$NUM_2;
    NUM_2=$NUM_3;
done
