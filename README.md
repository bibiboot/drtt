drtt
====

Estimated Round trip delay of a direct link

Undertanding directories
------------------------
- src/lib : Contains library specific codes written by the contributor.
- src/deps : Contains the external libraries which are dependency.
- etc      : Contains the data or setting text files used.
- scripts  : Contains shell scripts.
- bin      : Contains the runnable files created after build command.
- test     : Contains the sub-directories of the test files written.

Most important Coding guidlines
-------------------------------
- Follow 4 space indentation.
- Follow one line space between all the fucntions.
- Conditional statements must be in the below format.
```
    if (x == y) {
        ..
    } else if (x > y) {
        ...
    } else {
        ....
    }
```
- Functions much be written in the below format.
```
    int main (int argc, char *argv[])
    {
      ..
    }
```
- Use one space around (on each side of) most binary and ternary
  operators,
  such as any of these:
```
    =  +  -  <  >  *  /  %  |  &  ^  <=  >=  ==  !=  ?  :
```
- LOCAL variable names should be short, and to the point.  If you have
some random integer loop counter, it should probably be called "i".
Calling it "loop_counter" is non-productive, if there is no chance of it
being mis-understood.  Similarly, "tmp" can be just about any type of
variable that is used to hold a temporary value.
- Try to use  u8/u16/u32 , instead of long long int etc.
- Functions should be short and sweet, and do just one thing.  They
  should
  fit on one or two screenfuls of text (the ISO/ANSI screen size is
  80x24,
  as we all know), and do one thing and do that well.

  The maximum length of a function is inversely proportional to the
  complexity and indentation level of that function.  So, if you have a
  conceptually simple function that is just one long (but simple)
  case-statement, where you have to do lots of small things for a lot of
  different cases, it's OK to have a longer function.

  However, if you have a complex function, and you suspect that a
  less-than-gifted first-year high-school student might not even
  understand what the function is all about, you should adhere to the
  maximum limits all the more closely.  Use helper functions with
  descriptive names (you can ask the compiler to in-line them if you
  think
  it's performance-critical, and it will probably do a better job of it
  than you would have done).

  Another measure of the function is the number of local variables.
  They
  shouldn't exceed 5-10, or you're doing something wrong.  Re-think the
  function, and split it into smaller pieces.  A human brain can
  generally easily keep track of about 7 different things, anything more
  and it gets confused.  You know you're brilliant, but maybe you'd like
  to understand what you did 2 weeks from now.

Framework usuage guidelines
---------------------------
- Access global variable.
```
    struct globals {
        int new_variable;
        ...
    }

    globals.new_variable = 10;
```
- Access config variable.
