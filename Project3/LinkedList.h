#ifdef _LINKEDLIST_H
#define _LINKEDLIST_H
#include "AbstractLinkedList.h"
#include <iostream>
using namespace std;

template <class DT>
class LinkedList: public virtual AbstractLinkedList {
protected:
	DT* _info;
	LinkedList<DT>* _next;

public:
	LinkedList();
	LinkedList(const DT& info);
	LinkedList(const DT& info, LinkedList<DT>* next);
	bool isEmpty();
};
#include "LikedList.cpp"
#endif
