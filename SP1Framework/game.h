#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"

extern StopWatch g_timer;
extern bool g_quitGame;
extern int gamestate;
extern int upgradePage;
extern int isFirstTimeEnter;

enum Keys
{
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
	K_H,
	K_X,
	K_Z,
    K_ESCAPE,
	K_ENTER,
	K_INSERT,
	K_SPACE,
    K_COUNT
};

enum Sequence
{
        MENU,
		GAME,
		DEFENDMENU,
		DEFENDPLAY,
		DEFENDINTRODUCTION,
		DEFENDGAMEOVER,
		DEFENDUPGRADES,
		DEFENDHIGHSCORE,
		DEFENDINSTRUCTION1,
		DEFENDINSTRUCTION2,
		DEFENDINSTRUCTION3,
		TMBPLAY,
		TMBMENU,
		TMBGAMEOVER,
		TMBHIGHSCORE,
		TMBINSTRUCTION1,
		TMBINSTRUCTION2,
		TMBINSTRUCTION3,
        INTRO,
        ENDGAME,
};

void init();                // initialize your variables, allocate memory, etc
void getInput();            // get input from player
void update(double dt);     // update the game and the state of the game
void render();              // renders the current state of the game to the console
void shutdown();            // do clean up, free memory
int loadscoresDefend();  	// load high scores for Defend!
int savescoresDefend();		// saves high scores for Defend!
//Function prototypes for menu.
void renderMenu();
void initMenu();
void updateMenu(double dt);
//Function prototypes for Defend! Menu.
void renderDefendMenu();
void initDefendMenu();
void updateDefendMenu(double dt);
//Function prototypes for the game Defend!.
void initDefend();
void renderDefend();
void updateDefend(double dt);
// Function prototypes for Defend! Upgrade Page
void initDefendUpgrade();
void renderDefendUpgrade();
void updateDefendUpgrade(double dt);
// Function prototypes for Defend! Introduction Page
void initDefendIntroduction();
void renderDefendIntroduction();
void updateDefendIntroduction(double dt);
//Function prototypes for Defend! Instructions Page 1.
void renderDefendInstructions1();
void initDefendInstructions1();
void updateDefendInstructions1(double dt);
//Function prototypes for Defend! Instructions Page 2.
void renderDefendInstructions2();
void initDefendInstructions2();
void updateDefendInstructions2(double dt);
//Function prototypes for Defend! Instructions Page 3.
void renderDefendInstructions3();
void initDefendInstructions3();
void updateDefendInstructions3(double dt);
//Function prototypes for Defend! Gameover
void renderDefendGO();
void initDefendGO();
void updateDefendGO(double dt);
void gameovernoHSDefend();
//Function prototypes for Defend! Highscore
void renderDefendHS();
void initDefendHS();
void updateDefendHS(double dt);
void updateHSDefend();
//Function prototypes for Defend (wave info and monster spawns)
void Wave1Defend();
void Wave2Defend();
void Wave3Defend();
void Wave4Defend();
void Wave5Defend();
void Wave6Defend();
void Wave7Defend();
void Wave8Defend();
void Wave9Defend();
void Wave10Defend();
void numMonsterSpawn();
void greenMonsterSpawn();
void blueMonsterSpawn();
void yellowMonsterSpawn();
void redMonsterSpawn();
void clearMonster();
//Function prototypes for Too Many Bullets Menu.
void renderTMBMenu();
void initTMBMenu();
void updateTMBMenu(double dt);
//Function prototypes for Too Many Bullets game.
void renderTMB();
void initTMB();
void updateTMB(double dt);
void flagcleared();
//Function prototypes for Too Many Bullets Instructions Page 1.
void renderTMBInstructions1();
void initTMBInstructions1();
void updateTMBInstructions1(double dt);
//Function prototypes for Too Many Bullets Instructions Page 2.
void renderTMBInstructions2();
void initTMBInstructions2();
void updateTMBInstructions2(double dt);
//Function prototypes for Too Many Bullets Instructions Page 3.
void renderTMBInstructions3();
void initTMBInstructions3();
void updateTMBInstructions3(double dt);
//Too Many Bullets render patterns
void characterTMB(int posX, int posY);
void monster1TMB(int posX, int posY);
void monster2TMB(int posX, int posY);
void monster3TMB(int posX, int posY);
void monsterBOSSTMB(int posX, int posY);
void pattern1TMB(int posX, int posY);//1rad flower
void pattern2TMB(int posX, int posY);//3rad circle
void pattern3TMB(int posX, int posY);//4rad circle
void pattern4TMB(int posX, int posY);//wave
void pattern5TMB(int posX, int posY);//pistol shot
//Function prototypes for too many bullets Gameover
void renderTMBGO();
void initTMBGO();
void updateTMBGO(double dt);
void gameovernoHSTMB();
//Function prototypes for too many bullets Highscore
void renderTMBHS();
void initTMBHS();
void updateTMBHS(double dt);
void updateHSTMB();
int savescoresTMB();
int loadscoresTMB();

#endif // _GAME_H