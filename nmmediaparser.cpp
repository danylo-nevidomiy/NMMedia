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
    std::string text;
    int linesCounter = 0;
    int subtitlesCounter = 0;
    auto lines = doc.find("p");
    auto subtitles = doc.find("div.paper__content h1");
    CNode subT = subtitles.nodeAt(subtitlesCounter++);
    CNode curLine = lines.nodeAt(linesCounter++);
    std::string nextReadType = subTitleTag;
    while(curLine.valid()){
        if(nextReadType.substr(0, 3) == subTitleTag){
            text = AllText.substr(subT.startPos(), subT.endPos() - subT.startPos());
            todayNews.pushContentItem(text, Post::SUBTITLE);
            nextReadType = getNextOpenTag(AllText, subT.endPos());
            subT = subtitles.nodeAt(subtitlesCounter++);
        }else{
            text = AllText.substr(curLine.startPos(), curLine.endPos() - curLine.startPos());
            todayNews.pushContentItem(text, nextReadType);
            nextReadType = getNextOpenTag(AllText, curLine.endPos());
            curLine = lines.nodeAt(linesCounter++);
        }
    }
    AllText = "";
    bot->setDailyNewsPost(todayNews.generatePost());
    bot->run();

    //    c = doc.find("div.paper__date").nodeAt(0);
    //    std::string date = AllText.substr(c.startPos(), c.endPos() - c.startPos());
    //    std::cout << date << std::endl;
}

