#pragma once
#include "CompositeShapes.h"

class game;

class grid
{
	enum { MaxShapeCount = 1000 };	//assuming max shape count = 1000

	int rows, cols;	//numner of rows and columns in the grid to draw grid points
	int height, width;
	point uprLeft;	//upper left point of the grid

	//ShapeList should hold the RANDOMLY generated shapes
	shape* shapeList[MaxShapeCount];	//2D array of shape pointers

	shape* activeShape;	//The shape that the user works on to match to the ranom shapes

	int shapeCount;		//current number of shapes in the list
	game* pGame;
	point** gridPoints;
public:
	grid(point r_uprleft, int r_width, int r_height, game* r_pGame);
	~grid();
	//void draw() const;
	void drawGrid()const;
	void drawActiveShape()const;
	void drawLevelShapes()const;
	void clearGridArea() const;
	bool addShape(shape* newShape);
	void setActiveShape(shape* actShape);
	int getShapeCount()const;
	void setShapeCount(int s);
	int getMaxShapeCount()const;
	/////////
	void DELshapes(); // Delete the grid
	shape* getActiveShape();  // pointer to
	bool isShapeListEmpty();
	void nullifyShapeList();
	point getRandomGridPoint();

	point** getGridPoints() const;
};



