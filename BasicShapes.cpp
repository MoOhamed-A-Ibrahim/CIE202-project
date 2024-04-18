#include "BasicShapes.h"
#include "gameConfig.h"
#include "game.h"

////////////////////////////////////////////////////  class Rect  ///////////////////////////////////////

Rect::Rect(game* r_pGame, point ref, int r_hght, int r_wdth):shape(r_pGame,ref)
{
	pGame = r_pGame;
	hght = r_hght;
	wdth = r_wdth;
}

void Rect::draw() const
{
	window* pW = pGame->getWind();	//get interface window
	pW->SetPen(config.penColor, config.penWidth);
	pW->SetBrush(config.fillColor);
	point upperLeft, lowerBottom;
	upperLeft.x = RefPoint.x - wdth / 2;
	upperLeft.y = RefPoint.y -hght / 2;
	lowerBottom.x = RefPoint.x + wdth / 2;
	lowerBottom.y = RefPoint.y + hght / 2;

	pW->DrawRectangle(upperLeft.x, upperLeft.y, lowerBottom.x, lowerBottom.y, FILLED);
}
void Rect::setHeight(int height) {
	hght = height;
}
void Rect::setWidth(int width) {
	wdth = width;
}
int Rect::getHeight() const {
	return hght;
}
int Rect::getWidth() const {
	return wdth;
}
void Rect::resizeUp(double factor) {
	setHeight(hght * factor);
	setWidth(wdth * factor);
}
void Rect::resizeDown(double factor) {
	setHeight(hght / factor);
	setWidth(wdth /factor);
}
////////////////////////////////////////////////////  class circle  ///////////////////////////////////////
//TODO: Add implementation for class circle here
circle::circle(game* r_pGame, point ref, int r):shape(r_pGame,ref)
{
	rad = r;
}

void circle::draw() const
{
	window* pW = pGame->getWind();	//get interface window
	pW->SetPen(borderColor, config.penWidth);
	pW->SetBrush(fillColor);
	pW->DrawCircle(RefPoint.x, RefPoint.y, rad, FILLED);
}
void circle::setRadius(int radius) {
	rad = radius;
}
int circle::getRadius() const {
	return rad;
}
void circle::resizeUp(double factor) {
	setRadius(rad * factor);
}
void circle::resizeDown(double factor) {
	setRadius(rad / factor);
}

///Triangle class///////
triangle::triangle(game* r_pGame, point ref, int r_base) :shape(r_pGame, ref)
{
	base = r_base;
}

void triangle::draw() const
{
	window* pW = pGame->getWind();	//get interface window
	pW->SetPen(config.penColor, config.penWidth);
	pW->SetBrush(config.fillColor);
	point upperpoint, leftlowerpoint, rightlowerpoint; /// refrence point is centriod 
	leftlowerpoint.x = RefPoint.x - 0.5 * base;
	leftlowerpoint.y = RefPoint.y + (sqrt(3) / 6.0) * base;
	upperpoint.x = RefPoint.x;
	upperpoint.y = RefPoint.y - (sqrt(3) / 3.0) * base;
	rightlowerpoint.x = RefPoint.x + 0.5 * base;
	rightlowerpoint.y = RefPoint.y + (sqrt(3) / 6) * base;
	pW->DrawTriangle(leftlowerpoint.x, leftlowerpoint.y, rightlowerpoint.x, rightlowerpoint.x, upperpoint.x, upperpoint.y, FILLED);

}

void triangle::setbase(int BASE)
{
	base = BASE;
}

int triangle::getbase() const
{
	return base;
}

void triangle::resizeDown(double factor){
	setbase(base / factor);
}

void triangle::resizeUp(double factor) {
	setbase(base * factor);
}
