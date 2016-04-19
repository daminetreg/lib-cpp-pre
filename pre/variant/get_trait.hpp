#ifndef PRE_VARIANT_GET_TRAIT_HPP
#define PRE_VARIANT_GET_TRAIT_HPP

//#include <boost/variant.hpp>
#include <eggs/variant.hpp>
#include <boost/type_traits.hpp>

#include <pre/json/traits/is_boost_variant.hpp>
#include <pre/variant/detail/assignable_from.hpp>

#include <pre/variant/apply.hpp>

namespace pre { namespace variant { 

  namespace detail {
    template<class ResultVariant, template<class T> class TraitMetafunction>
    struct get_trait_visitor {

      
      template< class U > ResultVariant operator()(const U&) const { 
        return typename TraitMetafunction<U>::type{};
      }

      typedef ResultVariant result_type;
    };


    template<class Result, template<class T> class TraitMetafunction>
    struct get_value_trait_visitor {

      template< class U >
      Result operator()(const U&) const { 
        return typename TraitMetafunction<U>::type{};
      }

      typedef Result result_type;
    };
  }

  /**
   * \brief Runtime compile time traits access. 
   *        This function gets the active type of a variant and return a runtime
   *        instantiation of the associated type found by
   *        TraitMetafunction<active type>. 
   *
   * \param variant The variant whose active type will be queried for the given
   *                TraitMetafunction
   *
   * \param Result A boost::variant or any type capable to hold the runtime 
   *                     instance of the TraitMetafunction result.
   *
   * \param TraitMetafunction Template metafunction which will be called on the 
   *                          active type of the runtime parameter : variant.
   *
   * \param InspectedVariant A boost::variant to apply the TraitMetafunction on it's
   *                         active field.
   *
   */
  template<class Result, template<class T> class TraitMetafunction, class InspectedVariant,
    typename std::enable_if< 
      eggs::variants::detail::is_variant<Result>::value
    >::type* = nullptr
  > 
  inline Result get_trait(const InspectedVariant& variant) {
    return pre::variant::apply(detail::get_trait_visitor<Result, TraitMetafunction>{}, variant);
  }

  template<class Result, template<class T> class TraitMetafunction, class InspectedVariant,
    typename std::enable_if< 
      !eggs::variants::detail::is_variant<Result>::value
    >::type* = nullptr
  >
  inline Result get_trait(const InspectedVariant& variant) {
    return pre::variant::apply(detail::get_value_trait_visitor<Result, TraitMetafunction>{}, variant);
  }
  
}}

#endif
