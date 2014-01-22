#include <iostream>
#include <assert.h>
#include <string.h>
#include "dict.h"

using namespace std;

void test_dict()
{
	cout<<"--------test dict----------"<<endl;
	Dict dict;
	
	assert(dict.empty());
	assert(dict.size() == 0);
	assert(dict.rate() > -0.005 && dict.rate() < 0.005  );


	Dict d(10);
	
	assert(d.empty());
	assert(d.size() == 0);
	assert(d.rate() > -0.005 && d.rate() < 0.005  );

	cout<<"test OK"<<endl;	
}
void test_add()
{
	cout<<"--------test add----------"<<endl;
	Dict dict;
	char keys[][20] = { "a", "b", "c", "d", "e","f","g","h","l" };
	int values[] = {10,20,30,40,50,60,70,80,90};

	for(int i=0;i<9;i++){
		bool succ= dict.add(keys[i],&values[i]);
		if(succ)
			assert(*(int *)dict.get(keys[i]) == values[i]);
		else
			cout<<"add key"<<keys[i]<<"overflow"<<endl;
	}
	
	DictEntry *data = dict.data();


	assert(!dict.empty());
	cout<<"size:"<<dict.size()<<endl;
	
	cout<<"test OK"<<endl;	
}
void test_rehash()
{
	cout<<"--------test rehash----------"<<endl;
	Dict dict;
	char keys[][20] = { "a", "b", "c", "d", "e","f","g","h","l" };
	int values[] = {10,20,30,40,50,60,70,80,90};

	for(int i=0;i<9;i++){
		bool succ= dict.add(keys[i],&values[i]);
		if(!succ)
			cout<<"add key error ["<<keys[i]<<"]"<<endl;
	}
	
	
	/*!!!!!!!!!!**/
	dict.rehash(20);

	/*!!!!!!!!!!**/
	dict.rehash(5);

	assert(dict.size()==9);

	cout<<"size:"<<dict.size()<<endl;
	
	cout<<"test OK"<<endl;	
}
void test_set()
{
	cout<<"--------test set----------"<<endl;
	Dict dict;
	char keys[][20] = { "a", "b", "c", "d", "e","f","g","h","l" ,"i"};
	int values[] = {10,20,30,40,50,60,70,80,90,100};

	for(int i=0;i<9;i++){
		bool succ= dict.add(keys[i],&values[i]);
	}
	dict.set(keys[0],&values[2]);
	assert(*(int *)dict.get(keys[0]) == values[2]);

	dict.set(keys[9],&values[9]);

	assert(*(int *)dict.get(keys[9]) == values[9]);

	DictEntry *data = dict.data();

	cout<<"size:"<<dict.size()<<endl;
	
	cout<<"test OK"<<endl;	
}


void test_cmp()
{
	cout<<"--------test cmp----------"<<endl;
	Dict dict;
	dict.cmpfun = (EqualFun)strcmp;
	dict.keytype = Dict::K_STRING; 
	char keys[][20] = { "a", "b", "c", "d", "e","f","g","h","l" ,"i"};
	int values[] = {10,20,30,40,50,60,70,80,90,100};

	for(int i=0;i<9;i++){
		bool succ= dict.add(keys[i],&values[i]);
	}
	assert(*(int *)dict.get(keys[2]) == values[2]);

	assert(*(int *)dict.get("c") == values[2]);
	
	char t[] = "c";
	assert(*(int *)dict.get(t) == values[2]);

	cout<<"test OK"<<endl;	
}
void test_remove()
{
	cout<<"--------test remove----------"<<endl;
	Dict dict;
	dict.cmpfun = (EqualFun)strcmp;
	dict.keytype = Dict::K_STRING; 
	char keys[][20] = { "a", "b", "c", "d", "e","f","g","h","l" ,"i"};
	int values[] = {10,20,30,40,50,60,70,80,90,100};

	for(int i=0;i<9;i++){
		bool succ= dict.add(keys[i],&values[i]);
	}
	assert(*(int *)dict.get(keys[2]) == values[2]);
	
	dict.remove("c");
	assert(dict.get("c") == NULL);
	
	for(int i=0;i<9;i++){
		dict.remove(keys[i]);
	}
	
	assert(dict.empty());

	cout<<"test OK"<<endl;	

}
void test_test()
{
	Dict dict;
	dict.cmpfun = (EqualFun)strcmp;
	dict.keytype = Dict::K_STRING;
	{
		dict.set("a","1");
		dict.set("b","2");
		dict.set("c","3");
	}

	cout<<(char *)dict.get("a")<<endl;
	cout<<(char *)dict.get("b")<<endl;
	cout<<(char *)dict.get("c")<<endl;
}
int main()
{
	test_dict();
	test_add();
	test_rehash();
	test_set();
	test_cmp();
	test_remove();
	test_test();
	return 0;
}

