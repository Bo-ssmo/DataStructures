#pragma once
#include <iostream>
#include <vector>


/*
	hArr indexes are ranging from 1 -> n, not from 0 -> n-1
*/

template<class T>
class Heap
{
public:

	Heap() = default;
	Heap(size_t size) { m_hArr.reserve(size); }

	virtual void insertElement(T element) = 0;
	virtual T extractNext() = 0;

	const size_t remainingElements() const;

protected:

	void clearElements();
	void swap(size_t first, size_t second);
	const size_t getParent(size_t index);
	const size_t getChild(size_t index);

	std::vector<T> m_hArr;

};



template<class T>
inline const size_t Heap<T>::remainingElements() const
{
	return m_hArr.size();
}

template<class T>
inline void Heap<T>::clearElements()
{
	m_hArr.clear();
	m_hArr.shrink_to_fit();
}

template<class T>
inline void Heap<T>::swap(size_t first, size_t second)
{
	if (m_hArr.size() < first || m_hArr.size() < second || first < 0 || second < 0)
	{
		std::cout << "Swap positions out of bounds!\n";
	}
	else
	{
		T temp = m_hArr[first-1];
		m_hArr[first-1] = m_hArr[second-1];
		m_hArr[second-1] = temp;
	}
}

template<class T>
inline const size_t Heap<T>::getParent(size_t index)
{
	if (index < 1 || m_hArr.size() < index)
	{
		std::cout << "Get Parent index out of bounds!\n";
	}
	else
	{
		if (index == 1)
			return 1;
		else
			return index / 2;
	}

	// this code should never be reached
	return 0;
}

template<class T>
inline const size_t Heap<T>::getChild(size_t index)
{
	if (index < 1 || m_hArr.size() < index)
	{
		std::cout << "Get Child index out of bounds!\n";
	}
	else
	{
		return index * 2;
	}

	// this code should never be reached
	return 0;
}
