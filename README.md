UMath
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

    umath [input]

Example usages

	$ echo "input" | ./umath

	$ ./umath "input"

	$ ./umath
	> input

UMath can take input from stdin, arg1 or its own interactive prompt (using the readline library).

Regardless of input method, the prettified equation is printed to stdout.

E.g.:

    $ ./umath
    > G*mM/(r*r)
       mM  
    G⋅⎯⎯⎯⎯⎯
      (r⋅r)

