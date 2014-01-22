#ifndef _ERLER_DICT_H
#define _ERLER_DICT_H

#include "stddef.h"
#define DICT_MINSIZE 8
#ifndef _SIZE_T_
#define _SIZE_T_
typedef unsigned long size_t;
#endif

typedef  long (*HashFun)(const void *);
typedef  int (*EqualFun)(const void *a,const void *b);
typedef void (*delete_fun)(const void *);
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

	void init(EqualFun cmp_fun,HashFun hash_fun,int key_type=K_POINTER);
	
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
	
	void swap(Dict & other);
	bool rehash(const size_t new_size);

	DictEntry *data(){return *m_table;};
	
	EqualFun cmpfun;
	HashFun hashfun;
	enum KeyType{K_POINTER,K_STRING,K_LONG}keytype;
protected:
	Dict(const Dict &pther);
	Dict & operator= (const Dict & other);
private:	
	size_t m_all;
	size_t m_used;  
	size_t m_mask;

	DictEntry **m_table;

	bool rich_eq(const void *a,const void *b);
	long hash(const void *key);
	long pointer_hash(const void *key) const ;
	long long_hash(const long *key) const ;
	long string_hash(const char *key) const ;

};
#endif
