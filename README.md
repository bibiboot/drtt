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

