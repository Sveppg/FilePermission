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
void getMenu();

int main(int argc, char *argv[])
{
    int Menu; 
    char filename[101];
    char (*PTRfilename)[101] = &filename;
    
    CLEAR;
    HOME;

    if(argc != 2){ //Check for argument count
        printf("Too few Arguments!! Please Add a File...\n");
        exit(EXIT_FAILURE);
    }

    printf("_________________________________________________________\n");
    printf("| 1. Change an existing File for different Permissions? |\n");
    printf("| 2. Create a new File with new Permissions             |\n");
    printf("|                                                       |\n");
    printf("|                  1. or 2.?                            |\n");
    printf("*********************************************************\n");
    /*
    *   This if Condition will run the openFile_chPerm Func 
    */
    printf("Your Choice?"); scanf("%i", &Menu);
   
   
    if(Menu == 1){
        mode_t umask_arg;
        mode_t mode = 0; //Start with no permissions
        umask_arg = umask(002); // set umask to 002 for efficient permission passing
        getMenu();
        openFile_chPerm();
        
        umask(umask_arg);
    }
    
    /*
    *   This else if Condition will run the createFile_wPerm Func 
    *    and set or reset the umask 
    */
    else if(Menu == 2){
        mode_t umask_arg; // same as above
        mode_t mode = 0; // Start with no permissions
        umask_arg = umask(002);
        getMenu();
        createFile_wPerm();

        umask(umask_arg);
    }
    
    else{
        printf("Your UserInput is insufficent... Exit\n");
        printf("please run again...\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}





void getMenu(){
    printf("Select file permissions to set (bitwise OR will be used):\n");
    printf("________________________________________________________\n");
    printf("1. Read by owner (S_IRUSR)\n");
    printf("2. Write by owner (S_IWUSR)\n");
    printf("3. Execute by owner (S_IXUSR)\n");
    printf("123. All of them: (RWX)\n");
    printf("\n");
    printf("4. Read by group (S_IRGRP)\n");
    printf("5. Write by group (S_IWGRP)\n");
    printf("6. Execute by group (S_IXGRP)\n");
    printf("456. All of them: (RWX)\n");
    printf("\n");
    printf("7. Read by Other (S_IROTH)\n");
    printf("\n");
    printf("8. Write by Other (S_IWOTH)\n");
    printf("9. Execute by Other (S_IXOTH)\n");
    printf("789. All of them: (RWX)\n");

    printf("Enter choice (0 to end the program): \n");
}
void openFile_chPerm(const char *filename, int mode){
    int flags = O_RDWR | O_DIRECTORY | O_SYNC;
    int fd = open(argv[1], O_CREAT | O_RDWR);

}

void createFile_wPerm(char givenfilename[100], int flags, int mode){
    printf("File name? (max. 20 Char):\n");
    scanf("%s", &givenfilename);
    
}
 
