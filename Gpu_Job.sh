#! /bin/bash
######## Part 1 #########
# Script parameters     #
#########################
  
# Specify the partition name from which resources will be allocated, mandatory option
#SBATCH --partition=gpu
  
# Specify the QOS, mandatory option
#SBATCH --qos=debug
  
# Specify which group you belong to, mandatory option
# This is for the accounting, so if you belong to many group,
#SBATCH --account=junogpu
  
# Specify your job name, optional option, but strongly recommand to specify some name
#SBATCH --job-name=tt_se
  
# Specify how many cores you will need, default is one if not specified
#SBATCH --ntasks=8
  
# Specify the output file path of your job
# Attention!! Your afs account must have write access to the path
# Or the job will be FAILED!
##Or  SBATCH --output=/hpcfs/juno/junogpu/liuyan2016/cor-ana/gpujob-%j.out
##Or  SBATCH --error=/hpcfs/juno/junogpu/liuyan2016/cor-ana/gpujob-%j.err
  
# Specify memory to use, or slurm will allocate all available memory in MB
#SBATCH --mem-per-cpu=4G

# Specify how many GPU cards to use
######## Part 2 ######
# Script workload    #
######################
  
# Replace the following lines with your real workload
  
# list the allocated hosts
echo CUDA_VISIBLE_DEVICES $CUDA_VISIBLE_DEVICES
cd /hpcfs/juno/junogpu/liuyan2016/cor-ana
source setup.sh
#var=$RANDOM
#(/usr/bin/time -v python /hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/run.py --sel 1 --ana 1)>&/hpcfs/juno/junogpu/liuyan2016/cor-ana/logTimer/log_timer_1_1_${1}.txt
(/usr/bin/time -v python /hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/run_mtana.py --ana 2)>&/hpcfs/juno/junogpu/liuyan2016/cor-ana/logTimer/log_timer_0_2_1.txt
#source /hpcfs/juno/junogpu/liuyan2016/mt-sniper
#python /hpcfs/juno/junogpu/liuyan2016/mt-sniper/MtIOExample/share/run.py>&/hpcfs/juno/junogpu/liuyan2016/cor-ana/logTimer/log_test_1${1}.txt
