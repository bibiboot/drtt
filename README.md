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
