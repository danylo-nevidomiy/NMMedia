#ifndef PARSEDPOST_H
#define PARSEDPOST_H

#include <string>
#include <vector>
#include <iostream>

class Post
{

private:
    std::string postText;

    constexpr static char boldMark[] = "**";
    constexpr static auto maxLength = 4096;
public:
    Post();
    std::string title;
    std::vector<std::string> subtitles;
    std::vector<std::string> paragraphs;
    std::vector<std::string> splittedPostText;
    std::string date;
    const std::string &generatePost();
    auto generateSplitPost() -> decltype(splittedPostText);

};

#endif // PARSEDPOST_H
