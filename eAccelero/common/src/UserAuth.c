#ifndef MD
#define MD 5
#endif

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "global.h"
#include <stdlib.h>
#include "md5.h"
#include "CommonStructure.h"

#define TEST_BLOCK_LEN 1000
#define TEST_BLOCK_COUNT 1000


#define LENGTH_USERNAME 16
#define LENGTH_PASSWORD 16
#define LENGTH_USERINFO 32

#define AUTH_USER_NOT_FOUND     -1
#define AUTH_WRONG_PASSWORD     -2

extern void cli_log(const char *funName, int lineNo, int loglevel, const char *dataString, ...);

unsigned char buffer[32];
char digest[16];
static void MDFile PROTO_LIST ((int));
unsigned char *temp_read; 

char readUser[32];
char *readPasswd;

#define BUFSIZE 100;

#define MD_CTX MD5_CTX
#define MDInit MD5Init
#define MDUpdate MD5Update
#define MDFinal MD5Final


typedef struct userinfo {
    unsigned char username[LENGTH_USERNAME];
    unsigned char password[LENGTH_PASSWORD];
}USERINFO;

int dre_verify_UserPasswd(unsigned char *user_password,unsigned char *encryptedPassword);

int encryptPassword(unsigned char *password,unsigned char *encryptedPassword)
{
    CLI_DEBUG_LOG(" Entered ");
    int j=0;
    unsigned char *temp;

    temp = password;
    if((j=(int)strlen((char*)temp))>LENGTH_PASSWORD){
        CLI_ERROR_LOG(" password too long ");
        exit(-1);
    }
    /*generate MD5 checksum */
    MDFile(temp);

    /*Copy password to response buffer */
    memcpy(encryptedPassword,digest,16);

    CLI_DEBUG_LOG(" Exited ");
    return SUCCESS;

}

int dre_verify_Passwd(unsigned char *user_pass,unsigned char *encryptedPassword)
{
    return 0;
}
int dre_verify_UserPasswd(unsigned char *user_pass,unsigned char *encryptedPassword)
{
    int result = -1;

    temp_read = user_pass;
    /*generate MD5 checksum for the provided password*/
    MDFile(temp_read);


    /*compare the password */
    if(memcmp(digest,encryptedPassword,LENGTH_PASSWORD) == 0){
        result = 0;
        CLI_DEBUG_LOG(" Password Match ");
    }else{
        result = AUTH_WRONG_PASSWORD;
        CLI_ERROR_LOG(" Wrong Password ");
    }
    return result;
}


/* Digests a file and prints the result. */
static void MDFile (filename)
    char *filename;
{

    MD_CTX context;
    unsigned int len=strlen(filename);
    MDInit (&context);
    MDUpdate (&context, filename, len);
    MDFinal (digest, &context);
}

