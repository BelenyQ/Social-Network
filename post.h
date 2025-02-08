#ifndef POST_H
#define POST_H
#include <vector>
#include <iostream>
#include <map>
#include <stack>



class Post{
public:
    //pre:
    //post:default contructor
    Post();
    //pre:takes in messid, ownerid, and messeges and like
    //post:constructor
    Post(int messageId, int ownerId, std::string message, int likes);
    //pre:
    //post:returns messegeId
    int getMessageId();
    //pre:
    //post: returns ownerId
    int getOwnerId();
    //pre:
    //post:return likes
    int getLikes();
    //pre:
    //post:reutrn mesge
    std::string getMessage();
    //pre:
    //post:returns author
    virtual std::string getAuthor();
    //pre:
    //post:returns T or F
    virtual bool getIsPublic();
    //pre:
    //post:return a string "[message_] Liked by [likes_] people." where [message_] and [likes_] are replaced by their respective values
    virtual std::string toString();//added virtual bc step3

private:
    int messageId_;
    int ownerId_;
    int likes_;
    std::string message_;

};


class IncomingPost: public Post{
public:
    //pre:
    //post:default contructor
    IncomingPost();
    //pre:takes in in messid, ownerid, and messeges and like, bool, author
    //post:constructor
    IncomingPost(int messageId, int ownerId, std::string message, int likes, bool isPublic, std::string author);
    //pre:
    //post:return a string "[author_] wrote[private]: [toString]" where [author_] is the value of author_, [toString]
    //is the value obtained by calling the Post toString method, and [private] is the empty string if isPublic_ is true, and " (private)" if isPublic_ is false.
    std::string toString();
    //pre:
    //post:retuerns author
    std::string getAuthor();
    //pre:
    //post: gets bool
    bool getIsPublic();

private:

    std::string author_;
    bool isPublic_;





};



#endif
