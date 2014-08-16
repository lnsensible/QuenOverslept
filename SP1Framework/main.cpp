// This is the main file to hold everthing together

#include "Framework\timer.h"
#include "game.h"
#include <iostream>


StopWatch g_timer;            // Timer function to keep track of time and the frame rate
bool g_quitGame = false;      // Set to true if you want to quit the game
bool atMenu = true;			  // Check if user is at menu
const unsigned char FPS = 10; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame
int initialisedornot = 0;
int initialisedornot2 = 1;

void mainLoop();

// TODO:
// Bug in waitUnitil. it waits for the time from getElapsedTime to waitUntil, but should be insignificant.

void SetWindow(int Width, int Height)  //from 3dbuzz.com
   { 
    _COORD coord; 
    coord.X = Width; 
    coord.Y = Height; 

    _SMALL_RECT Rect; 
    Rect.Top = 0; 
    Rect.Left = 0; 
    Rect.Bottom = Height - 1; 
    Rect.Right = Width - 1; 

    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle 
    SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size 
    SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size 
    } 

int main()
{
	SetWindow(80, 26); //set size of console
    mainLoop();  // main loop
    shutdown();  // do clean up, if any. free memory.
	
	return 0;
}

// This main loop calls functions to get input, update and render the game
// at a specific frame rate
void mainLoop()
{
	while ( g_quitGame != true )
	{
		g_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
		while ( gamestate == MENU ) // MAIN MENU (SELECT GAME HERE)
		{

			if ( initialisedornot != 1 )
			{
				initMenu();
				initialisedornot = 1;
			}

			getInput();
			updateMenu(g_timer.getElapsedTime());
			renderMenu();
			g_timer.waitUntil(frameTime);

			if ( g_quitGame == true )
			break;
		}
		initialisedornot = 0;

		while ( gamestate == GAME ) // tests
		{

			if ( initialisedornot != 1 )
			{
				init();
				initialisedornot = 1;
			}

			getInput();
			update(g_timer.getElapsedTime());
			render();
			g_timer.waitUntil(frameTime);

			if ( g_quitGame == true )
			break;
		}
		initialisedornot = 0;

		while ( gamestate == DEFENDMENU ) // DEFEND! GAME MENU
		{

			if ( initialisedornot != 1 )
			{
				initDefendMenu();
				initialisedornot = 1;
			}

			getInput();
			updateDefendMenu(g_timer.getElapsedTime());
			renderDefendMenu();
			g_timer.waitUntil(frameTime);

			if ( g_quitGame == true )
			break;
		}
		initialisedornot = 0;

		while ( gamestate == DEFENDINSTRUCTION1 ) // DEFEND! GAME INSTRUCTIONS PAGE 1
		{

			if ( initialisedornot != 1 )
			{
				initDefendInstructions1();
				initialisedornot = 1;
			}

			getInput();
			updateDefendInstructions1(g_timer.getElapsedTime());
			renderDefendInstructions1();
			g_timer.waitUntil(frameTime);

			if ( g_quitGame == true )
			break;
		}
		initialisedornot = 0;

		while ( gamestate == DEFENDINSTRUCTION2 ) // DEFEND! GAME INSTRUCTIONS PAGE 2
		{

			if ( initialisedornot != 1 )
			{
				initDefendInstructions2();
				initialisedornot = 1;
			}

			getInput();
			updateDefendInstructions2(g_timer.getElapsedTime());
			renderDefendInstructions2();
			g_timer.waitUntil(frameTime);

			if ( g_quitGame == true )
			break;
		}
		initialisedornot = 0;

		while ( gamestate == DEFENDINSTRUCTION3 ) // DEFEND! GAME INSTRUCTIONS PAGE 3
		{

			if ( initialisedornot != 1 )
			{
				initDefendInstructions3();
				initialisedornot = 1;
			}

			getInput();
			updateDefendInstructions3(g_timer.getElapsedTime());
			renderDefendInstructions3();
			g_timer.waitUntil(frameTime);

			if ( g_quitGame == true )
			break;
		}
		initialisedornot = 0;

		while ( gamestate == DEFENDPLAY ) // DEFEND! GAME
		{

			if ( initialisedornot != 1 )
			{
				initDefend();
				initialisedornot = 1;
			}
				getInput();
				updateDefend(g_timer.getElapsedTime());
				renderDefend();
				g_timer.waitUntil(frameTime);

			if ( g_quitGame == true )
				break;
		}
		initialisedornot = 0;

		while ( gamestate == DEFENDUPGRADES ) // DEFEND! UPGRADE PAGE
		{

			if ( initialisedornot != 1 )
			{
				initDefendUpgrade();
				initialisedornot = 1;
			}

			getInput();
			updateDefendUpgrade(g_timer.getElapsedTime());
			renderDefendUpgrade();
			g_timer.waitUntil(frameTime);

			if ( g_quitGame == true )
				break;
		}
		initialisedornot = 0;

		while ( gamestate == DEFENDGAMEOVER ) // DEFEND! GAME OVER
		{

			if ( initialisedornot != 1 )
			{
				initDefendGO();
				initialisedornot = 1;
			}

			getInput();
			updateDefendGO(g_timer.getElapsedTime());
			renderDefendGO();
			g_timer.waitUntil(frameTime);

			if ( g_quitGame == true )
				break;
		}
		initialisedornot = 0;
		
		while ( gamestate == DEFENDINTRODUCTION ) // DEFEND! INTRODUCTION
		{

			if ( initialisedornot != 1 )
			{
				initDefendIntroduction();
				initialisedornot = 1;
			}

			getInput();
			updateDefendIntroduction(g_timer.getElapsedTime());
			renderDefendIntroduction();
			g_timer.waitUntil(frameTime);

			if ( g_quitGame == true )
				break;
		}
		initialisedornot = 0;
		
		while ( gamestate == DEFENDHIGHSCORE ) // DEFEND! High Score
		{

			if ( initialisedornot != 1 )
			{
				initDefendHS();
				initialisedornot = 1;
			}

			getInput();
			updateDefendHS(g_timer.getElapsedTime());
			renderDefendHS();
			g_timer.waitUntil(frameTime);

			if ( g_quitGame == true )
				break;
		}
		initialisedornot = 0;

		while ( gamestate == TMBMENU ) // TOO MANY BULLET MAIN MENU
		{

			if ( initialisedornot != 1 )
			{
				initTMBMenu();
				initialisedornot = 1;
			}

			getInput();
			updateTMBMenu(g_timer.getElapsedTime());
			renderTMBMenu();
			g_timer.waitUntil(frameTime);

			if ( g_quitGame == true )
				break;
		}
		initialisedornot = 0;
		
		while ( gamestate == TMBPLAY ) // TOO MANY BULLET GAME
		{

			if ( initialisedornot != 1 )
			{
				initTMB();
				initialisedornot = 1;
			}

			getInput();
			updateTMB(g_timer.getElapsedTime());
			renderTMB();
			g_timer.waitUntil(frameTime);

			if ( g_quitGame == true )
				break;
		}
		initialisedornot = 0;
		
		while ( gamestate == TMBINSTRUCTION1 ) // TOO MANY BULLET INSTRUCTIONS PAGE 1
		{

			if ( initialisedornot != 1 )
			{
				initTMBInstructions1();
				initialisedornot = 1;
			}

			getInput();
			updateTMBInstructions1(g_timer.getElapsedTime());
			renderTMBInstructions1();
			g_timer.waitUntil(frameTime);

			if ( g_quitGame == true )
				break;
		}
		initialisedornot = 0;
		
		while ( gamestate == TMBINSTRUCTION2 ) // TOO MANY BULLET INSTRUCIONS PAGE 2
		{

			if ( initialisedornot != 1 )
			{
				initTMBInstructions2();
				initialisedornot = 1;
			}

			getInput();
			updateTMBInstructions2(g_timer.getElapsedTime());
			renderTMBInstructions2();
			g_timer.waitUntil(frameTime);

			if ( g_quitGame == true )
				break;
		}
		initialisedornot = 0;
		
		while ( gamestate == TMBINSTRUCTION3 ) // TOO MANY BULLET INSTRUCTIONS PAGE 3
		{

			if ( initialisedornot != 1 )
			{
				initTMBInstructions3();
				initialisedornot = 1;
			}

			getInput();
			updateTMBInstructions3(g_timer.getElapsedTime());
			renderTMBInstructions3();
			g_timer.waitUntil(frameTime);

			if ( g_quitGame == true )
				break;
		}
		initialisedornot = 0;

		while ( gamestate == TMBGAMEOVER ) // TOO MANY BULLET GAMEOVER
		{

			if ( initialisedornot != 1 )
			{
				initTMBGO();
				initialisedornot = 1;
			}

			getInput();
			updateTMBGO(g_timer.getElapsedTime());
			renderTMBGO();
			g_timer.waitUntil(frameTime);

			if ( g_quitGame == true )
				break;
		}
		initialisedornot = 0;

		while ( gamestate == TMBHIGHSCORE ) // TOO MANY BULLET HIGH SCORES
		{

			if ( initialisedornot != 1 )
			{
				initTMBHS();
				initialisedornot = 1;
			}

			getInput();
			updateTMBHS(g_timer.getElapsedTime());
			renderTMBHS();
			g_timer.waitUntil(frameTime);

			if ( g_quitGame == true )
				break;
		}
		initialisedornot = 0;




	}
}
