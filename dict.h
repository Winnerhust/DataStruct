#ifndef _ERLER_DICT_H
#define _ERLER_DICT_H

#include "stddef.h"
#define DICT_MINSIZE 8
#ifndef _SIZE_T_
#define _SIZE_T_
typedef unsigned long size_t;
#endif

typedef  int (*EqualFun)(const void *a,const void *b);
typedef  void (*delete_fun)(void *);

typedef struct DictEntry{
	long me_hash;
	void *me_key;
	void *me_value;
	struct DictEntry *next;
	struct DictEntry *prev;
}DictEntry;

bool default_eq(const void * a,const void *b);
class Dict
{
public:
	Dict(const size_t size=8);
	~Dict();
	
	bool exist(const void *key) ;
	void *get(const void *key);
	bool get(const void *key,void **value);

	bool add(const void *key,const void *value);
	void set(const void *key,const void *value);

	void remove(const void *key);
	void clear(delete_fun elem_delete=NULL);
	
	size_t max_size() const;
	size_t size() const;
	bool empty() const;
	double rate() const;
	long hash(long key) const ;
	
	void swap(Dict & other);
	bool resize(const size_t new_size);

	DictEntry *data(){return *m_table;};
	
	EqualFun cmpfun;
private:	
	size_t m_all;
	size_t m_used;  
	size_t m_mask;
	DictEntry **m_table;

	bool rich_eq(const void *a,const void *b);

};
#endif
