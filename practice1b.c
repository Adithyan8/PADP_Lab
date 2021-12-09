#include<stdio.h>
#include<mpi.h>

int main(int argc, char **argv)
{
    int rank,iter = 100000,count=0,reduced_count,reduced_iter;
    double start;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if(rank==0)
        start = MPI_Wtime();
    else{
        srand(31241217);
        for(int i=1;i<=iter;i++)
        {
            double x = (double)rand()/RAND_MAX;
            double y = (double)rand()/RAND_MAX;
            double z = x*x + y*y;
            if(z<=1) count++;
        }
    }
    MPI_Reduce(&count,&reduced_count,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    MPI_Reduce(&iter,&reduced_iter,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    if(rank==0)
    {
        double end = MPI_Wtime();
        double pi = 4* (double)count/iter;
        printf("Time taken : %lf, PI : %lf\n",end-start);
    }
    MPI_Finalize();
    return 0;
}