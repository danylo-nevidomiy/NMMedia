#ifndef MEDIAMANAGER_H
#define MEDIAMANAGER_H

//#include <utility>
#include "QObject"
#include "nmmediaparser.h"
#include "parsedpost.h"
#include "publicationbot.h"
#include "downloader.h"

class MediaManager : public QObject
{
    Q_OBJECT
private:
    NMMediaParser* parser;
    Downloader *downloader;
    PublicationBot *bot;
    Post actualPost;
    static constexpr char address[] = "https://снми.рф/";
    static constexpr char number_html[] = "number.html";
    static constexpr char news_html[] = "news.html";
    std::string actualURL;
    void getNewURL() const;
    std::string parseNewURL() const;
    Post parseDailyNews() const;
public:
    MediaManager();
    void exec();
public slots:
//    void processData();
    void processData(QString filename);
signals:
    void load();
};

#endif // MEDIAMANAGER_H
