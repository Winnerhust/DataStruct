#ifndef _EULER_QUEUE_H
#define _EULER_QUEUE_H


#ifndef _SIZE_T_ 
#define _SIZE_T_
typedef unsigned long size_t;
#endif

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
