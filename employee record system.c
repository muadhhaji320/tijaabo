#include <stdio.h> ///for input output functions like printf, scanf
#include <stdlib.h>
#include <conio.h>
#include <windows.h> // shaqooyinka la xidhiidha wnds-ka ( faa`iido maleh)
#include <string.h>  ///string operations

/** List of Global Variable */
COORD coord = {0,0}; /// sare-bidix geerasha wnds-ka

/**
    function : gotoxy
    @param input: x and y coordinates
    @param output: moves the cursor in specified position of console
*/
void gotoxy(int x,int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

// bilowga guud ee code-ka 

int main()
{
    FILE *fp, *ft; /// file pointers
    char markale, dooro;

    /** qaabka loo qorayo shaqaalaha */
    struct shaqaale
    {
        char magaca[40]; ///magaca shaqaalaha
        int da; /// da`da shaqaalaha
        float mushaharka; /// mushaharka shaqaalaha
    };

    struct shaqaale sh; /// qaabka vb loo samaynayo

    char magacashaqaalaha[40]; /// s siloo kaydiyo magaca shaqaalaha

    long int recsize; /// size of each record of employee

    /** open the file in binary read and write mode
    * if the file EMP.DAT already exists then it open that file in read write mode
    * if the file doesn't exit it simply create a new copy
    */
    fp = fopen("xogta shaqaalaha","rb+");
    if(fp == NULL)
    {
        fp = fopen("xogta shaqaalaha","wb+");
        if(fp == NULL)
        {
            printf("ma furmayo file-kani");
            exit(1);
        }
    }

    /// sizeo of each record i.e. size of structure variable e
    recsize = sizeof(sh);

    /// infinite loop continues untile the break statement encounter
    while(1)
    {
        system("cls"); ///clear the console window
        gotoxy(30,10); /// move the cursor to postion 30, 10 from top-left corner
        printf("1. kudar xog"); /// option for add record
        gotoxy(30,12);
        printf("2. tax xog"); /// option for showing existing record
        gotoxy(30,14);
        printf("3. wax ka badal xog"); /// option for editing record
        gotoxy(30,16);
        printf("4. tirtir xog"); /// option for deleting record
        gotoxy(30,18);
        printf("5. kabax"); /// exit from the program
        gotoxy(30,20);
        printf("taabo dookhaaga: "); /// enter the choice 1, 2, 3, 4, 5
        fflush(stdin); /// flush the input buffer
        dooro  = getche(); /// get the input from keyboard
        switch(dooro)
        {
        case '1':  /// if user press 1
            system("cls");
            fseek(fp,0,SEEK_END); /// search the file and move cursor to end of the file
            /// here 0 indicates moving 0 distance from the end of the file

            markale = 'y';
            while(markale == 'y')  /// if user want to add another record
            {
                printf("\n Gali magaca: ");
                scanf("%s",sh.magaca);
                printf("\n Gali da`da: ");
                scanf("%d", &sh.da);
                printf("\n Gali mushaharka: ");
                scanf("%f", &sh.mushaharka);

                fwrite(&sh,recsize,1,fp); /// write the record in the file

                printf("\nAdd another record(y/n) ");
                fflush(stdin);
                markale = getche();
            }
            break;
        case '2':
            system("cls");
            rewind(fp); ///this moves file cursor to start of the file
            while(fread(&sh,recsize,1,fp)==1)  /// read the file and fetch the record one record per fetch
            {
                printf("\n%s %d %.2f",sh.magaca,sh.da,sh.mushaharka); /// print the name, age and basic salary
            }
            getch();
            break;

        case '3':  /// if user press 3 then do editing existing record
            system("cls");
            markale = 'y';
            while(markale == 'y')
            {
                printf(" Gali magaca aad rabto in aad wax ka badasho: ");
                scanf("%s", magacashaqaalaha);
                rewind(fp);
                while(fread(&sh,recsize,1,fp)==1)  /// fetch all record from file
                {
                    if(strcmp(sh.magaca,magacashaqaalaha) == 0)  ///if entered name matches with that in file
                    {
                        printf("\n Gali magaca cusub,da`da iyo mushaharka: ");
                        scanf("%s%d%f",sh.magaca,&sh.da,&sh.mushaharka);
                        fseek(fp,-recsize,SEEK_CUR); /// move the cursor 1 step back from current position
                        fwrite(&sh,recsize,1,fp); /// override the record
                        break;
                    }
                }
                printf("\n Wax ka badal xog kale (y/n)");
                fflush(stdin);
                markale = getche();
            }
            break;
        case '4':
            system("cls");
            markale = 'y';
            while(markale == 'y')
            {
                printf("\n Gali magaca aad rabto in aad tirtirto: ");
                scanf("%s",magacashaqaalaha);
                ft = fopen("Temp.dat","wb");  /// create a intermediate file for temporary storage
                rewind(fp); /// move record to starting of file
                while(fread(&sh,recsize,1,fp) == 1)  /// read all records from file
                {
                    if(strcmp(sh.magaca,magacashaqaalaha) != 0)  /// if the entered record match
                    {
                        fwrite(&sh,recsize,1,ft); /// move all records except the one that is to be deleted to temp file
                    }
                }
                fclose(fp);
                fclose(ft);
                remove("xogta.shaq"); /// remove the orginal file
                rename("Temp.dat","xogta.shaq"); /// rename the temp file to original file name
                fp = fopen("xogta.shaq", "rb+");
                printf("Delete another record(y/n)");
                fflush(stdin);
                markale = getche();
            }
            break;
        case '5':
            fclose(fp);  /// iska xidh fl-ka
            exit(0); /// ka noqo prgm-ka
        }
    }
    return 0;
}

