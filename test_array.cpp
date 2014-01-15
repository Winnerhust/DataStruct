/*
 * file : test_array.cpp
 */
#include <iostream>
#include <string.h>
#include <stdio.h>
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
void str_elem_delete(void *item)
{
	if(item){
		delete (char *)item;
	}
}
void test_push_back()
{
	cout<<"----------test push_back----------"<<endl;
	int a=4,b=10,c=5,d=7;
	Array array;
	Array array2(20);

	for(int i=0;i<16;++i){
		array.push_back(&a);	
		array.push_back(&b);	
		array.push_back(&c);	
		array.push_back(&d);	

		array2.push_back(&a);	
		array2.push_back(&b);	
		array2.push_back(&c);	
		array2.push_back(&d);	
	}
	
	assert(array.size()==16*4);
	assert(array2.size()==16*4);
	cout<<"capacity:"<<array.capacity() <<" "<<array2.capacity()<<endl;
	assert(*(int *)array.at(0)==4);
	assert(*(int *)array.at(5)==10);
	assert(*(int *)array2.at(0)==4);
	assert(*(int *)array2.at(5)==10);
	
	//array.elem_delete=int_elem_delete;
	array.clear();
	//array2.elem_delete=int_elem_delete;
	array2.clear();
	cout<<"test OK"<<endl;
}
void test_resize()
{
	
	cout<<"------------test resize-------------"<<endl;
	cout<<"size,capacity means the number and the max number of elements can cantains"<<endl;
	cout<<"------------------------------------"<<endl;
	int a=4,b=10,c=5,d=7;
	Array array;

	for(int i=0;i<16;++i){
		array.push_back(&a);	
		array.push_back(&b);	
		array.push_back(&c);	
		array.push_back(&d);	
	}
	
	assert(array.size()==16*4);
	assert(array.capacity()==16*4);
	cout<<"capacity:"<<array.capacity() <<endl;
	
	cout<<"--------"<<endl;

	Array array2(20);
	cout<<array2.capacity()<<endl;
	assert(array2.capacity()==32);

	for(int i=0;i<16;++i){
		array2.push_back(&a);	
		array2.push_back(&b);	
		array2.push_back(&c);	
		array2.push_back(&d);	
	}
	
	assert(array2.size()==16*4);
	assert(array2.capacity()==16*4);
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
	int a=4,b=10,c=5,d=7;
	Array array;

	for(int i=0;i<16;++i){
		array.push_back(&a);	
		array.push_back(&b);	
		array.push_back(&c);	
		array.push_back(&d);	
	}
	
	assert(array.size()==16*4);
	
	int *p =(int *) array.pop_back();
	
	assert(*(int *)p==7);
	assert(*(int *)array.back()==5);
	
	cout<<"-------"<<endl;
	
	int *q;
	array.pop_back((void **)&q);
	
	assert(*(int *)q==5);
	assert(*(int *)array.back()==10);
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
    for(int i=0;i<5;i++){
    	f[i]= new char(20);
    	sprintf(f[i],"abc%d",i);
    	array.push_back(f[i]);
    }
   	f[5]= new char(20);
    sprintf(f[5],"abc1");
    array.push_back(f[5]);

	array.elem_cmp = str_elem_cmp;

	assert(array.index("abc0")==0);
	assert(array.index("abc1")==1);
	assert(array.index("abc2")==2);

	array.elem_delete=str_elem_delete;
	array.clear();
	cout<<"test OK"<<endl;
}
void test_delete()
{
	cout<<"---------------------test delete----------------"<<endl;
    char *f[6];
	Array array;
    for(int i=0;i<5;i++){
    	f[i]= new char(20);
    	sprintf(f[i],"abc%d",i);
    	array.push_back(f[i]);
    }
   	f[5]= new char(20);
    sprintf(f[5],"abc1");
    array.push_back(f[5]);

	array.erase(2);
	assert(array.size()==5);
	assert(strcmp((char *)array.at(2),"abc3")==0);
	cout<<"------"<<endl;
	
	array.elem_cmp= str_elem_cmp;
	array.remove("abc1");
	assert(array.size()==4);
	assert(strcmp((char *)array.at(1),"abc3")==0);
	cout<<"------"<<endl;
	
	array.elem_delete = str_elem_delete;
	array.clear();
		
	assert(array.size()==0);
	
	printf("addr:%p\n",f);
	printf("addr:%p\n",f[0]);
	cout<<"f[0]:"<<f[0]<<" "<<*f<<endl;
	cout<<"test OK"<<endl;
}
void test_copy()
{
	cout<<"----------test copy--------"<<endl;
	Array array1(10);
	int a=3,b=5,c=7;
	
	array1.push_back(&a);
	array1.push_back(&b);
	array1.push_back(&c);

	Array array2(array1);
	
	//array1.clear();
	//
	
	assert(array2.size()==3);
	assert(array1.at(1)==&b);
	assert(array2.at(1)==&b);
	cout<<"-----"<<endl;
	
	Array array3=array2;

	array2.clear();
	assert(array3.size()==3);
	assert(array3.at(1)==&b);

	cout<<"-----test OK"<<endl;
}
void test_at()
{
	cout<<"---------test at --------"<<endl;
	Array array;
	int a=5,b=10;
	array.push_back(&a);

	int *p = (int *)array.at(0);
	assert(*p==5);

	array.assign(0,&b);

	assert(*(int *)array.at(0) == 10);

	cout<<"test OK"<<endl;

}
int main(int argc,char *argv[])
{
	cout<<"sizeof int:"<<sizeof(int)<<endl;
	cout<<"sizeof int *:"<<sizeof(int *)<<endl;
	cout<<"sizeof void *:"<<sizeof(void *)<<endl;
	cout<<"sizeof void **:"<<sizeof(void **)<<endl;
	test_copy();
    test_at();
	test_push_back();
	test_resize();
	test_pop_back();
	test_index();
	test_delete();
	return 0;
}
