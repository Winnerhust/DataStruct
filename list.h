#ifndef _EULER_LIST_H
#define _EULER_LIST_H

#include <assert.h>
#include <stdio.h>

#ifndef _SIZE_T_ 
#define _SIZE_T_
typedef unsigned long size_t;
#endif

#ifndef _EULER_ELEM_FUN_
#define _EULER_ELEM_FUN_
typedef  int  (*elem_cmp_fun)(const void *a,const void *b);
typedef  void (*elem_delete_fun)(void *);
typedef  bool (*elem_unpred_fun)(const void *a);
typedef  bool (*elem_binpred_fun)(const void *a,const void *b);
#endif

	
typedef struct ListNode {
	void* ptr;
	struct ListNode *prev;
	struct ListNode *next;
}ListNode;

class List
{
public:

	List();
	~List();

	void * front();
	void *back();

	void clear();
	bool empty() const;
	ListNode * erase(ListNode * pos) ;
	ListNode * begin();
	ListNode * end();
	ListNode * rbegin();
	ListNode * rend();
	ListNode * insert(ListNode * pos ,const void *elem);
	void merge(List & li,elem_cmp_fun elem_cmp=NULL);
	void pop_back();
	void pop_front();
	void push_back(const void *elem);
	void push_front(const void *elem);
	void remove(const void *elem);
	void remove_if(const void *elem,elem_unpred_fun elem_unpred=NULL);
	void reverse();
	size_t size() const;
	void sort(elem_cmp_fun elem_cmp);
	void unique(elem_binpred_fun elem_binpred=NULL);
		
	elem_cmp_fun 		elem_cmp;
	elem_delete_fun	 	elem_delete;
	elem_unpred_fun 	elem_unpred;
	elem_binpred_fun 	elem_binpred;
	
private:	
	//deep copy
	List(const List &other);
	List & operator= (const List &other);
private:

	ListNode * head;
	ListNode * curr;
	ListNode * tail;
	
	int len;
};


#endif
