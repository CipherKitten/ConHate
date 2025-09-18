#include <stdlib.h>
#include "../include/bot.h"
#include <string.h>
#include "../include/sanitize.h"
#include <assert.h>
#include <concord/discord.h>
#include <concord/log.h>
#include <stdbool.h>

static void on_message(struct discord* client, const struct discord_message* message){
    int messageLen = strlen(message->content);
}

/**
 * Checks if a message sent is someone "saying their name"
 * and if so, it replies with "Hi <NAME> I'm ConHate"
 *
 * example:            m1: I'm hungry
 *          conhate reply: Hi hungry, I'm ConHate
 *
 * As of the writing of this comment ConHate only does this behaviour when
 * the message starts with: [im, Im, I'm, i'm]
 * */
void check_for_im(char* message){
    trimstr(&message);
    char* ims[]= {"Im", "im", "I'm", "i'm", "IM", "I'M"};
    int imsLen = sizeof(ims)/sizeof(ims[0]);
    
    char* imPos = NULL;
    for(int i = 0; i<imsLen; i++){
        imPos = strstr(message, ims[i]);

        if(imPos != NULL){
            break;
        }
        free(imPos);
    }
    if(imPos == NULL) return; 


}




void botMain(char* configFile){
    ccord_global_init();

    struct discord *client = discord_config_init(configFile);
    assert(client != NULL && "There was a problem creating the client");

    discord_add_intents(client, DISCORD_GATEWAY_MESSAGE_CONTENT | DISCORD_GATEWAY_GUILD_MESSAGES);

    printf("Welcome to ConHate. An hatable discord bot built with concord");
    discord_set_on_message_create(client, on_message);
    discord_run(client);

}

/**
 * Gets the "name" (anything that comes after the word "im"
 * */
char* get_name_after_im(char* message){
    char* name = malloc(sizeof(char) * 31); // right here I am assuming that the "name" wont have more than 30 chars
                                                  // I will have to check before since someone can just type gibberish
    char* msgFromFirstSpace = strstr(message, " ");
    while(msgFromFirstSpace[0] == ' ') msgFromFirstSpace++; // skip the spaces

    int nameIdx = 0;
    while(msgFromFirstSpace[0] != ' '){
        name[nameIdx] = msgFromFirstSpace[0];
        nameIdx++;
        msgFromFirstSpace++;

        if(nameIdx == 30){
            name[nameIdx] = '\0';
            break;
        }
    }

    if(name[nameIdx] != '\0'){
        name[nameIdx] = '\0';
    }

    return name;
}
