#pragma once
#include <vector>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
/*
	Class that acts as the game engine.
*/

class Game {

private:
	// Variables
	// Window
	sf::RenderWindow* window;
	sf::Event event;
	sf::VideoMode videoMode;
	sf::Text playerHealthDisplay;
	sf::Text playerPointsDisplay;
	sf::Text EndScreenDisplay;
	sf::Text EndScreenRestart;
	sf::Font textFont;
	

	// Mouse Positions
	sf::Vector2i mousePosWindow;
	float cursorXPos;
	float cursorYPos;
	sf::Vector2f cursorPos;

	// Game Logic

	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	int playerHealth;
	int startingHealth;
	int points;
	int startingPoints;

	// Game Objects
	std::vector<sf::RectangleShape> Enemies;
	sf::RectangleShape enemyRectangle;


	void initializeVariables();
	void initializeWindow();
	void initializeEnemies();
	void initializeFont();

public:
	// Constructors & Destructors
	Game();
	virtual ~Game();

	// Accessors
	const bool getWindowIsOpen() const;

	// Functions
	bool gameOver();
	void endScreen();
	void restart();
	void spawnEnemies();
	void UpdateEnemies();
	void RenderEnemies();
	void renderUserInterface();
	void UpdatePollEvents();
	void UpdateMousePosition();
	void Update();
	void Render();
	void debugMessages();
};

