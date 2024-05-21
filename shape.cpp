#include "shape.h"
#include "game.h"
#include "gameConfig.h"
#include <fstream>

shape::shape(game* r_pGame, point ref)
{
	RefPoint = ref;
	pGame = r_pGame;
	fillColor = config.fillColor;
	borderColor = config.penColor;
	angle = 0;
	size = 1;
}



void shape::setRefPoint(point p)
{
	RefPoint = p;
}

point shape::getRefPoint() const {
	return RefPoint;
}


void shape::moveUp(double dist) {
	point oldRefPoint = this->getRefPoint();
	point newRefPoint;
	newRefPoint.x = oldRefPoint.x;
	newRefPoint.y = oldRefPoint.y - dist;

	this->setRefPoint(newRefPoint);
}

void shape::moveDown(double dist) {
	point oldRefPoint = this->getRefPoint();
	point newRefPoint;
	newRefPoint.x = oldRefPoint.x;
	newRefPoint.y = oldRefPoint.y + dist;

	this->setRefPoint(newRefPoint);
}

void shape::moveRight(double dist) {
	point oldRefPoint = this->getRefPoint();
	point newRefPoint;
	newRefPoint.x = oldRefPoint.x + dist;
	newRefPoint.y = oldRefPoint.y;

	this->setRefPoint(newRefPoint);
}

void shape::moveLeft(double dist) {
	point oldRefPoint = this->getRefPoint();
	point newRefPoint;
	newRefPoint.x = oldRefPoint.x - dist;
	newRefPoint.y = oldRefPoint.y;

	this->setRefPoint(newRefPoint);
}

string shape::getName() const
{
	return name;
}

color shape::getFillColor() const {
	return fillColor;
}

void shape::setFillColor(color newColor) {
	fillColor = newColor;
}

color shape::getBorderColor() const {
	return borderColor;
}

void shape::setBorderColor(color newColor) {
	borderColor = newColor;
}

double shape::getSize() const {
	return size;
}

void shape::setSize(double newSize) {
	size = newSize;
}
void shape::setName(string d)
{
	this->name = d;
}

double shape::getAngle() const {
	return angle;
}

void shape::setAngle(double newSize) {
	this->angle = newSize;
}

void shape::fileMyself(string txt)
{
	ofstream file;
	file.open(txt, std::ios::app);

	int intgername = int(name[0]);

	int pointx = RefPoint.x;
	int pointy = RefPoint.y;

	unsigned char fCR = fillColor.ucRed;
	unsigned char fCG = fillColor.ucGreen;
	unsigned char fCB = fillColor.ucBlue;
	 		 
	unsigned char bCR = borderColor.ucRed;
	unsigned char bCG = borderColor.ucGreen;
	unsigned char bCB = borderColor.ucBlue;

	file << intgername << " " << pointx << " " << pointy << " " << size << " " << angle << " "
		<< fCR << " " << fCG << " " << fCB << " "
		<< bCR << " " << bCG << " " << bCB << endl;

	file.close();
}

point shape::getBoundaryPointMin()const {
	return boundaryPointMin;
}
void shape::setBoundaryPointMin(point newBoundaryPointMin) {
	boundaryPointMin = newBoundaryPointMin;
}


point shape::getBoundaryPointMax()const {
	return boundaryPointMax;
}

void shape::setBoundaryPointMax(point newBoundaryPointMax) {
	boundaryPointMax = newBoundaryPointMax;
}
