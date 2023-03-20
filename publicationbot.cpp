#include "publicationbot.h"

PublicationBot::PublicationBot()
{
    std::string token("TOKEN");
    printf("Token: %s\n", token.c_str());

    bot = new Bot(token);
    bot->getEvents().onCommand("start", [&](Message::Ptr message) {
        bot->getApi().sendMessage(message->chat->id, "Hi!");
    });
    bot->getEvents().onCommand("news", [&](Message::Ptr message) {
        sendSplittedPost(message->chat->id, dailyNews);
    });
    bot->getApi().deleteWebhook();

}

void PublicationBot::sendPost(const std::string &post)
{
//    bot->getApi().sendMessage(ID, post);
}


void PublicationBot::sendSplittedPost(std::int64_t ID, const std::vector<std::string> &post) const
{
    for(auto &p : post){
        std::cout << "field = " << p << std::endl;
        bot->getApi().sendMessage(ID, p, true, false, nullptr, "HTML");
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void PublicationBot::setDailyNewsPost(std::vector<std::string> dailyNews)
{
    this->dailyNews = std::move(dailyNews);
}

void PublicationBot::run() const
{
    TgLongPoll longPoll(*bot);
    while(true){
        longPoll.start();
    }
}
