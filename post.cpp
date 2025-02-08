#include <iostream>
#include <cassert>
#include <vector>
#include <sstream>
#include "post.h"

/**/
//constuctions
Post::Post(): messageId_(0),ownerId_(0),message_(""),likes_(0) {}
Post::Post(int messageId, int ownerId, std::string message, int likes): messageId_(messageId),ownerId_(ownerId),message_(message),likes_(likes){}

//getters
int Post::getMessageId(){return messageId_; }
int Post::getOwnerId(){return ownerId_;}
int Post::getLikes(){return likes_;}
std::string Post::getMessage(){return message_;}

std::string Post::getAuthor(){return "";}
bool Post::getIsPublic(){return true;}
//Notes std::to_string converts int to string
std::string Post::toString(){return message_ + " Liked by " + std::to_string(likes_) + " people."; }//Notes std::to_string converts int to string
// test_post1-9 been tested adn works hip hip horray
//-------------------------------------
//incomingpost

IncomingPost::IncomingPost():Post(0,0,"",0),isPublic_(false),author_(""){}
IncomingPost::IncomingPost(int messageId, int ownerId, std::string message, int likes, bool isPublic, std::string author):Post(messageId,ownerId,message,likes),isPublic_(isPublic),author_(author){}


std::string IncomingPost::getAuthor(){return author_;}
bool IncomingPost::getIsPublic(){return isPublic_;}



std::string IncomingPost::toString(){
    std::string privacy;
    if(getIsPublic()){
        privacy="";
    }else{
        privacy="(private)";//had trouble with spelling so much time and teh ":"
    }

    return author_ + " wrote:" + privacy + " " + getMessage() + " Liked by " + std::to_string(getLikes()) + " people.";
}
// test_ipost1-7 were tested adn worked
//test virtual 1-3  worked

