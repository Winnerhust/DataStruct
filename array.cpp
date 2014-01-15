/*
 * file: array.cpp
 *
 * */
#ifndef _EULER_ARRAY_CPP
#define _EULER_ARRAY_CPP

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>
#include "array.h"

Array::Array():len(0),m_capacity(0),data(NULL),elem_cmp(NULL),elem_delete(NULL)
{
        data = (void  **) malloc(ARRAY_INIT_SZIE*sizeof(void *));
        assert(data);
		m_capacity = ARRAY_INIT_SZIE;
}
Array::Array(size_t length):len(0),data(NULL),elem_cmp(NULL),elem_delete(NULL)
{
		resize(length);
        data = (void **) malloc(m_capacity*sizeof(void *));
        assert(data);
}
Array::~Array()
{
        if(data)
                free(data);
		len = 0;
		m_capacity = 0;
}
Array::Array(const Array &other):len(0),m_capacity(0),data(NULL),
	elem_cmp(NULL),elem_delete(NULL)
{
	*this = other;
}
Array & Array::operator= (const Array &other)
{
	if (this != &other){
		if(data){
			this->clear();
			this->resize(other.size());
		}else{
		 	m_capacity = convert_to_capacity(other.size());
			data = (void **)malloc(m_capacity*sizeof(void *));
			assert(data);
		}
	
		memcpy(data, other.data,other.size()*sizeof(void *)); 
		for(int i =0;i<other.size();i++){
			printf("[%d]:%x %x\n",i,data[i],other.data[i]);
		}
		len = other.size();
		this->elem_cmp = other.elem_cmp;
		this->elem_delete = other.elem_delete;
	}
	return *this;
}

size_t Array::convert_to_capacity(const size_t length)
{
        size_t mod = length%ARRAY_INIT_SZIE;
        size_t t_capacity = (length / ARRAY_INIT_SZIE)*ARRAY_INIT_SZIE;
        if(mod)
                t_capacity += ARRAY_INIT_SZIE;

        return t_capacity;
}
void Array::resize(const size_t new_size)
{
        size_t t_capacity = convert_to_capacity(new_size);
        if(t_capacity != m_capacity){

                m_capacity = t_capacity;
				void **tmp=NULL;
				if(data){
                	tmp = (void**) realloc(data,m_capacity*sizeof(void *));
				}else{
					tmp = (void **)malloc(m_capacity*sizeof(void *));
				}
                data= tmp;
                assert(data);
        }
		
}
void Array::assign(const size_t index, void *elem)
{
    if(index >= len ){
        printf("array index out of range\n");
        return ;
    }
	
	data[index] = elem;

}
void * Array::at(const size_t index) const
{
        if(index >= len ){
                printf("array index out of range\n");
                return NULL;
        }
        
        return data[index];
}
long Array::index(const void *elem) const
{
	if(elem_cmp){
        for(size_t i=0;i<len; ++i){
                if(elem_cmp(elem,data[i])==0){
                        return i;
                }
        }
	}else{//default
        for(size_t i=0;i<len; ++i){
                if(elem == data[i]){
                        return i;
                }
        }

	}
    return -1;
}
        
void  Array::push_back(void *elem)
{
    if(len >= m_capacity){
   		resize(m_capacity*2);
	}
    data[len]=(char *)elem;
    len++;
}
        
void * Array::pop_back()
{
    return data[--len];
}
void Array::pop_back(void **item)
{
	*item = data[--len];
}
        
void Array::erase(const size_t pos,const size_t length)
{
    size_t t;
    if(pos+length >=len){
    	for(size_t i=pos;i<len;++i){
        	data[i]=0;
        }
        len = len-pos >0 ? len-pos : 0;
        return ;
    }
	if(this->elem_delete)
		this->elem_delete(data[pos]);
    
	for(size_t i=pos+length;i <len ;++i){
      	data[i-length]=data[i];
    }

    len = len -length;
}
void Array::remove(const void *elem)
{
        size_t i = index(elem);
        if(i >=0){
                erase(i);
        }
}
void Array::clear()
{
		if(this->elem_delete !=NULL){
        	
			// cannot  for(i =len;i>=0;--i)
	        // becase i-1 will large than 0 where i=0, it would make error
			printf("clear:len=%d\n",len);
        	for(size_t i=len;i > 0;--i){
                this->elem_delete(data[i-1]);
                data[i-1]=0;
        	}
		}
        len = 0;
}

#endif

