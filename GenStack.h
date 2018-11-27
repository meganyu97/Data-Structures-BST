#include <iostream>

using namespace std;

template <class T> //template class with data of type T 

class GenStack
{
public:
	GenStack(int maxsize);
	~GenStack();

	int getTop();
	void setTop(int index);
	int getMax();
	void setMax(int size);
	void push(T data);
	void expand(); //used if array is full & needs more room to store data
	T pop();
	T peek(); //top
	int isFull(); //checks to see if expand method is necessary to invoke 
	bool isEmpty();

private:
	T *myArray; //used to store data of type T 
				//T *tempArray; // used when changing size of array to store data temporarily
	int top;
	int max; //sets the maximum array size 
};


//IMPLEMENTATION
template <class T>
GenStack<T>::GenStack(int maxsize)
{
	myArray = new T[maxsize];
	max = maxsize;
	top = -1; //empty array

			  //tempArray = new T[max]; //creating a temporary array so when destructor deletes, it does not delete core
}
//destructor 
template <class T>
GenStack<T>::~GenStack()
{
	delete[]myArray;
	//delete []tempArray; //clears up memory 
	cout << "Done." << endl;
}

template<class T>
void GenStack<T>::expand() //increases the size of the array when more space is necessary for data storage
{
	T *tempArray; // used when changing size of array to store data temporarily

	int tempMax = getMax();
	tempArray = new T[tempMax];

	for (int x = 0; x <= top; x++) //copies content from array to temp array to clear array for size expansion
	{
		*(tempArray + x) = *(myArray + x);
	}

	//max += 25; //increases size of array by 25
	int oldMax = getMax();
	int newMax = oldMax * 2;
	setMax(newMax);

	int oldTopIndex = getTop();
	setTop(oldTopIndex);

	delete[]myArray;
	myArray = new T[max];

	for (int x = 0; x <= top; x++) //puts all variables that were stored in temp array back into bigger array
	{
		*(myArray + x) = *(tempArray + x);
	}
	setTop(oldTopIndex);
	setMax(newMax);

	delete[]tempArray;
}

template <class T>
void GenStack<T>::push(T data)
{
	if (isFull() == 1) // checks to see if array has enough room to store data
	{
		expand();
		push(data);
	}
	else
	{
		cout << "push" << endl;
		++top;
		*(myArray + top) = data; //puts data at top of stack 
	}

}

template <class T>
T GenStack<T>::pop()
{
	if (!isEmpty())
	{
		cout << "pop" << endl;
		top--;
		return *(myArray + top); //returns the top variable in the stack and removes it
	}
}

template <class T>
T GenStack<T>::peek()
{
	if (top == -1)
	{
		cout << "The array is empty." << endl;
		return ' ';
	}
	else
	{
		return *(myArray + top); //returns the top variable in the stack, but does nothing to it. 
	}
}

template <class T>
int GenStack<T>::isFull()
{
	return (top == max - 1);
}

template <class T>
bool GenStack<T>::isEmpty() {
	return top == 0;
}

template <class T>
int GenStack<T>::getMax()
{
	return max;
}

template <class T>
void GenStack<T>::setMax(int size)
{
	max = size;
}

template <class T>
int GenStack<T>::getTop()
{
	return top;
}

template <class T>
void GenStack<T>::setTop(int index)
{
	top = index;
}