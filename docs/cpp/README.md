# Kepler's equation.

Kepler's equation relates the mean anomaly (`M`) to the eccentric anomaly (`E`)
via the eccentricity (`e`):

```
M = E - e sin( E ). # valid for elliptical orbits
```

The equation is not algebraic in `E`, which means that it cannot be solved
*explicitly* for `E`. It can, however, be solved *iteratively*. Given given `M`
and `e`, we aim to find `E` such that

```
f( E ) = E - e sin( E ) - M = 0.
```

The most straightforward approach is to use Newton's method which under certain
conditions states that if the approximation `x_{k}` is such that `f( x_{k} ) ~
0`, then

```
x_{k+1} = x{k} - f( x_{k} ) / f'( x_{k} )
```

is a better approximation. In our case:

```
 f( E ) = E - e sin( E ) - M
f'( E ) = 1 - e cos( E )
```

and a relatively good initial approximation is `E_{0} = M`. The algorithm, then,
improves the initial approximation with iterates `E_{1}, E_{2}, ..., E_{k}`
until we reach a desired tolerance `| f( E_{k} ) | <= tol`.

Experiment with the attached code:

1. Is it good code? What is it missing?

2. What happens if you input `ecc = 0.99 man = 3.14`?

3. What happens if you input `ecc = 1.5`? Does it find a solution? Is it valid?

4. What are the limitations of Newton's method? Does it always converge? How
rapidly does it converge? How do you measure convergence rate?


## Software Notes

The code should compile under any relatively decent C++ compiler. I compiled as follows:

```
$ clang++ kepler.cpp -std=c++17 -Wall -Wextra -O2
```

1. What do the flags mean?

2. Do you understand absolutely everything in both `kepler.hpp` and `kepler.cpp`?

I recommend you visit cppreference.com and become familiarized with C++ and the
C++ Standard Library
