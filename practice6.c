#include<stdio.h>
#include<omp.h>
#include<string.h>

int word_search(char *search_word)
{
    int word_count=0;
    FILE *f = fopen("words.txt","r");
    char temp[10];
    while(feof(f)==0)
    {
        fscanf(f,"%s",temp);
        if(strcmpi(temp,search_word)==0)
            word_count++;
    }
    fclose(f);
    return word_count;
}

int main()
{
    char* search_words[3] = {"padp", "laptop", "ghi"};
    int count[3], i;
    for(int t = 1; t <= 8; t*=2)
    {
        double start = omp_get_wtime(),end;
        omp_set_num_threads(t);
        #pragma omp parallel for private(i)
        for(i=0;i<3;i++)
        {
            count[i] = word_search(search_words[i]);
        }

        end = omp_get_wtime();
        printf("Time taken by %d threads : %lf\n",t,end-start);
        for(int i=0;i<3;i++)
            printf("%s : %d\n",search_words[i],count[i]);
    }
    return 0;
}