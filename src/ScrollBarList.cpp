#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "ScrollBar.hpp"
#include "ScrollBarList.hpp"
#include "SettingState.hpp"
#include "Utility.hpp"
ScrollBarList::ScrollBarList() {}
ScrollBarList::ScrollBarList(std::string filename) 
  : mScrollBars(), mFileName(filename)
{
   // load mScrollBarList from text file
    
	std::ifstream fin(mFileName);
	if(fin.is_open())
	{
        std::string temp1,temp2,sound_string,music_string;
		fin >> temp1 >> sound_string >> temp2 >> music_string;
        std::cout<<sound_string<<std::endl;
		
		float a = std::stof(sound_string);
		float b = std::stof(music_string);
		ScrollBar mSB_Sound(600,430,200,a * 180 + 600);
		ScrollBar mSB_Music(600,530,200,b * 180 + 600);
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

void ScrollBarList::updateFile()
{
    // Open the file in input and output modes
    std::fstream file(mFileName, std::ios::in | std::ios::out);

    assertThrow(file.is_open(), "Failed to open file.");

    // Read the first line
    std::string firstLine;
    std::getline(file, firstLine);

    // Modify the first line as needed
    // For example, appending " - Modified" to the end of the line

    // Move the file pointer back to the beginning
    file.seekp(0, std::ios::beg);

    // Write the modified first line back to the file
    file << std::fixed << std::setprecision(2) <<  "Sound: " << mScrollBars[0].getValue() << " Music: " << mScrollBars[1].getValue() << "\n";
    

    // Close the file
    file.close();
}

bool ScrollBarList::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
    bool changed = false;
    for(int i=0;i<mScrollBars.size();i++)
    {
        if (mScrollBars[i].handleEvent(event,window)) {
            updateFile();
            changed = true;
        }
    }
    return changed;
}

float ScrollBarList::getVolumeSound() const
{
    return mScrollBars[0].getValue();
}

float ScrollBarList::getVolumeMusic() const
{
    return mScrollBars[1].getValue();
}
