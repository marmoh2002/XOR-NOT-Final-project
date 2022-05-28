#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* getString();
void programStart();
char* XorEncrypt(char*,int);
char* InvEncrypt(char*);
char* XorDecrypt(char*,int);
void encrypt(char*);
void decrypt(char*);
int checkin();
void checkNull(char*);
int main()
{
    programStart(); //starting the program in main
    return 0;
}

/*
This function is the main function
in the programو it starts
our program.
*/
void programStart()
{
    char* str = getString(); // making a pointer that points at the string entered by the user
    int n; // temporary variable to check whether the user wants encryption or decryption
    printf("Do you want:\n1-Encryption\n2-Decryption\n\n");
    n=checkin(); //calling the checkin() function that checks if the user entered the correct number
    if (n==1)
    {
        encrypt(str); //if the user enters 1 then call the encrypt function
    }
    else
    {
        decrypt(str); //if the user enters 2 then call the decrypt function
    }
    free(str);
}

/*
This function allows the user to input
a string and allocates a part of the
memory to that string
*/
char* getString()
{
    int size=1; //temporary size
    char c,*str;
    printf("Enter phrase: ");
    str=(char*)malloc(sizeof(char)*size); //memory allocates a starting amount of memory for the string
    checkNull(str); //checking if pointer was allocated correctly
    while((c=getchar())!='\n') // makes sure to end the while loop when the user starts a new line
    {
        str=(char*)realloc(str,sizeof(char)*size); //reallocates memory for every new char inputted by the user
        *(str+size-1)=c; // adds the new char to our string
        size++; // increases the size of our string by 1
    }
    str = realloc(str, sizeof(char)*size); //reallocates one more place in the memory
    *(str+size-1)='\0'; // adds NULL terminator to the end of the string

    return str; //returns the address of the pointer to where the function is called
}

/*
This function handles the encryption
with the XOR
key variable is the variable inputted
by the user and is used with the XOR
in order to encrypt the string
*/
char* XorEncrypt(char* str,int key)
{
    char temp[strlen(str)]; //creating a temporary array to store our encrypted string
    for(int i=0; i<strlen(str); i++)
    {
        temp[i] = str[i]^key; //XORing every character in the string with the key
    }

    char* result = (char*)malloc(sizeof(char)*strlen(str)); // creating the pointer to return the encrypted code to where the function is called
    checkNull(result); //checking if pointer was allocated correctly
    strcpy(result,temp); // copying the encrypted string in temp and putting it in result
    return result;
}
/*
This function handles the encryption
by inversion of bits
*/
char* InvEncrypt(char* str)
{
    char temp[strlen(str)]; //creating a temporary array to store our encrypted string
    for(int i=0; i<strlen(str); i++)
    {
        temp[i] = ~str[i]; //changing every 0 to 1 and vice versa for each bit
    }
    char* result = (char*)malloc(sizeof(char)*strlen(str)); // creating the pointer to return the encrypted code to where the function is called
    checkNull(result); //checking if pointer was allocated correctly
    strcpy(result,temp); // copying the encrypted string in temp and putting it in result
    return result;
}
/*
This function handles the decryption
with XOR
*/
char* XorDecrypt(char* str,int key)
{
    char temp[strlen(str)]; //creating a temporary array to store our encrypted string
    for(int i=0; i<strlen(str); i++)
    {
        temp[i] = key^str[i]; //XORing the key with every character in the encrypted string
    }
    char* result = (char*)malloc(sizeof(char)*strlen(str)); // creating the pointer to return the encrypted code to where the function is called
    checkNull(result); //checking if pointer was allocated correctly
    strcpy(result,temp); // copying the encrypted string in temp and putting it in result
    return result;
}
/*
This function is our main encryption
function it calls both the XOR encryption
and the inverse encryption and decides
when to call each
*/
void encrypt(char* str)
{
    int x,y; // temporary variables for checking the user input
    printf("Select type of encryption:\n1-XOR Encryption\n2-Inverter Encryption\n");
    y=checkin(); //checking whether the user input is valid or not
    if (y==1) // if the user enters 1 we use XOR encryption
    {
        int encryptor; //our key encryptor (inputted by the user)
        printf("Enter key: ");
        scanf("%d",&encryptor);

        char* xen = (char*)malloc(sizeof(char)*strlen(str)); //allocating memory to store our encrypted code
        checkNull(xen); //checking if pointer was allocated correctly
        xen = XorEncrypt(str,encryptor); //calling the XOR encryption function and storing the encrypted code in xen
        printf("Encrypted phrase is: %s\n", xen);
        printf("Do you want to decrypt? (1-yes,2-no):"); //checking whether the user wants to decrypt the code or not
        x=checkin();  //checking whether the user input is valid or not
        if (x==1) //if yes
        {
            printf("Decrypted phrase is: %s\n",XorDecrypt(xen,encryptor)); //decrypt
            free(xen);
            return;
        }
        else // if no
        {
            free(xen);
            return; //end the program
        }
    }
    else if(y==2) // if the user enters 2 we use inverse encryption
    {
        char* inven = (char*)malloc(sizeof(char)*strlen(str)); //allocating memory to store our encrypted code
        checkNull(inven); //checking if pointer was allocated correctly
        inven = InvEncrypt(str); //calling the inversion encryption function and storing the encrypted code in inven
        printf("Encrypted phrase is: %s\n", inven);
        printf("Do you want to decrypt? (1-yes,2-no):"); //checking whether the user wants to decrypt the code or not
        x=checkin();
        if (x==1) //if yes
        {
            printf("Decrypted phrase is: %s\n", InvEncrypt(inven)); //decrypt
            free(inven);
            return;
        }
        else //if no
        {
            free(inven);
            return;//end program
        }
    }

}
/*
This function is our main decryption
function it calls both the XOR decryption
and the inverse decryption and decides
when to call each
*/
void decrypt(char*str)
{
    printf("Select type of decryption:\n1-XOR Decryption\n2-Inverter Decryption\n");
    int x=checkin(); //checking whether the user input is valid or not
    if (x==1) //if user inputted 1 then we use XOR decryption
    {
        int k; //our key that is inputted by the user
        printf("Enter key: ");
        scanf("%d",&k);
        char* decrypted = (char*)malloc(sizeof(char)*strlen(str)); //allocating memory to store our decrypted code
        checkNull(decrypted); //checking if pointer was allocated correctly
        decrypted = XorDecrypt(str,k); //calling the XOR decryption function and storing the decrypted code
        printf("Decrypted phrase is: %s\n",decrypted);
        printf("Do you want to encrypt? (1-yes,2-no):"); //checking whether the user wants to encrypt the code or not
        x=checkin(); //checking whether the user input is valid or not
        if (x==1) //if yes
        {
            printf("Encrypted phrase is: %s\n",XorEncrypt(decrypted,k)); //encrypt
            free(decrypted);
            return;
        }
        else//if no
        {
            free(decrypted);
            return;//end the program
        }
        return;
    }

    else if(x==2) //if the user entered 2 then we use inversion of bits decryption
    {
        char* decrypted = (char*)malloc(sizeof(char)*strlen(str)); //allocating memory to store our decrypted code
        checkNull(decrypted); //checking if pointer was allocated correctly
        decrypted = InvEncrypt(str); //calling the inverse decryption function and storing the decrypted code note: inverse decryption and encryption use the same code
        printf("Encrypted phrase is: %s\n", decrypted);
        printf("Do you want to encrypt? (1-yes,2-no):"); //checking whether the user wants to encrypt the code or not
        x=checkin(); //checking whether the user input is valid or not
        if (x==1) //if yes
        {
            printf("Encrypted phrase is: %s\n", InvEncrypt(decrypted)); //encrypt
            free(decrypted);
            return;
        }
        else //if no
        {
            free(decrypted);
            return; //end program
        }
    }


}
/*
This function checks whether the input of the user
is valid or not
*/
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
        else
        {
            flag=0;
        }
    }
    return n;
}
/*
It is good programming practice
to check if pointers are equal
to NULL or not after malloc
operation if pointer equals NULL
we exit the program, else
continue as usual.
*/
void checkNull(char* str)
{
    if (str == NULL)
    {
        printf("An error occurred.");
        exit(0);
    }
}
