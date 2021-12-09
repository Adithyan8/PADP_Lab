# PADP_Lab
#To run mpi programs

Compile : mpicc filename.c

Execute : mpirun -np 4 a.out

#To run Openmp programs

Compile : gcc -fopenmp filename.c (For C) / g++ -fopenmp filename.cpp (For C++)

Execute : ./a.out
