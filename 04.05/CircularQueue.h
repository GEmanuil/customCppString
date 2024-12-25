#pragma once
#include <iostream>

template<typename T>
class CircularQueue
{
public:
	CircularQueue(const size_t queueSize = 16);
	CircularQueue(const CircularQueue& other);
	CircularQueue& operator=(const CircularQueue& other);
	~CircularQueue();


	// adds an element
	void enqueue(const T& element);

	// removes an element
	T dequeue();

	
	bool isEmpth() const;

	size_t count() const;

	void printQueue() const;

private:
	T* arr = nullptr;
	size_t arrSize;
	// beging and end act as indecies for the next element (are not indecies)
	size_t begin, end;

	void free();
	bool isFull() const;
	void increaseSize();

};

template<typename T>											 // !! The array will always have as a actual size + 1 
inline CircularQueue<T>::CircularQueue(const size_t queueSize) : arr(new T[queueSize + 1]), arrSize(queueSize + 1), begin(0), end(0) {}

template<typename T>
inline CircularQueue<T>::CircularQueue(const CircularQueue& other) : arr(new T[other.queueSize]), arrSize(other.arrSize), begin(other.begin), end(other.end)
{
	for (int i = 0; i < this->arrSize; i++)
	{
		this->arr[i] = other.arr[i];
	}
}

template<typename T>
inline CircularQueue<T>& CircularQueue<T>::operator=(const CircularQueue& other)
{
	if (this != &other)
	{
		free();

		this->arrSize = other.arrSize;
		this->begin = other.begin;
		this->end = other.end;

		arr = new T[other.arrSize];
		for (int i = 0; i < arrSize; i++)
		{
			arr[i] = other.arr[i];
		}
	}
	return *this;
}

template<typename T>
inline CircularQueue<T>::~CircularQueue()
{
	free();
}

template<typename T>
inline void CircularQueue<T>::enqueue(const T& element)
{
	if (isFull())
	{
		increaseSize();
	}
	arr[end % arrSize] = element;
	end++;
}

template<typename T>
inline T CircularQueue<T>::dequeue()
{
	if (isEmpth())
	{
		throw std::out_of_range("no more elements in the queue");
	}
	T result = arr[begin % arrSize];
	begin++;
	return result;
}

template<typename T>
inline void CircularQueue<T>::free()
{
	delete[] arr;
	arr = nullptr;
}

template<typename T>
inline void CircularQueue<T>::increaseSize()
{
	size_t newSize = arrSize * 2 - 1;
	size_t elCount = count();
	T* temp = new T[newSize];
	
	for (int i = 0; !isEmpth(); i++)
	{
		temp[i] = dequeue();
	}

	begin = 0;
	end = elCount;
	arrSize = newSize;
	free();
	arr = temp;

}

template<typename T>
inline bool CircularQueue<T>::isFull() const
{
	return (end + 1) % arrSize == begin;
}

template<typename T>
inline bool CircularQueue<T>::isEmpth() const
{
	return begin == end;
}

template<typename T>
inline size_t CircularQueue<T>::count() const
{
	return ((end - begin) % arrSize);
}

template<typename T>
inline void CircularQueue<T>::printQueue() const
{
	std::cout << std::endl << "Queue: ";
	for (int i = 0; i < count(); i++)
	{
		std::cout << arr[(i + begin) % (arrSize)] << " ";
	}
	std::cout << std::endl;
}
