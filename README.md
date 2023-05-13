# linux-process-monitoring-tool
Tool to display the tables used by the OS to keep track of open files, assignation of File Descriptors (FD) and processess.

The program, will generate:

- process FD table
- System-wide FD Table
- Vnodes FD table, and
- a composed view of the previous table
 

The program will accept multiple commands line arguments:

flagged arguments

--per-process, indicates that only the process FD table will be displayed

--systemWide, indicates that only the system-wide FD table will be displayed

--Vnodes, indicates that the Vnodes FD table will be displayed

--composite, indicates that only the composed table will be displayed

--threshold=X, where X denotes an integer, indicating that processes which have a number of FD assigned larger than X should be flagged in the output. For this it will list the PID and number of assigned FDs, e.g. PID (FD)

and combination of these, i.e. the program can receive multiple of these flags combined.

Default behaviour: if no argument is passed to the program, then the program will display the composite table, i.e. same effect as having used the --composite flag

positional argument:
only one positional argument indicating a particular process id number (PID), if not specified the program will attempt to process all the currently running processes for the user executing the program

Note: To run/use my program you enter the command "make" to compile the code and create the executable A2. Then you may run the command ./A2 [single optional positional argument] [any number of the valid command line arguments starting with "-". Each command line argument must be separated by exactly 1 space. And the positional argument if present must be positioned as the first argument right after ./A2


How did I solve the problem?

To solve this problem I had read over the proc, dirent.h and unistd.h manuals. From the proc manual I figured out the processes were stored and how to access the various pieces of information. For example you can find the UID and state of the process from /proc/[pid]/status. From the dirent.h manual I used various functions to help me work with the directories. From the unistd.h manual I used functions like readlink() and getuid().
How I went about coding the solution: I noticed that the composite table had all the information contained in the other tables. Using this observation I thought up the solution that went like: For each process gather up all the information such as pid, fd, filename, inode, then just print the correct pieces of info based of the command line argument given. So, my program starts off with the main() function which has many if statements and logic. What the main function does is that it calls myfunc() sending the positional argument if it exists and the other command line arguments 1 at a time. 

