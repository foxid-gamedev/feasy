#pragma once

#include "feasy.hpp"
#include "platform/feasy_allocator.hpp"
#include <utility>

namespace feasy
{
	template <typename T>
	class FEASY_API Ref
	{
	public:
		Ref()
		{
			// m_ptr = new T();
			m_ptr = Allocator::allocate<T>();

			// m_count = new i32;
			m_count = Allocator::allocate<i32>();
			*m_count = 1;
		}

		template <typename... Args>
		Ref(Args &&...args)
		{
			// m_ptr = new T(std::forward<Args>(args)...);
			m_ptr = Allocator::allocate<T>(std::forward<Args>(args)...);
			m_count = Allocator::allocate<i32>();
			*m_count = 1;
		}

		~Ref()
		{
			decrement();
		}

		Ref(const Ref &other)
		{
			if (this == &other)
				return;
			m_ptr = other.m_ptr;
			m_count = other.m_count;
			this->increment();
		}

		Ref(Ref &&other) noexcept
		{
			m_ptr = other.m_ptr;
			m_count = other.m_count;

			other.m_ptr = nullptr;
			other.m_count = nullptr;
		}

		Ref &operator=(const Ref &other)
		{
			if (this == &other)
				return *this;
			m_ptr = other.m_ptr;
			m_count = other.m_count;
			this->increment();
			return *this;
		}

		Ref &operator=(Ref &&other) noexcept
		{
			m_ptr = other.m_ptr;
			m_count = other.m_count;
			other.m_ptr = nullptr;
			other.m_count = nullptr;

			return *this;
		}

		T *operator->() const
		{
			return m_ptr;
		}

		T &operator*()
		{
			return *m_ptr;
		}

		const T &operator*() const
		{
			return *m_ptr;
		}

	private:
		void increment()
		{
			if (m_count == nullptr)
			{
				return;
			}

			(*m_count)++;
		}

		void decrement()
		{
			if (m_count == nullptr)
			{
				return;
			}

			(*m_count)--;

			if (*m_count <= 0)
			{
				if (m_ptr == nullptr)
				{
					return;
				}

				Allocator::deallocate(m_ptr);
				Allocator::deallocate(m_count);
				// delete m_ptr;
				// delete m_count;
				// m_ptr = nullptr;
				// m_count = nullptr;
			}
		}

		mutable T *m_ptr;
		mutable i32 *m_count;
	};

	template <typename T>
	Ref<T> createRef()
	{
		return Ref<T>();
	}

	template <typename T, typename... Args>
	Ref<T> createRef(Args &&...args)
	{
		return Ref<T>(std::forward<Args>(args)...);
	}
}