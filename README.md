Uncertain Values
================
This is a light-weight, header-only, templated, immutable class, which handles
values with an associated uncertainty.

It works well with floating point numeric types like float and double, as well
as it's multidimensional counterparts like mathematical vectors and matrices.

The code is unit tested with reasonable code coverage.
The code satisfies the basic exception safety guarantee.
The code is compatible with C++98 and newer.

Usage
-----
In order to use uncertain values in your C++ project, just include the uncertainty.hpp in your project
and start using the `uncertain_value<T>` class.

Example
-------
Here is a tiny application to illustrate how to use uncertain values.
This sample requires C++11 compiled with GCC.
```C++
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
```

This application will produce the following output:

```
Sum: 2252.54 plus/minus 10.7183
Mean: 563.136 plus/minus 2.67957
```
