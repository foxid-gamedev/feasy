#pragma once

#include "feasy.hpp"
#include <utility>

namespace feasy
{
	template <typename T>
	class FEASY_API Ref
	{
	public:
		template <typename... Args>
		explicit Ref(Args &&...args)
			: m_ptr(new T(std::forward<Args>(args)...))
		{
		}

		Ref(const Ref &other)
			: m_ptr(new T(*other.m_ptr))
		{
		}

		Ref(Ref &&other) noexcept
			: m_ptr(other.m_ptr)
		{
			other.m_ptr = nullptr;
		}

		~Ref()
		{
			delete m_ptr;
			m_ptr = nullptr;
		}

		Ref &operator=(const Ref &other)
		{
			if (this != &other)
			{
				delete m_ptr;
				m_ptr = new T(*other.m_ptr);
			}
			return *this;
		}

		Ref &operator=(Ref &&other) noexcept
		{
			if (this != &other)
			{
				delete m_ptr;
				m_ptr = other.m_ptr;
				other.m_ptr = nullptr;
			}
			return *this;
		}

		T *get() const
		{
			return m_ptr;
		}

		T &operator*() const
		{
			return *m_ptr;
		}

		T *operator->() const
		{
			return m_ptr;
		}

		explicit operator bool() const
		{
			return m_ptr != nullptr;
		}

		// ... Restlicher Code der Klasse

	private:
		T *m_ptr;
	};

	template <typename T, typename... Args>
	Ref<T> createRef(Args &&...args)
	{
		return Ref<T>(std::forward<Args>(args)...);
	}
}