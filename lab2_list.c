/*
NAME: Keyu Ji
EMAIL: g.jikeyu@gmail.com
ID: 704966744
*/

#include <stdio.h>
#include <stdlib.h>
//#include <sys/stat.h>
//#include <sys/types.h>
#include <sys/wait.h>
//#include <sys/time.h>
//#include <sys/resource.h>
#include <time.h>
#include <ctype.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <signal.h>
#include <errno.h>
#include <pthread.h>
#include "SortedList.h"

char sync_opt = 0;
int opt_yield = 0;
pthread_mutex_t *mutex; 
int *spinlock;
static const int key_length = 5;
int num_lists = 1;

unsigned long hash(const char *str) // adapted from http://www.cse.yorku.ca/~oz/hash.html
{
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

typedef struct {
	SortedList_t *list;
	SortedList_t *elements;
	int iterations;
	struct timespec start, finish;
	long long time;
} t_func_arg;

void *t_func(void *a)
{
	t_func_arg *b = (t_func_arg *)a;
	switch(sync_opt)
	{
		case 'm':
		{
			for (int i = 0; i < b->iterations; ++i)
			{
				unsigned long nlist = hash(b->elements[i].key) % num_lists;
				clock_gettime(CLOCK_REALTIME, &(b->start));
				pthread_mutex_lock(mutex+nlist);
				clock_gettime(CLOCK_REALTIME, &(b->finish));
				(*b).time += b->finish.tv_sec*1000000000 + b->finish.tv_nsec - b->start.tv_sec*1000000000 - b->start.tv_nsec;
				SortedList_insert(b->list+nlist, b->elements+i);
				pthread_mutex_unlock(mutex+nlist);
			}
			
			long long length;
			for (int i = 0; i < num_lists; ++i)
			{
				clock_gettime(CLOCK_REALTIME, &(b->start));
				pthread_mutex_lock(mutex+i);
				clock_gettime(CLOCK_REALTIME, &(b->finish));
				(*b).time += b->finish.tv_sec*1000000000 + b->finish.tv_nsec - b->start.tv_sec*1000000000 - b->start.tv_nsec;
				length = SortedList_length(b->list+i);
				pthread_mutex_unlock(mutex+i);
				if (length == -1)
				{
					fprintf(stderr, "list corrupted in length func\n");
					exit(2);
				}
			}
			for (int i = 0; i < b->iterations; ++i) //!!!
			{
				unsigned long nlist = hash(b->elements[i].key) % num_lists;
				clock_gettime(CLOCK_REALTIME, &(b->start));
				pthread_mutex_lock(mutex+nlist);
				clock_gettime(CLOCK_REALTIME, &(b->finish));
				(*b).time += b->finish.tv_sec*1000000000 + b->finish.tv_nsec - b->start.tv_sec*1000000000 - b->start.tv_nsec;
				SortedListElement_t *target = SortedList_lookup(b->list+nlist, b->elements[i].key);
				if (target == NULL)
				{
					fprintf(stderr, "list corrupted in lookup func\n");
					exit(2);
				}
				else
				{
					int rc = SortedList_delete(target);
					pthread_mutex_unlock(mutex+nlist);
					if(rc)
					{
						fprintf(stderr, "list corrupted in delete func, %d\n", i);
						exit(2);
					}
				}
			}
		}
		break;

		case 's':
		{
			for (int i = 0; i < b->iterations; ++i)
			{
				clock_gettime(CLOCK_REALTIME, &(b->start));
				unsigned long nlist = hash(b->elements[i].key) % num_lists;
				while(__sync_lock_test_and_set(spinlock+nlist, 1))
				{continue;}
				clock_gettime(CLOCK_REALTIME, &(b->finish));
				(*b).time += b->finish.tv_sec*1000000000 + b->finish.tv_nsec - b->start.tv_sec*1000000000 - b->start.tv_nsec;
				SortedList_insert(b->list+nlist, &(b->elements[i]));
				__sync_lock_release (spinlock+nlist);
			}

			long long length;
			for (int i = 0; i < num_lists; ++i)
			{
				clock_gettime(CLOCK_REALTIME, &(b->start));
				while(__sync_lock_test_and_set(spinlock+i, 1))
				{continue;}
				clock_gettime(CLOCK_REALTIME, &(b->finish));
				(*b).time += b->finish.tv_sec*1000000000 + b->finish.tv_nsec - b->start.tv_sec*1000000000 - b->start.tv_nsec;
				length = SortedList_length(b->list+i);
				__sync_lock_release (spinlock+i);
				if (length == -1)
				{
					fprintf(stderr, "list corrupted in length func\n");
					exit(2);
				}
			}
			
			
			for (int i = 0; i < b->iterations; ++i)
			{
				unsigned long nlist = hash(b->elements[i].key) % num_lists;
				clock_gettime(CLOCK_REALTIME, &(b->start));
				while(__sync_lock_test_and_set(spinlock+nlist, 1))
				{continue;}
				clock_gettime(CLOCK_REALTIME, &(b->finish));
				(*b).time += b->finish.tv_sec*1000000000 + b->finish.tv_nsec - b->start.tv_sec*1000000000 - b->start.tv_nsec;
				SortedListElement_t *target = SortedList_lookup(b->list+nlist, b->elements[i].key);
				if (target == NULL)
				{
					fprintf(stderr, "list corrupted in lookup func\n");
					exit(2);
				}
				else
				{
					int rc = SortedList_delete(target);
					__sync_lock_release (spinlock+nlist);
					if(rc)
					{
						fprintf(stderr, "list corrupted in delete func, %d\n", i);
						exit(2);
					}
				}
			}
		}
		break;

		case 0:
		{
			for (int i = 0; i < b->iterations; ++i)
			{
				unsigned long nlist = hash(b->elements[i].key) % num_lists;
				SortedList_insert((b->list+nlist), &(b->elements[i]));
			}

			for (int i = 0; i < num_lists; ++i)
			{
				if (SortedList_length(b->list+i) == -1)
				{
					fprintf(stderr, "list corrupted in length func\n");
					exit(2);
				}
			}
				
			for (int i = 0; i < b->iterations; ++i)
			{
				unsigned long nlist = hash(b->elements[i].key) % num_lists;
				SortedListElement_t *target = SortedList_lookup((b->list+nlist), b->elements[i].key);
				if (target == NULL)
				{
					fprintf(stderr, "list corrupted in lookup func\n");
					exit(2);
				}
				else
				{
					if(SortedList_delete(target))
					{
						fprintf(stderr, "list corrupted in delete func\n");
						exit(2);
					}
				}
			}
		}
		break;
	}
	return NULL;
}

void handler(int signum)
{
	fprintf(stderr, "signal %d caught\n", signum);
	exit(2);
}

int main(int argc, char* const argv[])
{
	struct sigaction act;
	act.sa_handler = handler;
	sigaction(SIGSEGV, &act, NULL);
	int option;
	pthread_t num_threads = 1;
	long num_iterations = 1;
	static struct option long_options[] = {
		{"iterations",	required_argument, 	0,  'i'},
		{"threads",		required_argument, 	0,  't'},
		{"yield",		required_argument, 	0,	'y'},
		{"sync",		required_argument,	0,	's'},
		{"lists",		required_argument, 	0,	'l'}
	};
	int long_index = 0;
	while ((option = getopt_long(argc, argv, "", long_options, &long_index)) && (option != -1))
	{
		switch(option)
		{
		case 'i':
			if (atoi(optarg) < 0)
			{
				fprintf(stderr, "invalid argument for number of iterations! exiting\n");
				exit(1);
			}
			num_iterations = atoi(optarg);
			break;
		case 't':
			if (atoi(optarg) < 0)
			{
				fprintf(stderr, "invalid argument for number of threads! exiting\n");
				exit(1);
			}
			num_threads = atoi(optarg);
			break;
		case 'y':
			for (size_t i = 0; i < strlen(optarg); ++i)
			{
				if (optarg[i] != 'i' && optarg[i] != 'd' && optarg[i] != 'l')
				{
					fprintf(stderr, "invalid argument for yield!\n");
					exit(2);
				}
				if (optarg[i] == 'i')
					opt_yield |= INSERT_YIELD;
				if (optarg[i] == 'd')
					opt_yield |= DELETE_YIELD;
				if (optarg[i] == 'l')
					opt_yield |= LOOKUP_YIELD;
			}
			break;
		case 's':
			if (optarg[0] != 'm' && optarg[0] != 's')
			{
				fprintf(stderr, "invalid argument for sync! exiting\n");
				exit(1);
			}
			sync_opt = optarg[0];
			break;
		case 'l':
			if (optarg[0] <= 0)
			{
				fprintf(stderr, "invalid argument for lists! exiting\n");
				exit(1);
			}
			num_lists = atoi(optarg);
			break;
		case '?':
			fprintf(stderr, "Unrecognized option, exiting\n");
			exit(1);
			break;
		}
	}

	if (sync_opt == 'm')
	{
		mutex = malloc(num_lists * sizeof(pthread_mutex_t));
		for (int i = 0; i < num_lists; ++i)
		{
			if (pthread_mutex_init(mutex+i, NULL))
			{
				fprintf(stderr, "mutex init failed\n");
				exit(1);
			}
		}
	}
	else if (sync_opt == 's')
	{
		spinlock = malloc(num_lists * sizeof(int));
		for (int i = 0; i < num_lists; ++i)
			spinlock[0] = 0;
	}

	SortedList_t *head = malloc(num_lists *sizeof(SortedList_t));
	if (head == NULL) {
		fprintf(stderr, "Unable to allocate memory.\n");
		fflush(stderr);
		exit(1);
	}
	for (int i = 0; i < num_lists; ++i)
	{
		(head+i)->next = (head+i); //!!!
		(head+i)->prev = (head+i);
		(head+i)->key = NULL;
	}

	long long num_elements = num_threads * num_iterations;
	SortedList_t *elements = malloc(num_elements *sizeof(SortedListElement_t));
	
	for (long long i = 0; i < num_elements; ++i)
	{		
		char *tmp = malloc(key_length * sizeof(char));
		for (int k = 0; k < key_length; ++k)
			tmp[k] = rand() % 256;
		elements[i].key = tmp;
	}
	pthread_t thread_id[num_threads];
	int rc;
	struct timespec start, finish;
	clock_gettime(CLOCK_REALTIME, &start);

	t_func_arg *args = malloc(num_threads*sizeof(t_func_arg)); //!!!
	for (unsigned int i = 0; i < num_threads; ++i) //!!!
	{
		args[i].list = head;
		args[i].elements = (elements + i*num_iterations);
		args[i].iterations = num_iterations;
		args[i].time = 0;
		int rc = pthread_create(&thread_id[i], NULL, t_func, &args[i]);
		if (rc)
		{
			fprintf(stderr, "Error on creation of thread, with code %d\n", rc);
			exit(1);
		}
	}


	for (unsigned int i = 0; i < num_threads; ++i)
	{
		rc = pthread_join(thread_id[i], NULL);
		if (rc)
		{
			fprintf(stderr, "Error on joining of thread, with code %d\n", rc);
			exit(1);
		}
	}
	
	clock_gettime(CLOCK_REALTIME, &finish);
	long long num_ops = num_threads*num_iterations*3;
	long long time_total = finish.tv_sec*1000000000 + finish.tv_nsec - start.tv_sec*1000000000 - start.tv_nsec;
	long long time_average = time_total / num_ops;
	long long waittime_total = 0;
	for (unsigned int i = 0; i < num_threads; ++i)
		waittime_total += args[i].time;
	long long waittime_average = waittime_total / ((num_iterations * 2 + 1)* num_threads);

	if (SortedList_length(head) != 0)
	{
		fprintf(stderr, "list corrupted\n");
		free(head);
		exit(2);
	}

	printf("list");
	if (opt_yield)
	{
		printf("-");
		if (opt_yield & INSERT_YIELD)
			printf("i");
		if (opt_yield & DELETE_YIELD)
			printf("d");
		if (opt_yield & LOOKUP_YIELD)
			printf("l");
	}
	else
		printf("-none");
	if (sync_opt)
		printf("-%c", sync_opt);
	else
		printf("-none");
	printf(",%ld,%ld,%d,%lld,%lld,%lld,%lld\n", num_threads, num_iterations, num_lists, num_ops, time_total, time_average, waittime_average);
	free(head); //free other stuff
	exit(0);
}
