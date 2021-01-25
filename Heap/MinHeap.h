#pragma once
#include "Heap.h"


template<class T>
class MinHeap : public Heap<T>
{
public:

	MinHeap() = default;
	MinHeap(size_t size) : Heap<T>(size) {}

	virtual void insertElement(T element);
	virtual T extractNext();

private:



};

template<class T>
inline void MinHeap<T>::insertElement(T element)
{
	this->m_hArr.push_back(element);
}

template<class T>
inline T MinHeap<T>::extractNext()
{
	if (this->m_hArr.size() == 0)
		return 0;
	else if (this->m_hArr.size() == 1)
	{
		T data = this->m_hArr[this->m_hArr.size() - 1];
		this->m_hArr.clear();
		return data;
	}
	else
	{
		size_t index = this->m_hArr.size();
		index = this->getParent(index);

		size_t leftChild = this->getChild(index);
		size_t rightChild = leftChild + 1;

		if (rightChild > this->m_hArr.size())
			rightChild = this->m_hArr.size();

		while (index >= 1)
		{
			try
			{
				if (this->m_hArr[index - 1] > this->m_hArr[leftChild - 1])
				{
					this->swap(index, leftChild);
				}
				else if (this->m_hArr[index - 1] > this->m_hArr[rightChild - 1])
				{
					this->swap(index, rightChild);
				}
				else
				{
					index--;
					if (index > 0)
					{
						leftChild = this->getChild(index);
						rightChild = leftChild + 1;

						if (rightChild > this->m_hArr.size())
							rightChild = this->m_hArr.size();
					}
				}
			}
			catch (std::exception e)
			{
				std::cout << e.what() << std::endl;
			}
		}

		if (this->m_hArr.size() > 1)
		{
			// swap item on top to the end
			this->swap(1, this->m_hArr.size());
		}

		T data = this->m_hArr[this->m_hArr.size()-1];
		this->m_hArr.pop_back();
		return data;
	}
}
