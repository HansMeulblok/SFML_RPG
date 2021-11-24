#include "Game.h"

// private funtions
void Game::initVariables()
{
    this->window = NULL;
    this->fullScreen = false;
    this->dt = 0.f;
  
}

void Game::initWindow()
{
    std::ifstream ifs("Config/window.ini");
    this->videoModes = sf::VideoMode::getFullscreenModes();
    std::string title = "None";
    sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
    bool fullscreen = false;
    unsigned framerate_limit = 120;
    bool vertical_sync_enabled = false;
    unsigned antialiasing_level = 0;

    if (ifs.is_open())
    {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> fullscreen;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
        ifs >> antialiasing_level;

    }

    ifs.close();
    this->fullScreen = fullscreen;
   

    this->windowSettings.antialiasingLevel = antialiasing_level;
   
    if (this->fullScreen)
    {
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, this->windowSettings);
    }
    else
    {
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, this->windowSettings);
    }
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
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
    this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}


// Constructors / destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
    this->initkeyBinds();
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
