#include<stdio.h>
#include<omp.h>
#include<time.h>
#include<stdlib.h>

int main()
{
    for(int t=1;t<=8;t*=2)
    {
        for(int tr=1000;tr<=1000000;tr*=10)
        {
            double start = omp_get_wtime(),end;
            srand(35791246);
            omp_set_num_threads(t);
            int count=0;
            #pragma omp parallel for
            for(int i=0;i<tr;i++)
            {
                double x = (double)rand()/RAND_MAX;
                double y = (double)rand()/RAND_MAX;
                double z = x*x + y*y;
                if(z<=1) count++;
            }
            printf("Value of PI : %lf, number of trials : %d\n",4*((double)count/tr),tr);
            end = omp_get_wtime();
            printf("Time taken by %d threads : %lf\n",t,end-start);
        }
    }
}