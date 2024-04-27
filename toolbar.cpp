#include "toolbar.h"
#include "game.h"
//#include "grid.h"


////////////////////////////////////////////////////  class toolbar   //////////////////////////////////////////////
toolbar::toolbar(game* pG)
{
	height = config.toolBarHeight;
	width = config.windWidth;
	this->pGame = pG;
	window* pWind = pGame->getWind();

	//You can draw the tool bar icons in any way you want.

	//First prepare List of images for each toolbar item
	toolbarItemImages[ITM_SIGN] = "images\\toolbarItems\\toolbar_sign.jpg";
	toolbarItemImages[ITM_TREE] = "images\\toolbarItems\\Tree.jpg";
	toolbarItemImages[ITM_CAR] = "images\\toolbarItems\\Car.jpg";
	toolbarItemImages[ITM_ICECREAM] = "images\\toolbarItems\\Icecream.jpg";
	toolbarItemImages[ITM_ROCKET] = "images\\toolbarItems\\Rocket.jpg";
	toolbarItemImages[ITM_HOUSE] = "images\\toolbarItems\\House.jpg";
	toolbarItemImages[ITM_EXIT] = "images\\toolbarItems\\Exit.jpg";
	toolbarItemImages[ITM_Rotate] = "images\\toolbarItems\\Rotate.jpg";
	toolbarItemImages[ITM_Enlarge] = "images\\toolbarItems\\Enlarge.jpg";
	toolbarItemImages[ITM_Minimize] = "images\\toolbarItems\\Minimize.jpg";
	toolbarItemImages[ITM_Trash] = "images\\toolbarItems\\Trash.jpg";
	toolbarItemImages[ITM_Select] = "images\\toolbarItems\\Select.jpg";
	toolbarItemImages[ITM_Refresh] = "images\\toolbarItems\\Refresh.jpg";
	toolbarItemImages[ITM_LOAD] = "images\\toolbarItems\\Load.jpg";
	toolbarItemImages[ITM_BLANK] = "images\\toolbarItems\\Blank.jpg";
	toolbarItemImages[ITM_Hint] = "images\\toolbarItems\\Hint.jpg";
	toolbarItemImages[ITM_Save] = "images\\toolbarItems\\Save.jpg";

	//TODO: Prepare image for each toolbar item and add it to the list

	//Draw toolbar item one image at a time
	for (int i = 0; i < ITM_CNT; i++)
		pWind->DrawImage(toolbarItemImages[i], i * config.toolbarItemWidth, 0, config.toolbarItemWidth, height);
	//pWind->SetPen(RED, 2);
	//pWind->DrawString(1000,50,"xx");
	//Draw a line under the toolbar
	pWind->SetPen(DARKBLUE, 3);
	pWind->DrawLine(0, height, width, height);

}



//handles clicks on toolbar icons, returns ITM_CNT if the click is not inside the toolbar
toolbarItem toolbar::getItemClicked(int x)
{
	//Check whick toolbar item was clicked
	//==> This assumes that toolbar items are lined up horizontally <==
	//Divide x coord of the point clicked by the icon width (int division)
	//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on





	if (x > ITM_CNT * config.toolbarItemWidth)	//click outside toolbar boundaries
		return ITM_CNT;

	return (toolbarItem)(x / config.toolbarItemWidth);

}