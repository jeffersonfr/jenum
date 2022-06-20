#include "jenum/jenum.h"

#include <gtest/gtest.h>

// teste
enum class teste {
  value1 = 1,
  value2 = 2,
  value3 = 4
};

TEST(EnumSuite, UnitTests) {
  using namespace jcore;

  teste t = teste::value1;

  std::cout << (t & teste::value3) << std::endl;
  std::cout << jenum_and(t, teste::value3) << std::endl;
  std::cout << jenum_or(t, teste::value3) << std::endl;

  auto e1 = jenum_or(t, teste::value2, teste::value3);
  auto e2 = jenum_not(teste::value1);
  auto e3 = jenum_and(jenum<teste>{teste::value1});

  std::cout << e1 << ", " << e2 << ", " << e3 << std::endl;

  std::cout << jenum_and(e1, e2) << std::endl;
}
