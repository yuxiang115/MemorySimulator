#ifdef _ABSTRACTLINKEDLIST_H
#define _ABSTRACTLINKEDLIST_H
template <class DT>
class abstract AbstractLikedList {
public:
	virtual DT& info() = NULL; //return the object info
	virtual AbstractLinkedList<DT>* next() = NULL; // return LinkedLIst that _next points to in the linkedList
	virtual bool isEmpty() = NULL; //check if the List is empty
	virtual int size() = NULL; //return size of LinkedList
	virtual void add(const DT& object) = NULL; //add object into list
	virtual void insert(const DT& object, int position) = NULL;
	virtual DT& remove() = NULL; //move the first object and return it
	virtual DT& remove(const DT& key) = NULL; //return the object that removed
	virtual DT& removeAt(int position) = NULL; //remove the object in the specific position
	virtual DT& infoAt(int position) = NULL;  //return the info in the specific position
	virtual AbstractLinkedList<DT>* setNext(AbstracLinkedList<DT> list) = NULL; //set the next,and return the old one
	virtual DT& find(DT& key) = NULL; //return the key that found in the list

};
#endif
