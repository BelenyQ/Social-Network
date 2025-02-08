#ifndef USER_H
#define USER_H
#include "post.h"
#include "picture.h"
#include <iostream>
#include <string>
#include <set>


class User{
public:
    //constructors
    //pre:
    //post: default
    User();
    //pre:takes in id,name,year,zip,friends
    //post:constructor
    User(int ID,std::string NAME,int YEAR,int ZIP,std::set<int>FRIENDS);//reg
    //must add
    //functions
    //pre:takes in ID
    //post:accepting the ID of a user to add as a friend
    void addFriend(int id);
    //pre:takes in ID
    //post:accepting the ID of a user to delete as a friend
    void deleteFriend(int id);

    //getters
    //pre:
    //post:returns id
    int getId();
    //pre:
    //post:returns year
    int getYear();
    //pre:
    //post:returns zip code
    int getZip();
    //pre:
    //post:returns name
    std::string getName();
    //pre:
    //post:return friend
    std::set<int>&getFriends();

    //
    //pre:
    //post;add post to messeges vector
    void addPost(Post * p);
    //pre:
    //post;get posts
    std::vector<Post*> getPosts();
    //pre:takes in int of how many adn bool and depending to see if want public or no
    //post;returns a string that holds the most recent howMany posts (or all posts, if there are less than howMany), according to the following instructions.
    std::string getPostsString(int howMany, bool showOnlyPublic);
    //picture class
    std::vector<Picture*>getPath();
    void addPic(Picture* p);



private:
    // variables
    int id_;
    int year_;
    int zip_;
    std::string name_;
    std::set<int>friends_;
    //new
    std::vector<Post*> messages_;

    //pictures class
    std::vector<Picture*> PicturePath_;



};


#endif
