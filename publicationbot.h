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
    void sendSplittedPost(std::int64_t ID, const std::vector<std::string> &post) const;
    void setDailyNewsPost(std::vector<std::string> dailyNews);
    void run() const;
private:
    TgBot::Bot *bot;
//    std::int64_t ID = 393913297;
    std::vector<std::string> dailyNews;
};



#endif // PUBLICATIONBOT_H
