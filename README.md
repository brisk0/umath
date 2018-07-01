UMATH
=====
Terminal-based prettifier for mathematical expressions using unicode maths symbols

Requirements
------------
* POSIX compliant standard library
* Clang (or GCC compatible compiler with tweak to Makefile)
* GNU readline library
* A terminal font with good support for unicode maths characters

Installation
------------
To build binary:

    $ make

Usage
-----
Run the binary:

    $ ./umath

Umath uses *readline* for interactive input, and prints prettified expression
to standard out.

E.g.:

    $ ./umath
    > G*mM/(r*r)
       mM  
    G⋅⎯⎯⎯⎯⎯
      (r⋅r)

