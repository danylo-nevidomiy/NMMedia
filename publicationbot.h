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
    PublicationBot(const std::string token);
    void publishNews();
    void publishNews(std::vector<std::string> splittedPost);
    template <typename T>
    void sendSplittedPost(T ID, const std::vector<std::string> &post) const;
    void setDailyNewsPost(std::vector<std::string> dailyNews);
    void run() const;
private:
    TgBot::Bot *bot;
    std::vector<std::string> dailyNews;
};



#endif // PUBLICATIONBOT_H
