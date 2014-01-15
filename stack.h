#ifndef _EULER_STACK_H
#define _EULER_STACK_H
/*
empty() 堆栈为空则返回真 
pop() 移除栈顶元素 
push() 在栈顶增加元素 
size() 返回栈中元素数目 
top() 返回栈顶元素 
*/

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
