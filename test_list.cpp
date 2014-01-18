#include <iostream>
#include <assert.h>
#include "list.h"
using namespace std;


void test_push_back()
{
	cout<<"-------test push_back-------"<<endl;
	List li;
	int a = 3,b = 5, c = 2;
	li.push_back(&a);
	assert(li.size()==1);
	assert(*(int *)li.back()==3);
	
	li.push_back(&b);
	assert(li.size()==2);
	assert(*(int *)li.front()==3);
	assert(*(int *)li.back()==5);
	
	li.push_back(&c);
	assert(li.size()==3);
	assert(*(int *)li.front()==3);
	assert(*(int *)li.back()==2);
	
	li.push_back(&c);
	assert(li.size()==4);
	assert(*(int *)li.front()==3);
	assert(*(int *)li.back()==2);
	
	cout<<"test OK"<<endl;
}
void test_push_front()
{
	cout<<"-------test push_front-------"<<endl;
	List li;
	int a = 3,b = 5, c = 2;
	li.push_front(&a);
	assert(li.size()==1);
	assert(*(int *)li.front()==3);
	
	li.push_front(&b);
	assert(li.size()==2);
	assert(*(int *)li.back()==3);
	assert(*(int *)li.front()==5);
	
	li.push_front(&c);
	assert(li.size()==3);
	assert(*(int *)li.back()==3);
	assert(*(int *)li.front()==2);
	
	li.push_front(&c);
	assert(li.size()==4);
	assert(*(int *)li.back()==3);
	assert(*(int *)li.front()==2);
	
	cout<<"test OK"<<endl;
}
void test_pop_back()
{
	cout<<"-------test pop_back-------"<<endl;
	List li;
	int a = 3,b = 5, c = 2;
	li.push_back(&a);
	li.push_back(&b);
	li.push_back(&c);
	li.push_back(&c);

	assert(li.size()==4);
	
	li.pop_back();
	assert(li.size()==3);
	assert(*(int *)li.front()==3);
	assert(*(int *)li.back()==2);
	
	li.pop_back();
	assert(li.size()==2);
	assert(*(int *)li.front()==3);
	assert(*(int *)li.back()==5);
	li.pop_back();
	li.pop_back();

	assert(li.size()==0);
	assert(li.empty());
	assert(li.front()==NULL);
	assert(li.back()==NULL);
	cout<<"test OK"<<endl;
}
void test_pop_front()
{
	cout<<"-------test pop_front-------"<<endl;
	List li;
	int a = 3,b = 5, c = 2;
	li.push_front(&a);
	li.push_front(&b);
	li.push_front(&c);
	li.push_front(&c);

	assert(li.size()==4);
	
	li.pop_front();
	assert(li.size()==3);
	assert(*(int *)li.back()==3);
	assert(*(int *)li.front()==2);
	
	li.pop_front();
	assert(li.size()==2);
	assert(*(int *)li.back()==3);
	assert(*(int *)li.front()==5);
	li.pop_front();
	li.pop_front();

	assert(li.size()==0);
	assert(li.empty());
	assert(li.front()==NULL);
	assert(li.back()==NULL);

	cout<<"test OK"<<endl;
}
void test_insert()
{
	cout<<"-------test insert-------"<<endl;
	
	List li;
	int a = 3 , b = 5 , c = 2, d =7;
	li.push_back(&a);
	// insert to head
	li.insert(li.begin(),&d);
	assert(*(int *)li.front() == 7);
	
	//insert to middle
	li.push_back(&b);
	li.push_back(&a);
	
	for(ListNode *i = li.begin() ; i != li.end() ; i = i->next){
		if(*(int *)(i->ptr) == b){
			li.insert(i,&c);
			break;
		}
	}
	
	assert(li.size() == 5);
	assert(*(int *)li.front() == 7);
	assert(*(int *)li.back() == 3);

	li.pop_back();
	li.pop_back();

	assert(*(int *)li.back() == c);

	//insert to end
	li.insert(li.rbegin(),&d);
	
	li.pop_back();

	assert(*(int *)li.back() == d);

	cout<<"test OK"<<endl;
}
void test_erase()
{
	cout<<"-------test erase-------"<<endl;
	
	List li;
	int a = 3 , b = 5 , c = 2, d =7;
	li.push_back(&a);
	li.push_back(&b);
	li.push_back(&c);
	li.push_back(&d);
	li.push_back(&b);
	// erase at head
	li.erase(li.begin());
	assert(*(int *)li.front() == b);
	
	// erase at end
	li.erase(li.rbegin());
	assert(*(int *)li.back() == d);

	//erase to middle
	ListNode *p = li.begin()->next;
	
	li.erase(p);
	
	assert(li.size() == 2);
	assert(*(int *)li.front() == b);
	assert(*(int *)li.back() == d);

	cout<<"test OK"<<endl;
}
void test_remove()
{
	cout<<"-------test remove-------"<<endl;
	
	List li;
	int a = 3 , b = 5 , c = 2, d =7;
	li.push_back(&a);
	li.push_back(&b);
	li.push_back(&c);
	li.push_back(&d);
	li.push_back(&b);
	
	li.remove(&a);
	assert(li.size() == 4);
	assert(*(int *)li.front() == b);
	
	li.remove(&b);
	assert(li.size()==2);
	assert(*(int *)li.back() == d);
	assert(*(int *)li.front() == c);

	li.remove(&d);
	
	assert(li.size() == 1);
	assert(*(int *)li.front() == c);
	assert(*(int *)li.back() == c);

	cout<<"test OK"<<endl;
}

void test_clear()
{
	cout<<"-------test clear-------"<<endl;
	
	List li;
	int a = 3 , b = 5 , c = 2, d =7;
	li.push_back(&a);
	li.push_back(&b);
	li.push_back(&c);
	li.push_back(&d);
	li.push_back(&b);
	
	li.clear();
	assert(li.empty());
	assert(li.back() == NULL);

	cout<<"test OK"<<endl;
}
void test_reverse()
{

	cout<<"-------test reverse-------"<<endl;
	
	List li;
	int a = 3 , b = 5 , c = 2, d =7;
	li.push_back(&a);
	li.push_back(&b);
	
	li.reverse();
	assert(li.size() == 2);
	assert(li.front() == &b);
	assert(li.back() == &a);

	
	li.push_back(&b);
	li.push_back(&c);
	li.push_back(&d);

	li.reverse();
	assert(li.size() == 5);
	assert(li.front() == &d);
	assert(li.back() == &b);
	
	cout<<"test OK"<<endl;
}

int main()
{
	test_push_back();
	test_push_front();
	test_pop_back();
	test_pop_front();
	test_insert();
	test_erase();
	test_remove();
	test_clear();
	test_reverse();

	return 0;
}


