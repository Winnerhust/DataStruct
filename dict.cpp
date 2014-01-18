#ifndef _ERLER_DICT_CPP
#define _ERLER_DICT_CPP

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "dict.h"
Dict::Dict():m_fill(DICT_MINSIZE),m_used(0),m_mask(DICT_MINSIZE-1),m_table(m_smalltable)
{
	memset(m_table,0,DICT_MINSIZE*sizeof(DictEntry));
}
Dict::Dict(const size_t size):m_used(0),m_table(m_smalltable)
{
	if(size > DICT_MINSIZE){
		m_table = (DictEntry *)malloc(size * sizeof(DictEntry));
		assert(m_table);
	}
	m_fill = (size > DICT_MINSIZE ? size : DICT_MINSIZE);
	m_mask = m_fill - 1;
	memset(m_table,0,m_fill*sizeof(DictEntry));
}

Dict::~Dict()
{
	if(m_table != m_smalltable){
		free(m_table);
	} 
}

bool Dict::empty() const
{
	return (m_used==0);
}
size_t Dict::size() const
{
	return m_used;
}
size_t Dict::max_size() const
{
	return m_fill;
}
double Dict::rate() const
{
	return (double)(m_used*1.0/m_fill);
}

void *Dict::get(const void *key)
{
	//todo
	return NULL;
}
int Dict::get(const void *key,void **value)
{
	//todo
	return 0;
}

int Dict::add(const void *key,const void *value)
{
	//todo
	return 0;
}
int Dict::set(const void *key,const void *value)
{
	//todo
	return 0;
}

void Dict::remove(const void *key)
{
	//todo
}
void Dict::clear(elem_delete_fun elem_delete/* =NULL */)
{
	//todo
}

size_t Dict::resize(const size_t new_size)
{
	//todo
	return 0;
}
#endif

