#ifndef PARSEDPOST_H
#define PARSEDPOST_H

#include <string>
#include <vector>
#include <iostream>

class Post
{
public:
    enum contentType{TITLE, SUBTITLE, TEXT, QUOTE, DATE};
    Post();
    std::string title;
    std::vector<std::string> subtitles;
    std::vector<std::string> paragraphs;
    std::vector<std::string> splittedPostText;
    std::string date;
    std::vector<std::string> generatePost();
    auto generateSplitPost() -> decltype(splittedPostText);
    void pushContentItem(std::string line, contentType type);
    void pushContentItem(const std::string &line, const std::string &type);
private:
    std::string postText;
    struct postContent{
        std::string line;
        contentType type;
    };
    std::vector<postContent> content;
    constexpr static char startBoldMark[] = "<b><u>";
    constexpr static char endBoldMark[] = "</u></b>";
    constexpr static auto maxLength = 4096;
    constexpr static char plainText[] = "<p>";
};

#endif // PARSEDPOST_H
