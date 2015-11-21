#include <iostream>
#include <utility>
#include <type_traits>

namespace ns
{
namespace detail
{


// detect whether its possible to call customize_me(T) via ADL
// before the generic version of customize_me() is part of the overload set
template<class T>
struct has_customize_me_impl
{
  template<class U,
           class = decltype(customize_me(std::declval<U>()))
          >
  static std::true_type test(int);

  template<class U>
  static std::false_type test(...);

  using type = decltype(test<T>(0));
};

template<class T>
using has_customize_me = typename has_customize_me_impl<T>::type;


template<class T,
         class = typename std::enable_if<
           !has_customize_me<T>::value
         >::type>
void customize_me(T&&)
{
  std::cout << "ns::detail::customize_me()" << std::endl;
}

struct call_customize_me
{
  template<class T>
  void operator()(T&& x) const
  {
    customize_me(std::forward<T>(x));
  }
};

}


detail::call_customize_me customize_me;

}


namespace custom
{

template<class T>
void customize_me(T&&)
{
  std::cout << "custom::customize_me()" << std::endl;
}

struct bar {};

}

int main()
{
  custom::bar b;
  ns::customize_me(b);

  return 0;
}
