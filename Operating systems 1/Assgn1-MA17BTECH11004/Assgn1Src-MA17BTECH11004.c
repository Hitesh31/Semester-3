#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <wait.h>


/*------------	Output the elapsed time from the start time to the end time.
				A negative value of the elapsed time will be reported
				if the end time is earlier than the start time.-------------*/

double get_elapsed_time(struct timeval *start_time, struct timeval *end_time) 
{
	double elapsed_seconds = end_time->tv_sec - start_time->tv_sec;
	elapsed_seconds += (double)(end_time->tv_usec - start_time->tv_usec) / 1e6;
	return elapsed_seconds;
}

int main(int argc, char* argv[]) 
{
	if(argc < 2) 
	{
		fprintf(stderr, "Provide command as: %s <command>\n", argv[0]);
		return 1;
	}

	int fd;
	struct timeval* start_time_ptr, end_time;
	const char* shm_name = "start_time";
	size_t SIZE = sizeof (struct timeval);
	pid_t pid;

	fd = shm_open(shm_name, O_RDWR | O_CREAT, 0666); // Opened shared memory in read and write mode
	if(fd < 0) 
	{
		perror("shm_open");
		return 1;
	}

	ftruncate(fd,SIZE); 
	 if(ftruncate(fd, SIZE) < 0) // Limited the shared size of memory to the size of struct timeval
	 {
	 	perror("ftruncate");
	 	return 1;
	 }

	start_time_ptr = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); // Created a mapping to file
	if(start_time_ptr == MAP_FAILED) 
	{
		perror("mmap");
		return 1;
	}
	pid = fork();	// Create a child process 
	if(pid < 0) 
	{
		perror("fork");
		shm_unlink(shm_name);
		return 1;
	}
	else if(pid == 0) 
	{ // child process 
		gettimeofday(start_time_ptr, NULL);
		if(execvp(argv[1], &argv[1]) < 0) 
		{
			return 1;
		}
	}
	else 
	{ // parent process 
		wait(NULL);
		gettimeofday(&end_time, NULL);
		printf("Elapsed time: %lfs\n", get_elapsed_time(start_time_ptr, &end_time));
	}

	shm_unlink(shm_name);
	return 1;
}