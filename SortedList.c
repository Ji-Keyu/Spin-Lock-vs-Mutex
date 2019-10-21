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

void SortedList_insert(SortedList_t *list, SortedListElement_t *element)
{
	
	SortedListElement_t *tracker = list->next;
	while((tracker != list) && (strcmp(tracker->key, element->key) <0))
		tracker = tracker->next;

	if (opt_yield & INSERT_YIELD)
		sched_yield();
	tracker->prev->next = element;
	element->prev = tracker->prev;
	element->next = tracker;
	tracker->prev = element;
}

int SortedList_delete(SortedListElement_t *element)
{
	if (element->next->prev != element || element->prev->next != element)
		return 1;

	if (opt_yield & DELETE_YIELD)
		sched_yield();
	element->next->prev = element->prev;
	element->prev->next = element->next;
	return 0;
}

SortedListElement_t *SortedList_lookup(SortedList_t *list, const char *key)
{
	if (list->next->key == NULL)
		return NULL;
	SortedListElement_t *tracker = list->next;
	while (tracker->key != NULL)
	{
		if (opt_yield & LOOKUP_YIELD)
			sched_yield();
		if ((strcmp(tracker->key, key)) == 0)
			return tracker;
		tracker = tracker->next;
	}
	return NULL;
}

int SortedList_length(SortedList_t *list)
{
	if (list == NULL || list->next->key == NULL)
	{
		if (list->prev->key != NULL)
			return -1;
		else
			return 0;
	}
	int counter = 0;
	SortedListElement_t *tracker = list->next;
	
	while (tracker != list)
	{
		if (opt_yield & LOOKUP_YIELD)
			sched_yield();
		if (tracker->next->prev != tracker || tracker->prev->next != tracker)
			return -1;
		counter++;
		tracker = tracker->next;
	}
	return counter;
}