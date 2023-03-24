#include <QCoreApplication>
#include <iostream>
#include <Document.h>
#include <Selection.h>
#include <Node.h>

#include <tgbot/tgbot.h>

#include "nmmediaparser.h"
#include "publicationbot.h"
#include "mediamanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "Running...";
    MediaManager MM;
    MM.exec();
//    NMMediaParser parser("https://снми.рф/253/", "./res.html");
//    PublicationBot bot;
//    bot.sendPost("run");
    return a.exec();
    return 0;
}
