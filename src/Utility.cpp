#include "Utility.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <cmath>
#include <cassert>
#include <vector>
#include <iostream>
#include <unordered_map>


void centerOrigin(sf::Sprite& sprite)
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

void centerOrigin(sf::Text& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

void setSize(sf::Sprite& sprite, float width, float height)
{
	sf::Vector2u textureSize = sprite.getTexture()->getSize();
	sprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setScale(width / bounds.width, height / bounds.height);
}

void setSize(sf::Sprite& sprite, sf::Vector2f size)
{
	setSize(sprite, size.x, size.y);
}

float intersection(sf::FloatRect rect1, sf::FloatRect rect2) {
	float x1 = rect1.left;
	float y1 = rect1.top;
	float x2 = rect1.left + rect1.width;
	float y2 = rect1.top + rect1.height;

	float x3 = rect2.left;
	float y3 = rect2.top;
	float x4 = rect2.left + rect2.width;
	float y4 = rect2.top + rect2.height;

	float x5 = std::max(x1, x3);
	float y5 = std::max(y1, y3);
	float x6 = std::min(x2, x4);
	float y6 = std::min(y2, y4);

	if (x5 > x6 || y5 > y6) {
		return 0;
	}
	return (x6 - x5) * (y6 - y5);
}

float squaredDistance(sf::Vector2f v1, sf::Vector2f v2) {
	return (v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y)*(v1.y - v2.y);
}

void assertThrow(bool expression, std::string message) {
	if (!expression) {
		std::cout << "ERROR: " << message << "\n";
		assert(false);
	}
}

int Rand(int l, int r) {
	return rand() % (r - l + 1) + l;
}

std::vector <int> randomIntSampling(int n, int k) {
    assert(0 <= k && k <= n);
    std::vector <int> s;
    for (int i = 0; i < n; i++) {
        s.push_back(i);
    }
    std::vector <int> res = randomSampling<int>(s, k);
    sort(res.begin(), res.end());
    return res;
}

std::string keyCodeToString(sf::Keyboard::Key keyCode) {
	switch (keyCode) {
	case sf::Keyboard::A: return "A";
	case sf::Keyboard::B: return "B";
	case sf::Keyboard::C: return "C";
	case sf::Keyboard::D: return "D";
	case sf::Keyboard::E: return "E";
	case sf::Keyboard::F: return "F";
	case sf::Keyboard::G: return "G";
	case sf::Keyboard::H: return "H";
	case sf::Keyboard::I: return "I";
	case sf::Keyboard::J: return "J";
	case sf::Keyboard::K: return "K";
	case sf::Keyboard::L: return "L";
	case sf::Keyboard::M: return "M";
	case sf::Keyboard::N: return "N";
	case sf::Keyboard::O: return "O";
	case sf::Keyboard::P: return "P";
	case sf::Keyboard::Q: return "Q";
	case sf::Keyboard::R: return "R";
	case sf::Keyboard::S: return "S";
	case sf::Keyboard::T: return "T";
	case sf::Keyboard::U: return "U";
	case sf::Keyboard::V: return "V";
	case sf::Keyboard::W: return "W";
	case sf::Keyboard::X: return "X";
	case sf::Keyboard::Y: return "Y";
	case sf::Keyboard::Z: return "Z";
	case sf::Keyboard::Num0: return "0";
	case sf::Keyboard::Num1: return "1";
	case sf::Keyboard::Num2: return "2";
	case sf::Keyboard::Num3: return "3";
	case sf::Keyboard::Num4: return "4";
	case sf::Keyboard::Num5: return "5";
	case sf::Keyboard::Num6: return "6";
	case sf::Keyboard::Num7: return "7";
	case sf::Keyboard::Num8: return "8";
	case sf::Keyboard::Num9: return "9";
	case sf::Keyboard::Escape: return "Escape";
	case sf::Keyboard::LControl: return "Left Control";
	case sf::Keyboard::LShift: return "Left Shift";
	case sf::Keyboard::LAlt: return "Left Alt";
	case sf::Keyboard::LSystem: return "Left System";
	case sf::Keyboard::RControl: return "Right Control";
	case sf::Keyboard::RShift: return "Right Shift";
	case sf::Keyboard::RAlt: return "Right Alt";
	case sf::Keyboard::RSystem: return "Right System";
	case sf::Keyboard::Menu: return "Menu";
	case sf::Keyboard::LBracket: return "[";
	case sf::Keyboard::RBracket: return "]";
	case sf::Keyboard::Semicolon: return ";";
	case sf::Keyboard::Comma: return ",";
	case sf::Keyboard::Period: return ".";
	case sf::Keyboard::Quote: return "'";
	case sf::Keyboard::Slash: return "/";
	case sf::Keyboard::Backslash: return "\\";
	case sf::Keyboard::Tilde: return "~";
	case sf::Keyboard::Equal: return "=";
	case sf::Keyboard::Hyphen: return "-";
	case sf::Keyboard::Space: return "Space";
	case sf::Keyboard::Enter: return "Enter";
	case sf::Keyboard::Backspace: return "Backspace";
	case sf::Keyboard::Tab: return "Tab";
	case sf::Keyboard::PageUp: return "Page Up";
	case sf::Keyboard::PageDown: return "Page Down";
	case sf::Keyboard::End: return "End";
	case sf::Keyboard::Home: return "Home";
	case sf::Keyboard::Insert: return "Insert";
	case sf::Keyboard::Delete: return "Delete";
	case sf::Keyboard::Add: return "+";
	case sf::Keyboard::Subtract: return "-";
	case sf::Keyboard::Multiply: return "*";
	case sf::Keyboard::Divide: return "/";
	case sf::Keyboard::Left: return "Left";
	case sf::Keyboard::Right: return "Right";
	case sf::Keyboard::Up: return "Up";
	case sf::Keyboard::Down: return "Down";
	case sf::Keyboard::Numpad0: return "Numpad 0";
	case sf::Keyboard::Numpad1: return "Numpad 1";
	case sf::Keyboard::Numpad2: return "Numpad 2";
	case sf::Keyboard::Numpad3: return "Numpad 3";
	case sf::Keyboard::Numpad4: return "Numpad 4";
	case sf::Keyboard::Numpad5: return "Numpad 5";
	case sf::Keyboard::Numpad6: return "Numpad 6";
	case sf::Keyboard::Numpad7: return "Numpad 7";
	case sf::Keyboard::Numpad8: return "Numpad 8";
	case sf::Keyboard::Numpad9: return "Numpad 9";
	case sf::Keyboard::F1: return "F1";
	case sf::Keyboard::F2: return "F2";
	case sf::Keyboard::F3: return "F3";
	case sf::Keyboard::F4: return "F4";
	case sf::Keyboard::F5: return "F5";
	case sf::Keyboard::F6: return "F6";
	case sf::Keyboard::F7: return "F7";
	case sf::Keyboard::F8: return "F8";
	case sf::Keyboard::F9: return "F9";
	case sf::Keyboard::F10: return "F10";
	case sf::Keyboard::F11: return "F11";
	case sf::Keyboard::F12: return "F12";
	case sf::Keyboard::F13: return "F13";
	case sf::Keyboard::F14: return "F14";
	case sf::Keyboard::F15: return "F15";
	case sf::Keyboard::Pause: return "Pause";
	default: return "Unknown";
	}
}

sf::Keyboard::Key stringToSFMLKey(const std::string& keyString) {
	static const std::unordered_map<std::string, sf::Keyboard::Key> keyMap = {
		{"A", sf::Keyboard::A},
		{"B", sf::Keyboard::B},
		{"C", sf::Keyboard::C},
		{"D", sf::Keyboard::D},
		{"E", sf::Keyboard::E},
		{"F", sf::Keyboard::F},
		{"G", sf::Keyboard::G},
		{"H", sf::Keyboard::H},
		{"I", sf::Keyboard::I},
		{"J", sf::Keyboard::J},
		{"K", sf::Keyboard::K},
		{"L", sf::Keyboard::L},
		{"M", sf::Keyboard::M},
		{"N", sf::Keyboard::N},
		{"O", sf::Keyboard::O},
		{"P", sf::Keyboard::P},
		{"Q", sf::Keyboard::Q},
		{"R", sf::Keyboard::R},
		{"S", sf::Keyboard::S},
		{"T", sf::Keyboard::T},
		{"U", sf::Keyboard::U},
		{"V", sf::Keyboard::V},
		{"W", sf::Keyboard::W},
		{"X", sf::Keyboard::X},
		{"Y", sf::Keyboard::Y},
		{"Z", sf::Keyboard::Z},
		{"Num0", sf::Keyboard::Num0},
		{"Num1", sf::Keyboard::Num1},
		{"Num2", sf::Keyboard::Num2},
		{"Num3", sf::Keyboard::Num3},
		{"Num4", sf::Keyboard::Num4},
		{"Num5", sf::Keyboard::Num5},
		{"Num6", sf::Keyboard::Num6},
		{"Num7", sf::Keyboard::Num7},
		{"Num8", sf::Keyboard::Num8},
		{"Num9", sf::Keyboard::Num9},
		{"Escape", sf::Keyboard::Escape},
		{"LControl", sf::Keyboard::LControl},
		{"LShift", sf::Keyboard::LShift},
		{"LAlt", sf::Keyboard::LAlt},
		{"LSystem", sf::Keyboard::LSystem},
		{"RControl", sf::Keyboard::RControl},
		{"RShift", sf::Keyboard::RShift},
		{"RAlt", sf::Keyboard::RAlt},
		{"RSystem", sf::Keyboard::RSystem},
		{"Menu", sf::Keyboard::Menu},
		{"LBracket", sf::Keyboard::LBracket},
		{"RBracket", sf::Keyboard::RBracket},
		{"SemiColon", sf::Keyboard::SemiColon},
		{"Comma", sf::Keyboard::Comma},
		{"Period", sf::Keyboard::Period},
		{"Quote", sf::Keyboard::Quote},
		{"Slash", sf::Keyboard::Slash},
		{"BackSlash", sf::Keyboard::BackSlash},
		{"Tilde", sf::Keyboard::Tilde},
		{"Equal", sf::Keyboard::Equal},
		{"Dash", sf::Keyboard::Dash},
		{"Space", sf::Keyboard::Space},
		{"Return", sf::Keyboard::Return},
		{"BackSpace", sf::Keyboard::BackSpace},
		{"Tab", sf::Keyboard::Tab},
		{"PageUp", sf::Keyboard::PageUp},
		{"PageDown", sf::Keyboard::PageDown},
		{"End", sf::Keyboard::End},
		{"Home", sf::Keyboard::Home},
		{"Insert", sf::Keyboard::Insert},
		{"Delete", sf::Keyboard::Delete},
		{"Add", sf::Keyboard::Add},
		{"Subtract", sf::Keyboard::Subtract},
		{"Multiply", sf::Keyboard::Multiply},
		{"Divide", sf::Keyboard::Divide},
		{"Left", sf::Keyboard::Left},
		{"Right", sf::Keyboard::Right},
		{"Up", sf::Keyboard::Up},
		{"Down", sf::Keyboard::Down},
		{"Numpad0", sf::Keyboard::Numpad0},
		{"Numpad1", sf::Keyboard::Numpad1},
		{"Numpad2", sf::Keyboard::Numpad2},
		{"Numpad3", sf::Keyboard::Numpad3},
		{"Numpad4", sf::Keyboard::Numpad4},
		{"Numpad5", sf::Keyboard::Numpad5},
		{"Numpad6", sf::Keyboard::Numpad6},
		{"Numpad7", sf::Keyboard::Numpad7},
		{"Numpad8", sf::Keyboard::Numpad8},
		{"Numpad9", sf::Keyboard::Numpad9},
		{"F1", sf::Keyboard::F1},
		{"F2", sf::Keyboard::F2},
		{"F3", sf::Keyboard::F3},
		{"F4", sf::Keyboard::F4},
		{"F5", sf::Keyboard::F5},
		{"F6", sf::Keyboard::F6},
		{"F7", sf::Keyboard::F7},
		{"F8", sf::Keyboard::F8},
		{"F9", sf::Keyboard::F9},
		{"F10", sf::Keyboard::F10},
		{"F11", sf::Keyboard::F11},
		{"F12", sf::Keyboard::F12},
		{"F13", sf::Keyboard::F13},
		{"F14", sf::Keyboard::F14},
		{"F15", sf::Keyboard::F15},
		{"Pause", sf::Keyboard::Pause},
		{"KeyCount", sf::Keyboard::KeyCount},
		{"Unknown", sf::Keyboard::Unknown}
	};

	auto it = keyMap.find(keyString);
	if (it != keyMap.end())
	{
		return it->second;
	}
	else
	{
		return sf::Keyboard::Unknown;
	}
}