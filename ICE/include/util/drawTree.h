#ifndef __DRAWTREE__H__
#define __DRAWTREE__H__

#include <ncurses.h>
#include <unistd.h>

typedef struct Node Node;
typedef struct DNode DNode;

struct Node
{
	int data;
	Node* left;
	Node* right;
}; 

struct DNode
{
	int data;
	int index;
	DNode* left;
	DNode* right;
};

void drawNode(int index, int data);
void draw(Node* node);
Node* Create(Node* root, int data);
void Convert(DNode*& droot, Node* root);
void Walk(Node* node);

#endif
