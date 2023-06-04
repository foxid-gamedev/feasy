#pragma once

#include "feasy.hpp"
#include "platform/feasy_allocator.hpp"
#include "feasy_math.hpp"
#include "feasy_string.hpp"
#include <initializer_list>

namespace feasy
{
	// TODO: add runtime assertions
	template <typename T>
	class FEASY_API DArray
	{
	public:
		DArray(i32 size = 1);
		DArray(T *data, i32 size);
		DArray(const DArray &other);
		DArray(DArray &&other) noexcept;
		DArray &operator=(const DArray &other);
		DArray &operator=(DArray &&other) noexcept;
		DArray(std::initializer_list<T> initList);
		~DArray();

		void push_back(const T &item);
		void clear();
		void pop_back();
		void erase(T item);
		void erase(const T &item);
		void removeAt(i32 index);
		void resize(i32 capacity);
		const T &operator[](i32 index) const;

		T front() const { return *m_ptr; }
		T back() const { return *(m_ptr + m_size); }
		T *data() const { return m_ptr; }
		i32 size() const { return m_size; }

		T *begin() { return m_ptr; }
		T *begin() const { return m_ptr; }
		T *end() { return m_ptr + m_size; }
		T *end() const { return m_ptr + m_size; }

	private:
		mutable T *m_ptr;
		i32 m_size{0};
		i32 m_capacity;
	};
}

template <typename T>
feasy::DArray<T>::DArray(feasy::i32 size)
{
	m_size = size;
	m_capacity = math::max(size, math::nextPowerOf2(size));
	m_ptr = Allocator::allocateBlock<T>(m_capacity);
}

template <typename T>
feasy::DArray<T>::~DArray()
{
	Allocator::deallocateBlock<T>(m_ptr);
}

template <typename T>
feasy::DArray<T>::DArray(T *data, feasy::i32 size)
{
	m_capacity = math::nextPowerOf2(size);
	m_ptr = Allocator::reallocateBlock<T>(data, m_capacity);
	m_size = size;
}

template <typename T>
feasy::DArray<T>::DArray(const DArray &other)
{
	m_capacity = other.m_capacity;
	m_size = other.m_size;
	m_ptr = Allocator::copyBlock<T>(other.m_ptr, other.m_capacity);
}

template <typename T>
feasy::DArray<T>::DArray(DArray &&other) noexcept
{
	m_capacity = other.m_capacity;
	m_size = other.m_size;
	m_ptr = other.m_ptr;

	other.m_capacity = 1;
	other.m_size = 0;
	other.m_ptr = nullptr;
}

template <typename T>
feasy::DArray<T> &feasy::DArray<T>::operator=(const DArray &other)
{
	if (this == &other)
		return *this;

	m_capacity = other.m_capacity;
	m_size = other.m_size;

	m_ptr = Allocator::copyBlock<T>(other.m_ptr, other.m_capacity);

	return *this;
}

template <typename T>
feasy::DArray<T> &feasy::DArray<T>::operator=(DArray &&other) noexcept
{
	m_capacity = other.m_capacity;
	m_size = other.m_size;
	m_ptr = other.m_ptr;

	other.m_capacity = 1;
	other.m_size = 0;
	other.m_ptr = nullptr;

	return *this;
}

template <typename T>
feasy::DArray<T>::DArray(std::initializer_list<T> initList)
{
	m_size = static_cast<i32>(initList.size());
	m_capacity = math::nextPowerOf2(static_cast<i32>(initList.size()));

	m_ptr = Allocator::allocateBlock<T>(m_capacity);

	for (i32 i = 0; i < m_size; i++)
	{
		m_ptr[i] = *(initList.begin() + i);
	}
}

template <typename T>
void feasy::DArray<T>::push_back(const T &item)
{
	if (m_capacity <= m_size)
		resize(m_capacity + 1);

	*(m_ptr + m_size) = item;
	m_size++;
}

// TODO: add push_range() function to DArray

template <typename T>
void feasy::DArray<T>::clear()
{
	m_capacity = 1;
	m_size = 0;
	m_ptr = Allocator::reallocateBlock<T>(m_ptr, m_capacity);
}

template <typename T>
void feasy::DArray<T>::pop_back()
{
	m_size--;
}

template <typename T>
void feasy::DArray<T>::erase(T item)
{
	T *hit_ptr = nullptr;
	for (T *ptr = m_ptr; ptr != nullptr; ptr++)
	{
		if (*ptr == item)
		{
			hit_ptr = ptr;
			break;
		}
	}

	if (hit_ptr != nullptr)
	{
		T *last_ptr = (m_ptr + m_size);
		for (T *ptr = hit_ptr; ptr != last_ptr; ptr++)
		{
			T *next = (ptr + 1);
			*ptr = *next;
		}

		last_ptr = nullptr;
		m_size--;
	}
}

template <typename T>
void feasy::DArray<T>::erase(const T &item)
{
	T *hit_ptr = nullptr;
	for (T *ptr = m_ptr; ptr != nullptr; ptr++)
	{
		if (ptr == &item)
		{
			hit_ptr = ptr;
			break;
		}
	}

	if (hit_ptr != nullptr)
	{
		T *last_ptr = (m_ptr + m_size);
		for (T *ptr = hit_ptr; ptr != last_ptr; ptr++)
		{
			T *next = (ptr + 1);
			*ptr = *next;
		}

		last_ptr = nullptr;
		m_size--;
	}
}

template <typename T>
void feasy::DArray<T>::removeAt(feasy::i32 index)
{
	// TODO: Assert (out of index)
	T *from_ptr = (m_ptr + index);
	T *last_ptr = (m_ptr + m_size);

	for (T *ptr = from_ptr; ptr != last_ptr; ptr++)
	{
		T *next = (ptr + 1);
		*ptr = *next;
	}

	last_ptr = nullptr;
	m_size--;
}

template <typename T>
void feasy::DArray<T>::resize(feasy::i32 capacity)
{
	// TODO: use dynamic assert function
	if (capacity >= m_capacity)
	{
		m_capacity = math::max(m_capacity, math::nextPowerOf2(capacity));
	}

	m_ptr = Allocator::reallocateBlock<T>(m_ptr, m_capacity);
}

template <typename T>
const T &feasy::DArray<T>::operator[](feasy::i32 index) const
{
	return *(m_ptr + index);
}