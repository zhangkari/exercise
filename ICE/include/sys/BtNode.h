#ifndef __BTNODE__H__
#define __BTNODE__H__

template <typename T>
class BtNode 
{
	public:
		BtNode();
		BtNode(T t);
		~BtNode();

/*
		BtNode<T>* GetLChild();
		BtNode<T>* GetRChild();
		T GetData();
*/

	private:
		T mData;
		BtNode<T>* mLChild;
		BtNode<T>* mRChild;

	friend class Tree;
};

template <typename T>
BtNode<T>::BtNode() : mLChild(0), mRChild(0)
{

}

template <typename T>
BtNode<T>::BtNode(T t) : mLChild(0), mRChild(0), mData(t)
{

}

template <typename T>
BtNode<T>::~BtNode()
{

}

/*
template <typename T>
BtNode<T>* BtNode<T>::GetLChild()
{
	return mLChild;
}

template <typename T>
BtNode<T>* BtNode<T>::GetRChild()
{
	return mRChild;
}

template <typename T>
T BtNode<T>::GetData()
{
	return mData;
}
*/

#endif
