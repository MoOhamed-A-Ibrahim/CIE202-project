#include "CompositeShapes.h"
#include "gameConfig.h"
#include<iostream>
using namespace std;

////////////////////////////////////////////////////  class Sign  ///////////////////////////////////////
Sign::Sign(game* r_pGame, point ref, double cSize, double cAngle, color cFill, color cBorder) :shape(r_pGame, ref)
{
	size = cSize;
	angle = cAngle;
	name = "Sign";
	double resizeFactor;
	//calc the ref point of the Sign base and top rectangles relative to the Sign shape
	point topRef = ref;	//top rect ref is the same as the sign
	point baseRef = { ref.x, ref.y + config.signShape.topHeight / 2 + config.signShape.baseHeight / 2 };


	top = new Rect(pGame, topRef, config.signShape.topHeight, config.signShape.topWdth, cFill, cBorder);
	base = new Rect(pGame, baseRef, config.signShape.baseHeight, config.signShape.baseWdth, cFill, cBorder);

	this->boundaryPointMin.x = top->getWidth() * size / 2;
	this->boundaryPointMin.y = config.toolBarHeight + top->getHeight() / 2;

	this->boundaryPointMax.x = config.windWidth - top->getWidth() / 2;
	this->boundaryPointMax.y = config.windHeight - config.statusBarHeight - base->getHeight() - top->getHeight() / 2;

	if (size < 1) {
		resizeFactor = 1 / size;
		this->resizeDown(resizeFactor);
	}
	else if (size > 1) {
		resizeFactor = size;
		this->resizeUp(resizeFactor);
	}
	if (angle == angleArr[1]) {
		this->rotate();
	}
	else if (angle == angleArr[2]) {
		this->rotate();
		this->rotate();
	}
	else if (angle == angleArr[3]) {
		this->rotate();
		this->rotate();
		this->rotate();
	}
}

void Sign::setRefPoint(point P) {
	point newBaseRef;
	if (this->getAngle() == ROT_angle[0] || this->getAngle() == ROT_angle[4]) {
		top->setRefPoint(P);
		newBaseRef.x = P.x;
		newBaseRef.y = P.y + top->getHeight() / 2 + base->getHeight() / 2;
		base->setRefPoint(newBaseRef);
	}
	else if (this->getAngle() == ROT_angle[1]) {
		top->setRefPoint(P);
		point newBaseRef;
		newBaseRef.x = P.x - top->getHeight() / 2 - base->getHeight() / 2;
		newBaseRef.y = P.y;
		base->setRefPoint(newBaseRef);
	}
	else if (this->getAngle() == ROT_angle[2]) {
		top->setRefPoint(P);
		point newBaseRef;
		newBaseRef.x = P.x;
		newBaseRef.y = P.y - top->getHeight() / 2 - base->getHeight() / 2;
		base->setRefPoint(newBaseRef);
	}
	else if (this->getAngle() == ROT_angle[3]) {
		top->setRefPoint(P);
		point newBaseRef;
		newBaseRef.x = P.x + top->getHeight() / 2 + base->getHeight() / 2;
		newBaseRef.y = P.y;
		base->setRefPoint(newBaseRef);
	}
}
void Sign::draw() const
{
	base->draw();
	top->draw();
}
void Sign::rotate()
{
	point oldRefPoint = top->getRefPoint();

	base->rotate();
	top->rotate();

	double newTopHeight = top->getHeight();
	double newBaseHeight = base->getHeight();


	if (*SignRotation == ROT_angle[4]) {
		SignRotation = ROT_angle + 1;
	}
	else {
		SignRotation = SignRotation + 1;
	}

	point baseRef;
	baseRef.x = (0 * cos(*SignRotation) - ((0 + newTopHeight / 2.0 + newBaseHeight / 2.0) * sin(*SignRotation))) + oldRefPoint.x;
	baseRef.y = (0 * sin(*SignRotation) + ((0 + newTopHeight / 2.0 + newBaseHeight / 2.0) * cos(*SignRotation))) + oldRefPoint.y;
	if (*SignRotation == ROT_angle[0] || *SignRotation == ROT_angle[4]) {
		this->boundaryPointMin.x = top->getWidth() / 2;
		this->boundaryPointMin.y = config.toolBarHeight + top->getHeight() / 2 + 2 * config.gridSpacing;

		this->boundaryPointMax.x = config.windWidth - top->getWidth() / 2;
		this->boundaryPointMax.y = config.windHeight - config.statusBarHeight - base->getHeight() - top->getHeight() / 2;
	}
	else if (*SignRotation == ROT_angle[1]) {
		this->boundaryPointMin.x = base->getHeight() + top->getHeight() / 2;
		this->boundaryPointMin.y = config.toolBarHeight + top->getWidth() / 2 + 4 * config.gridSpacing;

		this->boundaryPointMax.x = config.windWidth - top->getHeight() / 2;
		this->boundaryPointMax.y = config.windHeight - config.statusBarHeight - top->getWidth() / 2;
	}
	else if (*SignRotation == ROT_angle[2]) {
		this->boundaryPointMin.x = top->getWidth() / 2;
		this->boundaryPointMin.y = config.toolBarHeight + base->getHeight() + top->getHeight() / 2 + 2 * config.gridSpacing;

		this->boundaryPointMax.x = config.windWidth - top->getWidth() / 2;
		this->boundaryPointMax.y = config.windHeight - config.statusBarHeight - top->getHeight() / 2;
	}
	else if (*SignRotation == ROT_angle[3]) {
		this->boundaryPointMin.x = top->getHeight() / 2;
		this->boundaryPointMin.y = config.toolBarHeight + top->getWidth() / 2 + 4 * config.gridSpacing;

		this->boundaryPointMax.x = config.windWidth - base->getHeight() - top->getHeight() / 2;
		this->boundaryPointMax.y = config.windHeight - config.statusBarHeight - top->getWidth() / 2;
	}
	base->setRefPoint(baseRef);
	angle = *SignRotation;
}
point Sign::getRefPoint()const {
	return top->getRefPoint();
}

void Sign::moveUp(double dist) {
	top->moveUp(dist);
	base->moveUp(dist);
}

void Sign::moveDown(double dist) {
	top->moveDown(dist);
	base->moveDown(dist);
}

void Sign::moveRight(double dist) {
	top->moveRight(dist);
	base->moveRight(dist);
}

void Sign::moveLeft(double dist) {
	top->moveLeft(dist);
	base->moveLeft(dist);
}




void Sign::resizeUp(double factor) {
	point oldRefPoint = top->getRefPoint();

	top->resizeUp(factor);
	base->resizeUp(factor);

	double newTopHeight = top->getHeight();
	double newBaseHeight = base->getHeight();

	point refBase;
	refBase.x = oldRefPoint.x;
	refBase.y = oldRefPoint.y + newTopHeight / 2 + newBaseHeight / 2;

	point newRefBase;

	newRefBase.x = oldRefPoint.x + (refBase.x - oldRefPoint.x) * cos(*SignRotation) - (refBase.y - oldRefPoint.y) * sin(*SignRotation);
	newRefBase.y = oldRefPoint.y + (refBase.x - oldRefPoint.x) * sin(*SignRotation) + (refBase.y - oldRefPoint.y) * cos(*SignRotation);


	base->setRefPoint(newRefBase);

	size *= factor;
}

void Sign::resizeDown(double factor) {
	point oldRefPoint = top->getRefPoint();

	top->resizeDown(factor);
	base->resizeDown(factor);

	double newTopHeight = top->getHeight();
	double newBaseHeight = base->getHeight();

	point refBase;
	refBase.x = oldRefPoint.x;
	refBase.y = oldRefPoint.y + newTopHeight / 2 + newBaseHeight / 2;

	point newRefBase;

	newRefBase.x = oldRefPoint.x + (refBase.x - oldRefPoint.x) * cos(*SignRotation) - (refBase.y - oldRefPoint.y) * sin(*SignRotation);
	newRefBase.y = oldRefPoint.y + (refBase.x - oldRefPoint.x) * sin(*SignRotation) + (refBase.y - oldRefPoint.y) * cos(*SignRotation);


	base->setRefPoint(newRefBase);

	size /= factor;

}



////////////////////////////////////////////////////////////////

Tree::Tree(game* r_pGame, point ref, double cSize, double cAngle, color cFill, color cBorder) :shape(r_pGame, ref)
{
	angle = cAngle;
	size = cSize;
	name = "Tree";
	double resizeFactor;
	point baseRef = ref;
	point layer_1_ref = { ref.x, ref.y - config.tree.baseHeight / 2 - config.tree.baseWdth };
	point layer_2_ref = { ref.x, ref.y - config.tree.baseHeight / 2 - 2 * config.tree.baseWdth };
	point layer_3_ref = { ref.x, ref.y - config.tree.baseHeight / 2 - 3 * config.tree.baseWdth };
	point apple_ref = layer_3_ref;

	base = new Rect(pGame, baseRef, config.tree.baseHeight, config.tree.baseWdth, cFill, cBorder);
	Layer_1 = new triangle(pGame, layer_1_ref, config.tree.triwdth, cFill, cBorder);
	Layer_2 = new triangle(pGame, layer_2_ref, config.tree.triwdth, cFill, cBorder);
	layer_3 = new triangle(pGame, layer_3_ref, config.tree.triwdth, cFill, cBorder);
	apple = new circle(pGame, apple_ref, config.tree.apple, cFill, cBorder);

	this->boundaryPointMin.x = layer_3->getbase() / 2;
	this->boundaryPointMin.y = config.toolBarHeight + layer_3->getHeight() / 2 + base->getHeight() / 2 + 3 * base->getWidth();

	this->boundaryPointMax.x = config.windWidth - layer_3->getbase() / 2;
	this->boundaryPointMax.y = config.windHeight - config.statusBarHeight - base->getHeight() / 2;

	if (size < 1) {
		resizeFactor = 1 / size;
		this->resizeDown(resizeFactor);
	}
	else if (size > 1) {
		resizeFactor = size;
		this->resizeUp(resizeFactor);
	}
	if (angle == angleArr[1]) {
		this->rotate();
	}
	else if (angle == angleArr[2]) {
		this->rotate();
		this->rotate();
	}
	else if (angle == angleArr[3]) {
		this->rotate();
		this->rotate();
		this->rotate();
	}

}

point Tree::getRefPoint()const {
	return base->getRefPoint();
}
void Tree::setRefPoint(point p) {
	base->setRefPoint(p);
	point newLayer1, newLayer2, newLayer3, newApple;
	double newBaseHeight = base->getHeight();
	double newBaseWidth = base->getWidth();

	if (this->getAngle() == ROT_angle[0] || this->getAngle() == ROT_angle[4]) {
		newLayer1.x = p.x;
		newLayer1.y = p.y - newBaseHeight / 2 - newBaseWidth;

		newLayer2.x = p.x;
		newLayer2.y = p.y - newBaseHeight / 2 - 2 * newBaseWidth;

		newLayer3.x = p.x;
		newLayer3.y = p.y - newBaseHeight / 2 - 3 * newBaseWidth;

		newApple = newLayer3;
	}
	else if (this->getAngle() == ROT_angle[1]) {
		newLayer1.x = p.x + newBaseWidth / 2 + newBaseHeight;
		newLayer1.y = p.y;

		newLayer2.x = p.x + newBaseWidth / 2 + 2 * newBaseHeight;
		newLayer2.y = p.y;

		newLayer3.x = p.x + newBaseWidth / 2 + 3 * newBaseHeight;
		newLayer3.y = p.y;

		newApple = newLayer3;
	}
	else if (this->getAngle() == ROT_angle[2]) {
		newLayer1.x = p.x;
		newLayer1.y = p.y + newBaseHeight / 2 + newBaseWidth;

		newLayer2.x = p.x;
		newLayer2.y = p.y + newBaseHeight / 2 + 2 * newBaseWidth;

		newLayer3.x = p.x;
		newLayer3.y = p.y + newBaseHeight / 2 + 3 * newBaseWidth;

		newApple = newLayer3;
	}
	else if (this->getAngle() == ROT_angle[3]) {
		newLayer1.x = p.x - newBaseWidth / 2 - newBaseHeight;
		newLayer1.y = p.y;

		newLayer2.x = p.x - newBaseWidth / 2 - 2 * newBaseHeight;
		newLayer2.y = p.y;

		newLayer3.x = p.x - newBaseWidth / 2 - 3 * newBaseHeight;
		newLayer3.y = p.y;

		newApple = newLayer3;
	}

	Layer_1->setRefPoint(newLayer1);
	Layer_2->setRefPoint(newLayer2);
	layer_3->setRefPoint(newLayer3);
	apple->setRefPoint(newLayer3);
}

void Tree::draw() const
{
	base->draw();
	Layer_1->draw();
	Layer_2->draw();
	layer_3->draw();
	apple->draw();
}

void Tree::resizeUp(double factor) {
	point oldRefPoint = base->getRefPoint();

	base->resizeUp(factor);
	Layer_1->resizeUp(factor);
	Layer_2->resizeUp(factor);
	layer_3->resizeUp(factor);
	apple->resizeUp(factor);

	double newBaseHeight = base->getHeight();
	double newBaseWidth = base->getWidth();


	point newRefLay1;
	point newRefLay2;
	point newRefLay3;

	if (*TreeRotation == ROT_angle[0] || *TreeRotation == ROT_angle[4]) {
		newRefLay1.x = oldRefPoint.x;
		newRefLay1.y = oldRefPoint.y - newBaseHeight / 2 - newBaseWidth;

		newRefLay2.x = oldRefPoint.x;
		newRefLay2.y = oldRefPoint.y - newBaseHeight / 2 - 2 * newBaseWidth;

		newRefLay3.x = oldRefPoint.x;
		newRefLay3.y = oldRefPoint.y - newBaseHeight / 2 - 3 * newBaseWidth;

	}
	else if (*TreeRotation == ROT_angle[1]) {
		newRefLay1.x = oldRefPoint.x + newBaseWidth / 2 + newBaseHeight;
		newRefLay1.y = oldRefPoint.y;

		newRefLay2.x = oldRefPoint.x + newBaseWidth / 2 + 2 * newBaseHeight;
		newRefLay2.y = oldRefPoint.y;

		newRefLay3.x = oldRefPoint.x + newBaseWidth / 2 + 3 * newBaseHeight;
		newRefLay3.y = oldRefPoint.y;

	}
	else if (*TreeRotation == ROT_angle[2]) {
		newRefLay1.x = oldRefPoint.x;
		newRefLay1.y = oldRefPoint.y + newBaseHeight / 2 + newBaseWidth;

		newRefLay2.x = oldRefPoint.x;
		newRefLay2.y = oldRefPoint.y + newBaseHeight / 2 + 2 * newBaseWidth;

		newRefLay3.x = oldRefPoint.x;
		newRefLay3.y = oldRefPoint.y + newBaseHeight / 2 + 3 * newBaseWidth;

	}
	else if (*TreeRotation == ROT_angle[3]) {
		newRefLay1.x = oldRefPoint.x - newBaseWidth / 2 - newBaseHeight;
		newRefLay1.y = oldRefPoint.y;

		newRefLay2.x = oldRefPoint.x - newBaseWidth / 2 - 2 * newBaseHeight;
		newRefLay2.y = oldRefPoint.y;

		newRefLay3.x = oldRefPoint.x - newBaseWidth / 2 - 3 * newBaseHeight;
		newRefLay3.y = oldRefPoint.y;

	}

	Layer_1->setRefPoint(newRefLay1);
	Layer_2->setRefPoint(newRefLay2);
	layer_3->setRefPoint(newRefLay3);
	apple->setRefPoint(newRefLay3);
	size *= factor;

}




void Tree::resizeDown(double factor) {
	point oldRefPoint = base->getRefPoint();

	base->resizeDown(factor);
	Layer_1->resizeDown(factor);
	Layer_2->resizeDown(factor);
	layer_3->resizeDown(factor);
	apple->resizeDown(factor);

	double newBaseHeight = base->getHeight();
	double newBaseWidth = base->getWidth();


	point newRefLay1;
	point newRefLay2;
	point newRefLay3;

	if (*TreeRotation == ROT_angle[0] || *TreeRotation == ROT_angle[4]) {
		newRefLay1.x = oldRefPoint.x;
		newRefLay1.y = oldRefPoint.y - newBaseHeight / 2 - newBaseWidth;

		newRefLay2.x = oldRefPoint.x;
		newRefLay2.y = oldRefPoint.y - newBaseHeight / 2 - 2 * newBaseWidth;

		newRefLay3.x = oldRefPoint.x;
		newRefLay3.y = oldRefPoint.y - newBaseHeight / 2 - 3 * newBaseWidth;

	}
	else if (*TreeRotation == ROT_angle[1]) {
		newRefLay1.x = oldRefPoint.x + newBaseWidth / 2 + newBaseHeight;
		newRefLay1.y = oldRefPoint.y;

		newRefLay2.x = oldRefPoint.x + newBaseWidth / 2 + 2 * newBaseHeight;
		newRefLay2.y = oldRefPoint.y;

		newRefLay3.x = oldRefPoint.x + newBaseWidth / 2 + 3 * newBaseHeight;
		newRefLay3.y = oldRefPoint.y;

	}
	else if (*TreeRotation == ROT_angle[2]) {
		newRefLay1.x = oldRefPoint.x;
		newRefLay1.y = oldRefPoint.y + newBaseHeight / 2 + newBaseWidth;

		newRefLay2.x = oldRefPoint.x;
		newRefLay2.y = oldRefPoint.y + newBaseHeight / 2 + 2 * newBaseWidth;

		newRefLay3.x = oldRefPoint.x;
		newRefLay3.y = oldRefPoint.y + newBaseHeight / 2 + 3 * newBaseWidth;

	}
	else if (*TreeRotation == ROT_angle[3]) {
		newRefLay1.x = oldRefPoint.x - newBaseWidth / 2 - newBaseHeight;
		newRefLay1.y = oldRefPoint.y;

		newRefLay2.x = oldRefPoint.x - newBaseWidth / 2 - 2 * newBaseHeight;
		newRefLay2.y = oldRefPoint.y;

		newRefLay3.x = oldRefPoint.x - newBaseWidth / 2 - 3 * newBaseHeight;
		newRefLay3.y = oldRefPoint.y;

	}

	Layer_1->setRefPoint(newRefLay1);
	Layer_2->setRefPoint(newRefLay2);
	layer_3->setRefPoint(newRefLay3);
	apple->setRefPoint(newRefLay3);
	size /= factor;

}

void Tree::rotate()
{
	point oldRefPoint = base->getRefPoint();



	double newBaseWdth = base->getWidth();
	double newBaseHeight = base->getHeight();


	Layer_1->rotate();
	Layer_2->rotate();
	layer_3->rotate();
	base->rotate();
	apple->rotate();
	if (*TreeRotation == ROT_angle[4]) {
		TreeRotation = ROT_angle + 1;

	}
	else {
		TreeRotation = TreeRotation + 1;
	}


	point bottomRef;
	point middleRef;
	point topRef;
	point appleRef;


	if (*TreeRotation == ROT_angle[1] || *TreeRotation == ROT_angle[3])
	{
		bottomRef.x = (0 * cos(*TreeRotation) - ((0 - newBaseHeight / 2 - newBaseWdth) * sin(*TreeRotation))) + oldRefPoint.x;
		bottomRef.y = (0 * sin(*TreeRotation) + ((0 - newBaseHeight / 2 - newBaseWdth) * cos(*TreeRotation))) + oldRefPoint.y;


		middleRef.x = (0 * cos(*TreeRotation) - ((0 - newBaseHeight / 2 - 2 * newBaseWdth) * sin(*TreeRotation))) + oldRefPoint.x;
		middleRef.y = (0 * sin(*TreeRotation) + ((0 - newBaseHeight / 2 - 2 * newBaseWdth) * cos(*TreeRotation))) + oldRefPoint.y;

		topRef.x = (0 * cos(*TreeRotation) - ((0 - newBaseHeight / 2 - 3 * newBaseWdth) * sin(*TreeRotation))) + oldRefPoint.x;
		topRef.y = (0 * sin(*TreeRotation) + ((0 - newBaseHeight / 2 - 3 * newBaseWdth) * cos(*TreeRotation))) + oldRefPoint.y;
	}
	else {
		bottomRef.x = (0 * cos(*TreeRotation) - ((0 - newBaseWdth / 2 - newBaseHeight) * sin(*TreeRotation))) + oldRefPoint.x;
		bottomRef.y = (0 * sin(*TreeRotation) + ((0 - newBaseWdth / 2 - newBaseHeight) * cos(*TreeRotation))) + oldRefPoint.y;


		middleRef.x = (0 * cos(*TreeRotation) - ((0 - newBaseWdth / 2 - 2 * newBaseHeight) * sin(*TreeRotation))) + oldRefPoint.x;
		middleRef.y = (0 * sin(*TreeRotation) + ((0 - newBaseWdth / 2 - 2 * newBaseHeight) * cos(*TreeRotation))) + oldRefPoint.y;

		topRef.x = (0 * cos(*TreeRotation) - ((0 - newBaseWdth / 2 - 3 * newBaseHeight) * sin(*TreeRotation))) + oldRefPoint.x;
		topRef.y = (0 * sin(*TreeRotation) + ((0 - newBaseWdth / 2 - 3 * newBaseHeight) * cos(*TreeRotation))) + oldRefPoint.y;

	}
	if (*TreeRotation == ROT_angle[0] || *TreeRotation == ROT_angle[4]) {
		this->boundaryPointMin.x = layer_3->getbase() / 2;
		this->boundaryPointMin.y = config.toolBarHeight + layer_3->getHeight() / 2 + base->getHeight() / 2 + 3 * base->getWidth() + 4 * config.gridSpacing;

		this->boundaryPointMax.x = config.windWidth - layer_3->getbase() / 2;
		this->boundaryPointMax.y = config.windHeight - config.statusBarHeight - base->getHeight() / 2;

	}
	else if (*TreeRotation == ROT_angle[1]) {
		this->boundaryPointMin.x = layer_3->getbase() / 2;
		this->boundaryPointMin.y = config.toolBarHeight + base->getHeight() / 2 + 2 * config.gridSpacing;

		this->boundaryPointMax.x = config.windWidth - layer_3->getbase() / 2;
		this->boundaryPointMax.y = config.windHeight - config.statusBarHeight - layer_3->getHeight() - base->getHeight() / 2;
	}
	else if (*TreeRotation == ROT_angle[2]) {
		this->boundaryPointMin.x = base->getHeight() / 2;
		this->boundaryPointMin.y = config.toolBarHeight + layer_3->getbase() / 2 + 2 * config.gridSpacing;

		this->boundaryPointMax.x = config.windWidth - (layer_3->getHeight() + base->getHeight() / 2);
		this->boundaryPointMax.y = config.windHeight - (config.statusBarHeight + layer_3->getbase() / 2);

	}
	else if (*TreeRotation == ROT_angle[3]) {
		this->boundaryPointMin.x = layer_3->getHeight() + base->getHeight() / 2;
		this->boundaryPointMin.y = config.toolBarHeight + layer_3->getbase() / 2 + 2 * config.gridSpacing;

		this->boundaryPointMax.x = config.windWidth - (base->getHeight() / 2);
		this->boundaryPointMax.y = config.windHeight - (config.statusBarHeight + layer_3->getbase() / 2);
	}

	Layer_2->setRefPoint(middleRef);
	Layer_1->setRefPoint(bottomRef);
	layer_3->setRefPoint(topRef);
	apple->setRefPoint(topRef);

	angle = *TreeRotation;
}




void Tree::moveUp(double dist) {
	base->moveUp(dist);
	Layer_1->moveUp(dist);
	Layer_2->moveUp(dist);
	layer_3->moveUp(dist);
	apple->moveUp(dist);
}

void Tree::moveDown(double dist) {
	base->moveDown(dist);
	Layer_1->moveDown(dist);
	Layer_2->moveDown(dist);
	layer_3->moveDown(dist);
	apple->moveDown(dist);
}

void Tree::moveRight(double dist) {
	base->moveRight(dist);
	Layer_1->moveRight(dist);
	Layer_2->moveRight(dist);
	layer_3->moveRight(dist);
	apple->moveRight(dist);
}

void Tree::moveLeft(double dist) {
	base->moveLeft(dist);
	Layer_1->moveLeft(dist);
	Layer_2->moveLeft(dist);
	layer_3->moveLeft(dist);
	apple->moveLeft(dist);
}
//////////////////////////////////////////////////////////////////////
Car::Car(game* r_pGame, point ref, double cSize, double cAngle, color cFill, color cBorder) :shape(r_pGame, ref)
{
	angle = cAngle;
	size = cSize;
	name = "Car";
	double resizeFactor;
	point baseRef = ref;
	point fWRef = { ref.x + (0.3 * config.car.baseWdth), ref.y + config.car.baseHeight / 2 };
	point PWRef = { ref.x - (0.3 * config.car.baseWdth), ref.y + config.car.baseHeight / 2 };

	base = new Rect(pGame, baseRef, config.car.baseHeight, config.car.baseWdth, cFill, cBorder);
	frontalWheel = new circle(pGame, fWRef, config.car.wheelRadius, cFill, cBorder);
	posteriorWheel = new circle(pGame, PWRef, config.car.wheelRadius, cFill, cBorder);

	this->boundaryPointMin.x = base->getWidth() / 2;
	this->boundaryPointMin.y = config.toolBarHeight + base->getHeight() / 2;

	this->boundaryPointMax.x = config.windWidth - base->getWidth() / 2;
	this->boundaryPointMax.y = config.windHeight - (config.statusBarHeight + 2 * frontalWheel->getRadius() + base->getHeight() / 2);


	if (size < 1) {
		resizeFactor = 1 / size;
		this->resizeDown(resizeFactor);
	}
	else if (size > 1) {
		resizeFactor = size;
		this->resizeUp(resizeFactor);
	}
	if (angle == angleArr[1]) {
		this->rotate();
	}
	else if (angle == angleArr[2]) {
		this->rotate();
		this->rotate();
	}
	else if (angle == angleArr[3]) {
		this->rotate();
		this->rotate();
		this->rotate();
	}

}
void Car::setRefPoint(point p) {
	base->setRefPoint(p);
	point newFw, newPw;
	double newBaseWidth = base->getWidth();
	double newBaseHeight = base->getHeight();
	if (this->getAngle() == ROT_angle[0] || this->getAngle() == ROT_angle[4]) {
		newFw.x = p.x + (0.3 * newBaseWidth);
		newFw.y = p.y + newBaseHeight / 2;
		newPw.x = p.x - (0.3 * newBaseWidth);
		newPw.y = p.y + newBaseHeight / 2;
	}
	else if (this->getAngle() == ROT_angle[1]) {
		newFw.x = p.x - newBaseWidth / 2;
		newFw.y = p.y + (0.3 * newBaseHeight);
		newPw.x = p.x - newBaseWidth / 2;
		newPw.y = p.y - (0.3 * newBaseHeight);
	}
	else if (this->getAngle() == ROT_angle[2]) {
		newFw.x = p.x - (0.3 * newBaseWidth);
		newFw.y = p.y - newBaseHeight / 2;
		newPw.x = p.x + (0.3 * newBaseWidth);
		newPw.y = p.y - newBaseHeight / 2;
	}
	else if (this->getAngle() == ROT_angle[3]) {
		newFw.x = p.x + newBaseWidth / 2;
		newFw.y = p.y - (0.3 * newBaseHeight);
		newPw.x = p.x + newBaseWidth / 2;
		newPw.y = p.y + (0.3 * newBaseHeight);
	}

	frontalWheel->setRefPoint(newFw);
	posteriorWheel->setRefPoint(newPw);
}
point Car::getRefPoint()const {
	return base->getRefPoint();
}

void Car::draw() const
{
	base->draw();
	frontalWheel->draw();
	posteriorWheel->draw();
}

void Car::resizeUp(double factor) {
	point oldRefPoint = base->getRefPoint();

	base->resizeUp(factor);
	frontalWheel->resizeUp(factor);
	posteriorWheel->resizeUp(factor);

	double newBaseWidth = base->getWidth();
	double newBaseHeight = base->getHeight();


	point newFrontRefPoint;
	point newPostRefPoint;

	if (*CarRotation == ROT_angle[0] || *CarRotation == ROT_angle[4]) {
		newFrontRefPoint.x = oldRefPoint.x + (0.3 * newBaseWidth);
		newPostRefPoint.x = oldRefPoint.x - (0.3 * newBaseWidth);

		newFrontRefPoint.y = oldRefPoint.y + newBaseHeight / 2;
		newPostRefPoint.y = oldRefPoint.y + newBaseHeight / 2;
	}
	else if (*CarRotation == ROT_angle[1]) {
		newFrontRefPoint.y = oldRefPoint.y + (0.3 * newBaseHeight);
		newPostRefPoint.y = oldRefPoint.y - (0.3 * newBaseHeight);

		newFrontRefPoint.x = oldRefPoint.x - newBaseWidth / 2;
		newPostRefPoint.x = oldRefPoint.x - newBaseWidth / 2;
	}
	else if (*CarRotation == ROT_angle[2]) {
		newFrontRefPoint.x = oldRefPoint.x + (0.3 * newBaseWidth);
		newPostRefPoint.x = oldRefPoint.x - (0.3 * newBaseWidth);

		newFrontRefPoint.y = oldRefPoint.y - newBaseHeight / 2;
		newPostRefPoint.y = oldRefPoint.y - newBaseHeight / 2;
	}
	else if (*CarRotation == ROT_angle[3]) {
		newFrontRefPoint.y = oldRefPoint.y - (0.3 * newBaseHeight);
		newPostRefPoint.y = oldRefPoint.y + (0.3 * newBaseHeight);

		newFrontRefPoint.x = oldRefPoint.x + newBaseWidth / 2;
		newPostRefPoint.x = oldRefPoint.x + newBaseWidth / 2;
	}
	frontalWheel->setRefPoint(newFrontRefPoint);
	posteriorWheel->setRefPoint(newPostRefPoint);
	size *= 2;
}




void Car::resizeDown(double factor) {
	point oldRefPoint = base->getRefPoint();

	base->resizeDown(factor);
	frontalWheel->resizeDown(factor);
	posteriorWheel->resizeDown(factor);

	double newBaseWidth = base->getWidth();
	double newBaseHeight = base->getHeight();

	point FrontRefPoint;
	point PostRefPoint;

	FrontRefPoint.x = oldRefPoint.x + (0.3 * newBaseWidth);
	PostRefPoint.x = oldRefPoint.x - (0.3 * newBaseWidth);

	FrontRefPoint.y = oldRefPoint.y + newBaseHeight / 2;
	PostRefPoint.y = oldRefPoint.y + newBaseHeight / 2;

	point newFrontRefPoint;
	point newPostRefPoint;

	if (*CarRotation == ROT_angle[0] || *CarRotation == ROT_angle[4]) {
		newFrontRefPoint.x = oldRefPoint.x + (0.3 * newBaseWidth);
		newPostRefPoint.x = oldRefPoint.x - (0.3 * newBaseWidth);

		newFrontRefPoint.y = oldRefPoint.y + newBaseHeight / 2;
		newPostRefPoint.y = oldRefPoint.y + newBaseHeight / 2;
	}
	else if (*CarRotation == ROT_angle[1]) {
		newFrontRefPoint.y = oldRefPoint.y + (0.3 * newBaseHeight);
		newPostRefPoint.y = oldRefPoint.y - (0.3 * newBaseHeight);

		newFrontRefPoint.x = oldRefPoint.x - newBaseWidth / 2;
		newPostRefPoint.x = oldRefPoint.x - newBaseWidth / 2;
	}
	else if (*CarRotation == ROT_angle[2]) {
		newFrontRefPoint.x = oldRefPoint.x + (0.3 * newBaseWidth);
		newPostRefPoint.x = oldRefPoint.x - (0.3 * newBaseWidth);

		newFrontRefPoint.y = oldRefPoint.y - newBaseHeight / 2;
		newPostRefPoint.y = oldRefPoint.y - newBaseHeight / 2;
	}
	else if (*CarRotation == ROT_angle[3]) {
		newFrontRefPoint.y = oldRefPoint.y - (0.3 * newBaseHeight);
		newPostRefPoint.y = oldRefPoint.y + (0.3 * newBaseHeight);

		newFrontRefPoint.x = oldRefPoint.x + newBaseWidth / 2;
		newPostRefPoint.x = oldRefPoint.x + newBaseWidth / 2;
	}
	frontalWheel->setRefPoint(newFrontRefPoint);
	posteriorWheel->setRefPoint(newPostRefPoint);
	size /= 2;

}

void Car::rotate() {
	point oldRefPoint = base->getRefPoint();

	base->rotate();
	frontalWheel->rotate();
	posteriorWheel->rotate();

	double newBaseWidth = base->getWidth();
	double newBaseHeight = base->getHeight();

	if (*CarRotation == ROT_angle[4]) {
		CarRotation = ROT_angle + 1;

	}
	else {
		CarRotation = CarRotation + 1;
	}

	point new_fWRef, new_PWRef;
	if (*CarRotation == ROT_angle[4] || *CarRotation == ROT_angle[2]) {

		new_fWRef.x = ((0 + (0.3 * newBaseWidth)) * cos(*CarRotation) - (0 + (newBaseHeight / 2) * sin(*CarRotation))) + oldRefPoint.x;
		new_fWRef.y = ((0 + (0.3 * newBaseWidth)) * sin(*CarRotation) + (0 + (newBaseHeight / 2) * cos(*CarRotation))) + oldRefPoint.y;

		new_PWRef.x = ((0 - (0.3 * newBaseWidth)) * cos(*CarRotation) - (0 + (newBaseHeight / 2) * sin(*CarRotation))) + oldRefPoint.x;
		new_PWRef.y = ((0 - (0.3 * newBaseWidth)) * sin(*CarRotation) + (0 + (newBaseHeight / 2) * cos(*CarRotation))) + oldRefPoint.y;



	}
	else {

		new_fWRef.x = ((0 + (0.3 * newBaseHeight)) * cos(*CarRotation) - (0 + (newBaseWidth / 2) * sin(*CarRotation))) + oldRefPoint.x;
		new_fWRef.y = ((0 + (0.3 * newBaseHeight)) * sin(*CarRotation) + (0 + (newBaseWidth / 2) * cos(*CarRotation))) + oldRefPoint.y;

		new_PWRef.x = ((0 - (0.3 * newBaseHeight)) * cos(*CarRotation) - (0 + (newBaseWidth / 2) * sin(*CarRotation))) + oldRefPoint.x;
		new_PWRef.y = ((0 - (0.3 * newBaseHeight)) * sin(*CarRotation) + (0 + (newBaseWidth / 2) * cos(*CarRotation))) + oldRefPoint.y;

	}

	if (*CarRotation == ROT_angle[0] || *CarRotation == ROT_angle[4]) {
		this->boundaryPointMin.x = base->getWidth() / 2;
		this->boundaryPointMin.y = config.toolBarHeight + base->getHeight() / 2 + 4 * config.gridSpacing;

		this->boundaryPointMax.x = config.windWidth - base->getWidth() / 2;
		this->boundaryPointMax.y = config.windHeight - (config.statusBarHeight + 2 * frontalWheel->getRadius() + base->getHeight() / 2);

	}
	else if (*CarRotation == ROT_angle[1]) {
		this->boundaryPointMin.x = frontalWheel->getRadius() + base->getHeight() / 2;
		this->boundaryPointMin.y = config.toolBarHeight + base->getWidth() / 2 + 4 * config.gridSpacing;

		this->boundaryPointMax.x = config.windWidth - base->getHeight() / 2;
		this->boundaryPointMax.y = config.windHeight - (config.statusBarHeight + base->getWidth() / 2);

	}
	else if (*CarRotation == ROT_angle[2]) {
		this->boundaryPointMin.x = base->getWidth() / 2;
		this->boundaryPointMin.y = config.toolBarHeight + frontalWheel->getRadius() + base->getHeight() / 2 + 4 * config.gridSpacing;

		this->boundaryPointMax.x = config.windWidth - base->getWidth() / 2;
		this->boundaryPointMax.y = config.windHeight - (config.statusBarHeight + base->getHeight() / 2);

	}
	else if (*CarRotation == ROT_angle[3]) {
		this->boundaryPointMin.x = base->getHeight() / 2;
		this->boundaryPointMin.y = config.toolBarHeight + base->getWidth() / 2 + 4 * config.gridSpacing;

		this->boundaryPointMax.x = config.windWidth - (frontalWheel->getRadius() + base->getHeight() / 2);
		this->boundaryPointMax.y = config.windHeight - (config.statusBarHeight + base->getWidth() / 2);
	}
	frontalWheel->setRefPoint(new_fWRef);
	posteriorWheel->setRefPoint(new_PWRef);

	angle = *CarRotation;

}

void Car::moveUp(double dist) {
	base->moveUp(dist);
	frontalWheel->moveUp(dist);
	posteriorWheel->moveUp(dist);
}

void Car::moveDown(double dist) {
	base->moveDown(dist);
	frontalWheel->moveDown(dist);
	posteriorWheel->moveDown(dist);
}

void Car::moveRight(double dist) {
	base->moveRight(dist);
	frontalWheel->moveRight(dist);
	posteriorWheel->moveRight(dist);
}

void Car::moveLeft(double dist) {
	base->moveLeft(dist);
	frontalWheel->moveLeft(dist);
	posteriorWheel->moveLeft(dist);
}


///////////////////////////////////////////
IceCream::IceCream(game* r_pGame, point ref, double cSize, double cAngle, color cFill, color cBorder) :shape(r_pGame, ref)
{
	angle = cAngle;
	size = cSize;
	name = "Icecream";
	double resizeFactor;
	point baseRef = ref;
	point circleRef = { ref.x, ref.y + config.icecream.baseWdth / 3 };

	base = new triangle(pGame, baseRef, config.icecream.baseWdth, cFill, cBorder);
	iceCircle = new circle(pGame, circleRef, config.icecream.baseWdth / 2.17, cFill, cBorder);

	this->boundaryPointMin.x = base->getRefPoint().x - abs(base->getbase()) / 3;
	this->boundaryPointMin.y = config.toolBarHeight + iceCircle->getRadius();
	this->boundaryPointMax.x = config.windWidth - iceCircle->getRadius();
	this->boundaryPointMax.y = config.windHeight - (config.statusBarHeight + base->getHeight());

	if (size < 1) {
		resizeFactor = 1 / size;
		this->resizeDown(resizeFactor);
	}
	else if (size > 1) {
		resizeFactor = size;
		this->resizeUp(resizeFactor);
	}
	if (angle == angleArr[1]) {
		this->rotate();
	}
	else if (angle == angleArr[2]) {
		this->rotate();
		this->rotate();
	}
	else if (angle == angleArr[3]) {
		this->rotate();
		this->rotate();
		this->rotate();
	}

}

void IceCream::setRefPoint(point p) {
	base->setRefPoint(p);
	point newIceRef;
	double newBaseWidth = base->getbase();
	double newWidth = base->getwidth();

	if (this->getAngle() == ROT_angle[0] || this->getAngle() == ROT_angle[4]) {
		newIceRef.x = p.x;
		newIceRef.y = p.y + newBaseWidth / 3;
	}
	else if (this->getAngle() == ROT_angle[1]) {
		newIceRef.x = p.x - newWidth / 3;
		newIceRef.y = p.y;
	}
	else if (this->getAngle() == ROT_angle[2]) {
		newIceRef.x = p.x;
		newIceRef.y = p.y - newBaseWidth / 3;
	}
	else if (this->getAngle() == ROT_angle[3]) {
		newIceRef.x = p.x + newWidth / 3;
		newIceRef.y = p.y;
	}

	iceCircle->setRefPoint(newIceRef);

}

point IceCream::getRefPoint()const {
	return RefPoint;
}

void IceCream::draw() const
{
	iceCircle->draw();
	base->draw();
}

void IceCream::resizeUp(double factor) {
	point oldRefPoint = base->getRefPoint();

	base->resizeUp(factor);
	iceCircle->resizeUp(factor);

	double newBaseWidth = base->getbase();
	double newIceWidth = newBaseWidth / 2;
	double newWidth = base->getwidth();

	point newIceRefPoint;

	if (*IceCreamRotation == ROT_angle[0] || *IceCreamRotation == ROT_angle[4]) {
		newIceRefPoint.x = oldRefPoint.x;
		newIceRefPoint.y = oldRefPoint.y + abs(newBaseWidth) / 3;
	}
	else if (*IceCreamRotation == ROT_angle[1]) {
		newIceRefPoint.y = oldRefPoint.y;
		newIceRefPoint.x = oldRefPoint.x - abs(newWidth) / 3;
	}
	else if (*IceCreamRotation == ROT_angle[2]) {
		newIceRefPoint.x = oldRefPoint.x;
		newIceRefPoint.y = oldRefPoint.y - abs(newBaseWidth) / 3;
	}
	else if (*IceCreamRotation == ROT_angle[3]) {
		newIceRefPoint.y = oldRefPoint.y;
		newIceRefPoint.x = oldRefPoint.x + abs(newWidth) / 3;
	}


	iceCircle->setRefPoint(newIceRefPoint);
	size*= 2;
	angle = *IceCreamRotation;

}
void IceCream::resizeDown(double factor) {
	point oldRefPoint = base->getRefPoint();

	base->resizeDown(factor);
	iceCircle->resizeDown(factor);

	double newBaseWidth = base->getbase();
	double newIceWidth = newBaseWidth / 2;
	double newWidth = base->getwidth();

	point newIceRefPoint;

	if (*IceCreamRotation == ROT_angle[0] || *IceCreamRotation == ROT_angle[4]) {
		newIceRefPoint.x = oldRefPoint.x;
		newIceRefPoint.y = oldRefPoint.y + abs(newBaseWidth) / 3;
	}
	else if (*IceCreamRotation == ROT_angle[1]) {
		newIceRefPoint.y = oldRefPoint.y;
		newIceRefPoint.x = oldRefPoint.x - abs(newWidth) / 3;
	}
	else if (*IceCreamRotation == ROT_angle[2]) {
		newIceRefPoint.x = oldRefPoint.x;
		newIceRefPoint.y = oldRefPoint.y - abs(newBaseWidth) / 3;
	}
	else if (*IceCreamRotation == ROT_angle[3]) {
		newIceRefPoint.y = oldRefPoint.y;
		newIceRefPoint.x = oldRefPoint.x + abs(newWidth) / 3;
	}


	iceCircle->setRefPoint(newIceRefPoint);
	size /= 2;

	angle = *IceCreamRotation;

}
void IceCream::rotate()
{
	point oldRefPoint = base->getRefPoint();
	int a, b;
	base->rotate();


	iceCircle->rotate();

	double newBase = base->getbase();
	double newwidth = base->getwidth();

	if (*IceCreamRotation == ROT_angle[4]) {
		IceCreamRotation = ROT_angle + 1;

	}
	else {
		IceCreamRotation = IceCreamRotation + 1;
	}

	point New_baseRef;
	if (*IceCreamRotation == ROT_angle[1] || *IceCreamRotation == ROT_angle[3]) {
		New_baseRef.x = (0 * cos(*IceCreamRotation) - ((0 + abs(newwidth) / 3) * sin(*IceCreamRotation))) + oldRefPoint.x;
		New_baseRef.y = (0 * sin(*IceCreamRotation) + ((0 + abs(newwidth) / 3) * cos(*IceCreamRotation))) + oldRefPoint.y;

	}

	else {
		New_baseRef.x = (0 * cos(*IceCreamRotation) - ((0 + abs(newBase) / 3) * sin(*IceCreamRotation))) + oldRefPoint.x;
		New_baseRef.y = (0 * sin(*IceCreamRotation) + ((0 + abs(newBase) / 3) * cos(*IceCreamRotation))) + oldRefPoint.y;
	}

	if (*IceCreamRotation == ROT_angle[0] || *IceCreamRotation == ROT_angle[4]) {
		this->boundaryPointMin.x = base->getbase() / 2;
		this->boundaryPointMin.y = config.toolBarHeight + base->getbase() * sqrt(3) / 6;

		this->boundaryPointMax.x = config.windWidth - base->getbase() / 2;
		this->boundaryPointMax.y = config.windHeight - (config.statusBarHeight + iceCircle->getRadius() + base->getbase() * sqrt(3) / 6);
	}
	else if (*IceCreamRotation == ROT_angle[1]) {
		this->boundaryPointMin.x = iceCircle->getRadius() + base->getbase() * sqrt(3) / 6;
		this->boundaryPointMin.y = config.toolBarHeight + base->getbase() / 2;

		this->boundaryPointMax.x = config.windWidth - base->getbase() * sqrt(3) / 6;
		this->boundaryPointMax.y = config.windHeight - (config.statusBarHeight + base->getbase() / 2);
	}
	else if (*IceCreamRotation == ROT_angle[2]) {
		this->boundaryPointMin.x = base->getbase() / 2;
		this->boundaryPointMin.y = config.toolBarHeight + iceCircle->getRadius() + base->getbase() * sqrt(3) / 6;

		this->boundaryPointMax.x = config.windWidth - base->getbase() / 2;
		this->boundaryPointMax.y = config.windHeight - (config.statusBarHeight + base->getbase() * sqrt(3) / 6);
	}
	else if (*IceCreamRotation == ROT_angle[3]) {
		this->boundaryPointMin.x = base->getbase() * sqrt(3) / 6;
		this->boundaryPointMin.y = config.toolBarHeight + base->getbase() / 2;

		this->boundaryPointMax.x = config.windWidth - (iceCircle->getRadius() + base->getbase() * sqrt(3) / 6);
		this->boundaryPointMax.y = config.windHeight - (config.statusBarHeight + base->getbase() / 2);
	}

	iceCircle->setRefPoint(New_baseRef);

}



void IceCream::moveUp(double dist) {
	base->moveUp(dist);
	iceCircle->moveUp(dist);
}

void IceCream::moveDown(double dist) {
	base->moveDown(dist);
	iceCircle->moveDown(dist);
}

void IceCream::moveRight(double dist) {
	base->moveRight(dist);
	iceCircle->moveRight(dist);
}

void IceCream::moveLeft(double dist) {
	base->moveLeft(dist);
	iceCircle->moveLeft(dist);
}


////////////////////////////////////////////

Rocket::Rocket(game* r_pGame, point ref, double cSize, double cAngle, color cFill, color cBorder) :shape(r_pGame, ref)
{
	angle = cAngle;
	size = cSize;
	name = "Rocket";
	double resizeFactor;
	point baseRef = ref;
	point headref = { ref.x, ref.y - config.rocket.baseHeight / 2 - (sqrt(3) / 6.0) * config.rocket.headwdth };
	point leftbaseRef = { ref.x - config.rocket.baseWdth / 2 , ref.y + config.rocket.baseHeight / 2 - config.rocket.smallbaseWdth / 3 };
	point rightbaseRef = { ref.x + config.rocket.baseWdth / 2 , ref.y + config.rocket.baseHeight / 2 - config.rocket.smallbaseWdth / 3 };

	base = new Rect(pGame, baseRef, config.rocket.baseHeight, config.rocket.baseWdth, cFill, cBorder);
	head = new triangle(pGame, headref, config.rocket.headwdth, cFill, cBorder);
	liftbase = new triangle(pGame, leftbaseRef, config.rocket.smallbaseWdth, cFill, cBorder);
	rightbase = new triangle(pGame, rightbaseRef, config.rocket.smallbaseWdth, cFill, cBorder);
	door = new circle(pGame, baseRef, config.rocket.door, cFill, cBorder);

	this->boundaryPointMin.x = liftbase->getbase() / 2 + base->getWidth() / 2;
	this->boundaryPointMin.y = config.toolBarHeight + head->getHeight() + base->getHeight() / 2;

	this->boundaryPointMax.x = config.windWidth - (rightbase->getbase() / 2 + base->getWidth() / 2);
	this->boundaryPointMax.y = config.windHeight - base->getHeight() / 2;

	if (size < 1) {
		resizeFactor = 1 / size;
		this->resizeDown(resizeFactor);
	}
	else if (size > 1) {
		resizeFactor = size;
		this->resizeUp(resizeFactor);
	}
	if (angle == angleArr[1]) {
		this->rotate();
	}
	else if (angle == angleArr[2]) {
		this->rotate();
		this->rotate();
	}
	else if (angle == angleArr[3]) {
		this->rotate();
		this->rotate();
		this->rotate();
	}

}

void Rocket::setRefPoint(point p) {
	base->setRefPoint(p);
	point newHead, newLeftBase, newRightBase, newDoor;

	double newRocketBaseHeight = base->getHeight();
	double newRocketBaseWidth = base->getWidth();
	double newRocketHeadWidth = head->getbase();
	double newSmallBaseWidth = rightbase->getbase();

	double newSmallWidth = rightbase->getwidth();
	double newRocketTriangleWidth = head->getwidth();

	if (this->getAngle() == ROT_angle[0] || this->getAngle() == ROT_angle[4]) {
		newHead.x = p.x;
		newHead.y = p.y - newRocketBaseHeight / 2 - (sqrt(3) / 6) * newRocketHeadWidth;
		newLeftBase.x = p.x - newRocketBaseWidth / 2;
		newLeftBase.y = p.y + newRocketBaseHeight / 2 - newSmallBaseWidth / 3;
		newRightBase.x = p.x + newRocketBaseWidth / 2;
		newRightBase.y = p.y + newRocketBaseHeight / 2 - newSmallBaseWidth / 3;
		newDoor = p;
	}
	else if (this->getAngle() == ROT_angle[1]) {
		newHead.x = p.x + +newRocketBaseWidth / 2 + (sqrt(3) / 6.0) * abs(newRocketTriangleWidth);
		newHead.y = p.y;
		newLeftBase.x = p.x - newRocketBaseWidth / 2 + abs(newSmallWidth) / 3;
		newLeftBase.y = p.y - newRocketBaseHeight / 2;
		newRightBase.x = p.x - newRocketBaseWidth / 2 + abs(newSmallWidth) / 3;
		newRightBase.y = p.y + newRocketBaseHeight / 2;
		newDoor = p;
	}
	else if (this->getAngle() == ROT_angle[2]) {
		newHead.x = p.x;
		newHead.y = p.y + newRocketBaseHeight / 2 + (sqrt(3) / 6) * abs(newRocketHeadWidth);
		newLeftBase.x = p.x + newRocketBaseWidth / 2;
		newLeftBase.y = p.y - newRocketBaseHeight / 2 - newSmallBaseWidth / 3;
		newRightBase.x = p.x - newRocketBaseWidth / 2;
		newRightBase.y = p.y - newRocketBaseHeight / 2 - newSmallBaseWidth / 3;
		newDoor = p;
	}
	else if (this->getAngle() == ROT_angle[3]) {
		newHead.x = p.x - newRocketBaseWidth / 2 - (sqrt(3) / 6.0) * abs(newRocketTriangleWidth);
		newHead.y = p.y;
		newLeftBase.x = p.x + newRocketBaseWidth / 2 - abs(newSmallWidth) / 3;
		newLeftBase.y = p.y + newRocketBaseHeight / 2;
		newRightBase.x = p.x + newRocketBaseWidth / 2 - abs(newSmallWidth) / 3;
		newRightBase.y = p.y - newRocketBaseHeight / 2;
		newDoor = p;

	}

	head->setRefPoint(newHead);
	liftbase->setRefPoint(newLeftBase);
	rightbase->setRefPoint(newRightBase);
	door->setRefPoint(newDoor);
}

point Rocket::getRefPoint()const {
	return base->getRefPoint();
}

void Rocket::draw() const
{
	liftbase->draw();
	rightbase->draw();
	base->draw();
	head->draw();
	door->draw();
}

void Rocket::resizeUp(double factor) {
	point oldRefPoint = base->getRefPoint();

	liftbase->resizeUp(factor);
	rightbase->resizeUp(factor);
	base->resizeUp(factor);
	head->resizeUp(factor);
	door->resizeUp(factor);

	double newRocketBaseHeight = base->getHeight();
	double newRocketBaseWidth = base->getWidth();
	double newRocketHeadWidth = head->getbase();
	double newSmallBaseWidth = rightbase->getbase();

	double newSmallWidth = rightbase->getwidth();
	double newRocketTriangleWidth = head->getwidth();

	point newLeftBaseRefPoint, newRightBaseRefPoint, newHeadRefPoint;

	if (*RocketRotation == ROT_angle[0] || *RocketRotation == ROT_angle[4]) {
		newHeadRefPoint.x = oldRefPoint.x;
		newHeadRefPoint.y = oldRefPoint.y - newRocketBaseHeight / 2 - (sqrt(3) / 6.0) * newRocketHeadWidth;

		newLeftBaseRefPoint.x = oldRefPoint.x - newRocketBaseWidth / 2;
		newLeftBaseRefPoint.y = oldRefPoint.y + newRocketBaseHeight / 2 - newSmallBaseWidth / 3;

		newRightBaseRefPoint.x = oldRefPoint.x + newRocketBaseWidth / 2;
		newRightBaseRefPoint.y = oldRefPoint.y + newRocketBaseHeight / 2 - newSmallBaseWidth / 3;
	}
	else if (*RocketRotation == ROT_angle[1]) {
		newHeadRefPoint.y = oldRefPoint.y;
		newHeadRefPoint.x = oldRefPoint.x + newRocketBaseWidth / 2 + (sqrt(3) / 6.0) * abs(newRocketTriangleWidth);

		newLeftBaseRefPoint.y = oldRefPoint.y - newRocketBaseHeight / 2;
		newLeftBaseRefPoint.x = oldRefPoint.x - newRocketBaseWidth / 2 + abs(newSmallWidth) / 3;

		newRightBaseRefPoint.y = oldRefPoint.y + newRocketBaseHeight / 2;
		newRightBaseRefPoint.x = oldRefPoint.x - newRocketBaseWidth / 2 + abs(newSmallWidth) / 3;
	}
	else if (*RocketRotation == ROT_angle[2]) {
		newHeadRefPoint.x = oldRefPoint.x;
		newHeadRefPoint.y = oldRefPoint.y + newRocketBaseHeight / 2 + (sqrt(3) / 6.0) * abs(newRocketHeadWidth);

		newLeftBaseRefPoint.x = oldRefPoint.x + newRocketBaseWidth / 2;
		newLeftBaseRefPoint.y = oldRefPoint.y - newRocketBaseHeight / 2 - newSmallBaseWidth / 3;

		newRightBaseRefPoint.x = oldRefPoint.x - newRocketBaseWidth / 2;
		newRightBaseRefPoint.y = oldRefPoint.y - newRocketBaseHeight / 2 - newSmallBaseWidth / 3;
	}
	else if (*RocketRotation == ROT_angle[3]) {
		newHeadRefPoint.y = oldRefPoint.y;
		newHeadRefPoint.x = oldRefPoint.x - newRocketBaseWidth / 2 - (sqrt(3) / 6.0) * abs(newRocketTriangleWidth);

		newLeftBaseRefPoint.y = oldRefPoint.y + newRocketBaseHeight / 2;
		newLeftBaseRefPoint.x = oldRefPoint.x + newRocketBaseWidth / 2 - abs(newSmallWidth) / 3;

		newRightBaseRefPoint.y = oldRefPoint.y - newRocketBaseHeight / 2;
		newRightBaseRefPoint.x = oldRefPoint.x + newRocketBaseWidth / 2 - abs(newSmallWidth) / 3;
	}



	head->setRefPoint(newHeadRefPoint);
	liftbase->setRefPoint(newLeftBaseRefPoint);
	rightbase->setRefPoint(newRightBaseRefPoint);
	size *= 2;

}
void Rocket::resizeDown(double factor) {
	point oldRefPoint = base->getRefPoint();

	liftbase->resizeDown(factor);
	rightbase->resizeDown(factor);
	base->resizeDown(factor);
	head->resizeDown(factor);
	door->resizeDown(factor);

	double newRocketBaseHeight = base->getHeight();
	double newRocketBaseWidth = base->getWidth();
	double newRocketHeadWidth = head->getbase();
	double newSmallBaseWidth = rightbase->getbase();

	double newSmallWidth = rightbase->getwidth();
	double newRocketTriangleWidth = head->getwidth();

	point newLeftBaseRefPoint, newRightBaseRefPoint, newHeadRefPoint;

	if (*RocketRotation == ROT_angle[0] || *RocketRotation == ROT_angle[4]) {
		newHeadRefPoint.x = oldRefPoint.x;
		newHeadRefPoint.y = oldRefPoint.y - newRocketBaseHeight / 2 - (sqrt(3) / 6.0) * newRocketHeadWidth;

		newLeftBaseRefPoint.x = oldRefPoint.x - newRocketBaseWidth / 2;
		newLeftBaseRefPoint.y = oldRefPoint.y + newRocketBaseHeight / 2 - newSmallBaseWidth / 3;

		newRightBaseRefPoint.x = oldRefPoint.x + newRocketBaseWidth / 2;
		newRightBaseRefPoint.y = oldRefPoint.y + newRocketBaseHeight / 2 - newSmallBaseWidth / 3;
	}
	else if (*RocketRotation == ROT_angle[1]) {
		newHeadRefPoint.y = oldRefPoint.y;
		newHeadRefPoint.x = oldRefPoint.x + newRocketBaseWidth / 2 + (sqrt(3) / 6.0) * abs(newRocketTriangleWidth);

		newLeftBaseRefPoint.y = oldRefPoint.y - newRocketBaseHeight / 2;
		newLeftBaseRefPoint.x = oldRefPoint.x - newRocketBaseWidth / 2 + abs(newSmallWidth) / 3;

		newRightBaseRefPoint.y = oldRefPoint.y + newRocketBaseHeight / 2;
		newRightBaseRefPoint.x = oldRefPoint.x - newRocketBaseWidth / 2 + abs(newSmallWidth) / 3;
	}
	else if (*RocketRotation == ROT_angle[2]) {
		newHeadRefPoint.x = oldRefPoint.x;
		newHeadRefPoint.y = oldRefPoint.y + newRocketBaseHeight / 2 + (sqrt(3) / 6.0) * abs(newRocketHeadWidth);

		newLeftBaseRefPoint.x = oldRefPoint.x + newRocketBaseWidth / 2;
		newLeftBaseRefPoint.y = oldRefPoint.y - newRocketBaseHeight / 2 - newSmallBaseWidth / 3;

		newRightBaseRefPoint.x = oldRefPoint.x - newRocketBaseWidth / 2;
		newRightBaseRefPoint.y = oldRefPoint.y - newRocketBaseHeight / 2 - newSmallBaseWidth / 3;
	}
	else if (*RocketRotation == ROT_angle[3]) {
		newHeadRefPoint.y = oldRefPoint.y;
		newHeadRefPoint.x = oldRefPoint.x - newRocketBaseWidth / 2 - (sqrt(3) / 6.0) * abs(newRocketTriangleWidth);

		newLeftBaseRefPoint.y = oldRefPoint.y + newRocketBaseHeight / 2;
		newLeftBaseRefPoint.x = oldRefPoint.x + newRocketBaseWidth / 2 - abs(newSmallWidth) / 3;

		newRightBaseRefPoint.y = oldRefPoint.y - newRocketBaseHeight / 2;
		newRightBaseRefPoint.x = oldRefPoint.x + newRocketBaseWidth / 2 - abs(newSmallWidth) / 3;
	}



	head->setRefPoint(newHeadRefPoint);
	liftbase->setRefPoint(newLeftBaseRefPoint);
	rightbase->setRefPoint(newRightBaseRefPoint);

	size /= 2;
}
void Rocket::rotate()
{
	point oldRefPoint = base->getRefPoint();

	rightbase->rotate();
	liftbase->rotate();
	head->rotate();
	base->rotate();
	door->rotate();

	double newRocketBaseHeight = base->getHeight();
	double newRocketBaseWidth = base->getWidth();
	double newRocketHead = head->getbase();
	double newSmallBase = rightbase->getbase();
	double newRocketHead_wdth = head->getwidth();
	double newSmallBase_wdth = rightbase->getwidth();



	if (*RocketRotation == ROT_angle[4]) {
		RocketRotation = ROT_angle + 1;

	}
	else {
		RocketRotation = RocketRotation + 1;
	}

	point New_headref;
	point New_leftbaseRef;
	point New_rightbaseRef;

	if (*RocketRotation == ROT_angle[1] || *RocketRotation == ROT_angle[3]) {

		New_headref.x = ((0) * cos(*RocketRotation) - ((0 - newRocketBaseWidth / 2 - (sqrt(3) / 6.0) * abs(newRocketHead_wdth)) * sin(*RocketRotation))) + oldRefPoint.x;
		New_headref.y = ((0) * sin(*RocketRotation) + ((0 - newRocketBaseWidth / 2 - (sqrt(3) / 6.0) * abs(newRocketHead_wdth)) * cos(*RocketRotation))) + oldRefPoint.y;

		New_leftbaseRef.x = ((0 - newRocketBaseHeight / 2) * cos(*RocketRotation) - ((0 + newRocketBaseWidth / 2 - abs(newSmallBase_wdth) / 3) * sin(*RocketRotation))) + oldRefPoint.x;
		New_leftbaseRef.y = ((0 - newRocketBaseHeight / 2) * sin(*RocketRotation) + ((0 + newRocketBaseWidth / 2 - abs(newSmallBase_wdth) / 3) * cos(*RocketRotation))) + oldRefPoint.y;


		New_rightbaseRef.x = ((0 + newRocketBaseHeight / 2) * cos(*RocketRotation) - ((0 + newRocketBaseWidth / 2 - abs(newSmallBase_wdth) / 3) * sin(*RocketRotation))) + oldRefPoint.x;
		New_rightbaseRef.y = ((0 + newRocketBaseHeight / 2) * sin(*RocketRotation) + ((0 + newRocketBaseWidth / 2 - abs(newSmallBase_wdth) / 3) * cos(*RocketRotation))) + oldRefPoint.y;

	}
	else {

		New_headref.x = ((0) * cos(*RocketRotation) - ((0 - newRocketBaseHeight / 2 - (sqrt(3) / 6.0) * abs(newRocketHead)) * sin(*RocketRotation))) + oldRefPoint.x;
		New_headref.y = ((0) * sin(*RocketRotation) + ((0 - newRocketBaseHeight / 2 - (sqrt(3) / 6.0) * abs(newRocketHead)) * cos(*RocketRotation))) + oldRefPoint.y;

		New_leftbaseRef.x = ((0 - newRocketBaseWidth / 2) * cos(*RocketRotation) - ((0 + newRocketBaseHeight / 2 - abs(newSmallBase) / 3) * sin(*RocketRotation))) + oldRefPoint.x;
		New_leftbaseRef.y = ((0 - newRocketBaseWidth / 2) * sin(*RocketRotation) + ((0 + newRocketBaseHeight / 2 - abs(newSmallBase) / 3) * cos(*RocketRotation))) + oldRefPoint.y;


		New_rightbaseRef.x = ((0 + newRocketBaseWidth / 2) * cos(*RocketRotation) - ((0 + newRocketBaseHeight / 2 - abs(newSmallBase) / 3) * sin(*RocketRotation))) + oldRefPoint.x;
		New_rightbaseRef.y = ((0 + newRocketBaseWidth / 2) * sin(*RocketRotation) + ((0 + newRocketBaseHeight / 2 - abs(newSmallBase) / 3) * cos(*RocketRotation))) + oldRefPoint.y;
	}

	if (*RocketRotation == ROT_angle[0] || *RocketRotation == ROT_angle[4]) {
		this->boundaryPointMin.x = liftbase->getbase() / 2 + base->getWidth() / 2;
		this->boundaryPointMin.y = config.toolBarHeight + head->getHeight() + base->getHeight() / 2 + 4 * config.gridSpacing;

		this->boundaryPointMax.x = config.windWidth - (rightbase->getbase() / 2 + base->getWidth() / 2);
		this->boundaryPointMax.y = config.windHeight - base->getHeight() / 2;

	}
	else if (*RocketRotation == ROT_angle[1]) {
		this->boundaryPointMin.x = base->getHeight() / 2;
		this->boundaryPointMin.y = config.toolBarHeight + liftbase->getwidth() / 2 + base->getWidth() / 2 + 4 * config.gridSpacing;

		this->boundaryPointMax.x = config.windWidth - (head->getHeight() + base->getHeight() / 2);
		this->boundaryPointMax.y = config.windHeight - (config.statusBarHeight + rightbase->getwidth() / 2 + base->getWidth() / 2);
	}
	else if (*RocketRotation == ROT_angle[2]) {
		this->boundaryPointMin.x = rightbase->getbase() / 2 + base->getWidth() / 2;
		this->boundaryPointMin.y = config.toolBarHeight + base->getHeight() / 2 + 4 * config.gridSpacing;

		this->boundaryPointMax.x = config.windWidth - (liftbase->getbase() / 2 + base->getWidth() / 2);
		this->boundaryPointMax.y = config.windHeight - (config.statusBarHeight + head->getHeight() + base->getHeight() / 2);
	}
	else if (*RocketRotation == ROT_angle[3]) {
		this->boundaryPointMin.x = head->getHeight() + base->getHeight() / 2;
		this->boundaryPointMin.y = config.toolBarHeight + rightbase->getwidth() / 2 + base->getWidth() / 2 + 4 * config.gridSpacing;

		this->boundaryPointMax.x = config.windWidth - base->getHeight() / 2;
		this->boundaryPointMax.y = config.windHeight - (config.statusBarHeight + liftbase->getwidth() / 2 + base->getWidth() / 2);
	}

	head->setRefPoint(New_headref);
	liftbase->setRefPoint(New_leftbaseRef);
	rightbase->setRefPoint(New_rightbaseRef);

	angle = *RocketRotation;

}

void Rocket::moveUp(double dist) {
	base->moveUp(dist);
	head->moveUp(dist);
	liftbase->moveUp(dist);
	rightbase->moveUp(dist);
	door->moveUp(dist);
}

void Rocket::moveDown(double dist) {
	base->moveDown(dist);
	head->moveDown(dist);
	liftbase->moveDown(dist);
	rightbase->moveDown(dist);
	door->moveDown(dist);

}

void Rocket::moveRight(double dist) {
	base->moveRight(dist);
	head->moveRight(dist);
	liftbase->moveRight(dist);
	rightbase->moveRight(dist);
	door->moveRight(dist);
}

void Rocket::moveLeft(double dist) {
	base->moveLeft(dist);
	head->moveLeft(dist);
	liftbase->moveLeft(dist);
	rightbase->moveLeft(dist);
	door->moveLeft(dist);
}


///////////////////////////////////////////////////

House::House(game* r_pGame, point ref, double cSize, double cAngle, color cFill, color cBorder) :shape(r_pGame, ref)
{
	angle = cAngle;
	size = cSize;
	name = "House";
	double resizeFactor;
	point baseRef = ref;
	point headRef = { ref.x, ref.y - config.house.baseHeight / 2 - (sqrt(3) / 6.0) * config.house.baseWdth };
	point doorRef = { ref.x, ref.y + config.house.baseHeight / 2 - config.house.doorhight / 2 };

	base = new Rect(pGame, baseRef, config.house.baseHeight, config.house.baseWdth, cFill, cBorder);
	door = new Rect(pGame, doorRef, config.house.doorhight, config.house.doorwdth, cFill, cBorder);
	head = new triangle(pGame, headRef, config.house.headwdth, cFill, cBorder);

	this->boundaryPointMin.x = base->getWidth() / 2;
	this->boundaryPointMin.y = config.toolBarHeight + head->getHeight() + base->getHeight() / 2;

	this->boundaryPointMax.x = config.windWidth - base->getWidth() / 2;
	this->boundaryPointMax.y = config.windHeight - (config.statusBarHeight + head->getHeight() / 2);

	if (size < 1) {
		resizeFactor = 1 / size;
		this->resizeDown(resizeFactor);
	}
	else if (size > 1) {
		resizeFactor = size;
		this->resizeUp(resizeFactor);
	}
	if (angle == angleArr[1]) {
		this->rotate();
	}
	else if (angle == angleArr[2]) {
		this->rotate();
		this->rotate();
	}
	else if (angle == angleArr[3]) {
		this->rotate();
		this->rotate();
		this->rotate();
	}
}

void House::setRefPoint(point p) {
	base->setRefPoint(p);
	double newHouseBaseHeight = base->getHeight();
	double newHouseBaseWidth = base->getWidth();
	double newDoorHeight = door->getHeight();

	double newHeadWidth = head->getwidth();
	double newDoorWidth = door->getWidth();
	double newHeadBase = head->getbase();

	point newDoorRefPoint;
	point newHeadRefPoint;


	if (this->getAngle() == ROT_angle[0] || this->getAngle() == ROT_angle[4]) {
		newDoorRefPoint.x = p.x;
		newHeadRefPoint.x = p.x;

		newHeadRefPoint.y = p.y - newHouseBaseHeight / 2 - (sqrt(3) / 6.0) * newHouseBaseWidth;
		newDoorRefPoint.y = p.y + newHouseBaseHeight / 2 - newDoorHeight / 2;
	}
	else if (this->getAngle() == ROT_angle[1]) {
		newDoorRefPoint.y = p.y;
		newHeadRefPoint.y = p.y;

		newHeadRefPoint.x = p.x + newHouseBaseHeight / 2 + (sqrt(3) / 6.0) * newHouseBaseWidth;
		newDoorRefPoint.x = p.x - newHouseBaseHeight / 2 + newDoorWidth / 2;
	}
	else if (this->getAngle() == ROT_angle[2]) {
		newDoorRefPoint.x = p.x;
		newHeadRefPoint.x = p.x;

		newHeadRefPoint.y = p.y + newHouseBaseHeight / 2 + (sqrt(3) / 6.0) * newHouseBaseWidth;
		newDoorRefPoint.y = p.y - newHouseBaseHeight / 2 + newDoorHeight / 2;
	}
	else if (this->getAngle() == ROT_angle[3]) {
		newDoorRefPoint.y = p.y;
		newHeadRefPoint.y = p.y;

		newHeadRefPoint.x = p.x - newHouseBaseHeight / 2 - (sqrt(3) / 6.0) * newHouseBaseWidth;
		newDoorRefPoint.x = p.x + newHouseBaseHeight / 2 - newDoorWidth / 2;
	}

	door->setRefPoint(newDoorRefPoint);
	head->setRefPoint(newHeadRefPoint);
}

point House::getRefPoint()const {
	return base->getRefPoint();
}

void House::draw() const
{
	base->draw();
	door->draw();
	head->draw();
}


void House::resizeUp(double factor) {
	point oldRefPoint = base->getRefPoint();

	base->resizeUp(factor);
	door->resizeUp(factor);
	head->resizeUp(factor);

	double newHouseBaseHeight = base->getHeight();
	double newHouseBaseWidth = base->getWidth();
	double newDoorHeight = door->getHeight();

	double newHeadWidth = head->getwidth();
	double newDoorWidth = door->getWidth();
	double newHeadBase = head->getbase();

	point newDoorRefPoint;
	point newHeadRefPoint;

	if (*HouseRotation == ROT_angle[0] || *HouseRotation == ROT_angle[4]) {
		newDoorRefPoint.x = oldRefPoint.x;
		newHeadRefPoint.x = oldRefPoint.x;

		newHeadRefPoint.y = oldRefPoint.y - newHouseBaseHeight / 2 - (sqrt(3) / 6.0) * newHouseBaseWidth;
		newDoorRefPoint.y = oldRefPoint.y + newHouseBaseHeight / 2 - newDoorHeight / 2;
	}
	else if (*HouseRotation == ROT_angle[1]) {
		newDoorRefPoint.y = oldRefPoint.y;
		newHeadRefPoint.y = oldRefPoint.y;

		newHeadRefPoint.x = oldRefPoint.x + newHouseBaseHeight / 2 + (sqrt(3) / 6.0) * newHouseBaseWidth;
		newDoorRefPoint.x = oldRefPoint.x - newHouseBaseHeight / 2 + newDoorWidth / 2;
	}
	else if (*HouseRotation == ROT_angle[2]) {
		newDoorRefPoint.x = oldRefPoint.x;
		newHeadRefPoint.x = oldRefPoint.x;

		newHeadRefPoint.y = oldRefPoint.y + newHouseBaseHeight / 2 + (sqrt(3) / 6.0) * newHouseBaseWidth;
		newDoorRefPoint.y = oldRefPoint.y - newHouseBaseHeight / 2 + newDoorHeight / 2;
	}
	else if (*HouseRotation == ROT_angle[3]) {
		newDoorRefPoint.y = oldRefPoint.y;
		newHeadRefPoint.y = oldRefPoint.y;

		newHeadRefPoint.x = oldRefPoint.x - newHouseBaseHeight / 2 - (sqrt(3) / 6.0) * newHouseBaseWidth;
		newDoorRefPoint.x = oldRefPoint.x + newHouseBaseHeight / 2 - newDoorWidth / 2;
	}



	door->setRefPoint(newDoorRefPoint);
	head->setRefPoint(newHeadRefPoint);

	size *= 2;

}
void House::resizeDown(double factor) {
	point oldRefPoint = base->getRefPoint();

	base->resizeDown(factor);
	door->resizeDown(factor);
	head->resizeDown(factor);

	double newHouseBaseHeight = base->getHeight();
	double newHouseBaseWidth = base->getWidth();
	double newDoorHeight = door->getHeight();

	double newHeadWidth = head->getwidth();
	double newDoorWidth = door->getWidth();
	double newHeadBase = head->getbase();

	point newDoorRefPoint;
	point newHeadRefPoint;

	if (*HouseRotation == ROT_angle[0] || *HouseRotation == ROT_angle[4]) {
		newDoorRefPoint.x = oldRefPoint.x;
		newHeadRefPoint.x = oldRefPoint.x;

		newHeadRefPoint.y = oldRefPoint.y - newHouseBaseHeight / 2 - (sqrt(3) / 6.0) * newHouseBaseWidth;
		newDoorRefPoint.y = oldRefPoint.y + newHouseBaseHeight / 2 - newDoorHeight / 2;
	}
	else if (*HouseRotation == ROT_angle[1]) {
		newDoorRefPoint.y = oldRefPoint.y;
		newHeadRefPoint.y = oldRefPoint.y;

		newHeadRefPoint.x = oldRefPoint.x + newHouseBaseHeight / 2 + (sqrt(3) / 6.0) * newHouseBaseWidth;
		newDoorRefPoint.x = oldRefPoint.x - newHouseBaseHeight / 2 + newDoorWidth / 2;
	}
	else if (*HouseRotation == ROT_angle[2]) {
		newDoorRefPoint.x = oldRefPoint.x;
		newHeadRefPoint.x = oldRefPoint.x;

		newHeadRefPoint.y = oldRefPoint.y + newHouseBaseHeight / 2 + (sqrt(3) / 6.0) * newHouseBaseWidth;
		newDoorRefPoint.y = oldRefPoint.y - newHouseBaseHeight / 2 + newDoorHeight / 2;
	}
	else if (*HouseRotation == ROT_angle[3]) {
		newDoorRefPoint.y = oldRefPoint.y;
		newHeadRefPoint.y = oldRefPoint.y;

		newHeadRefPoint.x = oldRefPoint.x - newHouseBaseHeight / 2 - (sqrt(3) / 6.0) * newHouseBaseWidth;
		newDoorRefPoint.x = oldRefPoint.x + newHouseBaseHeight / 2 - newDoorWidth / 2;
	}



	door->setRefPoint(newDoorRefPoint);
	head->setRefPoint(newHeadRefPoint);

	size /= 2;
}


void House::rotate()
{
	point oldRefPoint = base->getRefPoint();

	head->rotate();
	base->rotate();
	door->rotate();

	double newHouseBaseHeight = base->getHeight();
	double newHouseBaseWidth = base->getWidth();
	double newDoorHeight = door->getHeight();
	double newDoorwidth = door->getWidth();

	if (*HouseRotation == ROT_angle[4]) {
		HouseRotation = ROT_angle + 1;

	}
	else {
		HouseRotation = HouseRotation + 1;
	}

	point New_headRef;
	point New_doorRef;
	if (*HouseRotation == ROT_angle[1] || *HouseRotation == ROT_angle[3])
	{
		New_headRef.x = ((0) * cos(*HouseRotation) - ((0 - newHouseBaseWidth / 2 - (sqrt(3) / 6.0) * newHouseBaseHeight) * sin(*HouseRotation))) + oldRefPoint.x;
		New_headRef.y = ((0) * sin(*HouseRotation) + ((0 - newHouseBaseWidth / 2 - (sqrt(3) / 6.0) * newHouseBaseHeight) * cos(*HouseRotation))) + oldRefPoint.y;

		New_doorRef.x = ((0) * cos(*HouseRotation) - ((0 + newHouseBaseWidth / 2 - newDoorwidth / 2) * sin(*HouseRotation))) + oldRefPoint.x;
		New_doorRef.y = ((0) * sin(*HouseRotation) + ((0 + newHouseBaseWidth / 2 - newDoorwidth / 2) * cos(*HouseRotation))) + oldRefPoint.y;

	}
	else {
		New_headRef.x = ((0) * cos(*HouseRotation) - ((0 - newHouseBaseHeight / 2 - (sqrt(3) / 6.0) * newHouseBaseWidth) * sin(*HouseRotation))) + oldRefPoint.x;
		New_headRef.y = ((0) * sin(*HouseRotation) + ((0 - newHouseBaseHeight / 2 - (sqrt(3) / 6.0) * newHouseBaseWidth) * cos(*HouseRotation))) + oldRefPoint.y;

		New_doorRef.x = ((0) * cos(*HouseRotation) - ((0 + newHouseBaseHeight / 2 - newDoorHeight / 2) * sin(*HouseRotation))) + oldRefPoint.x;
		New_doorRef.y = ((0) * sin(*HouseRotation) + ((0 + newHouseBaseHeight / 2 - newDoorHeight / 2) * cos(*HouseRotation))) + oldRefPoint.y;
	}

	if (*HouseRotation == ROT_angle[0] || *HouseRotation == ROT_angle[4]) {
		this->boundaryPointMin.x = base->getWidth() / 2;
		this->boundaryPointMin.y = config.toolBarHeight + head->getHeight() + base->getHeight() / 2 + 12 * config.gridSpacing;

		this->boundaryPointMax.x = config.windWidth - base->getWidth() / 2;
		this->boundaryPointMax.y = config.windHeight - (config.statusBarHeight + base->getHeight() / 2);

	}
	else if (*HouseRotation == ROT_angle[1]) {
		this->boundaryPointMin.x = base->getHeight() / 2;
		this->boundaryPointMin.y = config.toolBarHeight + base->getWidth() / 2 + 4 * config.gridSpacing;

		this->boundaryPointMax.x = config.windWidth - (head->getHeight() + base->getHeight() / 2);
		this->boundaryPointMax.y = config.windHeight - (config.statusBarHeight + base->getWidth());
	}
	else if (*HouseRotation == ROT_angle[2]) {
		this->boundaryPointMin.x = base->getWidth() / 2;
		this->boundaryPointMin.y = config.toolBarHeight + base->getHeight() / 2 + 4 * config.gridSpacing;

		this->boundaryPointMax.x = config.windWidth - base->getWidth() / 2;
		this->boundaryPointMax.y = config.windHeight - (config.statusBarHeight + head->getHeight() + base->getHeight() / 2);

	}
	else if (*HouseRotation == ROT_angle[3]) {
		this->boundaryPointMin.x = head->getHeight() + base->getHeight() / 2;
		this->boundaryPointMin.y = config.toolBarHeight + base->getWidth() / 2 + 4 * config.gridSpacing;

		this->boundaryPointMax.x = config.windWidth - base->getHeight() / 2;
		this->boundaryPointMax.y = config.windHeight - (config.statusBarHeight + base->getWidth());
	}

	head->setRefPoint(New_headRef);
	door->setRefPoint(New_doorRef);

	angle = *HouseRotation;

}
void House::moveUp(double dist) {
	base->moveUp(dist);
	door->moveUp(dist);
	head->moveUp(dist);
}

void House::moveDown(double dist) {
	base->moveDown(dist);
	door->moveDown(dist);
	head->moveDown(dist);
}

void House::moveRight(double dist) {
	base->moveRight(dist);
	door->moveRight(dist);
	head->moveRight(dist);
}

void House::moveLeft(double dist) {
	base->moveLeft(dist);
	door->moveLeft(dist);
	head->moveLeft(dist);
}

bool Sign::Match(shape* sh)
{
	Sign* sign = dynamic_cast<Sign*> (sh);
	if (sign) {
		return base->Match(sign->base) && top->Match(sign->top);
	}
	return false;
}
bool Tree::Match(shape* sh)
{
	Tree* tree = dynamic_cast<Tree*> (sh);
	if (tree) {
		return base->Match(tree->base) && Layer_1->Match(tree->Layer_1) && Layer_2->Match(tree->Layer_2) && layer_3->Match(tree->layer_3) && apple->Match(tree->apple);
	}
	return false;
}
bool Car::Match(shape* sh)
{
	Car* car = dynamic_cast<Car*> (sh);
	if (car) {
		return base->Match(car->base) && frontalWheel->Match(car->frontalWheel) && posteriorWheel->Match(car->posteriorWheel);
	}
	return false;
}

bool IceCream::Match(shape* sh)
{
	IceCream* ice = dynamic_cast<IceCream*> (sh);
	if (ice) {
		return base->Match(ice->base) && iceCircle->Match(ice->iceCircle);
	}
	return false;
}

bool Rocket::Match(shape* sh)
{
	Rocket* rock = dynamic_cast<Rocket*> (sh);
	if (rock) {
		return base->Match(rock->base) && head->Match(rock->head) && liftbase->Match(rock->liftbase) && rightbase->Match(rock->rightbase) && door->Match(rock->door);
	}
	return false;
}

bool House::Match(shape* sh)
{
	House* house = dynamic_cast<House*> (sh);
	if (house) {
		return door->Match(house->door) && base->Match(house->base) && head->Match(house->head);
	}
	return false;
}