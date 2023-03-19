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
