#pragma once

#include "feasy.hpp"
#include <utility>
#include <cstring>

namespace feasy
{
	// TODO: write a pool allocator instead
	class Allocator
	{
	public:
		template <typename T>
		inline static T *allocate()
		{
			return new T();
		}

		template <typename T, typename... Args>
		inline static T *allocate(Args &&...args)
		{
			return new T(std::forward<Args>(args)...);
		}

		template <typename T>
		inline static T *allocateBlock(i64 block)
		{
			return new T[block];
		}

		template <typename T, typename... Args>
		inline static T *allocateBlock(i64 block, Args &&...args)
		{
			return new T[block](std::forward(args)...);
		}

		template <typename T>
		inline static void deallocate(T *data)
		{
			delete data;
			data = nullptr;
		}

		template <typename T>
		inline static void deallocateBlock(T *data)
		{
			delete[] data;
			data = nullptr;
		}

		template <typename T>
		inline static T *reallocateBlock(T *data, i64 block)
		{
			T *newData = allocateBlock<T>(block);
			std::memcpy(newData, data, block);
			deallocateBlock(data);
			return newData;
		}

		template <typename T>
		inline static T *copyBlock(T *data, i64 block)
		{
			T *newData = allocateBlock<T>(block);
			std::memcpy(newData, data, block);
			return newData;
		}
	};
}
