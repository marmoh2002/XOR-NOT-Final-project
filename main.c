#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* getString();
void programStart();
char* XorEncrypt(char*,int ,int);
char* InvEncrypt(char*,int);
void XorDecrypt(char*,int,int);
int main()
{
    programStart();
}


void programStart()
{
    int n;
    char* str = getString();
    printf("Do you want:\n");
    printf("1-Encryption\n");
    printf("2-Decryption\n");
    while(1)
    {
        scanf("%d",&n);
        if (n>2 || n<1)
        {
            printf("Invalid input! Please enter 1 or 2.");
        }
        else{break;}
    }
    if (n==1)
    {
        int y;
        printf("Select type of encryption:\n");
        printf("1-XOR Encryption\n");
        printf("2-Inverter Encryption\n");
        scanf("%d",&y);
        if (y==1)
        {
            int encryptor, x;
            printf("Enter seed: ");
            scanf("%d",&encryptor);
            char* ptr=XorEncrypt(str,strlen(str),encryptor);
            printf("Do you want to decrypt? (1-yes,2-no):");
            scanf("%d",&x);
            if (x==1)
            {
                XorDecrypt(ptr,strlen(str),encryptor);
            }
        }
        else if(y==2)
        {
            InvEncrypt(str,strlen(str));
        }
    }
}

char* getString()
{
    int size=1;
    char c,*str;
    printf("Enter string:\n");
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



char* XorEncrypt(char* str,int size,int n)
{
    char enStr[size];
    char* ptr = enStr;
    for(int i=0;i<strlen(str);i++)
    {
        enStr[i] = str[i]^n;
    }
    for (int i=0; i<strlen(enStr);i++)
    {
        printf("%c",enStr[i]);
    }
    printf("\n");
    return ptr;
}


char* InvEncrypt(char* str,int size)
{
    char enStr[size];
    for(int i=0;i<strlen(str);i++)
    {
        enStr[i] = ~str[i];
    }
    for (int i=0; i<strlen(enStr);i++)
    {
        printf("%c",enStr[i]);
    }
    return enStr;
}

void XorDecrypt(char* str,int size,int n)
{
    char decStr[size];
    for(int i=0;i<strlen(str);i++)
    {
        decStr[i] = n^str[i];
    }
    for (int i=0; i<strlen(decStr);i++)
    {
        printf("%c",decStr[i]);
    }
    printf("\n");
}
