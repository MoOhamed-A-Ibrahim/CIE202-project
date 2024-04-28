#pragma once
#include "CMUgraphicsLib\CMUgraphics.h"
#include "toolbar.h"
#include "operations.h"
#include "grid.h"



class game
{

	/// Add more members if needed
	static int lives;
	static int score;
	static int level;
	toolbar* gameToolbar;

	window* pWind;	//Pointer to the CMU graphics window
	grid* shapesGrid;

public:
	game();
	~game();

	string getSrting() const;	 //Returns a string entered by the user
	void createWind(int, int, int, int); //creates the game window
	void clearStatusBar() const;	//Clears the status bar
	void printMessage(string msg) const;	//Print a message on Status bar
	void createToolBar();		//creates the toolbar
	void createGrid();		//creates the shapes grid
	void trackLives() const;

	window* getWind() const;		//returns a pointer to the graphics window
	grid* getGrid() const;		//returns a pointer to the shapes grid

	operation* createRequiredOperation(toolbarItem clickedItem);

	void run();	//start the game
	static int getLevel();
	static int getLives();
	static int getScore();

	static void setLives(int lvs);
	static void setScore(int sc);
	static void setLevel(int lvl);

};