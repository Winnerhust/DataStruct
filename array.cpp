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
		m_capacity = convert_to_capacity(length);
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
			this->reserve(other.size());
		}else{
		 	m_capacity = convert_to_capacity(other.size());
			data = (void **)malloc(m_capacity*sizeof(void *));
			assert(data);
		}
	
		memcpy(data, other.data,other.size()*sizeof(void *)); 
		
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
void Array::reserve(const size_t new_size)
{
        size_t t_capacity = convert_to_capacity(new_size);
        if(t_capacity != m_capacity){

                m_capacity = t_capacity;
				void **tmp = NULL;
				if(data){
                	tmp = (void**) realloc(data,m_capacity*sizeof(void *));
				}else{
					tmp = (void **)malloc(m_capacity*sizeof(void *));
				}
                data = tmp;
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
        for(size_t i = 0 ; i < len ; ++i){
                if(elem_cmp(elem,data[i]) == 0){
                        return i;
                }
        }
	}else{//default
        for(size_t i = 0 ; i < len ; ++i){
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
   		reserve(m_capacity*2);
	}
    data[len] = elem;
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
        
void Array::insert(const size_t pos,void *elem,const size_t length /* = 1 */)
{
    if(pos >= len){
    	size_t t = 0;
	
		while(t++ < length){
			push_back(elem);
		}
	}else{
		size_t newlen = length + len;

		if(newlen > m_capacity){
			reserve(newlen);
			//m_capacity = convert_to_capacity(newlen);
		}
		
		memmove(data + pos + length,data + pos,(len - pos) * sizeof(void *));
		
		for(size_t i = 0 ; i < length ; ++i){
			data[i + pos] = elem;	
		}

		len = newlen;
	}
}

void Array::erase(const size_t pos,const size_t length/* =1*/)
{
    size_t t;
    if(pos >= len){
		return ;
	}
	
	size_t limit = ((len < pos+length)? len :(pos+length));
    if(this->elem_delete){
		for(size_t i = pos ; i < limit ; ++i){
			this->elem_delete(data[i]);
        	data[i] = 0;
        }
       
    }else{
		for(size_t i = pos ; i < limit ; ++i){
        	data[i] = 0;
        }
	}
	
	memmove(data + pos, data + limit,(len - limit) * sizeof(void*));
    len = len - (limit - pos);
}
void Array::remove(const void *elem)
{
    long i;
	do{
		i = index(elem);
        if(i >= 0){
                erase(i);
        }
	}while(i >= 0);
}
void Array::clear()
{
		if(this->elem_delete != NULL){
        	
			// cannot  for(i =len;i>=0;--i)
	        // becase i-1 will large than 0 where i=0, it would make error
        	for(size_t i = len ; i > 0; --i){
                this->elem_delete( data[i-1]);
                data[i-1] = 0;
        	}
		}
        len = 0;
}

#endif

