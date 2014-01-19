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

	for(int i=0;i<dict.max_size();i++){
		if(data[i].state != DictEntry::UNUSED)
		cout<<"["<<i<<"]:"<<"dict["<<(char *)data[i].me_key<<"]="<<*(int *)data[i].me_value<<" hash="<<data[i].me_hash<< " state="<<data[i].state<<endl;
		else
		cout<<"["<<i<<"]:"<<"dict[NULL]=NULL hash=0 state=0"<<endl;
	}

	assert(!dict.empty());
	cout<<"size:"<<dict.size()<<endl;
	cout<<"max_size:"<<dict.max_size()<<endl;
//	assert(dict.max_size() == DICT_MINSIZE);
	
	
	cout<<"test OK"<<endl;	
}
void test_resize()
{
	cout<<"--------test resize----------"<<endl;
	Dict dict;
	char keys[][20] = { "a", "b", "c", "d", "e","f","g","h","l" };
	int values[] = {10,20,30,40,50,60,70,80,90};

	for(int i=0;i<9;i++){
		bool succ= dict.add(keys[i],&values[i]);
	}
	
	DictEntry *data = dict.data();

	for(int i=0;i<dict.max_size();i++){
		if(data[i].state != DictEntry::UNUSED)
		cout<<"["<<i<<"]:"<<"dict["<<(char *)data[i].me_key<<"]="<<*(int *)data[i].me_value<<" hash="<<data[i].me_hash<< " state="<<data[i].state<<endl;
		else
		cout<<"["<<i<<"]:"<<"dict[NULL]=NULL hash=0 state=0"<<endl;
	}

	/*!!!!!!!!!!**/
	dict.resize(20);

	data = dict.data();

	for(int i=0;i<dict.max_size();i++){
		if(data[i].state != DictEntry::UNUSED)
		cout<<"["<<i<<"]:"<<"dict["<<(char *)data[i].me_key<<"]="<<*(int *)data[i].me_value<<" hash="<<data[i].me_hash<< " state="<<data[i].state<<endl;
		else
		cout<<"["<<i<<"]:"<<"dict[NULL]=NULL hash=0 state=0"<<endl;
	}

	/*!!!!!!!!!!**/
	dict.resize(5);

	data = dict.data();

	for(int i=0;i<dict.max_size();i++){
		if(data[i].state != DictEntry::UNUSED)
		cout<<"["<<i<<"]:"<<"dict["<<(char *)data[i].me_key<<"]="<<*(int *)data[i].me_value<<" hash="<<data[i].me_hash<< " state="<<data[i].state<<endl;
		else
		cout<<"["<<i<<"]:"<<"dict[NULL]=NULL hash=0 state=0"<<endl;
	}

	assert(!dict.empty());
	cout<<"size:"<<dict.size()<<endl;
	
	cout<<"test OK"<<endl;	
}
int main()
{
	test_dict();
	test_add();
	test_resize();
	return 0;
}

