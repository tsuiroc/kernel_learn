/*
 * =====================================================================================
 *
 *       Filename:  char_app.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/10/2013 11:33:25 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  CUI PENG (), tsuiroc@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define READ  0
#define WRITE 1

static void cmd_help()           
{
    printf("\n1. input   rum cmd ./test -i xxxx");
    printf("\n2. display rum cmd ./test ");
    printf("\n2. help    rum cmd ./test -h");

    return ;
}

int main(int argc, char *argv[])
{
    int ch, rw = READ;
    if(argc == 1)
    {
        ch = READ;    
    }
    else
    {
        if((ch = getopt(argc, argv, "i:h")) == -1)
        {
            printf("getopt error");
            return -1;
        }
    }

    char *charp = NULL;
    switch(ch)
    {
        case 'i':
            rw = WRITE;
            charp = optarg;
            break;

        case 'h':
            cmd_help();            
            break;
    }
    
    int cui ;
    if((cui = open("/dev/cuipeng", O_RDWR)) < 0)
    {
        printf("fopen error");
        return -1;
    }

    if(rw == WRITE)
    {
        write(cui, charp, 6);
    }
    else
    {
        char buff[7] = {0};
        read(cui, buff, 6);
        printf("get string for drv:%s\n", buff);
    }
    close(cui);
    return 0;
}

