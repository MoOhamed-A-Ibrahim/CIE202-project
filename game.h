#pragma once
#include "CMUgraphicsLib\CMUgraphics.h"
#include "toolbar.h"
#include "operations.h"
#include "grid.h"
#include "Timer.h"



class game
{

	/// Add more members if needed
	 int lives=5;
	 int score=0;
	 int level=1;
	 bool isRandomized=0;
	toolbar* gameToolbar;

	window* pWind;	//Pointer to the CMU graphics window
	grid* shapesGrid;
	string statusBarMessage;
	Timer* countDownTimer;
	
public:
	game();
	~game();

	string getSrting() const;	 //Returns a string entered by the user
	void createWind(int, int, int, int); //creates the game window
	void clearStatusBar() const;	//Clears the status bar
	void printMessage(string msg) const;	//Print a message on Status bar
	void createToolBar();//creates the toolbar
	void updateToolbar();
	void createGrid();		//creates the shapes grid
	void trackLives() const;

	window* getWind() const;		//returns a pointer to the graphics window
	grid* getGrid() const;		//returns a pointer to the shapes grid

	operation* createRequiredOperation(toolbarItem clickedItem);

	void run();	//start the game
	 int getLevel()const;
	 int getLives()const;
	 int getScore()const;

	 void setLives(int lvs);
	 void setScore(int sc);
	 void setLevel(int lvl);
	 void setStatusBarMessage(string msg);
	 bool getRandomizationStatus();
	
	 void setRandomizationStatus(bool val);
	 void DrawTimer() const;
};