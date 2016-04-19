#ifndef PRE_VARIANT_IS_ACTIVE_TYPE
#define PRE_VARIANT_IS_ACTIVE_TYPE

//#include <boost/variant.hpp>
#include <eggs/variant.hpp>

#include <pre/variant/apply.hpp>

namespace pre { namespace variant { 
 
  /**
   * \brief is_active_type is meant to be used on a boost::variant.
   * \param variant the Variant to check which type is active.
   * \param T the type that is checked for being active.
   */
  template<typename T, typename... Ts>
  inline bool is_active_type(const eggs::variant<Ts...>& variant) {
    return (variant.which() == eggs::variants::detail::index_of<T, pack_params<Ts...>>::value - 1);
  }



}}

#endif
