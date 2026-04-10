/*
max width = 80 columns
tab = 4 spaces
01234567890123456789012345678901234567890123456789012345678901234567890123456789
*/

/*	Linguagens e Ambientes de Programação - Projeto de 2021/2022

	Eye Beast

	Program written in C/C ++ over the wxWidget platform.
	The wxWidget platform runs on Windows, MacOS and Linux.

	This file is only a starting point fo your work. The entire file can
	be changed, starting with this comment.


 AUTHORS IDENTIFICATION
	Student 1: 58119, Jose Trigueiro


O extra implementado foi a ideia dos niveis.
O jogo tem 3 niveis, o mais facil com 5 monstros,
o medio com 6 monstros e o mais dificil com 7 monstros.
Entre cada nivel aparece uma mensagem "Next level" ate finalizar o 3o nivel,
onde aparece "You won", ganhando assim o jogo.
Na barra inferior do jogo e dito em que nivel nos apresentamos,
sendo o primeiro nivel o nivel 1, depois o 2 e por fim o 3. 
Uma vez que o jogo faz uma pausa no final de cada nivel, e necessario
fazer RESTART para iniciar cada nivel, de forma a atualizar o numero de monstros.


 Place here the names and numbers of the authors, plus some comments, as
 asked in the listing of the project. Do not deliver an anonymous file with
 unknown authors.
*/

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* IDENTIFICATION */

#define APP_NAME	"Eye Beast"

#define AUTHOR1		"Jose Trigueiro (58119)"
#define AUTHOR2		"null"

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* INCLUDES */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "wxTiny.h"


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* STRINGS */

#define MAX_STRING	256
#define MAX_LINE	1024

typedef char String[MAX_STRING];
typedef char Line[MAX_LINE];


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* IMAGES */

/******************************************************************************
 * The images are specified in the XPM format [http://en.wikipedia.org/wiki/X_PixMap]
 * After created, each image is represented by an integer in the wxTiny library.
 ******************************************************************************/

typedef int Image;

static Image emptyImg, heroImg, chaserImg, blockImg, boundaryImg, invalidImg;

/* XPM */
static tyImage empty_xpm = {
"16 16 2 1",
"   c None",
".  c #FFFFFF",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................"};

/* XPM */
static tyImage hero_xpm = {
"16 16 3 1",
"   c None",
".  c #FFFFFF",
"+  c #000000",
"................",
"...+++...+++....",
"..+...+.+...+...",
".+.....+.....+..",
".+...+++++...+..",
".+...+++++...+..",
".+...+++++...+..",
".+.....+.....+..",
"..+...+.+...+...",
"...+++...+++....",
"................",
".....+++++......",
"....+.....+.....",
"................",
"................",
"................"};


/* XPM */
static tyImage chaser_xpm = {
"16 16 3 1",
"   c None",
".  c #FFFFFF",
"+  c #000000",
"................",
"...+++...+++....",
"..++.++.+.+++...",
".+..+++++++..+..",
".+...+++++...+..",
".+...+++++...+..",
".+...+++++...+..",
"..+...+.+...+...",
"...+++...+++....",
"................",
"................",
"....+++++++.....",
"................",
"................",
"................",
"................"};

/* XPM */
static tyImage block_xpm = {
"16 16 3 1",
"   c None",
".  c #000000",
"+  c #FFFFFF",
"................",
"................",
"..............+.",
"....+.+.+.+.+...",
"...+.+.+.+.+..+.",
"....+.+.+.+.+...",
"...+.+.+.+.+..+.",
"....+.+.+.+.+...",
"...+.+.+.+.+..+.",
"....+.+.+.+.+...",
"...+.+.+.+.+..+.",
"....+.+.+.+.+...",
"...+.+.+.+.+..+.",
"................",
"..+.+.+.+.+.+.+.",
"................"};

/* XPM */
static tyImage boundary_xpm = {
"16 16 3 1",
"   c None",
".  c #000000",
"+  c #FFFFFF",
"................",
"................",
"..............+.",
"....+.+.+.+.+...",
"...+.+.+.+.+..+.",
"....+.+.+.+.+...",
"...+.+.+.+.+..+.",
"....+.+.+.+.+...",
"...+.+.+.+.+..+.",
"....+.+.+.+.+...",
"...+.+.+.+.+..+.",
"....+.+.+.+.+...",
"...+.+.+.+.+..+.",
"................",
"..+.+.+.+.+.+.+.",
"................"};

/* XPM */
static tyImage invalid_xpm = {
"16 16 2 1",
"   c None",
".  c #FFFFFF",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................"};


/******************************************************************************
 * imagesCreate - Converts all the XPM images to the type Image
 ******************************************************************************/
void imagesCreate(void)
{
	emptyImg = tyCreateImage(empty_xpm);
	heroImg = tyCreateImage(hero_xpm);
	chaserImg = tyCreateImage(chaser_xpm);
	blockImg = tyCreateImage(block_xpm);
	boundaryImg = tyCreateImage(boundary_xpm);
	invalidImg = tyCreateImage(invalid_xpm);
}


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* ACTORS */

/******************************************************************************
 * Constants, types and functions for all kinds of actors
 ******************************************************************************/

#define ACTOR_PIXELS_X	16
#define ACTOR_PIXELS_Y	16

typedef enum {
	EMPTY, HERO, CHASER, BLOCK, BOUNDARY
} ActorKind;

typedef struct {
// specific fields can go here, but probably none will be needed
} Hero;

typedef struct {
// specific fields can go here, but probably none will be needed
} Chaser;

typedef struct {
// specific fields can go here, but probably none will be needed
} Block;

typedef struct {
// specific fields can go here, but probably none will be needed
} Boundary;

typedef struct {
// factored common fields
	ActorKind kind;
	int x, y;
	Image image;
	union { 
// specific fields for each kind
		Hero hero;
		Chaser chaser;
		Block block;
		Boundary boundary;
	} u;
	bool isTasty, isMovable;
} ActorStruct, *Actor;

#define WORLD_SIZE_X	31
#define WORLD_SIZE_Y	18
#define N_INNER_BLOCKS  110
#define N_MONSTERS      7
int level = 1;
int numMonsters = 5;

typedef struct {
	Actor world[WORLD_SIZE_X][WORLD_SIZE_Y];
	Actor hero;
	Actor monsters[N_MONSTERS];
} GameStruct, *Game;

/******************************************************************************
 * actorImage - Get the screen image corresponding to some kind of actor
 ******************************************************************************/
Image actorImage(ActorKind kind)
{
	switch( kind ) {
		case EMPTY:		return emptyImg;
		case HERO:		return heroImg;
		case CHASER:	return chaserImg;
		case BLOCK:		return blockImg;
		case BOUNDARY:	return boundaryImg;
		default:		return invalidImg;
	}
}

/******************************************************************************
 * cellSet - Useful function to update one cell in the matrix and in the screen
 ******************************************************************************/
void cellSet(Game g, Actor a, int x, int y, Image img)
{
	tyDrawImage(img, x * ACTOR_PIXELS_X, y * ACTOR_PIXELS_Y);
	g->world[x][y] = a;	
}

/******************************************************************************
 * cellIsEmpty - Check in the matrix if a cell is empty (if contains NULL)
 ******************************************************************************/
bool cellIsEmpty(Game g, int x, int y)
{
	return g->world[x][y] == NULL;
}

/******************************************************************************
 * actorShow - Install an actor in the matrix and in the screen
 ******************************************************************************/
void actorShow(Game g, Actor a)
{
	cellSet(g, a, a->x, a->y, a->image);
}

/******************************************************************************
 * actorHide - Removes an actor from the matrix and from the screen
 ******************************************************************************/
void actorHide(Game g, Actor a)
{
	cellSet(g, NULL, a->x, a->y, emptyImg);
}

/******************************************************************************
 * actorMove - Move an actor to a new position
 * pre: the new position is empty
 ******************************************************************************/
void actorMove(Game g, Actor a, int nx, int ny)
{
	actorHide(g, a);
	a->x = nx;
	a->y = ny;
	actorShow(g, a);
}

/******************************************************************************
 * actorNew - Creates a new actor and installs it in the matrix and the screen
 ******************************************************************************/
Actor actorNew(Game g, ActorKind kind, int x, int y)
{
	Actor a = malloc(sizeof(ActorStruct));
	a->kind = kind;
	a->x = x;
	a->y = y;
	a->image = actorImage(kind);
	a->isTasty = false;
	a->isMovable = false;
	actorShow(g, a);
	return a;
}

/******************************************************************************
 * heroAnimation - The hero moves using the cursor keys
 * INCOMPLETE!
 ******************************************************************************/
bool differentKindActors(Actor a, Actor b) {
	if(a->kind != b->kind)
		return true;
	return false;
	
}

void blockMove(Game g, int nx, int ny, int dx, int dy) {
	int v = 0;
	Actor blocks[WORLD_SIZE_X-4];
	
	for (int i = nx, j = ny; g->world[i][j]->isMovable; i+=dx, j+=dy, v++) {
		blocks[v] = g->world[i][j];
		if (cellIsEmpty(g, i+dx, j+dy)){
			 break;
	 	}
		else if (!g->world[i+dx][j+dy]->isMovable) //aborta
			return;
	}
	
		
	while (v > -1) {	
		actorMove(g, blocks[v], blocks[v]->x + dx, blocks[v]->y + dy);
		v--;
	}
	actorMove(g, g->hero, nx, ny);
	
		
}

void heroAnimation(Game g, Actor a)
{
	int dx = tyKeyDeltaX(), dy = tyKeyDeltaY();
	int nx = a->x + dx, ny = a->y + dy;
	if (cellIsEmpty(g, nx, ny))
		//mover heroi
		actorMove(g, a, nx, ny);
	else if (!cellIsEmpty(g, nx, ny) && 
	         g->world[nx][ny]->isTasty && 
	         differentKindActors(a,g->world[nx][ny])) {
		//terminar jogo
		tyAlertDialog("DEAD MEAT!!!", "See you later!");
		tyPaused(true);
	}
	else if (!cellIsEmpty(g, nx, ny) && 
	         !g->world[nx][ny]->isTasty &&
	         g->world[nx][ny]->isMovable)
		//empurrar
	   	blockMove(g, nx, ny, dx, dy);
	
}

/******************************************************************************
 * monsterAnimation - The monster moves
 * INCOMPLETE!
 * Needs smart movement!!!
 ******************************************************************************/
bool monsterAnimation(Game g, Actor monster, Actor hero) 
{
	int minx = monster->x, miny = monster->y, count = 0, nx, ny;
	bool canMove = true;
	
	for (int i = -1; i <= 1; i++)
	    for (int j = -1; j <= 1; j++) {
	    	if (!cellIsEmpty(g, monster->x + i, monster->y + j) && 
	    	    g->world[monster->x + i][monster->y + j] == hero) {
	    		actorHide(g, hero);
	    		actorMove(g, monster, monster->x + i, monster->y + j);
	    		tyAlertDialog("DEAD MEAT!!!", "See you later!");
		        tyPaused(true);
	    	}
	    	
	    	else if (cellIsEmpty(g, monster->x + i, monster->y + j) && 
	    	  tyDistance(monster->x + i, monster->y + j, hero->x, hero->y) < 
	    	    	tyDistance(minx, miny, hero->x, hero->y)) {
	    	    		minx = monster->x + i;
	    	    		miny = monster->y + j;
	    	    	}
		}
	
	if (cellIsEmpty(g, minx, miny)) 
		actorMove(g, monster, minx, miny);
	else 
		for (int i = -1; i <= 1; i++)
	    		for (int j = -1; j <= 1; j++) 
	    		  if (cellIsEmpty(g, monster->x + i, monster->y + j)) {
	    		    canMove = true;	    		    
	    		    do{
				nx = monster->x + tyRand(2) - tyRand(2);
				ny = monster->y + tyRand(2) - tyRand(2);
			    } while (!cellIsEmpty(g,nx,ny));
	    		    break;
	    		    actorMove(g, monster, nx, ny);
		          } else canMove = false;
			
	return canMove;    	
		
}

/******************************************************************************
 * actorAnimation - The actor behaves according to its kind
 * INCOMPLETE!
 ******************************************************************************/
int actorAnimation(Game g, Actor a)
{
	switch( a->kind ) {
		case HERO: heroAnimation(g, a);break;
		case CHASER: 
			if (!monsterAnimation(g, a, g->hero)) //nao move
				return 1;
			break;
		default: break;
	}
	
	return 0;
	
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* GAME */

/******************************************************************************
 * gameClearWorld - Clears the matrix and the screen
 ******************************************************************************/
void gameClearWorld(Game g)
{
	for(int y = 0; y < WORLD_SIZE_Y ; y++)
		for(int x = 0; x < WORLD_SIZE_X ; x++ )
			cellSet(g, NULL, x, y, emptyImg);
}

/******************************************************************************
 * gameInstallBoundaries - Install the boundary blocks
 ******************************************************************************/
void gameInstallBoundaries(Game g)
{
	for(int y = 0; y < WORLD_SIZE_Y ; y++)
		for(int x = 0; x < WORLD_SIZE_X ; x++)
			if( x == 0 || x == WORLD_SIZE_X - 1
			|| y == 0 || y == WORLD_SIZE_Y - 1 ) {
				actorNew(g, BOUNDARY, x, y);
			}
}

/******************************************************************************
 * gameInstallBlocks - Install the movable blocks
 * INCOMPLETE!
 ******************************************************************************/
void gameInstallBlocks(Game g)
{
	int x, y;	
	
	for (int i = 0; i < N_INNER_BLOCKS; i++) {	
		do {
		    x = tyRand(WORLD_SIZE_X);
		    y = tyRand(WORLD_SIZE_Y);
		} while (!cellIsEmpty(g, x, y));
		
		Actor aux = actorNew(g, BLOCK, x, y);
		aux->isMovable = true;
	}
}

/******************************************************************************
 * gameInstallMonsters - Install the monsters
 * INCOMPLETE!
 ******************************************************************************/
void gameInstallMonsters(Game g)
{
	int x, y;
	
	for (int i = 0; i < numMonsters; i++) {
		do {
		    x = tyRand(WORLD_SIZE_X);
		    y = tyRand(WORLD_SIZE_Y);
		} while (!cellIsEmpty(g, x, y));
		
		g->monsters[i] = actorNew(g, CHASER, x, y);
		g->monsters[i]->isTasty = true;
		
	}
}

/******************************************************************************
 * gameInstallHero - Install the hero
 * INCOMPLETE! This code is to change
 ******************************************************************************/
bool isMonsterNearHero(Game g,int x, int y) {
	for (int i = 0; i < numMonsters; i++)
		if (tyDistance(x, y, g->monsters[i]->x, g->monsters[i]->y) <= 4)
			return true;
	return false;
}

void gameInstallHero(Game g)
{	
	int x, y;
	
	do {
		x = tyRand(WORLD_SIZE_X);
		y = tyRand(WORLD_SIZE_Y);
	} while (!cellIsEmpty(g, x, y) || isMonsterNearHero(g, x, y));
	
	g->hero = actorNew(g, HERO, x, y);
	g->hero->isTasty = true;
		
}

/******************************************************************************
 * gameInit - Initialize the matrix and the screen
 ******************************************************************************/
Game gameInit(Game g)
{
	if (g == NULL)
		g = malloc(sizeof(GameStruct));
	imagesCreate();
	gameClearWorld(g);
	gameInstallBoundaries(g);
	gameInstallBlocks(g);
	gameInstallMonsters(g);
	gameInstallHero(g);
	return g;
}

/******************************************************************************
 * gameRedraw - Redraws the entire scenario. This function is called by
 * tyHandleRedraw in very specific circumstances. It should not be used anywhere
 * else because you don't want to be constantly redrawing the whole scenario.
 ******************************************************************************/
void gameRedraw(Game g)
{
	for(int y = 0; y < WORLD_SIZE_Y; y++)
		for(int x = 0; x < WORLD_SIZE_X; x++) {
			Actor a = g->world[x][y];
			if( !cellIsEmpty(g, x, y) )
				actorShow(g, a);
		}
}

/******************************************************************************
 * gameAnimation - Sends animation events to all the animated actors
 * This function is called every tenth of a second (more or less...)
 * INCOMPLETE!
******************************************************************************/
int counter = 1;

bool gameAnimation(Game g) {
	int won = 0;
		
	actorAnimation(g, g->hero);
	if (counter == 10) {
		counter = 1;
		for(int i = 0 ; i < numMonsters ; i++)
			won += actorAnimation(g, g->monsters[i]);
		}
	else counter++;
	
	return won == numMonsters;		
}


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* STATUS BAR */

/******************************************************************************
 * The function status populates the status bar, at the bottom of the window
 ******************************************************************************/

#define STATUS_ITEMS	5

void status(void)
{
	String s,c;
	sprintf(s, "TIME = %d seg.", tySeconds());
	tySetStatusText(4, s);
	sprintf(c, "LEVEL = %d", level);
	tySetStatusText(1, c);
}



/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* MENU COMMANDS */

/******************************************************************************
 * Each function handles one menu command
 ******************************************************************************/

void comandAbout(void)
{
	tyAlertDialog("About", "%s\n%s\n\n%s\n%s",
		APP_NAME,
		"(Reimplementation of the original game of Chuck Shotton)",
		AUTHOR1,
		AUTHOR2);


}

void comandRestart(void)
{
	tyHandleStart();
}

void comandFinish(void)
{
	tyAlertDialog("Quit", "See you later!");
	level = 1;
	numMonsters = 5;
	tyQuit();
}


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/


/* FUNCTIONS REQUIRED BY THE FRAMEWORK wxTiny */

/******************************************************************************
 * Section with all the "root" "functions required by the wxTiny support system. 
 * 
 * There is no function "main" in a wxTiny program, as the main function is
 * hidden within the wxTiny library. The most important thing you need to know
 * is that the function "tyHandleStart" is called when the program begins,
 * and that function "tyHandleTime" is called periodically 10 times per second,
 * to make the program progress. In some sense, both this function make a kind
 * of main function.
 * 
 * More information about the wxTiny functions in the file "wxTiny.h".
 ******************************************************************************/

static Game game = NULL; // defined here to be available to the "root" functions

/****************************************************************************** 
 * tyAppName - specify the name of the app
 ******************************************************************************/
tyStr tyAppName(void)
{
	return APP_NAME;
}

/****************************************************************************** 
 * tyWidth - specify the width of the window
 ******************************************************************************/
int tyWidth(void)
{
	return WORLD_SIZE_X * ACTOR_PIXELS_X;
}

/****************************************************************************** 
 * tyHeight - specify the height of the window
 ******************************************************************************/
int tyHeight(void)
{
	return WORLD_SIZE_Y * ACTOR_PIXELS_Y;
}

/****************************************************************************** 
 * tyStatusItems - specify the number of slots available in the status bar
 ******************************************************************************/
int tyStatusItems(void)
{
	return STATUS_ITEMS;
}

/****************************************************************************** 
 * tyMenus - specify the menus
 ******************************************************************************/
tyStr tyMenus(void)
{
	return ":+Menu"
			":&About\tCtrl-A"
			":-"
			":&Restart\tCtrl-R"
			":-"
			":&Quit\tCtrl-Q";
}

/****************************************************************************** 
 * tyHandleMenuCommand - Handles the menu commands
 ******************************************************************************/
void tyHandleMenuCommand(tyStr command)
{
	if( strcmp(command, "About") == 0 )
		comandAbout();
	else if( strcmp(command, "Restart") == 0 )
		comandRestart();
	else if( strcmp(command, "Quit") == 0 )
		comandFinish();
	else
		tyFatalError("Unknown command: \"%s\"", command);
}

/****************************************************************************** 
 * tyHandleRedraw - redraws the window
 *
 * Automatically called in rare situations, for example if the game window is
 * minimized and then maximized
 ******************************************************************************/
void tyHandleRedraw(void)
{
	gameRedraw(game);
}

/****************************************************************************** 
 * tyHandleTime - Called periodically, around 10 time per second
 * 
 * This function does the following: animate the actors; update the status bar;
 *	possibly more things
 ******************************************************************************/
void tyHandleTime(void)
{
	status();
	if (gameAnimation(game)) { //ganhaste
		if (level < 3) {
			tyAlertDialog("Next level...", "Lets goo!");
			numMonsters++;
			level++;
		}
		else {
			tyAlertDialog("You won!!", "All 3 levels are completed");
		}
		tyPaused(true);
	}
}

/****************************************************************************** 
 * tyHandleStart - Program initialization
 ******************************************************************************/
void tyHandleStart(void)
{
	tyPaused(false);
	tySecondsSetZero();
	game = gameInit(game);
}
