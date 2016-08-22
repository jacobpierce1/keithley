#!/bin/bash
# this script will execute plot_keithley.cpp in root, allowing for command line args.

python keithley.py

# if [ $1 == "sweep" ]
# then
#     shift
#     start=$1
#     shift
#     end=$1
#     shift
#     inc=$1
#     echo "performing sweep: "$start" "$end" "$inc
    
# elif [ $1 == "setv" ]
# then
#     shift
#     voltage=$1
#     echo "setting voltage"
# fi

# # run the file using args
# file="plot_keithley.cpp"$args
# echo $file
# root $file
