#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

char	**str_to_word_tab(char *str, char divide);

int main( int argc, char *argv[] )
{
    // Sleep 10 minutes in order to let the system boot and start mining.
    sleep(600);

    // Infinite loop because the program is suppose to run always.
    while (true) {

        FILE *fp;
        char path[1035];
        path[0] = '\0';
        bool alert = false;

        // Open the file containing the hashrate of every GPU  and execute the tail command through a pipe
        // The -1 parameter ask tail to return the last line of the file and "r" allow us to read the result.
        fp = popen("cat /var/run/ethos/miner_hashes.file | tail -1", "r");
        
        // If the command fail, exit the program.
        if (fp == NULL) {
            printf("Failed to run command\n");
            exit(1);
        }
        
        // fgets(char *s, int size, FILE *stream) read size - 1 char from stream and place them into the buffer pointed by s.
        // It stop reading after EOF or '\n'. At the end of the line '\0' is added.
        fgets(path, sizeof(path) - 1, fp);

        // Close the openened stream.
        pclose(fp);
        
        // If it didn't read anything, exit the program.
        if (path[0] == '\0') {
            return -1;
        }
        
        // Transform our array of char into and array of char*. Splitting the array of char every ' ' (space).
        char **result = str_to_word_tab(path, ' ');

        int x = 0;
        // Compare the hashrate of all GPUs and checked if one of them is mining at 00.00 Mh/s.
        while (result[x] != NULL) {
            if (strcmp(result[x], "00.00") == 0 || strcmp(result[x], "00.00\n") == 0) {
                // If you are here then one of your GPU has crashed.
                // In order to keep the memory clean we set an alert variable here in order to properly 
                // clean the memory before exiting the program.
                alert = true;
            }
            x = x + 1;
        }
        x = 0;
        // Free the allocated memory into the result variable.
        while (result[x] != NULL) {
            free(result[x]);
            x = x + 1;
        }
        // Free the result variable.
        free(result);

        // Finally check if alert have been setted.
        // If it does, it ask the system to reboot.
        if (alert == true) {
            printf("alert spotted");
            system("reboot");
        }
        // Sleep 60 seconds.
        sleep(60);
    }
}
