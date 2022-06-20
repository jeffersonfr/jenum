#include <iostream>
#include <cstdint>
#include <iomanip>
#include <type_traits>
#include <utility>

namespace jcore {

  template<typename T>
    struct jenum {

      using Type = typename std::underlying_type<T>::type;

      T value;

      operator bool () const
      {
        return static_cast<Type>(value) != Type{};
      }

      operator T () const
      {
        return value;
      }

      template<typename ...Args>
        typename std::enable_if<std::conjunction<std::is_convertible<Args, typename std::decay<T>::type>...>::value, jenum<T>>::type And(Args ...args)
        {
          return {static_cast<T>((to_underlying(value) & ... & to_underlying(static_cast<T>(args))))};
        }

      template<typename ...Args>
        typename std::enable_if<std::conjunction<std::is_convertible<Args, typename std::decay<T>::type>...>::value, jenum<T>>::type Or(Args ...args)
        {
          return {static_cast<T>((to_underlying(value) | ... | to_underlying(static_cast<T>(args))))};
        }

      jenum<T> Not()
      {
        return {static_cast<T>(~to_underlying(value))};
      }

      /*
      friend std::ostream & operator<<(std::ostream & stream, jenum const & obj)
      {
        stream << to_underlying(obj.value);

        return stream;
      }
      */

      private:
        template<typename Enum>
          constexpr static std::underlying_type_t<Enum> to_underlying(Enum e) noexcept
          {
            return static_cast<std::underlying_type_t<Enum>>(e);
          }

    };

  template<typename T, typename ...Args>
    auto jenum_and(T t, Args ...args) -> jenum<T>
    {
      return jenum<T>{t}.And(args...);
    }

  template<typename T, typename ...Args>
    auto jenum_and(jenum<T> t, Args ...args) -> jenum<T>
    {
      return jenum<decltype(t.value)>{t.value}.And(static_cast<decltype(t.value)>(args)...);
    }

  template<typename T, typename ...Args>
    auto jenum_or(T t, Args ...args) -> jenum<T>
    {
      return jenum<T>{t}.Or(args...);
    }

  template<typename T, typename ...Args>
    auto jenum_or(jenum<T> t, Args ...args) -> jenum<T>
    {
      return jenum<decltype(t.value)>{t.value}.Or(static_cast<decltype(t.value)>(args)...);
    }

  template<typename T>
    jenum<T> jenum_not(T t)
    {
      return jenum<T>{t}.Not();
    }

  template<typename T>
    jenum<T> jenum_not(jenum<T> t)
    {
      return jenum<decltype(t.value)>{t.value}.Not();
    }
  
  template <typename T>
    requires std::is_enum<T>::value
  std::ostream & operator << (std::ostream & stream, T obj)
  {
    stream << static_cast<std::underlying_type_t<T>>(obj);

    return stream;
  }

  template <typename T>
    requires std::is_enum<T>::value
  T operator & (T lhs, T rhs)
  {
    return jenum_and(lhs, rhs);
  }

  template <typename T>
    requires std::is_enum<T>::value
  T operator | (T lhs, T rhs)
  {
    return jenum_or(lhs, rhs);
  }

}

