#include <iostream>
#include <assert.h>
#include "queue.h"

using namespace std;

void test_push()
{
	cout<<"--------test push--------"<<endl;
	Queue q;
	int a = 3 , b = 5 , c = 2;
	
	q.push(&a);
	q.push(&b);
	q.push(&c);

	assert(q.size() == 3);
	assert(*(int *)q.front() == 3);
	assert(*(int *)q.back() == 2);

	cout<<"test OK"<<endl;
}
void test_pop()
{
	cout<<"--------test pop--------"<<endl;
	Queue q;
	int a = 3 , b = 5 , c = 2;
	
	q.push(&a);
	q.push(&b);
	q.push(&c);

	assert(q.size() == 3);
	assert(*(int *)q.front() == 3);
	assert(*(int *)q.back() == 2);
	assert(!q.empty());

	q.pop();
	assert(q.size() == 2);
	assert(*(int *)q.front() == 5);
	assert(*(int *)q.back() == 2);
	assert(!q.empty());

	cout<<"test OK"<<endl;
}

int main()
{
	test_push();
	test_pop();

	return 0;
}
