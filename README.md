# 479-project-1

## Description
Our algorithm selects the second largest value as the leader. The solution for the sequential algorithm is here: Solution here https://www.geeksforgeeks.org/find-second-largest-element-array/ but we consider a parallel program that uses MPI primitives to communicate among processes, and each process has a single generated ID.
Consider the ring communication shown in class, when the process of rank 0 sends a message to the process of rank 1, and that message is forwarded to the process of rank 2, etc. until it reaches back the process of rank 0: we can simplify that by saying that
the process of rank k (k>0) receives the message from the process of rank (k-1) modulo n and 
the process of rank k (k=0) sends a message to the process of rank (k+1) modulo n.

Each process will send a unique 5-digit ID NNDRR number to the process next in the ring . The 5-digit ID is computed as follows:
The first two digits NN is a randomly generated number by the process; the process generates a random number in the interval 10..99 and:
If the value is negative, then take the absolute value of it
If the value is less than 10, then add 10 to it
If the value is greater than 100, then take modulo 100
OR find a formula to make it exactly in the range 10..99
The third digit D represents the mod 2 of the random value generated earlier NN.
The last two digits RR represent the rank. Since the number of processes in the ring must be greater than 5, if the rank is one digit (e.g. rank 5) then left-pad it with one 0’s (.e.g 05).



## How To Run Project
1. Download project.cc file from github
2. In terminal, write mpic++ project1.cc -o project1
3. Then to execute code, mpirun -n 10<no of processor> project1

