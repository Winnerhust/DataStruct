#include <iostream>
#include <assert.h>
#include "stack.h"

using namespace std;

void test_push()
{
	cout<<"--------test push-------"<<endl;
	
	Stack s;
	
	int a=3,b=4,c=1;
	
	s.push(&a);
	s.push(&b);
	s.push(&c);
	
	assert(s.size()==3);
	assert(!s.empty());
	
	assert(*(int *)s.top()==1);

	cout<<"test Ok"<<endl;
}
void test_pop()
{
	cout<<"--------test pop-------"<<endl;
	
	Stack s;
	
	int a=3,b=4,c=1;
	
	s.push(&a);
	s.push(&b);
	s.push(&c);
	
	s.pop();
	s.pop();

	assert(s.size()==1);
	assert(!s.empty());
	assert(*(int *)s.top()==3);

	s.pop();
	
	assert(s.size()==0);
	assert(s.empty());
	assert((int *)s.top()==NULL);


	s.pop();
	
	assert(s.size()==0);
	assert(s.empty());
	assert((int *)s.top()==NULL);

	cout<<"test Ok"<<endl;
}

int main()
{
	test_push();
	test_pop();
	return 0;
}
