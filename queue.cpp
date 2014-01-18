#ifndef _EULER_QUEUE_CPP
#define _EULER_QUEUE_CPP

#include <assert.h>
#include <stdio.h>
#include "queue.h"

Queue::Queue(): head(NULL),tail(NULL),len(0)
{
}

Queue::~Queue()
{
	Qlist *p = head,*q = head;

	while(p){
		q = p;
		p = p->next;
		delete q;
	}
}

void *Queue::back()
{
	if( tail)
		return tail->data;

	return NULL;
}
void *Queue::front()
{
	if( head)
		return head->data;

	return NULL;
}

bool Queue::empty()const
{
	return (len==0);
}

size_t Queue::size() const
{
	return len;
}

void Queue::pop()
{
	Qlist *p = head;
	if(p){
		head = head ->next;
		delete p;

		--len;
	}
}

void Queue::push(void * elem)
{
	Qlist *p = new Qlist();
	assert(p);
	
	p->data = elem;
	p->next = NULL;
	
	++len;

	if(head == NULL){
		head = p;
		tail = head;
	}else{
		tail->next = p;
		tail = p;
	}
}

#endif

