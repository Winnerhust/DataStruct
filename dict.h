#ifndef _ERLER_DICT_H
#define _ERLER_DICT_H

#include "stddef.h"
#define DICT_MINSIZE 8
#ifndef _SIZE_T_
#define _SIZE_T_
typedef unsigned long size_t;
#endif

#ifndef _EULER_ELEM_FUN_
#define _EULER_ELEM_FUN_
typedef  int  (*elem_cmp_fun)(const void *a,const void *b);
typedef  void (*elem_delete_fun)(void *);
typedef  bool (*elem_unpred_fun)(const void *a);
typedef  bool (*elem_binpred_fun)(const void *a,const void *b);
#endif

typedef struct {
	long me_hash;
	enum {UNUSED,CTIVE,DUMMY}state;
	void *me_key;
	void *me_value;
}DictEntry;

class Dict
{
public:
	Dict();
	Dict(const size_t size);
	~Dict();

	void *get(const void *key);
	int get(const void *key,void **value);

	int add(const void *key,const void *value);
	int set(const void *key,const void *value);

	void remove(const void *key);
	void clear(elem_delete_fun elem_delete=NULL);
	
	size_t max_size() const;
	size_t size() const;
	bool empty() const;
	double rate() const;
protected:
	size_t resize(const size_t new_size);
private:	
	size_t m_fill;  /* # Active + # Dummy */
	size_t m_used;  /* # Active */
	
	size_t m_mask;
	
	DictEntry *m_table;
	DictEntry m_smalltable[DICT_MINSIZE];
};
#endif
