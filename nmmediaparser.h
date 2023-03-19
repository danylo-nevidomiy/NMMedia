#ifndef NMMEDIAPARSER_H
#define NMMEDIAPARSER_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QUrl>
#include <Document.h>
#include <Selection.h>
#include <Node.h>

#include <iostream>
#include <fstream>

#include "downloader.h"
#include "publicationbot.h"
#include "parsedpost.h"

class NMMediaParser : public QObject
{
    Q_OBJECT
public:
    NMMediaParser(const QString &url, const QString &filename, QObject *parent = 0);
    ~NMMediaParser();

private:
    Downloader *downloader;
    PublicationBot *bot;
    std::string AllText;
    Post todayNews;
private slots:
    void readFile();
signals:
    void load();

};

#endif // NMMEDIAPARSER_H
