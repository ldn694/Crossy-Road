#include "ScoreboardState.hpp"
#include "Utility.hpp"
#include "Foreach.hpp"
#include "ResourceHolder.hpp"
#include "StateIdentifiers.hpp"
#include"State.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>
#include <fstream>
#include <algorithm>

bool cmp(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
	return a.second > b.second;
}

class File {
private:
	std::vector<std::pair<std::string, int> > easy, medium, hard;
	std::vector < std::vector < std::pair<std::string, int> >> v = { easy,medium, hard };
	std::string path = "Assets/score/";
	std::vector<std::string> mode = { "easy.txt", "medium.txt", "hard.txt" };

public:
	static short num_mode;
	void readFile() {
		for (int i = 0; i < 3;i++) {
			std::ifstream fin(path+mode[i]);
			std::pair<std::string, int> tmp;

			while (!fin.eof()) {
				fin >> tmp.first >> tmp.second;
				if (fin.eof()) break;
				v[i].push_back(tmp);
			}

			sort(v[i].begin(), v[i].end(), cmp);

			while (v[i].size() < 5) {
				tmp.first = "";
				tmp.second = 0;
				v[i].push_back(tmp);
			}

			fin.close();
		}
	}

	void updateFile(int i, std::string name, int score) {
		if (i < 0 || i>2) return;
		std::ofstream ft(mode[i] + path, std::ios::app);
		ft << name << '\n' << score << '\n';
		ft.close();
	}

	void showScoreBoard() {
		
	}

	std::vector<std::pair<std::string,int> > getTop5(short i) {
		if (i<0|i>2) return v[0];
		return v[i];
	}
};

short File::num_mode = 0;

ScoreboardState::ScoreboardState(StateStack& stack, States::ID stateID, Context context, State::Info stateInfo)
	: State(stack, stateID, context), mOptions(), mOptionIndex(0), mClickableList(context)
{   
    sf::Texture &texture = context.textures->get(Textures::ScoreBoard_Background);
	sf::Font &font = context.fonts->get(Fonts::Bungee);

	mBackgroundSprite.setTexture(texture);
	mBackgroundSprite.setScale(1050.0f / mBackgroundSprite.getGlobalBounds().width, 600.0f / mBackgroundSprite.getGlobalBounds().height);

    std::string path = "Assets/Images/ForScore/";
	//ID
	context.textures->load(Textures::ID1, path + "1.png");
	context.textures->load(Textures::ID2, path + "2.png");
	context.textures->load(Textures::ID3, path + "3.png");
	context.textures->load(Textures::ID4, path + "4.png");
	context.textures->load(Textures::ID5, path + "5.png");

	//quit
	context.textures->load(Textures::scoreboard_quit, path + "quit.png");
	context.textures->load(Textures::scoreboard_quit_hover, path + "quit_hover.png");

	//left right
	context.textures->load(Textures::scoreboard_left, path + "left.png");
	context.textures->load(Textures::scoreboard_left_hover, path + "left_hover.png");
	context.textures->load(Textures::scoreboard_right, path + "right.png");
	context.textures->load(Textures::scoreboard_right_hover, path + "right_hover.png");

	//score name
	context.textures->load(Textures::scoreboard_name, path + "name.png");
	context.textures->load(Textures::scoreboard_name_hover, path + "name_hover.png");
	context.textures->load(Textures::scoreboard_score, path + "score.png");
	context.textures->load(Textures::scoreboard_score_hover, path + "score_hover.png");
	
	//ID
	float x = 220;
	float y = 140;
	float xp = 85;
	float yp = 110;

	mClickableList.registerClickable<Button>(Clickable::Type::Button);
	Clickable::Info info;
	info.floatList = { x, y, xp, yp, 15 };				
	info.status = Clickable::Status(true, true, true);          				
	info.textureIDList = { Textures::ID1, Textures::ID1};	    
	info.stringList = { "" };
	info.fontIDList = { Fonts::Bungee };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::ID1, info);

	info.floatList = {x, y+80, xp, yp, 15};
	info.textureIDList = { Textures::ID2, Textures::ID2};
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::ID2, info);

	info.floatList = {x, y+160, xp, yp, 15};
	info.textureIDList = { Textures::ID3, Textures::ID3};
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::ID3, info);

	info.floatList = {x, y+240, xp, yp, 15};
	info.textureIDList = { Textures::ID4, Textures::ID4};
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::ID4, info);

	info.floatList = {x, y+320, xp, yp, 15};
	info.textureIDList = { Textures::ID5, Textures::ID5};
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::ID5, info);

	//quit
	info.floatList = {30, 13, 70, 70, 15};
	info.textureIDList = { Textures::scoreboard_quit, Textures::scoreboard_quit_hover};
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::quit, info);

	//left right
	info.floatList = {70, 300, 40, 70, 15};
	info.textureIDList = { Textures::scoreboard_left, Textures::scoreboard_left_hover};
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::left, info);

	info.floatList = {880, 300, 40, 70, 15};
	info.textureIDList = { Textures::scoreboard_right, Textures::scoreboard_right_hover};
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::right, info);

	//score name
	File f;
	f.readFile();

	std::vector<std::pair<std::string,int> > top5 = f.getTop5(File::num_mode);
	std::vector<float> name = {325, 160, 280, 70, 30};
	std::vector<float> score = {650, 160, 120, 70, 30};
	std::vector<ClickableID> topname = {name1, name2, name3, name4, name5};
	std::vector<ClickableID> topscore = {score1, score2, score3, score4, score5};

	info.textureIDList = { Textures::scoreboard_name, Textures::scoreboard_name_hover};
	for (int i=0;i<5;i++) {
		info.floatList = name;
		info.stringList = {top5[i].first};
		mClickableList.addClickable(Clickable::Type::Button, topname[i], info);
		name[1]+=80;
	}
	
	info.textureIDList = { Textures::scoreboard_score, Textures::scoreboard_score_hover};
	for (int i=0;i<5;i++) {
		info.floatList = score;
		info.stringList = {std::to_string(top5[i].second)};
		if (top5[i].first == "") info.stringList = {""};
		mClickableList.addClickable(Clickable::Type::Button, topscore[i], info);
		score[1]+=80;
	}

	//mode
	/*
	std::vector<std::string> mode = {"easy.png", "medium.png", "hard.png"};
	context.textures->load(Textures::mode, path + mode[File::num_mode]);
	info.stringList ={""};
	info.floatList = {780, 40, 320, 150, 15};
	info.textureIDList = { Textures::mode, Textures::mode};
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::mode, info);
	*/

	std::vector<std::string> mode_v = {"easy", "medium", "hard"};
	sf::Text mode;
	mode.setFont(font);
	mode.setString(mode_v[File::num_mode]);
	centerOrigin(mode);
	mode.setPosition(sf::Vector2f(900, 115.f));
	mode.setScale(1.25,1.25);
	mOptions.push_back(mode);
}

void ScoreboardState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(mBackgroundSprite);

	FOREACH(const sf::Text & text, mOptions)
		window.draw(text);
	mClickableList.draw();
}

bool ScoreboardState::update(sf::Time dt)
{
	mClickableList.update(dt);
	return true;
}

bool ScoreboardState::handleEvent(const sf::Event& event)
{
	mClickableList.handleEvent(event);
	while (mClickableList.pendingAnnouncement()) {
		Clickable::Announcement announcement = mClickableList.popAnnouncement();
		if (announcement.action == Clickable::LeftPressed) {
			switch (announcement.id) {
				case ScoreboardState::ClickableID::quit: {
					requestStackPop();
					break;
				}
				case ScoreboardState::ClickableID::left: {
					File::num_mode--;
					if (File::num_mode<0) File::num_mode = 2;
					requestStackPop();
					requestStackPush(States::Scoreboard);
					break;
				}
				case ScoreboardState::ClickableID::right: {
					File::num_mode++;
					if (File::num_mode>2) File::num_mode = 0;
					requestStackPop();
					requestStackPush(States::Scoreboard);
					break;
				}
			}
		}
		else if (announcement.action == Clickable::RightPressed) {
			
		}
	}
	while (pendingNotification()) {
		State::Info info = popNotification();
		
	}
	if (event.type == sf::Event::MouseButtonPressed) {

	}
	// The demonstration Scoreboard logic
	if (event.type != sf::Event::KeyPressed)
		return false;


	return true;
}