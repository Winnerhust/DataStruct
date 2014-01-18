#include <iostream>
#include <stdio.h>
#include <assert.h>
#include "queue.h"
using namespace std;

#ifndef _BTREE_CPP
#define _BTREE_CPP

typedef struct Node{
	int key;
	struct Node *left;
	struct Node *right;
	struct Node *parent;
}Node;

class Btree
{
public:
	Btree();
	~Btree();
	void insert(const int key);
	void insert_noduplicate(const int key);
	void delete_node(Node *z);
	
	Node *search(const int key);
	Node * max(Node * p = NULL);
	Node * min(Node * p = NULL);
	Node *successor(Node *p);
	Node *predecessor(Node *p);

	void walk();
	void level_walk();
private:
	Node *root;
	
	void node_walk(Node *);
	void transplant(Node *u,Node *v);

};

Btree::Btree():root(NULL)
{
}

Btree::~Btree()
{
	if(root){
		if (root->left) delete root->left;
		if (root->right) delete root->right;
	}
}

void Btree::node_walk(Node *p)
{
	if(p){
		node_walk(p->left);
		printf(" %d ",p->key);
		node_walk(p->right);
	}
}
void Btree::walk()
{
	node_walk(root);
	printf("\n");
}

void Btree::level_walk()
{
	Node *p = NULL ;
	Queue Q;

	Q.push(root);

	while (!Q.empty()) {  
		p = (Node *)Q.front();  
		Q.pop(); 
		printf(" %d ",p->key);
		if (p->left!= NULL)  
			Q.push(p->left);  
		if (p->right!= NULL)  
			Q.push(p->right);  
	}						
}

Node * Btree::search(const int key)
{
	Node *p = root;

	while(p){
		if( key == p->key){
			return p;
		}else if( key > p->key){
			p = p->right;
		}else{
			p = p->left;
		}
	}

	return NULL;
}

void Btree::insert(const int key)
{
	Node *p = root;
	Node *pp = root;

	while(p){
		if( key >= p->key){
			pp = p;
			p = p->right;
		}else{
			pp = p;
			p = p->left;
		}
	}

	Node *q = new Node();

	assert(q);

	q->key = key;
	q->left = NULL;
	q->right = NULL;
	q->parent = pp;
	
	if(pp != NULL){
		if(key >= pp->key){
			pp->right = q;
		}else{
			pp->left = q;
		}
	}else{
		root = q;
	}
}
void Btree::insert_noduplicate(const int key)
{
	Node *p = root;
	Node *pp = root;

	while(p){
		if(key == p->key){
			return ;
		}
		else if( key > p->key){
			pp = p;
			p = p->right;
		}else{
			pp = p;
			p = p->left;
		}
	}

	Node *q = new Node();

	assert(q);

	q->key = key;
	q->left = NULL;
	q->right = NULL;
	q->parent == pp;

	if(pp != NULL){
		if(key >= pp->key){
			pp->right = q;
		}else{
			pp->left = q;
		}
	}else{
		root = q;
	}
}
Node * Btree::max(Node *p /*= NULL*/)
{
	if(p == NULL) p =root;
	Node *parent = p;
	while(p){
		parent = p;
		p = p->right;
	}

	return parent;
}
Node * Btree::min(Node *p /*= NULL*/)
{
	if(p == NULL) p =root;
	
	Node *parent = p;
	while(p){
		parent = p;
		p = p->left;
	}

	return parent;
}
Node * Btree::successor(Node * p)
{
	if(!p) return NULL;

	if(p->right) return min(p->right);

	Node *q = p->parent;
	Node *pp = p;

	while(q && pp==q->right){
		pp = q;
		q = q->parent;
	}

	return q;
}
Node *Btree::predecessor(Node *p)
{
	if(!p ) return NULL;
	if(p->left) return max(p->left);

	Node *q = p->parent;
	Node *pp = p;

	while(q && pp == q->left){
		pp = q;
		q = q->parent;
	}

	return q;
}
void Btree::transplant(Node *u,Node *v)
{
	if(u->parent == NULL) 
		root = v;
	else if(u = u->parent->left)
		u->parent->left = v;
	else 
		u->parent->right = v;
	
	if(v != NULL)
		v->parent = u->parent;
}
void Btree::delete_node(Node *z)
{
	if (z->left == NULL)
		transplant(z,z->right);
	else if (z->right == NULL)
		transplant(z,z->left);
	else {
		Node * y = min(z->right);
		if (y->parent != z){
			transplant(y,y->right);
			y->right = z->right;
			y->right->parent = y;
		}

		transplant(z,y);
		y->left = z->left;
		y->left->parent = y;
	}	
}
#endif

void test_insert()
{
	cout<<"--------test insert--------"<<endl;
	Btree btree;
	
	btree.insert(1);
	btree.insert(3);
	btree.insert(5);
	btree.insert(9);
	btree.insert(7);
	btree.insert(6);
	btree.insert(7);
	btree.insert(5);

	btree.walk();

	cout<<"test OK"<<endl;
}
void test_search()
{
	cout<<"--------test search--------"<<endl;
	Btree btree;
	
	btree.insert(1);
	btree.insert(3);
	btree.insert(5);
	btree.insert(9);
	btree.insert(7);
	btree.insert(6);
	btree.insert(7);
	btree.insert(5);
	
	assert(btree.search(7) != NULL);
	assert(btree.search(7)->key == 7);
	cout<<"test OK"<<endl;
}
void test_max_min()
{
	cout<<"--------test max min--------"<<endl;
	Btree btree;
	
	btree.insert(1);
	btree.insert(3);
	btree.insert(5);
	btree.insert(9);
	btree.insert(7);
	btree.insert(6);
	btree.insert(7);
	btree.insert(5);
	
	assert(btree.max()->key == 9);
	assert(btree.min()->key == 1);
	cout<<"test OK"<<endl;
}
void test_successor()
{
	cout<<"--------test successor--------"<<endl;
	Btree t;

	t.insert(1);
	t.insert(5);
	t.insert(3);
	t.insert(4);

	Node *p = t.search(3);

	assert(t.successor(p));
	assert(t.successor(p)->key ==4);

	p = t.search(4);

	assert(t.successor(p));
	assert(t.successor(p)->key ==5);
	
	p = t.search(5);

	assert(t.successor(p) == NULL);
	cout<<"test OK"<<endl;
}
void test_predecessor()
{
	cout<<"--------test predecessor--------"<<endl;
	Btree t;

	t.insert(1);
	t.insert(5);
	t.insert(3);
	t.insert(4);

	Node *p = t.search(3);

	assert(t.predecessor(p));
	assert(t.predecessor(p)->key ==1);

	p = t.search(4);

	assert(t.predecessor(p));
	assert(t.predecessor(p)->key ==3);
	
	p = t.search(1);

	assert(t.predecessor(p) == NULL);
	cout<<"test OK"<<endl;
}
void test_delete_node()
{
	cout<<"--------test delete_node--------"<<endl;
	Btree t;

	t.insert(1);
	t.insert(5);
	t.insert(3);
	t.insert(4);

	Node *p = t.search(3);

	assert(t.predecessor(p));
	
	t.walk();
	
	t.delete_node(p);

	p = t.search(3);

	assert(p==NULL);

	t.walk();
	
	cout<<"test OK"<<endl;
	
}
void test_walk()
{
	cout<<"--------test walk--------"<<endl;
	Btree t;

	t.insert(1);
	t.insert(5);
	t.insert(3);
	t.insert(4);

	cout<<"walk:"<<endl;

	t.walk();

	cout<<"level_walk:"<<endl;

	t.level_walk();
	
	cout<<"test OK"<<endl;
}
int main()
{
	test_insert();
	test_search();
	test_max_min();
	test_successor();
	test_predecessor();
	test_delete_node();
	test_walk();
	return 0;
}

