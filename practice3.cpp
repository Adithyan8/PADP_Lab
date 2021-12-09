#include<iostream>
#include<omp.h>
#include<math.h>
#include<string.h>

using namespace std;

double t=0;

long Strike(bool composite[],long start, long step, long limit)
{
    for(;start<=limit;start+=step)
        composite[start] = 1;
    return start;
}

long CacheUnfriendlySieve(long n)
{
    long count = 0, m = (long)sqrt((double(n)));
    bool *composite = new bool[n+1];
    memset(composite,0,n+1);

    t = omp_get_wtime();
    for(long i=2;i<=m;i++)
    {
        if(!composite[i])
        {
            ++count;
            Strike(composite,2*i,i,n);
        }
    }

    for(long i=m+1;i<=n;i++)
        if(!composite[i])
            ++count;
    
    t = omp_get_wtime() - t;
    delete[] composite;
    return count;
}

long CacheFriendlySieve(long n)
{
    long count = 0, m = (long)sqrt((double)n);
    bool *composite = new bool[n+1];
    memset(composite,0,n+1);
    long *striker = new long[m];
    long *factor = new long[m];
    long n_factor = 0;
    t = omp_get_wtime();
    for(long i=2;i<=m;i++)
    {
        if(!composite[i])
        {
            ++count;
            striker[n_factor] = Strike(composite,2*i,i,m);
            factor[n_factor++]=i;
        }
    }

    for(long window = m+1;window<=n;window+=m)
    {
        long limit = min(window+m-1,n);
        for(long k=0;k<n_factor;k++)
            striker[k] = Strike(composite,striker[k],factor[k],limit);
        for(long i=window;i<=limit;i++)
            if(!composite[i])
                ++count;
    }

    t = omp_get_wtime()-t;
    delete[] composite;
    delete[] factor;
    delete[] striker;
    return count;
}

long ParallelSieve(long n)
{
    long count=0, m=(long)sqrt((double)n);
    bool *composite = new bool[n+1];
    memset(composite,0,n+1);
    long *striker = new long[m];
    long *factor = new long[m];
    long n_factor = 0;
    t = omp_get_wtime();
    #pragma omp single
    for(long i=2;i<=m;i++)
    {
        if(!composite[i])
        {
            count++;
            striker[n_factor] = Strike(composite,2*i,i,m);
            factor[n_factor++] = i;
        }
    }

    #pragma omp parallel for
    for(long window = m+1;window<=n;window+=m)
    {
        long limit = min(window+m-1,n);
        for(long k=0;k<n_factor;k++)
            striker[k] = Strike(composite,striker[k],factor[k],limit);
        for(long i=window;i<=limit;i++)
            if(!composite[i])
                ++count;
    }
    t = omp_get_wtime() - t;
    delete[] composite;
    delete[] factor;
    delete[] striker;
    return count;
}

int main()
{
    for (long i = 100000000; i >= 1000000; i /= 10)
    {
        cout << "Input Size\t" << i << endl;
        long count1 = CacheUnfriendlySieve(i);
        cout << "Unfriendly\t" << count1 << "\t";
        cout << "Time:\t" << t << endl;

        long count2 = CacheFriendlySieve(i);
        cout << "Friendly\t" << count2 << "\t";
        cout << "Time:\t" << t << endl;

        long count3 = ParallelSieve(i);
        cout << "Parallel\t" << count3 << "\t";
        cout << "Time:\t" << t << endl;
    }
    return 0;
}