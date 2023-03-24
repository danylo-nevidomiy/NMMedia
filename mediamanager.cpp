#include "mediamanager.h"

void MediaManager::getNewURL() const
{
    downloader->loadData(address, number_html);
}

std::string MediaManager::parseNewURL() const
{
    return address + parser->getLastNumber(number_html);
}

Post MediaManager::parseDailyNews() const
{
    return parser->readNewspaper(news_html);
}

MediaManager::MediaManager()
{
    parser = new NMMediaParser();
    downloader = new Downloader();
    bot = new PublicationBot();
    connect(this, &MediaManager::load, downloader, &Downloader::getData);
    connect(downloader, &Downloader::onReady, this, &MediaManager::processData);
}

void MediaManager::exec()
{
    downloader->loadData(address, number_html);
}

//void MediaManager::processData(){
//    qDebug() << "processData" ;
//    QCoreApplication::quit();
//}

void MediaManager::processData(QString filename)
{
    if(filename == number_html){
        actualURL = parseNewURL();
        downloader->loadData(actualURL, news_html);
    }else if(filename == news_html){
        actualPost = parseDailyNews();
        bot->publishNews(actualPost.generatePost());
    }
}
