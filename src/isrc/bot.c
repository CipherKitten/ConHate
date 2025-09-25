#include <pthread.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/bot.h"
#include <string.h>
#include "../include/sanitize.h"
#include <assert.h>
#include <concord/discord.h>
#include <concord/log.h>
#include <stdbool.h>

static void on_message(struct discord* client, const struct discord_message* message){
    if(message->author->bot) return;

    // TODO: make this run on a different thread
    check_for_im(message->content, message, client);
    

    // sending the meme
    pthread_t meme_send;
    struct default_message_work* msg = malloc(sizeof(struct default_message_work));
    msg->client = client;
    msg->message = message;
    pthread_create(&meme_send, NULL, send_meme, msg);

    pthread_join(meme_send, NULL);
    free(msg);
    
}

/**
 * Sends a meme. As of wrtitng this comment it only sends a picture of baby jd vance.
 *
 * this method has a 1 in 3 chance of sending a meme and it waits 5 seconds before doing so
 * */
void* send_meme(void* args){
    int fiftyfifty = rand() % 3;

    printf("%i\n\n", fiftyfifty);

    if(fiftyfifty < 2) return NULL;

<<<<<<< HEAD
=======
    char* links[] = {"https://i.kym-cdn.com/photos/images/newsfeed/002/931/607/1ff"};
    int linksLen = sizeof(links)/sizeof(links[0]);

    int linkIdx = rand() % linksLen;
    int sizeOfCurrLink = strlen(links[linkIdx]);
    int maxTextSize = 30 + sizeOfCurrLink; // 30 might be a bit over board but just in case

    char* msgContent = malloc(sizeof(char) * maxTextSize);

    snprintf(msgContent, maxTextSize, "Check this out[:](%s)", links[linkIdx]);

>>>>>>> 06f6e5e (made it use a random meme)
    struct default_message_work* msg = (struct default_message_work*)args;
    const struct discord_message* message = msg->message;
    struct discord* client = msg->client;

    sleep(5);
    struct discord_create_message params = {0};
    struct discord_ret_message ret = {0};
<<<<<<< HEAD
    params.content = "Le J.D. Vance[:](https://i.kym-cdn.com/photos/images/newsfeed/002/931/607/1ff)";
    
    discord_create_message(client, message->channel_id, &params, &ret );
=======
    params.content = msgContent;
    
    discord_create_message(client, message->channel_id, &params, &ret );
    free(msgContent);

>>>>>>> 06f6e5e (made it use a random meme)

    return NULL;
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
void check_for_im(char* message, const struct discord_message* disc_msg, struct discord* client){
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

    if((imPos+2)[0]!= ' ' && ((imPos+1)[0] == 'm' || (imPos+1)[0] == 'M')) return;


    char* name = get_name_after_im(message);
    char* reply = malloc(sizeof(char)*60);

    snprintf(reply, 60, "Hi %s, Im ConHate", name);
    
    struct discord_create_message params = {0};
    struct discord_ret_message ret_msg = {0};
    params.content = reply;
    discord_create_message(client, disc_msg->channel_id, &params, &ret_msg);

    free(reply);

}




void botMain(char* configFile){
    ccord_global_init();

    struct discord *client = discord_config_init(configFile);
    assert(client != NULL && "There was a problem creating the client");
    
    /* explicitly request the intents you need (bitwise OR) */
    discord_add_intents(client,
        DISCORD_GATEWAY_GUILDS |
        DISCORD_GATEWAY_GUILD_MESSAGES |
        DISCORD_GATEWAY_DIRECT_MESSAGES |
        DISCORD_GATEWAY_MESSAGE_CONTENT
    );

    printf("Welcome to ConHate. An hatable discord bot built with concord\n");
    discord_set_on_message_create(client, on_message);
    discord_run(client);

    discord_cleanup(client);
    ccord_global_cleanup();

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
