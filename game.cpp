#include "game.h"
#include "gameConfig.h"
#include<iostream>
#include <thread>
#include <chrono>
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
//void game::initGame() {
//	bool choice;
//	char keyPressed;
//	window* pw = this->getWind();
//	grid* pGrid = this->getGrid();
//	//pw->DrawString(0.5 * (config.windWidth) - 150, config.windHeight - (int)(0.85 * config.statusBarHeight), "Press Y for timed game, N for non-timed game");
//	pw->WaitKeyPress(keyPressed);
//	if (keyPressed == 'y') {
//		this->clearStatusBar();
//		this->setUserChoice(true);
//		this->DrawTimer();
//	}
//	else if (keyPressed == 'n') {
//		this->setUserChoice(false);
//	}
//	this->clearStatusBar();
//}


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
	this->printMessage(statusBarMessage);
	//this->DrawTimer();
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
		statusBarMessage="Sign is being clicked";
		break;
	case ITM_Save:
		op = new operSaveProgress(this);
		statusBarMessage = "Save is being clicked";
		break;
	case ITM_Enlarge:
		if (shapesGrid->getActiveShape() != nullptr) {
			op = new operResizeUp(this);
		}
		statusBarMessage = "Enlarge is being clicked";
		break;
	case ITM_Minimize:
		if (shapesGrid->getActiveShape() != nullptr) {
			op = new operResizeDown(this);
		}		
		statusBarMessage = "Minimize is being clicked";
		break;
	case ITM_Hint:
		op = new operHint(this);
		statusBarMessage = "Hint is being clicked";
		break;
	case ITM_Rotate:
		if (shapesGrid->getActiveShape() != nullptr) {
			op = new operRotate(this);
		}	
		statusBarMessage = "Rotate is being clicked";
		break;
	case ITM_Refresh:
		op = new operRefresh(this);
		this->clearStatusBar();
		statusBarMessage = "Refresh is being clicked";
		break;
	case ITM_Select:
		op = new operSelectLevel(this);
		statusBarMessage = "Select is being clicked";
		break;
	case ITM_Trash:
		op = new operDELETE(this);
		statusBarMessage = "Trash is being clicked";
		break;
	case ITM_EXIT:
		statusBarMessage = "Exit is being clicked";
		break;
	case ITM_TREE:
		op = new operAddTree(this);
		statusBarMessage = "Tree is being clicked";
		break;
	case ITM_CAR:
		op = new operAddCar(this);
		statusBarMessage = "Car is being clicked";
		break;
	case ITM_ICECREAM:
		op = new operAddIceCream(this);
		statusBarMessage = "Icecream is being clicked";
		break;
	case ITM_ROCKET:
		op = new operRocket(this);
		statusBarMessage = "Rocket is being clicked";
		break;
	case ITM_HOUSE:
		op = new operAddHouse(this);
		statusBarMessage = "House is being clicked";
		break;
	case ITM_LOAD:
		op = new operLoad(this);
		statusBarMessage = "Load is being clicked";
		break;
	default:
		break;

	}
	return op;
}





//////////////////////////////////////////////////////////////////////////////////////////

void game::printMessage(string msg) const	//Prints a message on status bar
{
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
	/*this->initGame();*/
	int z = 0;
	do
	{
		countDownTimer->Timerr(true);
		DrawTimer(z);
		op2 = new operRandomizeShapes(this);
		op2->Act();

		pWind->GetKeyPress(keyPressed);
		if (shapesGrid->getActiveShape() != nullptr) {
			if (keyPressed == 32)
				shapesGrid->DetectMatch();
			if (keyPressed)
			if (keyPressed) {
				if (keyPressed == 8 || keyPressed == 'w') {
					statusBarMessage = "ARROW_UP/W is being clicked";
					op = new operMoveUp(this);
					op->Act();
				}
				else if (keyPressed == 2 || keyPressed == 's') {
					statusBarMessage = "ARROW_DOWN/S is being clicked";
					op = new operMoveDown(this);
					op->Act();
				}
				else if (keyPressed == 6 || keyPressed == 'd') {
					statusBarMessage = "ARROW_RIGHT/D is being clicked";
					op = new operMoveRight(this);
					op->Act();
				}
				else if (keyPressed == 4 || keyPressed == 'a') {
					statusBarMessage = "ARROW_LEFT/A is being clicked";
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

			//4-Redraw the grid after each actiondo
			shapesGrid->drawGrid();
			shapesGrid->drawActiveShape();
			shapesGrid->drawLevelShapes();
			this->clearStatusBar();
			this->updateToolbar();
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

//void game::DrawTimer() 
//{
//	pWind->SetPen(config.penColor, 50);
//	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
//	pWind->DrawString(0.5 * (config.windWidth) - 150, config.windHeight - (int)(0.85 * config.statusBarHeight), "Press any key to begin time");
//	char key;
//	int x, y;
//	int counter;
//	if (pWind->WaitKeyPress(key)!= NO_KEYPRESS || pWind->WaitMouseClick(x, y)== RIGHT_CLICK|| pWind->WaitMouseClick(x, y) == LEFT_CLICK) {
//		this->clearStatusBar();
//		if (this->getLevel() == 1) {
//			counter = 10;
//		}
//		else {
//			counter = 10 * shapesGrid->getShapeCount();
//		}
//		while (counter > 0) {
//			pWind->DrawString(0.5 * (config.windWidth), config.windHeight - (int)(0.85 * config.statusBarHeight), to_string(counter--));
//			std::this_thread::sleep_for(std::chrono::seconds(1));
//			this->clearStatusBar();
//		}
//	}
//}

void game::updateToolbar() {
	if (gameToolbar) {
		gameToolbar->update();
	}
}

void game::setStatusBarMessage(string msg) {
	statusBarMessage = msg;
}

bool game::getUserChoice()const {
	return userChoice;
}

void game::setUserChoice(bool ch) {
	userChoice = ch;
}

void game::DrawTimer( int &x) const
{
	pWind->SetPen(config.penColor, 50);
	pWind->SetFont(30, BOLD, BY_NAME, "Arial");
	pWind->DrawString(0.5 * (config.windWidth), config.windHeight - (int)(0.85 * config.statusBarHeight), countDownTimer->getinsec());
	if (((countDownTimer->getMax())-(stoi(countDownTimer->getinsec()))==x)) {
		clearStatusBar();
		x += 1;

	}

}

Timer* game::ReturnTime()const
{
	return countDownTimer;
}

