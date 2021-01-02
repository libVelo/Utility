#ifndef UTILITY_DEBUG_HPP
#define UTILITY_DEBUG_HPP

#ifndef NDEBUG
	#include<iostream>
	#define DEBUG(X) std::clog << "DEBUG: " << (X) << std::endl
	#define WATCH(X) std::clog << (#X) << " = " << (X) << std::endl
#else //NDEBUG
	#define DEBUG(X)
	#define WATCH(X)
#endif //NDEBUG

namespace utility
{
	struct debug
	{
		 template<typename T>
		 debug& operator<<(T t)
		 {
#ifndef NDEBUG
			std::clog << t;
#endif
			return *this;
		 }
	};
}

#endif
