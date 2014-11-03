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
  should do one thing and do that well.
- Another measure of the function is the number of local variables.
  They shouldn't exceed 5-10, or you're doing something wrong.  Re-think the
  function, and split it into smaller pieces.  A human brain can
  generally easily keep track of about 7 different things, anything more
  and it gets confused.  You know you're brilliant, but maybe you'd like
  to understand what you did 2 weeks from now.
- Always comment before the function starts in the below mentioned style.
```
    /*
     * This is the preferred style for multi-line
     * comments in the Linux kernel source code.
     * Please use it consistently.
     *
     * Description:  A column of asterisks on the left side,
     * with beginning and ending almost-blank lines.
     */
```
- Generally, you want your comments to tell WHAT your code does, not
  HOW.
- Linux style for comments is the C89 "/* ... */" style.
Don't use C99-style "// ..." comments.
-  If you have a function
that counts the number of active users, you should call that
"count_active_users()" or similar, you should _not_ call it "cntusr()"

Framework usage guidelines
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
```
    struct config {
        int packet_len;
    }

    int i = globals.config.packet_len;
```

Repo functionality
------------------
- Make echo request to all the direct linked nodes running drtt.
- Recieve the echo reply of all the request send.
- Calculate the RTT of a given directly connected node.
- Node can be router or host.
- Store the RTT in a persistent store.
- Create a functionality of IPC with the CNTP or CROUTER.

Protocol
--------
| Custom Header  | 64 Bit |
| ------------- | -------------- |
| Sender Timestamp | 16 bit |
| ------------- | -------------- |

| Custom Header | Send Timestamp |
| ------------- | -------------- |
