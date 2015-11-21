#include <iostream>
#include <utility>
#include <type_traits>

namespace ns
{
namespace detail
{


template<class T>
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
