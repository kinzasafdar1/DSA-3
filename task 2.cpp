#include <iostream>
using namespace std;

template <typename Type>
class List {
protected:
	Type* arr;
	int maxSize;
	int currentSize;

public:
	List(int size = 10) {
		maxSize = size;
		currentSize = 0;
		arr = new Type[maxSize];
	}

	List(const List<Type>& other) {
		maxSize = other.maxSize;
		currentSize = other.currentSize;
		arr = new Type[maxSize];
		for (int i = 0; i < currentSize; i++) {
			arr[i] = other.arr[i];
		}
	}

	virtual ~List() {
		delete[] arr;
	}

	virtual void addElementAtFirstIndex(Type element) = 0;
	virtual void addElementAtLastIndex(Type element) = 0;
	virtual void removeElementAtFirstIndex() = 0;
	virtual void removeElementAtLastIndex() = 0;
	virtual void display() const = 0;
};

template <typename Type>
class MyList : public List<Type> {
public:
	MyList(int size = 10) : List<Type>(size) {}

	MyList(const MyList<Type>& other) : List<Type>(other) {}

	~MyList() {};

	bool empty() {
		if (this->currentSize == 0)
		{
			return true;
		}
		return false;
	}

	bool full() {
		if (this->currentSize == this->maxSize)
		{
			return true;
		}
		return false;
	}

	int size() {
		return this->currentSize;
	}

	bool insertAt(int index, Type value) {
		if (index < 0 || index > this->currentSize) {
			cout << "Error: Invalid index for insertion!" << endl;
			return false;
		}
		if (full()) {
			cout << "Error: List is full!" << endl;
			return false;
		}
		for (int i = this->currentSize; i > index; i--) {
			this->arr[i] = this->arr[i - 1];
		}
		this->arr[index] = value;
		this->currentSize++;
		return true;
	}

	Type last() {
		if (!empty()) {
			return this->arr[this->currentSize - 1];
		}
		cout << "Error: List is empty, cannot retrieve last element!" << endl;
		return Type();
	}

	bool search(Type value) {
		for (int i = 0; i < this->currentSize; i++) {
			if (this->arr[i] == value) {
				return true;
			}
		}
		return false;
	}

	void addElementAtFirstIndex(Type element) {
		insertAt(0, element);
	}

	void addElementAtLastIndex(Type element) {
		insertAt(this->currentSize, element);
	}

	void removeElementAtFirstIndex() {
		if (!empty()) {
			for (int i = 0; i < this->currentSize - 1; i++) {
				this->arr[i] = this->arr[i + 1];
			}
			this->currentSize--;
		}
		else {
			cout << "Error: List is already empty!" << endl;
		}
	}

	void removeElementAtLastIndex() {
		if (!empty()) {
			this->currentSize--;
		}
		else {
			cout << "Error: List is already empty!" << endl;
		}
	}

	void display() const override {
		cout << "List elements: ";
		for (int i = 0; i < this->currentSize; i++) {
			cout << this->arr[i] << " ";
		}
		cout << endl;

	}
};

int main() {
	MyList<int> myList(5);
	int choice, value, index;

	do {
		cout << "\nMenu:" << endl;
		cout << "1. Add at First Index" << endl;
		cout << "2. Add at Last Index" << endl;
		cout << "3. Insert at Index" << endl;
		cout << "4. Remove First Element" << endl;
		cout << "5. Remove Last Element" << endl;
		cout << "6. Display List" << endl;
		cout << "7. Check if Empty" << endl;
		cout << "8. Check if Full" << endl;
		cout << "9. Get Size" << endl;
		cout << "10. Search Value" << endl;
		cout << "11. Get Last Element" << endl;
		cout << "12. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Enter value: ";
			cin >> value;
			myList.addElementAtFirstIndex(value);
			break;
		case 2:
			cout << "Enter value: ";
			cin >> value;
			myList.addElementAtLastIndex(value);
			break;
		case 3:
			cout << "Enter index and value: ";
			cin >> index >> value;
			if (!myList.insertAt(index, value)) {
				cout << "Insertion failed!" << endl;
			}
			break;
		case 4:
			myList.removeElementAtFirstIndex();
			break;
		case 5:
			myList.removeElementAtLastIndex();
			break;
		case 6:
			myList.display();
			break;
		case 7:
			cout << (myList.empty() ? "List is empty." : "List is not empty.") << endl;
			break;
		case 8:
			cout << (myList.full() ? "List is full." : "List is not full.") << endl;
			break;
		case 9:
			cout << "Current size of list: " << myList.size() << endl;
			break;
		case 10:
			cout << "Enter value to search: ";
			cin >> value;
			cout << (myList.search(value) ? "Value found!" : "Value not found!") << endl;
			break;
		case 11:
			cout << "Last element: " << myList.last() << endl;
			break;
		case 12:
			cout << "Exiting program. Goodbye!" << endl;
			break;
		default:
			cout << "Invalid choice! Please try again." << endl;
		}
	} while (choice != 12);

	system("pause");
	return 0;
}