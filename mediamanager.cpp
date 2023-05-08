#include "mediamanager.h"

void MediaManager::getNewURL() const
{
    downloader->loadData(address.toStdString(), number_html.toStdString());
}

std::string MediaManager::parseNewURL() const
{
    return address.toStdString() + parser->getLastNumber(number_html.toStdString());
}

Post MediaManager::parseDailyNews() const
{
    return parser->readNewspaper(news_html.toStdString());
}

MediaManager::MediaManager()
{
    parser = new NMMediaParser();
    downloader = new Downloader();

    timer = new QTimer(this);
    timer->setInterval(60*15*1000);
    connect(timer, &QTimer::timeout, this, &MediaManager::exec);
    connect(this, &MediaManager::load, downloader, &Downloader::getData);
    connect(downloader, &Downloader::onReady, this, &MediaManager::processData);
    settings = new QSettings(QString("configs/config.ini"), QSettings::IniFormat);
    address = settings->value("locations/host", "https://снми.рф/").toString();
    number_html = settings->value("locations/number_html", "number.html").toString();
    news_html = settings->value("locations/news_html", "news.html").toString();
    QString token = settings->value("bot/token").toString();
    bot = new PublicationBot(token.toStdString());
    actualURL = settings->value("post/actualURL").toString().toStdString();
}

MediaManager::~MediaManager()
{
    delete settings;
}

void MediaManager::exec()
{
    getNewURL();
    timer->start();
}

void MediaManager::processData(const QString filename)
{
    if(filename == number_html){
        auto url = parseNewURL();
        if(url != actualURL){
            actualURL = url;
            settings->setValue("post/actualURL", QString::fromStdString(actualURL));
            downloader->loadData(actualURL, news_html.toStdString());
        }
    }else if(filename == news_html){
        actualPost = parseDailyNews();
        bot->publishNews(actualPost.generatePost());
    }
}
