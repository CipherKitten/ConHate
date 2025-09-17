#include "../include/bot.h"
#include "../include/sanitize.h"
#include <assert.h>
#include <concord/discord.h>
#include <concord/log.h>

static void on_message(struct discord* client, const struct discord_message* message){

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
