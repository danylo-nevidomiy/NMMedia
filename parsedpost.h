#ifndef PARSEDPOST_H
#define PARSEDPOST_H

#include <string>
#include <vector>
#include <iostream>

class Post
{
public:
    enum contentType{TITLE, SUBTITLE, TEXT, QUOTE, LIST, DATE};
    Post();
    std::vector<std::string> splittedPostText;
    constexpr static char plainTextTag[] = "<p>";
    constexpr static char quoteTag[] = "<blockquote>";
    constexpr static char orderedListTag[] = "<ol>";
    std::vector<std::string> generatePost();
    void pushContentItem(const std::string &line, contentType type);
    void pushContentItem(const std::string &line, const std::string &type);
private:
    std::vector<std::pair<std::string, contentType>> content;
    constexpr static char startBIMark[] = "<b><u>";
    constexpr static char endBIMark[] = "</u></b>";
    constexpr static char startItalMark[] = "<i>";
    constexpr static char endItalMark[] = "</i>";
    constexpr static char startUnderMark[] = "<u>";
    constexpr static char endUnderMark[] = "</u>";
    constexpr static auto maxLength = 4096;

};

#endif // PARSEDPOST_H
