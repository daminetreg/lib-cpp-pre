#ifndef PRE_VARIANT_GET_HPP
#define PRE_VARIANT_GET_HPP

#include <boost/variant.hpp>
#include <boost/type_traits.hpp>

namespace pre { 
  template <typename T, typename... Ts>
  struct Index;

  template <typename T, typename... Ts>
  struct Index<T, T, Ts...> : std::integral_constant<std::size_t, 0> {};

  template <typename T, typename U, typename... Ts>
  struct Index<T, U, Ts...> : std::integral_constant<std::size_t, 1 + Index<T, Ts...>::value> {};

//  template <typename T, typename... Ts>
//  constexpr std::size_t Index_v = Index<T, Ts...>::value;



  template <typename U, typename... Ts >                                                                                                           
  inline typename boost::add_pointer<const U>::type get(                                                                           
      const boost::variant<Ts...>* operand) {                                                                                               
                                                                                                                                   
    typedef typename boost::add_pointer<const U>::type U_ptr;                                                                      
                                                                                                                                   
    if (operand->which() == Index<U, Ts...>::value) {                                                            
      return reinterpret_cast<U_ptr>(operand->storage_.address());                                                                 
    } else {                                                                                                                       
      return nullptr;                                                                                                              
    }                                                                                                                              
                                                                                                                                   
  }                                                                                                                                
                                                                                                                                   
                                                                                                                                   
  template <typename U, typename... Ts >                                                                                                           
  inline typename boost::add_reference<const U>::type get(                                                                         
      const boost::variant<Ts...>& operand) {                                                                                               
                                                                                                                                   
    auto* value = pre::get<U>(std::addressof(operand));                                                                            
    if (value != nullptr) {                                                                                                        
      return *value;                                                                                                               
    } else {                                                                                                                       
      boost::throw_exception(boost::bad_get());                                                                                    
    }                                                                                                                              
                                                                                                                                   
  }                                                                                                                                
                                                                                                                                   
  template <typename U , typename... Ts >                                                                                                           
  inline typename boost::add_pointer<U>::type get(                                                                                 
      boost::variant<Ts...>* operand) {                                                                                                     
                                                                                                                                   
    typedef typename boost::add_pointer<U>::type U_ptr;                                                                            
                                                                                                                                   
    if (operand->which() == Index<U, Ts...>::value) {                                                            
      return reinterpret_cast<U_ptr>(operand->storage_.address());                                                                 
    } else {                                                                                                                       
      return nullptr;                                                                                                              
    }                                                                                                                              
                                                                                                                                   
  }                                                                                                                                
                                                                                                                                   
                                                                                                                                   
  template <typename U, typename... Ts >                                                                                                           
  inline typename boost::add_reference<U>::type get(                                                                               
      boost::variant<Ts...>& operand) {                                                                                                     
                                                                                                                                   
    auto* value = pre::get<U>(std::addressof(operand));                                                                            
    if (value != nullptr) {                                                                                                        
      return *value;                                                                                                               
    } else {                                                                                                                       
      boost::throw_exception(boost::bad_get());                                                                                    
    }                                                                                                                              
                                                                                                                                   
  }
                                                                                                                                   
  template<typename F, typename... Ts, typename std::enable_if<                                                                    
    (!std::is_same<typename F::result_type, void>::value)            
  >::type* = nullptr>                                                                                                              
  inline auto apply_visitor(F f, const boost::variant<Ts...>& variant) -> typename F::result_type {                                
    typename F::result_type result;                                                                                                
    return std::initializer_list<int>{( ( pre::get<Ts>(std::addressof(variant)) != nullptr ) ?                                     
      (result = std::ref(f)(pre::get<Ts>(variant))),0 : 0)...}, result;                                                            
                                                                                                                                   
  }                                                                                                                                
                                                                                                                                   
  template<typename F, typename... Ts, typename std::enable_if<                                                                    
    (std::is_same<typename F::result_type, void>::value)             
  >::type* = nullptr>                                                                                                              
  inline auto apply_visitor(F f, const boost::variant<Ts...>& variant) -> void {                                                   
    std::initializer_list<int>{( ( pre::get<Ts>(std::addressof(variant)) != nullptr ) ?                                            
        (std::ref(f)(pre::get<Ts>(variant))),0 : 0)...};                                                                           
                                                                                                                                   
  }                                                                                                                                
                                                                                                                                   
                                                                                                                                   
  template<typename F, typename... Ts, typename std::enable_if<                                                                    
    (!std::is_same<typename F::result_type, void>::value)            
  >::type* = nullptr>                                                                                                              
  inline auto apply_visitor(F f, boost::variant<Ts...>& variant) -> typename F::result_type {                                      
    typename F::result_type result;                                                                                                
    return std::initializer_list<int>{( ( pre::get<Ts>(std::addressof(variant)) != nullptr ) ?                                     
      (result = std::ref(f)(pre::get<Ts>(variant))),0 : 0)...}, result;                                                            
                                                                                                                                   
  }                                                                                                                                
                                                                                                                                   
  template<typename F, typename... Ts, typename std::enable_if<                                                                    
    (std::is_same<typename F::result_type, void>::value)             
  >::type* = nullptr>                                                                                                              
  inline auto apply_visitor(F f, boost::variant<Ts...>& variant) -> void {                                                         
    std::initializer_list<int>{( ( pre::get<Ts>(std::addressof(variant)) != nullptr ) ?                                            
        (std::ref(f)(pre::get<Ts>(variant))),0 : 0)...};                                                                           
                                                                                                                                   
  }                                                                                                                                
}                                                                                                                                  

#endif
