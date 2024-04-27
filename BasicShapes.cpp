#include "BasicShapes.h"
#include "gameConfig.h"
#include "game.h"

////////////////////////////////////////////////////  class Rect  ///////////////////////////////////////

Rect::Rect(game* r_pGame, point ref, double r_hght, double r_wdth):shape(r_pGame,ref)
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
void Rect::setHeight(double height) {
	hght = height;
}
void Rect::setWidth(double width) {
	wdth = width;
}
double Rect::getHeight() const {
	return hght;
}
double Rect::getWidth() const {
	return wdth;
}
void Rect::resizeUp(double factor) {
	setHeight(hght * factor);
	setWidth(wdth * factor);
}
void Rect::resizeDown(double factor) {
	setHeight(hght / factor);
	setWidth(wdth / factor);
}
void Rect::rotate(double deg)
{


	double temp = wdth;
	wdth = hght;
	hght = temp;


}

////////////////////////////////////////////////////  class circle  ///////////////////////////////////////
//TODO: Add implementation for class circle here
circle::circle(game* r_pGame, point ref, double r):shape(r_pGame,ref)
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
void circle::setRadius(double radius) {
	rad = radius;
}
double circle::getRadius() const {
	return rad;
}
void circle::resizeUp(double factor) {
	setRadius(rad * factor);
}
void circle::resizeDown(double factor) {
	setRadius(rad / factor);
}
void circle::rotate(double deg)
{
	
}
///Triangle class///////
triangle::triangle(game* r_pGame, point ref, double r_base) :shape(r_pGame, ref)
{
	base = r_base;
	width = 0;

}

void triangle::draw() const
{
	window* pW = pGame->getWind();	//get interface window
	pW->SetPen(config.penColor, config.penWidth);
	pW->SetBrush(config.fillColor);
	point upperpoint, leftlowerpoint, rightlowerpoint; /// refrence point is centriod 
	leftlowerpoint.x = RefPoint.x - 0.5 * base - (sqrt(3) / 6.0) * width;
	leftlowerpoint.y = RefPoint.y + (sqrt(3) / 6.0) * base - 0.5 * width;
	upperpoint.x = RefPoint.x + (sqrt(3) / 3.0) * width;
	upperpoint.y = RefPoint.y - (sqrt(3) / 3.0) * base;
	rightlowerpoint.x = RefPoint.x + 0.5 * base - (sqrt(3) / 6) * width;
	rightlowerpoint.y = RefPoint.y + (sqrt(3) / 6) * base + 0.5 * width;
	pW->DrawTriangle((int)leftlowerpoint.x, (int)leftlowerpoint.y, (int)rightlowerpoint.x, (int)rightlowerpoint.y, (int)upperpoint.x, (int)upperpoint.y, FILLED);

}

void triangle::setbase(double BASE)
{
	base = BASE;
}

double triangle::getbase() const
{
	return base;
}

void triangle::resizeDown(double factor) {
	setbase(base / factor);
}

void triangle::resizeUp(double factor) {
	setbase(base * factor);
}

void triangle::rotate(double deg)
{

	int temp;
	temp = base;
	if (base != 0)
	{
		base = width;
	}
	if (width != 0)
	{
		base = -width;
	}
	width = temp;
	draw();
}