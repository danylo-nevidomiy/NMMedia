#ifndef PUBLICATIONBOT_H
#define PUBLICATIONBOT_H

#include <chrono>
#include <thread>

#include <tgbot/tgbot.h>

#include "parsedpost.h"

using namespace TgBot;

class PublicationBot
{
public:
    PublicationBot();
    void sendPost(const std::string &post);
    template <typename T>
    void sendSplittedPost(const T &post);
private:
    TgBot::Bot *bot;
    std::int64_t ID = 393913297;
};

template <typename T>
void PublicationBot::sendSplittedPost(const T &post)
{
    for(auto &p : post){
        std::cout << "field = " << p << std::endl;
        bot->getApi().sendMessage(ID, p);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

#endif // PUBLICATIONBOT_H
