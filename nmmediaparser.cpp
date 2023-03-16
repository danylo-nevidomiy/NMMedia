#include "nmmediaparser.h"

NMMediaParser::NMMediaParser(const QString &url, const QString &filename, QObject *parent) : QObject(parent)
{
    downloader = new Downloader(url, filename);
    bot = new PublicationBot();
    connect(this, &NMMediaParser::load, downloader, &Downloader::getData);
    connect(downloader, &Downloader::onReady, this, &NMMediaParser::readFile);
    emit load();
}

NMMediaParser::~NMMediaParser()
{

}

void NMMediaParser::readFile()
{
    QFile file(downloader->getFileout());
    if (!file.open(QIODevice::ReadOnly))
            return;
    QTextStream in(&file);
    while (!in.atEnd()) {
            QString line = in.readLine();
            AllText += line.toStdString() + "\n";
        }
    Post p;
    CDocument doc;
    doc.parse(AllText.c_str());
    CNode c = doc.find("div.paper__title").nodeAt(0);
    std::string title = AllText.substr(c.startPos(), c.endPos() - c.startPos());
    p.title = title;
    std::cout << title << std::endl;
    std::string subtitle;
    for(auto i=0;i<3;i++){
        c = doc.find("div.paper__content h1").nodeAt(i);
        subtitle = AllText.substr(c.startPos(), c.endPos() - c.startPos());
        p.subtitles.push_back(subtitle);
        std::cout << subtitle << std::endl;
    }
    std::string text;
    auto i = 0;
    auto txt = doc.find("p").nodeAt(i++);
    while(txt.valid()){
//    std::cout << txt.valid() << std::endl;
        p.paragraphs.push_back(txt.text());
    std::cout << "txt.text = " << txt.text() << std::endl;
    if(txt.childAt(0).valid()){
        std::cout << "child = " << txt.childAt(0).text() << std::endl;
    }
    if(txt.childAt(1).valid()){
        std::cout << "child = " << txt.childAt(1).text() << std::endl;
    }
    if(txt.childAt(2).valid()){
        std::cout << "child = " << txt.childAt(2).text() << std::endl;
    }
    txt = doc.find("p").nodeAt(i++);

//    std::cout << txt.ownText() << std::endl;
//    std::cout << txt.startPos() << std::endl;
//    std::cout << txt.endPos() << std::endl;
//    text = AllText.substr(txt.startPos(), txt.endPos() - txt.startPos());
//    std::cout << text << std::endl;


    }
    bot->sendSplittedPost(p.generateSplitPost());
    bot->sendPost(p.generatePost());

//    c = doc.find("div.paper__date").nodeAt(0);
//    std::string date = AllText.substr(c.startPos(), c.endPos() - c.startPos());
//    std::cout << date << std::endl;
}

