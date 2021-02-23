// Matthew Turi
// ID: 822202323

#include <fstream>
#include <iostream>
#include <pthread.h>
#include <cmath>
#include <sys/stat.h>

typedef struct {long *CurrentStatus;long InitialValue;long TerminationValue;} PROGRESS_STATUS;

void * progress_monitor(void * status){ // progress monitor pthread function
    PROGRESS_STATUS *args = (PROGRESS_STATUS *)status; //cast void ptr to our data struct
    int printed = 0; //keep track of how many chars we have printed to out
    int frq = int(args->TerminationValue)/50; //frq is set to total num bytes (chars) / 50, so we print every frq chars we parse
    if (frq == 0) // if termvalue < 50, set it to print every char parsed
        frq = 1;
    long prev_status = 0;
    int dif;

    while (*args->CurrentStatus < args->TerminationValue and (printed < 50)){
        dif = *args->CurrentStatus - prev_status;
        if (dif >= frq){ //if the change in status is >= frq set before, print something
            if ((printed+1) % 10 == 0){
                std::cout << '+';
                printed++;
            }
            else {
                std::cout << '-';
                printed++;
            }
            fflush(stdout);
            prev_status = *args->CurrentStatus;
        }
    }
    if (*args->CurrentStatus >= args->TerminationValue and (printed < 50)){ // catch block for if we exit the above loop before the progress bar is filled completely
        while (printed < 50){
            if ((printed % 10 == 0 or printed == 49) and printed != 0)
                std::cout << '+';
            else
                std::cout << '-';
            printed++;
            fflush(stdout);
        }
    }
    return NULL;
}

long wordcount(char* file){
    std::ifstream ifile;
    ifile.open(file);
    if (!ifile) {
        std::cout << "Unable to open file" << std::endl;
        exit(1);
    }
    pthread_t ptid;
    pthread_attr_t pthread_attributes;
    pthread_attr_init(&pthread_attributes);
    long init = 0;
    struct stat64 stat_buf;
    stat64(file, &stat_buf);
    long f_size = stat_buf.st_size; //size of file
    char curr_c;
    bool space = true;
    long word_count = 0;
    long char_count = 0;

    PROGRESS_STATUS *curr = new(PROGRESS_STATUS); //memory allocation for our struct, then set values
    curr->CurrentStatus = &char_count;
    curr->TerminationValue = f_size;
    curr->InitialValue = init;
    pthread_create( &ptid, &pthread_attributes,
                    &progress_monitor, (void *) curr);

    while(ifile.get(curr_c) and curr_c != EOF){
        if (isspace(curr_c)==0 && (space))
            ++word_count;
        space = isspace(curr_c);
        char_count++;
    }
    pthread_join(ptid, NULL); // wait till pthread finishes, then do something
    std::cout << "\nThere are " << word_count << " words in "<< file << std::endl;
    return word_count;
}

int main(int argc, char **argv) {
    if (!argv[1]){
        std::cout << "No file specified." << std::endl;
        exit(1);
    }
    else {
        wordcount(argv[1]);
    }
}
