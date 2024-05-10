#include "operations.h"
#include "game.h"
#include "CompositeShapes.h"
#include <fstream>
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
	///
}


operMoveUp::operMoveUp(game* r_pGame) :operation(r_pGame)
{
}

void operMoveUp::Act() {
	grid* pGrid = pGame->getGrid();
	shape* currentShape = pGrid->getActiveShape();
	currentShape->moveUp(config.gridSpacing);
	pGrid->setActiveShape(currentShape);
}

operMoveDown::operMoveDown(game* r_pGame) :operation(r_pGame)
{
}

void operMoveDown::Act() {
	grid* pGrid = pGame->getGrid();
	shape* currentShape = pGrid->getActiveShape();
	currentShape->moveDown(config.gridSpacing);
	pGrid->setActiveShape(currentShape);
}

operMoveRight::operMoveRight(game* r_pGame) :operation(r_pGame)
{
}

void operMoveRight::Act() {
	grid* pGrid = pGame->getGrid();
	shape* currentShape = pGrid->getActiveShape();
	currentShape->moveRight(config.gridSpacing);
	pGrid->setActiveShape(currentShape);
}

operMoveLeft::operMoveLeft(game* r_pGame) :operation(r_pGame)
{
}

void operMoveLeft::Act() {
	grid* pGrid = pGame->getGrid();
	shape* currentShape = pGrid->getActiveShape();
	currentShape->moveLeft(config.gridSpacing);
	pGrid->setActiveShape(currentShape);
}

operSaveProgress::operSaveProgress(game* r_pGame) : operation(r_pGame)
{
}

void operSaveProgress::Act()
{
	grid* pGrid = pGame->getGrid();
	shape* currentShape = pGrid->getActiveShape();
	string name = currentShape->getName();
	int level = pGame->getLevel();
	int lives = pGame->getLives();
	int score = pGame->getScore();
	ofstream outfile;
	outfile.open("Progress//Progress.txt");
	outfile << name << endl << level << endl << lives << endl << score << endl;
	outfile.close();
}