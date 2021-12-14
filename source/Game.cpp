#include "stdafx.h"
#include "Game.h"

// private funtions
void Game::initVariables()
{
    this->window = NULL;
    this->dt = 0.f;
    this->gridSize = 100.f;
  
}

void Game::initGraphicsSettings()
{
    this->graphicSettings.loadFromFile("Config/graphics.ini");



}

void Game::initStateData()
{
    this->stateData.window = this->window;
    this->stateData.gfxSettings = &this->graphicSettings;
    this->stateData.supportedKeys = &this->supportedKeys;
    this->stateData.states = &this->states;
    this->stateData.gridSize = this->gridSize;
}

void Game::initWindow()
{
   
    if (this->graphicSettings.fullscreen)
    {
        this->window = new sf::RenderWindow(this->graphicSettings.resolution, this->graphicSettings.title, sf::Style::Fullscreen, this->graphicSettings.contextSettings);
    }
    else
    {
        this->window = new sf::RenderWindow(this->graphicSettings.resolution, this->graphicSettings.title, sf::Style::Titlebar | sf::Style::Close, this->graphicSettings.contextSettings);
    }
    this->window->setFramerateLimit(this->graphicSettings.frameRateLimit);
    this->window->setVerticalSyncEnabled(this->graphicSettings.vSync);
}

void Game::initkeyBinds()
{
    std::ifstream ifs("Config/supported_keys.ini");
    if (ifs.is_open())
    {
        std::string key = "";
        int key_value = 0;

        while (ifs >> key >> key_value)
        {
            this->supportedKeys[key] = key_value;
        }

    }

    ifs.close();

    // debug
    for (auto i : this->supportedKeys)
    {
        std::cout << i.first << " " << i.second << std::endl;
    }
}

void Game::initStates()
{
    this->states.push(new MainMenuState(&this->stateData));
}


// Constructors / destructors
Game::Game()
{
	this->initVariables();
    this->initGraphicsSettings();
	this->initWindow();
    this->initkeyBinds();
    this->initStateData();
    this->initStates();
}

Game::~Game()
{
	delete this->window;

    while (this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}

// Accessors


// functions 

const bool Game::gameRunning() const
{
	return this->window->isOpen();
}

void Game::endApplication()
{
    std::cout << "ending app \n";
}

void Game::updateDt()
{
    // updates the dt variable with the time it took to update and render a frame.
    this->dt = this->dtClock.restart().asSeconds();

    //system("cls");
}

void Game::pollEvents()
{
    // event polling
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case::sf::Event::KeyPressed:
            //if (ev.key.code == sf::Keyboard::Key(this->supportedKeys.at("Escape")))
            //{
            //    this->window->close();
            //}
            break;
        default:
            break;
        }
    }
}

void Game::update()
{
    this->pollEvents();

    if (!this->states.empty())
    {
        this->states.top()->update(this->dt);

        if (this->states.top()->getEnding())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    else
    {
        this->endApplication();
        this->window->close();
    }

    
}

void Game::render()
{

    //- clear old frame
    //- render objects
    //- display frame in window

    this->window->clear(sf::Color(239, 213, 129, 255));

    // Render game objects here
    if (!this->states.empty())
    {
        this->states.top()->render(this->window);
    }

    this->window->display();
}

void Game::run()
{
    while (this->gameRunning())
    {
        // delta time
        this->updateDt();

        // Update
        this->update();

        // Render
        this->render();
    }

}
