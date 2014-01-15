#ifndef _EULER_QUEUE_H
#define _EULER_QUEUE_H


#ifndef _SIZE_T_ 
#define _SIZE_T_
typedef unsigned long size_t;
#endif
/*
 *back() 返回最后一个元素 
 *empty() 如果队列空则返回真 
 *front() 返回第一个元素 
 *pop() 删除第一个元素 
 *push() 在末尾加入一个元素 
 *size() 返回队列中元素的个数 
 */
class Queue
{
public:
	Queue();
	~Queue();
	void *back();
	bool empty() const;
	void *front();
	void pop();
	void push(void *elem);
	size_t size() const;
private:
	typedef struct Qlist{
		void *data;
		struct Qlist *next;
	}Qlist;
	Qlist *head,*tail;
	size_t len;
};

#endif
