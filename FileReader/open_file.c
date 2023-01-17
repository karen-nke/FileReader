#include <stdio.h>

//Task 1 - Reading a text file by setting the offset pointer

int main(){

    //Open file "test.txt"
    FILE * fpointer;
    fpointer = fopen("test.txt","r");

    // Set Byte Offset of the Document
    // Hello I love to drink coffee
    fseek(fpointer,3,SEEK_SET);
    int ch;
    printf("================================================================");
    printf("\n ==> This is the display of the text message offset by 3 <==\n");
    printf("================================================================\n");

    // If the pointer havent reach the end of the file
    while((ch=fgetc(fpointer))!=EOF)
   
    putchar(ch); //Display the message

    fclose(fpointer);
    return 0;

}