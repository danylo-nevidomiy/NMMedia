#include "publicationbot.h"

PublicationBot::PublicationBot(const std::string token)
{

    bot = new Bot(token);
    bot->getEvents().onCommand("start", [&](Message::Ptr message) {
        bot->getApi().sendMessage(message->chat->id, "Hi!");
    });
    bot->getEvents().onCommand("news", [&](Message::Ptr message) {
        sendSplittedPost(message->chat->id, dailyNews);
    });
    bot->getApi().deleteWebhook();

}

void PublicationBot::publishNews()
{
    sendSplittedPost<std::string>("@non_mass_media", dailyNews);
}

void PublicationBot::publishNews(std::vector<std::string> splittedPost)
{
    sendSplittedPost<std::string>("@non_mass_media", splittedPost);
}

template <typename T>
void PublicationBot::sendSplittedPost(T ID, const std::vector<std::string> &post) const
{
    for(auto &p : post){
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
