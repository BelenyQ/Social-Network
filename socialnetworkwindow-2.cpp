#include "socialnetworkwindow.h"
#include "ui_socialnetworkwindow.h"
#include <QPixmap>
#include <QFileDialog>
SocialNetworkWindow::SocialNetworkWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SocialNetworkWindow)
{
    ui->setupUi(this);
    //net.readUsers("users.txt");
    ui->ProfileLabel->setVisible(false);
    ui->FriendsTableWidget->setVisible(false);
    ui->BackButton->setVisible(false);
    ui->RecentPostLabel->setVisible(false);
    ui->SuggestedtableWidget->setVisible(false);
    ui->SuggestedFredLabel->setVisible(false);
    ui->AddFButton->setVisible(false);
    ui->ProfilePic->setVisible(false);
    ui->AddressLabel->setVisible(false);
    ui->picButton->setVisible(false);
    ui->FriendsLabel->setVisible(false);
    ui->PostLabel->setVisible(false);
    net.readUsers("/Users/belenyquiroz/Desktop/users.txt");
    net.readPosts("/Users/belenyquiroz/Desktop/posts.txt");
    net.readPicPath("/Users/belenyquiroz/Desktop/picPath.txt");
    //int i=net.getId("Aled Montes");
    //std::string UserPost=net.getUser(i);
    //QString s= QString::fromStdString(UserPost);
    //if(i==-1){
    //ui->testlabel->setText("fail to read");
    //}else{
    //ui->testlabel->setText("it reads");
    //}
    //ui->testlabel->setText(s);

    //int result=net.writeUsers(const_cast<char *>(std::string("/Users/belenyquiroz/Desktop/posts.txt").c_str()));
    //if(i==0){
    //ui->testlabel->setText("aeda");
    //}else{
    //->testlabel->setText("fail");
    //}

    connect(ui->LoginButton,&QPushButton::clicked,this,&SocialNetworkWindow::LoginButtonClick);
    connect(ui->FriendsTableWidget, &QTableWidget::cellClicked, this, &SocialNetworkWindow::FriendsClicked);
    connect(ui->BackButton, &QPushButton::clicked, this, &SocialNetworkWindow::Retract);
    connect(ui->SuggestedtableWidget, &QTableWidget::cellClicked, this, &SocialNetworkWindow::AddFriend);
    connect(ui->AddFButton, &QPushButton::clicked, this, &SocialNetworkWindow::addFriend);
    connect(ui->picButton,&QPushButton::clicked,this,&SocialNetworkWindow::PicClick);
}

SocialNetworkWindow::~SocialNetworkWindow()
{
    //here put write users adn posts
    //Any time the social network changes, the users.txt file should be updated.

    net.writeUsers(const_cast<char *>(std::string("/Users/belenyquiroz/Desktop/users.txt").c_str()));
    net.writePosts("/Users/belenyquiroz/Desktop/posts.txt");
    net.writePicPath("/Users/belenyquiroz/Desktop/picPath.txt");
    delete ui;
}


std::string SocialNetworkWindow::getMainProfile(){
    return mainProfile;
}

void SocialNetworkWindow::LoginButtonClick(){
    std::string name = (ui->NametextEdit->toPlainText()).toStdString();
    int id;
    std::set<int>Fred;
    std::vector<int>suggestFred;

    id=net.getId(name.substr(0,name.length()));


    if(id==-1){
        ui->NametextEdit->setVisible(false);
        ui->NametextEdit->setVisible(true);
    }else{
        if(users.empty()){
            mainProfile=name;
            users.push(name);
        }
        ui->Loginlabel->hide();
        ui->LoginButton->hide();
        ui->NametextEdit->hide();
        ui->ProfileLabel->setText(QString::fromStdString("My Profile"));
        ui->FriendsLabel->setVisible(true);
        ui->PostLabel->setVisible(true);

        ui->ProfileLabel->setVisible(true);
        ui->AddFButton->setVisible(false);

        //this should display friends
        ui->FriendsTableWidget->setVisible(true);
        ui->FriendsTableWidget->setColumnCount(1);
        Fred=net.getUser(id)->getFriends();
        ui->FriendsTableWidget->setRowCount(Fred.size());




        int j=0;
        for(auto i:Fred){
            User* FriendUser=net.getUser(i);
            std::string FName = FriendUser->getName();
            FName.substr(0,FName.length()-1);
            //ui->testlabel->setText(QString::fromStdString(FName));//id is shwon in testlabel and name
            ui->FriendsTableWidget->setItem(j,0,new QTableWidgetItem(QString::fromStdString(FName)));
            j++;
        }

        ui->BackButton->setVisible(false);




        //this shoudl display the users 5 posts this does not work bc it it gives me who know what, it was woking before but I dont know what happend
        ui->RecentPostLabel->setVisible(true);

        std::string UserP=net.getPostsString(id,5,true);
        //if(UserP.empty()){UserP="empty";}
        ui->RecentPostLabel->setText(QString::fromStdString(UserP));




        //Suggested friends
        //should display the suggested friends on table widget:)
        ui->SuggestedtableWidget->setVisible(true);
        ui->SuggestedFredLabel->setVisible(true);
        ui->SuggestedtableWidget->setColumnCount(1);
        ui->SuggestedFredLabel->setText(QString::fromStdString("Suggested Friends:  "));//why does it cut off ??

        int score=0;
        suggestFred = net.suggestFriends(id,score);
        int size= suggestFred.size();
        ui->SuggestedtableWidget->setRowCount(size);

        int b=0;
        for(auto i:suggestFred){
            User *us =net.getUser(i);
            std::string FFName=us->getName();
            FFName.substr(0,FFName.length());//just in case to get rid of unwanted spaces
            //ui->testlabel->setText(QString::fromStdString(FFName));
            ui->SuggestedtableWidget->setItem(b,0,new QTableWidgetItem(QString::fromStdString(FFName)));
            b++;
        }
        //add frend here after been clicked

        ui->picButton->setVisible(true);
        ui->ProfilePic->setVisible(true);

        std::string path=net.getPicPath(id);

        //ui->testlabel->setText(QString::fromStdString(path));


        QPixmap pix(QString::fromStdString(path));
        if(path=="none"){
            QPixmap pix("/Users/belenyquiroz/Desktop/defaultImage.jpeg");
            ui->ProfilePic->setPixmap(pix);
        }
        else{ui->ProfilePic->setPixmap(pix);}


    }

}






void SocialNetworkWindow::NewProfile(){
    std::set<int>NewMainFred;
    std::vector<int>suggestFred;
    std::string NewMainUser=users.top();
    ui->ProfileLabel->setText(QString::fromStdString(NewMainUser+"'s Profile"));
    ui->FriendsTableWidget->setVisible(true);
    ui->SuggestedFredLabel->setVisible(false);
    ui->FriendsTableWidget->setColumnCount(1);
    int id=net.getId(NewMainUser);
    NewMainFred=net.getUser(id)->getFriends();
    ui->FriendsTableWidget->setRowCount(NewMainFred.size());

    int j=0;
    for(auto i:NewMainFred){
        User* FriendUser=net.getUser(i);
        std::string FName = FriendUser->getName();
        FName.substr(0,FName.length());
        ui->FriendsTableWidget->setItem(j,0,new QTableWidgetItem(QString::fromStdString(FName)));
        j++;
    }
    //users.push(NewMainUser);
    ui->BackButton->setVisible(true);

    ui->SuggestedtableWidget->setVisible(false);
    ui->SuggestedFredLabel->setVisible(false);
    ui->SuggestedtableWidget->setColumnCount(1);
    ui->SuggestedFredLabel->setText(QString::fromStdString("Suggested Friends:  "));//why does it cut off ??
    ui->SuggestedFredLabel->setVisible(false);
    int score=0;
    suggestFred = net.suggestFriends(id,score);
    int size= suggestFred.size();
    ui->SuggestedtableWidget->setRowCount(size);

    int b=0;
    for(auto i:suggestFred){
        User *us =net.getUser(i);
        std::string FFName=us->getName();
        FFName.substr(0,FFName.length());//just in case to get rid of unwanted spaces
        //ui->testlabel->setText(QString::fromStdString(FFName));
        ui->SuggestedtableWidget->setItem(b,0,new QTableWidgetItem(QString::fromStdString(FFName)));
        b++;
    }
    //this should show the post but why doesnt it
    ui->RecentPostLabel->setVisible(true);
    User *curr=net.getUser(id);
    std::string UserPost=curr->getPostsString(5,true);
    //if(UserPost.empty()){UserPost="empty";}
    ui->RecentPostLabel->setText(QString::fromStdString(UserPost));
    //show we can add
    if((users.size()>2)){
        ui->AddFButton->setVisible(true);
    }else{
        ui->AddFButton->setVisible(false);
    }

    ui->picButton->setVisible(false);
    ui->picButton->setVisible(false);
    ui->ProfilePic->setVisible(true);

    std::string path=net.getPicPath(id);

    //ui->testlabel->setText(QString::fromStdString(path));
    QPixmap pix(QString::fromStdString(path));
    if(path=="none"){
        QPixmap pix("/Users/belenyquiroz/Desktop/defaultImage.jpeg");
        ui->ProfilePic->setPixmap(pix);
    }
    else{ui->ProfilePic->setPixmap(pix);}





}




void SocialNetworkWindow::FriendsClicked(int row,int column){
    QString temp= ui->FriendsTableWidget->item(row,column)->text();
    users.push(temp.toStdString());
    NewProfile();
}


void SocialNetworkWindow::Retract(){
    users.pop();//removes the last element of the vector
    std::string name= users.top();// i think i might have to use stack bc i thought the secon dot last tong should be returned as teh name

    if(users.size()==1){
        ui->NametextEdit->setPlainText(QString::fromStdString(users.top()));
        LoginButtonClick();
    }else{
        NewProfile();
    }

}

void SocialNetworkWindow::addFriend(){
    std::string s=users.top();
    //ui->testlabel->setText("addfriend yay");
    std::string m=getMainProfile();
    int i=net.addConnection(m.substr(0,m.length()-1),s);
    if(i==0){
        //ui->testlabel->setText("addfriend yay");
    }else{
        //ui->testlabel->setText("fail");
    }
}

void SocialNetworkWindow::AddFriend(int row,int column){
    QString temp=ui->SuggestedtableWidget->item(row,column)->text();
    std::string s =temp.toStdString();
    //std::string m;
    //if(users.size()==1||users.size()==0){
    //ui->testlabel->setText("mainuser profile");
    std::string m=getMainProfile();
    net.addConnection(m.substr(0,m.length()-1),s);
    LoginButtonClick();//does show the newly added conection to suggest //either way I need to put in the users.txt file

    //}//else{
    //ui->testlabel->setText("NOT mainuser profile");
    //std::string d = users.top();
    //net.addConnection(d.substr(0,d.length()-1),s);
    //NewProfile();//does not show in frends the newly added coneection to suggest :( //either way I need to put in the users.txt file

    //}
    //I need to do update but unsre how would I dot this since last time I messed up so bad
    //net.writeUsers("/path/to/your/users.txt"); how would you add the frend to the users.txt so its updated
    //int result=net.writeUsers(const_cast<char *>(std::string("users.txt").c_str()));
    //if(result==0){
    //ui->testlabel->setText("aeda");
    //}
    //ui->testlabel->setText("fail");

    //net.addConnection(mainProfile,temp.toStdString());
    //if(!(in==0)){
    //ui->testlabel->setText("aeda");//not adding connection so false
    //}

    //std::string i=std::to_string(in);
    //ui->testlabel->setText(QString::fromStdString(m.substr(0,m.length()-1)));
    //ui->testlabel->setText(QString::fromStdString(s+"x"));

}



void SocialNetworkWindow::PicClick(){
    QString filename=QFileDialog::getOpenFileName(this);
    int id= net.getId(mainProfile);
    ui->AddressLabel->setVisible(false);

    if(QString::compare(filename,QString()) !=0){
        QImage image;
        ui->ProfilePic->setVisible(true);
        //ui->AddressLabel->setVisible(true);
        bool valid = image.load(filename);
        ui->ProfilePic->setText("yup");
        if(valid){
            ui->ProfilePic->setPixmap(QPixmap::fromImage(image));
            //ui->AddressLabel->setText(filename);
             std::string path = filename.toStdString();
            net.addPicPath(id,path);
        }
    }else{
        QPixmap pix("/Users/belenyquiroz/Desktop/defaultImage.jpeg");
        ui->ProfilePic->setPixmap(pix);
    }
    LoginButtonClick();

}

