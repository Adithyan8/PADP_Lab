#include<stdio.h>
#include<mpi.h>
#include<string.h>

char temp[3][20] = {"Hello","CSE","RVCE"};
int main(int argc,char **argv)
{
    int rank,npr;
    char *msg;
    MPI_Init(&argc,&argv);
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&npr);

    if(rank == 0)
    {
        for(int i=0;i<npr;i++)
        {
            strcpy(msg,temp[i-1]);
            MPI_Send(&msg,32,MPI_CHAR,i,0,MPI_COMM_WORLD)
        }
    }
    else{
        MPI_Recv(&msg,32,MPI_CHAR,0,0,MPI_COMM_WORLD,&status);
        printf("%s was sent by process with rank %d to process with rank %d\n",msg,rank,0);
    }
    MPI_Finalize();
    return 0;
}