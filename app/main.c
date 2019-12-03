/**
 * History:
 * ================================================================
 * 2019-12-03 qing.zou created
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <getopt.h>
#include <sys/wait.h>

#define SW_VERSION  "v1.0"

int main(int argc, char **argv)
{
    int opt = 0;

    fprintf(stdout, "\n****************************** ******************************\n");
    fprintf(stdout, "*             timavc starting...                     *\n");
    fprintf(stdout, "*             version %s                                  *", SW_VERSION);
    fprintf(stdout, "\n****************************** ******************************\n\n\n");

    char *conf = NULL;
    char *type = NULL;
    while ((opt = getopt(argc, argv, "hvclt:")) != -1)
    {
        switch (opt)
        {
        case 'h':
            //help();
            return 0;
        case 'v':
            //version();
            return 0;
        case 'c':
            conf = optarg;
            break;
        case 't':
            type = optarg;
            break;
        case 'l':
            //showlog = 1;
        default:
            break;
        }
    }
    printf("type: %s\n", type);
    //signal(SIGCHLD, handler);

    load_init(argc, argv);

    load_start();

    load_done();

    return (0);
}
