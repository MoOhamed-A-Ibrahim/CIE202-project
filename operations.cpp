#include "operations.h"
#include "game.h"
#include "CompositeShapes.h"
#include <fstream>
#include<cstdlib>
#include"gameConfig.h"
#include<time.h>
#include"grid.h"
#include<iostream>
#include"shape.h"
#include<iostream>
#include <cctype> 
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
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);

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
}

//////////////////////////////

operAddIceCream::operAddIceCream(game* r_pGame) : operation(r_pGame)
{

}

void operAddIceCream::Act()
{
	window* pw = pGame->getWind();
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;
	point triShapeRef = { xGrid,yGrid };
	shape* psh = new IceCream(pGame, triShapeRef);
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);

}

///////////////////////////////

operAddCar::operAddCar(game* r_pGame) : operation(r_pGame)
{
}

void operAddCar::Act()
{
	window* pw = pGame->getWind();
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;
	point triShapeRef = { xGrid,yGrid };
	shape* psh = new Car(pGame, triShapeRef);
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);
}
////////////////////////////////////////////////

operAddHouse::operAddHouse(game* r_pGame) : operation(r_pGame)
{
}

void operAddHouse::Act()
{
	window* pw = pGame->getWind();
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;
	point triShapeRef = { xGrid,yGrid };
	shape* psh = new House(pGame, triShapeRef);
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);
}
////////////////////////////////////////

operAddTree::operAddTree(game* r_pGame) : operation(r_pGame)
{
}

void operAddTree::Act()
{
	window* pw = pGame->getWind();
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;
	point triShapeRef = { xGrid,yGrid };
	shape* psh = new Tree(pGame, triShapeRef);
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);
}

///////////////////////////////////////

operRocket::operRocket(game* r_pGame) : operation(r_pGame)
{
}
void operRocket::Act()
{
	window* pw = pGame->getWind();
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;
	point triShapeRef = { xGrid,yGrid };
	shape* psh = new Rocket(pGame, triShapeRef);
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);
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
}

operSaveProgress::operSaveProgress(game* r_pGame) : operation(r_pGame)
{
}

void operSaveProgress::Act()
{
	grid* pGrid = pGame->getGrid();
	shape* currentShape = pGrid->getActiveShape();
	int level = pGame->getLevel();
	int lives = pGame->getLives();
	int score = pGame->getScore();
	point refpoint;
	string name;
	int intgerName;
	int bCB;
	int bCG;
	int bCR;
	int fCB;
	int fCG;
	int fCR;
	int pointx;
	int pointy;
	int angle;
	int size;
	

	ofstream File;
	File.open("Progress//Progress.txt");
	File << level << " " << lives << " " << score << endl;
	if (currentShape)
	{

		name = currentShape->getName();
		intgerName = int(name[0]);
		refpoint = currentShape->getRefPoint();
		pointx = refpoint.x;
		pointy = refpoint.y;
		angle = currentShape->getAngle();
		bCB = currentShape->getBorderColor().ucBlue;
		bCG = currentShape->getBorderColor().ucGreen;
		bCR = currentShape->getBorderColor().ucRed;
		fCB = currentShape->getFillColor().ucBlue;
		fCG = currentShape->getFillColor().ucGreen;
		fCR = currentShape->getFillColor().ucRed;
		size = currentShape->getSize();

		File << pointx << " " << pointy << " " << size << " " << angle << " "
			<< fCR << " " << fCG << " " << fCB << " "
			<< bCR << " " << bCG << " " << bCB << endl;

	}
	else
	{
		File << 00000000000000000000000 << endl;
	}



	//shape** Array =  pGrid->getArrayElements();
	//for (int i = 0; i < pGrid->getShapeCount(); i++)
	//{

	//	name = Array[i]->getName();
	//	intgerName = int(name[0]);
	//	refpoint = Array[i]->getRefPoint();
	//	pointx = refpoint.x;
	//	pointy = refpoint.y;
	//	angle = Array[i]->getAngle();
	//	bCB = Array[i]->getBorderColor().ucBlue;
	//	bCG = Array[i]->getBorderColor().ucGreen;
	//	bCR = Array[i]->getBorderColor().ucRed;
	//	fCB = Array[i]->getFillColor().ucBlue;
	//	fCG = Array[i]->getFillColor().ucGreen;
	//	fCR = Array[i]->getFillColor().ucRed;
	//	size = Array[i]->getSize();

	//	File << pointx << " " << pointy << " " << size << " " << angle << " "
	//		<< fCR << " " << fCG << " " << fCB << " "
	//		<< bCR << " " << bCG << " " << bCB << endl;

	//	File.close();
	//}
}

operRefresh::operRefresh(game* r_pGame) :operation(r_pGame)
{
}

void operRefresh::Act() {
	grid* pGrid = pGame->getGrid();
	pGrid->clearGridArea();
	int currentLevel = pGame->getLevel();
	if (currentLevel > 1) {
		pGame->setLevel(currentLevel - 1);
	}
	pGrid->nullifyShapeList();
	pGame->setRandomizationStatus(false);
}


operRandomizeShapes::operRandomizeShapes(game* r_pGame) : operation(r_pGame)
{
}

void operRandomizeShapes::Act()
{
	//point boundaryPoint1 = {0,config.toolBarHeight };
	//point boundaryPoint2 = { config.windWidth ,config.windHeight - config.statusBarHeight };

	window* pw = pGame->getWind();
	grid* pGrid = pGame->getGrid();
	//pGrid->nullifyShapeList();

	bool currentRandomizationStatus = pGame->getRandomizationStatus();
	if (currentRandomizationStatus == false) {
		srand(time(nullptr) + rand());
		color randomFill;
		color randomBorder;
		double randomSize;
		double randomAngle;
		point randomGridReferencePoint;

		int currentLevel = pGame->getLevel();
		int currentShapeCount = 2 * currentLevel - 1;
		int maxShapes = pGrid->getMaxShapeCount();
		ShapeType randomShape;
		if (currentShapeCount > maxShapes) {
			currentShapeCount = maxShapes;
		}
		pGrid->setShapeCount(currentShapeCount);
		shape* newShape = nullptr;
		if (currentLevel < 3) {
			for (int i = 0; i < currentShapeCount; i++) {
				randomFill = getRandomColors(colorArr, 215)[0];
				randomBorder = getRandomColors(colorArr, 215)[1];
				randomSize = getRandomNum(sizeArr, 4);
				randomAngle = getRandomNum(angleArr, 4);
				randomShape = getRandomShape();
				randomGridReferencePoint = pGrid->getRandomGridPoint();
				switch (randomShape) {
				case SIGN:
					newShape = new Sign(pGame, { randomGridReferencePoint.x,randomGridReferencePoint.y }, randomSize, randomAngle, randomFill, randomBorder);
					break;
				case TREE:
					newShape = new Tree(pGame, { randomGridReferencePoint.x,randomGridReferencePoint.y }, randomSize, randomAngle, randomFill, randomBorder);
					break;
				case CAR:
					newShape = new Car(pGame, { randomGridReferencePoint.x,randomGridReferencePoint.y }, randomSize, randomAngle, randomFill, randomBorder);
					break;
				case ICECREAM:
					newShape = new IceCream(pGame, { randomGridReferencePoint.x,randomGridReferencePoint.y }, randomSize, randomAngle, randomFill, randomBorder);
					break;
				case HOUSE:
					newShape = new House(pGame, { randomGridReferencePoint.x,randomGridReferencePoint.y }, randomSize, randomAngle, randomFill, randomBorder);
					break;
				case ROCKET:
					newShape = new Rocket(pGame, { randomGridReferencePoint.x,randomGridReferencePoint.y }, randomSize, randomAngle, randomFill, randomBorder);
					break;
				}

				pGrid->addShape(newShape);
			}
		}
		else {
			for (int i = 0; i < currentShapeCount; i++) {
				randomFill = BLACK;
				randomBorder = BLACK;
				randomSize = getRandomNum(sizeArr, 4);
				randomAngle = getRandomNum(angleArr, 4);
				randomShape = getRandomShape();
				randomGridReferencePoint = pGrid->getRandomGridPoint();

				switch (randomShape) {
				case SIGN:
					newShape = new Sign(pGame, { randomGridReferencePoint.x,randomGridReferencePoint.y }, randomSize, randomAngle, randomFill, randomBorder);
					break;
				case TREE:
					newShape = new Tree(pGame, { randomGridReferencePoint.x,randomGridReferencePoint.y }, randomSize, randomAngle, randomFill, randomBorder);
					break;
				case CAR:
					newShape = new Car(pGame, { randomGridReferencePoint.x,randomGridReferencePoint.y }, randomSize, randomAngle, randomFill, randomBorder);
					break;
				case ICECREAM:
					newShape = new IceCream(pGame, { randomGridReferencePoint.x,randomGridReferencePoint.y }, randomSize, randomAngle, randomFill, randomBorder);
					break;
				case HOUSE:
					newShape = new House(pGame, { randomGridReferencePoint.x,randomGridReferencePoint.y }, randomSize, randomAngle, randomFill, randomBorder);
					break;
				case ROCKET:
					newShape = new Rocket(pGame, { randomGridReferencePoint.x,randomGridReferencePoint.y }, randomSize, randomAngle, randomFill, randomBorder);
					break;
				}

				pGrid->addShape(newShape);
			}
		}
		pGrid->drawGrid();
		pGrid->drawActiveShape();

		pGrid->drawLevelShapes();
		pGame->setRandomizationStatus(true);
		pGame->clearStatusBar();
	}
	
}


operHint::operHint(game* r_pGame) : operation(r_pGame)
{
}

void operHint::Act()
{
	grid* pGrid = pGame->getGrid();
	shape* currentShape = pGrid->getActiveShape();
	shape** Array =  pGrid->getArrayElements();
	int TrueFRed;
	int TrueFGreen;
	int TrueFBlue;
	int TrueBRed;
	int TrueBGreen;
	int TrueBBlue;
	
	for (int i = 0; i < pGrid->getShapeCount(); i++)
	{
		if (Array[i]->getName() == currentShape->getName())
		{
			TrueFRed= 255- Array[i]->getFillColor().ucRed;
			TrueFGreen = 255 - Array[i]->getFillColor().ucGreen;
			TrueFBlue = 255 - Array[i]->getFillColor().ucBlue;

			Array[i]->setFillColor(color(TrueFRed, TrueFGreen, TrueFBlue));

			TrueBRed = 255 - Array[i]->getBorderColor().ucRed;
			TrueFGreen = 255 - Array[i]->getBorderColor().ucGreen;
			TrueFBlue = 255 - Array[i]->getBorderColor().ucBlue;
			
			Array[i]->setBorderColor(color(TrueBRed, TrueBGreen, TrueBBlue));
			Array[i]->draw();
		}
		
	}

}
