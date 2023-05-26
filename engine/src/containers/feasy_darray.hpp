#pragma once

#include "feasy.hpp"
#include "platform/feasy_allocator.hpp"
#include "feasy_math.hpp"
#include "feasy_string.hpp"

namespace feasy
{
	template <typename T>
	class FEASY_API DArray
	{
	public:
		DArray(i32 capacity = 1)
			: m_capacity(capacity)
		{
			m_capacity = math::max(m_capacity, math::nextPowerOf2(capacity));
			m_ptr = Allocator::allocateBlock<T>(m_capacity);
		}

		~DArray()
		{
			Allocator::deallocateBlock<T>(m_ptr);
		}

		void push_back(const T &item)
		{
			if (m_capacity <= m_size)
				resize(m_capacity + 1);

			*(m_ptr + m_size) = item;
			m_size++;
		}

		void pop_back()
		{
			m_size--;
			Allocator::reallocateBlock(m_ptr, m_size);
		}

		void erase(T item)
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

				m_size--;
				Allocator::reallocateBlock(m_ptr, m_size);
			}
		}

		void erase(const T &item)
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

				m_size--;
				Allocator::reallocateBlock(m_ptr, m_size);
			}
		}

		void removeAt(i32 index)
		{
			// TODO: Assert (out of index)
			T *from_ptr = (m_ptr + index);
			T *last_ptr = (m_ptr + m_size);

			for (T *ptr = from_ptr; ptr != last_ptr; ptr++)
			{
				T *next = (ptr + 1);
				*ptr = *next;
			}

			m_size--;
			Allocator::reallocateBlock(m_ptr, m_size);
		}

		void resize(i32 capacity)
		{
			// TODO: use dynamic assert function
			if (capacity >= m_capacity)
			{
				m_capacity = math::max(m_capacity, math::nextPowerOf2(capacity));
			}

			Allocator::reallocateBlock<T>(m_ptr, m_capacity);
		}

		const T &operator[](i32 index) const
		{
			return *(m_ptr + index);
		}

		T *data() const { return m_ptr; }
		i32 size() const { return m_size; }

	private:
		mutable T *m_ptr;
		i32 m_size{0};
		i32 m_capacity;
	};
}