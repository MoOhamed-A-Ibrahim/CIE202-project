#include "game.h"
#include "gameConfig.h"
#include<iostream>
using namespace std;




game::game()
{

	//Create the main window
	createWind(config.windWidth, config.windHeight, config.wx, config.wy);

	//Create and draw the toolbar
	createToolBar();

	//Create and draw the grid
	createGrid();
	shapesGrid->drawGrid();	//draw the grid and all shapes it contains.
	shapesGrid->drawActiveShape();

	//Create and clear the status bar
	clearStatusBar();
	trackLives();

}

game::~game()
{
	delete pWind;
	delete shapesGrid;
}


//////////////////////////////////////////////////////////////////////////////////////////
void game::createWind(int w, int h, int x, int y) 
{
	pWind = new window(w, h, x, y);
	pWind->SetBrush(config.bkGrndColor);
	pWind->SetPen(config.bkGrndColor, 1);
	pWind->DrawRectangle(0, 0, w, h);
}
//////////////////////////////////////////////////////////////////////////////////////////
void game::clearStatusBar() const
{
	//Clear Status bar by drawing a filled rectangle
	pWind->SetPen(config.statusBarColor, 1);
	pWind->SetBrush(config.statusBarColor);
	pWind->DrawRectangle(0, config.windHeight - config.statusBarHeight, config.windWidth, config.windHeight);

	this->trackLives();
}

//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the mode
void game::createToolBar()
{
	gameToolbar = new toolbar(this);
}

void game::createGrid()
{	
	//calc some grid parameters
	point gridUpperLeftPoint = { 0, config.toolBarHeight };
	int gridHeight = config.windHeight - config.toolBarHeight - config.statusBarHeight;
	//create the grid
	shapesGrid = new grid(gridUpperLeftPoint, config.windWidth, gridHeight, this);
}

operation* game::createRequiredOperation(toolbarItem clickedItem)
{
	operation* op = nullptr;
	switch (clickedItem)
	{


	case ITM_SIGN:
		op = new operAddSign(this);
		printMessage("Sign is being clicked");
		break;
	case ITM_Save:
		if (shapesGrid->getActiveShape() != nullptr) {
			op = new operSaveProgress(this);
		}		printMessage("Save is being clicked");
		break;
	case ITM_Enlarge:
		if (shapesGrid->getActiveShape() != nullptr) {
			op = new operResizeUp(this);
		}
		printMessage("Enlarge is being clicked");
		break;
	case ITM_Minimize:
		if (shapesGrid->getActiveShape() != nullptr) {
			op = new operResizeDown(this);
		}		printMessage("Minimize is being clicked");
		break;
	case ITM_Hint:
		printMessage("Hint is being clicked");
		break;
	case ITM_Rotate:
		if (shapesGrid->getActiveShape() != nullptr) {
			op = new operRotate(this);
		}	printMessage("Rotates is being clicked");
		break;
	case ITM_Refresh:
		op = new operRefresh(this);
		this->clearStatusBar();
		printMessage("Refresh is being clicked");
		break;
	case ITM_Select:
		op = new operSelectLevel(this);
		printMessage("Select is being clicked");
		break;
	case ITM_Trash:
		op = new operDELETE(this);
		printMessage("Trash is being clicked");
		break;
	case ITM_EXIT:
		printMessage("Exit is being clicked");
		break;
	case ITM_TREE:
		op = new operAddTree(this);
		printMessage("Tree is being clicked");
		break;
	case ITM_CAR:
		op = new operAddCar(this);
		printMessage("Car is being clicked");
		break;
	case ITM_ICECREAM:
		op = new operAddIceCream(this);
		printMessage("Icecream is being clicked");
		break;
	case ITM_ROCKET:
		op = new operRocket(this);
		printMessage("Rocket is being clicked");
		break;
	case ITM_HOUSE:
		op = new operAddHouse(this);
		printMessage("House is being clicked");
		break;
	case ITM_LOAD:
		printMessage("Load is being clicked");
		break;
	default:
		break;

	}
	return op;
}





//////////////////////////////////////////////////////////////////////////////////////////

void game::printMessage(string msg) const	//Prints a message on status bar
{
	clearStatusBar();	//First clear the status bar
	pWind->SetPen(config.penColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, config.windHeight - (int)(0.85 * config.statusBarHeight), msg);
}

void game::trackLives() const {
	int currentLives = this->getLives();
	int currentLvl = this->getLevel();
	int currentScore = this->getScore();
	string msg = "Lives = "+to_string(currentLives)+" \nScore = "+to_string(currentScore)+" \nLevel = "+to_string(currentLvl);
	pWind->SetPen(config.penColor, 50);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(config.windWidth-250, config.windHeight - (int)(0.85 * config.statusBarHeight), msg);

}




window* game::getWind() const		//returns a pointer to the graphics window
{
	return pWind;
}



string game::getSrting() const
{
	string Label;
	char Key;
	keytype ktype;
	pWind->FlushKeyQueue();
	while (1)
	{
		ktype = pWind->WaitKeyPress(Key);
		if (ktype == ESCAPE)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if (Key == 8)	//BackSpace is pressed
			if (Label.size() > 0)
				Label.resize(Label.size() - 1);
			else
				Key = '\0';
		else
			Label += Key;
		printMessage(Label);
	}
}

grid* game::getGrid() const
{
	// TODO: Add your implementation code here.
	return shapesGrid;
}



////////////////////////////////////////////////////////////////////////
void game::run() 
{
	//This function reads the position where the user clicks to determine the desired operation
	int x, y;
	bool isExit = false;
	operation* op;
	operation* op2;
	char keyPressed;
	//Change the title
	pWind->ChangeTitle("- - - - - - - - - - SHAPE HUNT (CIE 101 / CIE202 - project) - - - - - - - - - -");
	toolbarItem clickedItem=ITM_CNT;

	do
	{
		op2 = new operRandomizeShapes(this);
		op2->Act();

		pWind->GetKeyPress(keyPressed);
		if (shapesGrid->getActiveShape() != nullptr) {
			if (keyPressed) {
				if (keyPressed == 8 || keyPressed == 'w') {
					printMessage("ARROW_UP/W is being clicked");
					op = new operMoveUp(this);
					op->Act();
				}
				else if (keyPressed == 2 || keyPressed == 's') {
					printMessage("ARROW_DOWN/S is being clicked");
					op = new operMoveDown(this);
					op->Act();
				}
				else if (keyPressed == 6 || keyPressed == 'd') {
					printMessage("ARROW_RIGHT/D is being clicked");
					op = new operMoveRight(this);
					op->Act();
				}
				else if (keyPressed == 4 || keyPressed == 'a') {
					printMessage("ARROW_LEFT/A is being clicked");
					op = new operMoveLeft(this);
					op->Act();

				}

			}
		}
		//printMessage("Ready...");
		//1- Get user click
		pWind->GetMouseClick(x, y);	//Get the coordinates of the user click

		//2-Explain the user click
		//If user clicks on the Toolbar, ask toolbar which item is clicked
		if (y >= 0 && y < config.toolBarHeight)
		{
			clickedItem=gameToolbar->getItemClicked(x);

			//3-create the approp operation accordin to item clicked by the user
			op = createRequiredOperation(clickedItem);
			if (op)
				op->Act();

			//4-Redraw the grid after each action
			shapesGrid->drawGrid();
			shapesGrid->drawActiveShape();
			shapesGrid->drawLevelShapes();
		}	

	} while (clickedItem!=ITM_EXIT);
}

int game::getLives()const {
	return lives;
}

int game::getScore()const {
	return score;
}

int game::getLevel()const {
	return level;
}

void game::setLives(int lvs) {
	lives = lvs;
}
void game::setScore(int sc) {
	score = sc;
}
void game::setLevel(int lvl) {
	level = lvl;
}

bool game::getRandomizationStatus() {
	return isRandomized;
}

void game::setRandomizationStatus(bool val) {
	isRandomized = val;
}