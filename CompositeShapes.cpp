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
void Sign::rotate(double deg)
{

	point baseRef;
	angle += 90;

	if (angle >= 90 && angle < 180) {
		baseRef = { (int)(RefPoint.x - config.signShape.baseWdth / 2.0 - config.signShape.topWdth / 2.0) ,(int)RefPoint.y };
	}
	else if (angle >= 180 && angle < 270) {
		baseRef = { (int)RefPoint.x,(int)(RefPoint.y - config.signShape.topWdth + config.signShape.baseHeight / 2.0) };
	}
	else if (angle >= 270 && angle < 360) {
		baseRef = { (int)(RefPoint.x + config.signShape.baseWdth / 2.0 + config.signShape.topWdth / 2.0),(int)RefPoint.y };


	}

	else if (angle >= 360 && angle < 450) {

		baseRef = { (int)RefPoint.x,(int)(RefPoint.y + config.signShape.topHeight / 2 + config.signShape.baseHeight / 2) };
		angle = 0;
	}


	base->setRefPoint(baseRef);


	top->rotate(deg);
	base->rotate(deg);


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

	point newRefBase;
	newRefBase.x = oldRefPoint.x;
	newRefBase.y = oldRefPoint.y + newTopHeight / 2 + newBaseHeight / 2;
	base->setRefPoint(newRefBase);

}

void Sign::resizeDown(double factor) {
	point oldRefPoint = top->getRefPoint();

	top->resizeDown(factor);
	base->resizeDown(factor);

	double newTopHeight = top->getHeight();
	double newBaseHeight = base->getHeight();

	point newRefBase;
	newRefBase.x = oldRefPoint.x;
	newRefBase.y = oldRefPoint.y + newTopHeight / 2 + newBaseHeight / 2;
	base->setRefPoint(newRefBase);

}



////////////////////////////////////////////////////////////////

Tree::Tree(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	point baseRef = ref;
	point layer_1_ref = { ref.x, ref.y - config.tree.baseHeight / 2 - config.tree.baseWdth };
	point layer_2_ref = { ref.x, ref.y - config.tree.baseHeight / 2 - 2 * config.tree.baseWdth };
	point layer_3_ref = { ref.x, ref.y - config.tree.baseHeight / 2 - 3 * config.tree.baseWdth };
	point apple_ref = { ref.x, ref.y - config.tree.baseHeight / 2 - 3 * config.tree.baseWdth };

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

	double newBaseHeight = base->getHeight();
	double newBaseWidth = base->getWidth();

	point newRefLay1;
	point newRefLay2;
	point newRefLay3;

	newRefLay1.x = oldRefPoint.x;
	newRefLay2.x = oldRefPoint.x;
	newRefLay3.x = oldRefPoint.x;

	newRefLay1.y = oldRefPoint.y - newBaseHeight / 2 - newBaseWidth;
	newRefLay2.y = oldRefPoint.y - newBaseHeight / 2 - 2 * newBaseWidth;
	newRefLay3.y = oldRefPoint.y - newBaseHeight / 2 - 3 * newBaseWidth;

	Layer_1->setRefPoint(newRefLay1);
	Layer_2->setRefPoint(newRefLay2);
	layer_3->setRefPoint(newRefLay3);

}
void Tree::resizeDown(double factor) {
	point oldRefPoint = base->getRefPoint();

	base->resizeDown(factor);
	Layer_1->resizeDown(factor);
	Layer_2->resizeDown(factor);
	layer_3->resizeDown(factor);

	double newBaseHeight = base->getHeight();
	double newBaseWidth = base->getWidth();

	point newRefLay1;
	point newRefLay2;
	point newRefLay3;

	newRefLay1.x = oldRefPoint.x;
	newRefLay2.x = oldRefPoint.x;
	newRefLay3.x = oldRefPoint.x;

	newRefLay1.y = oldRefPoint.y - newBaseHeight / 2 - newBaseWidth;
	newRefLay2.y = oldRefPoint.y - newBaseHeight / 2 - 2 * newBaseWidth;
	newRefLay3.y = oldRefPoint.y - newBaseHeight / 2 - 3 * newBaseWidth;

	Layer_1->setRefPoint(newRefLay1);
	Layer_2->setRefPoint(newRefLay2);
	layer_3->setRefPoint(newRefLay3);

}
void Tree::rotate(double deg)
{


	point bottomRef;
	point middleRef;
	point topRef;
	angle += 90;

	if (angle >= 90 && angle < 180) {


		bottomRef = { (int)(RefPoint.x + config.tree.baseHeight / 2.0 + config.tree.baseWdth)  ,(int)RefPoint.y };
		middleRef = { (int)(RefPoint.x + config.tree.baseHeight / 2.0 + 2.0 * config.tree.baseWdth),(int)RefPoint.y };
		topRef = { (int)(RefPoint.x + config.tree.baseHeight / 2.0 + 3.0 * config.tree.baseWdth)  , (int)RefPoint.y };

	}
	else if (angle >= 180 && angle < 270) {

		bottomRef = { (int)RefPoint.x,(int)(RefPoint.y + config.tree.baseHeight / 2.0 + config.tree.baseWdth) };
		middleRef = { (int)RefPoint.x, (int)(RefPoint.y + config.tree.baseHeight / 2.0 + 2.0 * config.tree.baseWdth) };
		topRef = { (int)RefPoint.x,(int)(RefPoint.y + config.tree.baseHeight / 2.0 + 3.0 * config.tree.baseWdth) };;

	}
	else if (angle >= 270 && angle < 360) {


		bottomRef = { (int)(RefPoint.x - config.tree.baseHeight / 2.0 - config.tree.baseWdth)  ,(int)RefPoint.y };
		middleRef = { (int)(RefPoint.x - config.tree.baseHeight / 2.0 - 2.0 * config.tree.baseWdth)   ,(int)RefPoint.y };
		topRef = { (int)(RefPoint.x - config.tree.baseHeight / 2.0 - 3.0 * config.tree.baseWdth)  , (int)RefPoint.y };
	}

	else {

		bottomRef = { (int)RefPoint.x,(int)(RefPoint.y - config.tree.baseHeight / 2.0 - config.tree.baseWdth) };
		middleRef = { (int)RefPoint.x,(int)(RefPoint.y - config.tree.baseHeight / 2.0 - 2.0 * config.tree.baseWdth) };
		topRef = { (int)RefPoint.x, (int)(RefPoint.y - config.tree.baseHeight / 2.0 - 3.0 * config.tree.baseWdth) };
		angle = 0;
	}




	Layer_2->setRefPoint(middleRef);
	Layer_1->setRefPoint(bottomRef);
	layer_3->setRefPoint(topRef);

	Layer_1->rotate(deg);
	Layer_2->rotate(deg);
	layer_3->rotate(deg);
	base->rotate(deg);
}


void Tree::moveUp(double dist) {
	base->moveUp(dist);
	Layer_1->moveUp(dist);
	Layer_2->moveUp(dist);
	layer_3->moveUp(dist);
}

void Tree::moveDown(double dist) {
	base->moveDown(dist);
	Layer_1->moveDown(dist);
	Layer_2->moveDown(dist);
	layer_3->moveDown(dist);
}

void Tree::moveRight(double dist) {
	base->moveRight(dist);
	Layer_1->moveRight(dist);
	Layer_2->moveRight(dist);
	layer_3->moveRight(dist);
}

void Tree::moveLeft(double dist) {
	base->moveLeft(dist);
	Layer_1->moveLeft(dist);
	Layer_2->moveLeft(dist);
	layer_3->moveLeft(dist);
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

	newFrontRefPoint.x = oldRefPoint.x + (0.3 * newBaseWidth);
	newPostRefPoint.x = oldRefPoint.x - (0.3 * newBaseWidth);

	newFrontRefPoint.y = oldRefPoint.y + newBaseHeight / 2;
	newPostRefPoint.y = oldRefPoint.y + newBaseHeight / 2;

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

	point newFrontRefPoint;
	point newPostRefPoint;

	newFrontRefPoint.x = oldRefPoint.x + (0.3 * newBaseWidth);
	newPostRefPoint.x = oldRefPoint.x - (0.3 * newBaseWidth);

	newFrontRefPoint.y = oldRefPoint.y + newBaseHeight / 2;
	newPostRefPoint.y = oldRefPoint.y + newBaseHeight / 2;

	frontalWheel->setRefPoint(newFrontRefPoint);
	posteriorWheel->setRefPoint(newPostRefPoint);

}

void Car::rotate(double deg)
{

	point C1Ref;
	point C2Ref;

	angle += 90;

	if (angle >= 90 && angle < 180) {

		C1Ref = { (int)(RefPoint.x - config.car.baseHeight / 2.0) ,(int)(RefPoint.y - 3.0 * config.car.baseWdth / 10.0) };
		C2Ref = { (int)(RefPoint.x - config.car.baseHeight / 2.0),(int)(RefPoint.y + 3.0 * config.car.baseWdth / 10.0) };
	}
	else if (angle >= 180 && angle < 270) {
		C1Ref = { (int)(RefPoint.x - 3.0 * config.car.baseWdth / 10.0), (int)(RefPoint.y - config.car.baseHeight / 2.0) };
		C2Ref = { (int)(RefPoint.x + 3.0 * config.car.baseWdth / 10.0),  (int)(RefPoint.y - config.car.baseHeight / 2.0) };

	}
	else if (angle >= 270 && angle < 360) {

		C1Ref = { (int)(RefPoint.x + config.car.baseHeight / 2.0),  (int)(RefPoint.y - 3.0 * config.car.baseWdth / 10.0) };
		C2Ref = { (int)(RefPoint.x + config.car.baseHeight / 2.0), (int)(RefPoint.y + 3.0 * config.car.baseWdth / 10.0) };

	}

	else {

		C1Ref = { (int)(RefPoint.x - 3.0 * config.car.baseWdth / 10.0), (int)(RefPoint.y + config.car.baseHeight / 2.0) };
		C2Ref = { (int)(RefPoint.x + 3.0 * config.car.baseWdth / 10.0) ,  (int)(RefPoint.y + config.car.baseHeight / 2.0) };
		angle = 0;
	}

	frontalWheel->setRefPoint(C1Ref);
	posteriorWheel->setRefPoint(C2Ref);

	base->rotate(deg);
	frontalWheel->rotate(deg);
	posteriorWheel->rotate(deg);

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

	point newIceRefPoint;

	newIceRefPoint.x = oldRefPoint.x;
	newIceRefPoint.y = oldRefPoint.y + newBaseWidth / 3;

	iceCircle->setRefPoint(newIceRefPoint);

}
void IceCream::resizeDown(double factor) {
	point oldRefPoint = base->getRefPoint();

	base->resizeDown(factor);
	iceCircle->resizeDown(factor);

	double newBaseWidth = base->getbase();
	double newIceWidth = newBaseWidth / 2;

	point newIceRefPoint;

	newIceRefPoint.x = oldRefPoint.x;
	newIceRefPoint.y = oldRefPoint.y + newBaseWidth / 3;

	iceCircle->setRefPoint(newIceRefPoint);

}

void IceCream::rotate(double deg)
{

	point New_circleRef;
	angle += 90;

	if (angle >= 90 && angle < 180) {
		New_circleRef = { (int)(RefPoint.x - config.signShape.baseWdth / 2.0) ,(int)RefPoint.y };
	}
	else if (angle >= 180 && angle < 270) {
		New_circleRef = { (int)RefPoint.x,(int)(RefPoint.y - config.icecream.baseWdth / 3.0) };
	}
	else if (angle >= 270 && angle < 360) {
		New_circleRef = { (int)(RefPoint.x + config.signShape.baseWdth / 2.0),(int)RefPoint.y };

	}

	else {

		New_circleRef = { (int)RefPoint.x, (int)(RefPoint.y + config.icecream.baseWdth / 3.0) };
		angle = 0;
	}


	iceCircle->setRefPoint(New_circleRef);


	base->rotate(deg);
	iceCircle->rotate(deg);
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

	double newRocketBaseHeight = base->getHeight();
	double newRocketBaseWidth = base->getWidth();
	double newRocketHeadWidth = head->getbase();
	double newSmallBaseWidth = rightbase->getbase();

	point newLeftBaseRefPoint, newRightBaseRefPoint, newHeadRefPoint;

	newHeadRefPoint.x = oldRefPoint.x;
	newHeadRefPoint.y = oldRefPoint.y - newRocketBaseHeight / 2 - (sqrt(3) / 6.0) * newRocketHeadWidth;

	newLeftBaseRefPoint.x = oldRefPoint.x - newRocketBaseWidth / 2;
	newLeftBaseRefPoint.y = oldRefPoint.y + newRocketBaseHeight / 2 - newSmallBaseWidth / 3;

	newRightBaseRefPoint.x = oldRefPoint.x + newRocketBaseWidth / 2;
	newRightBaseRefPoint.y = oldRefPoint.y + newRocketBaseHeight / 2 - newSmallBaseWidth / 3;

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

	double newRocketBaseHeight = base->getHeight();
	double newRocketBaseWidth = base->getWidth();
	double newRocketHeadWidth = head->getbase();
	double newSmallBaseWidth = rightbase->getbase();

	point newLeftBaseRefPoint, newRightBaseRefPoint, newHeadRefPoint;

	newHeadRefPoint.x = oldRefPoint.x;
	newHeadRefPoint.y = oldRefPoint.y - newRocketBaseHeight / 2 - (sqrt(3) / 6.0) * newRocketHeadWidth;

	newLeftBaseRefPoint.x = oldRefPoint.x - newRocketBaseWidth / 2;
	newLeftBaseRefPoint.y = oldRefPoint.y + newRocketBaseHeight / 2 - newSmallBaseWidth / 3;

	newRightBaseRefPoint.x = oldRefPoint.x + newRocketBaseWidth / 2;
	newRightBaseRefPoint.y = oldRefPoint.y + newRocketBaseHeight / 2 - newSmallBaseWidth / 3;

	head->setRefPoint(newHeadRefPoint);
	liftbase->setRefPoint(newLeftBaseRefPoint);
	rightbase->setRefPoint(newRightBaseRefPoint);

}
void Rocket::rotate(double deg)
{
	point New_headref;
	point New_leftbaseRef;
	point New_rightbaseRef;
	angle += 90;

	if (angle >= 90 && angle < 180) {
		New_headref = { (int)(RefPoint.x + config.rocket.baseHeight / 2.0 + (sqrt(3) / 6.0) * config.rocket.headwdth) ,(int)RefPoint.y };
		New_leftbaseRef = { (int)(RefPoint.x - config.rocket.baseHeight / 2.0 + config.rocket.smallbaseWdth / 3.0),(int)(RefPoint.y - config.rocket.baseWdth / 2.0) };
		New_rightbaseRef = { (int)(RefPoint.x - config.rocket.baseHeight / 2.0 + config.rocket.smallbaseWdth / 3.0),(int)(RefPoint.y + config.rocket.baseWdth / 2.0) };
	}
	else if (angle >= 180 && angle < 270) {
		New_headref = { (int)RefPoint.x, (int)(RefPoint.y + config.rocket.baseHeight / 2.0 + (sqrt(3) / 6.0) * config.rocket.headwdth) };
		New_leftbaseRef = { (int)(RefPoint.x - config.rocket.baseWdth / 2.0), (int)(RefPoint.y - config.rocket.baseHeight / 2.0 + config.rocket.smallbaseWdth / 3.0) };
		New_rightbaseRef = { (int)(RefPoint.x + config.rocket.baseWdth / 2.0) , (int)(RefPoint.y - config.rocket.baseHeight / 2.0 + config.rocket.smallbaseWdth / 3.0) };
	}
	else if (angle >= 270 && angle < 360) {
		New_headref = { (int)(RefPoint.x - config.rocket.baseHeight / 2.0 - (sqrt(3) / 6.0) * config.rocket.headwdth) ,(int)RefPoint.y };
		New_leftbaseRef = { (int)(RefPoint.x + config.rocket.baseHeight / 2.0 - config.rocket.smallbaseWdth / 3.0),(int)(RefPoint.y - config.rocket.baseWdth / 2.0) };
		New_rightbaseRef = { (int)(RefPoint.x + config.rocket.baseHeight / 2.0 - config.rocket.smallbaseWdth / 3.0),(int)(RefPoint.y + config.rocket.baseWdth / 2.0) };
	}

	else {

		New_headref = { (int)RefPoint.x, (int)(RefPoint.y - config.rocket.baseHeight / 2.0 - (sqrt(3) / 6.0) * config.rocket.headwdth) };
		New_leftbaseRef = { (int)(RefPoint.x - config.rocket.baseWdth / 2.0), (int)(RefPoint.y + config.rocket.baseHeight / 2.0 - config.rocket.smallbaseWdth / 3.0) };
		New_rightbaseRef = { (int)(RefPoint.x + config.rocket.baseWdth / 2.0) , (int)(RefPoint.y + config.rocket.baseHeight / 2.0 - config.rocket.smallbaseWdth / 3.0) };

		angle = 0;
	}



	head->setRefPoint(New_headref);
	liftbase->setRefPoint(New_leftbaseRef);
	rightbase->setRefPoint(New_rightbaseRef);

	rightbase->rotate(deg);
	liftbase->rotate(deg);
	head->rotate(deg);
	base->rotate(deg);
}

void Rocket::moveUp(double dist) {
	base->moveUp(dist);
	head->moveUp(dist);
	liftbase->moveUp(dist);
	rightbase->moveUp(dist);
}

void Rocket::moveDown(double dist) {
	base->moveDown(dist);
	head->moveDown(dist);
	liftbase->moveDown(dist);
	rightbase->moveDown(dist);
}

void Rocket::moveRight(double dist) {
	base->moveRight(dist);
	head->moveRight(dist);
	liftbase->moveRight(dist);
	rightbase->moveRight(dist);
}

void Rocket::moveLeft(double dist) {
	base->moveLeft(dist);
	head->moveLeft(dist);
	liftbase->moveLeft(dist);
	rightbase->moveLeft(dist);
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

	point newDoorRefPoint;
	point newHeadRefPoint;

	newDoorRefPoint.x = oldRefPoint.x;
	newHeadRefPoint.x = oldRefPoint.x;

	newHeadRefPoint.y = oldRefPoint.y - newHouseBaseHeight / 2 - (sqrt(3) / 6.0) * newHouseBaseWidth;
	newDoorRefPoint.y = oldRefPoint.y + newHouseBaseHeight / 2 - newDoorHeight / 2;

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

	point newDoorRefPoint;
	point newHeadRefPoint;

	newDoorRefPoint.x = oldRefPoint.x;
	newHeadRefPoint.x = oldRefPoint.x;

	newHeadRefPoint.y = oldRefPoint.y - newHouseBaseHeight / 2 - (sqrt(3) / 6.0) * newHouseBaseWidth;
	newDoorRefPoint.y = oldRefPoint.y + newHouseBaseHeight / 2 - newDoorHeight / 2;

	door->setRefPoint(newDoorRefPoint);
	head->setRefPoint(newHeadRefPoint);
}

void House::rotate(double deg)
{
	point New_headRef;
	point New_doorRef;

	angle += 90;

	if (angle >= 90 && angle < 180) {
		New_headRef = { (int)(RefPoint.x + config.house.baseHeight / 2.0 + (sqrt(3) / 6.0) * config.house.baseWdth),(int)RefPoint.y };
		New_doorRef = { (int)(RefPoint.x - config.house.baseHeight / 2.0 + config.house.doorhight / 2.0),(int)RefPoint.y };
	}
	else if (angle >= 180 && angle < 270) {
		New_headRef = { (int)RefPoint.x, (int)(RefPoint.y + config.house.baseHeight / 2.0 + (sqrt(3) / 6.0) * config.house.headwdth) };
		New_doorRef = { (int)RefPoint.x, (int)(RefPoint.y - config.house.baseHeight / 2.0 + config.house.doorhight / 2.0) };
	}
	else if (angle >= 270 && angle < 360) {
		New_headRef = { (int)(RefPoint.x - config.house.baseHeight / 2.0 - (sqrt(3) / 6.0) * config.house.baseWdth),(int)RefPoint.y };
		New_doorRef = { (int)(RefPoint.x + config.house.baseHeight / 2.0 - config.house.doorhight / 2.0),(int)RefPoint.y };

	}

	else {

		New_headRef = { (int)RefPoint.x, (int)(RefPoint.y - config.house.baseHeight / 2.0 - (sqrt(3) / 6.0) * config.house.headwdth) };
		New_doorRef = { (int)RefPoint.x, (int)(RefPoint.y + config.house.baseHeight / 2.0 - config.house.doorhight / 2.0) };
		angle = 0;
	}


	head->setRefPoint(New_headRef);
	door->setRefPoint(New_doorRef);


	head->rotate(deg);
	base->rotate(deg);
	door->rotate(deg);
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