#include "grid.h"
#include "game.h"
#include "gameConfig.h"
#include<cstdlib>
#include<time.h>
#include <algorithm>
#include<iostream>


grid::grid(point r_uprleft, int wdth, int hght, game* pG)
{
	uprLeft = r_uprleft;
	height = hght;
	width = wdth;
	pGame = pG;
	rows = height / config.gridSpacing;
	cols = width / config.gridSpacing;
	shapeCount = 0;

	for (int i = 0; i < MaxShapeCount; i++)
		shapeList[i] = nullptr;

	activeShape = nullptr;

	gridPoints = new point * [rows];

	for (int r = 0; r < rows; r++) {
		gridPoints[r] = new point[cols];

		for (int c = 0; c < cols; c++) {
			int x = c * config.gridSpacing;
			int y = r * config.gridSpacing + uprLeft.y;

			gridPoints[r][c].x = x;
			gridPoints[r][c].y = y;
		}
	}
}

grid::~grid()
{
	for (int i = 0; i < shapeCount; i++) {
		delete shapeList[i];
	}
	for (int i = 0; i < rows; i++) {
		delete[] gridPoints[i];
	}
	delete[] gridPoints;

}
//
//void grid::draw() const
//{
//	clearGridArea();
//	window* pWind = pGame->getWind();
//	
//	pWind->SetPen(config.gridDotsColor,1);
//	pWind->SetBrush(config.gridDotsColor);
//
//	//draw dots showing the grid reference points
//	for (int r = 1; r < rows; r++)
//		for (int c = 0; c < cols; c++)
//			pWind->DrawCircle(c * config.gridSpacing, r * config.gridSpacing + uprLeft.y, 1);
//			//pWind->DrawPixel(c * config.gridSpacing, r * config.gridSpacing + uprLeft.y);
//
//	//Draw ALL shapes
//	for (int i = 0; i < shapeCount; i++)
//			if (shapeList[i])
//				shapeList[i]->draw();	//draw each shape
//
//	//Draw the active shape
//	if(activeShape)
//		activeShape->draw();
//}

void grid::drawActiveShape()const {
	if (activeShape)
		activeShape->draw();
}

void grid::drawLevelShapes() {
	//Draw ALL shapes
	setArrSize(shapeCount);
	for (int i = 0; i < shapeCount; i++) {
		if (shapeList[i])
		{
			shapeList[i]->draw();	//draw each shape
			/*Arr[i]->setBorderColor(shapeList[i]->getBorderColor());
			Arr[i]->setFillColor(shapeList[i]->getBorderColor());
			Arr[i]->setAngle(shapeList[i]->getAngle());
			Arr[i]->setName(shapeList[i]->getName());
			Arr[i]->setRefPoint(shapeList[i]->getRefPoint());
			Arr[i]->setSize(shapeList[i]->getSize());*/
		}
	}
}

void grid::drawGrid()const {
	clearGridArea();
	window* pWind = pGame->getWind();

	pWind->SetPen(config.gridDotsColor, 1);
	pWind->SetBrush(config.gridDotsColor);

	//draw dots showing the grid reference points
	for (int r = 1; r < rows; r++)
		for (int c = 0; c < cols; c++)
			pWind->DrawCircle(c * config.gridSpacing, r * config.gridSpacing + uprLeft.y, 1);
	//pWind->DrawPixel(c * config.gridSpacing, r * config.gridSpacing + uprLeft.y);
}



void grid::clearGridArea() const
{
	window* pWind = pGame->getWind();
	pWind->SetPen(config.bkGrndColor, 1);
	pWind->SetBrush(config.bkGrndColor);
	pWind->DrawRectangle(uprLeft.x, uprLeft.y, uprLeft.x + width, uprLeft.y + height);
}

//Adds a shape to the randomly created shapes list.
bool grid::addShape(shape* newShape)
{
	bool val = false;
	//TODO:
	// 1- Check that the shape can be drawn witout being clipped by grid boundaries
	// 2- check shape count doesn't exceed maximum count
	// return false if any of the checks fail

	if (shapeCount < MaxShapeCount) {
		val = true;
		shapeList[shapeCount++] = newShape;
	}
	//Here we assume that the above checks are passed
	return val;
}

void grid::setActiveShape(shape* actShape)
{
	activeShape = actShape;
}

shape* grid::getActiveShape()
{
	return activeShape;
}


point grid::getRandomGridPoint() {
	srand(time(nullptr) + rand());
	int x = rand() % rows;
	int y = rand() % cols;

	point randomGrid = gridPoints[x][y];
	return randomGrid;

}



void grid::DELshapes()
{
	if (activeShape != nullptr) {
		delete activeShape; // after deltete(dangling)
		activeShape = nullptr;// activeShape(pointer)=nullptr
		drawGrid();// call again
	}
}

void grid::setShapeCount(int s) {
	shapeCount = s;
}

int grid::getShapeCount()const {
	return shapeCount;
}


int grid::getMaxShapeCount()const {
	return MaxShapeCount;
}

bool grid::isShapeListEmpty() {
	bool val = true;
	for (int i = 0; i < shapeCount; ++i) {
		if (shapeList[i] != nullptr) {
			val = false;
		}
	}
	return val;
}
void grid::nullifyShapeList() {
	for (int i = 0; i < MaxShapeCount; ++i) {
		shapeList[i] = nullptr; // Set each element to nullptr
	}
}

void grid::setArrSize(int n)
{
	if (Arr)
	{
		delete[] Arr;
		Arr = nullptr;
	}
	Arr = new shape* [n];
}

shape** grid::getArrayElements() const
{
	return Arr;
}
