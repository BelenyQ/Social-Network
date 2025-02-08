#ifndef SOCIALNETWORKWINDOW_H
#define SOCIALNETWORKWINDOW_H

#include <QMainWindow>
#include "user.h"
#include "network.h"
#include "post.h"
#include <vector>
#include <stack>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui {
class SocialNetworkWindow;
}
QT_END_NAMESPACE



class SocialNetworkWindow : public QMainWindow
{
    Q_OBJECT

public:
    SocialNetworkWindow(QWidget *parent = nullptr);
    ~SocialNetworkWindow();
    void LoginButtonClick();
    void FriendsClicked(int row,int column);
    void NewProfile();
    void Retract();
    void AddFriend(int row,int column);
    std::string getMainProfile();
    void addFriend();
    void PicClick();

private:
    Ui::SocialNetworkWindow *ui;
    Network net;
    User user;
    std::stack<std::string> users;
    std::string mainProfile;
    //Post post;
};
#endif // SOCIALNETWORKWINDOW_H
