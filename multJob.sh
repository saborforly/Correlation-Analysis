#!/bin/bash  
  
for i in $(seq 1 3)
do   
sbatch /hpcfs/juno/junogpu/liuyan2016/cor-ana/Job.sh $i
done  
