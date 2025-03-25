#include <iostream>
using namespace std;

template <typename Type>
class List
{
protected:
	Type* arr;
	int maxSize;
	int currentSize;

public:
	// Parameterized constructor with default arguments
	List(int size = 10)
	{
		maxSize = size;
		currentSize = 0;
		arr = new Type[maxSize];
	}

	// Copy constructor
	List(const List<Type>& other)
	{
		maxSize = other.maxSize;
		currentSize = other.currentSize;
		arr = new Type[maxSize];
		for (int i = 0; i < currentSize; ++i)
		{
			arr[i] = other.arr[i]; 
		}
	}

	// Destructor
	virtual ~List() 
	{
		delete[] arr;
	}

	// Pure virtual functions
	virtual void addElementAtFirstIndex(Type element) = 0;
	virtual void addElementAtLastIndex(Type element) = 0;
	virtual void removeElementAtFirstIndex() = 0;
	virtual void removeElementAtLastIndex() = 0;
	virtual void display() const = 0;
};

template <typename Type>
class Temp : public List<Type> {
public:
	// Constructor
	Temp(int a) : List<Type>(a) {}

	// Add element at the first index
	void addElementAtFirstIndex(Type element)
	{
		if (this->currentSize < this->maxSize)
		{
			for (int i = this->currentSize; i > 0; --i) 
			{
				this->arr[i] = this->arr[i - 1];
			}
			this->arr[0] = element;
			++this->currentSize;
		}
		else
		{
			cout << "List is full!" << endl;
		}
	}

	// Add element at the last index
	void addElementAtLastIndex(Type element) 
	{
		if (this->currentSize < this->maxSize) 
		{
			this->arr[this->currentSize] = element;
			++this->currentSize; 
		}
		else 
		{
			cout << "List is full!" << endl;
		}
	}

	// Remove the element at the first index
	void removeElementAtFirstIndex() {
		if (this->currentSize > 0)
		{
			for (int i = 0; i < this->currentSize - 1; ++i)
			{
				this->arr[i] = this->arr[i + 1];
			}
			this->arr[this->currentSize - 1] = 0;
			--this->currentSize;
		}
		else
		{
			cout << "List is empty!" << endl;
		}
	}

	// Remove the element at the last index
	void removeElementAtLastIndex()
	{
		if (this->currentSize > 0) 
		{
			this->arr[this->currentSize - 1] = 0;
			--this->currentSize;
		}
		else
		{
			cout << "List is empty!" << endl;
		}
	}

	// Display the elements of the list
	void display() const override 
	{
		if (this->currentSize == 0)
		{
			cout << "List is empty!" << endl;
		}
		else 
		{
			for (int i = 0; i < this->currentSize; ++i)
			{
				cout << this->arr[i] << " ";
			}
			cout << endl;
		}
	}
};

int main() 
{
	// Create a Temp object with a list size of 5
	Temp<int> myList(5);

	myList.addElementAtFirstIndex(10);
	myList.addElementAtFirstIndex(20);
	myList.addElementAtLastIndex(30);
	myList.display();

	myList.removeElementAtFirstIndex();
	myList.display();

	myList.removeElementAtLastIndex();
	myList.display();

	system("pause");
	return 0;
}