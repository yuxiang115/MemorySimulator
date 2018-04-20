/**
CS-2413 Xiang Yu
source.cpp
Purpose: build LinkedList to demonstrate the memory run mode

@author Xiang Yu
@version 1.0 3/23/17
*/

#include <iostream>
#include <string>
#include <exception>
using namespace std;
//classes which are below are exception class
class LinkedListException : public exception {};
class LinkedListMemory : public LinkedListException {
	virtual const char* what() const throw() {
		return "Sorry out of the Memory, create object fail.";
	}
};

class LinkedListBounds : public LinkedListException {
	virtual const char* what() const throw() {
		return "Sorry out of bounds.";
	}
};

class LinkedListNotFound : public LinkedListException {
	virtual const char* what() const throw() {
		return "Sorry object not found in list.";
	}
};

class LinkedListAttachToEmpty : public LinkedListException {
	virtual const char* what() const throw() {
		return "Sorry Attach to Empty list.";
	}
};

/**
LinkedList Class
*/
template <class DT>
class LinkedList {
	friend ostream& operator<< (ostream& s, LinkedList<DT>& list);
protected:
	DT* _info;
	LinkedList<DT>* _next;

private:
	void copy(const LinkedList<DT>& list);//copymethod

public:
	LinkedList(); //empty likedlist constructor
	LinkedList(const DT& info); //initiate list with a object
	LinkedList(const DT& info, LinkedList<DT>* next);//initiate with obejct and the next list
	LinkedList(const LinkedList<DT>& list);//copy constructor
	~LinkedList();//destructor
	void operator= (const LinkedList<DT> list);//copy operator function
	DT* info();//get the info method
	LinkedList<DT>* next();//get the next method
	bool isEmpty();//check if is empty in this node
	int size();//get size
	void add(const DT& object);//add object to list
	void insert(const DT& object, int position);//inset the object at specific position in list
	DT& infoAt(int position);//get the info in specific position in list
	LinkedList<DT>* setNext(LinkedList<DT>* newList);//attach the new list to this node
	DT& find(const DT& key);//find the list and return that list found
	int findIndex(const DT& key, int position);//find the node position in this list 
	DT remove();//remove the this node and return the object in this node
	DT removeAt(int position);//remove the object in the specific position in this list
	DT remove(const DT& key);//remove the specific object in the this list
	void display(ostream& s);//printer the list


};
//empty constructor
template<class DT>
LinkedList<DT>::LinkedList() {
	_info = NULL;
	_next = NULL;
}
/**
 initiate list with a object
 @paramater object need to add into this list
*/
template<class DT>
LinkedList<DT>::LinkedList(const DT& info) {
	_info = new DT(info);
	_next = NULL;
}
/**
 initiate with obejct and the next list
 @paramater info need to initiate the list
 @paramater next need to initiate the list
*/
template <class DT>
LinkedList<DT>::LinkedList(const DT& info, LinkedList<DT>* next) {
	_info = new DT(info);
	_next = next;
}

/**
	copy constructor
	@paramater list:LinkedList<DT>& copy this
*/
template <class DT>
LinkedList<DT>::LinkedList(const LinkedList<DT>& list) {
	copy(list);
}
/**
	destructor
*/
template <class DT>
LinkedList<DT>::~LinkedList() {
	if (_info != NULL) {
		delete _info;
		_info = NULL;
	}
	if (_next != NULL) {
		delete _next;
		_next = NULL;
	}
}

/**
	overload the = that copy the list
	@paramater list: linkedList<DT>
*/
template <class DT>
void LinkedList<DT>::operator=(const LinkedList<DT> list) {
	if (_info != NULL) {
		delete _info;
		_info = NULL;
	}
	if (_next != NULL) {
		delete _next;
		_next = NULL;
	}
	copy(list);
}
/**
	copy method that is private
	@paramater list: linkedList<DT>
*/
template <class DT>
void LinkedList<DT>::copy(const LinkedList<DT>& list) {
	if (list._info == NULL) _info = NULL;
	else {
		_info = new DT(*list._info);
		if (_info == NULL) throw LinkedListMemory();
	}
	if (list._next == NULL) _next = NULL;
	else {
		_next = new LinkedList<DT>(*(list._next));
		if (_next == NULL) throw LinkedListBounds();
	}
}
/**
	get the info method
	@paramater info DT*
*/
template <class DT>
DT* LinkedList<DT>::info() {
	return _info;
}
/**
get the next list method
@paramater list LinkedList<DT>*
*/
template <class DT>
LinkedList<DT>* LinkedList<DT>::next() {
	return _next;
}
/**
check if empty method
@return bool
*/
template <class DT>
bool LinkedList<DT>::isEmpty() {
	return (_info == NULL);
}
/**
get the size of the list method
@return size: int
*/
template <class DT>
int LinkedList<DT>::size() {
	if (_next == NULL) {
		if (_info == NULL) {
			return 0;
		}
		else {
			return 1;
		}
	}
	else {
		return 1 + _next->size();
	}
}

/**
add object to list method
@paramater object: DT&
*/
template <class DT>
void LinkedList<DT>::add(const DT& object) {
	if (_info == NULL) {
		_info = new DT(object);
		if (_info == NULL) throw LinkedListMemory();
	}
	else {
		LinkedList<DT>* newList = new LinkedList<DT>(*_info, _next);
		*_info = object;
		_next = newList;
	}
}
/**
insert the object int the specific position
@paramater object: DT&
@paramater position: int
*/
template <class DT>
void LinkedList<DT>::insert(const DT& object, int position) {
	if (position == 0) {
		add(object);
	}
	else {
		if (_next == NULL) {
			_next = new LinkedList<DT>(object);
			if (_next == NULL) throw LinkedListMemory();
		}
		else {
			return _next->insert(object, position - 1);
		}
	}
}
/**
get the info from the specific position
@paramater position: int
*/
template <class DT>
DT& LinkedList<DT>::infoAt(int position) {
	if (position < 0 || position >= size()) {
		throw LinkedListBounds();
	}

	if (position == 0) return *_info;
	else {
		return _next->infoAt(position - 1);
	}
}
/**
Attach the new next list to the this list
@paramater newList: LinkedList<DT>*
*/
template <class DT>
LinkedList<DT>* LinkedList<DT>::setNext(LinkedList<DT>* newList) {
	if (isEmpty()) throw LinkedListAttachToEmpty();
	LinkedList<DT>* oldList = _next;
	_next = newList;
	return oldList;
}
/**
find the object from list
@paramater key: DT&
@return target Object: DT&
*/
template <class DT>
DT& LinkedList<DT>::find(const DT& key) {
	if (isEmpty()) throw LinkedListNotFound();
	if (*_info == key) return *_info;
	if (_next == NULL) throw LinkedListBounds();
	return _next->find(key);
}
/**
find the obeject
@paramater key: DT&
@paramater position: int  the first index 0
@return position: int that object store
*/
template <class DT>
int LinkedList<DT>::findIndex(const DT& key, int position) {
	if (isEmpty()) return -1;
	if (*_info == key) return position;
	if (_next == NULL) return -1;
	return _next->findIndex(key, position + 1);
}
/**
remove the first object from the list
@return the object removed: DT&
*/
template <class DT>
DT LinkedList<DT>::remove() {
	if (isEmpty()) throw LinkedListBounds();
	DT temp = *_info;
	delete _info;
	if (_next == NULL) {
		_info = NULL;
	}
	else {
		LinkedList<DT>* oldList = _next;
		_info = _next->_info;
		_next = _next->_next;
		oldList->_info = NULL;
		oldList->_next = NULL;
		delete oldList;
	}
	return temp;
}

/**
remove the object at the specific postion
@paramater position: int
@return target removed: DT&
*/
template <class DT>
DT LinkedList<DT>::removeAt(int position) {
	if (position >= size() || position < 0) throw LinkedListBounds();
	if (position == 0) return remove();
	return _next->removeAt(position - 1);
}
/**
remove the specific object in the list
@paramater key: DT& need to remove
@return target object removed: DT&
*/
template <class DT>
DT LinkedList<DT>::remove(const DT& key) {
	if (isEmpty()) throw LinkedListBounds();
	if (*_info == key) return remove();
	if (_next == NULL) throw LinkedListBounds();
	return _next->remove(key);
}
/**
method that overload the operator<< to print
@paramater s: ostrem&
@paramater list: LinkedList<DT>&
return ostream&
*/
template<class DT>
ostream& operator<< (ostream& s, LinkedList<DT>& list) {
	list.display(s);
	return s;
}
/**
display method to print the message
@paramater s: ostream&
*/
template <class DT>
void LinkedList<DT>::display(ostream& s) {
	if (_info != NULL) {
		s << _info;
	}
	if (_next != NULL) {
		return _next->display();
	}
}
/**
process method indicate the process need memory status
demostrate in the text book chap4 the last page
*/
class Process {
	friend ostream& operator<< (ostream& s, Process& p);//overload method
private:
	void copy(const Process& newP);//copy method

public:
	int beginAddress;
	int endAddress;
	bool hole;//check if this block is free memory
	int processID;//-1 means print all free memory amout 0:print the process start and end address
	Process();//empty constructor
	Process(const int b, const int e, const bool hole, const int id);//initate constructor
	Process(const Process& newP);//copy constructor
	~Process() {};//destructor
	void operator= (const Process& newP);//overload the operator = copy method
	bool operator== (const Process& newP);//statement check overload the operator==
	int getMemorySize();//get the memory size in the list block
	void changeSize(int size);//change memory size of this block
	bool allocate(const int id, const int size);//alloacate the memory
	void display(ostream& s);//display method for printing

};
/**
display method for printing
@paramater s: ostream&
@return void
*/
void Process::display(ostream& s) {
	s << "Start Address: " << beginAddress << "                " << "End Address: " << endAddress << endl;
}

/**
operator<< overload for print
@paramater s: ostream&
@paramater p: Process& to print
@return ostream&
*/
ostream& operator<< (ostream& s, Process& p) {
	p.display(s);
	return s;
}

/**
default constructor
data is to fit this project
*/
Process::Process() {
	beginAddress = 1;
	endAddress = 128;
	hole = true;
	processID = -1;
}
/**
initate constructor
@paramater b: int beginAddress
@paramater e: int endAddress
@paramater hole: bool check if this block is hole(free memory)
@paramater id: int process ID
*/
Process::Process(const int b, const int e, const bool hole, const int id) {
	beginAddress = b;
	endAddress = e;
	this->hole = hole;
	processID = id;
}
/**
copy constructor
@paramater newP: Process& to copy
*/
Process::Process(const Process& newP) {
	copy(newP);
}
/**
overload operator to copy the other obejct
@parmater newP: Process& to copy
*/
void Process::operator=(const Process& newP) {
	copy(newP);
}
/**
overload operator== 
@paramater newP: Process to compare if they are same
@return bool
*/
bool Process::operator==(const Process& newP) {
	return(processID == newP.processID);
}
/**
copy method
@paramater newP: Process& for copy
*/
void Process::copy(const Process& newP) {
	beginAddress = newP.beginAddress;
	endAddress = newP.endAddress;
	hole = newP.hole;
	processID = newP.processID;
}
/**
get the memory size of this block
@return size of memory: int
*/
int Process::getMemorySize() {
	return endAddress + 1 - beginAddress;
}
/**
change the size of this block,
@paramater size: int change size
*/
void Process::changeSize(const int size) {
	if (!hole) {
		if (size == 0) {
			hole = true;
			processID = -1;
		}
		else {
			endAddress = endAddress + size;
		}
	}
	else {
		beginAddress = beginAddress - size;
	}
}
/**
alloacate the memory size for the process
@paramater size:int
@paramater id: int
@reutn bool true is sucessfully
*/
bool Process::allocate(const int id, const int size) {
	if (getMemorySize() >= size) {
		hole = false;
		endAddress = beginAddress + size - 1;
		processID = id;//bug
		return true;
	}
	else {
		return false;
	}
}

/**
compaction method to make the memory contiguous
@paramater list: LinkedList<DT>& main memory block
*/
template <class DT>
void compaction(LinkedList<DT>& list) {
	int size = 0;// size of the block or process
	try {
		for (int i = list.size(); i >= 0; i--) {
			if (list.infoAt(i).hole && i > 0) {
				if (!list.infoAt(i - 1).hole) {
					size = list.infoAt(i - 1).getMemorySize();
					list.infoAt(i).endAddress = size + list.infoAt(i).beginAddress - 1;
					list.infoAt(i).hole = false;
				}
				else {
					list.infoAt(i).endAddress = list.infoAt(i - 1).endAddress;
					list.removeAt(i - 1);
				}
			}
		}
	}
	catch (LinkedListException& e) {
		cout << "Error occured during Compaction the memory! " << e.what() << endl;
	}
}


void main() {
	Process partition = Process();//initiate the memory size 128k, free memory
	LinkedList<Process>* list = new LinkedList<Process>(partition);//add the this block into list
	int memorySize, id, endNumber, pSize, position;

	while (!cin.eof()) {//read the file
		cin >> id >> pSize;//read the data from file
		position = list->findIndex(Process(1, pSize, false, id), 0);
		if (id > 0) {
			if (position >= 0) {//if found the same process
				if (pSize > 0) {//allocate addition memory
					if (position > 0) {//check behind the current block, if there is more free memory
						try {
							if ((list->infoAt(position - 1).hole) && (list->infoAt(position - 1).getMemorySize() >= pSize)) {//check if there is more memory size
								list->infoAt(position).changeSize(pSize);
								if (list->infoAt(position - 1).getMemorySize() == pSize)
									list->removeAt(position - 1);
								else
									list->infoAt(position - 1).changeSize(pSize);
							}
						}
						catch (LinkedListException& e) {
							cout << "Error ocurred during changging the process in list!" << e.what() << endl;
						}
					}
					else {
						try {
							cout << "Connot alloacate more memory for the Process: " << list->infoAt(position).processID;
						}
						catch (LinkedListException& e) {
							cout << "Error ocurred during return alloacate fail message!" << e.what() << endl;
						}
					}
				}
				else {//deallocate the memory
					try {
						list->infoAt(position).changeSize(pSize);
						if (position > 0) {//check if there are more blocks behind this block
							list->infoAt(position - 1).changeSize(pSize);//move the free memory to current block
						}
						else {//there is no more block behind this block so create new one the hold the free memory
							list->add(Process(list->infoAt(0).endAddress + 1, list->infoAt(0).endAddress - 1 - pSize, true, -1));
							
						}
					}
					catch (LinkedListException& e) {
						cout << "Error ocurred during specific process in list free the memory!" << e.what() << endl;
					}
				}
			}
			else {
				try {//add new process to list, alloacate the new process
					for (int i = list->size() - 1; i >= 0; i--) {//go through the list to find the free memory to allocate
						bool isAllocated = false;//check if allocate successfully
						if (list->infoAt(i).hole) {//check if the block is free memory block
							//alloacating the process
							endNumber = list->infoAt(i).endAddress;
							isAllocated = list->infoAt(i).allocate(id, pSize);
							//checkt if it is empty block with free memory
							if (isAllocated && list->infoAt(i).getMemorySize() >= pSize) {//
								if (list->infoAt(i).getMemorySize() == pSize) {//this block's memory is equal to the process memory size so quit the loop
									break;
								}
								else {//after add the process to the block, there is some free memory, move the free memory away
									list->insert(Process(list->infoAt(i).endAddress + 1, endNumber, true, -1), i);
									break;
								}
							}
							if ((!isAllocated) && i == 0) {// complete the for loop, alloacate fail means no more free memory to alloacate
								cout << "Connote allocate the momory for Process: " << id << endl;
							}
						}
					}
				}
				catch (LinkedListException& e) {
					cout << "Error ocurred during alloacate the new process in to main memory!" << e.what() << endl;
				}


			}
		}
		else if (id == 0) {//print each content in list
			cout << list << endl;
		}
		else {//print amout of free memory
			int amout = 0;
			for (int i = 0; i < list->size(); i++) {
				if (list->infoAt(i).hole) {
					amout = amout + list->infoAt(i).getMemorySize();
				}
			}
			cout << "Available Momory is: " << amout << "KB." << endl;
		}

		compaction(*list);//compaction the memory
		
	}
	
}
