#include <ncurses.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <drawTree.h>

#define LEAF_MARGIN 8  // define margin between leaf node

int main()
{
	srand(time(0));
	Node* root = 0;
	
	int i;
	for(i=0; i<10; ++i)
	{
	root = Create(root, rand()%100);	
	}

	draw(root);
}

static void drawTree(DNode* root)
{
	if(root)
	{
		drawNode(root->index, root->data);
		drawTree(root->left);
		drawTree(root->right);
	}
}

void draw(Node* root)
{
	initscr();
	int i;

	DNode* droot = 0;
	Convert(droot, root);	

	if(droot)
	{
		drawTree(droot);
	}

	refresh();

	getch();
	endwin();

	return;
}

Node* Create(Node* root, int data)
{
	if(root == NULL)
	{
		root = new Node();
		root->data = data;
		root->left = 0;
		root->right = 0;
		return root;
	}

	if(data <= root->data)
	{
		root->left = Create(root->left, data);
	}
	else
	{
		root->right = Create(root->right, data);
	}

	return root;
}

void Walk(Node* root)
{
	if(root)
	{
		printf("%-4d", root->data);
		Walk(root->left);
		Walk(root->right);
	}
}

void Walk(DNode* root)
{
	if(root)
	{
		printf("%d(%d)  ", root->data, root->index);
		Walk(root->left);
		Walk(root->right);
	}
}

Node* Copy(Node* root)
{
	Node* r = 0;
	if(root)
	{
		r = new Node();
		r->data = root->data;
		r->left = Copy(root->left);
		r->right = Copy(root->right); 
	}
} 


static void convert(DNode*& dnode, int index, Node* node)
{
	if(node)
	{
		dnode = new DNode();
		dnode->index = index;
		dnode->data = node->data;
//		printf("data:%d\n", node->data);
		convert(dnode->left, 2*index, node->left);
		convert(dnode->right, 2*index+1, node->right);
	}
}

void Convert(DNode* &dnode, Node* node)
{
	convert(dnode, 1, node);	
}




static int getHeight(int level)
{
	if(level == 1)
		return 0;

	if(level == 2)
		return 3;

	if(level == 3)
		return 6;

	if(level == 4)
		return 9;

	if(level == 5)
		return 12;

	if(level == 6)
		return 15;
}

static int getLevel(int index)
{
	if(index == 1)
		return 1;

	if(index >= 2 && index <= 3)
		return 2;

	if(index >= 4 && index <= 7)
		return 3;

	if(index >= 8 && index <= 15)
		return 4;

	if(index >= 16 && index <= 31)
		return 5;

	if(index >= 32 && index <= 61)
		return 6;
}


static float simple_pow(float e, int n)
{
	int flag = 0;

	if(n < 0)
	{
		n *= -1;
		flag = 1;
	}

	float result = 1.0f;
	while(n>0)
	{
		result *= e;
		--n;
	}

	if(flag)
	{
		result = 1 / result;
	}

	return result;
}


static bool isOnLeft(int index)
{
	int level = getLevel(index);
	float value = 3 * simple_pow(2, level-2);
	if(index < value)
	{
		return true;
	}
	else
	{
		return false;		
	}
}

int getBaseIndex(int index)
{
	int level = getLevel(index);
	return simple_pow(2, level-1);
}

float getBaseCoord(int index)
{
	int level = getLevel(index);

	/*
	   bool isLeft = isOnLeft(index);
	   float length = 1 / simple_pow(2, level-2) * LEAF_MARGIN;
	 */

	switch(level)
	{
		case 1:
			return 0;
		case 2:
			return 2;
		case 3:
			return 3;
		case 4:
			return 3.5;
		case 5:
			return 3.75;

		case 6:
			return 3.875;
	}

}

void drawNode(int index, int data)
{
	if(index <= 0 || index >= 32)
		//	if(index <= 0 || index >= 64)
		return;


	int i;
	int level = getLevel(index);
	int height = getHeight(level);
	int offset = index - getBaseIndex(index);	
	float coord = getBaseCoord(index) * LEAF_MARGIN;
	coord = COLS/2 - coord;

	float length = 1 / simple_pow(2, level-2) * LEAF_MARGIN;
	float center = 0.0f;
	while(offset--)
	{
		center += length * 4;
	}

	center += coord;

	int left = center - length;
	int right = center + length;

	move(height, (int)center);
	printw("%d", data);
	move(height+1, left);

	if(index <= 15)
		//	if(index <= 63)
	{
		i = length;
		while(i--)
			printw("%c", '_');		

		printw("%c", '|');

		i = length;
		while(i--)
			printw("%c", '_');		

		move(height+2, left);
		printw("%c", '|');

		move(height+2, right);
		printw("%c", '|');
	}

}
