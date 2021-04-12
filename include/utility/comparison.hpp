#ifndef UTILITY_COMPARISON_HPP
#define UTILITY_COMPARISON_HPP

#include<functional>

constexpr auto tuple = [](auto ... types) { return [=](const auto& func) { return func(types...); }; };

constexpr auto and_elements = [](auto&& func) { return [func = std::forward<decltype(func)>(func)](auto ... elements) {return (func(elements) && ...); }; };
constexpr auto or_elements = [](auto&& func) { return [func = std::forward<decltype(func)>(func)](auto ... elements) {return (func(elements) || ...); }; };

constexpr auto bind_rh = [](auto func, auto rh) { return [=](auto lh) { return func(lh, rh); }; };

constexpr auto equal_to = [](auto rh) { return bind_rh(std::equal_to<decltype(rh)>{}, rh); };
constexpr auto not_equal_to = [](auto rh) { return bind_rh(std::not_equal_to<decltype(rh)>{}, rh); };

constexpr auto less_than = [](auto rh) { return bind_rh(std::less<decltype(rh)>{}, rh); };
constexpr auto less_equal_than = [](auto rh) { return bind_rh(std::less_equal<decltype(rh)>{}, rh); };

constexpr auto greater_than = [](auto rh) { return bind_rh(std::greater<decltype(rh)>{}, rh); };
constexpr auto greater_equal_than = [](auto rh) { return bind_rh(std::greater_equal<decltype(rh)>{}, rh); };

template<typename Function, typename Tuple>
struct operator_t
{
	operator_t(Function func, Tuple tuple) : m_tuple(tuple), m_func(func) {}

	template<typename T>
	constexpr auto operator==(const T& t) const { return apply(equal_to(t)); }
	template<typename T>
	constexpr auto operator!=(const T& t) const { return apply(not_equal_to(t)); }
	template<typename T>
	constexpr auto operator>(const T& t) const { return apply(greater_than(t)); }
	template<typename T>
	constexpr auto operator>=(const T& t) const { return apply(greater_equal_than(t)); }
	template<typename T>
	constexpr auto operator<(const T& t) const { return apply(less_than(t)); }
	template<typename T>
	constexpr auto operator<=(const T& t) const { return apply(less_equal_than(t)); }

private:
	template<typename F>
	auto apply(F func) const { return m_tuple(m_func(func)); }

	Tuple m_tuple;
	Function m_func;
};

constexpr auto each_of = [](auto ... types) { return operator_t<decltype(and_elements), decltype(tuple(types...))>(and_elements, tuple(types...)); };
constexpr auto any_of = [](auto ... types) { return operator_t<decltype(or_elements), decltype(tuple(types...))>(or_elements, tuple(types...)); };

#endif
