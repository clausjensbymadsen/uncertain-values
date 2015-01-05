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

#ifndef UNCERTAINTY_HPP
#define UNCERTAINTY_HPP

#include <stdexcept>

namespace uncertainty {

  // TODO: Use template metaprogramming to assert the requirements for T?
  template<typename T>
  class uncertain_value {
  private:
    T m_value;
    T m_uncertainty;
  public:
    // Constructors
    uncertain_value(T value, T uncertainty) : m_value(value), m_uncertainty(uncertainty) {
      if (m_uncertainty < 0)
        throw std::invalid_argument("Uncertainty can not be negative.");
    }

    uncertain_value(T value) : m_value(value), m_uncertainty(0) {}

    // Class getters
    T get_value() const {
      return m_value;
    }

    T get_uncertainty() const {
      return m_uncertainty;
    }

    T get_relative_uncertainty() const {
      return m_uncertainty / m_value;
    }

    // Equality operators
    bool operator==(const uncertain_value<T> &other) const {
      return (m_value == other.m_value) && (m_uncertainty == other.m_uncertainty);
    }

    bool operator!=(const uncertain_value<T> &other) const {
      return !operator==(other);
    }

    // Arithmetic operators
    uncertain_value<T> operator+(const uncertain_value<T> &other) const {
      return uncertain_value<T>(m_value + other.m_value, m_uncertainty + other.m_uncertainty);
    }

    uncertain_value<T> operator-(const uncertain_value<T> &other) const {
      return uncertain_value<T>(m_value - other.m_value, m_uncertainty + other.m_uncertainty);
    }

    uncertain_value<T> operator*(const uncertain_value<T> &other) const {
      return uncertain_value<T>(m_value * other.m_value, get_relative_uncertainty() + other.get_relative_uncertainty());
    }

    uncertain_value<T> operator/(const uncertain_value<T> &other) const {
      return uncertain_value<T>(m_value / other.m_value, get_relative_uncertainty() + other.get_relative_uncertainty());
    }

    uncertain_value<T> operator/(const T &other) const {
      return uncertain_value<T>(m_value / other, m_uncertainty / other);
    }
  };

  // Common types for convenience
  typedef uncertain_value<float> uncertain_float;
  typedef uncertain_value<double> uncertain_double;

  // If ostream is included, then extend C++ output streams to support uncertain values
  // TODO: Check if other library implementations use other ostream include guards (they probably do)
  // TODO: Probably a bad solution, as it makes include order significant. There might be a better template metaprogramming-based solution.
  #ifdef _GLIBCXX_OSTREAM
  template<typename T>
  std::ostream& operator<<(std::ostream& stream, uncertain_value<T> value) {
    return stream << value.get_value() << " plus/minus " << value.get_uncertainty();
  }
  #endif

  // TODO: Support for raising uncertain values to powers?
}

#endif