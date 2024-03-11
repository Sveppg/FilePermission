#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/ptrace.h>

//Costum Header Files loc. /HEADER_FILES
#include "escapesequenzen.h"


//Custom function definiton
void openFile_chPerm();
void createFile_wPerm();

int main(int args, char *argv[])
{
    int Menu; 
    char filename[101];
    char (*PTRfilename)[101] = &filename;
    
    CLEAR;
    HOME;

    printf("| 1. Change an existing File for different Permissions? |\n");
    printf("| 2. Create a new File with new Permissions             |\n");
    printf("|                                                       |\n");
    printf("|                  1. or 2.?                            |\n");
    scanf("%i", &Menu);
    
    if(Menu == 1){
        mode_t umask_arg;
        umask_arg = umask(002); // set umask to 002 for efficient permission passing
        printf("Please type in the file you want to edit: \n");
        printf("Format: name.type\n");
        scanf("%100s", filename);
        
        openFile_chPerm();
        
        umask(umask_arg);
    }
    
    else if(Menu == 2){
        mode_t umask_arg; // same as above
        umask_arg = umask(002);
        createFile_wPerm();

        umask(umask_arg);
    }
    
    else{
        printf("Your UserInput is insufficent... Exit\n");
        printf("please try again...\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}

void openFile_chPerm(const char *filename, int mode){
    int flags = O_RDWR | O_DIRECTORY | O_SYNC;
    
    int fd = open(filename, flags, mode);

}

void createFile_wPerm(char givenfilename[100], int flags, int mode){
    char *PTRgivenfilename = &givenfilename;
    printf("File name? (max. 20 Char):\n");
    scanf("%s", &PTRgivenfilename);

}
 