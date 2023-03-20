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

const std::string NMMediaParser::getNextOpenTag(const std::string &str, size_t startPosition)
{
    const std::string StartDelims = "<";
    const std::string StopDelims = ">";
    constexpr char excludeSym = '/';
    size_t start = startPosition;
    while(!isContain(StartDelims, str[start])){
        start++;
    }
    size_t count = 1, i = start;
    while(!isContain(StopDelims, str[i])){
        i++; count++;
    }
    std::string tag = str.substr(start, count);
    if(isContain(tag, excludeSym)){
        return getNextOpenTag(str, start+count);
    }
    return tag;
}

bool NMMediaParser::isContain(const std::string &str, char c)
{
    for(auto i : str){
        if(i == c){
            return true;
        }
    }
    return false;
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

    CDocument doc;
    doc.parse(AllText.c_str());
    CNode c = doc.find("div.paper__title").nodeAt(0);
    std::string title = AllText.substr(c.startPos(), c.endPos() - c.startPos());
    todayNews.pushContentItem(title, Post::TITLE);

    std::string subtitle;
    for(auto i=0;i<3;i++){
        c = doc.find("div.paper__content h1").nodeAt(i);
        subtitle = AllText.substr(c.startPos(), c.endPos() - c.startPos());
        std::cout << "opentag = " << getNextOpenTag(AllText, c.endPos()) << std::endl;
        std::cout << "start = " << c.startPos() << "\tend = " << c.endPos() << std::endl;
        todayNews.subtitles.push_back(subtitle);
        for(int j=0;j<c.childNum();j++){
            std::cout << "child " << j << " = " << AllText.substr(c.nextSibling().startPos(), c.nextSibling().endPos() - c.nextSibling().startPos()) << std::endl;
        }
        std::cout << subtitle << std::endl;
    }
    std::string text;
    auto i = 0;
    auto txt = doc.find("p").nodeAt(i++);
    while(txt.valid()){
//    std::cout << txt.valid() << std::endl;
//        todayNews.paragraphs.push_back(txt.text());

//    std::cout << "txt.text = " << txt.text() << std::endl;
//    if(txt.childAt(0).valid()){
//        std::cout << "child = " << txt.childAt(0).text() << std::endl;
//    }
//    if(txt.childAt(1).valid()){
//        std::cout << "child = " << txt.childAt(1).text() << std::endl;
//    }
//    if(txt.childAt(2).valid()){
//        std::cout << "child = " << txt.childAt(2).text() << std::endl;
//    }

//    std::cout << "ownText = " << txt.ownText() << std::endl;
//    std::cout << txt.startPos() << std::endl;
//    std::cout << txt.endPos() << std::endl;
    text = AllText.substr(txt.startPos(), txt.endPos() - txt.startPos());
    std::cout << "opentag = " << getNextOpenTag(AllText, txt.endPos()) << std::endl;
    std::cout << "text = " << text << std::endl;
    todayNews.paragraphs.push_back(text);
    txt = doc.find("p").nodeAt(i++);


    }
    AllText = "";
//    bot->sendSplittedPost(todayNews.generateSplitPost());
//    bot->sendPost(p.generatePost());
    bot->setDailyNewsPost(todayNews.generatePost());
    bot->run();

//    c = doc.find("div.paper__date").nodeAt(0);
//    std::string date = AllText.substr(c.startPos(), c.endPos() - c.startPos());
//    std::cout << date << std::endl;
}

