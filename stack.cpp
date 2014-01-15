#ifndef _EULER_STACK_CPP
#define _EULER_STACK_CPP
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

Stack::Stack():data(NULL),len(0),capacity(INIT_STACK_SIZE)
{
	data = (void **)malloc(INIT_STACK_SIZE*sizeof(void *));

	assert(data);
}

Stack::~Stack()
{
	if(data) delete data;

	len = 0;
}

bool Stack::empty() const
{
	return (len==0);
}
size_t Stack::size() const
{
	return len;
}

void * Stack::top()
{
	if(len>0)
		return data[len-1];
	return NULL;
}
void Stack::pop()
{
	if(len>0)
		data[--len] = 0;
}
void Stack::push(void *elem)
{
	if(len >= capacity){
		void ** tmp = (void **)realloc(data,capacity*2*sizeof(void *));
		data = tmp;
		assert(data);
	}

	data[len++] = elem;
}

#endif
