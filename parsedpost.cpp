#include "parsedpost.h"

Post::Post()
{

}

std::vector<std::string> Post::generatePost()
{  
    long unsigned int i=0;
    std::string message = startBIMark + content.at(i++).first + endBIMark + "\n";
    message += startUnderMark + content.at(i++).first + endUnderMark + "\n";
    for(;i<content.size();i++){
        if(content.at(i).second == SUBTITLE){
            splittedPostText.push_back(message);
            message = startUnderMark + content.at(i).first + endUnderMark + "\n";
        }else if(content.at(i).second == QUOTE){
            message+="\n";
            message+= startItalMark + content.at(i).first + endItalMark + "\n";
            message+="\n";
        }else{
            message += content.at(i).first + "\n";
        }
    }
    splittedPostText.push_back(message);
    return splittedPostText;
}

void Post::pushContentItem(const std::string &line, contentType type)
{
    content.push_back(std::make_pair(line, type));
}

void Post::pushContentItem(const std::string &line, const std::string &type)
{
    if(type == plainTextTag){
        content.push_back(std::make_pair(line, TEXT));
    }else if(type == quoteTag){
        content.push_back(std::make_pair(line, QUOTE));
    }else if(type == orderedListTag){
        content.push_back(std::make_pair(line, LIST));
    }else{
        content.push_back(std::make_pair(line, SUBTITLE));
    }
}
