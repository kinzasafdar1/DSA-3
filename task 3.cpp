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

	~MyList() {}

	bool empty() { return this->currentSize == 0; }
	bool full() { return this->currentSize == this->maxSize; }
	int size() { return this->currentSize; }

	bool insertAt(int index, Type value) {
		if (index < 0 || index > this->currentSize || full()) return false;
		for (int i = this->currentSize; i > index; i--) {
			this->arr[i] = this->arr[i - 1];
		}
		this->arr[index] = value;
		this->currentSize++;
		return true;
	}

	void addElementAtFirstIndex(Type element) { insertAt(0, element); }
	void addElementAtLastIndex(Type element) { insertAt(this->currentSize, element); }

	void removeElementAtFirstIndex() {
		if (!empty()) {
			for (int i = 0; i < this->currentSize - 1; i++) {
				this->arr[i] = this->arr[i + 1];
			}
			this->currentSize--;
		}
	}

	void removeElementAtLastIndex() {
		if (!empty()) this->currentSize--;
	}

	void display() const override {

		for (int i = 0; i < this->currentSize; i++) {
			cout << this->arr[i] << " ";
		}
		cout << endl;

	}
};

class CustomList : public MyList<int> {
public:
	CustomList(int size = 10) : MyList<int>(size) {}

	CustomList(const CustomList& other) : MyList<int>(other) {}

	~CustomList() {}

	bool isPrime(int num) {
		if (num < 2) return false;
		for (int i = 2; i * i <= num; i++) {
			if (num % i == 0) return false;
		}
		return true;
	}

	int sum_ofPrime() {
		int sum = 0;
		for (int i = 0; i < this->currentSize; i++) {
			if (isPrime(this->arr[i])) sum += this->arr[i];
		}
		return sum;
	}

	int secondMaxEven() {
		int max1 = -1, max2 = -1;
		for (int i = 0; i < this->currentSize; i++) {
			if (this->arr[i] % 2 == 0) {
				if (this->arr[i] > max1) {
					max2 = max1;
					max1 = this->arr[i];
				}
				else if (this->arr[i] > max2 && this->arr[i] < max1) {
					max2 = this->arr[i];
				}
			}
		}
		return max2;
	}

	int secondMinOdd() {
		int min1 = 99999, min2 = 99999;
		for (int i = 0; i < this->currentSize; i++) {
			if (this->arr[i] % 2 != 0) {
				if (this->arr[i] < min1) {
					min2 = min1;
					min1 = this->arr[i];
				}
				else if (this->arr[i] < min2 && this->arr[i] > min1) {
					min2 = this->arr[i];
				}
			}
		}
		return min2;
	}

	void printDuplicates() {
		cout << "Duplicate elements: ";
		for (int i = 0; i < this->currentSize; i++) {
			for (int j = i + 1; j < this->currentSize; j++) {
				if (this->arr[i] == this->arr[j]) {
					cout << this->arr[i] << " ";
					break;
				}
			}
		}
		cout << endl;
	}
};

int main() {
	CustomList myList(10);
	int choice, value;

	do {
		cout << "\nMenu:\n"
			<< "1. Add Element\n"
			<< "2. Display List\n"
			<< "3. Sum of Primes\n"
			<< "4. Second Max Even\n"
			<< "5. Second Min Odd\n"
			<< "6. Print Duplicates\n"
			<< "7. Exit\n"
			<< "Enter choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Enter value: ";
			cin >> value;
			myList.addElementAtLastIndex(value);
			break;
		case 2:
			myList.display();
			break;
		case 3:
			cout << "Sum of Prime Numbers: " << myList.sum_ofPrime() << endl;
			break;
		case 4:
			cout << "Second Maximum Even: " << myList.secondMaxEven() << endl;
			break;
		case 5:
			cout << "Second Minimum Odd: " << myList.secondMinOdd() << endl;
			break;
		case 6:
			myList.printDuplicates();
			break;
		case 7:
			cout << "Exiting..." << endl;
			break;
		default:
			cout << "Invalid choice!" << endl;
		}
	} while (choice != 7);

	system("pause");
	return 0;
}