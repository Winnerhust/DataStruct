#ifndef _ERLER_DICT_CPP
#define _ERLER_DICT_CPP

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "dict.h"
Dict::Dict():m_fill(0),m_used(0),m_mask(DICT_MINSIZE-1),dict_errno(0),m_table(m_smalltable)
{
	memset(m_table,0,DICT_MINSIZE*sizeof(DictEntry));
}
Dict::Dict(const size_t size):m_fill(0),m_used(0),dict_errno(0),m_table(m_smalltable)
{
	if(size > DICT_MINSIZE){
		m_table = (DictEntry *)malloc(size * sizeof(DictEntry));
		assert(m_table);
	}
	m_mask = (size > DICT_MINSIZE ? size-1 : DICT_MINSIZE-1);
	
	memset(m_table,0,m_mask*sizeof(DictEntry));
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
	return m_mask+1;
}
double Dict::rate() const
{
	return (double)(m_used*1.0/(m_mask+1));
}

void *Dict::get(const void *key)
{
	size_t index = find(key);
	
	if(m_table[index].state == DictEntry::ACTIVE){
		return m_table[index].me_value;
	}
		
	return NULL;
}

int Dict::get(const void *key,void **value )
{
	size_t index = find(key);
	
	if(m_table[index].state == DictEntry::ACTIVE){
		*value = m_table[index].me_value;
		return 1;
	}
	
	return 0;
}
size_t Dict::find(const void *key)
{
	size_t index = hash(key);
	size_t tmp = index;
	size_t pos = 1;
	while(m_table[index].state != DictEntry::UNUSED && m_table[index].me_key != key){
		index = tmp + pos*pos ;
		if(index >= m_mask){
			index = index % m_mask;
			if(pos > m_mask){
				printf("hash table overflow!\n");
				dict_errno = -1;
				return m_mask+1;
			}
		}
		++pos;
	}
//	printf("find times = %d\n",pos);
	return index;
}
bool Dict::exist(const void *key) 
{
	size_t index = find(key);
	if(dict_errno != 0){
		return false;
	}

	if(m_table[index].state == DictEntry::ACTIVE)
		return true;
	return false;
}
bool Dict::add(const void *key,const void *value)
{
	size_t len = m_mask + 1;
	if(m_used+1 >= len*0.6 ){
		resize(len*2);
	}

	return sys_add(key ,value);
}
bool Dict::sys_add(const void *key,const void *value)
{
	void * v;
	size_t index = find(key);

	if(dict_errno != 0){
		return false;
	}
	if(m_table[index].state == DictEntry::ACTIVE){
		return false;
	}else{
		if(m_table[index].state == DictEntry::UNUSED){
			++m_fill;
		}
		++m_used;

		m_table[index].state = DictEntry::ACTIVE;
		m_table[index].me_hash = hash(key);
		m_table[index].me_key = (void *)key;
		m_table[index].me_value = (void *)value;
	}

	return true;
}
void Dict::set(const void *key,const void *value)
{
	void * v;
	size_t index = find(key);
	if(dict_errno != 0){
		return ;
	}

	if(m_table[index].state == DictEntry::ACTIVE){
		m_table[index].me_value = (void *)value;
	}else{
		if(m_table[index].state == DictEntry::UNUSED){
			++m_fill;
		}
		++m_used;

		m_table[index].state = DictEntry::ACTIVE;
		m_table[index].me_value = (void *)value;
		m_table[index].me_key = (void *)key;
	}
}

void Dict::remove(const void *key)
{
	size_t index = find(key);
	if(dict_errno != 0){
		return ;
	}
	if(m_table[index].state == DictEntry::ACTIVE){
		m_table[index].state = DictEntry::DUMMY;
		--m_used;
	}
}
void Dict::clear(elem_delete_fun elem_delete/* =NULL */)
{
	if(elem_delete){
		for(size_t i = 0; i <= m_mask; ++i)	{
			if(m_table[i].state == DictEntry::ACTIVE){
				elem_delete(m_table[i].me_value);
			}
		}
	}else{
		memset(m_table,0,(m_mask+1)*sizeof(DictEntry));
	}

	m_fill = 0;
	m_used = 0;
}

size_t Dict::resize(const size_t new_size)
{
	if(new_size <= DICT_MINSIZE && m_table == m_smalltable){
			return m_used;
	}
	if(new_size == m_mask+1){
		return m_used;
	}

	DictEntry *old_table = m_table;
	size_t old_mask = m_mask ;
	size_t new_len =( new_size > DICT_MINSIZE ? new_size :DICT_MINSIZE);

	if(new_size <= DICT_MINSIZE){
		m_table = m_smalltable;
	}else{
		m_table = (DictEntry *)malloc(new_len*sizeof(DictEntry));
		assert(m_table);
	}

	memset(m_table,0,new_len*sizeof(DictEntry));
	m_mask = new_len-1;
	m_fill = 0;
	m_used = 0;
	dict_errno = 0;
	
	for(size_t i = 0; i<= old_mask ;++i){
		if (old_table[i].state == DictEntry::ACTIVE){
			sys_add(old_table[i].me_key , old_table[i].me_value);
		}
	}

	if(old_table != m_smalltable) free(old_table);
	
	return m_used;
}
size_t Dict::hash(const void *key) const
{
	size_t l,r;
	l = ((unsigned long)(key)) % m_mask;
	r = ((unsigned long)(key)) & m_mask;
//	printf("%%:%d &:%d\n",l,r);
	return l;
}
#endif

