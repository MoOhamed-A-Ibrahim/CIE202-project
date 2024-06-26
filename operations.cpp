#include "operations.h"
#include "game.h"
#include "CompositeShapes.h"
#include <fstream>
#include<cstdlib>
#include"gameConfig.h"
#include <thread>
#include <chrono>
#include<time.h>
#include"grid.h"
#include<iostream>
#include"shape.h"
#include<iostream>
#include <cctype> 
#include <sstream>
#include "Timer.h"
#include <ctime>
using namespace std;


double getRandomNum(const double arr[], int size) {
	srand(time(nullptr) + rand());

	int randomIndex = rand() % size;

	return arr[randomIndex];
}

color* getRandomColors(const color arr[], int size) {
	srand(time(nullptr) + rand());

	color* randomColors = new color[2];

	int randomIndex1 = rand() % size;
	int randomIndex2 = rand() % size;

	randomColors[0] = arr[randomIndex1];
	randomColors[1] = arr[randomIndex2];

	return randomColors;
}



ShapeType getRandomShape() {
	srand(time(nullptr) + rand());
	int randomIndex = rand() % (HOUSE + 1);

	return (ShapeType)randomIndex;
}





/////////////////////////////////// class operation  //////////////////
operation::operation(game* r_pGame)
{
	pGame = r_pGame;
}


/////////////////////////////////// class operAddSign  //////////////////

operAddSign::operAddSign(game* r_pGame) :operation(r_pGame)
{
}

void operAddSign::Act()
{
	window* pw = pGame->getWind();
	grid* pGrid = pGame->getGrid();
	if (pGrid->getActiveShape() == nullptr) {


		//TODO:
		// Don't allow adding new shape if there is alreday an active shape

		//align reference point to the nearest grid point
		int xGrid = config.RefX - config.RefX % config.gridSpacing;
		int yGrid = config.RefY - config.RefX % config.gridSpacing;

		//take the aligned point as the sign shape ref point
		point signShapeRef = { xGrid,yGrid };

		//create a sign shape
		shape* psh = new Sign(pGame, signShapeRef);

		//Add the shape to the grid

		pGrid->setActiveShape(psh);
	}
	else {
		pGame->printMessage("please Delte the shape first");

	}
}

///////////////////////////////////

operDELETE::operDELETE(game* r_pGame) : operation(r_pGame) // intialize the constructor  witj operation class
{
	// a constructor that take a pointer to a game object as a parameter
}

void operDELETE::Act()
{
	grid* grid = pGame->getGrid(); //pGame is pointer to the game class
	grid->DELshapes();
}


///////////////////////////////////

operResizeUp::operResizeUp(game* r_pGame) : operation(r_pGame) // intialize the constructor  witj operation class
{
	// a constructor that take a pointer to a game object as a parameter
}

void operResizeUp::Act()
{
	grid* pGrid = pGame->getGrid();
	shape* currentShape = pGrid->getActiveShape();
	currentShape->resizeUp(2);
	pGrid->setActiveShape(currentShape);
	pGame->clearStatusBar();
	pGame->updateToolbar();
}


///////////////////////////////////
operResizeDown::operResizeDown(game* r_pGame) : operation(r_pGame) // intialize the constructor  witj operation class
{
	// a constructor that take a pointer to a game object as a parameter
}

void operResizeDown::Act()
{
	grid* pGrid = pGame->getGrid();
	shape* currentShape = pGrid->getActiveShape();
	currentShape->resizeDown(2);
	pGrid->setActiveShape(currentShape);
	pGame->clearStatusBar();
	pGame->updateToolbar();
}




operSelectLevel::operSelectLevel(game* r_pGame) : operation(r_pGame) // intialize the constructor  witj operation class
{
	// a constructor that take a pointer to a game object as a parameter
}

void operSelectLevel::Act()
{
	char keyPressed;
	window* pw = pGame->getWind();
	grid* pGrid = pGame->getGrid();
	pw->WaitKeyPress(keyPressed);

	if (isdigit(keyPressed)) {
		int kP = stoi(std::string(1, keyPressed));
		pGame->setLevel(kP);
		pGame->clearStatusBar();
		pGrid->nullifyShapeList();
		pGame->setRandomizationStatus(false);
	}
	pGame->clearStatusBar();
	pGame->updateToolbar();
}

//////////////////////////////

operAddIceCream::operAddIceCream(game* r_pGame) : operation(r_pGame)
{

}

void operAddIceCream::Act()
{
	window* pw = pGame->getWind();
	grid* pGrid = pGame->getGrid();
	if (pGrid->getActiveShape() == nullptr) {
		int xGrid = config.RefX - config.RefX % config.gridSpacing;
		int yGrid = config.RefY - config.RefX % config.gridSpacing;
		point triShapeRef = { xGrid,yGrid };
		shape* psh = new IceCream(pGame, triShapeRef);

		pGrid->setActiveShape(psh);
	}
	else {
		pGame->printMessage("please Delte the shape first");

	}

}

///////////////////////////////

operAddCar::operAddCar(game* r_pGame) : operation(r_pGame)
{
}

void operAddCar::Act()
{
	window* pw = pGame->getWind();
	grid* pGrid = pGame->getGrid();
	if (pGrid->getActiveShape() == nullptr) {
		int xGrid = config.RefX - config.RefX % config.gridSpacing;
		int yGrid = config.RefY - config.RefX % config.gridSpacing;
		point triShapeRef = { xGrid,yGrid };
		shape* psh = new Car(pGame, triShapeRef);

		pGrid->setActiveShape(psh);
	}
	else {
		pGame->printMessage("please Delte the shape first");

	}
}
////////////////////////////////////////////////

operAddHouse::operAddHouse(game* r_pGame) : operation(r_pGame)
{
}

void operAddHouse::Act()
{
	window* pw = pGame->getWind();
	grid* pGrid = pGame->getGrid();
	if (pGrid->getActiveShape() == nullptr) {
		int xGrid = config.RefX - config.RefX % config.gridSpacing;
		int yGrid = config.RefY - config.RefX % config.gridSpacing;
		point triShapeRef = { xGrid,yGrid };
		shape* psh = new House(pGame, triShapeRef);
		pGrid->setActiveShape(psh);
	}
	else {
		pGame->printMessage("please Delte the shape first");

	}

}
////////////////////////////////////////

operAddTree::operAddTree(game* r_pGame) : operation(r_pGame)
{
}

void operAddTree::Act()
{
	window* pw = pGame->getWind();
	grid* pGrid = pGame->getGrid();

	if (pGrid->getActiveShape() == nullptr) {

		int xGrid = config.RefX - config.RefX % config.gridSpacing;
		int yGrid = config.RefY - config.RefX % config.gridSpacing;
		point triShapeRef = { xGrid,yGrid };
		shape* psh = new Tree(pGame, triShapeRef);
		grid* pGrid = pGame->getGrid();
		pGrid->setActiveShape(psh);

	}
	else {

		pGame->printMessage("please Delte the shape first");
	}
}

///////////////////////////////////////

operRocket::operRocket(game* r_pGame) : operation(r_pGame)
{
}
void operRocket::Act()
{
	window* pw = pGame->getWind();
	grid* pGrid = pGame->getGrid();
	if (pGrid->getActiveShape() == nullptr) {
		int xGrid = config.RefX - config.RefX % config.gridSpacing;
		int yGrid = config.RefY - config.RefX % config.gridSpacing;
		point triShapeRef = { xGrid,yGrid };
		shape* psh = new Rocket(pGame, triShapeRef);
		pGrid->setActiveShape(psh);
	}
	else {
		pGame->printMessage("please Delte the shape first");

	}


}
/////////////////////////////////////////

operRotate::operRotate(game* r_pGame) :operation(r_pGame)
{
}

void operRotate::Act()
{
	double angle = 90;
	grid* grid = pGame->getGrid();
	shape* shape = grid->getActiveShape();
	shape->rotate();
	pGame->clearStatusBar();
	pGame->updateToolbar();
}


operMoveUp::operMoveUp(game* r_pGame) :operation(r_pGame)
{
}

void operMoveUp::Act() {
	grid* pGrid = pGame->getGrid();
	shape* currentShape = pGrid->getActiveShape();
	currentShape->moveUp(config.gridSpacing);
	pGrid->setActiveShape(currentShape);
	pGrid->drawGrid();
	pGrid->drawActiveShape();
	pGrid->drawLevelShapes();
	pGame->clearStatusBar();
	pGame->createToolBar();
}

operMoveDown::operMoveDown(game* r_pGame) :operation(r_pGame)
{
}

void operMoveDown::Act() {
	grid* pGrid = pGame->getGrid();
	shape* currentShape = pGrid->getActiveShape();
	currentShape->moveDown(config.gridSpacing);
	pGrid->setActiveShape(currentShape);
	pGrid->drawGrid();
	pGrid->drawActiveShape();
	pGrid->drawLevelShapes();
	pGame->clearStatusBar();
	pGame->createToolBar();
}

operMoveRight::operMoveRight(game* r_pGame) :operation(r_pGame)
{
}

void operMoveRight::Act() {
	grid* pGrid = pGame->getGrid();
	shape* currentShape = pGrid->getActiveShape();
	currentShape->moveRight(config.gridSpacing);
	pGrid->setActiveShape(currentShape);
	pGrid->drawGrid();
	pGrid->drawActiveShape();
	pGrid->drawLevelShapes();
	pGame->clearStatusBar();
	pGame->createToolBar();
}

operMoveLeft::operMoveLeft(game* r_pGame) :operation(r_pGame)
{
}

void operMoveLeft::Act() {
	grid* pGrid = pGame->getGrid();
	shape* currentShape = pGrid->getActiveShape();
	currentShape->moveLeft(config.gridSpacing);
	pGrid->setActiveShape(currentShape);
	pGrid->drawGrid();
	pGrid->drawActiveShape();
	pGrid->drawLevelShapes();
	pGame->clearStatusBar();
	pGame->createToolBar();
}

operSaveProgress::operSaveProgress(game* r_pGame) : operation(r_pGame)
{
}

void operSaveProgress::Act()
{
	grid* pGrid = pGame->getGrid();
	shape* currentShape = pGrid->getActiveShape();
	int shapecount = pGrid->getShapeCount();
	int level = pGame->getLevel();
	int lives = pGame->getLives();
	int score = pGame->getScore();

	ofstream File;
	File.open("Progress//Progress.txt");
	File << shapecount << " " << level << " " << lives << " " << score << endl;
	File.close();
	if (currentShape)
	{
		currentShape->fileMyself("Progress//Progress.txt");
	}
	else
	{
		File.open("Progress//Progress.txt", std::ios::app);
		File << 00000000000000000000000 << endl;
		File.close();
	}


	///////////////////////////////////////////////////////

	shape** shapelist = pGrid->getshapeList();
	for (int i = ((pGrid->getShapeCount()) / 2); i < (pGrid->getShapeCount()); i++)
	{
		if (shapelist[i])
		{
			(shapelist[i])->fileMyself("Progress//Progress.txt");
		}
		else
		{
			File.open("Progress//Progress.txt", std::ios::app);
			File << 00000000000000000000000 << endl;
			File.close();
		}
	}
}

operRefresh::operRefresh(game* r_pGame) :operation(r_pGame)
{
}

void operRefresh::Act() {
	grid* pGrid = pGame->getGrid();
	pGrid->clearGridArea();
	int currentLives = pGame->getLives();
	if (currentLives > 1) {
		pGame->setLives(currentLives - 1);
	}
	pGrid->nullifyShapeList();
	pGame->setRandomizationStatus(false);
	pGame->clearStatusBar();
	pGame->updateToolbar();
}

operRandomizeShapes::operRandomizeShapes(game* r_pGame) : operation(r_pGame)
{
}

void operRandomizeShapes::Act()
{
	window* pw = pGame->getWind();
	grid* pGrid = pGame->getGrid();
	pGrid->nullifyShapesReferencePoints();
	point* referenceShapes = pGrid->getShapesRefList();

	bool currentRandomizationStatus = pGame->getRandomizationStatus();
	if (!currentRandomizationStatus) {
		srand(time(nullptr) + rand());
		color randomFill;
		color randomBorder;
		double randomSize;
		double randomAngle;
		point randomGridReferencePoint;
		shape* newShape = nullptr;

		int currentLevel = pGame->getLevel();
		int currentShapeCount = 2 * currentLevel - 1;
		int maxShapes = pGrid->getMaxShapeCount();
		if (currentShapeCount > maxShapes) {
			currentShapeCount = maxShapes;
		}
		pGrid->setShapeCount(currentShapeCount);

		for (int i = 0; i < currentShapeCount; i++) {
			if (currentLevel < 3) {
				randomFill = getRandomColors(colorArr, 215)[0];
				randomBorder = getRandomColors(colorArr, 215)[1];
			}
			else {
				randomFill = BLACK;
				randomBorder = BLACK;
			}
			randomSize = getRandomNum(sizeArr, 4);
			randomAngle = getRandomNum(angleArr, 4);
			ShapeType randomShape = getRandomShape();
			randomGridReferencePoint = pGrid->getRandomGridPoint();
			switch (randomShape) {
			case SIGN:
				newShape = new Sign(pGame, { randomGridReferencePoint.x, randomGridReferencePoint.y }, randomSize, randomAngle, randomFill, randomBorder);
				break;
			case TREE:
				newShape = new Tree(pGame, { randomGridReferencePoint.x, randomGridReferencePoint.y }, randomSize, randomAngle, randomFill, randomBorder);
				break;
			case CAR:
				newShape = new Car(pGame, { randomGridReferencePoint.x, randomGridReferencePoint.y }, randomSize, randomAngle, randomFill, randomBorder);
				break;
			case ICECREAM:
				newShape = new IceCream(pGame, { randomGridReferencePoint.x, randomGridReferencePoint.y }, randomSize, randomAngle, randomFill, randomBorder);
				break;
			case HOUSE:
				newShape = new House(pGame, { randomGridReferencePoint.x, randomGridReferencePoint.y }, randomSize, randomAngle, randomFill, randomBorder);
				break;
			case ROCKET:
				newShape = new Rocket(pGame, { randomGridReferencePoint.x, randomGridReferencePoint.y }, randomSize, randomAngle, randomFill, randomBorder);
				break;
			}
			point newShapeRefPoint = newShape->getRefPoint();
			if (currentShapeCount == 1) {
				if (randomShape != ICECREAM) {
					randomGridReferencePoint = pGrid->getRandomGridPoint(newShape);
				}
			}
			else if (currentShapeCount > 1 && !pGrid->isShapeListEmpty()) {
				if (referenceShapes) {
					if (currentLevel < 3) {
						while (pGrid->gridInVicinity(randomGridReferencePoint, referenceShapes[i], 9)) {
							cout << randomGridReferencePoint.x << " " << randomGridReferencePoint.y << " " << referenceShapes[i].x << " " << referenceShapes[i].y << endl;
							randomGridReferencePoint = pGrid->getRandomGridPoint(newShape);
						}
					}
					else {
						bool overlaps = false;
						while (overlaps == true) {///should be false
							cout << randomGridReferencePoint.x << " " << randomGridReferencePoint.y << " " << referenceShapes[i].x << " " << referenceShapes[i].y << endl;
							randomGridReferencePoint = pGrid->getRandomGridPoint(newShape);
							for (int j = 0; j < i; j++) {
								if (!pGrid->gridInVicinity(randomGridReferencePoint, referenceShapes[j], 2)) {
									overlaps = true;
									break;
								}
							}
						}
					}
				}
			}
			pGrid->addShape(newShape);
			referenceShapes[currentShapeCount] = newShape->getRefPoint();
		}
		pGrid->drawGrid();
		pGrid->drawActiveShape();
		pGrid->drawLevelShapes();
		pGame->setRandomizationStatus(true);
		pGame->clearStatusBar();
		pGame->updateToolbar();
	}
}

operHint::operHint(game* r_pgame) : operation(r_pgame)
{
}

void operHint::Act()
{

	int x, y;
	if (this->c == 0)
	{
		this->c++;
		x = stoi(pGame->ReturnTime()->getinsec());
	}
	y= stoi(pGame->ReturnTime()->getinsec());

	grid* pGrid = pGame->getGrid();
	shape* currentShape = pGrid->getActiveShape();
	int shapecount = pGrid->getShapeCount();
	shape** shapelist = pGrid->getshapeList();
	shape* LooShape;
	int level = pGame->getLevel();
	int lives = pGame->getLives();
	int score = pGame->getScore();

	if ((x-y) <= 15) 
	{

		if (level >= 3)
		{
			score -= 1;

			pGame->setLives(lives);
			pGame->setLevel(level);
			pGame->setScore(score);
			pGame->clearStatusBar();

			if (shapelist[shapecount - 1])
			{
				point Ref = shapelist[shapecount - 1]->getRefPoint();
				double size = shapelist[shapecount - 1]->getSize();
				double angle = shapelist[shapecount - 1]->getAngle();
				switch ((shapelist[shapecount - 1]->getName())[0])
				{
				case (int('S')):
					LooShape = new Sign(pGame, Ref, size, angle, YELLOW, BLACK);
					break;
				case (int('T')):
					LooShape = new Tree(pGame, Ref, size, angle, YELLOW, BLACK);
					break;
				case (int('C')):
					LooShape = new Car(pGame, Ref, size, angle, YELLOW, BLACK);
					break;
				case (int('I')):
					LooShape = new IceCream(pGame, Ref, size, angle, YELLOW, BLACK);
					break;
				case (int('R')):
					LooShape = new Rocket(pGame, Ref, size, angle, YELLOW, BLACK);
					break;
				case (int('H')):
					LooShape = new House(pGame, Ref, size, angle, YELLOW, BLACK);
					break;
				}
			}
			pGrid->DELshapes();
			pGrid->DelShapefromlist();
			pGrid->addShape(LooShape);
			pGrid->drawLevelShapes();
		}

		
	}
	if (level >= 3)
	{
		if (shapelist[shapecount - 1])
		{
			point Ref = shapelist[shapecount - 1]->getRefPoint();
			double size = shapelist[shapecount - 1]->getSize();
			double angle = shapelist[shapecount - 1]->getAngle();
			switch ((shapelist[shapecount - 1]->getName())[0])
			{
			case (int('S')):
				LooShape = new Sign(pGame, Ref, size, angle, BLACK, BLACK);
				break;
			case (int('T')):
				LooShape = new Tree(pGame, Ref, size, angle, BLACK, BLACK);
				break;
			case (int('C')):
				LooShape = new Car(pGame, Ref, size, angle, BLACK, BLACK);
				break;
			case (int('I')):
				LooShape = new IceCream(pGame, Ref, size, angle, BLACK, BLACK);
				break;
			case (int('R')):
				LooShape = new Rocket(pGame, Ref, size, angle, BLACK, BLACK);
				break;
			case (int('H')):
				LooShape = new House(pGame, Ref, size, angle, BLACK, BLACK);
				break;
			}
		}
		pGrid->DELshapes();
		pGrid->DelShapefromlist();
		pGrid->addShape(LooShape);
		pGrid->drawLevelShapes();
	}
	
}


operLoad::operLoad(game* r_pGame) : operation(r_pGame)
{
}

void operLoad::Act()
{
	//inittalize variables and nullify shapes//

	grid* pGrid = pGame->getGrid();
	shape** shapelist = pGrid->getshapeList();
	shape* currentShape = pGrid->getActiveShape();
	shape* LooShape;

	pGrid->nullifyShapeList();
	pGrid->DELshapes();

	//file open//

	ifstream File;
	File.open("Progress//Progress.txt");
	if (File.is_open()) {


		string line;
		getline(File, line);

		int Level, Lives, Score, shapecount;
		istringstream iss1(line);
		iss1 >> shapecount >> Level >> Lives >> Score;


		pGame->setLives(Lives);
		pGame->setLevel(Level);
		pGame->setScore(Score);
		pGame->clearStatusBar();


		int intgername;
		double pointx;
		double pointy;
		double size;
		double angle;
		char fCR, fCG, fCB; char bCR, bCG, bCB;
		point Ref;

		if (getline(File, line)) {
			istringstream iss2(line);
			iss2 >> intgername >> pointx >> pointy >> size >> angle >> fCR >> fCG >> fCB >> bCR >> bCG >> bCB;
			color Bordercolor = color(bCR, bCG, bCB);
			color Fillcolor = color(fCR, fCG, fCB);
			Ref.x = pointx;
			Ref.y = pointy;
			if (line != "0")
			{


				switch (intgername)
				{
				case (int('S')):
					currentShape = new Sign(pGame, Ref, size, angle, Fillcolor, Bordercolor);
					break;
				case (int('T')):
					currentShape = new Tree(pGame, Ref, size, angle, Fillcolor, Bordercolor);
					break;
				case (int('C')):
					currentShape = new Car(pGame, Ref, size, angle, Fillcolor, Bordercolor);
					break;
				case (int('I')):
					currentShape = new IceCream(pGame, Ref, size, angle, Fillcolor, Bordercolor);
					break;
				case (int('R')):
					currentShape = new Rocket(pGame, Ref, size, angle, Fillcolor, Bordercolor);
					break;
				case (int('H')):
					currentShape = new House(pGame, Ref, size, angle, Fillcolor, Bordercolor);
					break;
				}
				pGrid->setActiveShape(currentShape);
				pGrid->drawActiveShape();
			}
			for (int i = 0; i < shapecount / 2; i++)
			{
				if (getline(File, line)) {
					istringstream issi(line);

					issi >> intgername >> pointx >> pointy >> size >> angle >> fCR >> fCG >> fCB >> bCR >> bCG >> bCB;
					color Bordercolor = color(bCR, bCG, bCB);
					color Fillcolor = color(fCR, fCG, fCB);
					Ref.x = pointx;
					Ref.y = pointy;

				}
				switch (intgername)
				{
				case (int('S')):
					LooShape = new Sign(pGame, Ref, size, angle, Fillcolor, Bordercolor);
					break;
				case (int('T')):
					LooShape = new Tree(pGame, Ref, size, angle, Fillcolor, Bordercolor);
					break;
				case (int('C')):
					LooShape = new Car(pGame, Ref, size, angle, Fillcolor, Bordercolor);
					break;
				case (int('I')):
					LooShape = new IceCream(pGame, Ref, size, angle, Fillcolor, Bordercolor);
					break;
				case (int('R')):
					LooShape = new Rocket(pGame, Ref, size, angle, Fillcolor, Bordercolor);
					break;
				case (int('H')):
					LooShape = new House(pGame, Ref, size, angle, Fillcolor, Bordercolor);
					break;
				}

				pGrid->addShape(LooShape);

			}
			pGrid->drawLevelShapes();
		}

	}
}

operExit::operExit(game* r_pGame) :operation(r_pGame)
{
}

void operExit::Act()
{
	grid* grid = pGame->getGrid();
	shape* shape = grid->getActiveShape();
	delete shape;
	shape = nullptr;

}

operPowerUp::operPowerUp(game* r_pGame) :operation(r_pGame)
{
}

void operPowerUp::Act()
{
	grid* pGrid = pGame->getGrid();
	shape** shapelist = pGrid->getshapeList();
	int score = pGame->getScore();

	int x, y;
	if (this->c == 0)
	{
		this->c++;
		x = stoi(pGame->ReturnTime()->getinsec());
	}
	y = stoi(pGame->ReturnTime()->getinsec());
	int height = config.toolBarHeight;
	int width = config.windWidth;
	window* pWind = pGame->getWind();
	while (x - y <= 50)
	{
		if ((pGame->getScore()) > score)
		{
			window* pWind = pGame->getWind();
			pWind->DrawImage("images\\PowerUp\\PowerUp.jpg", 14 * config.toolbarItemWidth, 0, config.toolbarItemWidth, config.toolBarHeight);
			pWind->SetPen(DARKBLUE, 3);
			pWind->DrawLine(0, height, width, height);
		}
	}
}
