#include "parsedpost.h"

Post::Post()
{

}

const std::string &Post::generatePost()
{
    postText += boldMark + title + boldMark + "\n";
    for(auto &i : paragraphs)
    {
        postText+= i + "\n";
    }
    return postText;
}

auto Post::generateSplitPost()  -> decltype(splittedPostText)
{
    generatePost();
    if(postText.length() < maxLength){
        splittedPostText.push_back(postText);
    }else{
        int from = 0, to = 0;
        while(postText.length()-from>maxLength){
            to += maxLength;
            splittedPostText.push_back(postText.substr(from, to));
            from += maxLength;
        }
        splittedPostText.push_back(postText.substr(from, postText.length()));
    }
    return splittedPostText;
}
