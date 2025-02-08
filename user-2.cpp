#include "user.h"
#include "post.h"
#include "picture.h"
//user class actual code

//constructors
User::User():id_(0),year_(0),zip_(0){}//take off friend bc dont know what to do there,can you ecen create an empty set
User::User(int ID,std::string NAME,int YEAR,int ZIP,std::set<int>FRIENDS):id_(ID),name_(NAME),year_(YEAR),zip_(ZIP),friends_(FRIENDS){};//reg

//functions
//use set for frinds so to teh set notes
void User::addFriend(int id){friends_.insert(id);}
void User::deleteFriend(int id){friends_.erase(id);}



//getters
int User::getId(){return id_;}
int User::getYear(){return year_;}
int User::getZip(){return zip_;}
std::string User::getName(){return name_;}
std::set<int>& User::getFriends(){return friends_;}


/**/

std::vector<Post*> User::getPosts(){return messages_;}

void User::addPost(Post * p){ messages_.push_back(p);}
//^^ done
//how many =limit
/**/
std::string User::getPostsString(int howMany, bool showOnlyPublic){
    std::string result;
    int Postadded=0;
    //start backwards to get highest first since inorder
    for(int i=messages_.size()-1; i>=0;i--){
        if(Postadded>=howMany){break;}


        //showOnlyPublis checks if we want to show the oublic so if true yes we do if no thn fale
        //getIspulc checksit it has been posted so tue it has and false if not
        //show and post not in pub we skip and move on
        //continue=move to next iteration
        if(showOnlyPublic && !messages_[i]->getIsPublic()){continue;}

        result=result+ messages_[i]->toString();
        result=result+"\n\n";
        Postadded++;
    }
    return result;
}
//Not done ^^^

//picture class
std::vector<Picture*> User::getPath(){return PicturePath_;}
void User::addPic(Picture* p){PicturePath_.push_back(p);}



