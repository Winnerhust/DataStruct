#ifndef _EULER_LIST_CPP
#define _EULER_LIST_CPP

#include "list.h"
#include <assert.h>

List::List():head(NULL),curr(NULL),tail(NULL),len(0),
	elem_cmp(NULL),elem_delete(NULL),elem_unpred(NULL),elem_binpred(NULL)
{
}

List::~List()
{
	ListNode * curr = head;
	ListNode * p = head;

	while(curr != NULL){
		p = curr->next;
		printf("delete %d\n",*(int *)curr->ptr);

		delete curr;

		curr = p;
	}
}

void *List::back()
{
	if(tail != NULL)
		return tail->ptr;
	return NULL;
}
void * List::front()
{
	if(head)
		return head->ptr;
	return NULL;
}

size_t List::size()const
{
	return len;
}
bool List::empty()const
{
	return (len==0);
}
void List::pop_back()
{
	if(len > 1){
		ListNode * pp = tail->prev;
		ListNode * p = tail;
		tail = pp;
		if(curr == p )
			curr = pp;
		pp->next = NULL;

		printf("delete %d\n",*(int *)p->ptr);
		delete p;
	
		--len;
	}else if (len == 1){
		printf("delete %d\n",*(int *)tail->ptr);
		delete tail;
		head = NULL;
		tail = NULL;
		curr = NULL;
		--len;
	}else
		return ;
}
void List::pop_front()
{
	if(len > 1){
		ListNode * p = head->next;
		
		printf("delete %d\n",*(int *)head->ptr);
		delete head;

		p->prev = NULL;

		head = p;
		curr = p->next;
		--len;
	}else if(len == 1){
		printf("delete %d\n",*(int *)head->ptr);
		delete head;
		head = NULL;
		tail = NULL;
		curr = NULL;
		--len;
	}else	
		return ;
}
void List::push_back(const void *elem)
{
	ListNode * p = new ListNode();
	assert(p);
	p->ptr = (void *)elem;
	printf("new :%d\n",*(int *)elem);
	p->prev = tail;
	p->next = NULL;
	
	if(len > 0){
		tail->next = p;
		tail = p;
	}else{
		head = p;
		tail = p;
	}
	
	++len;
}
void List::push_front(const void *elem)
{
	ListNode * p = new ListNode();
	assert(p);
	p->ptr = (void *)elem;
	printf("new :%d\n",*(int *)elem);
	p->prev = NULL;
	p->next = head;
	
	if(len > 0){
		head->prev = p;
		head = p;
	}else{
		head = p;
		tail = p;
	}

	++len;
}

ListNode * List::begin()
{
	return head;
}
ListNode * List::end()
{
	return NULL;
}
ListNode * List::rbegin()
{
	return tail;
}
ListNode * List::rend()
{
	return NULL;
}
ListNode * List::insert(ListNode * pos ,const void *elem)
{
	if(pos ==NULL) return NULL;
	
	ListNode * q = new ListNode();
	assert(q);
	q->ptr = (void *)elem;
	printf("new :%d\n",*(int *)elem);
	q->prev = pos->prev;
	q->next = pos;

	pos->prev = q;
	
	if(head == pos){
		head = q;
	}else{
		q->prev->next = q;
	}
	
	++len;
	return q;
}

void List::clear()
{
	ListNode * p = head;
	curr = head;
	if(elem_delete){
		while(curr){
			elem_delete(curr->ptr);
			
			p = curr;
			curr = curr->next;
			
			printf("delete %d\n",*(int *)p->ptr);
			delete p;
		}
	}else{
		
		while(curr){
			p = curr;
			curr  = curr->next;
			
			printf("delete %d\n",*(int *)p->ptr);
			delete p;
		}
	}
	head = NULL;
	tail = NULL;
	curr = NULL;
	len = 0;
}
ListNode * List::erase(ListNode * pos) 
{
	if(pos == NULL)
		return NULL;
	if(pos == head){
		pop_front();
		return head;
	}
	if(pos == tail) {
		pop_back();
		return NULL;
	}
	
	ListNode * pp = pos->prev;
	ListNode * pn = pos->next;

	pp->next = pn;
	pn->prev = pp;

	//if(elem_delete) elem_delete(pos->ptr);

	printf("delete %d\n",*(int *)pos->ptr);
	delete pos;
	
	--len ;
	return pn;
}
void List::merge(List & li,elem_cmp_fun elem_cmp/*=NULL*/)
{
	//todo
}
void List::remove(const void *elem)
{
	if(elem_cmp){
		ListNode * p = head;

		while(p){
			if(elem_cmp(elem,p->ptr) == 0){
				p = erase(p);
			}else{
				p = p->next;
			}
		}
	}else{
		ListNode * p = head;

		while(p){
			if(elem == p->ptr){
				p = erase(p);
			}else{
				p = p->next;
			}
		}
	}
}
void remove_if(const void *elem,elem_unpred_fun elem_unpred /*=NULL*/)
{
//todo
}
void List::reverse()
{
	if(len <= 1) return ;
	
	ListNode * p = head;
	ListNode * pn = head->next ;

	tail = head;

	while(pn){
		p->next = p->prev;
		p->prev = pn;

		p = pn;
		pn = pn->next;
	}
	
	head = p;
	head->next = p->prev;
	head->prev = NULL;
}

void List::sort(elem_cmp_fun elem_cmp)
{
	if(elem_cmp == NULL) return ;

	//todo
}
void List::unique(elem_binpred_fun elem_binpred /*=NULL*/)
{
	//todo	
}

#endif
