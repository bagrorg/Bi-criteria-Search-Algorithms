#!/bin/bash
python mergeGraphFiles.py $1 $2 $3 $4

python dijkstra.py $1 $5 $8
python dijkstra.py $2 $6 $8

if [ -z "${13}" ]
  then
    if [ -z "${11}" ]
      then
        ./$9 --algo ${10} --graph_path $4 --start_id $7 --goal_id $8 --h_time_path $5 --h_dist_path $6
      else
        ./$9 --algo ${10} --graph_path $4 --start_id $7 --goal_id $8 --eps_time ${11} --eps_dist ${12} --h_time_path $5 --h_dist_path $6
    fi
  else
    if [ -z "${11}" ]
      then
        ./$9 --algo ${10} --graph_path $4 --start_id $7 --goal_id $8 --history_path ${13} --h_time_path $5 --h_dist_path $6
      else
        ./$9 --algo ${10} --graph_path $4 --start_id $7 --goal_id $8 --history_path ${13} --eps_time ${11} --eps_dist ${12} --h_time_path $5 --h_dist_path $6
    fi
fi

