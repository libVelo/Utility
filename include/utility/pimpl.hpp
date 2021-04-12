#ifndef UTILITY_PIMPL_HPP
#define UTILITY_PIMPL_HPP

#include<type_traits>
#include<new>

namespace utility
{
	template<typename T, size_t Size, size_t Alignment>
	struct pimpl
	{
		template<typename... Args>
		explicit pimpl(Args&&... args) { new(ptr()) T(std::forward<Args>(args)...);  }
		
		pimpl& operator=(pimpl&& rhs)
		{
			*ptr() = std::move(*rhs);
			return *this;
		}

		~pimpl() noexcept
		{
			validate<sizeof(T), alignof(T)>();
			ptr()->~T();
		}

		T* operator->() noexcept { return ptr(); }
		const T* operator->() const noexcept { return ptr(); }

		T& operator*() noexcept { return *ptr(); }
		const T& operator*() const noexcept { return *ptr(); }

	private:
		template<size_t ActualSize, size_t ActualAlignmrnt>
		void validate() noexcept
		{
			static_assert(Size == ActualSize, "Size mismatch");
			static_assert(Alignment == ActualAlignmrnt, "Alignment mismatch");
		}

		T* ptr() noexcept { return reinterpret_cast<T*>(&m_data); }

		std::aligned_storage<Size, Alignment> m_data;
	};
}

#endif
