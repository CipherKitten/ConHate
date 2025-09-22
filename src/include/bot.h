#ifndef BOT
#define BOT

#include <concord/discord.h>
void botMain(char* configFile);
void check_for_im(char* message, const struct discord_message* disc_msg, struct discord* client);
char* get_name_after_im(char* message);
void* send_meme(void* args);

/**
 * Struct used to store values frequently used in methods that work with messages. I use this for the async crazy
 * crazy maluco coding programations im doing
 * */
struct default_message_work{
    struct discord* client;
    const struct discord_message* message;
};

#endif
