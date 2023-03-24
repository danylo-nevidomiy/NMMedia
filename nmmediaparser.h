#ifndef NMMEDIAPARSER_H
#define NMMEDIAPARSER_H

#include <QCoreApplication>
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
    NMMediaParser(QObject *parent = 0);
    NMMediaParser(const QString &url, const QString &filename, QObject *parent = 0);
    ~NMMediaParser();
    Post readNewspaper(const std::string &filename);
    std::string getLastNumber(const std::string &filename);
private:
//    Downloader *downloader;
//    PublicationBot *bot;
    CDocument doc;
    static const std::string getNextOpenTag(const std::string& str, size_t startPosition);
    static bool isContain(const std::string &str, char c);
    constexpr static char plainTextTag[] = "<p>";
    constexpr static char quoteTag[] = "<blockquote>";
    constexpr static char subTitleTag[] = "<h1";
    constexpr static char orderedListTag[] = "<ol>";
    constexpr static char orderedListElemTag[] = "<li>";
    constexpr static char basic_url[] = "https://xn--h1ahcp.xn--p1ai/";
    constexpr static int basic_url_length = 28;

};

#endif // NMMEDIAPARSER_H
