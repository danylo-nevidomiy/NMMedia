#include "publicationbot.h"

PublicationBot::PublicationBot()
{
    std::string token("TOKEN");
    printf("Token: %s\n", token.c_str());

    bot = new Bot(token);
    bot->getEvents().onCommand("start", [&](Message::Ptr message) {
        //        ID = message->chat->id;
        bot->getApi().sendMessage(message->chat->id, "Hi!");
    });
}

void PublicationBot::sendPost(const std::string &post)
{
    bot->getApi().sendMessage(ID, post);
}


