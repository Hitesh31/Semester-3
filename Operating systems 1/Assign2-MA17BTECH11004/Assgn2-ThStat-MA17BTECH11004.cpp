#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <cmath>
using namespace std;
long double mean=0;	/* mean value of the numbers */
long double median;	/* the median of the numbers */
long double standard_deviation;	/* the standard deviation of the numbers */
long double variance=0; /* the variance of the numbers */
int n;
long double *a;
/* function to calculate the mean */
void *worker_mean(void *param) 
{
	for(int i=0;i<n;i++)
	{
		mean=mean+a[i];
	}
	mean=mean/n;
	pthread_exit(NULL);
}
/* function to calculate the median */
void *worker_median(void *param) 
{
	long double *arr;
	arr=(long double*)malloc(n*sizeof(long double));
	for(int i=0;i<n;i++)
		arr[i]=a[i];
	sort(arr,arr+n);
	median=(arr[n/2]+arr[(n-1)/2])/2;
	free(arr);
	pthread_exit(NULL);
}
/* function to calculate standard deviation */
void *worker_standard_deviation(void *param) 
{
	long double temp=0;
	for(int i=0;i<n;i++)
		temp=temp+a[i];
	temp=temp/n;
	for(int i=0;i<n;i++)
	{
		variance=variance+(a[i]-temp)*(a[i]-temp);
	}
	variance=variance/n;
	standard_deviation=sqrt(variance);
	pthread_exit(NULL);
}
int main(int argc, char *argv[]) 
{
	cin>>n;
	a=(long double*)malloc(n*sizeof(long double));
	for(int i=0;i<n;i++)
		cin>>a[i];
	pthread_t thread1,thread2,thread3;
	/* initialize and launch the threads */
	pthread_create(&thread1, NULL, worker_median,(void *)&a[0]);
	pthread_create(&thread2, NULL, worker_mean,(void *)&a[0]);
	pthread_create(&thread3, NULL, worker_standard_deviation,(void *)&a[0]);
	/* wait for thread completion */
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL); 
	pthread_join(thread3, NULL);
	/* print statistical values */
	cout<<"The average value is "<<mean<<endl;
	cout<<"The standard deviation value is "<<standard_deviation<<endl;
	cout<<"The median value is "<<median<<endl;
	free(a);
	return 0;
}
