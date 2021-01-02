#ifndef UTILITY_BIT_HELPER_HPP
#define UTILITY_BIT_HELPER_HPP

#define BIT_UP(var, bit)		((var) |= (1 << (bit)))
#define BIT_DOWN(var, bit)		((var) &= ~(1 << (bit)))
#define IS_BIT_UP(var, bit)	(((var) & (1 << (bit))) != 0)

#define BIT_SET(port, pin, val) (((val) > 0) ? PIN_ON((port),(pin)) : PIN_OFF((port),(pin)))

namespace utility::bit
{
	constexpr auto set(auto& value, int bit)		{ BIT_UP(value, bit); }
	constexpr auto unset(auto& value, int bit)	{ BIT_DOWN(value, bit); }
	constexpr bool is_set(auto& value, int bit)	{ IS_BIT_UP(value, bit); }
	constexpr auto toggle(auto& value, int bit) { IS_BIT_UP(value, bit) ? BIT_DOWN(value, bit) : BIT_UP(alue, bit); }
}

#endif
