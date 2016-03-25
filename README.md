# Tribit
-----

Task: Implement the following Tribit algorithm in any programming language.

Evaluation criteria:

1) The program must work correctly.

2) The code has to be simple and easy to maintain - we are not
interested in architectural astronauts, with lots of abstraction or
other complicated design patterns.
   Do not write the code for future extensibility. Instead, write the
code to solve the task at hand in the simplest and best way and to be as
readable as possible. A short, but readable program is better than a
long and general one.

Please report how much time you spent, and an approximate breakdown of what 
this time was spent for.


Tribit takes place in a 2D pyramid of triangles. The pyramids vary in size, from the smallest of 
size 1 being a single cell:

    ^
   / \
  *---*

doubling to the pyramid with 4 cells:

      ^
     / \
    *---*
   / \ / \
  *---*---*

Double again to get the pyramid with 16 cells:

          ^
         / \
        *---*
       / \ / \
      *---*---*
     / \ / \ / \
    *---*---*---*
   / \ / \ / \ / \
  *---*---*---*---*

This could be doubled to one with 64 cells:

                  ^
                 / \
                *---*
               / \ / \
              *---*---*
             / \ / \ / \
            *---*---*---*
           / \ / \ / \ / \
          *---*---*---*---*
         / \ / \ / \ / \ / \
        *---*---*---*---*---*
       / \ / \ / \ / \ / \ / \
      *---*---*---*---*---*---*
     / \ / \ / \ / \ / \ / \ / \
    *---*---*---*---*---*---*---*
   / \ / \ / \ / \ / \ / \ / \ / \
  *---*---*---*---*---*---*---*---*

and so on, so that the number of cells is a power of 4.

Each cell is either black or white, representing a bit. Therefore, each triangle corresponds to a 
binary number, where the bits are numbered in reading order:

      ^
     /0\
    *---*
   /1\2/3\
  *---*---*

So this triangle with three black cells and one white cell

      ^
     /1\
    *---*
   /0\1/1\
  *---*---*

corresponds to the binary number 1101 = 0x0D.

The binary number 1100 corresponds to this pyramid:

      ^
     /0\
    *---*
   /0\1/1\ 
  *---*---*

Similary, the binary number 

    0101110 11010 011 0
  = 0101 1101 1010 0110 = 0x5da6

corresponds to this pyramid:

          ^
         /0\ 
        *---*
       /1\1/0\
      *---*---*
     /0\1/0\1/1\
    *---*---*---*
   /0\1/1\1/0\1/0\
  *---*---*---*---*

Tribit is a kind of checksum algorithm, which takes a binary number and calculates
a single-bit checksum.

It does this by matching patterns in the input pyramid, and reducing those patterns 
according to the following 16 transition rules:

  0000 -> 0000
  0001 -> 1000
  0010 -> 0001
  0011 -> 0010
  0100 -> 0000
  0101 -> 0010
  0110 -> 1011
  0111 -> 1011
  1000 -> 0100
  1001 -> 0101
  1010 -> 0111
  1011 -> 1111
  1100 -> 1101
  1101 -> 1110
  1110 -> 0111
  1111 -> 1111

So the third rule 0010 -> 0001 states that a group of four triangles with this shape
changes like this:

      ^              ^
     /0\            /1\
    *---*    ->    *---*
   /1\0/0\        /0\0/0\
  *---*---*      *---*---*

For a pyramid with 16 cells, the rules apply in groups of 4:

          ^
         /A\
        *---*
       /A\A/A\
      *---*---*
     /B\C/C\C/D\
    *---*---*---*
   /B\B/B\C/D\D/D\
  *---*---*---*---*

where the group C is upside-down and the bits numbered like this:

      *---*---*
       \1/2\3/
        *---*
         \0/
          *

Example:

          ^
         /0\ 
        *---*
       /1\1/0\
      *---*---*
     /0\1/0\1/1\
    *---*---*---*
   /0\1/1\1/0\1/0\
  *---*---*---*---*

Group A is

          ^
         /0\ 
        *---*
       /1\1/0\
      *---*---*

(0110) and transforms to (1011):

          ^
         /1\ 
        *---*
       /1\0/1\
      *---*---*

In this way, the entire pyramid transforms to this:

          ^ 
         /1\ 
        *---*
       /1\0/1\
      *---*---*
     /1\1/1\1/0\
    *---*---*---*
   /0\1/1\1/1\0/0\
  *---*---*---*---*

This is step 1.

The next step is this:

          ^ 
         /1\ 
        *---*
       /1\1/1\
      *---*---*
     /0\1/1\1/1\
    *---*---*---*
   /1\1/1\1/0\0/0\
  *---*---*---*---*

The algorithm iterates like this.

There is one additional rule: If a pattern matches at group level, then the entire pyramid
reduces to a simpler one.

So, if we have this pyramid:

          ^ 
         /1\ 
        *---*
       /1\1/1\
      *---*---*
     /1\1/1\1/0\
    *---*---*---*
   /1\1/1\1/0\0/0\
  *---*---*---*---*

this reduces to this smaller pyramid

          ^
         /1\ 
        *---*
       /1\1/0\
      *---*---*

in a single step.

Transitively, if you have this pyramid:

                  ^
                 /0\
                *---*
               /0\0/0\
              *---*---*
             /0\0/0\0/0\
            *---*---*---*
           /0\0/0\0/0\0/0\
          *---*---*---*---*
         /0\0/0\0/0\0/0\0/0\
        *---*---*---*---*---*
       /0\0/0\0/0\0/0\0/0\0/0\
      *---*---*---*---*---*---*
     /0\0/0\0/0\0/0\0/0\0/0\0/0\
    *---*---*---*---*---*---*---*
   /0\0/0\0/0\0/0\0/0\0/0\0/0\0/0\
  *---*---*---*---*---*---*---*---*

this reduces to

    ^
   /0\
  *---*

in a single step.

The rules are structured so that it is always well-defined how to transform a pyramid.

Your task is to implement a program that takes any string of 0 and 1s of suitable length, lowest bit at the end on the command
line, internally constructs the corresponding pyramid, prints the pyramid as a binary string on one line (so the first line
is the same as the input), applies the rules, prints the resulting pyramid in each step as a binary string in one line, 
and loops until the pyramid is reduced to a single bit and you print either a 0 or 1 on a single line.

Sample session:

> tribit.exe 0100
0100
0000
0

Please include the dump of a session starting with your birthday as an integer in MMDDYY divded by two, encoded to binary 
in your response.
So if you are born the 24th of December 1980, the seed is 122480/2 = 61240 and it becomes this invocation:

> tribit.exe 1110111100111000
...
1

Also, please include a dump of a session with this input:

> tribit.exe 1100100100001111110110101010001000100001011010001100001000110100
...
1

For reference, here is a visual dump of the rules:

     ^             ^
    / \           / \
   *---*   ->    *---*
  / \ / \       / \ / \
 *---*---*     *---*---*

     ^             ^
    /#\           / \
   *---*   ->    *---*
  / \ / \       / \ /#\
 *---*---*     *---*---*

     ^             ^
    / \           /#\
   *---*   ->    *---*
  /#\ / \       / \ / \
 *---*---*     *---*---*

     ^             ^
    /#\           / \
   *---*   ->    *---*
  /#\ / \       /#\ / \
 *---*---*     *---*---*

     ^             ^
    / \           / \
   *---*   ->    *---*
  / \#/ \       / \ / \
 *---*---*     *---*---*

     ^             ^
    /#\           / \
   *---*   ->    *---*
  / \#/ \       /#\ / \
 *---*---*     *---*---*

     ^             ^
    / \           /#\
   *---*   ->    *---*
  /#\#/ \       /#\ /#\
 *---*---*     *---*---*

     ^             ^
    /#\           /#\
   *---*   ->    *---*
  /#\#/ \       /#\ /#\
 *---*---*     *---*---*

     ^             ^
    / \           / \
   *---*   ->    *---*
  / \ /#\       / \#/ \
 *---*---*     *---*---*

     ^             ^
    /#\           /#\
   *---*   ->    *---*
  / \ /#\       / \#/ \
 *---*---*     *---*---*

     ^             ^
    / \           /#\
   *---*   ->    *---*
  /#\ /#\       /#\#/ \
 *---*---*     *---*---*

     ^             ^
    /#\           /#\
   *---*   ->    *---*
  /#\ /#\       /#\#/#\
 *---*---*     *---*---*

     ^             ^
    / \           /#\
   *---*   ->    *---*
  / \#/#\       / \#/#\
 *---*---*     *---*---*

     ^             ^
    /#\           / \
   *---*   ->    *---*
  / \#/#\       /#\#/#\
 *---*---*     *---*---*

     ^             ^
    / \           /#\
   *---*   ->    *---*
  /#\#/#\       /#\#/ \
 *---*---*     *---*---*

     ^             ^
    /#\           /#\
   *---*   ->    *---*
  /#\#/#\       /#\#/#\
 *---*---*     *---*---*
