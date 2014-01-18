#include <iostream>
#include <assert.h>
#include "dict.h"

using namespace std;

void test_dict()
{
	cout<<"--------test dict----------"<<endl;
	Dict dict;
	
	assert(dict.empty());
	assert(dict.size() == 0);
	assert(dict.max_size() == DICT_MINSIZE);
	assert(dict.rate() > -0.005 && dict.rate() < 0.005  );


	Dict d(10);
	
	assert(d.empty());
	assert(d.size() == 0);
	assert(d.max_size() == 10);
	assert(d.rate() > -0.005 && d.rate() < 0.005  );

	cout<<"test OK"<<endl;	
}
int main()
{
	test_dict();
	return 0;
}

