#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* getString();
void programStart();
char* XorEncrypt(char*,int);
char* InvEncrypt(char*);
char* XorDecrypt(char*,int);
int checkin();
int main()
{
    programStart();
}


void programStart()
{
    int n,flag=1;
    char* str = getString();
    printf("Do you want:\n1-Encryption\n2-Decryption\n");
    n=checkin();
    if (n==1)
    {
        int x,y;
        printf("Select type of encryption:\n");
        printf("1-XOR Encryption\n");
        printf("2-Inverter Encryption\n");
        y=checkin();
        if (y==1)
        {
            int encryptor;
            printf("Enter seed: ");
            scanf("%d",&encryptor);

            char* xen = (char*)malloc(sizeof(char*));
            xen = XorEncrypt(str,encryptor);
            printf("Encrypted phrase is: %s\n", xen);
            printf("Do you want to decrypt? (1-yes,2-no):");
            x=checkin();
            if (x==1)
            {
               printf("Decrypted phrase is: %s\n",XorDecrypt(xen,encryptor));
               return;
            }
            else
            {
                return;
            }
        }
        else if(y==2)
        {
            char* inven = (char*)malloc(sizeof(char*));
            inven = InvEncrypt(str);
            printf("Encrypted phrase is: %s\n", inven);
            printf("Do you want to decrypt? (1-yes,2-no):");
            x=checkin();
            if (x==1)
            {
               printf("Decrypted phrase is: %s\n", InvEncrypt(inven));
               return;
            }
            else
            {
                return;
            }
        }
    }
}

char* getString()
{
    int size=1;
    char c,*str;
    printf("Enter phrase: ");
    str=(char*)malloc(sizeof(char)*size);
    while((c=getchar())!='\n')
    {
        str=(char*)realloc(str,sizeof(char)*size);
        *(str+size-1)=c;
        size++;
    }
    str = realloc(str, sizeof(char)*size);
    *(str+size-1)='\0';

    return str;
}



char* XorEncrypt(char* str,int key)
{
    char temp[strlen(str)];
    for(int i=0;i<strlen(str);i++)
    {
        temp[i] = str[i]^key;
    }

    char* result = (char*)malloc(sizeof(char*));
    strcpy(result,temp);
    return result;
}

char* InvEncrypt(char* str)
{
    char temp[strlen(str)];
    for(int i=0;i<strlen(str);i++)
    {
        temp[i] = ~str[i];
    }
    char* result = (char*)malloc(sizeof(char*));
    strcpy(result,temp);
    return result;
}

char* XorDecrypt(char* str,int key)
{
    char temp[strlen(str)];
    for(int i=0;i<strlen(str);i++)
    {
        temp[i] = key^str[i];
    }
    char* result = (char*)malloc(sizeof(char*));
    strcpy(result,temp);
    return result;
}
int checkin()
{
    int flag=1, n;
    while(flag)
    {
        scanf("%d",&n);
        if (n>2 || n<1)
        {
            printf("Invalid input! Please choose between 1 and 2.\n\n");
        }
        else{flag=0;}
    }
 return n;
}
