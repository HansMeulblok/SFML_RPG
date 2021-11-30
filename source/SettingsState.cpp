#include "SettingsState.h"

void SettingsState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();

}

void SettingsState::initBackground()
{
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!this->backgroundTexture.loadFromFile("resources/Images/Backgrounds/desert.png"))
	{
		throw "ERROR:SETTINGS: failed to load background";
	}

	this->background.setTexture(&this->backgroundTexture);
}

void SettingsState::initFonts()
{
	if (!this->font.loadFromFile("fonts/8-BIT WONDER.ttf"))
	{
		throw("ERROR:SETTINGS: failed to load font");
	}
}

void SettingsState::initkeyBinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keyBinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void SettingsState::initGui()
{
	this->buttons["BACK"] = new GUI::Button(
		500.f, 600.f, 250.f, 50.f,
		&this->font, "Back", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 100), sf::Color(150, 150, 150, 100), sf::Color(20, 20, 20, 100));

	this->buttons["APPLY"] = new GUI::Button(
		800.f, 600.f, 250.f, 50.f,
		&this->font, "Apply", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 100), sf::Color(150, 150, 150, 100), sf::Color(20, 20, 20, 100));

	std::vector<std::string> modes_str;
	for (auto& i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + "x" + std::to_string(i.height) + "y");
	}

	this->dropDownLists["RESOLUTION"] = new GUI::DropDownList(800, 450, 200, 50, font, modes_str.data(), modes_str.size());
}

void SettingsState::initText()
{
	this->optionsText.setFont(this->font);
	this->optionsText.setPosition(sf::Vector2f(100.f, 450.f));
	this->optionsText.setCharacterSize(30);
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));
	this->optionsText.setString(
		"Resolution\n\nFullscreen\n\nVsync\n\nAntialiasing\n\n" 

	);
}


SettingsState::SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initkeyBinds();
	this->initGui();
	this->initText();
}

SettingsState::~SettingsState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	auto it2 = this->dropDownLists.begin();
	for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2)
	{
		delete it2->second;
	}
}

//Accessors

//Functions
void SettingsState::updateInput(const float & dt)
{

}

void SettingsState::updateGui(const float& dt)
{
	/*Updates all the GUI in the state and handles their functionlaity.*/
	// buttons
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	//Button functionality
	//Quit the game
	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
	}

	// apply selected settings
	if (this->buttons["APPLY"]->isPressed())
	{
		//TEST DEBUG
		this->window->create(this->modes[this->dropDownLists["RESOLUTION"]->getActiveElementId()], "test", sf::Style::Default);
	}

	// Dropdown lists
	for (auto& it : this->dropDownLists)
	{
		it.second->update(this->mousePosView, dt);
	}

	// DropDown lists functionality


}

void SettingsState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateGui(dt);

}

void SettingsState::renderGui(sf::RenderTarget& target)
{
	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}

	for (auto& it : this->dropDownLists)
	{
		it.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderGui(*target);

	target->draw(this->optionsText);

	//Debug
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);
}