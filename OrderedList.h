#ifndef _ORDERED_LIST_GUARD
#define _ORDERED_LIST_GUARD 1

using namespace std;

template <class T>
class OrderedList
{

	private:
		struct Node
		{
			T value;
			struct Node *nextNode;
		};
		Node *firstNode;
		int length;
		int (*defaultCompare)(T, T);

	public:
		OrderedList(int (*dc)(T, T))
		{
			firstNode = nullptr;
			length = 0;
			defaultCompare = dc;
		}

		~OrderedList()
		{
			if(firstNode != nullptr)
			{
				Node* temp = firstNode;
				while(temp != nullptr)
				{
					Node* del  = temp;
					temp = temp->nextNode;
					delete del;
				}
			}
		}

		int getLength();
		bool remove(T target);
		bool insert(T newItem);
		T *search(T target);
		void traverse(void (*visit)(int, T));
		double traverseDouble(double initialValue, double (*visit)(double, T));
		int traverseInt(int initialValue, int (*visit)(int, T));
		void traverseOut(ofstream *f, void (*visit)(ofstream *, T));
};
template <class T>
int OrderedList<T>::getLength()
{
	return length;
}
template <class T>
T *OrderedList<T>::search(T target)
{
	Node* temp = firstNode;
	for(int i = 0; i < length; i++)
	{
		if(defaultCompare(target, temp->value) == 0)
		{
			return &(temp->value);
		}
	}
	return nullptr;
}
template <class T>
bool OrderedList<T>::insert(T newItem)
{
	Node* newNode = new Node;
	newNode->value = newItem;
	newNode->nextNode = nullptr;
	if(firstNode == nullptr)
	{
		firstNode = newNode;
		length += 1;
		return true;
	}
	Node* temp = firstNode;
	while(temp->nextNode != nullptr)
	{
		if(defaultCompare(temp->value, newItem) == 0)
		{
			return false;
		}
		temp = temp->nextNode;
	}
	temp->nextNode = newNode;
	length += 1;
	return true;
}
template <class T>
bool OrderedList<T>::remove(T target)
{
	Node* ptr = firstNode;
	Node* prevNode;
	if(ptr != nullptr && (defaultCompare(ptr->value, target) == 0))
	{
		firstNode = ptr->nextNode;
		delete ptr;
		length -= 1;
		return true;
	}
	while(ptr != nullptr && (defaultCompare(ptr->value, target) != 0))
	{
		prevNode = ptr;
		ptr = ptr->nextNode;
	}
	if(ptr == nullptr)
	{
		return false;
	}
	prevNode->nextNode = ptr->nextNode;
	delete ptr;
	length -= 1;
	return true;
}
template <class T>
void OrderedList<T>::traverse(void (*visit)(int, T))
{
	Node* temp = firstNode;
	for(int i = 0; i < length; i++)
	{
		visit(i, temp->value);
		temp = temp->nextNode;
	}
}
template <class T>
double OrderedList<T>::traverseDouble(double initialValue, double (*visit)(double, T))
{
	double val = initialValue;
	Node* temp = firstNode;
	while(temp != nullptr)
	{
		val = visit(val, temp->value);
		temp = temp->nextNode;
	}
	return val;
}
template <class T>
int OrderedList<T>::traverseInt(int initialValue, int (*visit)(int, T))
{
	int val = initialValue;
	Node* temp = firstNode;
	while(temp != nullptr)
	{
		val = visit(val, temp->value);
		temp = temp->nextNode;
	}
	return val;
}
template <class T>
void OrderedList<T>::traverseOut(ofstream *f, void (*visit)(ofstream *, T))
{
	Node* temp = firstNode;
	while(temp != nullptr)
	{
		visit(f, temp->value);
		temp = temp->nextNode;
	}
}

#endif
