# unix-ls-command

Purpose/requirements:
- Print directory and file information in multiple formats
- Must be able to use the flags l, r, a, t, and R
- No leaks and no unexpcted failures

What I learned:
- How to manage file and directory information using functions provided by dirent.h
- How to navigate directories in a C program by properly concatenating strings based on user input or given flags such as the recursive -R flag
- Simple ways to sort information either by the time of creating or (by default) ascii value.
- Information parsing!
- More information parsing!
- So much parsing...

Overall this project was pretty simple and straight forward. At this point I am confident in my ability to use, parse, and use parsed information. The tricky part was setting up a recursive function that no only goes through each directory recursivly, but to also work with multiple flags.

ie. -latR should print out the long format of each file/directory, also print all hidden files, sort the files/directories printed by time of creation, and preform this for each directory found

I really enjoyed this project! It was not as challenging as I would have liked. Almost all the skills required to complete this project were very basic. However I should have used a better sorting algorithm than buble sort. Quick sort should have been my go to!
