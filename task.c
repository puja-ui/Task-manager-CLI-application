#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//structure to store task and their priority number
struct data{
    char task[100];
    int pr;
};

/* struct data1{
    char st1[100];
    char st2[20];
}; */
//an attempt to sort the tasks according to their priority
/* void sorttxt(){
    FILE* fpsort;
    fpsort = fopen("task.txt", "w+");
    int i=0, c=0, flag = 0;
    char ch;
    while((ch=fgetc(fpsort)) != EOF){
            if(ch == '\n') c++;
    }
    struct data1 tarr[c]; 
    while((ch = fgetc(fpsort)) != EOF){
        if(ch == '[') flag = 1;
        else if(ch == ']'){
            flag = 0;
            i++;
        }
        if(ch != '[' && ch != ']'){
            if(flag == 0) *tarr[i].st1 = ch;
            else if(flag == 1) *tarr[i].st2 = ch;
        }
    }
    for(i=0;i<c;i++){
        printf("%s---%s\n", tarr[i].st1, tarr[i].st2);
    }
    fclose(fpsort);
} */

void dell(int i){
    FILE *fpsrc, *fpdemo;
    fpsrc = fopen("task.txt", "r");
    char ch;
    int c=1;
    fpdemo = fopen("demo.txt", "w"); // copying all items to a another file except the one while will be deleted
        while((ch = fgetc(fpsrc)) != EOF){ //EOF is the macro for checking End Of File, in this case it is helping to check 
            if(ch == '\n') c++;             // if the file pointer fpsrc has reached at the end of the file
            //if(c < i) {printf("task does not exist.\n"); break;} //attempt to print error msz while task doesnot exist
            if(c != i){
                fputc(ch, fpdemo);
            }
        }
    fclose(fpsrc);
    fclose(fpdemo);
    remove("task.txt"); //deleting old file
    rename("demo.txt", "task.txt"); //renaming new file
}

/* int main(){
    sorttxt();
} */
int main(int argc, char* argv[]){

    //help command working
    if(argc == 1 || strcmp(argv[1], "help") == 0){
        FILE* fpHelp;
        fpHelp = fopen("help.txt", "r"); //didn't hardcode the instruction here to make it updation friendly
        char ch;
        while((ch=fgetc(fpHelp)) != EOF){ // reading the characters of the file  help.txt with the 
            printf("%c",ch);                //file pointer fpHelp and printing on the console
        }
        printf("\n");
        fclose(fpHelp);
    }

    //add working
    else if(strcmp(argv[1], "add") == 0){
        FILE* fpadd;
        fpadd = fopen("task.txt", "ab+"); //this can be done using simply "a" mode too,
                                          //added ab+ mode cause i was working with fwrite which writes binary data
        struct data *Data = malloc(sizeof(struct data));
        Data->pr = atoi(argv[2]); //command-line input are strings so convering it to integer using atoi()
        strcpy(Data->task, argv[3]);
        fprintf(fpadd, "%s [%d]\n", Data->task, Data->pr);//using the structure Data to insert tasks
        fclose(fpadd);
    }
    
    //report working
    else if(strcmp(argv[1], "report") == 0){
        FILE *fpstat1, *fpstat2;
        fpstat1 = fopen("task.txt", "r"); 
        int c = 0;
        char ch1, ch2, ch3;
        while((ch1=fgetc(fpstat1)) != EOF){ //loop trough the content and count the number of lines 
            if(ch1 == '\n') c++;
        }
        printf("Pendeng task: %d\n\n", c);
        rewind(fpstat1);
        printf("1. ");
        int j = 1;
        while((ch1=fgetc(fpstat1)) != EOF){ 
            if(ch1 == '\n' && j<c){
                j++;
                printf("\n%d. ", j); //printing the index as the pointer fined a new line
            }
            if(ch1 != '\n') printf("%c",ch1); //open the task.txt file, read all the characters and display them in the console
        }
        fclose(fpstat1);

        fpstat2 = fopen("completed.txt", "r");
        c = 0;
        while((ch2=fgetc(fpstat2)) != EOF){ 
            if(ch2 == '\n') c++; //counting number of lines in completed.txt
        }
        printf("\n\nCompleted task: %d\n\n", c);
        rewind(fpstat2);
        printf("1. ");
        j=1;
        while((ch2=fgetc(fpstat2)) != EOF){
            if(ch2 == '\n' && j<c){
                j++;
                printf("\n%d. ", j); //printing the index as the pointer fined a new line
            }
            if(ch2 != '\n') printf("%c",ch2); //open the completed.txt file, read and display all the characters in the console
        }
        printf("\n");
        fclose(fpstat2);
    }

    //ls working
    else if(strcmp(argv[1], "ls") == 0){
        FILE* fpstat;
        fpstat = fopen("task.txt", "r");
        char ch1;
        int j=1;
        printf("1. ");
        while((ch1=fgetc(fpstat)) != EOF){
            if(ch1 == '\n'){
                j++;
                printf("\n%d. ", j); //printing index
            }
            if(ch1 != '\n') printf("%c",ch1); //printing characters(content of file.txt)
        }
        printf("\n");
        fclose(fpstat);
    }

    //done working
    else if(strcmp(argv[1], "done") == 0){
        FILE* fpsrc;
        fpsrc = fopen("task.txt", "r"); //open task.txt in read mode
        FILE* fpdest;
        fpdest = fopen("completed.txt", "a"); //open compleed.txt in append mode
        int c=1;
        char ch, ch1;
        int i = atoi(argv[2]);
        while((ch=fgetc(fpsrc)) != EOF){
            if(ch == '\n') c++;
            //if(c < i) {printf("task does not exist.\n"); break;}
            if(c == i){
                while((ch1 = fgetc(fpsrc)) != ']'){
                    fputc(ch1, fpdest); //copying the perticular item from task.txt to completed.txt
                }
                    fprintf(fpdest, "]\n");
            }
        }
        fclose(fpsrc);
        fclose(fpdest);
        dell(i); //deleting the perticular task from task.txt by calling dell() function
    }

    else if(strcmp(argv[1], "del") == 0){
        int i = atoi(argv[2]); //convertig string input to integer
        dell(i); //calling dell function
    }

    return 0;
}