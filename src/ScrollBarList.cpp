#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ScrollBar.hpp"
#include "ScrollBarList.hpp"
ScrollBarList::ScrollBarList() 
  : mScrollBars()
{
   // load mScrollBarList from text file
	std::ifstream fin("Assets/Files/Setting.txt");
	if(fin.is_open())
	{
        std::string temp1,temp2,sound_string,music_string;
		fin >> temp1 >> sound_string >> temp2 >> music_string;
        std::cout<<sound_string<<std::endl;
		
		int a = std::stoi(sound_string);
		int b = std::stoi(music_string);
		ScrollBar mSB_Sound(600,270,200,a);
		ScrollBar mSB_Music(600,370,200,b);
        mScrollBars.push_back(mSB_Sound);
        mScrollBars.push_back(mSB_Music);
}
        fin.close();
	}
    
void ScrollBarList::draw(sf::RenderWindow &window)
{
    for(int i =0;i<mScrollBars.size();i++)
    {
        mScrollBars[i].draw(window);
    }
}

void ScrollBarList::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
    for(int i=0;i<mScrollBars.size();i++)
    {
        mScrollBars[i].handleEvent(event,window);
    }
    // save to text file
    std::ofstream fout("Assets/Files/Setting.txt",std::ios::trunc);
    if(fout.is_open())
    {
        fout<<"Sound: "<<(int)mScrollBars[0].getPos()<<" "<<"Music: "<<(int)mScrollBars[1].getPos();
        fout.close();
    }

}

float ScrollBarList::getVolumeSound() const
{
    return mScrollBars[0].getValue();
}

float ScrollBarList::getVolumeMusic() const
{
    return mScrollBars[1].getValue();
}
