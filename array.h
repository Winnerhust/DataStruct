/*
 * file: array.h
 * time:2014/1/14 12:07:32
 * */
#ifndef _EULER_ARRAY_H
#define _EULER_ARRAY_H

#define ARRAY_INIT_SZIE 16

#ifndef _SIZE_T_ 
#define _SIZE_T_
typedef unsigned long size_t;
#endif
typedef void (*elem_delete_fun)(void *);
typedef int (*elem_cmp_fun)(const void *,const void *);

class Array
{
public:
        Array();
        Array(size_t length);
        ~Array();
		
		/*the number of element*/
        size_t size() const{return len;} 
		/*the max number of elements can be cantained*/
        size_t capacity() const {return m_capacity;}
        
        bool empty() const{return len==0;}
        /*adjust capacity */
        void resize(const size_t new_size);
		
		void assign(const size_t index, void *elem);
        /*return the element at index*/
        void * at (const size_t index)const ; 

        /* return the index of the first elem ,if not found retrun -1 */
        long index(const void *elem) const ;
        
        void * front(){return (char *)(data[0]);}
        void * back(){ return (char *)(data[len-1]);}

//        void  push_front(void *elem);
//        void  pop_front(void *elem);
        void  push_back(void *elem);
        void * pop_back(); //dangerous
        void pop_back(void **item);
        
        
        void erase(const size_t pos,const size_t length=1);
        void remove(const void *elem);

        // clear all elements , you shoud define a function to  delete one element;
        void clear();
		//elements  compare function,use to index(),remove()
		elem_cmp_fun elem_cmp;
		//use to remove(),erase();
		elem_delete_fun elem_delete;
		
		//deep copy
		Array(const Array &other);
		Array & operator= (const Array &other);
private:
        size_t len;
        size_t m_capacity;
        void ** data;

        size_t convert_to_capacity(const size_t length);
};

#endif
