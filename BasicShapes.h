//Header file for Basic shapes in the game
#pragma once
#include "shape.h"

////////////////////////////////////////////////////  class Rect  ///////////////////////////////////////
//Rectanle class
/*							wdth
					---------------------
					|					|
			hght    |		 x			|     x is the reference point of the rectangle
					|					|
					--------------------
*/


class Rect:public shape
{
	double hght, wdth;	//height and width of the recangle
public:

	Rect(game* r_pGame, point ref, double r_hght, double r_wdth);
	virtual void draw() const;
	void setHeight(double height);
	void setWidth(double width);
	double getHeight() const;
	double getWidth() const;
	virtual void resizeUp(double factor);
	virtual void resizeDown(double factor);
	virtual void rotate(double deg);
};


////////////////////////////////////////////////////  class circle  ///////////////////////////////////////
//Reference point of the circle is its center
class circle :public shape
{
	//Add data memebrs for class circle
	double rad;
public:	
	circle(game* r_pGame, point ref, double r);	//add more parameters for the constructor if needed
	virtual void draw() const;
	void setRadius(double radius);
	double getRadius() const;
	virtual void resizeUp(double factor);
	virtual void resizeDown(double factor);
	virtual void rotate(double deg);
};

class triangle :public shape {
	double base;
public:
	triangle(game* r_pGame, point ref, double r_base);
	virtual void draw() const;
	void setbase(double BASE);
	double getbase()const;
	virtual void resizeUp(double factor);
	virtual void resizeDown(double factor);
	virtual void rotate(double deg);
};
