#include <iostream>
#include "GameClasses.h"

// Private Functions
void Game::initializeVariables()
{

	this->window = nullptr;

	// Game Logic
	this->startingHealth = 3;
	this->startingPoints = 0;
	this->points = startingPoints;
	this->enemySpawnTimerMax = 50.0f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 20;
	this->playerHealth = startingHealth;


}

void Game::initializeWindow()
{

	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "2D Mouse Control", sf::Style::Titlebar | sf::Style::Close);
	this->window->setVerticalSyncEnabled(true);
	

}

void Game::initializeFont()
{
	this->textFont.loadFromFile("Fonts/Akira.otf");
}

void Game::initializeEnemies() 
{
	this->enemyRectangle.setPosition(sf::Vector2f(100.0f, 100.0f));
	this->enemyRectangle.setSize(sf::Vector2f(35.0f, 35.0f));
	this->enemyRectangle.setFillColor(sf::Color::Green);
	this->enemyRectangle.setOutlineColor(sf::Color::Cyan);
	this->enemyRectangle.setOutlineThickness(1.0f);
}


// Constructors / Destructors

Game::Game() 
{
	this->initializeVariables();
	this->initializeWindow();
	this->initializeEnemies();
	this->initializeFont();
}

Game::~Game() 
{
	delete this->window;
}

const bool Game::getWindowIsOpen() const 
{
	return this->window->isOpen();
}

//Functions

void Game::renderUserInterface() {
	// Lives
	this->playerHealthDisplay.setString("Lives: " + std::to_string(playerHealth));
	this->playerHealthDisplay.setFont(textFont);
	this->playerHealthDisplay.setCharacterSize(20);
	this->playerHealthDisplay.setFillColor(sf::Color::White);
	this->window->draw(this->playerHealthDisplay);

	// Points
	this->playerPointsDisplay.setString("Points: " + std::to_string(points));
	this->playerPointsDisplay.setFont(textFont);
	this->playerPointsDisplay.setCharacterSize(20);
	this->playerPointsDisplay.setOrigin(sf::Vector2f(0.0f, -20.0f));
	this->playerPointsDisplay.setFillColor(sf::Color::White);
	this->window->draw(this->playerPointsDisplay);
}

void Game::spawnEnemies()
{
	/*
		@return void

		Spawns enemies and sets their properties and positions.
		- Sets a random position
		- Sets a random colour.
		- Adds enemy to the vector
	*/

	this->enemyRectangle.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemyRectangle.getSize().x)),
		0.0f
	);

	this->enemyRectangle.setFillColor(sf::Color::Red);

	// Spawns the enemy
	Enemies.push_back(this->enemyRectangle);



}

void Game::UpdateEnemies() 
{
	/*
		@return void

		-	Updates the enemy spawn timer and spawns enemies 
			when the total enemies is smaller than the maximum
		-	Moves the enemy position
	*/

	// Updating the timer for enemy spawning
	if (this->Enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax) 
		{
			// Spawn the enemy and reset the timer
			this->spawnEnemies();
			this->enemySpawnTimer = 0.0f;
		}
		else
			this->enemySpawnTimer += 1.0f;
	}


	/* For every enemy in the vector, move on the Y-axis.
		Check if the enemy is out of bounds and if so, delete the game object */
	for (int i = 0; i < Enemies.size(); i++) {
		Enemies[i].move(sf::Vector2f(0.0f, 1.0f));

		if (this->Enemies[i].getPosition().y > 600) {
			this->Enemies.erase(Enemies.begin() + i);
			if (this->playerHealth != 0) {
				this->playerHealth -= 1;
			}
		}
	}
}



void Game::RenderEnemies() 
{
	// Rendering all the enemies;
	for (auto	&e : this->Enemies) {
		this->window->draw(e);
	}
}

bool Game::gameOver() {
	if (playerHealth == 0) {
		return true;
	}

	return false;
}

void Game::restart() {
	this->playerHealth = this->startingHealth;
	this->points = this->startingPoints;
	this->Enemies.clear();
}


void Game::UpdateMousePosition()
{
	/*
	@return void

	Updates the mouse positions:
		Mouse position relative to the window (Vector2i)
	*/
	cursorXPos = sf::Mouse::getPosition(*this->window).x;
	cursorYPos = sf::Mouse::getPosition(*this->window).y;
	cursorPos = sf::Vector2f(cursorXPos, cursorYPos);
}

void Game::UpdatePollEvents() 
{

	// Event polling
	while (this->window->pollEvent(event))
	{
		switch (event.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				this->window->close();
			if (event.key.code == sf::Keyboard::R && this->gameOver() == true) {
				this->restart();
			}

		case sf::Event::MouseButtonPressed:
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				for (int i = 0; i < Enemies.size(); i++) {
					if (Enemies[i].getGlobalBounds().contains(sf::Vector2f(cursorPos))) {
						Enemies.erase(Enemies.begin() + i);
						this->points++;
					}
				}
			}
			break;


		}
	}
}
void Game::debugMessages()
{

	//	std::cout << "Mouse Position X: " << this->cursorXPos << " Mouse Position Y: " << this->cursorYPos << std::endl;
	//	std::cout << "Enemies: " << Enemies.size() << std::endl;
	//	std::cout << "Remaining Lives: " << playerHealth << std::endl;
	//	if (this->gameOver()) { std::cout << "Success!" << std::endl; }
}

void Game::endScreen()
{
	this->EndScreenDisplay.setString(sf::String("test"));

	// End screen display
	this->EndScreenDisplay.setString("Game Over! You got a total of " + std::to_string(points) + " points!");
	this->EndScreenDisplay.setFont(textFont);
	this->EndScreenDisplay.setCharacterSize(20);
	this->EndScreenDisplay.setOrigin(sf::Vector2f(-90.0f, -300.0f));
	this->EndScreenDisplay.setFillColor(sf::Color::White);

	this->EndScreenRestart.setString("Type R to restart");
	this->EndScreenRestart.setFont(textFont);
	this->EndScreenRestart.setCharacterSize(20);
	this->EndScreenRestart.setOrigin(sf::Vector2f(-90.0f, -350.0f));
	this->EndScreenRestart.setFillColor(sf::Color::White);

}

// Functions
void Game::Update()
{
	this->UpdateMousePosition();
	this->UpdatePollEvents();
	this->UpdateEnemies();
	this->debugMessages();


}

void Game::Render()
{
	/*
		- Clears old frame
		- Renders the game objects
		- displays the frame in window
	*/

	if (this->gameOver() == false) {

		this->window->clear(sf::Color::Black);

		//Draw Game Objects 
		this->RenderEnemies();

		//Draw User Interface
		this->renderUserInterface();

		this->window->display();
	}
	else if(this->gameOver() == true)
	{
		this->window->clear(sf::Color::Red);

		this->endScreen();

		// End Screen Text
		this->window->draw(this->EndScreenDisplay);
		this->window->draw(this->EndScreenRestart);

		this->window->display(); 
	}
	
}




