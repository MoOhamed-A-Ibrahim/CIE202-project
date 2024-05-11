#pragma once
#include <string>
using namespace std;
#include "CMUgraphicsLib\CMUgraphics.h"

class game;     //forward declaration

struct point
{
	int x, y;
};


//Base class for all shapes including Basic shapes, Composite shapes
class shape
{
protected:
	string name;
	point RefPoint;		//Each shape must have a reference point
	game* pGame;        //pointer to game object
	color fillColor;	//shape fill color
	color borderColor;	//shape border color
	double PI_Value = 22.0 / 7.0;
	double ROT_angle[5] = { 0,  PI_Value / 2.0,  PI_Value, 3.0 * PI_Value / 2.0, 2.0 * PI_Value };
	double size;
	double angle;

public:
	shape(game* r_pGame, point ref);
	virtual void draw() const = 0;//for a shape to draw itself on the screen
	virtual void resizeUp(double factor) = 0;
	virtual void resizeDown(double factor) = 0;
	void setRefPoint(point p);
	point getRefPoint() const;
	string getName() const;

	virtual void moveUp(double dist);
	virtual void moveDown(double dist);
	virtual void moveRight(double dist);
	virtual void moveLeft(double dist);

	color getFillColor() const;
	void setFillColor(color newColor);

	color getBorderColor() const;
	void setBorderColor(color newColor);

	double getSize() const;
	void setSize(double newSize);

	double getAngle()const;
	void setAngle(double ang);

	//-- The following functions should be supported by the shape class
	//-- It should be overridden by each inherited shape
	//-- Decide the parameters that you should pass to each function	

	virtual void rotate() = 0;	//Rotate the shape
	//virtual void move() = 0;		//Move the shape
	//virtual void save(ofstream &OutFile) = 0;	//Save the shape parameters to the file
	//virtual void load(ifstream &Infile) = 0;	//Load the shape parameters to the file

};
