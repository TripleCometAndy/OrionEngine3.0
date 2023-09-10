#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include <iostream>
#include "SecondOrderDynamics.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST(MyTest, MyProperty) {
  rc::check([](int x, int y) {
    ASSERT_TRUE(x + y == y + x);
  });
}

TEST(SecondOrderTest, BasicAssertions) {
  SecondOrderDynamics dynamics(1, 1, 0, 0);

  std::cout << dynamics.update(0.016, 0) << std::endl;
  std::cout << dynamics.update(0.016, 0) << std::endl;
  std::cout << dynamics.update(0.016, 0) << std::endl;
  std::cout << dynamics.update(0.016, 0) << std::endl;
  std::cout << dynamics.update(0.016, 0) << std::endl;
  std::cout << dynamics.update(0.016, 0) << std::endl;
  std::cout << dynamics.update(0.016, 1) << std::endl;
  std::cout << dynamics.update(0.016, 1) << std::endl;


}