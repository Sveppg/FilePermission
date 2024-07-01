#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/ptrace.h>

//Costum Header Files loc. /HEADER_FILES
#include "escapesequenzen.h"
//function definiton
mode_t collectPermissions();
void getMenu();

int main(int argc, char **argv){
    int Menu;
    mode_t mode;
    CLEAR;
    HOME;
        if(argc != 2){ //Check for argument count
            printf("Too few Arguments!! Please Add a File...\n");
            printf("The one you want to edit or the name of the new File -> with formate ending: exp. Foo.txt\n");
            exit(EXIT_FAILURE);
        }

        printf("_________________________________________________________\n");
        printf("| 1. Change Permissions for existing File?              |\n");
        printf("| 2. Create a new File with specific Permissions        |\n");
        printf("|                                                       |\n");
        printf("|                  1. or 2.?                            |\n");
        printf("|                                                       |\n");
        printf("|_______________________________________________________|\n");
        
        /*
        *   This if Condition will run the openFile_chPerm Func 
        */
        
        printf("Your Choice?:"); scanf("%i", &Menu);
    
        if(Menu == 1){
        mode_t umask_arg;
        umask_arg = umask(002); // set umask to 002 for efficient permission passing    
        mode = collectPermissions();
            if(chmod(argv[1], mode)){
                perror(argv[1]);
                exit(EXIT_FAILURE);
            }
            else{
                printf("%.100s permissions are changed to %o\n", argv[1], mode);
            }
            umask(umask_arg);
        }
        /*
        *   This else if Condition will run the createFile_wPerm Func 
        *    and set or reset the umask 
        */
        else if(Menu == 2){
            mode_t umask_arg; // same as above
            umask_arg = umask(002);
            mode = collectPermissions();
            int fd = open(argv[1], O_CREAT | O_WRONLY, mode);
            if(fd == -1){
                perror("Failed to create File");
                exit(EXIT_FAILURE);
            }
            else{
		printf("\n");
                printf("%.100s: File created with permissions %o\n", argv[1], mode);
            }
            close(fd);
            umask(umask_arg);
        }
        else{
            printf("Your UserInput is insufficent... Exit\n");
	    exit(EXIT_FAILURE); 
        }
    return 0;
}

void getMenu(){
    FORECOLOR_VIOLETT;
    printf("_________________________________________________________\n");
    printf("|Select file permissions to set (bitwise OR will be used)|:\n");
    printf("|________________________________________________________|\n");
    printf("| 1. Read by owner (S_IRUSR)                             |\n");
    printf("| 2. Write by owner (S_IWUSR)                            |\n");
    printf("| 3. Execute by owner (S_IXUSR)                          |\n");
    printf("| 123. All of them: (RWX)                                |\n");
    printf("|                                                        |\n");
    printf("| 4. Read by group (S_IRGRP)                             |\n");
    printf("| 5. Write by group (S_IWGRP)                            |\n");
    printf("| 6. Execute by group (S_IXGRP)                          |\n");
    printf("| 456. All of them: (RWX)                                |\n");
    printf("|                                                        |\n");
    printf("| 7. Read by Other (S_IROTH)                             |\n");
    printf("| 8. Write by Other (S_IWOTH)                            |\n");
    printf("| 9. Execute by Other (S_IXOTH)                          |\n");
    printf("| 789. All of them: (RWX)                                |\n");
    printf("|________________________________________________________|\n");
    FORECOLOR_YELLOW;
    printf("Enter choice (0 to end the program): \n");
    FORECOLOR_WHITE;
}

mode_t collectPermissions(void){
    int choice;
    mode_t mode = 0;
    getMenu();
    while(scanf("%d", &choice) && choice != 0)
    {
        switch(choice){
            case 1: mode |= S_IRUSR; break;
            case 2: mode |= S_IWUSR; break;
            case 3: mode |= S_IXUSR; break;
            case 123: mode |= S_IRWXU; break;
            case 4: mode |= S_IRGRP; break;
            case 5: mode |= S_IWGRP; break;
            case 6: mode |= S_IXGRP; break;
            case 456: mode |= S_IRWXG; break;
            case 7: mode |= S_IROTH; break;
            case 8: mode |= S_IWOTH; break;
            case 9: mode |= S_IXOTH; break;
            case 789: mode |= S_IRWXO; break;
            default: printf("Invalid Choice. Please try again...\n"); break;
        }
        if(choice != 0){ 
            HOME;
            CLEAR; 
                printf("Changes applied...\n");
		printf("\n");
                printf("Type 0 to end the programm\n");
        }
    }    
    return mode;
}
