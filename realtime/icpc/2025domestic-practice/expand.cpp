#include <bits/stdc++.h>
inline constexpr bool DEV_ENV = false;
inline constexpr bool NO_EXCEPT = true;
namespace uni {
namespace internal {
using size_t = std::int64_t;
using int128_t = __int128_t;
using uint128_t = __uint128_t;
}
}
namespace uni {
namespace internal {
template<class R, class T>
concept convertibel_range = std::convertible_to<std::ranges::range_value_t<R>, T>;
template<class T, class V>
concept item_or_convertible_range = std::convertible_to<T, V> || convertibel_range<T, V>;
template<class Structure>
concept available =
requires () {
typename Structure;
};
template<
template<class...> class Structure,
class... TemplateParameters
>
concept available_with = available<Structure<TemplateParameters...>>;
template<class T> concept arithmetic = std::is_arithmetic_v<T>;
template<class T> concept floating_point = std::is_floating_point_v<T>;
template<class T> concept pointer = std::is_pointer_v<T>;
template<class T> concept structural = std::is_class_v<T>;
template<class Large, class Small>
concept has_double_digits_of = (std::numeric_limits<Large>::digits == 2 * std::numeric_limits<Small>::digits);
template<class Large, class Small>
concept has_more_digits_than = (std::numeric_limits<Large>::digits > std::numeric_limits<Small>::digits);
template<class Large, class Small>
concept has_or_more_digits_than = (std::numeric_limits<Large>::digits >= std::numeric_limits<Small>::digits);
template<class T>
concept has_static_zero = requires { T::zero; };
template<class T>
concept has_static_one = requires { T::one; };
template<class L, class R = L>
concept weakly_bitand_calcurable = requires (L lhs, R rhs) { lhs & rhs; };
template<class L, class R = L>
concept weakly_bitor_calcurable = requires (L lhs, R rhs) { lhs | rhs; };
template<class L, class R = L>
concept weakly_bitxor_calcurable = requires (L lhs, R rhs) { lhs ^ rhs; };
template<class L, class R = L>
concept weakly_addable = requires (L lhs, R rhs) { lhs + rhs; };
template<class L, class R = L>
concept weakly_subtractable = requires (L lhs, R rhs) { lhs - rhs; };
template<class L, class R = L>
concept weakly_multipliable = requires (L lhs, R rhs) { lhs * rhs; };
template<class L, class R = L>
concept weakly_divisable = requires (L lhs, R rhs) { lhs / rhs; };
template<class L, class R = L>
concept weakly_remainder_calculable = requires (L lhs, R rhs) { lhs % rhs; };
template<class L, class R = L>
concept weakly_bitand_assignable = requires (L lhs, R rhs) { lhs += rhs; };
template<class L, class R = L>
concept weakly_bitor_assignable = requires (L lhs, R rhs) { lhs |= rhs; };
template<class L, class R = L>
concept weakly_bitxor_assignable = requires (L lhs, R rhs) { lhs ^= rhs; };
template<class L, class R = L>
concept weakly_addition_assignable = requires (L lhs, R rhs) { lhs += rhs; };
template<class L, class R = L>
concept weakly_subtraction_assignable = requires (L lhs, R rhs) { lhs -= rhs; };
template<class L, class R = L>
concept weakly_multipliation_assignalbe = requires (L lhs, R rhs) { lhs *= rhs; };
template<class L, class R = L>
concept weakly_division_assignable = requires (L lhs, R rhs) { lhs /= rhs; };
template<class L, class R = L>
concept weakly_remainder_assignable = requires (L lhs, R rhs) { lhs /= rhs; };
template<class L, class R = L>
concept bitand_calculable =
weakly_bitand_calcurable<L, R> &&
weakly_bitand_calcurable<std::invoke_result_t<std::bit_and<>&, L, R>, R> &&
weakly_bitand_calcurable<L, std::invoke_result_t<std::bit_and<>&, L, R>> &&
weakly_bitand_calcurable<std::invoke_result_t<std::bit_and<>&, L, R>, std::invoke_result_t<std::bit_and<>&, L, R>>;
template<class L, class R = L>
concept bitor_calculable =
weakly_bitor_calcurable<L, R> &&
weakly_bitor_calcurable<std::invoke_result_t<std::bit_or<>&, L, R>, R> &&
weakly_bitor_calcurable<L, std::invoke_result_t<std::bit_or<>&, L, R>> &&
weakly_bitor_calcurable<std::invoke_result_t<std::bit_or<>&, L, R>, std::invoke_result_t<std::bit_or<>&, L, R>>;
template<class L, class R = L>
concept bitxor_calculable =
weakly_bitxor_calcurable<L, R> &&
weakly_bitxor_calcurable<std::invoke_result_t<std::bit_xor<>&, L, R>, R> &&
weakly_bitxor_calcurable<L, std::invoke_result_t<std::bit_xor<>&, L, R>> &&
weakly_bitxor_calcurable<std::invoke_result_t<std::bit_xor<>&, L, R>, std::invoke_result_t<std::bit_xor<>&, L, R>>;
template<class L, class R = L>
concept addable =
weakly_addable<L, R> &&
weakly_addable<std::invoke_result_t<std::plus<>&, L, R>, R> &&
weakly_addable<L, std::invoke_result_t<std::plus<>&, L, R>> &&
weakly_addable<std::invoke_result_t<std::plus<>&, L, R>, std::invoke_result_t<std::plus<>&, L, R>>;
template<class L, class R = L>
concept subtractable =
weakly_subtractable<L, R> &&
weakly_subtractable<std::invoke_result_t<std::minus<>&, L, R>, R> &&
weakly_subtractable<L, std::invoke_result_t<std::minus<>&, L, R>> &&
weakly_subtractable<std::invoke_result_t<std::minus<>&, L, R>, std::invoke_result_t<std::minus<>&, L, R>>;
template<class L, class R = L>
concept multipliable =
weakly_multipliable<L, R> &&
weakly_multipliable<std::invoke_result_t<std::multiplies<>&, L, R>, R> &&
weakly_multipliable<L, std::invoke_result_t<std::multiplies<>&, L, R>> &&
weakly_multipliable<std::invoke_result_t<std::multiplies<>&, L, R>, std::invoke_result_t<std::multiplies<>&, L, R>>;
template<class L, class R = L>
concept divisable =
weakly_divisable<L, R> &&
weakly_divisable<std::invoke_result_t<std::divides<>&, L, R>, R> &&
weakly_divisable<L, std::invoke_result_t<std::divides<>&, L, R>> &&
weakly_divisable<std::invoke_result_t<std::divides<>&, L, R>, std::invoke_result_t<std::divides<>&, L, R>>;
template<class L, class R = L>
concept remainder_calculable =
weakly_remainder_calculable<L, R> &&
weakly_remainder_calculable<std::invoke_result_t<std::modulus<>&, L, R>, R> &&
weakly_remainder_calculable<L, std::invoke_result_t<std::modulus<>&, L, R>> &&
weakly_remainder_calculable<std::invoke_result_t<std::modulus<>&, L, R>, std::invoke_result_t<std::modulus<>&, L, R>>;
template<class L, class R = L>
concept bitand_assignable =
weakly_bitand_assignable<L, R> &&
weakly_bitand_assignable<std::invoke_result_t<std::bit_and<>&, L, R>, R> &&
weakly_bitand_assignable<L, std::invoke_result_t<std::bit_and<>&, L, R>> &&
weakly_bitand_assignable<std::invoke_result_t<std::bit_and<>&, L, R>, std::invoke_result_t<std::bit_and<>&, L, R>>;
template<class L, class R = L>
concept bitor_assignable =
weakly_bitor_calcurable<L, R> &&
weakly_bitor_calcurable<std::invoke_result_t<std::bit_or<>&, L, R>, R> &&
weakly_bitor_calcurable<L, std::invoke_result_t<std::bit_or<>&, L, R>> &&
weakly_bitor_calcurable<std::invoke_result_t<std::bit_or<>&, L, R>, std::invoke_result_t<std::bit_or<>&, L, R>>;
template<class L, class R = L>
concept bitxor_assignable =
weakly_bitxor_calcurable<L, R> &&
weakly_bitxor_calcurable<std::invoke_result_t<std::bit_xor<>&, L, R>, R> &&
weakly_bitxor_calcurable<L, std::invoke_result_t<std::bit_xor<>&, L, R>> &&
weakly_bitxor_calcurable<std::invoke_result_t<std::bit_xor<>&, L, R>, std::invoke_result_t<std::bit_xor<>&, L, R>>;
template<class L, class R = L>
concept addition_assignable =
weakly_addition_assignable<L, R> &&
weakly_addition_assignable<std::remove_cvref_t<std::invoke_result_t<std::plus<>&, L, R>>, R> &&
weakly_addition_assignable<L, std::invoke_result_t<std::plus<>&, L, R>> &&
weakly_addition_assignable<std::remove_cvref_t<std::invoke_result_t<std::plus<>&, L, R>>, std::invoke_result_t<std::plus<>&, L, R>>;
template<class L, class R = L>
concept subtraction_assignable =
weakly_subtraction_assignable<L, R> &&
weakly_subtraction_assignable<std::remove_cvref_t<std::invoke_result_t<std::minus<>&, L, R>>, R> &&
weakly_subtraction_assignable<L, std::invoke_result_t<std::minus<>&, L, R>> &&
weakly_subtraction_assignable<std::remove_cvref_t<std::invoke_result_t<std::minus<>&, L, R>>, std::invoke_result_t<std::minus<>&, L, R>>;
template<class L, class R = L>
concept multipliation_assignalbe =
weakly_multipliation_assignalbe<L, R> &&
weakly_multipliation_assignalbe<std::remove_cvref_t<std::invoke_result_t<std::multiplies<>&, L, R>>, R> &&
weakly_multipliation_assignalbe<L, std::invoke_result_t<std::multiplies<>&, L, R>> &&
weakly_multipliation_assignalbe<std::remove_cvref_t<std::invoke_result_t<std::multiplies<>&, L, R>>, std::invoke_result_t<std::multiplies<>&, L, R>>;
template<class L, class R = L>
concept division_assignable =
weakly_division_assignable<L, R> &&
weakly_division_assignable<std::remove_cvref_t<std::invoke_result_t<std::divides<>&, L, R>>, R> &&
weakly_division_assignable<L, std::invoke_result_t<std::divides<>&, L, R>> &&
weakly_division_assignable<std::remove_cvref_t<std::invoke_result_t<std::divides<>&, L, R>>, std::invoke_result_t<std::divides<>&, L, R>>;
template<class L, class R = L>
concept remainder_assignable =
weakly_remainder_assignable<L, R> &&
weakly_remainder_assignable<std::remove_cvref_t<std::invoke_result_t<std::modulus<>&, L, R>>, R> &&
weakly_remainder_assignable<L, std::invoke_result_t<std::modulus<>&, L, R>> &&
weakly_remainder_assignable<std::remove_cvref_t<std::invoke_result_t<std::modulus<>&, L, R>>, std::invoke_result_t<std::modulus<>&, L, R>>;
template<class T>
concept weakly_incrementable =
std::movable<T> &&
requires (T v) {
{ ++v } -> std::same_as<T&>;
v++;
};
template<class T>
concept weakly_decrementable =
std::movable<T> &&
requires (T v) {
{ --v } -> std::same_as<T&>;
v--;
};
template<class T>
concept incrementable =
std::regular<T> &&
weakly_incrementable<T> &&
requires (T v) {
{ v++ } -> std::same_as<T>;
};
template<class T>
concept decrementable =
std::regular<T> &&
weakly_decrementable<T> &&
requires (T v) {
{ v-- } -> std::same_as<T>;
};
template<class L, class R = L>
concept weakly_arithmetic_operable =
weakly_addable<L, R> &&
weakly_subtractable<L, R> &&
weakly_multipliable<L, R> &&
weakly_divisable<L, R>;
template<class L, class R = L>
concept weakly_arithmetic_operation_assignable =
weakly_addition_assignable<L, R> &&
weakly_subtraction_assignable<L, R> &&
weakly_multipliation_assignalbe<L, R> &&
weakly_division_assignable<L, R>;
template<class L, class R = L>
concept arithmetic_operable =
weakly_arithmetic_operable<L, R> &&
addable<L, R> &&
subtractable<L, R> &&
multipliable<L, R> &&
divisable<L, R>;
template<class L, class R = L>
concept arithmetic_operation_assignable =
weakly_arithmetic_operation_assignable<L, R> &&
addition_assignable<L, R> &&
subtraction_assignable<L, R> &&
multipliation_assignalbe<L, R> &&
division_assignable<L, R>;
template<class T>
concept unary_addable =
requires (T v) {
{ +v } -> std::same_as<T>;
};
template<class T>
concept unary_subtractable =
requires (T v) {
{ -v } -> std::same_as<T>;
};
template<class T>
concept numeric =
std::regular<T> &&
arithmetic_operable<T> &&
arithmetic_operation_assignable<T> &&
weakly_incrementable<T> &&
unary_addable<T> &&
unary_subtractable<T>;
}
}
namespace uni {
template<class T, class R>
requires
internal::remainder_calculable<T, R> &&
internal::subtractable<T, R> &&
internal::unary_subtractable<T>
inline T mod(T x, const R& r) noexcept(NO_EXCEPT) {
if(x >= 0) return x % r;
x = -x % r;
if(x != 0) x = r - x;
return x;
}
}
namespace uni {
namespace internal {
template<class... T> inline constexpr bool EXCEPTION_ON_TYPE = false;
template<auto T> inline constexpr bool EXCEPTION_ON_VALUE = false;
}
}
namespace uni {
template<std::input_iterator I, std::sentinel_for<I> S>
std::string join(I first, S last, const char* sep = "") noexcept(NO_EXCEPT) {
if(first == last) return "";
std::ostringstream res;
while(true) {
res << *first;
std::ranges::advance(first, 1);
if(first == last) break;
res << sep;
}
return res.str();
}
template<std::ranges::input_range R>
std::string join(R&& range, const char* sep = "") noexcept(NO_EXCEPT) {
return join(std::ranges::begin((range)),std::ranges::end((range)), sep);
}
template<class I, class T = std::iter_value_t<I>>
requires std::sentinel_for<I, I>
T sum(I first, I last, const T& base = T()) noexcept(NO_EXCEPT) {
return std::accumulate(first, last, base);
}
template<std::ranges::input_range R, class T = std::ranges::range_value_t<R>>
auto sum(R&& range, T base = T()) noexcept(NO_EXCEPT) {
auto&& r = range | std::views::common;
return sum(std::ranges::begin((r)),std::ranges::end((r)), base);
}
}
namespace uni {
namespace internal {
template<class Base>
struct advanced_container : Base {
private:
inline Base* _base() noexcept(NO_EXCEPT) {
return static_cast<Base*>(this);
}
inline const Base* _base() const noexcept(NO_EXCEPT) {
return static_cast<const Base*>(this);
}
public:
using Base::Base;
advanced_container(const Base& base) : Base(base) {}
using size_type = decltype(std::ranges::size(std::declval<Base>()));
using value_type = Base::value_type;
inline auto ssize() const noexcept(NO_EXCEPT) { return std::ranges::ssize(*this->_base()); }
inline const auto& operator[](internal::size_t p) const noexcept(NO_EXCEPT) {
p = p < 0 ? p + this->size() : p;
assert(0 <= p && p < this->ssize());
return this->Base::operator[](p);
}
inline auto& operator[](internal::size_t p) noexcept(NO_EXCEPT) {
p = p < 0 ? p + this->size() : p;
assert(0 <= p && p < this->ssize());
return this->Base::operator[](p);
}
inline auto& fill(const value_type& v) noexcept(NO_EXCEPT) {
std::ranges::fill(*this, v);
return *this;
}
inline auto& swap(const size_type i, const size_type j) noexcept(NO_EXCEPT) {
std::swap(this->operator[](i), this->operator[](j));
return *this;
}
inline auto& sort() noexcept(NO_EXCEPT) {
std::ranges::sort(*this);
return *this;
}
template<class F>
inline auto& sort(F&& f) noexcept(NO_EXCEPT) {
std::ranges::sort(*this, std::forward<F>(f));
return *this;
}
inline auto& stable_sort() noexcept(NO_EXCEPT) {
std::ranges::stable_sort(*this);
return *this;
}
template<class F>
inline auto& stable_sort(F&& f) noexcept(NO_EXCEPT) {
std::ranges::stable_sort(*this, std::forward<F>(f));
return *this;
}
inline auto& reverse() noexcept(NO_EXCEPT) {
std::ranges::reverse(*this);
return *this;
}
inline auto count(const value_type& v) const noexcept(NO_EXCEPT) {
return std::ranges::count(*this, v);
}
inline auto contains(const value_type& v) const noexcept(NO_EXCEPT) {
return this->count(v) > 0;
}
template<class F>
inline auto count_if(F&& f) const noexcept(NO_EXCEPT) {
return std::ranges::count_if(*this, std::forward<F>(f));
}
inline auto& resize(const size_type k) noexcept(NO_EXCEPT) {
this->Base::resize(k);
return *this;
}
inline auto& resize(const size_type k, const value_type& v) noexcept(NO_EXCEPT) {
this->Base::resize(k, v);
return *this;
}
template<class F>
inline auto& shuffle(F&& f) noexcept(NO_EXCEPT) {
std::ranges::shuffle(*this, std::forward<F>(f));
return *this;
}
inline auto& unique() noexcept(NO_EXCEPT) {
const auto rest = std::ranges::unique(*this);
this->erase(std::ranges::begin((rest)),std::ranges::end((rest)));
return *this;
}
template<class T>
inline auto binary_search(T&& v) const noexcept(NO_EXCEPT) {
return std::ranges::binary_search(*this, std::forward<T>(v));
}
template<class T>
inline auto lower_bound(T&& v) const noexcept(NO_EXCEPT) {
return std::ranges::lower_bound(*this, std::forward<T>(v));
}
template<class T>
inline auto upper_bound(T&& v) const noexcept(NO_EXCEPT) {
return std::ranges::upper_bound(*this, std::forward<T>(v));
}
template<class T>
inline auto find(T&& v) const noexcept(NO_EXCEPT) {
return std::ranges::find(*this, std::forward<T>(v));
}
template<class T>
inline auto index(T&& v) const noexcept(NO_EXCEPT) {
return this->find(std::forward<T>(v)) - this->begin();
}
inline auto join(const char* sep = "") const noexcept(NO_EXCEPT) {
return uni::join(*this, sep);
}
inline auto sum() const noexcept(NO_EXCEPT) { return uni::sum(*this); }
inline auto max() const noexcept(NO_EXCEPT) { return std::ranges::max(*this->_base()); }
inline auto min() const noexcept(NO_EXCEPT) { return std::ranges::min(*this); }
inline auto begin() noexcept(NO_EXCEPT) { return std::ranges::begin(*this->_base()); }
inline auto begin() const noexcept(NO_EXCEPT) { return std::ranges::begin(*this->_base()); }
inline auto end() noexcept(NO_EXCEPT) { return std::ranges::end(*this->_base()); }
inline auto end() const noexcept(NO_EXCEPT) { return std::ranges::end(*this->_base()); }
auto& operator +=(const value_type& v) noexcept(NO_EXCEPT) requires internal::weakly_addition_assignable<value_type> { if constexpr(internal::weakly_addition_assignable<Base, value_type>) { this->Base::operator +=(v); } else { for(std::common_type_t<std::remove_cvref_t<decltype(std::ranges::begin((*this)))>,std::remove_cvref_t<decltype(std::ranges::end((*this)))>> itr=(std::ranges::begin((*this))), itr$=(std::ranges::end((*this))); itr<itr$; ++itr) *itr += v; } return *this; } auto& operator +=(const advanced_container& rhs) noexcept(NO_EXCEPT) requires internal::weakly_addition_assignable<value_type> { if constexpr(internal::weakly_addition_assignable<Base>) { this->Base::operator +=(*rhs._base()); } else { auto itr = std::ranges::begin(*this), rhs_itr = std::ranges::begin(rhs); auto end = std::ranges::end(*this); for(; itr != end; ++itr, ++rhs_itr) { *itr += *rhs_itr; } } return *this; } template<class T = value_type> requires internal::weakly_addition_assignable<value_type> && (std::convertible_to<T, value_type> || std::same_as<T, advanced_container>) friend auto operator +(advanced_container lhs, const T& rhs) noexcept(NO_EXCEPT) { return lhs += rhs; } template<class T = value_type> requires internal::weakly_addition_assignable<value_type> && std::convertible_to<T, value_type> friend auto operator +(const T& lhs, advanced_container rhs) noexcept(NO_EXCEPT) { return advanced_container(rhs.size(), lhs) += rhs; }
auto& operator -=(const value_type& v) noexcept(NO_EXCEPT) requires internal::weakly_subtraction_assignable<value_type> { if constexpr(internal::weakly_subtraction_assignable<Base, value_type>) { this->Base::operator -=(v); } else { for(std::common_type_t<std::remove_cvref_t<decltype(std::ranges::begin((*this)))>,std::remove_cvref_t<decltype(std::ranges::end((*this)))>> itr=(std::ranges::begin((*this))), itr$=(std::ranges::end((*this))); itr<itr$; ++itr) *itr -= v; } return *this; } auto& operator -=(const advanced_container& rhs) noexcept(NO_EXCEPT) requires internal::weakly_subtraction_assignable<value_type> { if constexpr(internal::weakly_subtraction_assignable<Base>) { this->Base::operator -=(*rhs._base()); } else { auto itr = std::ranges::begin(*this), rhs_itr = std::ranges::begin(rhs); auto end = std::ranges::end(*this); for(; itr != end; ++itr, ++rhs_itr) { *itr -= *rhs_itr; } } return *this; } template<class T = value_type> requires internal::weakly_subtraction_assignable<value_type> && (std::convertible_to<T, value_type> || std::same_as<T, advanced_container>) friend auto operator -(advanced_container lhs, const T& rhs) noexcept(NO_EXCEPT) { return lhs -= rhs; } template<class T = value_type> requires internal::weakly_subtraction_assignable<value_type> && std::convertible_to<T, value_type> friend auto operator -(const T& lhs, advanced_container rhs) noexcept(NO_EXCEPT) { return advanced_container(rhs.size(), lhs) -= rhs; }
auto& operator *=(const value_type& v) noexcept(NO_EXCEPT) requires internal::weakly_multipliation_assignalbe<value_type> { if constexpr(internal::weakly_multipliation_assignalbe<Base, value_type>) { this->Base::operator *=(v); } else { for(std::common_type_t<std::remove_cvref_t<decltype(std::ranges::begin((*this)))>,std::remove_cvref_t<decltype(std::ranges::end((*this)))>> itr=(std::ranges::begin((*this))), itr$=(std::ranges::end((*this))); itr<itr$; ++itr) *itr *= v; } return *this; } auto& operator *=(const advanced_container& rhs) noexcept(NO_EXCEPT) requires internal::weakly_multipliation_assignalbe<value_type> { if constexpr(internal::weakly_multipliation_assignalbe<Base>) { this->Base::operator *=(*rhs._base()); } else { auto itr = std::ranges::begin(*this), rhs_itr = std::ranges::begin(rhs); auto end = std::ranges::end(*this); for(; itr != end; ++itr, ++rhs_itr) { *itr *= *rhs_itr; } } return *this; } template<class T = value_type> requires internal::weakly_multipliation_assignalbe<value_type> && (std::convertible_to<T, value_type> || std::same_as<T, advanced_container>) friend auto operator *(advanced_container lhs, const T& rhs) noexcept(NO_EXCEPT) { return lhs *= rhs; } template<class T = value_type> requires internal::weakly_multipliation_assignalbe<value_type> && std::convertible_to<T, value_type> friend auto operator *(const T& lhs, advanced_container rhs) noexcept(NO_EXCEPT) { return advanced_container(rhs.size(), lhs) *= rhs; }
auto& operator /=(const value_type& v) noexcept(NO_EXCEPT) requires internal::weakly_division_assignable<value_type> { if constexpr(internal::weakly_division_assignable<Base, value_type>) { this->Base::operator /=(v); } else { for(std::common_type_t<std::remove_cvref_t<decltype(std::ranges::begin((*this)))>,std::remove_cvref_t<decltype(std::ranges::end((*this)))>> itr=(std::ranges::begin((*this))), itr$=(std::ranges::end((*this))); itr<itr$; ++itr) *itr /= v; } return *this; } auto& operator /=(const advanced_container& rhs) noexcept(NO_EXCEPT) requires internal::weakly_division_assignable<value_type> { if constexpr(internal::weakly_division_assignable<Base>) { this->Base::operator /=(*rhs._base()); } else { auto itr = std::ranges::begin(*this), rhs_itr = std::ranges::begin(rhs); auto end = std::ranges::end(*this); for(; itr != end; ++itr, ++rhs_itr) { *itr /= *rhs_itr; } } return *this; } template<class T = value_type> requires internal::weakly_division_assignable<value_type> && (std::convertible_to<T, value_type> || std::same_as<T, advanced_container>) friend auto operator /(advanced_container lhs, const T& rhs) noexcept(NO_EXCEPT) { return lhs /= rhs; } template<class T = value_type> requires internal::weakly_division_assignable<value_type> && std::convertible_to<T, value_type> friend auto operator /(const T& lhs, advanced_container rhs) noexcept(NO_EXCEPT) { return advanced_container(rhs.size(), lhs) /= rhs; }
auto& operator %=(const value_type& v) noexcept(NO_EXCEPT) requires internal::weakly_remainder_assignable<value_type> { if constexpr(internal::weakly_remainder_assignable<Base, value_type>) { this->Base::operator %=(v); } else { for(std::common_type_t<std::remove_cvref_t<decltype(std::ranges::begin((*this)))>,std::remove_cvref_t<decltype(std::ranges::end((*this)))>> itr=(std::ranges::begin((*this))), itr$=(std::ranges::end((*this))); itr<itr$; ++itr) *itr %= v; } return *this; } auto& operator %=(const advanced_container& rhs) noexcept(NO_EXCEPT) requires internal::weakly_remainder_assignable<value_type> { if constexpr(internal::weakly_remainder_assignable<Base>) { this->Base::operator %=(*rhs._base()); } else { auto itr = std::ranges::begin(*this), rhs_itr = std::ranges::begin(rhs); auto end = std::ranges::end(*this); for(; itr != end; ++itr, ++rhs_itr) { *itr %= *rhs_itr; } } return *this; } template<class T = value_type> requires internal::weakly_remainder_assignable<value_type> && (std::convertible_to<T, value_type> || std::same_as<T, advanced_container>) friend auto operator %(advanced_container lhs, const T& rhs) noexcept(NO_EXCEPT) { return lhs %= rhs; } template<class T = value_type> requires internal::weakly_remainder_assignable<value_type> && std::convertible_to<T, value_type> friend auto operator %(const T& lhs, advanced_container rhs) noexcept(NO_EXCEPT) { return advanced_container(rhs.size(), lhs) %= rhs; }
auto& operator &=(const value_type& v) noexcept(NO_EXCEPT) requires internal::weakly_bitand_assignable<value_type> { if constexpr(internal::weakly_bitand_assignable<Base, value_type>) { this->Base::operator &=(v); } else { for(std::common_type_t<std::remove_cvref_t<decltype(std::ranges::begin((*this)))>,std::remove_cvref_t<decltype(std::ranges::end((*this)))>> itr=(std::ranges::begin((*this))), itr$=(std::ranges::end((*this))); itr<itr$; ++itr) *itr &= v; } return *this; } auto& operator &=(const advanced_container& rhs) noexcept(NO_EXCEPT) requires internal::weakly_bitand_assignable<value_type> { if constexpr(internal::weakly_bitand_assignable<Base>) { this->Base::operator &=(*rhs._base()); } else { auto itr = std::ranges::begin(*this), rhs_itr = std::ranges::begin(rhs); auto end = std::ranges::end(*this); for(; itr != end; ++itr, ++rhs_itr) { *itr &= *rhs_itr; } } return *this; } template<class T = value_type> requires internal::weakly_bitand_assignable<value_type> && (std::convertible_to<T, value_type> || std::same_as<T, advanced_container>) friend auto operator &(advanced_container lhs, const T& rhs) noexcept(NO_EXCEPT) { return lhs &= rhs; } template<class T = value_type> requires internal::weakly_bitand_assignable<value_type> && std::convertible_to<T, value_type> friend auto operator &(const T& lhs, advanced_container rhs) noexcept(NO_EXCEPT) { return advanced_container(rhs.size(), lhs) &= rhs; }
auto& operator |=(const value_type& v) noexcept(NO_EXCEPT) requires internal::weakly_bitor_assignable<value_type> { if constexpr(internal::weakly_bitor_assignable<Base, value_type>) { this->Base::operator |=(v); } else { for(std::common_type_t<std::remove_cvref_t<decltype(std::ranges::begin((*this)))>,std::remove_cvref_t<decltype(std::ranges::end((*this)))>> itr=(std::ranges::begin((*this))), itr$=(std::ranges::end((*this))); itr<itr$; ++itr) *itr |= v; } return *this; } auto& operator |=(const advanced_container& rhs) noexcept(NO_EXCEPT) requires internal::weakly_bitor_assignable<value_type> { if constexpr(internal::weakly_bitor_assignable<Base>) { this->Base::operator |=(*rhs._base()); } else { auto itr = std::ranges::begin(*this), rhs_itr = std::ranges::begin(rhs); auto end = std::ranges::end(*this); for(; itr != end; ++itr, ++rhs_itr) { *itr |= *rhs_itr; } } return *this; } template<class T = value_type> requires internal::weakly_bitor_assignable<value_type> && (std::convertible_to<T, value_type> || std::same_as<T, advanced_container>) friend auto operator |(advanced_container lhs, const T& rhs) noexcept(NO_EXCEPT) { return lhs |= rhs; } template<class T = value_type> requires internal::weakly_bitor_assignable<value_type> && std::convertible_to<T, value_type> friend auto operator |(const T& lhs, advanced_container rhs) noexcept(NO_EXCEPT) { return advanced_container(rhs.size(), lhs) |= rhs; }
auto& operator ^=(const value_type& v) noexcept(NO_EXCEPT) requires internal::weakly_bitxor_assignable<value_type> { if constexpr(internal::weakly_bitxor_assignable<Base, value_type>) { this->Base::operator ^=(v); } else { for(std::common_type_t<std::remove_cvref_t<decltype(std::ranges::begin((*this)))>,std::remove_cvref_t<decltype(std::ranges::end((*this)))>> itr=(std::ranges::begin((*this))), itr$=(std::ranges::end((*this))); itr<itr$; ++itr) *itr ^= v; } return *this; } auto& operator ^=(const advanced_container& rhs) noexcept(NO_EXCEPT) requires internal::weakly_bitxor_assignable<value_type> { if constexpr(internal::weakly_bitxor_assignable<Base>) { this->Base::operator ^=(*rhs._base()); } else { auto itr = std::ranges::begin(*this), rhs_itr = std::ranges::begin(rhs); auto end = std::ranges::end(*this); for(; itr != end; ++itr, ++rhs_itr) { *itr ^= *rhs_itr; } } return *this; } template<class T = value_type> requires internal::weakly_bitxor_assignable<value_type> && (std::convertible_to<T, value_type> || std::same_as<T, advanced_container>) friend auto operator ^(advanced_container lhs, const T& rhs) noexcept(NO_EXCEPT) { return lhs ^= rhs; } template<class T = value_type> requires internal::weakly_bitxor_assignable<value_type> && std::convertible_to<T, value_type> friend auto operator ^(const T& lhs, advanced_container rhs) noexcept(NO_EXCEPT) { return advanced_container(rhs.size(), lhs) ^= rhs; }
};
}
}
namespace uni {
using string = internal::advanced_container<std::string>;
}
namespace std {
template<>
struct hash<uni::string> {
inline auto operator()(const uni::string& key) const noexcept(NO_EXCEPT) {
return std::hash<std::string>{}(static_cast<std::string>(key));
}
};
}
namespace uni {
using i16 = std::int16_t;
using u16 = std::uint16_t;
using i32 = std::int32_t;
using u32 = std::uint32_t;
using i64 = std::int64_t;
using u64 = std::uint64_t;
using i128 = __int128_t;
using u128 = __uint128_t;
using f128 = __float128;
using uint = unsigned;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
}
namespace std {
template<class C, class S>
auto& operator>>(std::basic_istream<C, S>& in, uni::i128& v) noexcept(NO_EXCEPT) {
std::string str; in >> str;
v = 0;
bool negative = (str[0] == '-');
for(std::common_type_t<std::remove_cvref_t<decltype(std::ranges::next(str.begin(), negative))>,std::remove_cvref_t<decltype(str.end())>> d=(std::ranges::next(str.begin(), negative)), d$=(str.end()); d<d$; ++d) {
assert(std::isdigit(*d));
v = v * 10 + *d - '0';
}
if(negative) v *= -1;
return in;
}
template<class C, class S>
auto& operator>>(std::basic_istream<C, S>& in, uni::u128& v) noexcept(NO_EXCEPT) {
std::string str; in >> str;
v = 0U;
assert(str[0] != '-');
for(std::common_type_t<std::remove_cvref_t<decltype(str.begin())>,std::remove_cvref_t<decltype(str.end())>> d=(str.begin()), d$=(str.end()); d<d$; ++d) {
assert(std::isdigit(*d));
v = v * 10U + *d - '0';
}
return in;
}
template<class C, class S>
auto& operator<<(std::basic_ostream<C, S>& out, uni::i128 v) noexcept(NO_EXCEPT) {
if(v == 0) return out << 0;
if(v < 0) out << '-', v *= -1;
std::string str;
while(v > 0) str += static_cast<char>(v%10) + '0', v /= 10;
std::reverse(str.begin(), str.end());
return out << str;
}
template<class C, class S>
auto& operator<<(std::basic_ostream<C, S>& out, uni::u128 v) noexcept(NO_EXCEPT) {
if(v == 0) return out << 0U;
std::string str;
while(v > 0) str += static_cast<char>(v%10U) + '0', v /= 10U;
std::reverse(str.begin(), str.end());
return out << str;
}
}
namespace uni {
namespace internal {
template<class... Ts> struct tuple_or_pair { using type = std::tuple<Ts...>; };
template<class T, class U> struct tuple_or_pair<T,U> { using type = std::pair<T, U>; };
template <class... Ts> using tuple_or_pair_t = typename tuple_or_pair<Ts...>::type;
template<class T>
constexpr std::underlying_type_t<T> to_underlying(const T& v) noexcept(NO_EXCEPT) {
return static_cast<std::underlying_type_t<T>>(v);
}
template<class T, class... Ts>
using are_same = std::conjunction<std::is_same<T, Ts>...>;
template<class T, class... Ts>
inline constexpr bool are_same_v = are_same<T, Ts...>::value;
template<class T, class... Ts>
using is_same_as_any_of = std::disjunction<std::is_same<T, Ts>...>;
template<class T, class... Ts>
inline constexpr bool is_same_as_any_of_v = is_same_as_any_of<T, Ts...>::value;
template<class T, class... Ts>
concept same_as_any_of = is_same_as_any_of_v<T, Ts...>;
template<class Base, class... Derived>
using is_base_of_all = std::conjunction<std::is_base_of<Base, Derived>...>;
template<class Base, class... Derived>
inline constexpr bool is_base_of_all_v = is_base_of_all<Base, Derived...>::value;
template<class Base, class... Derived>
using is_base_of_any = std::disjunction<std::is_base_of<Base, Derived>...>;
template<class Base, class... Derived>
inline constexpr bool is_base_of_any_v = is_base_of_any<Base, Derived...>::value;
template<class T> struct remove_cvref {
using type = typename std::remove_cv_t<std::remove_reference_t<T>>;
};
template<class T> using remove_cvref_t = typename remove_cvref<T>::type;
template<class T> struct literal_operator { static constexpr const char* value = ""; };
template<> struct literal_operator<unsigned> { static constexpr const char* value = "U"; };
template<> struct literal_operator<long> { static constexpr const char* value = "L"; };
template<> struct literal_operator<unsigned long> { static constexpr const char* value = "UL"; };
template<> struct literal_operator<long long> { static constexpr const char* value = "LL"; };
template<> struct literal_operator<unsigned long long> { static constexpr const char* value = "ULL"; };
template<> struct literal_operator<float> { static constexpr const char* value = "F"; };
template<> struct literal_operator<double> { static constexpr const char* value = "D"; };
template<> struct literal_operator<long double> { static constexpr const char* value = "LD"; };
template<> struct literal_operator<__int128_t> { static constexpr const char* value = "LLL"; };
template<> struct literal_operator<__uint128_t> { static constexpr const char* value = "ULLL"; };
template<class T> inline constexpr auto literal_operator_v = literal_operator<T>::value;
template <std::size_t N, typename... Types>
using nth_type_t = std::tuple_element_t<N, std::tuple<Types...>>;
template<template <class...> class, class> struct is_template_of : std::false_type {};
template<template <class...> class Template, class... Args> struct is_template_of<Template, Template<Args...>> : std::true_type {};
template<template <class...> class Template, class Type>
inline constexpr bool is_template_of_v = is_template_of<Template, Type>::value;
template<class Type, template <class...> class Template>
concept substituted_from = is_template_of_v<Template, Type>;
template<template <class...> class Base, class Derived>
struct _is_basic_tempalte_of
{
template<class... Ts>
static constexpr std::true_type test(const Base<Ts...> *);
static constexpr std::false_type test(...);
using type = decltype(test(std::declval<Derived*>()));
};
template<template <class...> class Base, class Derived>
using is_basic_tempalte_of = _is_basic_tempalte_of<Base, Derived>::type;
template<template <class...> class Base, class Derived>
inline constexpr bool is_basic_tempalte_of_v = is_basic_tempalte_of<Base, Derived>::value;
template<class Derived, template <class...> class Base>
concept derived_from_template = is_basic_tempalte_of_v<Base, Derived>;
template<class T> struct is_loggable {
template<class U>
static constexpr auto External(U &&v) -> decltype(_debug(v), std::true_type());
static constexpr std::false_type External(...);
template<class U>
static constexpr auto Member(U &&v) -> decltype(v._debug(), std::true_type());
static constexpr std::false_type Member(...);
static constexpr bool value = (
decltype(External(std::declval<T>()))::value ||
decltype(Member(std::declval<T>()))::value
);
};
template<class T>
inline constexpr auto is_loggable_v = is_loggable<T>::value;
template<class T>
concept loggable = is_loggable_v<T>;
template<class T> struct _has_iterator {
template<class U>
static constexpr auto ADL(U &&v) -> decltype(begin(v), end(v), std::true_type());
static constexpr std::false_type ADL(...);
template<class U>
static constexpr auto STL(U &&v) -> decltype(std::begin(v), std::end(v), std::true_type());
static constexpr std::false_type STL(...);
template<class U>
static constexpr auto Member(U &&v) -> decltype(v.begin(), v.end(), std::true_type());
static constexpr std::false_type Member(...);
};
template<class T> struct has_iterator {
struct ADL : decltype(_has_iterator<T>::ADL(std::declval<T>())) {};
struct STL : decltype(_has_iterator<T>::STL(std::declval<T>())) {};
struct Member : decltype(_has_iterator<T>::Member(std::declval<T>())) {};
static constexpr auto adl_v = ADL::value;
static constexpr auto stl_v = STL::value;
static constexpr auto member_v = Member::value;
};
template<class T>
struct is_iterable {
static constexpr bool value = has_iterator<T>::adl_v || has_iterator<T>::stl_v || has_iterator<T>::member_v;
};
template<class T>
inline constexpr auto is_iterable_v = is_iterable<T>::value;
template<class T>
concept iterable = is_iterable_v<T>;
namespace iterator_resolver {
template<class T>
inline constexpr auto begin(T&& v) noexcept(NO_EXCEPT) {
static_assert(is_iterable_v<T>);
if constexpr(has_iterator<T>::member_v) {
return v.begin();
}
else {
using std::begin;
return begin(std::forward<T>(v));
}
}
template<class T>
inline constexpr auto end(T&& v) noexcept(NO_EXCEPT) {
static_assert(is_iterable_v<T>);
if constexpr(has_iterator<T>::member_v) {
return v.end();
}
else {
using std::end;
return end(std::forward<T>(v));
}
}
};
template<class C> using iterator_t = decltype(iterator_resolver::begin(std::declval<C&>()));
template<class C> using container_size_t = decltype(std::size(std::declval<C&>()));
template<bool Const, class T>
using maybe_const_t = std::conditional_t<Const, const T, T>;
template<class T> using with_ref = T&;
template<class T> concept can_reference = requires { typename with_ref<T>; };
}
}
namespace uni {
namespace internal {
template<int P> struct resolving_rank : resolving_rank<P-1> {};
template<> struct resolving_rank<0> {};
}
}
namespace debugger {
template<class T>
auto _debug (T&& val) -> decltype(val._debug()) {
return val._debug();
}
std::ostream *cdebug = &std::clog;
constexpr std::string COLOR_LINE = "";
constexpr std::string COLOR_IDENTIFIER = "";
constexpr std::string COLOR_INIT = "";
constexpr std::string COLOR_STRING = "";
constexpr std::string COLOR_TYPE = "";
constexpr std::string COLOR_NUMERIC = "";
constexpr std::string COLOR_LITERAL_OPERATOR = "";
using Brackets = std::pair<std::string, std::string>;
template<class T>
std::string dump(T&&);
template<class T>
const std::string get_type_name(T&& val) {
const char* const name = typeid(std::forward<T>(val)).name();
int status = -4;
char* const demangled_name = abi::__cxa_demangle(name, NULL, NULL, &status);
std::string res{name};
if (status == 0) {
res = std::string(demangled_name);
free(demangled_name);
}
return COLOR_TYPE + res + COLOR_INIT;
}
struct debug_t : std::string {
using std::string::string;
debug_t(const std::string& str) {
this->assign(str);
}
};
template<size_t N, class T>
void dump_tuple_impl([[maybe_unused]] T&& val, std::stringstream &res) {
if constexpr(N < std::tuple_size_v<std::remove_cvref_t<T>>) {
res << dump(std::get<N>(val));
if constexpr(N < std::tuple_size_v<std::remove_cvref_t<T>> - 1) res << ", ";
dump_tuple_impl<N + 1>(std::forward<T>(val), res);
}
}
template<std::ranges::input_range R>
std::string dump_range_impl(R&& range, const Brackets& brcs = { "[", "]" }, const std::string& spl = ", ") {
std::stringstream res;
res << brcs.first << " ";
auto itr = std::ranges::begin(range);
auto end = std::ranges::end(std::forward<R>(range));
while(itr != end) {
if(std::ranges::next(itr) == end) res << dump(*itr) << " ";
else res << dump(*itr) << spl;
++itr;
}
res << brcs.second ;
return res.str();
}
std::string dump_debug_t(debug_t info) {
return info;
}
struct dump_primitive_like {
std::string operator()(std::nullptr_t) const {
return COLOR_INIT;
}
template<uni::internal::pointer T>
std::string operator()(const T ptr) const {
return dump(*ptr);
}
template<class T>
requires uni::internal::derived_from_template<std::remove_cvref_t<T>, std::basic_string>
std::string operator()(T&& val) const {
std::stringstream res;
res << COLOR_STRING << "`" << val << "`" << COLOR_INIT;
return res.str();
}
std::string operator()(const char val) const {
std::stringstream res;
res << COLOR_STRING << "\'" << val << "\'" << COLOR_INIT;
return res.str();
}
std::string operator()(const char val[]) const {
std::stringstream res;
res << COLOR_STRING << "\"" << val << "\"" << COLOR_INIT;
return res.str();
}
std::string operator()(const unsigned char val) const {
std::stringstream res;
res << COLOR_NUMERIC << static_cast<int>(val) << COLOR_INIT;
return res.str();
}
std::string operator()(const bool val) const {
std::stringstream res;
res << COLOR_NUMERIC << (val ? "true" : "false" ) << COLOR_INIT;
return res.str();
}
template<uni::internal::arithmetic T>
std::string operator()(const T val) const {
std::stringstream res;
res << std::setprecision(std::numeric_limits<T>::digits10) << val;
auto str = res.str();
std::string dst = "";
if constexpr(std::integral<T>) {
while(str.length() > 3) {
dst = ',' + str.substr(str.length() - 3, 3) + dst;
str = str.substr(0, str.length() - 3);
}
}
return COLOR_NUMERIC + str + dst + COLOR_LITERAL_OPERATOR + uni::internal::literal_operator_v<T> + COLOR_INIT;
};
template<class T>
requires uni::internal::derived_from_template<std::remove_cvref_t<T>, std::optional>
std::string operator()(T&& val) const {
if(val.has_value()) return dump(*val);
return COLOR_TYPE + "invalid" + COLOR_INIT;
}
};
struct dump_bitset {
template<std::size_t N>
std::string operator()(const std::bitset<N>& val) const {
std::stringstream res;
res << COLOR_NUMERIC << val.to_string() << COLOR_INIT;
return res.str();
}
};
struct dump_has_val {
template<class T>
requires requires (T val) { val.val(); }
std::string operator()(T&& val) const {
return dump(val.val());
}
};
struct dump_iterator {
template<std::input_or_output_iterator I>
std::string operator()(I&& itr) const {
return COLOR_TYPE + "<iterator> " + COLOR_INIT+ dump(*itr);
}
};
struct dump_wrapper {
template<class T>
requires uni::internal::derived_from_template<std::remove_cvref_t<T>, std::map>
std::string operator()(T&& val) const {
return dump_range_impl(val, Brackets("{", "}"));
}
template<class T>
requires uni::internal::derived_from_template<std::remove_cvref_t<T>, std::multimap>
std::string operator()(T&& val) const {
return dump_range_impl(val, Brackets("{", "}"));
}
template<class T>
requires uni::internal::derived_from_template<std::remove_cvref_t<T>, std::unordered_map>
std::string operator()(T&& val) const {
return dump_range_impl(val, Brackets("{", "}"));
}
template<class T>
requires uni::internal::derived_from_template<std::remove_cvref_t<T>, std::unordered_multimap>
std::string operator()(T&& val) const {
return dump_range_impl(val, Brackets("{", "}"));
}
template<class T>
requires uni::internal::derived_from_template<std::remove_cvref_t<T>, std::set>
std::string operator()(T&& val) const {
return dump_range_impl(val, Brackets("{", "}"));
}
template<class T>
requires uni::internal::derived_from_template<std::remove_cvref_t<T>, std::multiset>
std::string operator()(T&& val) const {
return dump_range_impl(val, Brackets("{", "}"));
}
template<class T>
requires uni::internal::derived_from_template<std::remove_cvref_t<T>, std::unordered_set>
std::string operator()(T&& val) const {
return dump_range_impl(val, Brackets("{", "}"));
}
template<class T>
requires uni::internal::derived_from_template<std::remove_cvref_t<T>, std::unordered_multiset>
std::string operator()(T&& val) const {
return dump_range_impl(val, Brackets("{", "}"));
}
template<class T>
requires uni::internal::derived_from_template<std::remove_cvref_t<T>, std::valarray>
std::string operator()(T&& val) const {
return dump_range_impl(val, Brackets("[", "]"));
}
template<class T>
requires uni::internal::derived_from_template<std::remove_cvref_t<T>, std::vector>
std::string operator()(T&& val) const {
return dump_range_impl(val, Brackets("[", "]"));
}
template<class T>
requires uni::internal::derived_from_template<std::remove_cvref_t<T>, std::deque>
std::string operator()(T&& val) const {
return dump_range_impl(val, Brackets("[", "]"));
}
template<uni::internal::derived_from_template<std::queue> T>
std::string operator()(T val) const {
std::vector<typename T::value_type> vec;
while(!val.empty()) vec.emplace_back(val.front()), val.pop();
return dump_range_impl(vec, Brackets("<", ">"));
}
template<uni::internal::derived_from_template<std::stack> T>
std::string operator()(T val) const {
std::vector<typename T::value_type> vec;
while(!val.empty()) vec.emplace_back(val.top()), val.pop();
std::ranges::reverse(vec);
return dump_range_impl(vec, Brackets("<", ">"));
}
template<uni::internal::derived_from_template<std::priority_queue> T>
std::string operator()(T val) const {
std::vector<typename T::value_type> vec;
while(!val.empty()) vec.emplace_back(val.top()), val.pop();
return dump_range_impl(vec, Brackets("<", ">"));
}
template<class T>
requires uni::internal::derived_from_template<std::remove_cvref_t<T>, std::pair>
std::string operator()(T&& val) const {
std::stringstream res;
res << "( " << dump(val.first) << ", " << dump(val.second) << " )";
return res.str();
}
template<class T>
requires uni::internal::derived_from_template<std::remove_cvref_t<T>, std::tuple>
std::string operator()(T&& val) const {
std::stringstream res;
res << "( ";
dump_tuple_impl<0>(val, res);
res << " )";
return res.str();
}
};
struct dump_range {
template<std::ranges::input_range T>
std::string operator()(T&& val) const {
return dump_range_impl(val);
}
};
struct dump_loggable {
template<uni::internal::loggable T>
std::string operator()(T&& val) const {
auto res = _debug(val);
if constexpr(std::same_as<decltype(res), debug_t>) {
return res;
}
else {
return dump(res);
}
}
};
template<class T>
std::string dump(T&& val) {
if constexpr(std::same_as<std::remove_cvref_t<T>, debug_t>) {
return dump_debug_t(std::forward<T>(val));
}
if constexpr(std::invocable<dump_primitive_like, T>) {
return dump_primitive_like{}(std::forward<T>(val));
}
if constexpr(std::invocable<dump_loggable, T>) {
return dump_loggable{}(std::forward<T>(val));
}
if constexpr(std::invocable<dump_has_val, T>) {
return dump_has_val{}(std::forward<T>(val));
}
if constexpr(std::invocable<dump_bitset, T>) {
return dump_bitset{}(std::forward<T>(val));
}
if constexpr(std::invocable<dump_iterator, T>) {
return dump_iterator{}(std::forward<T>(val));
}
if constexpr(std::invocable<dump_wrapper, T>) {
return dump_wrapper{}(std::forward<T>(val));
}
if constexpr(std::invocable<dump_range, T>) {;
return dump_range{}(std::forward<T>(val));
}
return "== dump error ==";
}
template<class T> void debug(T&& val, const std::string& endl) {
*cdebug << dump(val) << endl << std::flush;
}
constexpr std::string_view WHITESPACES = " \n\r\t\f\v";
std::string ltrim(const std::string &s)
{
size_t start = s.find_first_not_of(WHITESPACES);
return (start == std::string::npos) ? "" : s.substr(start);
}
std::string rtrim(const std::string &s)
{
size_t end = s.find_last_not_of(WHITESPACES);
return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
std::string trim(const std::string &s) {
return rtrim(ltrim(s));
}
std::vector<std::string> split(const std::string& str) {
static constexpr char SEPARATOR = ',';
static constexpr char ESCAPE = '\\';
static constexpr std::string_view QUOTATIONS = "\"\'";
static constexpr std::string_view PARENTHESES = "()[]{}<>";
static constexpr auto PARENTHESES_KINDS = std::ranges::size(PARENTHESES);
static_assert(PARENTHESES_KINDS % 2 == 0);
std::vector<std::string> res = { "" };
bool quoted = false;
std::array<int,(PARENTHESES_KINDS / 2)> enclosed = { 0 };
for(auto itr = std::ranges::begin(str); itr != std::ranges::end(str); ++itr) {
if(std::ranges::find(QUOTATIONS, *itr) != std::ranges::end(QUOTATIONS)) {
if(itr == std::ranges::begin(str) or *std::ranges::prev(itr) != ESCAPE) {
quoted ^= true;
}
}
if(const auto found = std::ranges::find(PARENTHESES, *itr); found != std::ranges::end(PARENTHESES)) {
if(not quoted) {
auto& target = enclosed[std::ranges::distance(std::begin(PARENTHESES), found) / 2];
target = std::max(0, target - static_cast<int>((std::ranges::distance(std::begin(PARENTHESES), found) % 2) * 2) + 1);
}
}
if(
not quoted
and static_cast<std::size_t>(std::ranges::count(enclosed, 0)) == std::ranges::size(enclosed)
and *itr == SEPARATOR
) {
res.push_back("");
}
else {
res.back() += *itr;
}
}
for(auto&& v : res) v = trim(v);
return res;
}
template<class Arg> void raw(std::nullptr_t, Arg&& arg) { *cdebug << std::forward<Arg>(arg) << std::flush; }
template<class Arg> void raw(Arg&& arg) { *cdebug << dump(std::forward<Arg>(arg)) << std::flush; }
void debug(const std::vector<std::string>, const size_t, const int, const std::string) { debug(nullptr, COLOR_INIT + "\n"); }
std::map<std::pair<std::string, int>, int> count;
template<class Head, class... Tail>
void debug(
const std::vector<std::string> args, const size_t idx,
const int line, const std::string path,
Head&& H, Tail&&... T
) {
if(idx == 0) {
std::string file = path.substr(path.find_last_of("/") + 1);
debug(nullptr, COLOR_LINE + file + " #" + std::to_string(line) + " (" + std::to_string(count[{ file, line }]++) + ")" + COLOR_INIT);
}
debug(nullptr, "\n - ");
const std::string content = dump(H);
const std::string type_name = get_type_name(std::forward<Head>(H));
debug(nullptr, COLOR_IDENTIFIER + args[idx] + COLOR_INIT + " : ");
debug(nullptr, content);
if(type_name.size() + content.size() >= 300) debug(nullptr, "\n ");
debug(nullptr, " " + type_name);
debug(args, idx + 1, 0, path, std::forward<Tail>(T)...);
}
}
namespace uni {
constexpr char LN = '\n';
constexpr char SPC = ' ';
constexpr uni::string DIRECTIONS = "URDL";
constexpr std::pair<int,int> DIRS4[] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };
constexpr std::pair<int,int> DIRS4P[] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 }, { 0, 0 } };
constexpr std::pair<int,int> DIRS8[] = { { -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 }, { 1, 0 }, { 1, -1 }, { 0, -1 }, { -1, -1 } };
constexpr std::pair<int,int> DIRS8P[] = { { -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 }, { 1, 0 }, { 1, -1 }, { 0, -1 }, { -1, -1 }, { 0, 0 } };
template<class T>
using spair = std::pair<T,T>;
template<class T>
using priority_queue_rev = std::priority_queue<T, std::vector<T>, std::greater<T>>;
}
namespace std {
using bit_reference = std::vector<bool>::reference;
bit_reference operator |= (bit_reference a, const bool b) noexcept(NO_EXCEPT) { return a = a | b; }
bit_reference operator &= (bit_reference a, const bool b) noexcept(NO_EXCEPT) { return a = a & b; }
}
namespace uni {
template<class Comparator, std::input_iterator I, std::sentinel_for<I> S>
constexpr std::optional<internal::size_t> cyclically_ordered(I first, S end) noexcept(NO_EXCEPT) {
constexpr auto comparator = Comparator{};
internal::size_t res = -1;
auto itr = first, prev = first;
for(internal::size_t i = 0; ++i, ++itr != end; ++prev) {
if(!comparator(*prev, *itr)) {
if(res >= 0) return {};
else res = i;
}
}
if(!comparator(*prev, *first)) {
if(res >= 0) return {};
else return 0;
}
return res;
}
template<class Comparator, std::ranges::input_range R>
constexpr auto cyclically_ordered(R&& vals) noexcept(NO_EXCEPT) {
return cyclically_ordered<Comparator>(std::ranges::begin((vals)),std::ranges::end((vals)));
}
template<std::ranges::input_range R>
constexpr auto cyclically_ordered(R&& vals) noexcept(NO_EXCEPT) {
return cyclically_ordered<std::less<>>(std::ranges::begin((vals)),std::ranges::end((vals)));
}
template<class Comparator, class T>
constexpr auto cyclically_ordered(std::initializer_list<T> vals) noexcept(NO_EXCEPT) {
return cyclically_ordered<Comparator>(std::ranges::begin((vals)),std::ranges::end((vals)));
}
template<class T>
constexpr auto cyclically_ordered(std::initializer_list<T> vals) noexcept(NO_EXCEPT) {
return cyclically_ordered<std::less<>>(std::ranges::begin((vals)),std::ranges::end((vals)));
}
template<class Comparator, class... Ts>
requires std::relation<Comparator, std::common_type_t<Ts...>, std::common_type_t<Ts...>>
constexpr auto cyclically_ordered(Ts&&... ps) noexcept(NO_EXCEPT) {
return cyclically_ordered<Comparator, std::common_type_t<Ts...>>({ std::forward<Ts>(ps)... });
}
template<class... Ts>
constexpr auto cyclically_ordered(Ts&&... ps) noexcept(NO_EXCEPT) {
return cyclically_ordered<std::less<>, std::common_type_t<Ts...>>({ std::forward<Ts>(ps)... });
}
}
__attribute__((constructor)) inline void fast_io() noexcept(NO_EXCEPT) { std::ios::sync_with_stdio(false), std::cin.tie(nullptr); }
namespace uni {
namespace gnu {
template<class Base>
struct hash_table : Base {
using key_type = typename Base::key_type;
using value_type = typename Base::value_type;
using mapped_type = typename Base::mapped_type;
inline bool contains(const key_type& key) const noexcept(NO_EXCEPT) {
return this->Base::find(key) != this->Base::end();
}
template<class K, class T>
inline decltype(auto) emplace(K&& key, T&& val) noexcept(NO_EXCEPT) {
return this->Base::insert({ std::forward<K>(key), std::forward<T>(val) });
}
mapped_type& at(const key_type& key) {
auto itr = this->Base::find(key);
if(itr == this->Base::end()) throw std::out_of_range("hash_table::at()");
return itr->second;
};
const mapped_type& at(const key_type & key) const {
auto itr = this->Base::find(key);
if(itr == this->Base::end()) throw std::out_of_range("hash_table::at()");
return itr->second;
};
};
template<class Key, class T, class Hash = void>
struct cc_hash_table : hash_table<__gnu_pbds::cc_hash_table<Key, T, Hash>> {
using hash_table<__gnu_pbds::cc_hash_table<Key, T, Hash>>::hash_table;
};
template<class Key, class T>
struct cc_hash_table<Key, T, void> : hash_table<__gnu_pbds::cc_hash_table<Key, T>> {
using hash_table<__gnu_pbds::cc_hash_table<Key, T>>::hash_table;
};
template<class Key, class T, class Hash = void>
struct gp_hash_table : hash_table<__gnu_pbds::gp_hash_table<Key, T, Hash>> {
using hash_table<__gnu_pbds::gp_hash_table<Key, T, Hash>>::hash_table;
};
template<class Key, class T>
struct gp_hash_table<Key, T, void> : hash_table<__gnu_pbds::gp_hash_table<Key, T>> {
using hash_table<__gnu_pbds::gp_hash_table<Key, T>>::hash_table;
};
}
}
namespace uni {
template<class T, int N>
using array = internal::advanced_container<std::array<T,N>>;
}
namespace uni {
template<class P>
requires
requires(P p) {
p.first;
p.second;
}
inline P swapped(P& pair) {
return P{ pair.second, pair.first };
}
}
namespace atcoder {
namespace internal {
constexpr long long safe_mod(long long x, long long m) {
x %= m;
if (x < 0) x += m;
return x;
}
struct barrett {
unsigned int _m;
unsigned long long im;
explicit barrett(unsigned int m) : _m(m), im((unsigned long long)(-1) / m + 1) {}
unsigned int umod() const { return _m; }
unsigned int mul(unsigned int a, unsigned int b) const {
unsigned long long z = a;
z *= b;
unsigned long long x =
(unsigned long long)(((unsigned __int128)(z)*im) >> 64);
unsigned long long y = x * _m;
return (unsigned int)(z - y + (z < y ? _m : 0));
}
};
constexpr long long pow_mod_constexpr(long long x, long long n, int m) {
if (m == 1) return 0;
unsigned int _m = (unsigned int)(m);
unsigned long long r = 1;
unsigned long long y = safe_mod(x, m);
while (n) {
if (n & 1) r = (r * y) % _m;
y = (y * y) % _m;
n >>= 1;
}
return r;
}
constexpr bool is_prime_constexpr(int n) {
if (n <= 1) return false;
if (n == 2 || n == 7 || n == 61) return true;
if (n % 2 == 0) return false;
long long d = n - 1;
while (d % 2 == 0) d /= 2;
constexpr long long bases[3] = {2, 7, 61};
for (long long a : bases) {
long long t = d;
long long y = pow_mod_constexpr(a, t, n);
while (t != n - 1 && y != 1 && y != n - 1) {
y = y * y % n;
t <<= 1;
}
if (y != n - 1 && t % 2 == 0) {
return false;
}
}
return true;
}
template <int n> constexpr bool is_prime = is_prime_constexpr(n);
constexpr std::pair<long long, long long> inv_gcd(long long a, long long b) {
a = safe_mod(a, b);
if (a == 0) return {b, 0};
long long s = b, t = a;
long long m0 = 0, m1 = 1;
while (t) {
long long u = s / t;
s -= t * u;
m0 -= m1 * u;
auto tmp = s;
s = t;
t = tmp;
tmp = m0;
m0 = m1;
m1 = tmp;
}
if (m0 < 0) m0 += b / s;
return {s, m0};
}
constexpr int primitive_root_constexpr(int m) {
if (m == 2) return 1;
if (m == 167772161) return 3;
if (m == 469762049) return 3;
if (m == 754974721) return 11;
if (m == 998244353) return 3;
int divs[20] = {};
divs[0] = 2;
int cnt = 1;
int x = (m - 1) / 2;
while (x % 2 == 0) x /= 2;
for (int i = 3; (long long)(i)*i <= x; i += 2) {
if (x % i == 0) {
divs[cnt++] = i;
while (x % i == 0) {
x /= i;
}
}
}
if (x > 1) {
divs[cnt++] = x;
}
for (int g = 2;; g++) {
bool ok = true;
for (int i = 0; i < cnt; i++) {
if (pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1) {
ok = false;
break;
}
}
if (ok) return g;
}
}
template <int m> constexpr int primitive_root = primitive_root_constexpr(m);
unsigned long long floor_sum_unsigned(unsigned long long n,
unsigned long long m,
unsigned long long a,
unsigned long long b) {
unsigned long long ans = 0;
while (true) {
if (a >= m) {
ans += n * (n - 1) / 2 * (a / m);
a %= m;
}
if (b >= m) {
ans += n * (b / m);
b %= m;
}
unsigned long long y_max = a * n + b;
if (y_max < m) break;
n = (unsigned long long)(y_max / m);
b = (unsigned long long)(y_max % m);
std::swap(m, a);
}
return ans;
}
}
}
namespace atcoder {
long long pow_mod(long long x, long long n, int m) {
assert(0 <= n && 1 <= m);
if (m == 1) return 0;
internal::barrett bt((unsigned int)(m));
unsigned int r = 1, y = (unsigned int)(internal::safe_mod(x, m));
while (n) {
if (n & 1) r = bt.mul(r, y);
y = bt.mul(y, y);
n >>= 1;
}
return r;
}
long long inv_mod(long long x, long long m) {
assert(1 <= m);
auto z = internal::inv_gcd(x, m);
assert(z.first == 1);
return z.second;
}
std::pair<long long, long long> crt(const std::vector<long long>& r,
const std::vector<long long>& m) {
assert(r.size() == m.size());
int n = int(r.size());
long long r0 = 0, m0 = 1;
for (int i = 0; i < n; i++) {
assert(1 <= m[i]);
long long r1 = internal::safe_mod(r[i], m[i]), m1 = m[i];
if (m0 < m1) {
std::swap(r0, r1);
std::swap(m0, m1);
}
if (m0 % m1 == 0) {
if (r0 % m1 != r1) return {0, 0};
continue;
}
long long g, im;
std::tie(g, im) = internal::inv_gcd(m0, m1);
long long u1 = (m1 / g);
if ((r1 - r0) % g) return {0, 0};
long long x = (r1 - r0) / g % u1 * im % u1;
r0 += x * m0;
m0 *= u1;
if (r0 < 0) r0 += m0;
}
return {r0, m0};
}
long long floor_sum(long long n, long long m, long long a, long long b) {
assert(0 <= n && n < (1LL << 32));
assert(1 <= m && m < (1LL << 32));
unsigned long long ans = 0;
if (a < 0) {
unsigned long long a2 = internal::safe_mod(a, m);
ans -= 1ULL * n * (n - 1) / 2 * ((a2 - a) / m);
a = a2;
}
if (b < 0) {
unsigned long long b2 = internal::safe_mod(b, m);
ans -= 1ULL * n * ((b2 - b) / m);
b = b2;
}
return ans + internal::floor_sum_unsigned(n, m, a, b);
}
}
namespace uni {
template<class... Args>
using vector = internal::advanced_container<std::vector<Args...>>;
}
namespace uni {
template<std::size_t B, class T>
uni::string to_base_n_string(T v) noexcept(NO_EXCEPT) {
constexpr std::string_view CHARS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static_assert(0 < B and B <= std::ranges::size(CHARS));
assert(0 <= v);
uni::string res;
while(v > 0) {
res += CHARS[v%B];
v /= B;
}
std::reverse(std::ranges::begin((res)),std::ranges::end((res)));
return res;
}
template<class T>
uni::string to_base_n_string(T v, const uni::internal::size_t b) noexcept(NO_EXCEPT) {
constexpr std::string_view CHARS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
assert(1 < b && b <= std::ranges::ssize(CHARS));
assert(0 <= v);
if(v == 0) return "0";
uni::string res;
while(v > 0) {
res += CHARS[v % b];
v /= b;
}
std::reverse(std::ranges::begin((res)),std::ranges::end((res)));
return res;
}
template<class T>
uni::vector<T> to_base_n_vector(T v, const uni::internal::size_t b) noexcept(NO_EXCEPT) {
assert(1 < b);
assert(0 <= v);
uni::vector<T> res;
while(v > 0) {
res.push_back(v%b);
v /= b;
}
return res;
}
template<std::bidirectional_iterator I, class T = typename std::iterator_traits<I>::value_type>
T from_base_n_sequence(I begin, I end, const uni::internal::size_t b) noexcept(NO_EXCEPT) {
assert(1 < b);
if(begin == end) return 0;
T res = 0;
for(auto itr=end; itr-- != begin; ) {
res *= b;
res += *itr;
}
return res;
}
template<class T, std::forward_iterator I>
T from_base_n_string(I begin, I end, const uni::internal::size_t b) noexcept(NO_EXCEPT) {
assert(1 < b);
if(begin == end) return 0;
T sgn = 1;
if(*begin == '-') {
sgn = -1;
++begin;
}
T res = 0;
for(auto itr=begin; itr != end; ++itr) {
res *= b;
if('0' <= *itr && *itr <= '9') {
res += *itr - '0';
}
else if('a' <= *itr && *itr <= 'z') {
res += *itr - 'a' + 10;
}
else if('A' <= *itr && *itr <= 'Z'){
res += *itr - 'A' + 10;
}
else {
assert(false);
}
}
return res * sgn;
}
template<std::ranges::bidirectional_range R, class T = std::ranges::range_value_t<R>>
requires std::ranges::common_range<R>
T from_base_n_sequence(R range, const uni::internal::size_t b) noexcept(NO_EXCEPT) {
return from_base_n_sequence(std::ranges::begin(range), std::ranges::end(range), b);
}
template<class T, std::ranges::bidirectional_range R>
requires std::ranges::common_range<R>
T from_base_n_string(R range, const uni::internal::size_t b) noexcept(NO_EXCEPT) {
return from_base_n_string<T>(std::ranges::begin(range), std::ranges::end(range), b);
}
}
namespace uni {
namespace internal {
template<class T>
struct iterator_interface {
using iterator_category = std::output_iterator_tag;
using difference_type = size_t;
using value_type = T;
using pointer = T*;
using reference = T&;
};
template<class T>
struct forward_iterator : iterator_interface<T> {
using iterator_category = std::forward_iterator_tag;
};
template<class T>
struct bidirectional_iterator_interface : forward_iterator<T> {
using iterator_category = std::bidirectional_iterator_tag;
};
template<class T>
struct random_access_iterator_base : bidirectional_iterator_interface<T> {
using iterator_category = std::random_access_iterator_tag;
using difference_type = typename bidirectional_iterator_interface<T>::difference_type;
public:
friend inline random_access_iterator_base operator+(random_access_iterator_base itr, const difference_type count) noexcept(NO_EXCEPT) { return itr += count, itr; }
friend inline random_access_iterator_base operator-(random_access_iterator_base itr, const difference_type count) noexcept(NO_EXCEPT) { return itr -= count, itr; }
};
template<class T, class Container, class Derived>
struct container_iterator_interface : random_access_iterator_base<T> {
using difference_type = std::make_signed_t<typename Container::size_type>;
private:
using derived = std::remove_cvref_t<Derived>;
Container* _ref;
difference_type _pos;
static_assert(std::three_way_comparable<difference_type>);
inline auto* _derived() noexcept(NO_EXCEPT) {
return static_cast<derived*>(this);
}
inline const auto* _derived() const noexcept(NO_EXCEPT) {
return static_cast<const derived*>(this);
}
public:
container_iterator_interface() noexcept = default;
container_iterator_interface(Container *const ref, const difference_type pos) noexcept(NO_EXCEPT) : _ref(ref), _pos(pos) {}
inline auto ref() const noexcept(NO_EXCEPT) { return this->_ref; }
inline auto pos() const noexcept(NO_EXCEPT) { return this->_pos; }
inline auto& pos() { return this->_pos; }
inline auto& operator++() noexcept(NO_EXCEPT) { return ++this->_pos, *this->_derived(); }
inline auto& operator--() noexcept(NO_EXCEPT) { return --this->_pos, *this->_derived(); }
inline auto operator++(int) noexcept(NO_EXCEPT) { auto res = *this->_derived(); return ++this->_pos, res; }
inline auto operator--(int) noexcept(NO_EXCEPT) { auto res = *this->_derived(); return --this->_pos, res; }
inline auto& operator+=(const difference_type count) noexcept(NO_EXCEPT) { return this->_pos += count, *this->_derived(); }
inline auto& operator-=(const difference_type count) noexcept(NO_EXCEPT) { return this->_pos -= count, *this->_derived(); }
inline auto operator*() const noexcept(NO_EXCEPT) { return this->ref()->get(this->_pos); }
inline auto operator[](const difference_type count) const noexcept(NO_EXCEPT) { return *(*this->_derived() + count); }
inline auto operator-(const derived& other) const noexcept(NO_EXCEPT) { return this->_pos - other._pos; }
friend inline bool operator==(const derived& lhs, const derived& rhs) noexcept(NO_EXCEPT) {
if(lhs.ref() == rhs.ref()) return lhs._pos == rhs._pos;
return false;
}
friend inline std::partial_ordering operator<=>(const derived& lhs, const derived& rhs) noexcept(NO_EXCEPT) {
if(lhs.ref() != rhs.ref()) return std::partial_ordering::unordered;
return lhs._pos <=> rhs._pos;
}
};
namespace iterator_impl {
template<class... Tags>
using is_all_random_access_iterator = is_base_of_all<std::random_access_iterator_tag,Tags...>;
template<class... Tags>
using is_all_bidirectional_iterator = is_base_of_all<std::bidirectional_iterator_tag,Tags...>;
template<class... Tags>
using is_all_forward_iterator = is_base_of_all<std::forward_iterator_tag,Tags...>;
template<class... Tags>
using is_all_input_iterator = is_base_of_all<std::input_iterator_tag,Tags...>;
template<class... Tags>
constexpr auto _most_primitive_iterator_tag() {
if constexpr(is_all_random_access_iterator<Tags...>::value) {
return std::random_access_iterator_tag{};
}
else if constexpr(is_all_bidirectional_iterator<Tags...>::value) {
return std::bidirectional_iterator_tag{};
}
else if constexpr(is_all_forward_iterator<Tags...>::value) {
return std::forward_iterator_tag{};
}
else {
return std::input_iterator_tag{};
}
}
}
template<class... Tags>
using most_primitive_iterator_tag = decltype(iterator_impl::_most_primitive_iterator_tag<Tags...>());
template<class T, class = void>
struct is_iterator {
static constexpr bool value = false;
};
template<class T>
struct is_iterator<T, typename std::enable_if<!std::is_same<typename std::iterator_traits<T>::value_type, void>::value>::type> {
static constexpr bool value = true;
};
template<class T>
inline constexpr bool is_iterator_v = is_iterator<T>::value;
template<class T>
using is_iterator_t = std::enable_if_t<is_iterator_v<T>>;
template<class T>
using iota_diff_t = std::make_signed_t<T>;
}
}
namespace uni {
namespace internal {
template<class Range>
concept resizable_range
= std::ranges::range<Range> &&
requires (Range& r) { r.resize(0); };
template<class range>
concept simple_view
= std::ranges::view<range> && std::ranges::range<const range> &&
std::same_as<std::ranges::iterator_t<range>, std::ranges::iterator_t<const range>> &&
std::same_as<std::ranges::sentinel_t<range>, std::ranges::sentinel_t<const range>>;
template<class... Ranges>
concept zip_is_common = (sizeof...(Ranges) == 1 && (std::ranges::common_range<Ranges> && ...))
|| (!(std::ranges::bidirectional_range<Ranges> && ...) && (std::ranges::common_range<Ranges> && ...))
|| ((std::ranges::random_access_range<Ranges> && ...) && (std::ranges::sized_range<Ranges> && ...));
template<bool Const, class... Views>
concept all_contiguous = (std::ranges::contiguous_range<maybe_const_t<Const, Views>> && ...);
template<bool Const, class... Views>
concept all_random_access = (std::ranges::random_access_range<maybe_const_t<Const, Views>> && ...);
template<bool Const, class... Views>
concept all_bidirectional = (std::ranges::bidirectional_range<maybe_const_t<Const, Views>> && ...);
template<bool Const, class... Views>
concept all_forward = (std::ranges::forward_range<maybe_const_t<Const, Views>> && ...);
template<bool Const, class... Views> struct zip_view_iterator_category {};
template<bool Const, class... Views>
requires all_forward<Const, Views...>
struct zip_view_iterator_category<Const, Views...> {
using iterator_category = std::input_iterator_tag;
};
template<bool Const, class... Views>
static auto _most_primitive_iterator_concept() noexcept(NO_EXCEPT) {
if constexpr(all_random_access<Const, Views...>)
return std::random_access_iterator_tag{};
else if constexpr(all_bidirectional<Const, Views...>)
return std::bidirectional_iterator_tag{};
else if constexpr(all_forward<Const, Views...>)
return std::forward_iterator_tag{};
else
return std::input_iterator_tag{};
}
template<bool Const, class... Views>
using most_primitive_iterator_concept = decltype(_most_primitive_iterator_concept<Const, Views...>());
template<class Range, bool Const>
using range_iterator_category = typename std::iterator_traits<
std::ranges::iterator_t<maybe_const_t<Const, Range>>
>::iterator_category;
template<class Range>
static constexpr auto _iterator_concept() noexcept(NO_EXCEPT) {
if constexpr(std::ranges::random_access_range<Range>)
return std::random_access_iterator_tag{};
else if constexpr(std::ranges::bidirectional_range<Range>)
return std::bidirectional_iterator_tag{};
else if constexpr(std::ranges::forward_range<Range>)
return std::forward_iterator_tag{};
else
return std::input_iterator_tag{};
}
template<class Range>
using iterator_concept = decltype(_iterator_concept<Range>());
template<std::ranges::range Range> struct cached_position {
constexpr bool has_value() const { return false; }
constexpr std::ranges::iterator_t<Range> get(const Range&) const {
__builtin_unreachable();
}
constexpr void set(const Range &, const std::ranges::iterator_t<Range> &) const {}
};
template<std::ranges::forward_range Range>
struct cached_position<Range> : protected std::optional<std::ranges::iterator_t<Range>> {
using std::optional<std::ranges::iterator_t<Range>>::optioanl;
using std::optional<std::ranges::iterator_t<Range>>::has_value;
constexpr std::ranges::iterator_t<Range> get(const Range&) const {
assert(this->has_value());
return **this;
}
constexpr void set(const Range&, const std::ranges::iterator_t<Range>& itr) {
assert(!this->has_value());
this->emplace(*itr);
}
};
template<std::ranges::random_access_range Range>
requires(sizeof(std::ranges::range_difference_t<Range>) <= sizeof(std::ranges::iterator_t<Range>))
struct cached_position<Range> {
private:
std::ranges::range_difference_t<Range> _offset = -1;
public:
cached_position() = default;
constexpr cached_position(const cached_position &) = default;
constexpr cached_position(cached_position &&other) noexcept {
*this = std::move(other);
}
constexpr cached_position &operator=(const cached_position &) = default;
constexpr cached_position &operator=(cached_position &&other) noexcept {
this->_offset = other._offset;
other._offset = -1;
return *this;
}
constexpr bool has_value() const { return this->_offset >= 0; }
constexpr std::ranges::iterator_t<Range> get(Range& range) const {
assert(this->has_value());
return std::ranges::begin(range) + this->_offset;
}
constexpr void set(Range &range, const std::ranges::iterator_t<Range> &itr) {
assert(!this->has_value());
this->_offset = itr - std::ranges::begin(range);
}
};
template<typename T, int Disc>
struct absent { };
template<bool PRESENT, class T, int Disc = 0>
using maybe_present_t = std::conditional_t<PRESENT, T, absent<T, Disc>>;
}
namespace views::adaptor {
template<class Adaptor, class... Args>
concept adaptor_invocable = requires { std::declval<Adaptor>()(std::declval<Args>()...); };
template<class Adaptor, class... Args>
concept adaptor_partial_app_viable =
(Adaptor::arity > 1) && (sizeof...(Args) == Adaptor::arity - 1) &&
(std::constructible_from<std::remove_cvref_t<Args>, Args> && ...);
template<class Adaptor, class... Args> struct partial;
template<class, class> struct pipe;
template<class Derived> struct range_adaptor_closure {};
template<class T, class U>
requires(!std::same_as<T, range_adaptor_closure<U>>)
void is_range_adaptor_closure_fn(const T &, const range_adaptor_closure<U> &);
template<class T>
concept is_range_adaptor_closure = requires(T t) { adaptor::is_range_adaptor_closure_fn(t, t); };
template<class Self, class Range>
requires is_range_adaptor_closure<Self> && adaptor_invocable<Self, Range>
constexpr auto operator|(Range&& range, Self&& self) {
return std::forward<Self>(self)(std::forward<Range>(range));
}
template<class Lhs, class Rhs>
requires is_range_adaptor_closure<Lhs> && is_range_adaptor_closure<Rhs>
constexpr auto operator|(Lhs&& lhs, Rhs&& rhs) {
return pipe<std::remove_cvref_t<Lhs>, std::remove_cvref_t<Rhs>>{ std::forward<Lhs>(lhs), std::forward<Rhs>(rhs)};
}
template<class Derived> struct range_adaptor {
template<class... Args>
requires adaptor_partial_app_viable<Derived, Args...>
inline constexpr auto operator()(Args&& ..._args) const noexcept(NO_EXCEPT) {
return partial<Derived, std::remove_cvref_t<Args>...>{
std::forward<Args>(_args)...
};
}
};
template<class Adaptor>
concept closure_has_simple_call_op = Adaptor::has_simple_call_op;
template<class Adaptor, class... Args>
concept adaptor_has_simple_extra_args =
Adaptor::has_simple_extra_args ||
Adaptor::template has_simple_extra_args<Args...>;
template<class Adaptor, class... Args>
struct partial : range_adaptor_closure<partial<Adaptor, Args...>> {
std::tuple<Args...> args;
constexpr partial(Args... _args) noexcept(NO_EXCEPT) : args(std::move(_args)...) {}
template<class Range>
requires adaptor_invocable<Adaptor, Range, const Args &...>
inline constexpr auto operator()(Range&& range) const & noexcept(NO_EXCEPT) {
const auto forwarder = [&range](const auto &..._args) constexpr noexcept(NO_EXCEPT) {
return Adaptor{}(std::forward<Range>(range), _args...);
};
return std::apply(forwarder, this->args);
}
template<class Range>
requires adaptor_invocable<Adaptor, Range, Args...>
inline constexpr auto operator()(Range&& range) && noexcept(NO_EXCEPT) {
const auto forwarder = [&range](auto &..._args) constexpr noexcept(NO_EXCEPT) {
return Adaptor{}(std::forward<Range>(range), std::move(_args)...);
};
return std::apply(forwarder, this->args);
}
template<class Range>
inline constexpr auto operator()(Range&& range) const && = delete;
};
template<class Adaptor, class Arg>
struct partial<Adaptor, Arg> : range_adaptor_closure<partial<Adaptor, Arg>> {
Arg arg;
constexpr partial(Arg _arg) noexcept(NO_EXCEPT) : arg(std::move(_arg)) {}
template<class Range>
requires adaptor_invocable<Adaptor, Range, const Arg &>
inline constexpr auto operator()(Range&& range) const & noexcept(NO_EXCEPT) {
return Adaptor{}(std::forward<Range>(range), this->arg);
}
template<class Range>
requires adaptor_invocable<Adaptor, Range, Arg>
inline constexpr auto operator()(Range&& range) && noexcept(NO_EXCEPT) {
return Adaptor{}(std::forward<Range>(range), std::move(this->arg));
}
template<class Range>
inline constexpr auto operator()(Range&& range) const && = delete;
};
template<class Adaptor, class... Args>
requires adaptor_has_simple_extra_args<Adaptor, Args...> && (std::is_trivially_copyable_v<Args> && ...)
struct partial<Adaptor, Args...> : range_adaptor_closure<partial<Adaptor, Args...>> {
std::tuple<Args...> args;
constexpr partial(Args... _args) noexcept(NO_EXCEPT) : args(std::move(_args)...) {}
template<class Range>
requires adaptor_invocable<Adaptor, Range, const Args &...>
inline constexpr auto operator()(Range&& range) const noexcept(NO_EXCEPT) {
const auto forwarder = [&range](const auto &..._args) constexpr noexcept(NO_EXCEPT) {
return Adaptor{}(std::forward<Range>(range), _args...);
};
return std::apply(forwarder, this->args);
}
static constexpr bool has_simple_call_op = true;
};
template<class Adaptor, class Arg>
requires adaptor_has_simple_extra_args<Adaptor, Arg> &&
std::is_trivially_copyable_v<Arg>
struct partial<Adaptor, Arg> : range_adaptor_closure<partial<Adaptor, Arg>> {
Arg arg;
constexpr partial(Arg _arg) noexcept(NO_EXCEPT) : arg(std::move(_arg)) {}
template<class Range>
requires adaptor_invocable<Adaptor, Range, const Arg &>
inline constexpr auto operator()(Range&& range) const noexcept(NO_EXCEPT) {
return Adaptor{}(std::forward<Range>(range), this->arg);
}
static constexpr bool has_simple_call_op = true;
};
template<class Lhs, class Rhs, class Range>
concept pipe_invocable = requires {
std::declval<Rhs>()(std::declval<Lhs>()(std::declval<Range>()));
};
template<class Lhs, class Rhs> struct pipe : range_adaptor_closure<pipe<Lhs, Rhs>> {
[[no_unique_address]] Lhs lhs;
[[no_unique_address]] Rhs rhs;
constexpr pipe(Lhs _lhs, Rhs _rhs) noexcept(NO_EXCEPT) : lhs(std::move(_lhs)), rhs(std::move(_rhs)) {}
template<class Range>
requires pipe_invocable<const Lhs &, const Rhs &, Range>
inline constexpr auto operator()(Range&& range) const & noexcept(NO_EXCEPT) {
return rhs(lhs(std::forward<Range>(range)));
}
template<class Range>
requires pipe_invocable<Lhs, Rhs, Range>
inline constexpr auto operator()(Range&& range) && noexcept(NO_EXCEPT) {
return std::move(rhs)(std::move(lhs)(std::forward<Range>(range)));
}
template<class Range>
inline constexpr auto operator()(Range&& range) const && = delete;
};
template<class Lhs, class Rhs>
requires closure_has_simple_call_op<Lhs> && closure_has_simple_call_op<Rhs>
struct pipe<Lhs, Rhs> : range_adaptor_closure<pipe<Lhs, Rhs>> {
[[no_unique_address]] Lhs lhs;
[[no_unique_address]] Rhs rhs;
constexpr pipe(Lhs _lhs, Rhs _rhs) noexcept(NO_EXCEPT) : lhs(std::move(_lhs)), rhs(std::move(_rhs)) {}
template<class Range>
requires pipe_invocable<const Lhs &, const Rhs &, Range>
inline constexpr auto operator()(Range&& range) const noexcept(NO_EXCEPT) {
return rhs(lhs(std::forward<Range>(range)));
}
static constexpr bool has_simple_call_op = true;
};
}
}
namespace uni {
template<class T> struct valarray : internal::advanced_container<std::valarray<T>> {
private:
using base = internal::advanced_container<std::valarray<T>>;
public:
using size_type = internal::size_t;
using iterator = T*;
using const_iterator = const T*;
protected:
inline bool _validate_index_in_right_open([[maybe_unused]] const size_type p) const noexcept(NO_EXCEPT) {
return 0 <= p and p < this->size();
}
inline bool _validate_index_in_closed([[maybe_unused]] const size_type p) const noexcept(NO_EXCEPT) {
return 0 <= p and p <= this->size();
}
inline bool _validate_rigth_open_interval([[maybe_unused]] const size_type l, [[maybe_unused]] const size_type r) const noexcept(NO_EXCEPT) {
return 0 <= l and l <= r and r <= this->size();
}
inline size_type _positivize_index(const size_type p) const noexcept(NO_EXCEPT) {
return p < 0 ? this->size() + p : p;
}
public:
valarray() noexcept(NO_EXCEPT) {}
explicit valarray(const std::size_t length, const T& val = T{}) noexcept(NO_EXCEPT) : base(val, length) {}
template<std::input_iterator I, std::sentinel_for<I> S>
valarray(I first, S last) noexcept(NO_EXCEPT) : base(std::ranges::distance(first, last)) { std::ranges::copy(first, last, std::ranges::begin(*this)); }
template<class U> valarray(const U* pointer, const size_t n) noexcept(NO_EXCEPT) : base(pointer, n) {};
valarray(const std::slice_array<T>& arr) noexcept(NO_EXCEPT) : base(arr) {};
valarray(const std::gslice_array<T>& arr) noexcept(NO_EXCEPT) : base(arr) {};
valarray(const std::mask_array<T>& arr) noexcept(NO_EXCEPT) : base(arr) {};
valarray(const std::indirect_array<T>& arr) noexcept(NO_EXCEPT) : base(arr) {};
valarray(const std::initializer_list<T>& init) noexcept(NO_EXCEPT) : base(init) {}
valarray(const internal::advanced_container<std::valarray<T>>& arr) noexcept(NO_EXCEPT) : base(arr) {}
template<class Dom> valarray(const std::_Expr<Dom,T>& expr) noexcept(NO_EXCEPT) : base(expr) {}
inline auto size() const noexcept(NO_EXCEPT) { return static_cast<size_type>(this->base::size()); }
inline void reserve(const size_type) noexcept(NO_EXCEPT) { }
template<std::input_iterator I, std::sentinel_for<I> S>
inline void assign(I first, S last) noexcept(NO_EXCEPT) {
this->resize(std::ranges::distance(first, last));
std::ranges::copy(first, last, std::ranges::begin(*this));
}
inline void assign(const std::size_t length, const T& val = T{}) noexcept(NO_EXCEPT) {
this->base::resize(length, val);
}
inline void resize(const std::size_t length, const T& val = T{}) noexcept(NO_EXCEPT) {
base temp = *this;
this->assign(length, val);
std::move(std::begin(temp), std::min(std::end(temp), std::next(std::begin(temp), length)), std::begin(*this));
}
inline const T& operator[](size_type pos) const noexcept(NO_EXCEPT) {
pos = this->_positivize_index(pos), assert(this->_validate_index_in_right_open(pos));
return this->base::operator[](pos);
}
inline T& operator[](size_type pos) noexcept(NO_EXCEPT) {
pos = this->_positivize_index(pos), assert(this->_validate_index_in_right_open(pos));
return this->base::operator[](pos);
}
inline const T& back() const noexcept(NO_EXCEPT) { return *std::prev(this->end()); }
inline T& back() noexcept(NO_EXCEPT) { return *std::prev(this->end()); }
inline const T& front() const noexcept(NO_EXCEPT) { return *this->begin(); }
inline T& front() noexcept(NO_EXCEPT) { return *this->begin(); }
inline auto rbegin() noexcept(NO_EXCEPT) { return std::make_reverse_iterator(std::ranges::end(*this)); }
inline auto rend() noexcept(NO_EXCEPT) { return std::make_reverse_iterator(std::ranges::begin(*this)); }
inline auto rbegin() const noexcept(NO_EXCEPT) { return std::make_reverse_iterator(std::ranges::end(*this)); }
inline auto rend() const noexcept(NO_EXCEPT) { return std::make_reverse_iterator(std::ranges::begin(*this)); }
};
}
namespace uni {
template<class SizeType = internal::size_t, class Container = valarray<SizeType>>
struct z_array : Container {
using size_type = SizeType;
template<std::input_iterator I, std::sentinel_for<I> S>
z_array(I first, S last) : Container(std::ranges::distance(first, last), {}) {
const size_type n = static_cast<size_type>(std::ranges::distance(first, last));
if(n == 0) return;
for(size_type i = 1, j = 0; i < n; ++i) {
size_type& k = this->operator[](i);
k = (j + this->operator[](j) <= i) ? 0 : std::ranges::min(j + this->operator[](j) - i, this->operator[](i - j));
while(i + k < n and first[k] == first[i + k]) ++k;
if(j + this->operator[](j) < i + this->operator[](i)) j = i;
}
*this->begin() = n;
}
template<std::ranges::input_range R>
explicit z_array(R&& range) : z_array(std::ranges::begin((range)),std::ranges::end((range))) {}
};
}
namespace uni {
namespace internal {
namespace view_impl {
template<std::ranges::input_range V0, std::ranges::input_range V1>
requires std::ranges::view<V0> && std::ranges::view<V1>
struct concat_view : std::ranges::view_interface<concat_view<V0, V1>> {
private:
V0 _b0;
V1 _b1;
template<bool Const> using B0 = internal::maybe_const_t<Const, V0>;
template<bool Const> using B1 = internal::maybe_const_t<Const, V1>;
template<bool Const> struct iterator_tag {};
template<bool Const>
requires std::ranges::forward_range<B0<Const>> && std::ranges::forward_range<B1<Const>>
struct iterator_tag<Const> {
public:
using iterator_category = uni::internal::most_primitive_iterator_tag<
typename std::iterator_traits<std::ranges::iterator_t<B0<Const>>>::iterator_category,
typename std::iterator_traits<std::ranges::iterator_t<B1<Const>>>::iterator_category
>;
};
public:
template<bool> class iterator;
constexpr explicit concat_view(V0 v0, V1 v1) noexcept(NO_EXCEPT)
: _b0(std::move(v0)), _b1(std::move(v1))
{}
inline constexpr std::pair<V0, V1> base() const & noexcept(NO_EXCEPT)
requires std::copy_constructible<V0> && std::copy_constructible<V0>
{
return { this->_b0, this->_b1 };
}
inline constexpr std::pair<V0,V1> base() && noexcept(NO_EXCEPT) {
return { std::move(this->_b0), std::move(this->_b1) };
}
inline constexpr auto begin() noexcept(NO_EXCEPT)
requires (!internal::simple_view<V0> && !internal::simple_view<V1>)
{
return iterator<false>(this, std::ranges::begin(this->_b0), std::ranges::begin(this->_b1), 0);
}
inline constexpr auto begin() const noexcept(NO_EXCEPT)
requires std::ranges::range<const V0> && std::ranges::range<const V1>
{
return iterator<true>(this, std::ranges::begin(this->_b0), std::ranges::begin(this->_b1), 0);
}
inline constexpr auto end() noexcept(NO_EXCEPT)
requires (!internal::simple_view<V0> && !internal::simple_view<V1>)
{
if constexpr(std::ranges::common_range<V0> && std::ranges::common_range<V1>) {
return iterator<false>(this, std::ranges::end(this->_b0), std::ranges::end(this->_b1), 1);
}
else {
return std::default_sentinel;
}
}
inline constexpr auto end() const noexcept(NO_EXCEPT)
requires std::ranges::range<const V0> && std::ranges::range<const V1>
{
if constexpr(std::ranges::common_range<const V0> && std::ranges::common_range<const V1>) {
return iterator<true>(this, std::ranges::end(this->_b0), std::ranges::end(this->_b1), 1);
}
else {
return std::default_sentinel;
}
}
inline constexpr auto size() noexcept(NO_EXCEPT)
requires std::ranges::sized_range<V0> && std::ranges::sized_range<V1>
{
return static_cast<std::size_t>(std::ranges::distance(this->_b0) + std::ranges::distance(this->_b1));
}
inline constexpr auto size() const noexcept(NO_EXCEPT)
requires std::ranges::sized_range<const V0> && std::ranges::sized_range<const V1>
{
return static_cast<std::size_t>(std::ranges::distance(this->_b0) + std::ranges::distance(this->_b1));
}
};
template<std::ranges::input_range V0, std::ranges::input_range V1>
requires std::ranges::view<V0> && std::ranges::view<V1>
template<bool Const>
struct concat_view<V0, V1>::iterator : iterator_tag<Const> {
private:
using Parent = internal::maybe_const_t<Const, concat_view>;
using B0 = concat_view::B0<Const>;
using B1 = concat_view::B1<Const>;
std::ranges::iterator_t<B0> _c0 = std::ranges::iterator_t<B0>();
std::ranges::iterator_t<B0> _b0 = std::ranges::iterator_t<B0>();
std::ranges::sentinel_t<B0> _e0 = std::ranges::sentinel_t<B0>();
std::ranges::iterator_t<B1> _c1 = std::ranges::iterator_t<B1>();
std::ranges::iterator_t<B1> _b1 = std::ranges::iterator_t<B1>();
std::ranges::sentinel_t<B1> _e1 = std::ranges::sentinel_t<B1>();
int _block = 0;
constexpr iterator(Parent *const parent, const std::ranges::iterator_t<B0> c0, const std::ranges::iterator_t<B1> c1, const int block) noexcept(NO_EXCEPT)
: _c0(std::move(c0)), _b0(std::ranges::begin(parent->_b0)), _e0(std::ranges::end(parent->_b0)),
_c1(std::move(c1)), _b1(std::ranges::begin(parent->_b1)), _e1(std::ranges::end(parent->_b1)),
_block(block || std::ranges::empty(parent->_b0))
{}
friend concat_view;
public:
using difference_type = std::common_type_t<std::ranges::range_difference_t<B0>, std::ranges::range_difference_t<B1>>;
using value_type = std::common_type_t<std::ranges::range_value_t<B0>, std::ranges::range_value_t<B1>>;
using reference_type = std::common_reference_t<std::ranges::range_reference_t<B0>, std::ranges::range_reference_t<B1>>;
using iterator_concept = most_primitive_iterator_concept<Const, V0, V1>;
iterator() noexcept(NO_EXCEPT)
requires std::default_initializable<std::ranges::iterator_t<B0>> &&
std::default_initializable<std::ranges::iterator_t<B0>>
= default;
constexpr iterator(iterator<!Const> itr) noexcept(NO_EXCEPT)
requires
Const &&
std::convertible_to<std::ranges::iterator_t<V0>, std::ranges::iterator_t<B0>> &&
std::convertible_to<std::ranges::sentinel_t<V0>, std::ranges::sentinel_t<B0>> &&
std::convertible_to<std::ranges::iterator_t<V1>, std::ranges::iterator_t<B1>> &&
std::convertible_to<std::ranges::sentinel_t<V1>, std::ranges::sentinel_t<B1>>
: _c0(std::move(itr._c0)), _b0(std::move(itr._b0)), _e0(std::move(itr._e0)),
_c1(std::move(itr._c0)), _b1(std::move(itr._b0)), _e1(std::move(itr._e1)),
_block(itr._block)
{}
inline constexpr std::variant<std::ranges::iterator_t<B0>, std::ranges::iterator_t<B1>>
base() && noexcept(NO_EXCEPT) {
if(this->_block == 0) return std::move(this->_c0);
else return std::move(this->_C1);
}
inline constexpr
std::variant<
std::reference_wrapper<const std::ranges::iterator_t<B0>>,
std::reference_wrapper<const std::ranges::iterator_t<B1>>
>
base() const & noexcept {
if(this->_block == 0) return std::move(this->_c0);
else return std::move(this->_c1);
}
inline constexpr reference_type operator*() const noexcept(NO_EXCEPT)
{
if(this->_block == 0) return *this->_c0;
else return *this->_c1;
}
inline constexpr iterator& operator++() noexcept(NO_EXCEPT)
{
assert(this->_c0 != this->_e0 or this->_c1 != this->_e1);
if(this->_block == 0) {
if(++this->_c0 == this->_e0) {
this->_block = 1;
assert(this->_c1 == this->_b1);
}
}
else {
++this->_c1;
}
return *this;
}
inline constexpr void operator++(int) noexcept(NO_EXCEPT) { ++*this; }
inline constexpr iterator operator++(int) noexcept(NO_EXCEPT)
requires std::ranges::forward_range<B0> && std::ranges::forward_range<B1>
{
const auto res = *this; ++*this; return res;
}
inline constexpr iterator& operator--() noexcept(NO_EXCEPT)
requires
std::ranges::bidirectional_range<B0> && std::ranges::bidirectional_range<B1> &&
std::bidirectional_iterator<std::ranges::sentinel_t<B0>>
{
if(this->_block == 1) {
if(this->_c1 == this->_b1) {
this->_block = 0;
this->_c0 = std::ranges::prev(this->_e0);
}
else {
--this->_c1;
}
}
else {
--this->_c0;
}
return *this;
}
inline constexpr iterator operator--(int) noexcept(NO_EXCEPT)
requires std::ranges::bidirectional_range<B0> && std::ranges::bidirectional_range<B1>
{
const auto res = *this; --*this; return res;
}
inline constexpr iterator& operator+=(const difference_type diff) noexcept(NO_EXCEPT)
requires
std::ranges::random_access_range<B0> && std::ranges::random_access_range<B1>
{
if(diff > 0) {
if(this->_block == 0) {
const auto missing = std::ranges::advance(this->_c0, diff, this->_e0);
if(this->_c0 == this->_e0) {
this->_block = 1;
assert(this->_c1 == this->_b1);
std::ranges::advance(this->_c1, missing, this->_e1);
}
}
else {
std::ranges::advance(this->_c1, diff, this->_e1);
}
}
if(diff < 0) {
if(this->_block == 1) {
const auto missing = std::ranges::advance(this->_c1, diff, this->_b1);
if(missing < 0) {
this->_block = 0;
assert(this->_c0 == this->_e0);
std::ranges::advance(this->_c0, missing, this->_b0);
}
}
else {
std::ranges::advance(this->_c0, diff, this->_b0);
}
}
return *this;
}
inline constexpr iterator& operator-=(const difference_type diff) noexcept(NO_EXCEPT)
requires std::ranges::random_access_range<B0> && std::ranges::random_access_range<B1>
{
return *this += -diff;
}
inline constexpr decltype(auto) operator[](const difference_type diff) const noexcept(NO_EXCEPT)
requires std::ranges::random_access_range<B0> && std::ranges::random_access_range<B1>
{
return *(*this + diff);
}
friend inline constexpr bool operator==(const iterator& lhs, std::default_sentinel_t) noexcept(NO_EXCEPT)
{
if(lhs._block == 0) return false;
if(lhs._block == 1) return lhs._c1 == lhs._e1;
assert(false);
}
friend inline constexpr bool operator==(const iterator& lhs, const iterator& rhs) noexcept(NO_EXCEPT)
requires
std::equality_comparable<std::ranges::iterator_t<B0>> &&
std::equality_comparable<std::ranges::iterator_t<B1>>
{
if(lhs._block != rhs._block) return false;
return lhs._block == 0 ? lhs._c0 == rhs._c0 : lhs._c1 == rhs._c1;
}
friend inline constexpr auto operator<=>(const iterator& lhs, const iterator& rhs) noexcept(NO_EXCEPT)
requires std::ranges::random_access_range<B0> && std::ranges::random_access_range<B1>
{
if(lhs._block != rhs._block) return lhs._block <=> rhs._block;
return lhs._block == 0 ? lhs._c0 <=> rhs._c0 : lhs._c1 <=> rhs._c1;
}
friend inline constexpr iterator operator+(const iterator& itr, const difference_type diff) noexcept(NO_EXCEPT)
requires std::ranges::random_access_range<B0> && std::ranges::random_access_range<B1>
{
auto res = itr; res += diff; return res;
}
friend inline constexpr iterator operator+(const difference_type diff, const iterator& itr) noexcept(NO_EXCEPT)
requires std::ranges::random_access_range<B0> && std::ranges::random_access_range<B1>
{
return itr + diff;
}
friend inline constexpr iterator operator-(const iterator& itr, const difference_type diff) noexcept(NO_EXCEPT)
requires std::ranges::random_access_range<B0> && std::ranges::random_access_range<B1>
{
auto res = itr; res -= diff; return res;
}
friend inline constexpr const difference_type operator-(const iterator& lhs, const iterator& rhs) noexcept(NO_EXCEPT)
requires
std::sized_sentinel_for<std::ranges::iterator_t<B0>, std::ranges::iterator_t<B0>> &&
std::sized_sentinel_for<std::ranges::iterator_t<B1>, std::ranges::iterator_t<B1>>
{
if(lhs._block == rhs._block) {
return lhs._block == 0 ? std::ranges::distance(rhs._c0, lhs._c0) : std::ranges::distance(rhs._c1, lhs._c1);
}
if(lhs._block > rhs._block) return std::ranges::distance(rhs._c0, rhs._e0) + std::ranges::distance(lhs._b1, lhs._c1);
if(lhs._block < rhs._block) return -(rhs - lhs);
assert(false);
}
friend inline constexpr const difference_type operator-(std::default_sentinel_t, const iterator& rhs) noexcept(NO_EXCEPT)
requires
std::sized_sentinel_for<std::ranges::sentinel_t<B0>, std::ranges::iterator_t<B0>> &&
std::sized_sentinel_for<std::ranges::sentinel_t<B1>, std::ranges::iterator_t<B1>>
{
if(rhs._block == 0) return std::ranges::distance(rhs._c0, rhs._e0) + std::ranges::distance(rhs._b1, rhs._e1);
if(rhs._block == 1) return std::ranges::distance(rhs._c1, rhs._e1);
assert(false);
}
friend inline constexpr const difference_type operator-(const iterator& lhs, std::default_sentinel_t rhs) noexcept(NO_EXCEPT)
requires
std::sized_sentinel_for<std::ranges::sentinel_t<B0>, std::ranges::iterator_t<B0>> &&
std::sized_sentinel_for<std::ranges::sentinel_t<B1>, std::ranges::iterator_t<B1>>
{
return -(rhs - lhs);
}
friend inline constexpr
std::common_reference_t<
std::ranges::range_rvalue_reference_t<B0>,
std::ranges::range_rvalue_reference_t<B1>
>
iter_move(const iterator& itr) noexcept(NO_EXCEPT)
{
if(itr._block == 0) return std::ranges::iter_move(itr._c0);
if(itr._block == 1) return std::ranges::iter_move(itr._c1);
assert(false);
}
friend inline constexpr void iter_swap(const iterator& lhs, const iterator& rhs) noexcept(NO_EXCEPT)
requires
std::indirectly_swappable<std::ranges::iterator_t<B0>> &&
std::indirectly_swappable<std::ranges::iterator_t<B1>> &&
std::indirectly_swappable<std::ranges::iterator_t<B0>, std::ranges::iterator_t<B1>>
{
if(lhs._block == 0 && rhs._block == 0) std::ranges::iter_swap(lhs._c0, rhs._c0);
if(lhs._block == 0 && rhs._block == 1) std::ranges::iter_swap(lhs._c0, rhs._c1);
if(lhs._block == 1 && rhs._block == 0) std::ranges::iter_swap(lhs._c1, rhs._c0);
if(lhs._block == 1 && rhs._block == 1) std::ranges::iter_swap(lhs._c1, rhs._c1);
assert(false);
}
};
}
}
template<class...> struct concat_view;
template<class T>
struct concat_view<T> : std::views::all_t<T> {
using std::views::all_t<T>::all_t;
};
template<class T0, class T1>
struct concat_view<T0, T1> : internal::view_impl::concat_view<std::views::all_t<T0>, std::views::all_t<T1>> {
explicit concat_view(T0&& v0, T1&& v1) noexcept(NO_EXCEPT)
: internal::view_impl::concat_view<std::views::all_t<T0>, std::views::all_t<T1>>(std::forward<T0>(v0), std::forward<T1>(v1))
{}
};
template<class T0, class T1, class... Ts>
struct concat_view<T0, T1, Ts...> : concat_view<concat_view<T0, T1>, Ts...> {
explicit concat_view(T0&& v0, T1&& v1, Ts&&... vs) noexcept(NO_EXCEPT)
: concat_view<concat_view<T0, T1>, Ts...>(
concat_view<T0, T1>(std::forward<T0>(v0), std::forward<T1>(v1)), std::forward<Ts>(vs)...
)
{}
};
namespace views {
namespace internal {
template<class... Ts>
concept can_concat_view = requires { concat_view<Ts...>(std::declval<Ts>()...); };
}
struct Concat {
template<class... Ts>
requires (sizeof...(Ts) == 0 || internal::can_concat_view<Ts...>)
inline constexpr auto operator() [[nodiscard]] (Ts&&... vs) const {
if constexpr(sizeof...(Ts) == 0) return std::views::empty<std::nullptr_t>;
else return concat_view<std::views::all_t<Ts>...>(std::forward<Ts>(vs)...);
}
};
inline constexpr Concat concat;
}
}
namespace std::ranges {
template<class... Views>
inline constexpr bool enable_borrowed_range<uni::concat_view<Views...>> = (enable_borrowed_range<Views> && ...);
}
namespace uni {
template<class T>
struct numeric_limits : std::numeric_limits<T> {
static constexpr long double FLOAT_EPSILON = 1E-14;
static constexpr T arithmetic_infinity() noexcept(NO_EXCEPT) {
return std::numeric_limits<T>::max() / 2 - 1;
}
static constexpr T arithmetic_negative_infinity() noexcept(NO_EXCEPT) {
return std::numeric_limits<T>::lowest() / 2 + 1;
}
static constexpr T arithmetic_epsilon() noexcept(NO_EXCEPT) {
if constexpr(std::is_floating_point_v<T>) {
return numeric_limits::FLOAT_EPSILON;
}
else {
return 0;
}
}
};
constexpr i32 INF32 = numeric_limits<i32>::arithmetic_infinity();
constexpr i64 INF64 = numeric_limits<i64>::arithmetic_infinity();
template<class T>
constexpr T INF = numeric_limits<T>::arithmetic_infinity();
template<class T>
constexpr T EPSILON = numeric_limits<T>::arithmetic_epsilon();
}
namespace uni {
namespace internal {
template<class T>
consteval auto get_pi() {
if constexpr(std::integral<T>) {
return static_cast<T>(3);
}
else if constexpr(std::same_as<T, float>) {
return M_PIf;
}
else if constexpr(std::same_as<T, double>) {
return M_PI;
}
else if constexpr(std::same_as<T, ld>) {
return M_PIl;
}
else {
static_assert(EXCEPTION_ON_TYPE<T>);
}
}
}
namespace letters {
constexpr std::string_view LOWERCASE = "abcdefghijklmnopqrstuvwxyz";
constexpr std::string_view UPPERCASE = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
}
template<class T = ld>
constexpr auto PI = internal::get_pi<T>();
enum class comparison : std::uint8_t {
equal_to,
not_equal_to,
equals = equal_to,
eq = equal_to,
under,
over,
or_under,
or_over,
less = under,
more = over,
less_than = under,
more_than = over,
not_less_than = or_over,
not_more_than = or_under,
leq = or_under,
geq = or_over
};
enum class interval_notation : std::uint8_t {
right_open,
left_open,
open,
closed,
};
enum class replacement_policy : std::uint8_t {
insert_sync,
overwrite_sync,
overwrite_async
};
enum class rotation : std::int8_t {
clockwise,
counter_clockwise,
anti_clockwise = counter_clockwise,
};
enum class positional_relation : std::int8_t {
clockwise,
counter_clockwise,
anti_clockwise = counter_clockwise,
backward,
forward,
in,
on,
out,
included = in,
inscribed,
intersecting,
circumscribed,
distant,
};
enum class alignment : std::int8_t {
left,
center,
right
};
}
namespace uni {
template<std::ranges::input_range R0, std::ranges::input_range R1>
requires std::constructible_from<
R0, std::common_type_t<std::ranges::range_size_t<R0>,std::ranges::range_size_t<R1>>
>
R0 concat(R0&& r0, R1&& r1) noexcept(NO_EXCEPT) {
R0 res(std::ranges::size(r0) + std::ranges::size(r1));
std::ranges::copy(r0, std::ranges::begin(res));
std::ranges::copy(r1, std::ranges::next(std::ranges::begin(res), std::ranges::size(r0)));
return res;
}
template<std::ranges::input_range R, std::ranges::input_range... Rs>
R concat(R&& range, Rs&&... tails) noexcept(NO_EXCEPT) {
return uni::concat(range, uni::concat(tails...));
}
template<std::ranges::input_range R>
requires
requires(R&& r) {
r.erase(std::ranges::begin((std::ranges::unique(r))),std::ranges::end((std::ranges::unique(r))));
}
inline auto unique(R&& range) noexcept(NO_EXCEPT) {
const auto v = std::ranges::unique(range);
range.erase(std::ranges::begin(v), std::ranges::end(v));
return range;
}
template<
std::input_iterator I,
std::sentinel_for<I> S,
class T = std::iter_value_t<I>
>
T mex(I first, S last, const T& base = T()) noexcept(NO_EXCEPT) {
std::vector<T> val(first, last);
std::ranges::sort(val);
{
auto range = std::ranges::unique(val);
val.erase(std::ranges::begin((range)),std::ranges::end((range)));
}
val.erase(val.begin(), std::ranges::lower_bound(val, base));
T i = 0;
while(i < std::ranges::ssize(val) && val[i] == i + base) ++i;
return T{i} + base;
}
template<std::ranges::input_range R>
auto mex(R&& range, const std::ranges::range_value_t<R>& base = std::ranges::range_value_t<R>()) noexcept(NO_EXCEPT) {
return mex(std::ranges::begin((range)),std::ranges::end((range)), base);
}
template<class T>
auto mex(const std::initializer_list<T> v, const T& base = T()) noexcept(NO_EXCEPT) {
return mex(std::ranges::begin((v)),std::ranges::end((v)), base);
}
template<std::input_iterator I, std::sentinel_for<I> S, class T>
inline constexpr auto gcd(I first, S last) noexcept(NO_EXCEPT) {
T res = T{0};
for(auto itr=first; itr!=last; ++itr) res = std::gcd(res, *itr);
return res;
}
template<std::input_iterator I, std::sentinel_for<I> S, class T>
inline constexpr auto lcm(I first, S last) noexcept(NO_EXCEPT) {
T res = T{1};
for(auto itr=first; itr!=last; ++itr) res = std::lcm(res, *itr);
return res;
}
template<std::ranges::input_range R, class T = std::ranges::range_value_t<R>>
auto mex(R&& range, const T& base) noexcept(NO_EXCEPT) {
return mex(std::ranges::begin((range)),std::ranges::end((range)), base);
}
template<std::ranges::input_range R>
auto gcd(R&& range) noexcept(NO_EXCEPT) {
return gcd(std::ranges::begin((range)),std::ranges::end((range)));
}
template<std::ranges::input_range R>
auto lcm(R&& range) noexcept(NO_EXCEPT) {
return lcm(std::ranges::begin((range)),std::ranges::end((range)));
}
template<class R, std::input_iterator I, std::sentinel_for<I> S, class D>
requires
requires (R r, I itr) {
r.emplace_back(itr, itr);
}
auto split(I first, S last, const D& delim = ' ') noexcept(NO_EXCEPT) {
R res;
for(auto itr=first, fnd=first; ; itr=std::ranges::next(fnd)) {
fnd = std::find(itr, last, delim);
res.emplace_back(itr, fnd);
if(fnd == last) break;
}
return res;
}
template<class R, std::ranges::input_range V, class D>
requires (!std::ranges::input_range<D>)
auto split(V&& v, D&& d) noexcept(NO_EXCEPT) { return split<R>(std::ranges::begin((v)),std::ranges::end((v)), d); }
template<class R, std::ranges::input_range V, std::ranges::input_range Ds>
auto split(V&& v, Ds&& ds) noexcept(NO_EXCEPT) {
R res = { v };
for(const auto &d : (ds)) {
R tmp;
for(const auto &p : (res)) tmp = concat(tmp, split<R>(p, d));
res = std::move(tmp);
}
return res;
}
template<class R, std::ranges::input_range V, class T>
auto split(V&& v, const std::initializer_list<T> ds) noexcept(NO_EXCEPT){
return split<R,V>(v, std::vector<T>(std::ranges::begin((ds)),std::ranges::end((ds))));
}
template<std::ranges::sized_range Source, std::ranges::sized_range Qeury>
auto find(Source&& source, Qeury&& query) noexcept(NO_EXCEPT) {
z_array z_arr(views::concat(query, source));
const auto query_size = std::ranges::ssize(query);
vector<std::ranges::iterator_t<Source>> res;
{
auto itr = std::ranges::begin(source);
for(std::common_type_t<std::remove_cvref_t<decltype(query_size)>,std::remove_cvref_t<decltype(std::ranges::size(z_arr))>> i=(query_size), i$=(std::ranges::size(z_arr)); i<i$; ++i) {
if(z_arr[i] >= query_size) res.push_back(itr);
++itr;
}
}
return res;
}
template<
replacement_policy POLICY,
std::ranges::sized_range R,
std::ranges::sized_range From,
std::ranges::sized_range To
>
auto replaced(R&& source, From&& from, To&& to) noexcept(NO_EXCEPT) {
std::remove_cvref_t<R> res;
if constexpr(POLICY == replacement_policy::insert_sync) {
const auto found = find(source, from);
auto itr = std::ranges::begin(source);
for(auto &fn : (found)) {
std::ranges::copy(itr, fn, std::back_inserter(res));
std::ranges::copy(std::ranges::begin((to)),std::ranges::end((to)), std::back_inserter(res));
itr = std::ranges::next(fn, std::ranges::size(from));
}
std::ranges::copy(itr, std::ranges::end(source), std::back_inserter(res));
}
else {
res = source;
res.resize(std::ranges::size(source) + std::ranges::size(to));
const auto found = find(res, from);
auto prev = std::ranges::begin(res);
for(auto &fn : (found)) {
if constexpr(POLICY == replacement_policy::overwrite_sync) {
if(prev <= fn) prev = std::ranges::copy(to, fn);
}
else {
std::ranges::copy(to, fn);
}
}
res.resize(std::ranges::size(source));
}
return res;
}
template<
std::ranges::sized_range R,
std::ranges::sized_range From,
std::ranges::sized_range To
>
inline auto replaced(R&& source, From&& from, To&& to) noexcept(NO_EXCEPT) {
return replaced<replacement_policy::insert_sync, R, From, To>(std::forward<R>(source), std::forward<From>(from), std::forward<To>(to));
}
template<alignment ALIGNMENT, internal::resizable_range R, class T = std::ranges::range_value_t<R>>
auto align(R&& source, const internal::size_t size, const T& v = T()) noexcept(NO_EXCEPT) {
if(std::ssize(source) >= size) return source;
if(ALIGNMENT == alignment::left) {
R left, right;
left = source;
right.resize(size - std::size(left), v);
return R(std::ranges::begin((uni::views::concat(left, right))),std::ranges::end((uni::views::concat(left, right))));
}
if(ALIGNMENT == alignment::center) {
R left, center, right;
center = source;
left.resize((size - std::size(center)) / 2, v);
right.resize(size - std::size(center) - std::size(left), v);
return R(std::ranges::begin((uni::views::concat(left, center, right))),std::ranges::end((uni::views::concat(left, center, right))));
}
if(ALIGNMENT == alignment::right) {
R left, right;
right = source;
left.resize(size - std::size(right), v);
return R(std::ranges::begin((uni::views::concat(left, right))),std::ranges::end((uni::views::concat(left, right))));
}
assert(false);
}
template<internal::resizable_range R, class T = std::ranges::range_value_t<R>>
auto ljust(R&& source, const internal::size_t size, const T& v = T()) noexcept(NO_EXCEPT) {
return align<alignment::left>(source, size, v);
}
template<internal::resizable_range R, class T = std::ranges::range_value_t<R>>
auto cjust(R&& source, const internal::size_t size, const T& v = T()) noexcept(NO_EXCEPT) {
return align<alignment::center>(source, size, v);
}
template<internal::resizable_range R, class T = std::ranges::range_value_t<R>>
auto rjust(R&& source, const internal::size_t size, const T& v = T()) noexcept(NO_EXCEPT) {
return align<alignment::right>(source, size, v);
}
template<
class Res,
std::ranges::random_access_range Target,
std::ranges::forward_range Order
>
requires std::ranges::output_range<Res, std::ranges::range_value_t<Target>>
Res ordered_by(Target&& target, Order&& order) noexcept(NO_EXCEPT) {
const auto target_size = std::ranges::ssize(target);
const auto order_size = std::ranges::ssize(order);
Res res(order_size);
{
auto res_itr = std::ranges::begin(res);
auto order_itr = std::ranges::begin(order);
const auto order_end = std::ranges::end(std::forward<Order>(order));
for(; order_itr != order_end; ++res_itr, ++order_itr) {
if constexpr(std::signed_integral<std::ranges::range_value_t<Order>>) assert(0 <= *order_itr);
assert(*order_itr < target_size);
*res_itr = target[*order_itr];
}
}
return res;
}
template<
std::ranges::random_access_range Target,
std::ranges::forward_range Order
>
auto ordered_by(Target&& target, Order&& order) noexcept(NO_EXCEPT) {
return ordered_by<std::remove_cvref_t<Target>, Target, Order>(std::forward<Target>(target), std::forward<Order>(order));
}
template<std::ranges::input_range Target, std::ranges::input_range Source>
requires std::equality_comparable_with<std::ranges::range_value_t<Target>, std::ranges::range_value_t<Source>>
auto is_subsequence_of(Target&& target, Source&& source) noexcept(NO_EXCEPT) {
auto target_itr = std::ranges::begin(source);
auto source_itr = std::ranges::begin(source);
const auto target_end = std::ranges::end(source);
const auto source_end = std::ranges::end(source);
for(; source_itr != source_end; ++source_itr) {
if(*target_itr == *source_itr) ++target_itr;
}
return target_itr == target_end;
}
template<std::ranges::input_range Target, std::ranges::input_range Source>
requires std::equality_comparable_with<std::ranges::range_value_t<Target>, std::ranges::range_value_t<Source>>
auto is_continuous_subsequence_of(Target&& target, Source&& source) noexcept(NO_EXCEPT) {
const auto found = find(source, target);
return found.size() > 0;
}
template<std::ranges::bidirectional_range R>
auto is_palindrome(R&& range) noexcept(NO_EXCEPT) {
const auto n = std::ranges::distance(range);
auto fwd = std::ranges::begin(range);
auto rev = std::ranges::rbegin(range);
for(std::remove_cvref_t<decltype(n / 2)> _$0=0, _$0$=(n / 2); _$0<_$0$; ++_$0) {
if(*(fwd++) != *(rev++)) return false;
}
return true;
}
}
namespace uni {
template<class T>
inline constexpr T div_floor(const T& x, const T& d) noexcept(NO_EXCEPT) {
if constexpr(std::is_integral_v<T>) {
return x / d - (x % d && ((x < 0) ^ (d < 0)));
}
else {
return std::floor(x / d);
}
}
template<class T>
inline constexpr T div_ceil(const T& x, const T& d) noexcept(NO_EXCEPT) {
if constexpr(std::is_integral_v<T>) {
return div_floor(x + d - 1, d);
}
else {
return std::ceil(x / d);
}
}
template<class T>
inline constexpr T div_round(const T& x, const T& d) noexcept(NO_EXCEPT) {
if constexpr(std::is_integral_v<T>) {
return div_round<ld>(x, d);
}
else {
return std::round(x / d);
}
}
template<class T>
inline constexpr std::make_signed_t<T> to_signed(const T& x) noexcept(NO_EXCEPT) {
return std::bit_cast<std::make_signed_t<T>>(x);
}
template<class T>
inline constexpr std::make_unsigned_t<T> to_unsigned(const T& x) noexcept(NO_EXCEPT) {
return std::bit_cast<std::make_unsigned_t<T>>(x);
}
namespace internal {
template<class T>
inline constexpr auto perm(const T& n, const T& r) noexcept(NO_EXCEPT) {
T res = 1;
for(std::remove_cvref_t<decltype(r)> i=0, i$=(r); i<i$; ++i) res *= n - i;
return res;
}
template<class T>
inline constexpr auto comb(const T& n, T r) noexcept(NO_EXCEPT) {
if(n < 2 * r) r = n - r;
T p = 1, q = 1;
for(std::remove_cvref_t<decltype(r)> i=0, i$=(r); i<i$; ++i) p *= n - i, q *= r - i;
return p / q;
}
}
template<class T0, std::common_with<T0> T1>
inline constexpr auto perm(const T0& n, const T1& r) noexcept(NO_EXCEPT) {
assert(n >= 0), assert(r >= 0);
using T = std::common_type_t<T0, T1>;
if(n < r) return static_cast<T>(0);
return internal::perm<T>(n, r);
}
template<class T0, std::common_with<T0> T1>
inline constexpr auto comb(const T0& n, const T1& r) noexcept(NO_EXCEPT) {
assert(n >= 0), assert(r >= 0);
using T = std::common_type_t<T0, T1>;
if(n < r) return static_cast<T>(0);
if(n == r) return static_cast<T>(1);
return internal::comb<T>(n, r);
}
template<class T, class U, std::invocable<T, T> F = std::multiplies<>>
constexpr T pow(T x, U n, F mul = F(), T one = static_cast<T>(1)) noexcept(NO_EXCEPT) {
if(n == 0) return one;
if(n == 1 || x == one) return x;
T res = one;
while(true) {
if(n & 1) res = mul(res, x);
x = mul(x, x);
if(n == 0) return res;
n >>= 1;
}
assert(false);
}
using atcoder::pow_mod;
using atcoder::inv_mod;
using atcoder::crt;
template<class T> inline constexpr T sign(const T& x) noexcept(NO_EXCEPT) {
if(x == 0) return 0;
return (x > 0) ? 1 : -1;
}
template<class T, T FROM_MIN, T FROM_MAX, T TO_MIN, T TO_MAX> inline constexpr T mapping(const T x) {
return (x - FROM_MIN) * (TO_MAX - TO_MIN) / (FROM_MAX - FROM_MIN) + TO_MIN;
}
template<class T> inline constexpr T mapping(const T x, const T from_min, const T from_max, const T to_min, const T to_max) {
return (x - from_min) * (to_max - to_min) / (from_max - from_min) + to_min;
}
template<class... Args>
inline constexpr std::common_type_t<Args...> min(const Args&... args) noexcept(NO_EXCEPT) {
return std::min({ static_cast<std::common_type_t<Args...>>(args)... });
}
template<class... Args>
inline constexpr std::common_type_t<Args...> max(const Args&... args) noexcept(NO_EXCEPT) {
return std::max({ static_cast<std::common_type_t<Args...>>(args)... });
}
template<class T>
inline constexpr T gcd(const std::initializer_list<T> args) noexcept(NO_EXCEPT) {
return gcd(std::ranges::begin((args)),std::ranges::end((args)));
}
template<class... Args>
inline constexpr std::common_type_t<Args...> gcd(const Args&... args) noexcept(NO_EXCEPT) {
return gcd({ static_cast<std::common_type_t<Args...>>(args)... });
}
template<class T>
inline constexpr T lcm(const std::initializer_list<T> args) noexcept(NO_EXCEPT) {
return lcm(std::ranges::begin((args)),std::ranges::end((args)));
}
template<class... Args>
inline constexpr std::common_type_t<Args...> lcm(const Args&... args) noexcept(NO_EXCEPT) {
return lcm({ static_cast<std::common_type_t<Args...>>(args)... });
}
template<std::integral T0, std::integral T1>
inline constexpr std::optional<std::common_type_t<T0, T1>> add_overflow(const T0& a, const T1& b) noexcept(NO_EXCEPT) {
std::common_type_t<T0, T1> res;
if(__builtin_add_overflow(a, b, &res)) return {};
return res;
}
template<std::integral T0, std::integral T1>
inline constexpr std::optional<std::common_type_t<T0, T1>> sub_overflow(const T0& a, const T1& b) noexcept(NO_EXCEPT) {
std::common_type_t<T0, T1> res;
if(__builtin_sub_overflow(a, b, &res)) return {};
return res;
}
template<std::integral T0, std::integral T1>
inline constexpr std::optional<std::common_type_t<T0, T1>> mul_overflow(const T0& a, const T1& b) noexcept(NO_EXCEPT) {
std::common_type_t<T0, T1> res;
if(__builtin_mul_overflow(a, b, &res)) return {};
return res;
}
template<std::integral T0, std::integral T1, std::integral Limit>
inline auto add_clamp(const T0 x, const T1 y, const Limit inf, const Limit sup) noexcept(NO_EXCEPT) {
using Common = std::common_type_t<T0, T1, Limit>;
const auto res = add_overflow<Common>(x, y);
if(!res) {
if(x < 0 && y < 0) return inf;
if(x > 0 && y > 0) return sup;
assert(false);
}
return std::clamp<Common>(*res, inf, sup);
}
template<std::integral T0, std::integral T1, std::integral Limit>
inline auto sub_clamp(const T0 x, const T1 y, const Limit inf, const Limit sup) noexcept(NO_EXCEPT) {
using Common = std::common_type_t<T0, T1, Limit>;
const auto res = sub_overflow<Common>(x, y);
if(!res) {
if(x < 0 && y > 0) return inf;
if(x > 0 && y < 0) return sup;
assert(false);
}
return std::clamp<Common>(*res, inf, sup);
}
template<std::integral T0, std::integral T1, std::integral Limit>
inline auto mul_clamp(const T0 x, const T1 y, const Limit inf, const Limit sup) noexcept(NO_EXCEPT) {
using Common = std::common_type_t<T0, T1, Limit>;
const auto res = mul_overflow<Common>(x, y);
if(!res) {
if((x > 0) xor (y > 0)) return inf;
else return sup;
assert(false);
}
return std::clamp<Common>(*res, inf, sup);
}
template<class T>
inline constexpr T sqrt_floor(const T x) noexcept(NO_EXCEPT) {
return static_cast<T>(std::sqrt(static_cast<long double>(x)));
}
template<class T>
inline constexpr T sqrt_ceil(const T x) noexcept(NO_EXCEPT) {
T res = sqrt_floor(x);
if constexpr(std::is_floating_point_v<T>) {
while(res * res < x) res += 1;
}
else {
while(mul_overflow(res, res).value_or(std::numeric_limits<T>::max()) < x) ++res;
}
return res;
}
template<class T, std::integral K>
inline constexpr T kth_root_floor(T x, const K k) noexcept(NO_EXCEPT) {
assert(x >= 0);
if(std::signed_integral<K>) assert(k > 0);
if(x <= 1 or k == 1) return x;
constexpr auto DIGITS = std::numeric_limits<T>::digits;
if(k >= DIGITS) return T{1};
if(k == 2) return sqrt_floor(x);
constexpr auto MAX = std::numeric_limits<T>::max();
if(x == MAX) --x;
auto pow = [&](T t, i64 p) {
if(p == 0) return T{1};
T res = 1;
while(p) {
if(p & 1) {
res = mul_overflow(res, t).value_or(MAX);
}
t = mul_overflow(t, t).value_or(MAX);
p >>= 1;
}
return res;
};
auto res = static_cast<T>(std::pow(x, std::nextafter(1 / static_cast<double>(k), 0)));
while(pow(res + 1, k) <= x) ++res;
return res;
}
template<std::integral T>
T inline constexpr extended_gcd(const T& a, const T& b, T& x, T& y) noexcept {
if(b == 0) {
x = 1;
y = 0;
return a;
}
const T d = extended_gcd(b, a%b, y, x);
y -= a / b * x;
return d;
};
template<std::integral T>
std::pair<T, spair<T>> inline constexpr extended_gcd(const T& a, const T& b) noexcept {
T x, y;
const T d = extended_gcd(a, b, x, y);
return { d, spair<T>{ x, y } };
};
template<std::integral T>
std::optional<spair<T>> inline constexpr bezout_equation(const T& a, const T& b, const T& c) noexcept {
if(a == 0) {
if(b == 0) {
if(c == 0) return spair<T>{ 0, 0 };
else { };
}
if(c % b == 0) return spair<T>{ 0, c / b };
return {};
}
if(b == 0) {
const auto ans = bezout_equation(b, a, c);
if(ans.has_value()) return swapped(ans.value());
return {};
}
T x, y;
const T gcd = extended_gcd(a, b, x, y);
if(c % gcd != 0) return {};
const T p = c / gcd;
return spair<T>{ x * p, y * p };
};
}
namespace uni {
namespace internal {
template<class T> constexpr T plus(const T a, const T b) noexcept(NO_EXCEPT) { return std::plus<T>{}(a, b); }
template<class T> constexpr T minus(const T a, const T b) noexcept(NO_EXCEPT) { return std::minus<T>{}(a, b); }
template<class T> constexpr T bit_xor(const T a, const T b) noexcept(NO_EXCEPT) { return a xor b; }
}
template<class T, class U> inline auto to_optional_if_equal(const T& v, const U& ill) noexcept(NO_EXCEPT) -> std::optional<T> {
return v == ill ? std::optional<T>{} : std::optional<T>(v);
}
template<class T, class U> inline auto to_optional_if_over(const T& v, const U& ill) noexcept(NO_EXCEPT) -> std::optional<T> {
return v > ill ? std::optional<T>{} : std::optional<T>(v);
}
template<class T, class U> inline auto to_optional_if_or_over(const T& v, const U& ill) noexcept(NO_EXCEPT) -> std::optional<T> {
return v >= ill ? std::optional<T>{} : std::optional<T>(v);
}
template<class T, class U> inline auto to_optional_if_under(const T& v, const U& ill) noexcept(NO_EXCEPT) -> std::optional<T> {
return v < ill ? std::optional<T>{} : std::optional<T>(v);
}
template<class T, class U> inline auto to_optional_if_or_under(const T& v, const U& ill) noexcept(NO_EXCEPT) -> std::optional<T> {
return v <= ill ? std::optional<T>{} : std::optional<T>(v);
}
template<class T, class F> inline auto to_optional_if(const T& v, F&& f) noexcept(NO_EXCEPT) -> decltype(f(v), std::optional<T>{}){
return f(v) ? std::optional<T>{} : std::optional<T>(v);
}
template<class T, class U> inline bool chmin(T &a, const U& b) noexcept(NO_EXCEPT) { return (a>b ? a=b, true : false); }
template<class T, class U> inline bool chmax(T &a, const U& b) noexcept(NO_EXCEPT) { return (a<b ? a=b, true : false); }
template<class T, class... Ts> inline bool chmin(T &a, Ts... b) noexcept(NO_EXCEPT) { return chmin(a, min(b...)); }
template<class T, class... Ts> inline bool chmax(T &a, Ts... b) noexcept(NO_EXCEPT) { return chmax(a, max(b...)); }
template<class... Ts>
inline constexpr std::common_type_t<Ts...> tuple_sum(const std::tuple<Ts...>& tuple, const std::common_type_t<Ts...>& base = std::common_type_t<Ts...>()) noexcept(NO_EXCEPT) {
std::common_type_t<Ts...> res = base;
tuple_for_each(tuple, [&](const auto& v) constexpr { res += v; });
return res;
}
template<class... Ts>
inline constexpr std::common_type_t<Ts...> min_element(const std::tuple<Ts...>& tuple) noexcept(NO_EXCEPT) {
return std::apply([&](auto&&... v) constexpr { return min(v...); }, tuple);
}
template<class... Ts>
inline constexpr std::common_type_t<Ts...> max_element(const std::tuple<Ts...>& tuple) noexcept(NO_EXCEPT) {;
return std::apply([&](auto&&... v) constexpr { return max(v...); }, tuple);
}
template<interval_notation INTERVAL, class T0, class T1, class T2>
inline constexpr bool in_range(const T0& x, const T1& l, const T2& r) noexcept(NO_EXCEPT) {
if constexpr(INTERVAL == interval_notation::right_open) return l <= x and x < r;
else if constexpr(INTERVAL == interval_notation::left_open) return l < x and x <= r;
else if constexpr(INTERVAL == interval_notation::open) return l < x and x < r;
return l <= x and x <= r;
}
template<class F, class Tuple>
constexpr void tuple_for_each(F&& f, Tuple&& tuple) {
std::apply(
[&]<class... Ts>(Ts&&... elems) {
(std::invoke(f, std::forward<Ts>(elems)), ...);
},
std::forward<Tuple>(tuple)
);
}
template<class F, class Tuple>
constexpr auto tuple_transform(F&& f, Tuple&& tuple) {
return std::apply(
[&]<class...Ts>(Ts&&... elems) {
return internal::tuple_or_pair_t<std::invoke_result_t<F&,Ts>...>(
std::invoke(f, std::forward<Ts>(elems))...
);
},
std::forward<Tuple>(tuple)
);
}
}
namespace uni {
namespace internal {
template<std::unsigned_integral Value, std::unsigned_integral Large>
requires has_double_digits_of<Large, Value>
struct builtin_reduction {
using value_type = Value;
using large_type = Large;
private:
value_type _mod;
public:
static constexpr int digits = std::numeric_limits<value_type>::digits;
static constexpr value_type max() noexcept { return std::numeric_limits<value_type>::max(); }
inline constexpr value_type mod() const noexcept(NO_EXCEPT) { return this->_mod; }
constexpr builtin_reduction() noexcept = default;
constexpr builtin_reduction(const value_type mod) noexcept(NO_EXCEPT) : _mod(mod) {
assert(0 < mod && mod < builtin_reduction::max());
}
inline constexpr value_type reduce(const large_type v) const noexcept(NO_EXCEPT) { return v % this->_mod; }
inline constexpr value_type add(value_type x, const value_type y) const noexcept(NO_EXCEPT) {
if(x >= this->_mod - y) x -= this->_mod;
x += y;
return x;
}
inline constexpr value_type subtract(value_type x, const value_type y) const noexcept(NO_EXCEPT) {
if(x < y) x += this->_mod;
x -= y;
return x;
}
inline constexpr value_type multiply(const value_type x, const value_type y) const noexcept(NO_EXCEPT) {
return this->reduce(static_cast<large_type>(x) * static_cast<large_type>(y));
}
template<std::integral K>
inline constexpr value_type pow(const value_type v, const K p) const noexcept(NO_EXCEPT) {
if constexpr(std::signed_integral<K>) assert(p >= 0);
if(this->_mod == 0) return 0;
return uni::pow(v, p, [this](const value_type x, const value_type y) { return this->multiply(x, y); });
}
inline constexpr auto compare(const value_type x, const value_type y) const noexcept(NO_EXCEPT) {
return x <=> y;
}
constexpr value_type convert_raw(const value_type v) const noexcept(NO_EXCEPT) { return v; }
template<std::integral T>
constexpr value_type convert(T v) const noexcept(NO_EXCEPT) {
using common_type = std::common_type_t<T, value_type>;
const common_type mod = static_cast<common_type>(this->_mod);
if(std::is_constant_evaluated()) {
v %= mod;
if constexpr(std::signed_integral<T>) {
if(v < 0) v += mod;
}
}
else {
if(v > 0 && static_cast<common_type>(v) >= mod) {
v %= mod;
}
if constexpr(std::signed_integral<T>) {
if(v < 0) {
if(static_cast<common_type>(-v) <= mod) v += mod;
else {
v %= mod;
if(v != 0) v += mod;
}
}
}
}
return static_cast<value_type>(v);
}
constexpr value_type revert(const value_type v) const noexcept(NO_EXCEPT) { return this->_mod == 1 ? 0 : v; }
};
}
using builtin_reduction_32bit = internal::builtin_reduction<u32, u64>;
using builtin_reduction_64bit = internal::builtin_reduction<u64, u128>;
}
namespace uni {
template<std::unsigned_integral T>
constexpr T multiply_high(const T x, const T y) noexcept(NO_EXCEPT) {
constexpr int digits = std::numeric_limits<T>::digits;
if constexpr(digits <= 16) {
return static_cast<T>((static_cast<u32>(x) * static_cast<u32>(y)) >> digits);
}
else if constexpr(digits <= 32) {
return static_cast<T>((static_cast<u64>(x) * static_cast<u64>(y)) >> digits);
}
else if constexpr(digits <= 64) {
return static_cast<T>((static_cast<u128>(x) * static_cast<u128>(y)) >> digits);
}
else {
constexpr int h_digits = digits / 2;
constexpr T mask = (T{ 1 } << h_digits) - 1;
const T xh = x >> h_digits, yh = y >> h_digits;
const T xl = x & mask, yl = y & mask;
const T ph = xh * yh, pl = xl * yl;
return (((pl >> h_digits) + (xh + xl) * (yh + yl) - (ph + pl)) >> h_digits) + ph;
}
}
template<std::unsigned_integral T>
inline constexpr int highest_bit_pos(const T v) noexcept(NO_EXCEPT) {
return (int)std::bit_width(v) - 1;
}
template<std::unsigned_integral T>
inline constexpr int lowest_bit_pos(const T v) noexcept(NO_EXCEPT) {
if(v == 0) return -1;
return std::countr_zero(v);
}
template<std::unsigned_integral T, std::integral I = int>
__attribute__((target("bmi2")))
inline constexpr T clear_higher_bits(const T v, const I p) {
if constexpr(std::signed_integral<I>) assert(0 <= p);
constexpr int DIGITS = std::numeric_limits<T>::digits;
assert(p <= DIGITS);
if constexpr(DIGITS <= 32) return _bzhi_u32(v, static_cast<u32>(p));
if constexpr(DIGITS <= 64) return _bzhi_u64(v, static_cast<u64>(p));
else {
static_assert(DIGITS <= 128);
constexpr std::uint64_t MAX64 = std::numeric_limits<std::uint64_t>::max();
const std::uint64_t high = v >> 64;
const std::uint64_t low = v & MAX64;
if(p < 64) return _bzhi_u64(low, p);
return low | (T{_bzhi_u64(high, p - 64)} << 64);
}
}
template<std::unsigned_integral T, std::integral I = int> constexpr T shiftl(const T, const I = 1);
template<std::unsigned_integral T, std::integral I = int> constexpr T shiftr(const T, const I = 1);
template<std::unsigned_integral T, std::integral I>
constexpr T shiftl(const T x, const I n) {
constexpr int DIGITS = std::numeric_limits<T>::digits;
if constexpr(std::signed_integral<I>) {
if(n < 0) return shiftr(x, -n);
}
if(n >= DIGITS) return 0;
return x << n;
}
template<std::unsigned_integral T, std::integral I>
constexpr T shiftr(const T x, const I n) {
constexpr int DIGITS = std::numeric_limits<T>::digits;
if constexpr(std::signed_integral<I>) {
if(n < 0) return shiftl(x, -n);
}
if(n >= DIGITS) return 0;
return x >> n;
}
template<std::unsigned_integral T, std::integral I = int>
inline constexpr bool bit(const T x, const I p) {
if constexpr(std::signed_integral<I>) assert(0 <= p);
assert(p < std::numeric_limits<T>::digits);
return shiftr(x, p) & T{1};
}
template<std::unsigned_integral T, std::integral I = int>
inline constexpr auto reset_bit(const T x, const I p) {
if constexpr(std::signed_integral<I>) assert(0 <= p);
assert(p < std::numeric_limits<T>::digits);
return x & ~(T{1} << p);
}
template<std::unsigned_integral T, std::integral I = int>
inline constexpr auto set_bit(const T x, const I p, const bool bit = true) {
if constexpr(std::signed_integral<I>) assert(0 <= p);
assert(p < std::numeric_limits<T>::digits);
if(!bit) return reset_bit(x, p);
return x | (T{1} << p);
}
template<std::unsigned_integral T, std::integral I = int>
inline constexpr T lower_bits(const T x, const I digits) {
if constexpr(std::signed_integral<I>) assert(0 <= digits);
assert(digits <= std::numeric_limits<T>::digits);
return x & (uni::shiftl(x, digits) - 1);
}
constexpr int select64(const u64 x0, u32 k) {
const u64 x1 = (x0 & UINT64_C(0x5555555555555555)) + (x0 >> 1 & UINT64_C(0x5555555555555555));
const u64 x2 = (x1 & UINT64_C(0x3333333333333333)) + (x1 >> 2 & UINT64_C(0x3333333333333333));
const u64 x3 = (x2 & UINT64_C(0x0F0F0F0F0F0F0F0F)) + (x2 >> 4 & UINT64_C(0x0F0F0F0F0F0F0F0F));
const u64 x4 = (x3 & UINT64_C(0x00FF00FF00FF00FF)) + (x3 >> 8 & UINT64_C(0x00FF00FF00FF00FF));
const u64 x5 = (x4 & UINT64_C(0x0000FFFF0000FFFF)) + (x4 >> 16 & UINT64_C(0x0000FFFF0000FFFF));
int res = 0;
u32 t;
t = x5 & 0xFFFFFFFF;
if(t <= k) k -= t, res += 32;
t = x4 >> res & 0xFFFF;
if(t <= k) k -= t, res += 16;
t = x3 >> res & 0xFF;
if(t <= k) k -= t, res += 8;
t = x2 >> res & 0xF;
if(t <= k) k -= t, res += 4;
t = x1 >> res & 0x3;
if(t <= k) k -= t, res += 2;
t = x0 >> res & 0x1;
if(t <= k) k -= t, res += 1;
return res;
}
namespace internal {
template<std::unsigned_integral T>
constexpr T binary_gcd(T a, T b) noexcept(NO_EXCEPT) {
if(!a || !b) return a | b;
T t, s = std::countr_zero(a | b);
a >>= std::countr_zero(a);
do {
b >>= std::countr_zero(b);
if(a > b) t = a, a = b, b = t;
b -= a;
} while(b);
return a << s;
}
template<std::signed_integral T>
inline constexpr T binary_gcd(const T a, const T b) noexcept(NO_EXCEPT) {
return binary_gcd(a < 0 ? -a : a, b < 0 ? -b : b);
}
}
template<std::integral T0, std::integral T1>
inline constexpr auto binary_gcd(T0 v0, T1 v1) noexcept(NO_EXCEPT) {
using common_type = std::common_type_t<T0, T1>;
return internal::binary_gcd(static_cast<common_type>(v0), static_cast<common_type>(v1));
}
template<std::unsigned_integral T, std::unsigned_integral S>
inline constexpr bool is_subset_of(T target, S superset) noexcept(NO_EXCEPT) {
return (target & ~superset) == 0;
}
template<std::unsigned_integral T, std::unsigned_integral S>
inline constexpr bool is_superset_of(T target, S subset) noexcept(NO_EXCEPT) {
return (~target & subset) == 0;
}
template<std::unsigned_integral S0, std::unsigned_integral S1>
inline constexpr auto comapre_as_bitset(S0 s0, S1 s1) noexcept(NO_EXCEPT) {
if(s0 == s1) return std::partial_ordering::equivalent;
if(is_subset_of(s0, s1)) return std::partial_ordering::less;
if(is_superset_of(s0, s1)) return std::partial_ordering::greater;
return std::partial_ordering::unordered;
}
}
namespace uni {
namespace internal {
template<std::unsigned_integral Value>
struct binary_reduction {
using value_type = Value;
private:
value_type _mask;
public:
static constexpr int digits = std::numeric_limits<value_type>::digits;
static constexpr value_type max() noexcept { return std::numeric_limits<value_type>::max(); }
inline constexpr value_type mod() const noexcept(NO_EXCEPT) { return this->_mask + 1; }
constexpr binary_reduction() noexcept = default;
constexpr explicit inline binary_reduction(const value_type mod) noexcept(NO_EXCEPT) : _mask(mod - 1) {
assert(std::has_single_bit(mod));
}
inline constexpr value_type reduce(const value_type v) const noexcept(NO_EXCEPT) { return v; }
inline constexpr value_type add(const value_type x, const value_type y) const noexcept(NO_EXCEPT) {
return x + y;
}
inline constexpr value_type subtract(const value_type x, const value_type y) const noexcept(NO_EXCEPT) {
return x - y;
}
inline constexpr value_type multiply(const value_type x, const value_type y) const noexcept(NO_EXCEPT) {
return x * y;
}
template<std::integral K>
inline constexpr value_type pow(const value_type v, const K p) const noexcept(NO_EXCEPT) {
if constexpr(std::signed_integral<K>) assert(p >= 0);
if(this->_mask == 0) return 0;
return uni::pow(v, p);
}
inline constexpr auto compare(const value_type x, const value_type y) const noexcept(NO_EXCEPT) {
return this->revert(x) <=> this->revert(y);
}
constexpr value_type convert_raw(const value_type v) const noexcept(NO_EXCEPT) {
return v;
}
template<std::integral T>
constexpr value_type convert(T v) const noexcept(NO_EXCEPT) {
return static_cast<value_type>(v);
}
constexpr value_type revert(const value_type v) const noexcept(NO_EXCEPT) {
return v & this->_mask;
}
};
}
using binary_reduction_32bit = internal::binary_reduction<u32>;
using binary_reduction_64bit = internal::binary_reduction<u64>;
using binary_reduction_128bit = internal::binary_reduction<u128>;
}
namespace uni {
namespace internal {
template<std::unsigned_integral Value, std::unsigned_integral Large>
requires has_double_digits_of<Large, Value>
struct barrett_reduction {
using value_type = Value;
using large_type = Large;
private:
large_type _mod = 0, _mi;
inline constexpr std::pair<large_type,value_type> _reduce(const large_type v) const noexcept(NO_EXCEPT) {
large_type x = multiply_high(v, this->_mi);
return { x, static_cast<value_type>(v - x * this->_mod) };
}
public:
static constexpr int digits = std::numeric_limits<value_type>::digits - 1;
static constexpr value_type max() noexcept { return (value_type{ 1 } << barrett_reduction::digits) - 1; }
inline constexpr value_type mod() const noexcept(NO_EXCEPT) { return this->_mod; }
constexpr barrett_reduction() noexcept = default;
constexpr explicit inline barrett_reduction(const value_type mod)
: _mod(mod), _mi(std::numeric_limits<large_type>::max() / mod + 1)
{
assert(0 < mod && mod <= barrett_reduction::max());
}
inline constexpr large_type quotient(const large_type v) const noexcept(NO_EXCEPT) {
const auto [ x, r ] = this->_reduce(v);
return static_cast<large_type>(this->_mod <= r ? x - 1 : x);
}
inline constexpr value_type reduce(const large_type v) const noexcept(NO_EXCEPT) {
const auto [ x, r ] = this->_reduce(v);
return static_cast<value_type>(this->_mod <= r ? r + this->_mod : r);
}
inline constexpr std::pair<large_type,value_type> divide(const large_type v) const noexcept(NO_EXCEPT) {
const auto [ x, r ] = this->_reduce(v);
if(this->_mod <= r) return { static_cast<large_type>(x - 1), static_cast<value_type>(r + this->_mod) };
return { static_cast<large_type>(x), static_cast<value_type>(r) };
}
inline constexpr value_type add(value_type x, const value_type y) const noexcept(NO_EXCEPT) {
x += y;
if(x >= this->_mod) x -= this->_mod;
return x;
}
inline constexpr value_type subtract(value_type x, const value_type y) const noexcept(NO_EXCEPT) {
if(x < y) x += this->_mod;
x -= y;
return x;
}
inline constexpr value_type multiply(const value_type x, const value_type y) const noexcept(NO_EXCEPT) {
return this->reduce(static_cast<large_type>(x) * static_cast<large_type>(y));
}
template<std::integral K>
inline constexpr value_type pow(const large_type v, const K p) const noexcept(NO_EXCEPT) {
if constexpr(std::signed_integral<K>) assert(p >= 0);
if(this->_mod == 1) return 0;
return uni::pow(
this->reduce(v), p,
[&](const value_type x, const value_type y) noexcept(NO_EXCEPT) { return this->multiply(x, y); }
);
}
inline constexpr auto compare(const value_type x, const value_type y) const noexcept(NO_EXCEPT) {
return x <=> y;
}
constexpr value_type convert_raw(const value_type v) const noexcept(NO_EXCEPT) { return v; }
template<std::integral T>
constexpr value_type convert(T v) const noexcept(NO_EXCEPT) {
using common_type = std::common_type_t<T, value_type>;
const common_type mod = static_cast<common_type>(this->_mod);
if(v > 0 && static_cast<common_type>(v) >= mod) {
if(static_cast<common_type>(v) <= barrett_reduction::max()) v = this->reduce(v);
else v %= mod;
}
if constexpr(std::signed_integral<T>) {
if(v < 0) {
if(static_cast<common_type>(-v) <= mod) v += mod;
else if(static_cast<common_type>(-v) <= barrett_reduction::max()) {
v = mod - this->reduce(static_cast<value_type>(-v - 1)) - 1;
}
else {
v %= mod;
if(v != 0) v += mod;
}
}
}
return static_cast<value_type>(v);
}
constexpr value_type revert(const value_type v) const noexcept(NO_EXCEPT) { return this->reduce(v); }
};
}
using barrett_reduction_32bit = internal::barrett_reduction<u32, u64>;
using barrett_reduction_64bit = internal::barrett_reduction<u64, u128>;
}
namespace uni {
namespace internal {
template<std::unsigned_integral Value, std::unsigned_integral Large>
requires has_double_digits_of<Large, Value>
struct montgomery_reduction {
using value_type = Value;
using large_type = Large;
private:
value_type _mod = 0, _r2, _mp;
constexpr value_type _inv() const noexcept(NO_EXCEPT) {
value_type res = this->_mod;
while(this->_mod * res != 1) res *= value_type{ 2 } - this->_mod * res;
return res;
}
public:
static constexpr int digits = std::numeric_limits<value_type>::digits - 2;
static constexpr value_type max() noexcept { return (value_type{ 1 } << montgomery_reduction::digits) - 1; }
inline constexpr value_type mod() const noexcept(NO_EXCEPT) { return this->_mod; }
value_type zero = 0;
value_type one;
constexpr montgomery_reduction() noexcept = default;
constexpr montgomery_reduction(const value_type mod) noexcept(NO_EXCEPT)
: _mod(mod), _r2(static_cast<value_type>(-static_cast<large_type>(mod) % mod)),
_mp(-this->_inv()), one(this->reduce(this->_r2))
{
assert((mod & 1) == 1);
assert(mod <= montgomery_reduction::max());
}
constexpr value_type reduce(const large_type v) const noexcept(NO_EXCEPT) {
return
static_cast<value_type>(
(
v + static_cast<large_type>(static_cast<value_type>(v) * this->_mp) * this->_mod
) >> std::numeric_limits<value_type>::digits
);
}
inline constexpr value_type add(value_type x, const value_type y) const noexcept(NO_EXCEPT) {
x += y;
if(x >= (this->_mod << 1)) x -= (this->_mod << 1);
return x;
}
inline constexpr value_type subtract(value_type x, const value_type y) const noexcept(NO_EXCEPT) {
if(x < y) x += (this->_mod << 1);
x -= y;
return x;
}
inline constexpr value_type multiply(const value_type x, const value_type y) const noexcept(NO_EXCEPT) {
return this->reduce(static_cast<large_type>(x) * static_cast<large_type>(y));
}
template<std::integral K>
inline constexpr value_type pow(const large_type v, const K p) const noexcept(NO_EXCEPT) {
if constexpr(std::signed_integral<K>) assert(p >= 0);
if(this->_mod == 1) return 0;
return uni::pow(
v, p,
[&](const value_type x, const value_type y) noexcept(NO_EXCEPT) { return this->multiply(x, y); },
static_cast<large_type>(this->one)
);
}
inline constexpr value_type normalize(const value_type v) const noexcept(NO_EXCEPT) {
assert(0 <= v && v < (this->_mod << 1));
if(v < this->_mod) return v;
return v - this->_mod;
}
inline constexpr auto compare(const value_type x, const value_type y) const noexcept(NO_EXCEPT) {
return this->normalize(x) <=> this->normalize(y);
}
inline constexpr value_type convert_raw(const value_type v) const noexcept(NO_EXCEPT) {
if(v == 1) return this->one;
return this->multiply(v, this->_r2);
}
template<std::integral T>
constexpr value_type convert(T v) const noexcept(NO_EXCEPT) {
if(v == 1) return this->one;
using common_type = std::common_type_t<T, value_type>;
const common_type mod2 = static_cast<common_type>(this->_mod << 1);
if(v > 0 && static_cast<common_type>(v) >= mod2) {
v %= mod2;
}
if constexpr(std::is_signed_v<T>) {
if(v < 0 && static_cast<common_type>(-v) >= mod2) {
v %= mod2;
if(v != 0) v += mod2;
}
}
return this->multiply(v, this->_r2);
}
constexpr value_type revert(const value_type v) const noexcept(NO_EXCEPT) {
return this->normalize(this->reduce(v));
}
};
template<std::unsigned_integral Value, std::unsigned_integral Large>
requires has_double_digits_of<Large, Value>
struct arbitrary_montgomery_reduction {
using value_type = Value;
using large_type = Large;
private:
using context = arbitrary_montgomery_reduction;
static constexpr int width = std::numeric_limits<value_type>::digits;
value_type _mod = 0;
int _tz;
value_type _m0;
large_type _m0i, _mask;
value_type _r2;
constexpr large_type _inv() const noexcept(NO_EXCEPT) {
large_type res = this->_m0;
while(((this->_m0 * res) & this->_mask) != 1) res *= large_type{ 2 } - this->_m0 * res;
return res & this->_mask;
}
constexpr value_type _m0ip() const noexcept(NO_EXCEPT) {
if(this->_tz == 0) return 0;
value_type res = this->_m0;
const value_type mask = (value_type{ 1 } << this->_tz) - 1;
while(((this->_m0 * res) & mask) != 1) res *= value_type{ 2 } - this->_m0 * res;
return res & mask;
}
public:
static constexpr int digits = std::numeric_limits<value_type>::digits - 2;
static constexpr value_type max() noexcept { return (value_type{ 1 } << context::digits) - 1; }
inline constexpr value_type mod() const noexcept(NO_EXCEPT) { return this->_mod; }
value_type one;
constexpr arbitrary_montgomery_reduction() noexcept = default;
constexpr arbitrary_montgomery_reduction(value_type m) noexcept(NO_EXCEPT) {
assert(0 < m);
if(this->_mod == m) return;
this->_mod = m;
this->_tz = std::countr_zero(m);
this->_m0 = m >> this->_tz;
assert(this->_mod < context::max());
this->_mask = (large_type{ 1 } << (context::width + this->_tz)) - 1;
this->_m0i = this->_inv();
{
const value_type x = (std::numeric_limits<large_type>::max() % this->_m0) + 1;
const value_type mask = (value_type{ 1 } << this->_tz) - 1;
this->_r2 = (x + ((((large_type{ 1 } - x) * this->_m0ip()) & mask) * this->_m0));
}
this->one = this->reduce(this->_r2);
}
constexpr value_type reduce(const large_type v) const noexcept(NO_EXCEPT) {
const value_type res =
static_cast<value_type>(
(
v +
this->_m0 *
((((v << std::numeric_limits<value_type>::digits) - v) * this->_m0i) & this->_mask)
) >> std::numeric_limits<value_type>::digits
);
return res;
}
inline constexpr value_type add(value_type x, const value_type y) const noexcept(NO_EXCEPT) {
x += y;
if(x >= (this->_mod << 1)) x -= (this->_mod << 1);
return x;
}
inline constexpr value_type subtract(value_type x, const value_type y) const noexcept(NO_EXCEPT) {
if(x < y) x += (this->_mod << 1);
x -= y;
return x;
}
inline constexpr value_type multiply(const value_type x, const value_type y) const noexcept(NO_EXCEPT) {
return this->reduce(static_cast<large_type>(x) * static_cast<large_type>(y));
}
template<std::integral K>
inline constexpr value_type pow(const large_type v, K p) const noexcept(NO_EXCEPT) {
if constexpr(std::signed_integral<K>) assert(p >= 0);
if(this->_mod == 1) return 0;
return uni::pow(
v, p,
[&](const value_type x, const value_type y) noexcept(NO_EXCEPT) { return this->multiply(x, y); },
static_cast<large_type>(this->one)
);
}
inline constexpr value_type normalize(const value_type v) const noexcept(NO_EXCEPT) {
assert(0 <= v && v < (this->_mod << 1));
if(v < this->_mod) return v;
return v - this->_mod;
}
inline constexpr auto compare(const large_type x, const large_type y) const noexcept(NO_EXCEPT) {
return this->normalize(x) <=> this->normalize(y);
}
inline constexpr value_type convert_raw(const value_type v) const noexcept(NO_EXCEPT) {
if(v == 1) return this->one;
return this->multiply(v, this->_r2);
}
template<std::integral T>
constexpr value_type convert(T v) const noexcept(NO_EXCEPT) {
if(v == 1) return this->one;
using common_type = std::common_type_t<T, value_type>;
const common_type mod2 = static_cast<common_type>(this->_mod << 1);
if(v > 0 && static_cast<common_type>(v) >= mod2) {
v %= mod2;
}
if constexpr(std::signed_integral<T>) {
if(v < 0) {
if(static_cast<common_type>(-v) >= mod2) v %= mod2;
if(v < 0) v += mod2;
}
}
return this->multiply(v, this->_r2);
}
constexpr value_type revert(const value_type v) const noexcept(NO_EXCEPT) {
return this->normalize(this->reduce(v));
}
};
}
using montgomery_reduction_32bit = internal::montgomery_reduction<u32, u64>;
using montgomery_reduction_64bit = internal::montgomery_reduction<u64, u128>;
using arbitrary_montgomery_reduction_32bit = internal::arbitrary_montgomery_reduction<u32, u64>;
using arbitrary_montgomery_reduction_64bit = internal::arbitrary_montgomery_reduction<u64, u128>;
}
namespace uni {
namespace internal {
template<class T>
concept modint_family =
numeric<T> &&
has_static_one<T> && has_static_zero<T> &&
requires (T v, i64 p, typename T::value_type x) {
{ v.pow(p) } -> std::same_as<T>;
{ v.inv() } -> std::same_as<T>;
{ T::raw(x) } -> std::same_as<T>;
{ v.val() } -> std::same_as<typename T::value_type>;
{ T::mod() } -> std::same_as<typename T::value_type>;
{ T::max() } -> std::same_as<typename T::value_type>;
T::digits;
T::context::dynamic;
};
template<class T>
concept dynamic_modint_family =
modint_family<T> &&
T::context::dynamic &&
requires (typename T::value_type v) {
T::set_mod(v);
};
template<class T>
concept static_modint_family =
modint_family<T> &&
(!T::context::dynamic);
template<class T>
concept modular_reduction =
std::default_initializable<T> &&
std::constructible_from<T, typename T::value_type> &&
requires (T v, typename T::value_type x, i64 p) {
typename T::value_type;
T::digits;
{ T::max() } -> std::same_as<typename T::value_type>;
{ v.mod() } -> std::same_as<typename T::value_type>;
{ v.reduce(x) } -> std::same_as<typename T::value_type>;
{ v.add(x, x) } -> std::same_as<typename T::value_type>;
{ v.subtract(x, x) } -> std::same_as<typename T::value_type>;
{ v.multiply(x, x) } -> std::same_as<typename T::value_type>;
{ v.multiply(x, x) } -> std::same_as<typename T::value_type>;
{ v.pow(x, p) } -> std::same_as<typename T::value_type>;
{ v.convert_raw(x) } -> std::same_as<typename T::value_type>;
{ v.convert(x) } -> std::same_as<typename T::value_type>;
{ v.revert(x) } -> std::same_as<typename T::value_type>;
v.compare(x, x);
};
template<class T>
concept modular_context =
requires {
typename T::reductor;
typename T::value_type;
T::reduction;
};
}
template<internal::modular_reduction Reduction, typename Reduction::value_type Mod>
struct static_modular_context {
using reductor = Reduction;
using value_type = typename reductor::value_type;
static constexpr bool dynamic = false;
static constexpr reductor reduction = reductor(Mod);
private:
using context = static_modular_context;
};
template<internal::modular_reduction Reduction, i64 Id>
struct dynamic_modular_context {
using reductor = Reduction;
using value_type = typename reductor::value_type;
static constexpr bool dynamic = true;
static inline reductor reduction;
private:
using context = dynamic_modular_context;
public:
static constexpr void set_mod(const value_type mod) noexcept(NO_EXCEPT) { context::reduction = reductor(mod); }
};
template<internal::modular_context> struct modint;
template<u32 Mod> using static_builtin_modular_context_32bit = static_modular_context<builtin_reduction_32bit, Mod>;
template<u64 Mod> using static_builtin_modular_context_64bit = static_modular_context<builtin_reduction_64bit, Mod>;
template<u32 Mod> using static_barrett_modular_context_32bit = static_modular_context<barrett_reduction_32bit, Mod>;
template<u64 Mod> using static_barrett_modular_context_64bit = static_modular_context<barrett_reduction_64bit, Mod>;
template<u32 Mod> using static_montgomery_modular_context_32bit = static_modular_context<montgomery_reduction_32bit, Mod>;
template<u64 Mod> using static_montgomery_modular_context_64bit = static_modular_context<montgomery_reduction_64bit, Mod>;
template<u32 Mod> using static_arbitrary_montgomery_modular_context_32bit = static_modular_context<arbitrary_montgomery_reduction_32bit, Mod>;
template<u64 Mod> using static_arbitrary_montgomery_modular_context_64bit = static_modular_context<arbitrary_montgomery_reduction_64bit, Mod>;
template<u32 Mod> using static_binary_modular_context_32bit = static_modular_context<binary_reduction_32bit, Mod>;
template<u64 Mod> using static_binary_modular_context_64bit = static_modular_context<binary_reduction_64bit, Mod>;
template<u128 Mod> using static_binary_modular_context_128bit = static_modular_context<binary_reduction_128bit, Mod>;
template<u32 Mod> using static_builtin_modint_32bit = modint<static_builtin_modular_context_32bit<Mod>>;
template<u64 Mod> using static_builtin_modint_64bit = modint<static_builtin_modular_context_64bit<Mod>>;
template<u32 Mod> using static_barrett_modint_32bit = modint<static_barrett_modular_context_32bit<Mod>>;
template<u64 Mod> using static_barrett_modint_64bit = modint<static_barrett_modular_context_64bit<Mod>>;
template<u32 Mod> using static_montgomery_modint_32bit = modint<static_montgomery_modular_context_32bit<Mod>>;
template<u64 Mod> using static_montgomery_modint_64bit = modint<static_montgomery_modular_context_64bit<Mod>>;
template<u32 Mod> using static_arbitrary_montgomery_modint_32bit = modint<static_arbitrary_montgomery_modular_context_32bit<Mod>>;
template<u64 Mod> using static_arbitrary_montgomery_modint_64bit = modint<static_arbitrary_montgomery_modular_context_64bit<Mod>>;
template<u32 Mod> using static_binary_modint_32bit = modint<static_binary_modular_context_32bit<Mod>>;
template<u64 Mod> using static_binary_modint_64bit = modint<static_binary_modular_context_64bit<Mod>>;
template<u128 Mod> using static_binary_modint_128bit = modint<static_binary_modular_context_128bit<Mod>>;
template<i64 Id> using dynamic_builtin_modular_context_32bit = dynamic_modular_context<builtin_reduction_32bit, Id>;
template<i64 Id> using dynamic_builtin_modular_context_64bit = dynamic_modular_context<builtin_reduction_64bit, Id>;
template<i64 Id> using dynamic_barrett_modular_context_32bit = dynamic_modular_context<barrett_reduction_32bit, Id>;
template<i64 Id> using dynamic_barrett_modular_context_64bit = dynamic_modular_context<barrett_reduction_64bit, Id>;
template<i64 Id> using dynamic_montgomery_modular_context_32bit = dynamic_modular_context<montgomery_reduction_32bit, Id>;
template<i64 Id> using dynamic_montgomery_modular_context_64bit = dynamic_modular_context<montgomery_reduction_64bit, Id>;
template<i64 Id> using dynamic_arbitrary_montgomery_modular_context_32bit = dynamic_modular_context<arbitrary_montgomery_reduction_32bit, Id>;
template<i64 Id> using dynamic_arbitrary_montgomery_modular_context_64bit = dynamic_modular_context<arbitrary_montgomery_reduction_64bit, Id>;
template<i64 Id> using dynamic_binary_modular_context_32bit = dynamic_modular_context<binary_reduction_32bit, Id>;
template<i64 Id> using dynamic_binary_modular_context_64bit = dynamic_modular_context<binary_reduction_64bit, Id>;
template<i64 Id> using dynamic_binary_modular_context_128bit = dynamic_modular_context<binary_reduction_128bit, Id>;
template<i64 Id> using dynamic_builtin_modint_32bit = modint<dynamic_builtin_modular_context_32bit<Id>>;
template<i64 Id> using dynamic_builtin_modint_64bit = modint<dynamic_builtin_modular_context_64bit<Id>>;
template<i64 Id> using dynamic_barrett_modint_32bit = modint<dynamic_barrett_modular_context_32bit<Id>>;
template<i64 Id> using dynamic_barrett_modint_64bit = modint<dynamic_barrett_modular_context_64bit<Id>>;
template<i64 Id> using dynamic_montgomery_modint_32bit = modint<dynamic_montgomery_modular_context_32bit<Id>>;
template<i64 Id> using dynamic_montgomery_modint_64bit = modint<dynamic_montgomery_modular_context_64bit<Id>>;
template<i64 Id> using dynamic_arbitrary_montgomery_modint_32bit = modint<dynamic_arbitrary_montgomery_modular_context_32bit<Id>>;
template<i64 Id> using dynamic_arbitrary_montgomery_modint_64bit = modint<dynamic_arbitrary_montgomery_modular_context_64bit<Id>>;
template<i64 Id> using dynamic_binary_modint_32bit = modint<dynamic_binary_modular_context_32bit<Id>>;
template<i64 Id> using dynamic_binary_modint_64bit = modint<dynamic_binary_modular_context_64bit<Id>>;
template<i64 Id> using dynamic_binary_modint_128bit = modint<dynamic_binary_modular_context_128bit<Id>>;
template<u32 Mod> using static_modint_32bit = static_builtin_modint_32bit<Mod>;
template<u64 Mod> using static_modint_64bit = static_builtin_modint_64bit<Mod>;
using modint998244353 = static_modint_32bit<998244353>;
using modint1000000007 = static_modint_32bit<1000000007>;
using modint_32 = dynamic_barrett_modint_32bit<-1>;
using modint_64 = dynamic_barrett_modint_64bit<-1>;
template<const unsigned Val, const unsigned Mod = 998244353>
const uni::static_modint_32bit<Mod> MINT = Val;
template<const unsigned Val, const unsigned Mod = 998244353>
const unsigned INV = uni::static_modint_32bit<Mod>{ Val }.inv().val();
template<const unsigned Val, const unsigned Mod = 998244353>
const int SINV = uni::static_modint_32bit<Mod>{ Val }.inv().val();
}
namespace uni {
template<std::derived_from<std::ios_base> Source = std::istream>
struct input_adaptor {
using source_type = Source;
private:
template<class T>
requires std::derived_from<T, std::valarray<typename T::value_type>>
auto _set(uni::internal::resolving_rank<6>, T& val) noexcept(NO_EXCEPT) -> int {
this->operator()(std::ranges::begin((val)),std::ranges::end((val)));
return 0;
}
template<class T>
requires
requires (source_type& in, T& val) {
in >> val;
}
int _set(uni::internal::resolving_rank<5>, T& val) noexcept(NO_EXCEPT) {
*this->in >> val;
return 0;
}
template<std::ranges::range T>
int _set(uni::internal::resolving_rank<4>, T& val) noexcept(NO_EXCEPT) {
this->operator()(std::ranges::begin(val), std::ranges::end(val));
return 0;
}
template<class T>
requires
requires (T& val) {
val.first;
val.second;
}
int _set(uni::internal::resolving_rank<3>, T& val) noexcept(NO_EXCEPT) {
*this >> val.first >> val.second;
return 0;
}
template<class T>
requires
requires (T& val) {
std::get<0>(val);
}
int _set(uni::internal::resolving_rank<2>, T& val) noexcept(NO_EXCEPT) {
tuple_for_each([this](auto&& v) { *this >> v; }, val);
return 0;
}
template<uni::internal::modint_family T>
int _set(uni::internal::resolving_rank<1>, T& val) noexcept(NO_EXCEPT) {
std::int64_t v; std::cin >> v;
val = { v };
return 0;
}
template<class T>
requires
requires {
typename T::value_type;
}
int _set(uni::internal::resolving_rank<0>, T& val) noexcept(NO_EXCEPT) {
typename T::value_type v; *this >> v;
val = { v };
return 0;
}
protected:
template<class T>
source_type *set(T& val) noexcept(NO_EXCEPT) {
this->_set(uni::internal::resolving_rank<10>{}, val);
return this->in;
}
template<class T>
source_type *set(T&& _val) noexcept(NO_EXCEPT) {
T val = _val;
this->_set(uni::internal::resolving_rank<10>{}, val);
return this->in;
}
public:
using char_type = typename source_type::char_type;
source_type *in;
input_adaptor(source_type *_in = &std::cin) noexcept(NO_EXCEPT) : in(_in) {}
template<class T>
inline input_adaptor& operator>>(T&& s) noexcept(NO_EXCEPT) {
this->set(std::forward<T>(s));
return *this;
}
template<class T>
inline T one() noexcept(NO_EXCEPT) {
T val; *this >> val;
return val;
}
template<class T>
inline auto& operator()(T& val) noexcept(NO_EXCEPT) {
*this >> val;
return *this;
}
template<class T, class... Args>
inline auto& operator()(T& head, Args&... tail) noexcept(NO_EXCEPT) {
*this >> head;
this->operator()(tail...);
return *this;
}
template<std::input_or_output_iterator I, std::sentinel_for<I> S>
inline auto& operator()(I first, S last) noexcept(NO_EXCEPT) {
for(I itr=first; itr!=last; ++itr) *this >> *itr;
return *this;
}
explicit operator bool() const noexcept(NO_EXCEPT) { return (bool)*this->in; }
};
}
namespace uni {
template<class Destination = std::ostream>
struct output_adaptor {
using destination_type = Destination;
private:
template<class T>
requires
requires (destination_type& out, T val) {
out << val;
}
int _put(uni::internal::resolving_rank<5>, T&& val) noexcept(NO_EXCEPT) {
*this->out << std::forward<T>(val);
return 0;
}
template<class T>
requires
requires (T&& val) {
val.val();
}
int _put(uni::internal::resolving_rank<4>, T&& val) noexcept(NO_EXCEPT) {
this->put(val.val());
return 0;
}
template<std::ranges::input_range T>
int _put(uni::internal::resolving_rank<3>, T&& val) noexcept(NO_EXCEPT) {
(*this)(std::ranges::begin(val), std::ranges::end(val), false);
return 0;
}
template<class T>
requires
requires (T&& val) {
val.first;
val.second;
}
int _put(uni::internal::resolving_rank<2>, T&& val) noexcept(NO_EXCEPT) {
*this << val.first, this->put_separator();
*this << val.second;
return 0;
}
template<class T>
requires
requires (T&& val) {
std::get<0>(val);
}
auto _put(uni::internal::resolving_rank<1>, T&& val) noexcept(NO_EXCEPT) {
std::apply([this](const auto&... args) constexpr { ((*this << args, this->put_separator()), ...); }, std::forward<T>(val));
return 0;
}
template<std::input_or_output_iterator T>
int _put(uni::internal::resolving_rank<0>, T&& val) noexcept(NO_EXCEPT) {
(*this)(*std::forward<T>(val));
return 0;
}
protected:
template<class T>
destination_type* put(T&& val) noexcept(NO_EXCEPT){
this->_put(uni::internal::resolving_rank<10>{}, std::forward<T>(val));
return this->out;
}
public:
using char_type = typename destination_type::char_type;
static constexpr auto sendl = std::endl<char_type,std::char_traits<char_type>>;
static constexpr auto sflush = std::flush<char_type,std::char_traits<char_type>>;
protected:
using sfunc_type = std::remove_const_t<decltype(output_adaptor::sendl)>;
public:
using separator_type = std::variant<std::string,sfunc_type>;
destination_type *out;
separator_type endline;
separator_type separator;
protected:
void put_separator() noexcept(NO_EXCEPT) {
if(this->separator.index() == 0) *this->out << std::get<std::string>(this->separator);
if(this->separator.index() == 1) *this->out << std::get<sfunc_type>(this->separator);
}
void put_endline() noexcept(NO_EXCEPT) {
if(this->endline.index() == 0) *this->out << std::get<std::string>(this->endline);
if(this->endline.index() == 1) *this->out << std::get<sfunc_type>(this->endline);
}
public:
template<class Terminator = std::string, class Separator = std::string>
output_adaptor(destination_type *des = &std::cout, Terminator endl = "\n", Separator sep = " ") noexcept(NO_EXCEPT)
: out(des), endline(endl), separator(sep)
{
*this << std::fixed << std::setprecision(20);
}
inline auto& seekp(const typename destination_type::off_type off, const std::ios_base::seekdir dir = std::ios_base::cur) noexcept(NO_EXCEPT) {
this->out->seekp(off, dir); return *this;
};
template<class T> inline output_adaptor& operator<<(T&& s) noexcept(NO_EXCEPT){
this->put(std::forward<T>(s));
return *this;
}
template<class T = std::string>
inline auto& operator()(T&& val = "") noexcept(NO_EXCEPT){
*this << std::forward<T>(val), this->put_endline();
return *this;
}
template<class T, class ...Args>
inline auto& operator()(T&& head, Args&& ...tail) noexcept(NO_EXCEPT){
*this << std::forward<T>(head), this->put_separator();
(*this)(std::forward<Args>(tail)...);
return *this;
}
template<std::forward_iterator I, std::sentinel_for<I> S>
inline auto& operator()(I first, S last, const bool terminate = true) noexcept(NO_EXCEPT) {
for(I itr=first; itr!=last;) {
*this << *itr;
if(++itr == last) {
if(terminate) this->put_endline();
}
else this->put_separator();
}
return *this;
}
template<class T>
inline auto& operator()(const std::initializer_list<T> vals) noexcept(NO_EXCEPT) {
std::vector wrapped(vals.begin(), vals.end());
(*this)(wrapped.begin(), wrapped.end());
return *this;
}
template<class T0, class T1>
inline auto& conditional(const bool cond, const T0& a, const T1& b) noexcept(NO_EXCEPT) {
if(cond) (*this)(a);
else (*this)(b);
return *this;
}
inline auto& yesno(const bool cond) noexcept(NO_EXCEPT) {
if(cond) this->yes();
else this->no();
return *this;
}
inline auto yes() noexcept(NO_EXCEPT) {
*this->out << "Yes";
this->put_endline();
return *this;
}
inline auto no() noexcept(NO_EXCEPT) {
*this->out << "No";
this->put_endline();
return *this;
}
inline auto flush() noexcept(NO_EXCEPT) {
*this->out << std::flush;
return *this;
}
};
}
namespace uni {
uni::input_adaptor _input;
uni::output_adaptor _print;
}
namespace uni {
namespace internal {
template<class Set>
struct set_wrapper : Set {
using Set::Set;
using value_type = typename Set::value_type;
using size_type = internal::size_t;
template<class Key>
auto remove(Key&& key) noexcept(NO_EXCEPT) { return this->extract(std::forward<Key>(key)); }
inline auto ssize() const noexcept(NO_EXCEPT) { return std::ranges::ssize(*this); }
inline auto min_element() const noexcept(NO_EXCEPT) { return this->begin(); }
inline auto max_element() const noexcept(NO_EXCEPT) { return std::ranges::prev(this->end()); }
inline auto min() const noexcept(NO_EXCEPT) { return *this->begin(); }
inline auto max() const noexcept(NO_EXCEPT) { return *std::ranges::prev(this->end()); }
inline auto& pop_min() noexcept(NO_EXCEPT) { this->erase(this->begin()); return *this; }
inline auto& pop_max() noexcept(NO_EXCEPT) { this->erase(std::ranges::prev(this->end())); return *this; }
inline auto kth_smallest_element(const size_type k) const noexcept(NO_EXCEPT) {
return std::ranges::next(this->begin(), k);
}
inline auto kth_largest_element(const size_type k) const noexcept(NO_EXCEPT) {
return std::ranges::prev(this->end(), k + 1);
}
inline auto kth_smallest(const size_type k) const noexcept(NO_EXCEPT) {
return *std::ranges::next(this->begin(), k);
}
inline auto kth_largest(const size_type k) const noexcept(NO_EXCEPT) {
return *std::ranges::prev(this->end(), k + 1);
}
inline auto& pop_kth_smallest(const size_type k) const noexcept(NO_EXCEPT) {
return this->erase(std::ranges::next(this->begin(), k));
return *this;
}
inline auto& pop_kth_largest(const size_type k) const noexcept(NO_EXCEPT) {
return this->erase(std::ranges::prev(this->end(), k + 1));
return *this;
}
auto next_element(const typename Set::key_type& key, const size_type _count = 0) const noexcept(NO_EXCEPT) {
size_type count = std::abs(_count);
auto itr = this->lower_bound(key);
const auto begin = this->begin(), end = this->end();
if(itr == end) return this->end();
if(itr == begin) return this->begin();
while(count--) {
if(_count < 0) if(itr-- == begin) return this->begin();
if(_count > 0) if(++itr == end) return this->end();
}
return itr;
}
auto prev_element(const typename Set::key_type& key, const size_type _count = 0) const noexcept(NO_EXCEPT) {
size_type count = std::abs(_count);
auto itr = this->upper_bound(key);
const auto begin = this->begin(), end = this->end();
if(itr == end) return this->end();
if(itr-- == begin) return this->begin();
while(count--) {
if(_count < 0) if(itr-- == begin) return this->begin();
if(_count > 0) if(++itr == end) return this->end();
}
return itr;
}
std::optional<typename Set::value_type> next(const typename Set::key_type& key, size_type count = 0) const noexcept(NO_EXCEPT) {
if(this->empty()) return {};
auto itr = this->lower_bound(key);
const auto end = this->end();
if(itr == end) return {};
while(count--) if(++itr == end) return {};
return { *itr };
}
std::optional<typename Set::value_type> prev(const typename Set::key_type& key, size_type count = 0) const noexcept(NO_EXCEPT) {
if(this->empty()) return {};
auto itr = this->upper_bound(key);
const auto begin = this->begin();
if(itr-- == begin) return {};
while(count--) if(itr-- == begin) return {};
return { *itr };
}
template<class Rhs>
inline set_wrapper& operator|=(Rhs&& rhs) noexcept(NO_EXCEPT) {
set_wrapper res;
std::ranges::set_union(*this, std::forward<Rhs>(rhs), std::inserter(res, res.end()));
this->swap(res);
return *this;
}
template<class Rhs>
inline set_wrapper& operator&=(Rhs&& rhs) noexcept(NO_EXCEPT) {
set_wrapper res;
std::ranges::set_intersection(*this, std::forward<Rhs>(rhs), std::inserter(res, res.end()));
this->swap(res);
return *this;
}
template<class Rhs>
inline set_wrapper& operator^=(Rhs&& rhs) noexcept(NO_EXCEPT) {
set_wrapper res;
std::ranges::set_symmetric_difference(*this, std::forward<Rhs>(rhs), std::inserter(res, res.end()));
this->swap(res);
return *this;
}
template<class... Args>
inline set_wrapper operator|(set_wrapper<Args...> rhs) noexcept(NO_EXCEPT) {
return rhs |= *this;
}
template<class... Args>
inline set_wrapper operator&(set_wrapper<Args...> rhs) noexcept(NO_EXCEPT) {
return rhs &= *this;
}
template<class... Args>
inline set_wrapper operator^(set_wrapper<Args...> rhs) noexcept(NO_EXCEPT) {
return rhs ^= *this;
}
template<class... Args>
inline auto operator<=>(const set_wrapper<Args...>& rhs) const noexcept(NO_EXCEPT) {
const bool leq = this->size() <= rhs.size() && std::ranges::includes(rhs, *this);
const bool geq = rhs.size() <= this->size() && std::ranges::includes(*this, rhs);
if(leq) {
if(geq) return std::partial_ordering::equivalent;
return std::partial_ordering::less;
}
if(geq) return std::partial_ordering::greater;
return std::partial_ordering::unordered;
}
};
}
template<class... Args> using set = internal::set_wrapper<std::set<Args...>>;
template<class... Args> using unordered_set = internal::set_wrapper<std::unordered_set<Args...>>;
template<class... Args> using multiset = internal::set_wrapper<std::multiset<Args...>>;
template<class... Args> using unordered_multiset = internal::set_wrapper<std::unordered_multiset<Args...>>;
}
namespace uni {
namespace internal {
template<class Map>
using map_wrapper_base = set_wrapper<Map>;
template<class Map> struct map_wrapper : map_wrapper_base<Map> {
private:
using base = map_wrapper_base<Map>;
public:
using base::base;
using mapped_type = typename base::mapped_type;
using key_type = typename base::key_type;
protected:
using default_func_noarg_type = std::function<mapped_type(void)>;
using default_func_type = std::function<mapped_type(key_type)>;
int _default_type = 0;
mapped_type _default_val = mapped_type();
default_func_noarg_type _default_func_noarg;
default_func_type _default_func;
inline mapped_type _get_default(const key_type& key) const noexcept(NO_EXCEPT) {
if(this->_default_type == 0) return this->_default_val;
if(this->_default_type == 1) return this->_default_func_noarg();
if(this->_default_type == 2) return this->_default_func(key);
else assert(false);
}
public:
inline auto& set_default(const mapped_type& val) noexcept(NO_EXCEPT) {
this->_default_val = val;
this->_default_type = 0;
return *this;
}
inline auto& set_default(const default_func_noarg_type func) noexcept(NO_EXCEPT) {
this->_default_func_noarg = func;
this->_default_type = 1;
return *this;
}
inline auto& set_default(const default_func_type func) noexcept(NO_EXCEPT) {
this->_default_func = func;
this->_default_type = 2;
return *this;
}
inline auto& operator[](const key_type& key) noexcept(NO_EXCEPT) {
auto found = this->base::find(key);
if(found == this->base::end()) return this->base::emplace(key, this->_get_default(key)).first->second;
return found->second;
}
inline auto& operator()(const key_type& key) noexcept(NO_EXCEPT) {
return this->base::operator[](key);
}
inline std::optional<mapped_type> get(const key_type& key) const noexcept(NO_EXCEPT) {
const auto found = this->base::find(key);
if(found == this->base::end()) return {};
return found->second;
}
};
}
template<class... Args> using map = internal::map_wrapper<std::map<Args...>>;
template<class... Args> using unordered_map = internal::map_wrapper<std::unordered_map<Args...>>;
template<class... Args> using multimap = internal::map_wrapper<std::multimap<Args...>>;
template<class... Args> using unordered_multimap = internal::map_wrapper<std::unordered_multimap<Args...>>;
template<class... Args> using cc_hash_table = internal::map_wrapper<gnu::cc_hash_table<Args...>>;
template<class... Args> using gp_hash_table = internal::map_wrapper<gnu::gp_hash_table<Args...>>;
}
namespace uni {
namespace internal {
namespace multi_container_impl {
template<class Holder> struct base : Holder {
using Holder::Holder;
protected:
template<std::integral T>
constexpr internal::size_t _positivize_index(const T _x) const noexcept(NO_EXCEPT) {
auto x = static_cast<internal::size_t>(_x);
return x < 0 ? this->size() + x : x;
}
};
}
}
template<class T, unsigned int RANK, template<class...> class Holder = vector, template<class...> class Container = vector>
struct multi_container : internal::multi_container_impl::base<Holder<multi_container<T, RANK - 1, Holder, Container>>> {
private:
using base = internal::multi_container_impl::base<Holder<multi_container<T, RANK - 1, Holder, Container>>>;
public:
using base::base;
template<std::integral Head, class... Tail>
constexpr multi_container(const Head head, Tail&&... tail) noexcept(NO_EXCEPT)
: base(head, multi_container<T, RANK - 1, Holder, Container>(std::forward<Tail>(tail)...))
{
assert(head >= 0);
}
template<std::integral Head, class... Tail>
constexpr T& operator()(Head _head, Tail&&... tail) noexcept(NO_EXCEPT) {
static_assert(std::is_integral_v<Head>, "index must be integral");
const auto index = this->_positivize_index(_head);
assert(0 <= index && index < std::ranges::ssize(*this));
return (*this)[index](std::forward<Tail>(tail)...);
}
template<std::integral Head, class... Tail>
constexpr T& operator()(Head _head, Tail&&... tail) const noexcept(NO_EXCEPT) {
static_assert(std::is_integral_v<Head>, "index must be integral");
const auto index = this->_positivize_index(_head);
assert(0 <= index && index < std::ranges::ssize(*this));
return (*this)[index](std::forward<Tail>(tail)...);
}
};
template<class T, template<class...> class Holder, template<class...> class Container>
struct multi_container<T, 1, Holder, Container> : internal::multi_container_impl::base<Container<T>> {
using internal::multi_container_impl::base<Container<T>>::base;
template<class... Args>
constexpr multi_container(const Args&... args) noexcept(NO_EXCEPT) : internal::multi_container_impl::base<Container<T>>(args...)
{}
template<class Index>
constexpr T& operator()(Index&& _index) noexcept(NO_EXCEPT) {
const auto index = this->_positivize_index(std::forward<Index>(_index));
assert(0 <= index && index < std::ranges::ssize(*this));
return (*this)[index];
}
template<class Index>
constexpr T& operator()(Index&& _index) const noexcept(NO_EXCEPT) {
const auto index = this->_positivize_index(std::forward<Index>(_index));
assert(0 <= index && index < std::ranges::ssize(*this));
return (*this)[index];
}
};
template<class T, template<class...> class Holder, template<class...> class Container>
struct multi_container<T, 0, Holder, Container> {
static_assert(internal::EXCEPTION_ON_TYPE<T>, "invalid rank: 0, should be 1 or more");
};
}
namespace uni {
template<class T, class Allocator = std::allocator<T>>
using stack = std::stack<T, std::vector<T, Allocator>>;
}
namespace uni {
template<std::ranges::range R, class F>
inline R applied(R v, F&& func) noexcept(NO_EXCEPT) {
func(std::ranges::begin(v), std::ranges::end(v));
return v;
}
template<std::ranges::range R>
inline auto sorted(R&& v) noexcept(NO_EXCEPT) {
return applied(std::forward<R>(v), std::ranges::sort);
}
template<std::ranges::range R>
inline auto reversed(R&& v) noexcept(NO_EXCEPT) {
return applied(std::forward<R>(v), std::ranges::reverse);
}
}
namespace uni {
template<std::input_iterator I, std::sentinel_for<I> S, class Res = std::string>
Res to_lower(I first, S last) noexcept(NO_EXCEPT) {
Res res;
res.reserve(std::ranges::distance(first, last));
std::ranges::transform(first, last, std::back_inserter(res), ::tolower);
return res;
}
template<std::input_iterator I, std::sentinel_for<I> S, class Res = std::string>
Res to_uppwer(I first, S last) noexcept(NO_EXCEPT) {
Res res;
res.reserve(std::ranges::distance(first, last));
std::ranges::transform(first, last, std::back_inserter(res), ::toupper);
return res;
}
template<class Res = std::string>
Res to_lower(const std::string str) noexcept(NO_EXCEPT) {
return to_lower<std::string::const_iterator, std::string::const_iterator, Res>(std::begin(str), std::end(str));
}
template<class Res = std::string>
Res to_uppwer(const std::string str) noexcept(NO_EXCEPT) {
return to_uppwer<std::string::const_iterator, std::string::const_iterator, Res>(std::begin(str), std::end(str));
}
}
using namespace std::literals;
using std::cin;
using std::cout;
using std::pair;
using std::tuple;
using std::queue;
using std::stack;
using std::priority_queue;
using std::bitset;
using std::ranges::sort;
using std::ranges::reverse;
using std::ranges::min_element;
using std::ranges::max_element;
using std::make_pair;
using std::make_tuple;
using uni::i32;
using uni::u32;
using uni::i64;
using uni::u64;
using uni::i128;
using uni::u128;
using uni::uint;
using uni::ll;
using uni::ull;
using uni::ld;
using uni::INF32;
using uni::INF64;
using uni::INF;
using uni::MINT;
using uni::INV;
using uni::SINV;
using uni::LN;
using uni::SPC;
using uni::DIRECTIONS;
using uni::DIRS4;
using uni::DIRS8;
using uni::DIRS4P;
using uni::DIRS8P;
using uni::input_adaptor;
using uni::output_adaptor;
using uni::pow_mod;
using uni::inv_mod;
using uni::spair;
using uni::multi_container;
using uni::modint998244353;
using uni::modint1000000007;
using uni::modint_32;
using uni::modint_64;
using uni::sorted;
using uni::reversed;
using uni::chmin;
using uni::chmax;
using uni::multiset;
using uni::unordered_set;
using uni::unordered_multiset;
using uni::map;
using uni::multimap;
using uni::unordered_map;
using uni::unordered_multimap;
using uni::valarray;
using uni::vector;
using uni::string;
using uni::array;
void solve();
signed main() {
({ ; });
int $ = 0;
while(true) {
({ ; });
solve();
}
return 0;
}
#pragma GCC diagnostic warning "-Wshadow=local"
void solve() {
int n;
std::cin >> n;
if(n == 0)exit(0);
int a;
vector<int> t(1e5,false);
for(int i = 0; i < n; i++){
std::cin >> a;
a--;
t[a] = true;
}
for(int i = 0; i< 1e5; i++){
if(t[i] != true){
std::cout << i +1 << std::endl;
return;
}
}
}
