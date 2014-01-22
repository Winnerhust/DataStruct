#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
#ifndef _EULER_PHYOPERATOR_H
#define _EULER_PHYOPERATOR_H

typedef struct PhyOperator PhyOperator;


typedef bool (*inquiry)(PhyOperator *a);
typedef bool (*getnextfun)(PhyOperator *a); //todo

struct PhyOperator {
	bool found;     
	inquiry open;   
	getnextfun get_next; 
	inquiry close;  
	char name[80];
};



class NestLoopJoin
{
public:	
	NestLoopJoin(PhyOperator *l,PhyOperator *r)
	{
		left = l;
		right = r;
		
		op.found = false;
		op.open = open;
		op.get_next = get_next;
		op.close = close;

		sprintf(op.name,"NestLoopJoin(%s-%s)",l->name,r->name);
	}
	NestLoopJoin(const char *s)
	{
		left=right=NULL;
		
		op.found = false;
		op.open = open;
		op.get_next = get_next;
		op.close = close;
		
		strcpy(op.name,s);
	}
	PhyOperator op;/*must be first element !*/
	static bool open(PhyOperator*tt);
	static bool get_next(PhyOperator *t);
	static bool close(PhyOperator *t);
private:	
	/*user data*/
	PhyOperator *left;
	PhyOperator *right;
};

class IndexScan
{
public:	
	IndexScan(PhyOperator *l)
	{
		left = l;
		
		op.found = false;
		op.open = open;
		op.get_next = get_next;
		op.close = close;
		
		sprintf(op.name,"IndexScan(%s)",l->name);
	}
	IndexScan(const char *s)
	{
		left=NULL;
		
		op.found = false;
		op.open = open;
		op.get_next = get_next;
		op.close = close;
		
		strcpy(op.name,s);
	}

	PhyOperator op;/*must be first element !*/
	static bool open(PhyOperator*tt);
	static bool get_next(PhyOperator *t);
	static bool close(PhyOperator *t);
private:	
	/*user data*/
	PhyOperator *left;
};

bool NestLoopJoin::open(PhyOperator *t)
{
	NestLoopJoin *p = (NestLoopJoin *)t;
	cout<<"NestLoopJoin::open"<<endl;
	if(p->left){
		p->left->open(p->left);
	}
	if(p->right){
		p->right->open(p->right);
	}
	return true;
}
bool NestLoopJoin::get_next(PhyOperator *t)
{
	return true;
}
bool NestLoopJoin::close(PhyOperator *t)
{
	return true;
}
bool IndexScan::open(PhyOperator*t)
{
	IndexScan *p = (IndexScan *)t;
	cout<<"IndexScan::open"<<endl;
	if(p->left){
		p->left->open(p->left);
	}
	return true;
}
bool IndexScan::get_next(PhyOperator *t)
{
	return true;
}
bool IndexScan::close(PhyOperator *t)
{
	return true;
}
#endif

int main()
{
	NestLoopJoin t("t");
	NestLoopJoin p("p");
	IndexScan index("index");
	IndexScan index2((PhyOperator *)&t);
	NestLoopJoin m((PhyOperator *)&index2,(PhyOperator *)&index);

//	IndexScan::open((PhyOperator *)&index2);

	NestLoopJoin::open((PhyOperator *)&m);

	cout<<t.op.name<<endl;
	cout<<p.op.name<<endl;
	cout<<m.op.name<<endl;

	return 0;
}
