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

#include <iostream>
#include <vector>
#include <algorithm>

#include "uncertainty.hpp"

using namespace std;
using namespace uncertainty;

int main() {
  vector<uncertain_double> data;
  data.push_back(uncertain_double(4.56, 1.425));
  data.push_back(uncertain_double(472.184, 4.183));
  data.push_back(uncertain_double(-8.3, 0.8263));
  data.push_back(uncertain_double(1784.1, 4.284));

  uncertain_double sum = accumulate(begin(data), end(data), uncertain_double(0));
  cout << "Sum: " << sum << endl;

  uncertain_double mean = sum / 4;
  cout << "Mean: " << mean << endl;

  return 0;
}