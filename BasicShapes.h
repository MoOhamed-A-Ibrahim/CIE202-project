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
	int hght, wdth;	//height and width of the recangle
public:

	Rect(game* r_pGame, point ref, int r_hght, int r_wdth);
	virtual void draw() const;
	void setHeight(int height);
	void setWidth(int width);
	int getHeight() const;
	int getWidth() const;
	void resizeUp(double factor);
	void resizeDown(double factor);
};


////////////////////////////////////////////////////  class circle  ///////////////////////////////////////
//Reference point of the circle is its center
class circle :public shape
{
	//Add data memebrs for class circle
	int rad;
public:	
	circle(game* r_pGame, point ref, int r);	//add more parameters for the constructor if needed
	virtual void draw() const;
	void setRadius(int radius);
	int getRadius() const;
	void resizeUp(double factor);
	void resizeDown(double factor);
};

class triangle :public shape {
	int base;
public:
	triangle(game* r_pGame, point ref, int r_base);
	virtual void draw() const;
	void setbase(int BASE);
	int getbase()const;
	void resizeUp(double factor);
	void resizeDown(double factor);
};
