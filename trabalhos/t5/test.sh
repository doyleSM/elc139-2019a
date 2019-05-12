
#!/bin/bash
#SBATCH -J test           # job name
#SBATCH -o test%j.out       # output file name (%j expands to jobID), this file captures standered output from the shell
#SBATCH -e test%j.err      # error file name (%j expands to jobID), this file captures standered errors genereted from the program
#SBATCH  --nodes  8        # total number of nodes requested
#SBATCH --ntasks-per-node 2 # total number cores requested per node. Using this option and --node option above you could fine tune resource requests.
#SBATCH -p qCDER            # partition --qCDER (to find out available partitions please run 'sinfo' command)
#SBATCH --mem-per-cpu=3000   # request specific amount of RAM per CPU, now since we request 16 cores, the total amount of memory avilable for the program is 48GB
#SBATCH --gres=gpu:1      # request gpus for the job,if needed, otherwise remove this line
#SBATCH -t 01:30:00       # run time (hh:mm:ss) - 1.5 hours
 
## Included any modules that may be required for your job. in this example load MPI module
module load Compilers/mvapich2_ACoRE
 
 
# execute any program
#to run MPI program
srun --mpi=pmi2 ./a.out