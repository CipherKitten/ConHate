#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/include/sanitize.h"
int main(){

    char* totrim = "    Ok       ";
    trimstr(&totrim);

    if(totrim[0] == ' '){
        printf("trim start failed");
    }

    if(totrim[strlen(totrim)-1] == ' '){
        printf("trimend failed");
    }
    return EXIT_SUCCESS;
}
