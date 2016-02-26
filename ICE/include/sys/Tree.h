#ifndef __TREE__H__
#define __TREE__H__

#include <BtNode.h>

template <class T>
class Tree
{
	public:
		Tree() : mRoot(0)
		{
			
		}

		Tree(Tree& tree)
		{
			*this = tree;
		}

		Tree operator=(Tree& tree)
		{
			*this = tree;
		}

	private:
		BtNode<T>* mRoot;
};

#endif
