// The MIT License (MIT)
//
// Copyright (c) 2015 Claus Jensby Madsen
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "gtest/gtest.h"
#include "uncertainty.hpp"

using namespace std;
using namespace uncertainty;

// This function tells the test framework how to output the contents of the
// object. This is used to give feedback when a test assertion fails.
void PrintTo(const uncertain_value<int> uv, ::std::ostream* os) {
  *os << "Value: " << uv.get_value() << ", Uncertainty: " << uv.get_uncertainty();
}

// Make sure the class isn't bigger than necessary.
TEST(MiscTests, ClassSize) {
  ASSERT_EQ(sizeof(int) * 2, sizeof(uncertain_value<int>));
  ASSERT_EQ(sizeof(float) * 2, sizeof(uncertain_value<float>));
  ASSERT_EQ(sizeof(double) * 2, sizeof(uncertain_value<double>));
}

// Ensure data members are initialized properly.
TEST(ConstructionTests, ConstructionInitializeMembers) {
  uncertain_value<int> uv(10, 20);
  ASSERT_EQ(10, uv.get_value());
  ASSERT_EQ(20, uv.get_uncertainty());
  ASSERT_EQ(2, uv.get_relative_uncertainty());
}

// Throw exception only if initializing with a negative uncertainty, which doesn't make sense.
TEST(ConstructionTests, NegativeUncertainty) {
  ASSERT_NO_THROW(uncertain_value<int> uv(10, 2));
  ASSERT_NO_THROW(uncertain_value<int> uv(10, 0));
  ASSERT_THROW(uncertain_value<int> uv(10, -2), invalid_argument);
  ASSERT_NO_THROW(uncertain_value<int> uv(10, 2));
  ASSERT_NO_THROW(uncertain_value<int> uv(0, 2));
  ASSERT_NO_THROW(uncertain_value<int> uv(-10, 2));
}

// Test the == operator
TEST(ArithmeticTests, Equality) {
  ASSERT_EQ(uncertain_value<int>(10, 3), uncertain_value<int>(10, 3));
  ASSERT_NE(uncertain_value<int>(10, 3), uncertain_value<int>(12, 3));
  ASSERT_NE(uncertain_value<int>(10, 3), uncertain_value<int>(10, 5));
}

// Ensure it adds properly
TEST(ArithmeticTests, Addition) {
  ASSERT_EQ(uncertain_value<int>(5 + 11, 1 + 3), uncertain_value<int>(5, 1) + uncertain_value<int>(11, 3));
}

// Ensure it subtracts properly
TEST(ArithmeticTests, Subtraction) {
  ASSERT_EQ(uncertain_value<int>(17 - 9, 4 + 1), uncertain_value<int>(17, 4) - uncertain_value<int>(9, 1));
}

// Ensure it multiplies properly
TEST(ArithmeticTests, Multiplication) {
  uncertain_value<int> uv1(15, 30);
  uncertain_value<int> uv2(4, 12);
  uncertain_value<int> uv3(uv1.get_value() * uv2.get_value(), uv1.get_relative_uncertainty() + uv2.get_relative_uncertainty());
  ASSERT_EQ(uv3, uv1 * uv2);
}

// Ensure it divides properly
TEST(ArithmeticTests, Division) {
  uncertain_value<int> uv1(10, 60);
  uncertain_value<int> uv2(5, 15);
  uncertain_value<int> uv3(uv1.get_value() / uv2.get_value(), uv1.get_relative_uncertainty() + uv2.get_relative_uncertainty());
  ASSERT_EQ(uv3, uv1 / uv2);
}

TEST(ArithmeticTests, Division2) {
  uncertain_value<int> uv1(20, 6);
  uncertain_value<int> uv2(10, 3);
  ASSERT_EQ(uv2, uv1 / 2);
}
