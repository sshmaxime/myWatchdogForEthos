#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

char	**str_to_word_tab(char *str, char divide);


int main( int argc, char *argv[] )
{
    sleep(600);

    while (true) {

        FILE *fp;
        char path[1035];
        path[0] = '\0';
        bool alert = false;

        fp = popen("cat /var/run/ethos/miner_hashes.file | tail -1", "r");
        if (fp == NULL) {
            printf("Failed to run command\n");
            exit(1);
        }

        fgets(path, sizeof(path) - 1, fp);

        if (path[0] == '\0') {
            pclose(fp);
            return -1;
        }
        char **result = str_to_word_tab(path, ' ');

        int x = 0;
        while (result[x] != NULL) {
            if (strcmp(result[x], "00.00") == 0 || strcmp(result[x], "00.00\n") == 0) {
                alert = true;
            }
            x = x + 1;
        }
        x = 0;
        while (result[x] != NULL) {
            free(result[x]);
            x = x + 1;
        }

        free(result);
        pclose(fp);

        if (alert == true) {
            printf("alert spotted");
            system("reboot");
        }
        sleep(60);
    }
}