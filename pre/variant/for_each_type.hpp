#ifndef PRE_VARIANT_FOR_EACH_TYPE_HPP
#define PRE_VARIANT_FOR_EACH_TYPE_HPP

#include <eggs/variant.hpp>

namespace pre { namespace variant {

  template<typename F, typename... Ts >
  void for_each_type(F f, const eggs::variant<Ts...>& variant = eggs::variant<Ts...>{} ) {
    std::initializer_list<int>{
      (f(Ts{}),0)...
    };
  }
  

}}

#endif
