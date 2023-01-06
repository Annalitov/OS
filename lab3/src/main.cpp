#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <chrono>
#include <ctime> 


using namespace std;

int array_size;
int n_threads;

int part=0;
int* a ;


void merge(int low, int mid, int high)
{
    int n1 = mid - low + 1, nr = high - mid, i, j;
    
    int* left = (int*)calloc(n1,sizeof(int));
    int* right = (int*)calloc(nr,sizeof(int));
    
    for(i = 0; i < n1; i++)
        left[i] = a[i + low];
    
    for(i = 0; i < nr; i++)
        right[i] = a[i + mid + 1];
    
    int k = low;
    i = j = 0;
    
    while(i < n1 && j < nr)
    {
        if(left[i] <= right[j])
            a[k++] = left[i++];
        else
            a[k++] = right[j++];
    }
    
    while(i < n1) {
        a[k++] = left[i++];
    }
    
    while(j < nr) {
        a[k++] = right[j++];
    }
    
}


void merge_sort(int low, int high)
{
    int mid = low + ((high - low) / 2);
    if(low < high) {
        
        merge_sort(low, mid);
        
        merge_sort(mid + 1, high);

        merge(low, mid, high);
    }
}


void* merge_sort_tread(void *args)
{
    int thread_part = part;
    part+=1;

    int low = thread_part * (array_size / n_threads);
    int high = (thread_part + 1) * (array_size / n_threads) - 1;
    
    int mid = low + (high - low) / 2;
    
    if(low < high)
    {
        merge_sort(low, mid);
        merge_sort(mid + 1, high);
        merge(low, mid, high);
    }
    return 0;
    
}



void merge_rec(int tread_m)
{
    if(tread_m>n_threads)
        return;
    
    merge_rec(tread_m*2);
    
    int minsize = array_size/tread_m;
    
    for(int i=0;i<tread_m;i++)
    {
        
        int low = i * minsize;
        int high = (i + 1) * (minsize) - 1;
        int mid = low + (high - low) / 2;
        
        merge(low, mid, high);
    }
    
}

int main()
{
	cout<<"Enter the number of threads: ";
	cin>>n_threads;
	cout<<endl;

	cout<<"Enter the array size: ";
	cin>>array_size;
    
    
    a = (int*)calloc(array_size,sizeof(int));
    cout<<"The input array: ";
    int i;
    srand(time(NULL));
    for( i=0; i < array_size; i++)
    {
        a[i] = rand() % array_size;
        cout<<a[i]<<" ";
    }
    cout<<"\n";

    pthread_t threads[n_threads];
    int status;

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    for(int i = 0; i < n_threads; i++)
    {
        cout<<"part- "<< part << endl;
        
        status = pthread_create(&threads[i], NULL, merge_sort_tread, NULL);
        if (status != 0)
            cout<<"main error: can't create thread, status = "<< status <<endl;

    }
    for(int i = 0; i < n_threads; i++)
        pthread_join(threads[i], NULL);

    merge_rec(2);
    merge(0, (array_size - 1)/2, array_size - 1);  
    chrono::steady_clock::time_point end = chrono::steady_clock::now(); 

    cout<<"The output array: "<<endl;
    for(int i = 0; i < array_size; i++)
        cout<<a[i]<<endl;
    
    cout<<"The number of threads:"<<n_threads<<endl;
    cout<<chrono::duration_cast<chrono::microseconds>(end-begin).count()<<endl;
    return 0;
}

