/*
 * file : test_array.cpp
 */
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "array.h"
using namespace std;

/* for example: when the item is a pointer to string*/
int  str_elem_cmp(const void *a,const void *b)
{
	return strcmp((char *)a,(char *)b);
}
void int_elem_delete(void *item)
{
	if(item){
		delete (int *)item;
	}
}
void str_elem_delete(char *item)
{
	char *p = (char *)item;
	if(p){
		cout<<"str_elem_delete:"<<p<<endl;
		free(p);
	}
}
void test_push_back()
{
	cout<<"----------test push_back----------"<<endl;
	int a = 4,b = 10,c = 5,d = 7;
	Array array;
	Array array2(20);

	for(int i = 0 ; i < 16; ++i){
		array.push_back(&a);	
		array.push_back(&b);	
		array.push_back(&c);	
		array.push_back(&d);	

		array2.push_back(&a);	
		array2.push_back(&b);	
		array2.push_back(&c);	
		array2.push_back(&d);	
	}
	
	assert(array.size() == 16*4);
	assert(array2.size() == 16*4);
	cout<<"capacity:"<<array.capacity() <<" "<<array2.capacity()<<endl;
	assert(*(int *)array.at(0) == 4);
	assert(*(int *)array.at(5) == 10);
	assert(*(int *)array2.at(0) == 4);
	assert(*(int *)array2.at(5) == 10);
	
	//array.elem_delete=int_elem_delete;
	array.clear();
	//array2.elem_delete=int_elem_delete;
	array2.clear();
	cout<<"test OK"<<endl;
}
void test_reserve()
{
	
	cout<<"------------test reserve-------------"<<endl;
	cout<<"size,capacity means the number and the max number of elements can cantains"<<endl;
	cout<<"------------------------------------"<<endl;
	int a = 4, b = 10, c = 5, d = 7;
	Array array;

	for(int i = 0 ; i < 16 ; ++i){
		array.push_back(&a);	
		array.push_back(&b);	
		array.push_back(&c);	
		array.push_back(&d);	
	}
	
	assert(array.size() == 16*4);
	assert(array.capacity() == 16*4);
	cout<<"capacity:"<<array.capacity() <<endl;
	
	cout<<"--------"<<endl;

	Array array2(20);
	cout<<array2.capacity()<<endl;
	assert(array2.capacity() == 32);

	for(int i = 0 ; i < 16 ; ++i){
		array2.push_back(&a);	
		array2.push_back(&b);	
		array2.push_back(&c);	
		array2.push_back(&d);	
	}
	
	assert(array2.size() == 16*4);
	assert(array2.capacity() == 16*4);
	cout<<"capacity:"<<array2.capacity() <<endl;
	
	//array.elem_delete=int_elem_delete;
	array.clear();
	//array2.elem_delete=int_elem_delete;
	array2.clear();
	cout<<"test OK"<<endl;
}
void test_pop_back()
{
	cout<<"---------------------test pop_back----------------"<<endl;
	int a = 4 , b = 10, c = 5, d = 7;
	Array array;

	for(int i = 0 ; i < 16 ; ++i){
		array.push_back(&a);	
		array.push_back(&b);	
		array.push_back(&c);	
		array.push_back(&d);	
	}
	
	assert(array.size() == 16*4);
	
	int *p =(int *) array.pop_back();
	
	assert(*(int *)p == 7);
	assert(*(int *)array.back() == 5);
	
	cout<<"-------"<<endl;
	
	int *q;
	array.pop_back((void **)&q);
	
	assert(*(int *)q == 5);
	assert(*(int *)array.back() == 10);
	//array.elem_delete = int_elem_delete;
	array.clear();
	//delete p;
	//delete q;
	cout<<"test OK"<<endl;
}
void test_index()
{
	cout<<"---------------------test index----------------"<<endl;
    char *f[6];
	Array array;
    for(int i = 0 ; i < 5 ; i++){
    	f[i] = (char *)malloc(20*sizeof(char));
    	sprintf(f[i],"abc%d",i);
    	array.push_back(f[i]);
    }
   	f[5] = (char *)malloc(20*sizeof(char));
    sprintf(f[5],"abc1");
    array.push_back(f[5]);

	array.elem_cmp = str_elem_cmp;

	assert(array.index("abc0") == 0);
	assert(array.index("abc1") == 1);
	assert(array.index("abc2") == 2);

	array.elem_delete = (elem_delete_fun)str_elem_delete;
	array.clear();
	cout<<"test OK"<<endl;
}
void test_erase()
{
	cout<<"---------------------test erase----------------"<<endl;
   
	Array array;
	array.elem_delete = (elem_delete_fun)str_elem_delete;
   	char *f = (char *)malloc(20*sizeof(char));
   	sprintf(f,"abc1");
   	array.push_back(f);
    
	array.erase(0);
	assert(array.empty());
	cout<<"------"<<endl;
	
	//printf("f:%s\n",f);
	
	cout<<"test earse 2------------"<<endl;

    char *str[4];
	Array array1;
	array1.elem_delete = (elem_delete_fun)str_elem_delete;

   	str[0] = (char *)malloc(20*sizeof(char));
   	str[1] = (char *)malloc(20*sizeof(char));
   	str[2] = (char *)malloc(20*sizeof(char));
   	str[3] = (char *)malloc(20*sizeof(char));
   	sprintf(str[0],"abc1");
   	sprintf(str[1],"abc2");
   	sprintf(str[2],"abc3");
   	sprintf(str[3],"abc4");
   	array1.push_back(str[0]);
   	array1.push_back(str[1]);
   	array1.push_back(str[2]);
   	array1.push_back(str[3]);
    
	array1.erase(2);

	assert(array1.size() == 3);

	assert(strcmp((char *)array1.at(0),str[0]) == 0);
	assert(strcmp((char *)array1.at(1),str[1]) == 0);
	assert(strcmp((char *)array1.at(2),str[3]) == 0);
		
	array1.clear();

	cout<<"test OK"<<endl;

}
void test_delete()
{
	cout<<"---------------------test delete----------------"<<endl;
    char *f[6];
	Array array;
	array.elem_delete = (elem_delete_fun)str_elem_delete;
	array.elem_cmp = (elem_cmp_fun)strcmp;

    for(int i = 0 ; i < 5 ; i++){
    	f[i] = (char *)malloc(20*sizeof(char));
    	sprintf(f[i],"abc%d",i);
    	array.push_back(f[i]);
    }
   	f[5] = (char *)malloc(20*sizeof(char));
    sprintf(f[5],"abc1");
    array.push_back(f[5]);

	array.erase(2);
	for(int i = 0 ; i < 6 ; i++){
		if(array.at(i))
			cout<<(char *)array.at(i)<<endl;
	}

	assert(array.size() == 5);
	assert(strcmp((char *)array.at(0),"abc0") == 0);
	assert(strcmp((char *)array.at(1),"abc1") == 0);
	assert(strcmp((char *)array.at(2),"abc3") == 0);
	assert(strcmp((char *)array.at(3),"abc4") == 0);
	assert(strcmp((char *)array.at(4),"abc1") == 0);

	cout<<"------"<<endl;
	
	array.remove("abc1");
	for(int i = 0 ; i < 6 ; i++){
		if(array.at(i))
			cout<<(char *)array.at(i)<<endl;
	}
	assert(array.size() == 3);
	assert(strcmp((char *)array.at(0),"abc0") == 0);
	assert(strcmp((char *)array.at(1),"abc3") == 0);
	assert(strcmp((char *)array.at(2),"abc4") == 0);
	cout<<"------"<<endl;
	
	array.erase(0,array.size());
		
	assert(array.size() == 0);
	
	cout<<"test OK"<<endl;
}
void test_copy()
{
	cout<<"----------test copy--------"<<endl;
	Array array1(10);
	int a = 3, b = 5, c = 7;
	
	array1.push_back(&a);
	array1.push_back(&b);
	array1.push_back(&c);

	Array array2(array1);
	
	//array1.clear();
	
	assert(array2.size() == 3);
	assert(array1.at(1) == &b);
	assert(array2.at(1) == &b);
	cout<<"-----"<<endl;
	
	Array array3 = array2;

	array2.clear();
	assert(array3.size() == 3);
	assert(array3.at(1) == &b);

	cout<<"-----test OK"<<endl;
}
void test_at()
{
	cout<<"---------test at --------"<<endl;
	Array array;
	int a = 5 , b = 10;
	array.push_back(&a);

	int *p = (int *)array.at(0);
	assert(*p == 5);

	array.assign(0,&b);

	assert(*(int *)array.at(0) == 10);

	cout<<"test OK"<<endl;

}
void test_insert()
{
	cout<<"---------test insert--------"<<endl;
	Array array;
	int a = 5 , b = 10 , c = 34 , d = 21;

	array.insert(0,&c);
	array.push_back(&a);
	array.push_back(&b);
	
	array.insert(0,&c);

	assert(*(int *)array.at(0) == c);
	assert(*(int *)array.at(1) == c);
	assert(*(int *)array.at(2) == a);
	assert(*(int *)array.at(3) == b);
	
	array.insert(10,&d);

	assert(*(int *)array.at(0) == c);
	assert(*(int *)array.at(1) == c);
	assert(*(int *)array.at(2) == a);
	assert(*(int *)array.at(3) == b);
	assert(*(int *)array.at(4) == d);
	
	array.insert(1,&d,40);

	assert(*(int *)array.at(0) == c);
	assert(*(int *)array.at(1) == d);
	assert(*(int *)array.at(40) == d);
	assert(*(int *)array.at(41) == c);
	assert(*(int *)array.at(42) == a);
	assert(*(int *)array.at(43) == b);

	assert(*(int *)array.at(44)==d);
	cout<<"test OK"<<endl;

}
int main(int argc,char *argv[])
{
	cout<<"sizeof int:"<<sizeof(int)<<endl;
	cout<<"sizeof int *:"<<sizeof(int *)<<endl;
	cout<<"sizeof void *:"<<sizeof(void *)<<endl;
	cout<<"sizeof char *:"<<sizeof(char *)<<endl;
	cout<<"sizeof void **:"<<sizeof(void **)<<endl;

	test_copy();
    test_at();
	test_push_back();
	test_reserve();
	test_pop_back();
	test_index();
	test_delete();
	test_erase();
	test_insert();
	return 0;
}
