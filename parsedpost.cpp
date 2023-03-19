#include "parsedpost.h"

Post::Post()
{

}

std::vector<std::string> Post::generatePost()
{  
    std::string text = startBoldMark + title + endBoldMark + "\n";
    int totalLength = text.size();
    for(int i=0;i<paragraphs.size();i++)
    {
        const int size = paragraphs.at(i).size();
        if(totalLength+size < maxLength){
            text+=paragraphs.at(i);
            totalLength+=size;
        }else{
            splittedPostText.push_back(text);
            text = "";
            totalLength = 0;
        }
    }
    return splittedPostText;
}

auto Post::generateSplitPost()  -> decltype(splittedPostText)
{
    constexpr char delim[] = " ";
    generatePost();
    if(postText.length() < maxLength){
        splittedPostText.push_back(postText);
    }else{
        int from = 0, to = 0, cur = 0;
        while(postText.length()-from>maxLength){
            to = from;
            while((cur = postText.find(delim, to + 1)) < maxLength){
                to = cur;
            }
            splittedPostText.push_back(postText.substr(from, to));
            from = to;
        }
        splittedPostText.push_back(postText.substr(from, postText.length()));
    }
    return splittedPostText;
}
