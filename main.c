#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int concat(int a, int b)
{

    char s1[20];
    char s2[20];

    // Convert both the integers to string
    sprintf(s1, "%d", a);
    sprintf(s2, "%d", b);

    // Concatenate both strings
    strcat(s1, s2);

    // Convert the concatenated string
    // to integer
    int c = atoi(s1);

    // return the formed integer
    return c;
}

int key_gen()
{
    srand(time(0));
    char c = (rand() % 15 + 33);
    char a = (rand() % 26 + 65);
    char b = (rand() % 3 + 97);
    int d = (rand() % 900 + 100);
    int first = (int)a;
    int second = (int)b;
    int third = (int)c;
    int final1 = concat(third, d);
    int final2 = concat(first, second);
    int ultimate = concat(final2, final1);
    printf("Key is : %c%c%c%d", a, b, c, d);
    return ultimate;
}

void rename_()
{
    char newname[100];
    printf("Rename the new encrypted file\n");
    printf("Enter the name: ");
    scanf("%s", newname);
    rename("temp.txt", newname);
}

int encrypt()
{
    char fname[200], ch;
    FILE *fps, *fpt;
    printf("Enter Filename: ");
    scanf("%s", fname);
    fps = fopen(fname, "r");
    if (fps == NULL)
    {
        printf("File doesn't exist\n");
        return 0;
    }
    fpt = fopen("temp.txt", "w");
    if (fpt == NULL)
        return 0;
    ch = fgetc(fps);
    // srand(time(0));
    // int key;
    int key = key_gen();
    printf("\n");

    while (ch != EOF)
    {
        ch = ch + key;
        fputc(ch, fpt);
        ch = fgetc(fps);
    }
    fclose(fps);
    fclose(fpt);
    fps = fopen(fname, "w");
    if (fps == NULL)
        return 0;
    fpt = fopen("temp.txt", "r");
    if (fpt == NULL)
        return 0;
    ch = fgetc(fpt);
    while (ch != EOF)
    {
        ch = fputc(ch, fps);
        ch = fgetc(fpt);
    }

    // char aux[100];
    // strcpy(aux, fname);
    // strtok(aux, ".");
    // strcat(aux, "e.txt");

    fclose(fps);
    fclose(fpt);
    rename_();
    printf("File %s Encrypted Successfully!\n", fname);
}

int decrypt()
{
    char fname[20], ch;
    FILE *fps;
    
    printf("Enter Filename: ");
    scanf("%s", fname);
    
    fps = fopen(fname, "r");
    if (fps == NULL)
    {
        printf("File doesn't exist\n");
        return 0;
    }
    
    FILE* fpt=fopen("temp.txt","w");
    if (fpt == NULL)
    {
        printf("File doesn't exist\n");
        return 0;
    }
    
    char c=fgetc(fps);
    while (c != EOF)
    {
        fputc(c, fpt);
        c = fgetc(fps);
    }
  
    fclose(fps);
    fclose(fpt);
    
    FILE* fpt2=fopen("temp.txt","r");
    if (fpt2 == NULL)
    {
        printf("File doesn't exist\n");
        return 0;
    }
    
    FILE* fps2=fopen(fname,"w");
    if (fps == NULL)
    {
        printf("File doesn't exist\n");
        return 0;
    }

    char key[20];
    printf("Enter the key: ");
    scanf("%s", key);
    int key1 = (int)key[0];
    int key2 = (int)key[1];
    int key3 = (int)key[2];
    char number[3];
    number[0] = key[3];
    number[1] = key[4];
    number[2] = key[5];
    int key4 = atoi(number);
    int final1_ = concat(key1, key2);
    int final2_ = concat(key3, key4);
    int result = concat(final1_, final2_);

    ch = fgetc(fpt2);
    while (ch != EOF)
    {
        ch = ch - result;
        fputc(ch, fps2);
        ch = fgetc(fpt2);
    }

    fclose(fps2);
    fclose(fpt2);

    printf("File %s Decrypted Successfully!\n", fname);
    printf("Thank you for using our service\n");
    remove("temp.txt");
}

int main()
{
    int choice;
    printf("*********************** WELCOME TO SECURITY SOLUTIONS **************************\n");
    do
    {
        choice = 0;
        printf("_________________ Select the number of the operation you want to Perform _________________\n");
        printf("\t1.file encryption\n");
        printf("\t2.file decryption\n");
        printf("\t3.exit\n");
        scanf("\t%d", &choice);
        switch (choice)
        {
        case 1:
            encrypt();
            printf("------------------------------------------------------------------------------------------------\n");
            break;
        case 2:
            decrypt();
            printf("------------------------------------------------------------------------------------------------\n");
            break;
        default:
            exit(0);
        }
    } while (choice < 4);

    return 0;
}