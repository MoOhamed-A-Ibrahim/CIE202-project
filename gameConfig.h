#pragma once
#include "CMUgraphicsLib/CMUgraphics.h"


//The folowing struct contains all game configurations
// (MAY be loaded from a configuration file later)
__declspec(selectany) //This line to prevent "redefinition error"
struct
{
	int	windWidth = 1200, windHeight = 600,	//Window width and height
		wx = 5, wy = 5,			//Window starting coordinates

		//The window is divded into 3 areas: toolbar, Working area, and statusbar
		toolBarHeight = 60,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		toolbarItemWidth = 70,			//Width of each icon in toolbar
		statusBarHeight = 50;	//Status Bar Height

	int remainingHeight = windHeight - toolBarHeight - statusBarHeight;

	int gridHeight = int(remainingHeight * (2 / 3.0)); 		//The grid is where bricks can be drawn

	//Default colors
	color	penColor = RED,			//color used to draw borders/write messages
		fillColor = BLUE,			//shapes fill color (Default)
		bkGrndColor = LAVENDER,		//Screen Background color
		statusBarColor = LIGHTSEAGREEN;	//background color of the status
	int penWidth = 3;			//width of the pen that draws shapes


	color gridDotsColor = RED;
	int gridSpacing = 30;	//spacing between grid points

	////// Configuration for the composite shapes //////
	// default Ref Point for any newly created shape 
	int RefX = windWidth * (2.0 / 3);
	int RefY = windHeight * (0.5);

	////-----  Sign Shape Confoguration ---------////
	// For the Sign shape, define width and height of both rectangles
	struct {
		double baseWdth = 20, baseHeight = 80;
		double topWdth = 100, topHeight = 50;
	}signShape;

	struct {
		double baseWdth = 20, baseHeight = 80;
		double triwdth = 100;
	}tree;

	struct {
		double baseWdth = 160, baseHeight = 100;
		double wheelRadius = 20;
	}car;

	struct {
		double baseWdth = 30;
	}icecream;

	struct {
		double baseWdth = 35, baseHeight = 100;
		double headwdth = 35;
		double smallbaseWdth = 15;
	}rocket;

	struct {
		double baseWdth = 100, baseHeight = 100;
		double headwdth = 100;
		double doorwdth = 30; double doorhight = 60;
	}house;

}config;
enum toolbarItem //The items of the  toolbar (you should add more items)
{
	//Note: Items are ordered here as they appear in the toolbar
	//If you want to change the toolbar items order, just change the order here
	ITM_SIGN,
	ITM_TREE,
	ITM_CAR,
	ITM_ICECREAM,
	ITM_ROCKET,
	ITM_HOUSE,
	ITM_Enlarge,
	ITM_Minimize,
	ITM_Hint,
	ITM_Rotate,
	ITM_Refresh,
	ITM_Select,
	ITM_Trash,
	ITM_Save,
	ITM_LOAD,
	ITM_BLANK,
	ITM_EXIT,

	ITM_CNT		//no. of toolbar items ==> This should be the last line in this enum

};