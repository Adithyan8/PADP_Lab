#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
    int **a,**b,**res,r1,r2,c1,c2,i,j,k;
    printf("Enter dim for A :\n");
    scanf("%d%d",&r1,&c1);
    printf("Enter dim for B :\n");
    scanf("%d%d",&r2,&c2);
    a = (int**)malloc(sizeof(int*)*r1);
    b = (int**)malloc(sizeof(int*)*r2);
    res = (int**)malloc(sizeof(int*)*r1);

    for(i=0;i<r1;i++)
    {
        a[i] = (int*)malloc(sizeof(int)*c1);
        res[i] = (int*)malloc(sizeof(int)*c2);
    }

    for(i=0;i<r2;i++)
        b[i] = (int*)malloc(sizeof(int)*c1);

    printf("Enter elements of matrix 1 : \n");
    for(i=0;i<r1;i++)
        for(j=0;j<c1;j++)
            a[i][j] = 0;
            //scanf("%d",&a[i][j]);

    printf("Enter elements of matrix 2 : \n");
    for(i=0;i<r2;i++)
        for(j=0;j<c2;j++)
            b[i][j] = 0;
            //scanf("%d",&b[i][j]);

    for(int t=1;t<=8;t*=2)
    {
        double start = omp_get_wtime(),end;
        int sum = 0;
        omp_set_num_threads(t);
        #pragma omp parallel for private(j,k)
        for(i=0;i<r1;i++)
            for(j=0;j<c2;j++)
            {
                sum=0;
                for(k=0;k<c1;k++)
                    sum += a[i][k]+b[k][j];
                res[i][j] = sum;
            }

        for(i=0;i<r1;i++)
        {
            for(j=0;j<c2;j++)
                printf("%d ",res[i][j]);
            printf("\n");
        }     
        end = omp_get_wtime();
        printf("Time taken by %d threads : %lf\n",t,end-start);        
    }
}