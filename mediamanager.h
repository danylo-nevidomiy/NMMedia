#ifndef MEDIAMANAGER_H
#define MEDIAMANAGER_H

//#include <utility>
#include <QObject>
#include <QTimer>
#include <QSettings>
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
    QTimer *timer;
    Post actualPost;
    QString address;
    QString number_html;
    QString news_html;
    QSettings *settings;
    std::string actualURL = "";
    void getNewURL() const;
    std::string parseNewURL() const;
    Post parseDailyNews() const;
public:
    MediaManager();
    ~MediaManager();
public slots:
    void processData(const QString filename);
    void exec();
signals:
    void load();
};

#endif // MEDIAMANAGER_H
