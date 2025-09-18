#ifndef BOT
#define BOT

#include <concord/discord.h>
void botMain(char* configFile);
void check_for_im(char* message, const struct discord_message* disc_msg, struct discord* client);
char* get_name_after_im(char* message);

#endif
