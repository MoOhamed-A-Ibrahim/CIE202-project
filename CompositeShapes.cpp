#include "CompositeShapes.h"
#include "gameConfig.h"

////////////////////////////////////////////////////  class Sign  ///////////////////////////////////////
Sign::Sign(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	//calc the ref point of the Sign base and top rectangles relative to the Sign shape
	point topRef = ref;	//top rect ref is the same as the sign
	point baseRef = { ref.x, ref.y + config.signShape.topHeight / 2 + config.signShape.baseHeight / 2 };


	top = new Rect(pGame, topRef, config.signShape.topHeight, config.signShape.topWdth);
	base = new Rect(pGame, baseRef, config.signShape.baseHeight, config.signShape.baseWdth);


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

	base->setRefPoint(baseRef);
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

}



////////////////////////////////////////////////////////////////

Tree::Tree(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	point baseRef = ref;
	point layer_1_ref = { ref.x, ref.y - config.tree.baseHeight / 2 -  config.tree.baseWdth };
	point layer_2_ref = { ref.x, ref.y - config.tree.baseHeight / 2 - 2 *  config.tree.baseWdth };
	point layer_3_ref = { ref.x, ref.y - config.tree.baseHeight / 2 - 3 * config.tree.baseWdth };
	point apple_ref = layer_3_ref;

	base = new Rect(pGame, baseRef, config.tree.baseHeight, config.tree.baseWdth);
	Layer_1 = new triangle(pGame, layer_1_ref, config.tree.triwdth);
	Layer_2 = new triangle(pGame, layer_2_ref, config.tree.triwdth);
	layer_3 = new triangle(pGame, layer_3_ref, config.tree.triwdth);
	apple = new circle(pGame, apple_ref, config.tree.apple);
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
		newRefLay1.x = oldRefPoint.x + newBaseWidth /2 + newBaseHeight;
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
	Layer_2->setRefPoint(middleRef);
	Layer_1->setRefPoint(bottomRef);
	layer_3->setRefPoint(topRef);
	apple->setRefPoint(topRef);
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
Car::Car(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	point baseRef = ref;
	point fWRef = { ref.x + (0.3 * config.car.baseWdth), ref.y + config.car.baseHeight / 2 };
	point PWRef = { ref.x - (0.3 * config.car.baseWdth), ref.y + config.car.baseHeight / 2 };

	base = new Rect(pGame, baseRef, config.car.baseHeight, config.car.baseWdth);
	frontalWheel = new circle(pGame, fWRef, config.car.wheelRadius);
	posteriorWheel = new circle(pGame, PWRef, config.car.wheelRadius);
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
	frontalWheel->setRefPoint(new_fWRef);
	posteriorWheel->setRefPoint(new_PWRef);


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
IceCream::IceCream(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	point baseRef = ref;
	point circleRef = { ref.x, ref.y + config.icecream.baseWdth / 3 };

	base = new triangle(pGame, baseRef, config.icecream.baseWdth);
	iceCircle = new circle(pGame, circleRef, config.icecream.baseWdth / 2.17);
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
		newIceRefPoint.y = oldRefPoint.y + abs(newBaseWidth)/ 3;
	}
	else if (*IceCreamRotation == ROT_angle[1]) {
		newIceRefPoint.y = oldRefPoint.y;
		newIceRefPoint.x = oldRefPoint.x - abs(newWidth)/ 3;
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

Rocket::Rocket(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	point baseRef = ref;
	point headref = { ref.x, ref.y - config.rocket.baseHeight / 2 - (sqrt(3) / 6.0) * config.rocket.headwdth };
	point leftbaseRef = { ref.x - config.rocket.baseWdth / 2 , ref.y + config.rocket.baseHeight / 2 - config.rocket.smallbaseWdth / 3 };
	point rightbaseRef = { ref.x + config.rocket.baseWdth / 2 , ref.y + config.rocket.baseHeight / 2 - config.rocket.smallbaseWdth / 3 };

	base = new Rect(pGame, baseRef, config.rocket.baseHeight, config.rocket.baseWdth);
	head = new triangle(pGame, headref, config.rocket.headwdth);
	liftbase = new triangle(pGame, leftbaseRef, config.rocket.smallbaseWdth);
	rightbase = new triangle(pGame, rightbaseRef, config.rocket.smallbaseWdth);
	door = new circle(pGame, baseRef, config.rocket.door);
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

	head->setRefPoint(New_headref);
	liftbase->setRefPoint(New_leftbaseRef);
	rightbase->setRefPoint(New_rightbaseRef);
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

House::House(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	point baseRef = ref;
	point headRef = { ref.x, ref.y - config.house.baseHeight / 2 - (sqrt(3) / 6.0) * config.house.baseWdth };
	point doorRef = { ref.x, ref.y + config.house.baseHeight / 2 - config.house.doorhight / 2 };

	base = new Rect(pGame, baseRef, config.house.baseHeight, config.house.baseWdth);
	door = new Rect(pGame, doorRef, config.house.doorhight, config.house.doorwdth);
	head = new triangle(pGame, headRef, config.house.headwdth);
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
	head->setRefPoint(New_headRef);
	door->setRefPoint(New_doorRef);

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