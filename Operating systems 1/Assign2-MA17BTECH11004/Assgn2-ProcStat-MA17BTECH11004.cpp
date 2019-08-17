#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <stdio.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <wait.h>
using namespace std;
int n;
long double *a;
struct stats
{
	long double mean;	/* mean value of the numbers */
	long double median;	/* the median of the numbers */
	long double standard_deviation;	/* the standard deviation of the numbers */
};
long double mean_cal()
{
	long double mean=0;
	for(int i=0;i<n;i++)
	{
		mean=mean+a[i]; //calculating mean
	}
	mean=mean/n;
	return mean;
}
long double median_cal()
{
	long double median;
	long double *arr; //make new array so if we sort then the original array remains same
	arr=(long double*)malloc(n*sizeof(long double));
	for(int i=0;i<n;i++)
		arr[i]=a[i];	//copy the array in oher array 
	sort(arr,arr+n);	//sort the new array
	median=(arr[n/2]+arr[(n-1)/2])/2;
	free(arr);
	return median;
}
long double standard_deviation_cal()
{	
	long double value=0;
	for(int i=0;i<n;i++)
		value=value+a[i];
	value=value/n;
	long double variance=0;
	for(int i=0;i<n;i++)
	{
		variance=variance+(a[i]-value)*(a[i]-value); //here value is mean
	}
	variance=variance/n; //calculating variance using mean
	long double standard_deviation=sqrt(variance); //here value is variance
	return standard_deviation;
}
int main()
{
	cin>>n;
	a=(long double*)malloc(n*sizeof(long double));
	for(int i=0;i<n;i++)
		cin>>a[i];
	int fd;
	struct stats *ptr;
	const char* shm_name = "Process";
	size_t SIZE=sizeof(struct stats);	//create size of "stuct stats" in the memory
	fd = shm_open(shm_name, O_RDWR | O_CREAT, 0666); // Opened shared memory in read and write mode
	ftruncate(fd,SIZE); 
	if(ftruncate(fd, SIZE) < 0) // Limited the shared size of memory to the size of struct stats
	{
		perror("ftruncate");
		return 1;
	}
	ptr = (struct stats *)mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); // Created a mapping to file
	pid_t pid;
	pid=fork(); /* fork a parent process*/
	if(pid < 0) 
	{
		perror("fork");
		shm_unlink(shm_name);
		return 1;
	}
	else if(pid==0)
	{
		pid=fork(); /*since pid of child is 0 now,fork the child process to make 2 processes*/
		if(pid < 0)
		{
			perror("fork");
			shm_unlink(shm_name);
		}
		else if(pid==0)
		{
			ptr->mean=mean_cal();	/* Use the child of child process to calculate mean*/
		}
		else
		{
			wait(NULL); 	/*wait for child's child process*/
			ptr->standard_deviation=standard_deviation_cal(); /*use the new child process to calculate SD*/
		}
	}
	else
	{
		wait(NULL); /*wait for the child process to complete*/
		pid=fork(); /*fork the parent again to make a child*/
		if(pid<0)
		{
			perror("fork");
			shm_unlink(shm_name);
		}
		else if(pid==0)
		{
			ptr->median=median_cal(); /*use the child process to calculate median*/
		}
		else
		{
			/*parent process to print the values as mentioned*/
			wait(NULL);
			cout<<"The average value is "<<ptr->mean<<endl;
			cout<<"The standard deviation value is "<<ptr->standard_deviation<<endl;
			cout<<"The median value is "<<ptr->median<<endl;	
			shm_unlink(shm_name);
			free(a);
		}
	}
	return 1;
}

