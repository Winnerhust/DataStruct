#ifndef _EULER_STACK_H
#define _EULER_STACK_H

#ifndef _SIZE_T_ 
#define _SIZE_T_
typedef unsigned long size_t;
#endif

#define INIT_STACK_SIZE 256

class Stack
{
public:
	Stack();
	~Stack();

	bool empty() const;
	void pop();
	void push(void *elem);
	size_t size() const;
	void *top();
private:
	void ** data;
	size_t len;
	size_t capacity;
};

#endif
