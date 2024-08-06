# wgu-flashcards
flash.c must be compiled with gcc, and all of the *.flash files are flashcards for the entire course overall. flash.c is the source code for the actual program that runs the flashcard iterator. Compile the file with "gcc flash.c -o (whatever you want to name it)" and then run the program from the command line. If on Linux you can do this with "./flash" or "./(whatever you named the program)" while inside the directory you compiled it

# adding your own flashcards
All you need to do to create and add your own flashcards is make a file called *(whatever you want to name it).flash and it will be displayed as a valid file to open when you start flash. If you don't want to or are unable to create a .flash file, you can modify the source code and remove the filter. Inside the .flash file, the format to structure your flash cards is, on separate lines:
\n
Question
Answer, prefaced by --

# example
"Where is SRAM primarily used"
"--Cache memory"
