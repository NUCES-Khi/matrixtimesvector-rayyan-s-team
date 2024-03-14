# Assignment 1

## Team Members
|std_id|Name|
|--------|-|
|k21-3079|Rayyan Ahmed|
|k21-3051|Shaikh Abdul Rafay|
|k21-3072|Minal Alam|
## System Specification 
- Intel(R) Core(TM) i7-4770K CPU @ 3.50GHz
- 16.0 GB (15.9 GB usable)
- 64-bit operating system, x64-based processor
- Number of processors on which MPI was executed was 4
## Output Screenshots
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

## Results and Analysis
- OMP_Naive and OMP_tiling produce the same results
- MPI_tiling performed the best with the lowest time taken for each size of matrix
- MPI_Naive produced even worse than sequential
- With small matrix size we are not getting any speedup with parallel programs

## Major Problems Encountered
1 - Syntax Errors:
One of the primary challenges faced was the occurrence of syntax errors when attempting to run the shell script. These errors manifested as "syntax error: operand expected" or "syntax error: syntax error" messages during script execution. Despite verifying the syntax, the errors persisted, leading to uncertainty about the root cause.

2 - Debugging MPI and OpenMP Invocation:
Debugging the invocation of MPI and OpenMP programs within the shell script posed a challenge. Ensuring the correct command-line arguments and appropriate execution environment for these parallel programs required meticulous attention to detail. Incorrect invocation resulted in unexpected behavior and erroneous results.

3 - Ensuring Consistent Execution:
Achieving consistent execution of MPI and OpenMP programs across multiple runs proved challenging. Variability in execution times due to system load, resource contention, or other environmental factors made it difficult to obtain reliable performance measurements. Ensuring that each program executed under similar conditions for accurate comparison demanded careful consideration.

4 - Automation Complexity:
The complexity of automating the execution of multiple MPI and OpenMP programs across different input sizes added to the challenge. Coordinating the execution of various programs, handling input data, capturing execution times, and aggregating results required a robust and well-structured approach. Balancing automation efficiency with flexibility for future modifications was a key consideration.
