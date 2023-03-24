#include "nmmediaparser.h"

NMMediaParser::NMMediaParser(QObject *parent)
{
    //    connect(this, &NMMediaParser::load, downloader, &Downloader::getData);
    //    connect(downloader, &Downloader::onReady, this, &NMMediaParser::readFile);
}

NMMediaParser::NMMediaParser(const QString &url, const QString &filename, QObject *parent) : QObject(parent)
{
    //    downloader = new Downloader(url, filename);
    //    bot = new PublicationBot();
    //    connect(this, &NMMediaParser::load, downloader, &Downloader::getData);
    //    connect(downloader, &Downloader::onReady, this, &NMMediaParser::readFile);
    //    emit load();
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

Post NMMediaParser::readNewspaper(const std::string &filename)
{
    QFile file(QString::fromStdString(filename));
    if (!file.open(QIODevice::ReadOnly))
        return Post();
    QTextStream in(&file);
    Post todayNews;
    std::string AllText;
    while (!in.atEnd()) {
        QString line = in.readLine();
        AllText += line.toStdString() + "\n";
    }
    doc.parse(AllText.c_str());
    CNode c = doc.find("div.paper__title").nodeAt(0);
    std::string title = AllText.substr(c.startPos(), c.endPos() - c.startPos());
    todayNews.pushContentItem(title, Post::TITLE);
    std::string text;
    int linesCounter = 0;
    int subtitlesCounter = 0;
    int listElemsCounter = 0;
    auto lines = doc.find("p");
    auto subtitles = doc.find("div.paper__content h1");
    auto lists = doc.find("li");
    CNode curSubT = subtitles.nodeAt(subtitlesCounter++);
    CNode curLine = lines.nodeAt(linesCounter++);
    CNode curListEl = lists.nodeAt(++listElemsCounter);
    std::string nextReadType = subTitleTag;
    while(curLine.valid()){
        if(nextReadType.substr(0, 3) == subTitleTag){
            text = AllText.substr(curSubT.startPos(), curSubT.endPos() - curSubT.startPos());
            todayNews.pushContentItem(text, Post::SUBTITLE);
            nextReadType = getNextOpenTag(AllText, curSubT.endPos());
            curSubT = subtitles.nodeAt(subtitlesCounter++);
        }else if(nextReadType == orderedListTag){
            do{
                text = AllText.substr(curListEl.startPos(), curListEl.endPos() - curListEl.startPos());
                todayNews.pushContentItem(std::to_string(listElemsCounter) + ". " + text, Post::LIST);
                auto endPos = curListEl.endPos();
                curListEl = lists.nodeAt(++listElemsCounter);
                nextReadType = getNextOpenTag(AllText, endPos);
            }while(nextReadType == orderedListElemTag);
        }else{
            text = AllText.substr(curLine.startPos(), curLine.endPos() - curLine.startPos());
            todayNews.pushContentItem(text, nextReadType);
            nextReadType = getNextOpenTag(AllText, curLine.endPos());
            curLine = lines.nodeAt(linesCounter++);
        }
    }
    return todayNews;
}

std::string NMMediaParser::getLastNumber(const std::string &filename)
{
    QFile file(QString::fromStdString(filename));
    if (file.open(QIODevice::ReadOnly)){
        std::string htmlText = "";
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            htmlText += line.toStdString() + "\n";
        }
        doc.parse(htmlText);
        CNode c = doc.find("script").nodeAt(0);
        std::string script = c.text();
        int index = script.find(basic_url, 0);
        std::cout << "index = " << index << std::endl;
        std::string number = "";
        index+=basic_url_length;
        while(std::isdigit(script[index])){
            number += script[index];
            index++;
        }
        return number;
    }
    return std::string();
}

