#ifndef _ERLER_DICT_CPP
#define _ERLER_DICT_CPP

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "dict.h"

Dict::Dict(const size_t size/*=8*/):m_all(0),m_used(0),m_table(NULL),
	cmpfun(NULL),hashfun(NULL),keytype(K_POINTER)
{
	size_t newsize = (size > DICT_MINSIZE ? size : DICT_MINSIZE);
	
	m_mask = newsize - 1;

	m_table = new DictEntry *[newsize];
	assert(m_table);
	
	for(size_t i = 0 ; i< newsize; ++i){
		m_table[i] = NULL;
	}
}

Dict::~Dict()
{
	DictEntry *p = NULL,*q=NULL;

	for(size_t i = 0 ; i <= m_mask; ++i ){
		p = m_table[i];
		while(p != NULL){
			q = p;
			p = p->next;
			delete q;
		}
	}

	delete [] m_table;
}
void Dict::init(EqualFun cmp_fun,HashFun hash_fun,int key_type/*=K_POINTER*/)
{
	cmpfun = cmp_fun;
	hashfun = hash_fun;
	keytype = (KeyType)key_type;
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
	//todo
	return 0;
}
double Dict::rate() const
{
	//todo 
	return 0;
}

bool Dict::exist(const void *key) 
{
	void *value;
	return get(key,&value);
}
void *Dict::get(const void *key)
{
	void * value=NULL;
	get(key,&value);

	return value;
}

bool Dict::get(const void *key,void **value )
{
	long h = hash(key);
	size_t index = h & m_mask;
	
	DictEntry *p = m_table[index]; 
	
	for( ; p != NULL; p = p->next){
		if(rich_eq(p->me_key,key)){
			*value = p->me_value;	
			return true;
		}
	}

	return false;
	
}
bool Dict::add(const void *key,const void *value)
{	
	long h = hash(key);
	size_t index = h & m_mask;
	
	DictEntry *p = m_table[index]; 
	
	for( ; p != NULL; p = p->next){
		if(rich_eq(p->me_key,key)){
			return false;	
		}
	}
	
	DictEntry *entry = new DictEntry;
	assert(entry);

	entry->me_hash = h;
	entry->me_key = (void *)key;
	entry->me_value = (void *)value;
	entry->next = m_table[index];
	entry->prev = NULL;

	if(m_table[index] != NULL){
		m_table[index]->prev = entry;
	}

	m_table[index] = entry;

	++m_used;

	return true;
}
void Dict::set(const void *key,const void *value)
{
	long h = hash(key);
	size_t index = h & m_mask;
	
	DictEntry *p = m_table[index]; 
	
	for( ; p != NULL; p = p->next){
		
		if(rich_eq(p->me_key, key)){
			p->me_value = (void *)value;
			return ;
		}
	}
	
	DictEntry *entry = new DictEntry;
	assert(entry);

	entry->me_hash = h;
	entry->me_key = (void *)key;
	entry->me_value = (void *)value;
	entry->next = m_table[index];
	entry->prev = NULL;

	if(m_table[index] != NULL){
		m_table[index]->prev = entry;
	}

	m_table[index] = entry;

	++m_used;

}

void Dict::remove(const void *key)
{
	long h = hash(key);
	size_t index = h & m_mask;
	
	DictEntry *p = m_table[index]; 
	bool b_find = false;
	for( ; p != NULL; p = p->next){
		
		if(rich_eq(p->me_key , key)){
			b_find = true ;
			break;
		}
	}
	if(b_find){
		if(p == m_table[index])
			m_table[index] = p->next;
		if (p->prev != NULL)
		    p->prev->next = p->next;
		if (p->next != NULL)
			p->next->prev = p->prev;	
		delete p; 

		--m_used;
	}
}

void Dict::clear(delete_fun elem_delete/* =NULL */)
{
	DictEntry *p = NULL,*q=NULL;

	for(size_t i = 0 ; i <= m_mask; ++i ){
		p = m_table[i];
		while(p != NULL){
			q = p;
			p = p->next;
			delete q;
		}
		m_table[i] = NULL;
	}

	m_all = 0;
	m_used = 0;
}
void num_swap(size_t &a,size_t &b)
{
	size_t tmp;
	tmp = a;
	a = b;
	b = tmp;
}
void Dict::swap(Dict & other)
{
	num_swap(other.m_all,m_all);
	num_swap(other.m_used,m_used);
	num_swap(other.m_mask,m_mask);
	
	DictEntry **tmp_tbl = m_table;
	m_table = other.m_table;
	other.m_table = tmp_tbl;

	EqualFun tmp_eq = cmpfun;
	cmpfun = other.cmpfun;
	other.cmpfun = cmpfun;

	HashFun tmp_hash = hashfun;
	hashfun = other.hashfun;
	other.hashfun = hashfun;

	KeyType	tmp_type = keytype;
	keytype = other.keytype;
	other.keytype = keytype;
}
bool Dict::rehash(const size_t new_size)
{
	Dict other(new_size);
	other.cmpfun = cmpfun;
	other.hashfun = hashfun;
	other.keytype = keytype;

	DictEntry *p = NULL;
	int cnt=0;
	for(size_t i = 0 ; i <= m_mask; ++i ){
		p = m_table[i];
		while(p != NULL){
			if(!other.add(p->me_key,p->me_value)){
				return false;
			}
			cnt++;
			p = p->next;
			
		}
	}
	printf("rehash:cnt:%d mask=:%d old_mask:%d\n",cnt,other.m_mask,m_mask);
	swap(other);
	printf("rehash:cnt:%d mask=:%d old_mask:%d\n",cnt,other.m_mask,m_mask);

	return true;
}

bool Dict::rich_eq(const void *a,const void *b)
{
	bool ret = false;
	if(a == b )
		ret = true;
	else if(cmpfun != NULL)
		ret = (cmpfun(a,b)==0);
	else if(keytype==K_STRING)
		return strcmp((char *)a,(char *)b);
	else if(keytype==K_LONG)
		return (*(long *)a == *(long *)b);
	return ret;
}
long Dict::hash(const void *key)
{
	if(hashfun){
		return hashfun(key);
	}else if(keytype==K_STRING){
		return string_hash((char *)key);
	}else if(keytype==K_LONG){
		return long_hash((long *)key);
	}else{
		return pointer_hash(key);
	}
}
long Dict::pointer_hash(const void *key) const
{
	
	long h =(long)key;
	h ^= (h >> 20) ^ (h >> 12);
	h ^= (h >> 7) ^ (h >> 4);
	return (long)h;
}
long Dict::long_hash(const long *key) const
{
	if(key == NULL){
		return 0;
	}	
	return *key;
}

long Dict::string_hash(const char *str)const
{
	if(str == NULL)
		return 0;
	long len = strlen(str);

	unsigned char *p = (unsigned char *)str;
	long x = *p << 7;
	while(--len >= 0){
		x = (1000003*x)^ *p++;
	}
	x ^= len;

	return x;
}

#endif

