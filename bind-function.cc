#include<iostream>
#include<boost/bind.hpp>
#include<boost/function.hpp>


class Button
{
public:

    boost::function<void()> onClick;
};

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
    Button playButton;
    Button stopButton;

public:

    User(Button play,Button stop)
        :playButton(play),stopButton(stop)
    {
    }
    
    void clickPlay()
    {
        playButton.onClick();
    }
    
    void clickStop()
    {
        stopButton.onClick();
    }
};


int main()
{
    //The Button class was an interface
    Button playButton, stopButton;
    Player player;
    
    //set callback function object
    playButton.onClick = boost::bind(&Player::play, &player);
    stopButton.onClick = boost::bind(&Player::stop, &player);
    User user(playButton, stopButton);
    
    //event
    user.clickPlay();
    user.clickStop();
}
