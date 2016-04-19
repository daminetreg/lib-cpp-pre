#ifndef PRE_VARIANT_APPLY_HPP
#define PRE_VARIANT_APPLY_HPP

#include <pre/type_traits/function_traits.hpp>

namespace pre { namespace variant { 

  template<typename... Ts>
  using pack_params = eggs::variants::detail::pack< eggs::variants::detail::empty, typename std::remove_cv<Ts>::type...  >;

  template<typename F, typename... Ts, typename std::enable_if<!std::is_same<typename F::result_type, void>::value>::type* = nullptr>
  auto apply(F f, const eggs::variant<Ts...>& variant) -> typename F::result_type {
    //return std::initializer_list<int>{(std::ref(f)(std::forward<Ts>(variant.template target<Ts>())),0)...}, return_val;
    typename F::result_type result;
    return std::initializer_list<int>{( (variant.which() == eggs::variants::detail::index_of<Ts, pack_params<Ts...>>::value - 1) 
        ? 
        (result = std::ref(f)(eggs::variants::get<Ts>(variant))),0 : 0)...}, result;

  }

  template<typename F, typename... Ts>
  auto apply(F f, const eggs::variant<Ts...>& variant) -> void {
    std::cout << "Hello accessing variant " << variant.which() << std::endl;
    std::initializer_list<int>{( (variant.which() == eggs::variants::detail::index_of<Ts, pack_params<Ts...>>::value - 1) 
        ? 
        (std::ref(f)(eggs::variants::get<Ts>(variant))),0 : 0)...};

  }



}}

//eggs::variants::detail::index_of<Ts, pack_params<Ts>>::value

#endif
