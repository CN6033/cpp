#include<iostream>
 

class Player
{
public:

    void play()
    {
        std::cout << "Play..." << '\n';
    }
    
    void stop()
    {
        std::cout << "Stop..." << '\n';
    }
};

class User
{
public:

    User(Player player):player_(player){}
    
    void clickPlay()
    {
        player_.play();
    }
    
    void clickStop()
    {
        player_.stop();
    }

private:
    Player player_;
};


int main()
{
    Player player;
    User user(player);
    
    //Event
    user.clickPlay();
    user.clickStop();
}
