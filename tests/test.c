#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/include/sanitize.h"
#include "../src/include/bot.h"

int main(){

    printf("«««««««««««« START TRIM TEST »»»»»»»»»»»»»»»»»»»»»»» \n");
    char* totrim = "    Ok       ";
    trimstr(&totrim);

    if(totrim[0] == ' '){
        printf("trim start failed \n");
    }
    else if(totrim[strlen(totrim)-1] == ' '){
        printf("trimend failed \n");
    }
    else{
        printf("TRIM TEST PASSED  %s\n", totrim);
    }
    printf("«««««««««««««««« TRIM TEST END »»»»»»»»»»»»»»»»»»»»»»»»»» \n");

    printf("\n\n\n\n");

    printf("«««««««««««««««««««« START GET NAME AFTER IM TEST »»»»»»»»»»»»»»»»»»» \n");
    printf("\n\n");
    char* name = get_name_after_im("im     1234567890QWERTYUIO             ");
    printf("'%s' \n\n", name);
    printf("«««««««««««««««« GET NAME AFER IM TEST END »»»»»»»»»»»»»»»»»»»»»»» \n");
    return EXIT_SUCCESS;
}
