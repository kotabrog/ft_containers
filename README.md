# ft_containers

## Overview

Created some container classes in c++

## Requirement

- clang (or docker)

## Usage

By including vector.hpp and map.hpp in inc, you can use your own vector and map.

Tests can be run as follows

```
git clone ...
cd ft_containers
make
./ft_containers 800 > test0
```

Then you can test vector and map with std by changing the makefile as follows.

```diff
- FT_EQUAL_STD = 0
+ FT_EQUAL_STD = 1
```

Then compare the output results between my own classes and std.

```
make re
./ft_containers 800 > test1
diff test0 test1
```

※ Please put any number you like in 800. It is a random seed value.

You can also use make docker instead of make if you do not have clang in your environment.

You can also verify the speed of vector and map below.

```
make time_test
./time_test
```

## Features

The following classes and functions are reproduced (with the exception of a few, which are reproduced from c++98).

- enable_if
- equal
- is_integral
- iterator_traits
- lexicographical_compare
- map
- pair
- reverse_iterator
- vector

## Reference

- [cppreference](https://en.cppreference.com/w/Main_Page)

## Licence

[MIT](https://github.com/kotabrog/ft_containers/blob/main/LICENSE)
