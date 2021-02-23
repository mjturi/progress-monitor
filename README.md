# progress-monitor

## Simple cpp program to compute the word count of a given file and display a "progress bar" as the process executes.

### Design
- the program takes a filename as an argument from the command line, and then proceeds to parse it character by character
- as the file is read, a pthread is used to display the current progress as it reads
- once the pthread terminates, and the progress bar is filled, the program outputs the total word count of the given file

### Sample Output
- this "progress bar" will fill as the file is read -> shown is the final console log
---------+---------+---------+---------+---------+ <br>
There are 1095695 words in big.txt
