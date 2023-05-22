#pragma once

#include "feasy.hpp"
#include <utility>

namespace feasy
{
	template <typename T>
	class FEASY_API Ref
	{
	public:
		Ref() : m_ptr(nullptr), m_refCount(nullptr) {}
		explicit Ref(T *ptr) : m_ptr(ptr), m_refCount(new size_t(1)) {}
		Ref(const Ref<T> &other) : m_ptr(other.m_ptr), m_refCount(other.m_refCount)
		{
			if (m_refCount)
				++(*m_refCount);
		}
		Ref(Ref<T> &&other) noexcept : m_ptr(other.m_ptr), m_refCount(other.m_refCount)
		{
			other.m_ptr = nullptr;
			other.m_refCount = nullptr;
		}
		~Ref()
		{
			release();
		}

		Ref<T> &operator=(const Ref<T> &other)
		{
			if (this != &other)
			{
				release();
				m_ptr = other.m_ptr;
				m_refCount = other.m_refCount;
				if (m_refCount)
					++(*m_refCount);
			}
			return *this;
		}

		Ref<T> &operator=(Ref<T> &&other) noexcept
		{
			if (this != &other)
			{
				release();
				m_ptr = other.m_ptr;
				m_refCount = other.m_refCount;
				other.m_ptr = nullptr;
				other.m_refCount = nullptr;
			}
			return *this;
		}

		T *get() const { return m_ptr; }
		T &operator*() const { return *m_ptr; }
		T *operator->() const { return m_ptr; }
		explicit operator bool() const { return m_ptr != nullptr; }

	private:
		T *m_ptr;
		size_t *m_refCount;

		void release()
		{
			if (m_refCount)
			{
				--(*m_refCount);
				if (*m_refCount == 0)
				{
					delete m_ptr;
					delete m_refCount;
				}
			}
		}
	};

	template <typename T, typename... Args>
	Ref<T> createRef(Args &&...args)
	{
		return Ref<T>(new T(std::forward<Args>(args)...));
	}
}