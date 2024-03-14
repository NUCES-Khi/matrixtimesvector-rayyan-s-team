[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-7f7980b617ed060a017424585567c406b6ee15c891e84e1186181d67ecf80aa0.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=14276170)
# PDC Assignments and Projects
## Team Members
|std_id|Name|
|--------|-|
|k21-3079|Rayyan Ahmed|
|k21-3051|Shaikh Abdul Rafay|
|k21-3072|Minal Alam|

# Assignments 1 ##
Status: **Completed**

## System Specification 
- Intel(R) Core(TM) i7-4770K CPU @ 3.50GHz
- 16.0 GB (15.9 GB usable)
- 64-bit operating system, x64-based processor
- Number of processors on which MPI was executed was 4

### Shell Compliling all 5 Programs
![image](https://github.com/NUCES-Khi/matrixtimesvector-rayyan-s-team/assets/127647228/0450872d-3ceb-47d8-abca-37e5908a2afc)

### CSV File
![image](https://github.com/NUCES-Khi/matrixtimesvector-rayyan-s-team/assets/127647228/32484966-7a7c-4a12-a727-48be1db692e8)
### Variable description
- Size: Size of Matrix
- MPIN: MPI_Naive
- OMPT: Open_MP_Tiling
- ompN: Opne_MP_Naive
- MPIT: MPI_Tiling
- seq: Sequential

### Line Graph
![image](https://github.com/NUCES-Khi/matrixtimesvector-rayyan-s-team/assets/127647228/d6369245-40f0-4fb8-9bec-fde42b532f19)

## Conclusion
- OMP_Naive and OMP_tiling produce the same results
- MPI_tiling performed the best with the lowest time taken for each size of matrix
- MPI_Naive produced even worse than sequential
- With small matrix size we are not getting any speedup with parallel programs


## Assignment 2 ##
Status: **Not assigned yet**
