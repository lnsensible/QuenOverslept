// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];
COORD charLocation;
COORD consoleSize;

int gamestate;
int upgradePage;
std::string playerName = "TWY";
int typewriter = 0;
int isFirstTimeEnter = 0;

//Variables for Defend game.
int enterIntro = 0, enterGame = 0, clsUpgrade = 0, clsGame = 0, levelwarning = 0, instructionClear = 0;
int pistolMag, shotgunMag, mgunMag, pistolCap, shotgunCap, mgunCap, shotgunBought = 0, mgunBought = 0;
double pistolReload, shotgunReload, mgunReload, preloadTimer, sreloadTimer, mreloadTimer;
double bulletWait, monsterWait;
std::string ShotgunBought = "5000 Experience", MgunBought = "7500 Experience";
std::string pistolBulletUp = "200 Experience", shotgunBulletUp = "400 Experience", mgunBulletUp = "900 Experience";
std::string pistolReloadDown = "500 Experience", shotgunReloadDown = "1000 Experience", mgunReloadDown = "2000 Experience";
int gunType, level, defendhp, spawntrack, leveltrack, expDefend, zombiesAlive, zombiesLeft, totalKills;
double playerScoreDefend; // score = monsters killed - bullets missed x.1
const char bullet = (char)250;
const char monster = (char)2;
const char pBullet = (char)249;
const char sBullet = (char)229;
const char mBullet = (char)250;
std::vector<int> numBullet; //Stores coordinates of bullets [x-1, y-1, x-2, y-2...]
std::vector<int> numMonster; //Stores coordinates of monsters [x-1, y-1, x-2, y-2...]
std::vector<int> greenMonster; // ^ stores coordinates of green mobs
std::vector<int> blueMonster; // ^ stores coordinates of blue mobs + health [x-1, y-1, h-1]
std::vector<int> yellowMonster; // ^ stores coordinates of yellow mobs + health
std::vector<int> redMonster; // ^ stores coordinates of red mob + health
double greenspawn, bluespawn, yellowspawn, redspawn; //chances of mobs spawning
int Lives, LivesCheat, bombsamtDefend, bombKC; //lives system
std::string ScoreDefend1N, ScoreDefend2N, ScoreDefend3N, ScoreDefend4N, ScoreDefend5N, ScoreDefend6N, ScoreDefend7N, ScoreDefend8N, ScoreDefend9N, ScoreDefend10N;//stores name of highscore
double ScoreDefend1, ScoreDefend2, ScoreDefend3, ScoreDefend4, ScoreDefend5, ScoreDefend6, ScoreDefend7, ScoreDefend8, ScoreDefend9, ScoreDefend10;//stores value of highscore
 std::string DLine1 = "It's year 3000....";
 std::string DLine2 = "Scientists were working on a way to grant immortality.";
 std::string DLine3 = "Humans were unable to appreciate life as it was.";
 std::string DLine4 = "There was a theory written that questioned the possibility of using a";
 std::string DLine5 = "parasite called Zyombyee.";
 std::string DLine6 = "This parasite attachs itself to the host and mutates the hosts' cells to be";
 std::string DLine7 = "regenerative.";
 std::string DLine8 = "However, the parasite eventually takes over all neuroactivities.";
std::string DLine10 = "Scientists tried to modify the genes of the Zyombyee.";
std::string DLine11 = "They wanted only the regenerative power it provided.";
std::string DLine12 = "In order to continue experiments easily, they started breeding the Zyombyees.";
std::string DLine13 = "In response, the Zyombyees also adapted to reproduce more easily.";
std::string DLine14 = "As experiments continued, scientists found that the Zyombyee could reproduce";
std::string DLine15 = "simply by using its host as a proxy, to infect another host through blood.";
std::string DLine16 = "The scientists took advantage of this behavior, as it allowed for a bigger";
std::string DLine17 = "amount of Zyombyee to work with...";
std::string DLine18 = "Soon, progress was good enough that the scientists decided to start";
std::string DLine19 = "experimentation on humans.";
std::string DLine20 = "Permission granted, a selected group of scientists visited a hospital,";
std::string DLine21 = "and implanted the Zyombyee into a patient at his deathbed.";
std::string DLine22 = "Things were looking great: Within the next minute, the patient who was ";
std::string DLine23 = "dying now looked as healthy as he was before he caught his illness.";
std::string DLine24 = "Then it happened.";
std::string DLine25 = "The experimental subject clawed at the scientist beside him, drawing blood.";
std::string DLine26 = "And it continued.";
std::string DLine27 = "They were unable to lockdown the hospital to contain the spread of Zyombyees.";
std::string DLine28 = "The Zyombyee doesn't take over neuroactivity anymore.";
std::string DLine29 = "Instead, they now taint the host with their urge to reproduce (through blood).";
std::string DLine30 = "Using the strength of their host (humans), they start reproducing.";
std::string DLine31 = "And so, this was the start of the Zyombyee outbreak.";
std::string DLine32 = "The hosts could only be killed when their brains were destroyed, making them a  tough opponent...";
std::string DLine33 = "By the time the military had authority to take action, it was already too late.";
std::string DLine34 = "There were so many infected that the military couldn't destroy them all.";
std::string DLine35 = "You are one of the soldiers that the military has deployed.";
std::string DLine36 = "You managed to prevent being infected, and have set up a fort in a house";
std::string DLine37 = "which you must defend at all costs.";
std::string DLine38 = "Don't worry about ammo.";
std::string DLine39 = "Current technology allows you to shoot laser bullets.";


//Variables for TMB game.
int stagehp, level1clear, level2clear, level3clear, level4clear;
int flag1clear, flag2clear, flag3clear, flag4clear, flag5clear, flag6clear, flag7clear, flag8clear, flag9clear, flag10clear, flagtrack;
int monstermovement;
int bombsamtTMB, livesamtTMB, bossdamagedTMB, maxbosshpTMB;
double monsterShootDelay, monster2ShootDelay, monster3ShootDelay, monster4ShootDelay;
double playerScoreTMB; // score = stage x 5000 + monsterskilled x 250 - bulletsmissed x 10. Bombs -= 2500
const char bullett = '`';
const char mybullett = '.';
std::string bossHPbar = "####################";
std::vector<int> myBullets; //stores coordinates of bullets player shoot v
std::vector<int> renderBullets; //stores coordinates of bullets [x-1, y-1, x-2, y-2...]
std::vector<int> monster1; //stores coordinates and health of monster1
std::vector<int> monster2; // ^
std::vector<int> monster3; // ^
std::vector<int> monsterBOSS; // BOSS D;
std::string ScoreTMB1N, ScoreTMB2N, ScoreTMB3N, ScoreTMB4N, ScoreTMB5N, ScoreTMB6N, ScoreTMB7N, ScoreTMB8N, ScoreTMB9N, ScoreTMB10N;//stores name of highscore
double ScoreTMB1, ScoreTMB2, ScoreTMB3, ScoreTMB4, ScoreTMB5, ScoreTMB6, ScoreTMB7, ScoreTMB8, ScoreTMB9, ScoreTMB10;//stores value of highscore

//Default functions
void init()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set character location
    charLocation.X = 69;
    charLocation.Y = 13;

    elapsedTime = 0.0;
}

void render()
{
    // clear previous screen
    colour(0x0F);
    cls();

    //render the game

    //render test screen code (not efficient at all)
    const WORD colors[] =   {
	                        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
	                        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	                        };
	
	for (int i = 0; i < 255; ++i)
	{
		gotoXY(0,i);
		std::cout << (char)i << " " << i;
	}
		Sleep(99999);

    // render time taken to calculate this frame
    gotoXY(70, 0);
    colour(0x1A);
    std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
    gotoXY(0, 0);
    colour(0x59);
    std::cout << elapsedTime << "secs" << std::endl;

    // render character
    gotoXY(charLocation);
    colour(0x0C);
    std::cout << (char)1;

    
}

void update(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

    // Updating the location of the character based on the key press
    if (keyPressed[K_UP] && charLocation.Y > 0)
    {
        Beep(1440, 30);
        charLocation.Y--; 
    }
    if (keyPressed[K_LEFT] && charLocation.X > 0)
    {
        gamestate = GAME; 
    }
    if (keyPressed[K_DOWN] && charLocation.Y < consoleSize.Y - 1)
    {
        Beep(1440, 30);
        charLocation.Y++; 
    }
    if (keyPressed[K_RIGHT] && charLocation.X < consoleSize.X - 1)
    {
        Beep(1440, 30);
        charLocation.X++; 
    }

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
        g_quitGame = true;    
}

void shutdown()
{
    // Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void getInput()
{    
    keyPressed[K_UP] = isKeyPressed(VK_UP);
    keyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
    keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
    keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	keyPressed[K_H] = isKeyPressed(0x48);
	keyPressed[K_X] = isKeyPressed(0x58);
	keyPressed[K_Z] = isKeyPressed(0x5A);
    keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	keyPressed[K_ENTER] = isKeyPressed(VK_RETURN);
	keyPressed[K_INSERT] = isKeyPressed(VK_INSERT);
	keyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
}

//Menu functions
void initMenu()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set character location
    charLocation.X = 14;
    charLocation.Y = 13;

    elapsedTime = 0.0;
}

void renderMenu()
{
	// clear previous screen
	colour(0x0F);
    cls();

	// render time taken to calculate this frame
    gotoXY(70, 0);
    colour(0x1A);
    std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
    gotoXY(0, 0);
    colour(0x59);
    std::cout << elapsedTime << "secs" << std::endl;

	// render options
	colour(0x0F);

	gotoXY(15, 13);
	std::cout << "Defend!";

	gotoXY(15, 16);
	std::cout << "Quen Overslept!";

	gotoXY(15, 19);
	std::cout << "Game 7";

	gotoXY(15, 22);
	std::cout << "Game 10";

	gotoXY(35, 13);
	std::cout << "Too Many Bullets";

	gotoXY(35, 16);
	std::cout << "Game 5";

	gotoXY(35, 19);
	std::cout << "Game 8";

	gotoXY(35, 22);
	std::cout << "Game 11";

	gotoXY(55, 13);
	std::cout << "Game 3";

	gotoXY(55, 16);
	std::cout << "Game 6";

	gotoXY(55, 19);
	std::cout << "Game 9";

	gotoXY(55, 22);
	std::cout << "Game 12";

	// render ASCII title screen
	gotoXY(6, 2);
	std::cout << "  __________________    ______   _____ __________  _____________   __";

	gotoXY(6, 3);
	std::cout << " /_  __/  _/_  __/ /   / ____/  / ___// ____/ __ \\/ ____/ ____/ | / /";

	gotoXY(6, 4);
	std::cout << "  / /  / /  / / / /   / __/     \\__ \\/ /   / /_/ / __/ / __/ /  |/ / ";

	gotoXY(6, 5);
	std::cout << " / / _/ /  / / / /___/ /___    ___/ / /___/ _, _/ /___/ /___/ /|  /  ";

	gotoXY(6, 6);
	std::cout << "/_/ /___/ /_/ /_____/_____/   /____/\\____/_/ |_/_____/_____/_/ |_/   ";

	// render cursor
    gotoXY(charLocation);
    colour(0x0C);
    std::cout << (char)16;

}

void updateMenu(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

    // Updating the location of the cursor
    if (keyPressed[K_UP] && charLocation.Y != 13) // Move Up.
    {
        Beep(700, 30);
        charLocation.Y -= 3; 
    }

    if (keyPressed[K_LEFT] && charLocation.X != 14) // Move left.
    {
		Beep(700, 30);
		charLocation.X -= 20;
    }

    if (keyPressed[K_DOWN] && charLocation.Y != 22) // Move Down.
    {
		Beep(700, 30);
		charLocation.Y += 3;
    }

    if (keyPressed[K_RIGHT] && charLocation.X != 54) // Move right.
    {
		Beep(700, 30);
		charLocation.X += 20;
    }

	if (keyPressed[K_ENTER] )
	{
		Beep(100, 200);
		if ( charLocation.X == 14 && charLocation.Y == 13)
		{
			gamestate = DEFENDMENU;
		}
		if ( charLocation.X == 34 && charLocation.Y == 13)
		{
			gamestate = TMBMENU;
		}
	}

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
	{
		gotoXY(0, 1);
        g_quitGame = true;    
	}

	if (keyPressed[K_X]) //test key
	{
		gamestate = DEFENDPLAY;
	}
} //Tests here press X

//Defend functions
//Highscore functions.
void clearMonster()
{
	numMonster.clear();
	redMonster.clear();
	greenMonster.clear();
	blueMonster.clear();
	yellowMonster.clear();
}

int loadscoresDefend()
{
	std::string data;
	double data2 = 0;
	std::fstream myScores;
	std::fstream myHighs;
	myScores.open("defendScores.txt");

	getline(myScores, data);
	ScoreDefend1N = data;
	getline(myScores, data);
	ScoreDefend2N = data;
	getline(myScores, data);
	ScoreDefend3N = data;
	getline(myScores, data);
	ScoreDefend4N = data;
	getline(myScores, data);
	ScoreDefend5N = data;
	getline(myScores, data);
	ScoreDefend6N = data;
	getline(myScores, data);
	ScoreDefend7N = data;
	getline(myScores, data);
	ScoreDefend8N = data;
	getline(myScores, data);
	ScoreDefend9N = data;
	getline(myScores, data);
	ScoreDefend10N = data;
	
	myScores.close();

	myHighs.open("defendHighs.txt");

	myHighs >> data2;
	ScoreDefend1 = data2;
	myHighs >> data2;
	ScoreDefend2 = data2;
	myHighs >> data2;
	ScoreDefend3 = data2;
	myHighs >> data2;
	ScoreDefend4 = data2;
	myHighs >> data2;
	ScoreDefend5 = data2;
	myHighs >> data2;
	ScoreDefend6 = data2;
	myHighs >> data2;
	ScoreDefend7 = data2;
	myHighs >> data2;
	ScoreDefend8 = data2;
	myHighs >> data2;
	ScoreDefend9 = data2;
	myHighs >> data2;
	ScoreDefend10 = data2;

	myHighs.close();
	return 0;
}

int savescoresDefend()
{
	std::string data;
	double data2 = 0;
	std::fstream myScores;
	myScores.open("defendScores.txt");

	myScores << ScoreDefend1N << std::endl;
	myScores << ScoreDefend2N << std::endl;
	myScores << ScoreDefend3N << std::endl;
	myScores << ScoreDefend4N << std::endl;
	myScores << ScoreDefend5N << std::endl;
	myScores << ScoreDefend6N << std::endl;
	myScores << ScoreDefend7N << std::endl;
	myScores << ScoreDefend8N << std::endl;
	myScores << ScoreDefend9N << std::endl;
	myScores << ScoreDefend10N;

	myScores.close();

	std::fstream myHighs;
	myHighs.open("defendHighs.txt");

	myHighs << ScoreDefend1 << std::endl;
	myHighs << ScoreDefend2 << std::endl;
	myHighs << ScoreDefend3 << std::endl;
	myHighs << ScoreDefend4 << std::endl;
	myHighs << ScoreDefend5 << std::endl;
	myHighs << ScoreDefend6 << std::endl;
	myHighs << ScoreDefend7 << std::endl;
	myHighs << ScoreDefend8 << std::endl;
	myHighs << ScoreDefend9 << std::endl;
	myHighs << ScoreDefend10;

	myHighs.close();
	return 0;
}

void initDefend()
{

	loadscoresDefend();

    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set character location
    charLocation.X = 69;
    charLocation.Y = 7;

    elapsedTime = 0.0;
	bulletWait = 0.0;
	monsterWait = 0.0;
	preloadTimer = 0.0;
	sreloadTimer = 0.0;
	mreloadTimer = 0.0;

	gunType = 0;
	playerScoreDefend = 0;
	enterGame = 0;
	leveltrack = 1;
	clsGame = 0;
	clsUpgrade = 0;

	level = 1;
	Lives = 3;
	LivesCheat = 0;
	bombsamtDefend = 3;
	defendhp = 0;
	spawntrack = 0;
	expDefend = 0;
	totalKills = 0;

	pistolReload = 2.5;
	pistolMag = 6;
	shotgunReload = 3.0;
	shotgunMag = 2;
	mgunReload = 7.0;
	mgunMag = 20;
	pistolCap = 6;
	shotgunCap = 2;
	mgunCap = 20;

	numBullet.clear();
	numMonster.clear();
	greenMonster.clear();
	blueMonster.clear();
	yellowMonster.clear();
	redMonster.clear();
}

void renderDefend()
{
	// clear previous screen
    colour(0x0F);
	if ( clsGame == 0 )
	{
		cls();
		clsGame = 1;
		//static renders
	
		//Render the border
		gotoXY(0, 16);
		std::cout << char(201);
		gotoXY(1, 16);
		for (int i = 0; i < 78; i++)
			std::cout << char(205);
		gotoXY(79, 16);
		std::cout << char(187);
		for (int i = 17; i < 24; i++)
		{
			gotoXY(0, i);
			std::cout << char(186);
		}
		for (int i = 17; i < 24; i++)
		{
			gotoXY(79, i);
			std::cout << char(186);
		}
		gotoXY(0, 24);
		std::cout << char(200);
		gotoXY(1, 24);
		for (int i = 0; i < 78; i++)
			std::cout << char(205);
		gotoXY(79, 24);
		std::cout << char(188);
		//render gun border
		gotoXY(1, 17);
		std::cout << char(218);
		for (int i = 18; i < 23; i++)
		{
			gotoXY(1, i);
			std::cout << char(179);
		}
		gotoXY(1, 23);
		std::cout << char(192);
		for (int i = 18; i < 23; i++)
		{
			gotoXY(20, i);
			std::cout << char(179);
		}
		gotoXY(20, 17);
		std::cout << char(191);
		gotoXY(20, 23);
		std::cout << char(217);



		gotoXY(21, 17);
		std::cout << "Weapon Selected:";

		gotoXY(68, 1);
		std::cout << char(178) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178);
		gotoXY(68, 2);
		std::cout << char(178) << char(178) << char(178) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177);
		gotoXY(68, 13);
		std::cout << char(178) << char(178) << char(178) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177);
		gotoXY(68, 14);
		std::cout << char(178) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178) << char(178);
	}
	else
	{
		ClearRows(0, 1); //clear only play area
		ClearRows(3, 13);
	}
	//render barricade wall. don't ask why i'm not using a for loop
	gotoXY(68, 3);
	std::cout << char(178);
	gotoXY(68, 4);
	std::cout << char(178);
	gotoXY(68, 5);
	std::cout << char(178);
	gotoXY(68, 6);
	std::cout << char(178);
	gotoXY(68, 7);
	std::cout << char(178);
	gotoXY(68, 8);
	std::cout << char(178);
	gotoXY(68, 9);
	std::cout << char(178);
	gotoXY(68, 10);
	std::cout << char(178);
	gotoXY(68, 11);
	std::cout << char(178);
	gotoXY(68, 12);
	std::cout << char(178);

	//render bullet count @ top
	gotoXY(5, 0);
	std::cout << "Bullets: ";
	gotoXY(15, 0);
	if ( gunType == 0 )
	{
			for (int i = 0; i < pistolMag; i++)
				std::cout << pBullet;
	}
	else if ( gunType == 1 )
	{
		for (int i = 0; i < shotgunMag; i++)
			std::cout << sBullet;
	}
	else if ( gunType == 2 )
	{
		for (int i = 0; i < mgunMag; i++)
			std::cout << mBullet;
	}
	//if reloading, show reload timer. ^^
	if ( gunType == 0 && pistolMag == 0 )
	{
		gotoXY(63, 0);
		std::cout << "Reloading: " << pistolReload - preloadTimer;
	}
	else if ( gunType == 1 && shotgunMag == 0 )
	{
		gotoXY(63, 0);

		std::cout << "Reloading: " << shotgunReload - sreloadTimer;
	}
	else if ( gunType == 2 && mgunMag == 0 )
	{
		gotoXY(63, 0);
		std::cout << "Reloading: " << mgunReload - mreloadTimer;
	}
		
	
	colour(0x0F);
	//Check and render bullets
	for ( unsigned int i = 0; i + 1 < numBullet.size(); i += 2 )
	{
		gotoXY( numBullet[i], numBullet[i+1] );
		std::cout << bullet; // Spawn bullets.

		if ( numBullet[i] > 0 ) // If bullet doesn't reach end of screen, 
			--numBullet[i]; // decrease X coordinate of bullet.
		else // GG MISSED
		{
			playerScoreDefend -= 0.01;
			numBullet.erase (numBullet.begin()); // Cleanup
			numBullet.erase (numBullet.begin()); // Cleanup
		}
	}

	// Check and render white monsters
	for ( unsigned int i = 0; i + 1 < numMonster.size(); i += 2 )
	{
		gotoXY( numMonster[i], numMonster[i+1] );
		std::cout << monster; // Spawn monsters.

		if ( numMonster[i] == 68 ) // If monster reaches barricade
		{
			if ( Lives > 0 ) // lose a life.
			{
				numMonster.erase (numMonster.begin() + i);
				numMonster.erase (numMonster.begin() + i);
				Beep(1337, 100);
				--Lives;
			}
			else // Game over.
			{
				if ( LivesCheat == 1 ) // You used coins!!! D:
				{
					gameovernoHSDefend();//show score and ask user to return
				}
				else
				{
					if ( playerScoreDefend > ScoreDefend10 ) //check if is in top 10, if yes ask user to input name.
						updateHSDefend();
					else
						gameovernoHSDefend(); //if not, show score and ask user to return
				}
			}
		}
		else
		{
			++numMonster[i]; // increase X coordinate of monster.
		}
	}

	// Check and render green monsters
	for ( unsigned int i = 0; i + 1 < greenMonster.size(); i += 2 )
	{
		gotoXY( greenMonster[i], greenMonster[i+1] );
		colour(0x02);
		std::cout << monster; // Spawn monsters.
		colour(0x0F);
		if ( greenMonster[i] == 68 ) // If monster reaches barricade
		{
			if ( Lives > 0 ) // lose a life.
			{
				greenMonster.erase (greenMonster.begin() + i);
				greenMonster.erase (greenMonster.begin() + i);
				Beep(1337, 100);
				--Lives;
			}
			else // Game over.
			{
				if ( LivesCheat == 1 ) // You used coins!!! D:
				{
					gameovernoHSDefend();//show score and ask user to return
				}
				else
				{
					if ( playerScoreDefend > ScoreDefend10 ) //check if is in top 10, if yes ask user to input name.
						updateHSDefend();
					else
					gameovernoHSDefend();//if not, show score and ask user to return
				}
			}
		}
		else
		{
			++greenMonster[i]; // increase X coordinate of monster.
			++greenMonster[i];
		}
	}

	
	// Check and render blue monsters
	for ( unsigned int i = 0; i + 2 < blueMonster.size(); i += 3 )
	{
		gotoXY( blueMonster[i], blueMonster[i+1] );
		colour(0x01);
		std::cout << monster; // Spawn monsters.
		colour(0x0F);
		if ( blueMonster[i] == 68 ) // If monster reaches barricade
		{
			if ( Lives > 0 ) // lose a life.
			{
				blueMonster.erase (blueMonster.begin() + i);
				blueMonster.erase (blueMonster.begin() + i);
				blueMonster.erase (blueMonster.begin() + i);
				Beep(1337, 100);
				--Lives;
			}
			else // Game over.
			{
				if ( LivesCheat == 1 ) // You used coins!!! D:
				{
					gameovernoHSDefend();//show score and ask user to return
				}
				else
				{
					if ( playerScoreDefend > ScoreDefend10 ) //check if is in top 10, if yes ask user to input name.
						updateHSDefend();
					else
					gameovernoHSDefend();//if not, show score and ask user to return
				}
			}
		}
		else
		{
			++blueMonster[i]; // increase X coordinate of monster.
		}
	}
	
	// Check and render yellow monsters
	for ( unsigned int i = 0; i + 2 < yellowMonster.size(); i += 3 )
	{
		gotoXY( yellowMonster[i]-5, yellowMonster[i+1] );
		colour(0x0E);
		std::cout << ",___/="; // Spawn monsters.
		gotoXY( yellowMonster[i]-5, yellowMonster[i+i]+1 );
		std::cout << "'! !  ";
		colour(0x0F);
		if ( yellowMonster[i] == 68 ) // If monster reaches barricade
		{
			if ( Lives > 0 ) // lose a life.
			{
				yellowMonster.erase (yellowMonster.begin() + i);
				yellowMonster.erase (yellowMonster.begin() + i);
				yellowMonster.erase (yellowMonster.begin() + i);
				Beep(1337, 100);
				--Lives;
			}
			else // Game over.
			{
				if ( LivesCheat == 1 ) // You used coins!!! D:
				{
					gameovernoHSDefend();//show score and ask user to return
				}
				else
				{
					if ( playerScoreDefend > ScoreDefend10 ) //check if is in top 10, if yes ask user to input name.
						updateHSDefend();
					else
					gameovernoHSDefend();//if not, show score and ask user to return
				}
			}
		}
		else
		{
			++yellowMonster[i]; // increase X coordinate of monster.
			++yellowMonster[i];
		}
	}
	
	// Check and render red monsters
	for ( unsigned int i = 0; i + 2 < redMonster.size(); i += 3 )
	{
		gotoXY( redMonster[i], redMonster[i+1] );
		colour(0x04);
		std::cout << monster; // Spawn monsters.
		colour(0x0F);
		if ( redMonster[i] == 68 ) // If monster reaches barricade
		{
			if ( Lives > 0 ) // lose a life.
			{
				redMonster.erase (redMonster.begin() + i);
				redMonster.erase (redMonster.begin() + i);
				redMonster.erase (redMonster.begin() + i);
				Beep(1337, 100);
				--Lives;
			}
			else // Game over.
			{
				if ( LivesCheat == 1 ) // You used coins!!! D:
				{
					gameovernoHSDefend();
				}
				else
				{
					if ( playerScoreDefend > ScoreDefend10 ) //check if is in top 10, if yes ask user to input name.
						updateHSDefend();
					else
					gameovernoHSDefend();//if not, show score and ask user to return
				}
			}
		}
		else
		{
			++redMonster[i]; // increase X coordinate of monster.
		}
	}

	// Check for white monster hit
	for ( unsigned int i = 0; i + 1 < numBullet.size(); i += 2 )
	{
		for ( unsigned int j = 0; j + 1 < numMonster.size() && i + 1 < numBullet.size(); j += 2 ) // Check if bullet hits a monster
		{
			if ( (( numBullet[i] == numMonster[j] ) && ( numBullet[i+1] == numMonster[j+1] )) || (( numBullet[i]+1 == numMonster[j] ) && ( numBullet[i+1] == numMonster[j+1] )) ) // Hit!
			{
				++bombKC;
				expDefend += 30;
				// Remove bullet that hit
				numBullet.erase (numBullet.begin() + i); 
				numBullet.erase (numBullet.begin() + i); 
				//Remove monster that died
				numMonster.erase (numMonster.begin() + j);
				numMonster.erase (numMonster.begin() + j); 
				playerScoreDefend++; //+1 to score!
				--zombiesLeft;
				++totalKills;
				//Reset loop
				i = 0;
				j = 0;
			}
		}
	}

	// Check for green monster hit
	for ( unsigned int i = 0; i + 1 < numBullet.size(); i += 2 )
	{
		for ( unsigned int j = 0; j + 1 < greenMonster.size(); j += 2 ) // Check if bullet hits a monster
		{
			if ( (( numBullet[i] == greenMonster[j] ) && ( numBullet[i+1] == greenMonster[j+1] )) || (( numBullet[i]+1 == greenMonster[j] ) && ( numBullet[i+1] == greenMonster[j+1] )) || (( numBullet[i]+2 == greenMonster[j] ) && ( numBullet[i+1] == greenMonster[j+1] )) ) // Hit!
			{
				++bombKC;
				expDefend += 50;
				// Remove bullet that hit
				numBullet.erase (numBullet.begin() + i); 
				numBullet.erase (numBullet.begin() + i); 
				//Remove monster that died
				greenMonster.erase (greenMonster.begin() + j);
				greenMonster.erase (greenMonster.begin() + j); 
				playerScoreDefend+=3; //+3 to score!
				--zombiesLeft;
				++totalKills;
				//Reset loop
				i = 0;
				j = 0;
			}
		}
	}

	// Check for blue monster hit
	for ( unsigned int i = 0; i + 1 < numBullet.size(); i += 2 )
	{
		for ( unsigned int j = 0; j + 2 < blueMonster.size(); j += 3 ) // Check if bullet hits a monster
		{
			if ( (( numBullet[i] == blueMonster[j] ) && ( numBullet[i+1] == blueMonster[j+1] )) || (( numBullet[i]+1 == blueMonster[j] ) && ( numBullet[i+1] == blueMonster[j+1] )) ) // Hit!
			{
				++bombKC;
				expDefend += 50;
				// Remove bullet that hit
				numBullet.erase (numBullet.begin() + i); 
				numBullet.erase (numBullet.begin() + i); 
				// Decrease monster health/kill monster
				if ( blueMonster[j+2] > 1 )
				{
					--blueMonster[j+2];
				}
				else
				{
				//Remove monster that died
				blueMonster.erase (blueMonster.begin() + j);
				blueMonster.erase (blueMonster.begin() + j); 
				blueMonster.erase (blueMonster.begin() + j);
				playerScoreDefend+=3; //+3 to score!
				--zombiesLeft;
				++totalKills;
				}
				//Reset loop
				i = 0;
				j = 0;
			}
		}
	}

	// Check for yellow monster hit
	for ( unsigned int i = 0; i + 1 < numBullet.size(); i += 2 )
	{
		for ( unsigned int j = 0; j + 2 < yellowMonster.size(); j += 3 ) // Check if bullet hits a monster
		{
			if ( (( numBullet[i] == yellowMonster[j] ) && ( numBullet[i+1] == yellowMonster[j+1] )) || (( numBullet[i]+1 == yellowMonster[j] ) && ( numBullet[i+1] == yellowMonster[j+1] )) || (( numBullet[i]+2 == yellowMonster[j] ) && ( numBullet[i+1] == yellowMonster[j+1] ))  || (( numBullet[i]+2 == yellowMonster[j]-2 ) && ( numBullet[i+1] == yellowMonster[j+1]+1 ))  || (( numBullet[i]+1 == yellowMonster[j]-2 ) && ( numBullet[i+1] == yellowMonster[j+1]+1 )) ) // Hit!
			{
				++bombKC;
				expDefend += 75;
				// Remove bullet that hit
				numBullet.erase (numBullet.begin() + i); 
				numBullet.erase (numBullet.begin() + i); 
				// Decrease monster health/kill monster
				if ( yellowMonster[j+2] > 0 )
				{
					--yellowMonster[j+2];
				}
				else
				{
				//Remove monster that died
				yellowMonster.erase (yellowMonster.begin() + j);
				yellowMonster.erase (yellowMonster.begin() + j); 
				yellowMonster.erase (yellowMonster.begin() + j); 
				playerScoreDefend+=5; //+3 to score!
				--zombiesLeft;
				++totalKills;
				}
				//Reset loop
				i = 0;
				j = 0;
			}
		}
	}

	// Check for red monster hit
	for ( unsigned int i = 0; i + 1 < numBullet.size(); i += 2 )
	{
		for ( unsigned int j = 0; j + 2 < redMonster.size(); j += 3 ) // Check if bullet hits a monster
		{
			if ( (( numBullet[i] == redMonster[j] ) && ( numBullet[i+1] == redMonster[j+1] )) || (( numBullet[i]+1 == redMonster[j] ) && ( numBullet[i+1] == redMonster[j+1] )) ) // Hit!
			{
				++bombKC;
				expDefend += 135;
				// Remove bullet that hit
				numBullet.erase (numBullet.begin() + i); 
				numBullet.erase (numBullet.begin() + i);
				// Decrease monster health/kill monster
				if ( redMonster[j+2] > 0 )
				{
					--redMonster[j+2];
				}
				else
				{
				//Remove monster that died
				redMonster.erase (redMonster.begin() + j);
				redMonster.erase (redMonster.begin() + j); 
				redMonster.erase (redMonster.begin() + j); 
				playerScoreDefend+=10; //+3 to score!
				--zombiesLeft;
				++totalKills;
				}
				//Reset loop
				
				i = 0;
				j = 0;
			}
		}
	}


	//UI
	//Gun type
	gotoXY(21, 18);
	if ( gunType == 0 )
	{
		std::cout << "Pistol";
		gotoXY(6, 18);
		std::cout << "  _______.";
		gotoXY(6, 19);
		std::cout << "~(_]-----'";
		gotoXY(6, 20);
		std::cout << "/_(";
	}
	else if ( gunType == 1 )
	{
		std::cout << "Shotgun";
		gotoXY(3, 18);
		std::cout << "   ,________,__";
		gotoXY(3, 19);
		std::cout << "  / __.---===--'";
		gotoXY(3, 20);
		std::cout << " /#(-'";
		gotoXY(3, 21);
		std::cout << " `''";
	}
	else if ( gunType == 2 )
	{
		std::cout << "Machine Gun";
		gotoXY(3, 18);
		std::cout << "\\__-)==/______,_";
		gotoXY(3, 19);
		std::cout << " / .-^-||`'    ";
		gotoXY(3, 20);
		std::cout << "/_/    ||      ";
	}
	else
		std::cout << "CHEATER!";

    // render character
    gotoXY(charLocation);
    colour(0x0C);
    std::cout << (char)1;

	//Bombs, Lives, Score, Level, EXP, bullets left.
    colour(0x0F);
	gotoXY(21, 20);
	std::cout << "Bombs: " << bombsamtDefend;
	gotoXY(21, 21);
	std::cout << "Barricade HP: " << Lives;
	gotoXY(21, 22);
	std::cout << "Experience: " << expDefend;
	gotoXY(21, 23);
    std::cout << "Score: " << playerScoreDefend;
	gotoXY(60, 17);
	std::cout << "Night " << leveltrack;
	gotoXY(60, 18);
	std::cout << "Zombies: " << zombiesAlive;
	gotoXY(60, 19);
	std::cout << "Zombies Left: " << zombiesLeft;
	if (zombiesLeft < 10 ) //since we're not clearing screen... manually fix it
	{
		gotoXY(75, 19);
		std::cout << " ";
	}
	gotoXY(60, 20);
	std::cout << "Total Kills: " << totalKills;

	// render time taken to calculate this frame
    gotoXY(60, 22);
    std::cout << 1.0 / deltaTime << " fps";
	gotoXY(69, 22);
	std::cout << "      ";
    gotoXY(60, 23);
    std::cout << elapsedTime << " sec";

	//force gameover if not
	if ( Lives <= 0 )
	{
		if ( playerScoreDefend > ScoreDefend10 && LivesCheat == 0)
			updateHSDefend();
		else
			gameovernoHSDefend();
	}

}

void updateDefend(double dt)
{
	isFirstTimeEnter = 1;
    // get the delta time
    elapsedTime += dt;
	bulletWait += dt;
	monsterWait += dt;
    deltaTime = dt;
	zombiesAlive = ( numMonster.size()/2 + greenMonster.size()/2 + blueMonster.size()/3 + redMonster.size()/3 + yellowMonster.size()/3 );
	// Update level
	if ( pistolMag == 0 && gunType == 0 ) // Delay for reload.
	{
		preloadTimer += dt;
		if ( preloadTimer >= pistolReload )
		{
			pistolMag = pistolCap;
			preloadTimer = 0;
		}
	}
	if ( shotgunMag == 0 && gunType == 1 )
	{
		sreloadTimer += dt;
		if ( sreloadTimer >= shotgunReload )
		{
			shotgunMag = shotgunCap;
			sreloadTimer = 0;
		}
	}
	if ( mgunMag == 0 && gunType == 2 )
	{
		mreloadTimer += dt;
		if ( mreloadTimer >= mgunReload )
		{
			mgunMag = mgunCap;
			mreloadTimer = 0;
		}
	}
	//bomb based on kills
	if ( bombKC > 50 )
	{
		bombKC = 0;
		bombsamtDefend +=1;
	}

	if ( leveltrack == 1 )
	{
		//welcome player
		if ( levelwarning == 0 )
		{
			gotoXY(20, 4);	std::cout << (char)218;
			gotoXY(50, 4);	std::cout << (char)191;
			gotoXY(20, 9);	std::cout << (char)192;
			gotoXY(50, 9);	std::cout << (char)217;
			gotoXY(21, 4);  std::cout << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196;
			gotoXY(21, 9);  std::cout << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196;
			gotoXY(20, 5);  std::cout << (char)179;
			gotoXY(20, 6);  std::cout << (char)179;
			gotoXY(20, 7);  std::cout << (char)179;
			gotoXY(20, 8);  std::cout << (char)179;
			gotoXY(50, 5);  std::cout << (char)179;
			gotoXY(50, 6);  std::cout << (char)179;
			gotoXY(50, 7);  std::cout << (char)179;
			gotoXY(50, 8);  std::cout << (char)179;
			gotoXY(21, 5);
			colour(0x04);
			std::cout << "Zombies can smell you out and";
			gotoXY(21, 6);
			std::cout << "are heading for you...";
			colour(0x0F);
			gotoXY(21, 8);
			std::cout << "Are you ready for them..?";
			Sleep(5000);
			levelwarning = 1;
		}
		if ( monsterWait > 2.0 )
		{
			Wave1Defend();
			monsterWait = 0;
		}
		if ( spawntrack == 21 && zombiesAlive == 0 ) //after all zombies finished spawning and dead.
		{
			numBullet.clear();
			clearMonster();
			spawntrack = 0; //reset spawn tracker
			Lives++;
			Beep(329,200); Beep(493,200); Beep(698,200); Beep(659,600); Beep(392,250); Beep(440,200);
			leveltrack++;
			gamestate = DEFENDUPGRADES; // go to upgrade screen
		}
	}

	if ( leveltrack == 2 )
	{
		if ( monsterWait > 2.0 )
		{
			Wave2Defend();
			monsterWait = 0;
		}
		if ( spawntrack == 26 && zombiesAlive == 0 ) //after all zombies finished spawning and dead.
		{
			spawntrack = 0; //reset spawn tracker
			Lives++;
			Beep(329,200); Beep(493,200); Beep(698,200); Beep(659,600); Beep(392,250); Beep(440,200);
			leveltrack++;
			clsUpgrade = 0;
			gamestate = DEFENDUPGRADES; // go to upgrade screen
		}
	}

	if ( leveltrack == 3 )
	{
		if ( monsterWait > 2.0 )
		{
			Wave3Defend();
			monsterWait = 0;
		}
		if ( spawntrack == 36 && zombiesAlive == 0 ) //after all zombies finished spawning and dead.
		{
			spawntrack = 0; //reset spawn tracker
			Lives++;
			Beep(329,200); Beep(493,200); Beep(698,200); Beep(659,600); Beep(392,250); Beep(440,200);
			leveltrack++;
			clsUpgrade = 0;
			gamestate = DEFENDUPGRADES; // go to upgrade screen
		}
	}

	if ( leveltrack == 4 )
	{
		if ( monsterWait > 2.0 )
		{
			Wave4Defend();
			monsterWait = 0;
		}
		if ( spawntrack == 41 && zombiesAlive == 0 ) //after all zombies finished spawning and dead.
		{
			spawntrack = 0; //reset spawn tracker
			Lives++;
			Beep(329,200); Beep(493,200); Beep(698,200); Beep(659,600); Beep(392,250); Beep(440,200);
			leveltrack++;
			clsUpgrade = 0;
			gamestate = DEFENDUPGRADES; // go to upgrade screen
		}
	}

	if ( leveltrack == 5 )
	{
		if ( monsterWait > 2.0 )
		{
			Wave5Defend();
			monsterWait = 0;
		}
		if ( spawntrack == 51 && zombiesAlive == 0 ) //after all zombies finished spawning and dead.
		{
			spawntrack = 0; //reset spawn tracker
			Lives++;
			Beep(329,200); Beep(493,200); Beep(698,200); Beep(659,600); Beep(392,250); Beep(440,200);
			leveltrack++;
			clsUpgrade = 0;
			gamestate = DEFENDUPGRADES; // go to upgrade screen
		}
	}

	if ( leveltrack == 6 )
	{
		//warn player that its gonna be hell (;
		if ( levelwarning == 0 )
		{
			gotoXY(20, 4);	std::cout << (char)218;
			gotoXY(50, 4);	std::cout << (char)191;
			gotoXY(20, 9);	std::cout << (char)192;
			gotoXY(50, 9);	std::cout << (char)217;
			gotoXY(21, 4);  std::cout << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196;
			gotoXY(21, 9);  std::cout << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196;
			gotoXY(20, 5);  std::cout << (char)179;
			gotoXY(20, 6);  std::cout << (char)179;
			gotoXY(20, 7);  std::cout << (char)179;
			gotoXY(20, 8);  std::cout << (char)179;
			gotoXY(50, 5);  std::cout << (char)179;
			gotoXY(50, 6);  std::cout << (char)179;
			gotoXY(50, 7);  std::cout << (char)179;
			gotoXY(50, 8);  std::cout << (char)179;
			gotoXY(21, 5);
			colour(0x04);
			std::cout << "Looks like tonight's going to";
			gotoXY(21, 6);
			std::cout << "be dangerous...";
			colour(0x0F);
			gotoXY(21, 8);
			std::cout << "Are you prepared...?";
			Sleep(5000);
			levelwarning = 1;
		}
		if ( monsterWait > 1.5 )
		{
			Wave6Defend();
			monsterWait = 0;
		}
		if ( spawntrack == 41 && zombiesAlive == 0 ) //after all zombies finished spawning and dead.
		{
			spawntrack = 0; //reset spawn tracker
			Lives++;
			Beep(329,200); Beep(493,200); Beep(698,200); Beep(659,600); Beep(392,250); Beep(440,200);
			leveltrack++;
			clsUpgrade = 0;
			gamestate = DEFENDUPGRADES; // go to upgrade screen
		}
	}

	if ( leveltrack == 7 )
	{
		if ( monsterWait > 1.5 )
		{
			Wave7Defend();
			monsterWait = 0;
		}
		if ( spawntrack == 51 && zombiesAlive == 0 ) //after all zombies finished spawning and dead.
		{
			spawntrack = 0; //reset spawn tracker
			Lives++;
			Beep(329,200); Beep(493,200); Beep(698,200); Beep(659,600); Beep(392,250); Beep(440,200);
			leveltrack++;
			clsUpgrade = 0;
			gamestate = DEFENDUPGRADES; // go to upgrade screen
		}
	}

	if ( leveltrack == 8 )
	{
		if ( monsterWait > 1.5 )
		{
			Wave8Defend();
			monsterWait = 0;
		}
		if ( spawntrack == 71 && zombiesAlive == 0 ) //after all zombies finished spawning and dead.
		{
			spawntrack = 0; //reset spawn tracker
			Lives++;
			Beep(329,200); Beep(493,200); Beep(698,200); Beep(659,600); Beep(392,250); Beep(440,200);
			leveltrack++;
			clsUpgrade = 0;
			gamestate = DEFENDUPGRADES; // go to upgrade screen
		}
	}

	if ( leveltrack == 9 )
	{
		if ( monsterWait > 1.0 )
		{
			Wave9Defend();
			monsterWait = 0;
		}
		if ( spawntrack == 66 && zombiesAlive == 0 ) //after all zombies finished spawning and dead.
		{
			spawntrack = 0; //reset spawn tracker
			Lives++;
			Beep(329,200); Beep(493,200); Beep(698,200); Beep(659,600); Beep(392,250); Beep(440,200);
			leveltrack++;
			clsUpgrade = 0;
			gamestate = DEFENDUPGRADES; // go to upgrade screen
		}
	}

	if ( leveltrack == 10 )
	{
		if ( monsterWait > 1.0 )
		{
			Wave10Defend();
			monsterWait = 0;
		}
		if ( spawntrack == 71 && zombiesAlive == 0 ) //after all zombies finished spawning and dead.
		{
			spawntrack = 0; //reset spawn tracker
			Lives++;
			Beep(329,200); Beep(493,200); Beep(698,200); Beep(659,600); Beep(392,250); Beep(440,200);
			leveltrack++;
			clsUpgrade = 0;
			gamestate = DEFENDUPGRADES; // go to upgrade screen
		}
	}
	
	/* // Old spawn monster code
	if ( monsterWait > 2.0 )
	{
		if ( level/3 >= 1 ) //above level 3
		{
			greenspawn = rand()%10 + level/8;
			if ( greenspawn >= 4 ) //level 1 mob pass
			{
				bluespawn = rand()%4 + level/8; 
				if ( bluespawn == 0 ) // level 2 mob fail. spawn green. 
				{
					greenMonster.push_back(0);
					greenMonster.push_back(rand() % 10 + 3);

					if ( level < 10 )
						monsterWait = (0.1 * level);
					else if ( level > 9 )
						monsterWait = 1.1;
					else if ( level > 20 )
						monsterWait = 1.6;
					else if ( level > 30 )
						monsterWait = 1.8;
				}
				else if ( bluespawn == 1 )// level 2 mob pass. spawn blue.
				{
					blueMonster.push_back(0);
					blueMonster.push_back(rand() % 10 + 3);
					blueMonster.push_back(2);

					if ( level < 10 )
						monsterWait = (0.1 * level);
					else if ( level > 10 )
						monsterWait = 1.1;
					else if ( level > 20 )
						monsterWait = 1.6;
					else if ( level > 30 )
						monsterWait = 1.8;
				}
				else
				{
					if ( level/6 >= 1 ) //above level 6
					{
						yellowspawn = rand()%10 + level/8;
						if ( yellowspawn >= 4 ) //level 3 mob pass.
						{
							if ( level/9 >= 1 ) //above level 9
							{
								redspawn = rand()%10 + level/8;
								if ( redspawn >= 4 ) //level 4 mob pass.
								{
									redMonster.push_back(0);
									redMonster.push_back(rand() % 10 + 3);
									redMonster.push_back(4);

									if ( level < 10 )
										monsterWait = (0.1 * level);
									else if ( level > 9 )
										monsterWait = 1.1;
									else if ( level > 20 )
										monsterWait = 1.6;
									else if ( level > 30 )
										monsterWait = 1.8;
								}
								else //level 4 mob fail. spawn yellow
								{
									yellowMonster.push_back(0);
									yellowMonster.push_back(rand() % 10 + 3);
									yellowMonster.push_back(2);

									if ( level < 10 )
										monsterWait = (0.1 * level);
									else if ( level > 9 )
										monsterWait = 1.1;
									else if ( level > 20 )
										monsterWait = 1.6;
									else if ( level > 30 )
										monsterWait = 1.8;
								}
							}
						}
						else
						{
							numMonster.push_back(0);
							numMonster.push_back(rand() % 10 + 3);

							if ( level < 10 )
								monsterWait = (0.1 * level);
							else if ( level > 9 )
								monsterWait = 1.1;
							else if ( level > 20 )
								monsterWait = 1.6;
							else if ( level > 30 )
								monsterWait = 1.8;
						}
					}
				}
			}
			else
			{
				numMonster.push_back(0);
				numMonster.push_back(rand() % 10 + 3);

				if ( level < 10 )
					monsterWait = (0.1 * level);
				else if ( level > 9 )
					monsterWait = 1.1;
				else if ( level > 20 )
					monsterWait = 1.6;
				else if ( level > 30 )
					monsterWait = 1.8;
			}
		
			if ( level < 10 )
				monsterWait = (0.1 * level);
			else if ( level > 9 )
				monsterWait = 1.1;
			else if ( level > 20 )
				monsterWait = 1.6;
			else if ( level > 30 )
				monsterWait = 1.8;
		}
		else
		{
			numMonster.push_back(0);
			numMonster.push_back(rand() % 10 + 3);

			if ( level < 10 )
				monsterWait = (0.1 * level);
			else if ( level > 9 )
				monsterWait = 1.1;
			else if ( level > 20 )
				monsterWait = 1.6;
			else if ( level > 30 )
				monsterWait = 1.8;
			
		}
	}*/



	
    // Updating the location of the character based on the key press
	// Character cannot move left and right, only up and down.
    if (keyPressed[K_UP] && charLocation.Y > 3) // Move Up.
    {
        Beep(700, 30);
        charLocation.Y--; 
    }

    if (keyPressed[K_LEFT] && charLocation.X > 0) //Shoot
    {
		if ( gunType == 0 ) // Pistol.
		{
			if ( pistolMag > 0 && bulletWait >= 0.4)
			{
				Beep(1479, 30);
				numBullet.push_back(charLocation.X-2);
				numBullet.push_back(charLocation.Y);
				--pistolMag;
				bulletWait = 0;
			}
			else 
			{
				if ( preloadTimer >= pistolReload )
				{
					pistolMag = pistolCap;
					preloadTimer = 0;
				}
			}
		}
		else if ( gunType == 1 ) // Shotgun
		{
			if ( shotgunMag > 0 && bulletWait >= 0.8)
			{
				Beep(800, 30);
				Beep(3000, 30);
				if ( charLocation.Y == 3)
				{
					numBullet.push_back(charLocation.X-3);
					numBullet.push_back(charLocation.Y);
					numBullet.push_back(charLocation.X-2);
					numBullet.push_back(charLocation.Y);
					numBullet.push_back(charLocation.X-1);
					numBullet.push_back(charLocation.Y);
					numBullet.push_back(charLocation.X-3);
					numBullet.push_back(charLocation.Y+1);
					numBullet.push_back(charLocation.X-2);
					numBullet.push_back(charLocation.Y+1);
					numBullet.push_back(charLocation.X-1);
					numBullet.push_back(charLocation.Y+1);
					--shotgunMag;
				}
				else if ( charLocation.Y == 12)
				{
					numBullet.push_back(charLocation.X-3);
					numBullet.push_back(charLocation.Y);
					numBullet.push_back(charLocation.X-2);
					numBullet.push_back(charLocation.Y);
					numBullet.push_back(charLocation.X-1);
					numBullet.push_back(charLocation.Y);
					numBullet.push_back(charLocation.X-3);
					numBullet.push_back(charLocation.Y-1);
					numBullet.push_back(charLocation.X-2);
					numBullet.push_back(charLocation.Y-1);
					numBullet.push_back(charLocation.X-1);
					numBullet.push_back(charLocation.Y-1);
					--shotgunMag;
				}
				else
				{
					numBullet.push_back(charLocation.X-3);
					numBullet.push_back(charLocation.Y);
					numBullet.push_back(charLocation.X-2);
					numBullet.push_back(charLocation.Y);
					numBullet.push_back(charLocation.X-1);
					numBullet.push_back(charLocation.Y);
					numBullet.push_back(charLocation.X-3);
					numBullet.push_back(charLocation.Y-1);
					numBullet.push_back(charLocation.X-2);
					numBullet.push_back(charLocation.Y-1);
					numBullet.push_back(charLocation.X-3);
					numBullet.push_back(charLocation.Y+1);
					numBullet.push_back(charLocation.X-2);
					numBullet.push_back(charLocation.Y+1);
					--shotgunMag;
				}
			}
			else
			{
				if ( sreloadTimer >= shotgunReload )
				{
						shotgunMag = shotgunCap;
						sreloadTimer = 0;
				}
			}
			bulletWait = 0;
		}
		else if ( gunType == 2 ) // Machinegun. 
		{
			if ( mgunMag > 0 )
			{
				Beep(400, 30);
				numBullet.push_back(charLocation.X-2);
				numBullet.push_back(charLocation.Y);
				--mgunMag;
			}
			else
			{
				if ( mreloadTimer >= mgunReload )
				{
					mgunMag = mgunCap;
					mreloadTimer = 0;
				}
			}
		}
		else if ( gunType == 3 ) // railgun lmao
		{
			Beep(2000, 50);
			numBullet.push_back(charLocation.X-2); numBullet.push_back(charLocation.Y);
			numBullet.push_back(charLocation.X-3); numBullet.push_back(charLocation.Y);
			numBullet.push_back(charLocation.X-4); numBullet.push_back(charLocation.Y);
			numBullet.push_back(charLocation.X-5); numBullet.push_back(charLocation.Y);
			numBullet.push_back(charLocation.X-6); numBullet.push_back(charLocation.Y);
			numBullet.push_back(charLocation.X-7); numBullet.push_back(charLocation.Y);
			numBullet.push_back(charLocation.X-8); numBullet.push_back(charLocation.Y);
			numBullet.push_back(charLocation.X-9); numBullet.push_back(charLocation.Y);
			numBullet.push_back(charLocation.X-10); numBullet.push_back(charLocation.Y);
			numBullet.push_back(charLocation.X-11); numBullet.push_back(charLocation.Y);
			numBullet.push_back(charLocation.X-12); numBullet.push_back(charLocation.Y);
		}
    }

    if (keyPressed[K_DOWN] && charLocation.Y < 12) // Move Down.
    {
        Beep(600, 30);
        charLocation.Y++; 
    }

    if (keyPressed[K_RIGHT]) //cycle weapons
    {
		if ( gunType == 0 )//when using pistol
		{
			if ( shotgunBought == 1 ) //if shotgun unlocked
			{
				Beep(300, 30);
				gunType = 1; //go to shotgun
			}
			else //or if shotgun locked
			{
				if ( mgunBought == 1 ) //but machinegun unlocked
				{
					Beep(300, 30);
					gunType = 2; //go to machinegun
				}
			}
		}
		else if ( gunType == 1 ) //when using shotgun
		{
			if ( mgunBought == 1 ) //if machinegun locked
			{
				Beep(300, 30);
				gunType = 2; //go to machinegun
			}
			else
			{
				Beep(300, 30);
				gunType = 0;
			}
		}
		else if ( gunType == 2 ) //when using machinegun
		{
			Beep(300, 30);
			gunType = 0;
		}
    }

	if (keyPressed[K_H])
	{
		gunType = 3;
		Beep(300, 30);
		Beep(800, 30);
		Beep(1300, 30);
		Beep(1800, 30);
	}

	if (keyPressed[K_SPACE])
	{
		leveltrack = 6;
		spawntrack = 0;
		shotgunBought = 1;
	}

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
	{
		Beep(4000, 30);
        gamestate = DEFENDMENU;  
	}

	if (keyPressed[K_INSERT])
	{
		Beep(1480, 100);
		Beep(1568, 100);
		Beep(1568, 100);
		Beep(1568, 100);
		Beep(740, 100);
		Beep(784, 100);
		Beep(784, 100);
		Beep(784, 100);
		Beep(370, 100);
		Beep(392, 100);
		Beep(370, 100);
		Beep(392, 100);
		Beep(196, 100);
		Lives++;
		LivesCheat = 1;
	}

	if (keyPressed[K_X])
	{
		if ( bombsamtDefend > 0 )
		{
			Beep(250, 200);
			Beep(120, 500);
			--bombsamtDefend;
			numMonster.clear();
			greenMonster.clear();
			blueMonster.clear();
			yellowMonster.clear();
			redMonster.clear();
		}
	}

	if (keyPressed[K_Z]) //reload
	{
		if ( gunType == 0 && pistolMag > 0)
		{
			Beep(300, 100);
			Beep(300, 100);
			pistolMag = 0;
		}
		else if ( gunType == 1 && shotgunMag > 0)
		{
			Beep(300, 100);
			Beep(300, 100);
			shotgunMag = 0;
		}
		else if ( gunType == 2 && mgunMag > 0 )
		{
			Beep(300, 100);
			Beep(300, 100);
			mgunMag = 0;
		}
	}
}

void Wave1Defend()
{
	if ( spawntrack == 0)
	{
		zombiesLeft = 21;
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 1)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 2)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 3)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 4)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 5)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 6)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 7)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 8)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 9)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 10)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 11)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 12)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 13)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 14)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 15)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 16)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 17)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 18)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 19)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 20)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
}

void Wave2Defend()
{
	if ( spawntrack == 0)
	{
		zombiesLeft = 26;
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 1)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 2)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 3)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 4)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 5)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 6)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 7)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 8)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 9)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 10)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 11)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 12)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 13)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 14)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 15)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 16)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 17)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 18)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 19)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 20)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 21)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 22)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 23)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 24)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 25)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
}

void Wave3Defend()
{
	if ( spawntrack == 0)
	{
		zombiesLeft = 36;
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 1)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 2)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 3)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 4)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 5)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 6)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 7)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 8)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 9)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 10)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 11)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 12)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 13)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 14)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 15)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 16)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 17)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 18)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 19)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 20)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 21)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 22)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 23)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 24)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 25)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 26)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 27)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 28)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 29)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 30)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 31)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 32)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 33)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 34)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 35)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
}

void Wave4Defend()
{
	if ( spawntrack == 0)
	{
		zombiesLeft = 41;
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 1)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 2)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 3)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 4)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 5)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 6)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 7)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 8)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 9)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 10)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 11)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 12)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 13)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 14)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 15)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 16)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 17)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 18)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 19)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 20)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 21)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 22)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 23)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 24)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 25)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 26)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 27)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 28)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 29)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 30)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 31)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 32)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 33)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 34)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 35)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 36)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 37)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 38)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 39)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 40)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
}

void Wave5Defend()
{
	if ( spawntrack == 0)
	{
		zombiesLeft = 51;
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 1)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 2)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 3)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 4)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 5)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 6)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 7)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 8)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 9)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 10)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 11)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 12)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 13)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 14)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 15)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 16)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 17)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 18)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 19)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	if ( spawntrack == 20)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 21)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 22)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 23)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 24)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 25)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 26)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 27)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 28)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 29)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 30)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 31)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 32)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 33)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 34)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 35)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 36)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 37)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 38)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 39)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 40)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 41)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 42)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 43)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 44)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 45)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 46)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 47)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 48)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 49)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
	else if ( spawntrack == 50)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 0;
	}
}

void Wave6Defend()
{
	if ( spawntrack == 0)
	{
		zombiesLeft = 41;
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 1)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 2)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 3)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 4)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 5)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 6)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 7)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 8)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 9)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 10)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 11)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 12)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 13)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 14)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 15)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 16)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 17)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 18)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 19)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 20)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 21)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 22)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 23)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 24)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 25)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 26)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 27)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 28)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 29)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 30)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 31)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 32)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 33)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 34)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 35)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 36)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 37)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 38)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 39)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 40)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
}

void Wave7Defend()
{
	if ( spawntrack == 0)
	{
		zombiesLeft = 51;
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 1)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 2)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 3)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 4)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 5)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 6)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 7)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 8)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 9)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 10)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 11)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 12)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 13)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 14)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 15)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 16)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 17)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 18)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 19)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 20)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 21)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 22)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 23)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 24)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 25)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 26)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 27)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 28)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 29)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 30)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 31)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 32)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 33)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 34)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 35)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 36)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 37)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 38)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 39)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 40)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 41)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 42)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 43)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 44)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 45)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 46)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 47)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 48)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 49)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 50)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
}

void Wave8Defend()
{
	if ( spawntrack == 0)
	{
		zombiesLeft = 71;
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 1)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 2)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 3)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 4)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 5)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 6)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 7)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 8)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 9)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 10)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 11)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 12)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 13)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 14)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 15)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 16)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 17)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 18)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 19)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 20)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 21)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 22)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 23)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 24)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 25)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 26)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 27)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 28)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 29)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 30)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 31)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 32)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 33)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 34)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 35)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 36)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 37)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 38)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 39)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 40)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 41)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 42)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 43)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 44)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 45)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 46)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 48)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 49)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 50)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 51)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 52)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 53)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 54)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 55)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 56)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 57)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 58)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 59)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 60)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 61)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 62)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 63)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 64)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 65)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 66)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 67)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 68)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 69)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 70)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
}

void Wave9Defend()
{
	if ( spawntrack == 0)
	{
		zombiesLeft = 66;
		redMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 1)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 2)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 3)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 4)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 5)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 6)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 7)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 8)
	{
		redMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 9)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 10)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 11)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 12)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 13)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 14)
	{
		redMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 15)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 16)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 17)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 18)
	{
		redMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 19)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 20)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 21)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 22)
	{
		redMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 23)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 24)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 25)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 26)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 27)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 28)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 29)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 30)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 31)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 32)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 33)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 34)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 35)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 36)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 37)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 38)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 39)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 40)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 41)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 42)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 43)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 44)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 45)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 46)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 47)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 48)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 49)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 50)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 51)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 52)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 53)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 54)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 55)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 56)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 57)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 58)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 59)
	{
		numMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 60)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 61)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 62)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 63)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 64)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 65)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
}

void Wave10Defend()
{
	if ( spawntrack == 0)
	{
		zombiesLeft = 71;
		redMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 1)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 2)
	{
		redMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 3)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 4)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 5)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 6)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 7)
	{
		redMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 8)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 9)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 10)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 11)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 12)
	{
		redMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 13)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 14)
	{
		redMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 15)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 16)
	{
		redMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 17)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 18)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 19)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 20)
	{
		redMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 21)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 22)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 23)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 24)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 25)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 26)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 27)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 28)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 29)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 30)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 31)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 32)
	{
		redMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 33)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 34)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 35)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 36)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 37)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 38)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 39)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 40)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 41)
	{
		redMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 42)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 43)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 44)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 45)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 46)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 47)
	{
		redMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 48)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 49)
	{
		redMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 50)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 51)
	{
		redMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 52)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 53)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 54)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 55)
	{
		redMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 56)
	{
		redMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 57)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 58)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 59)
	{
		redMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 60)
	{
		redMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 61)
	{
		redMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 62)
	{
		yellowMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 63)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 64)
	{
		redMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 65)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 66)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 67)
	{
		redMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 68)
	{
		greenMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 69)
	{
		blueMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
	else if ( spawntrack == 70)
	{
		redMonsterSpawn();
		spawntrack++;
		monsterWait = 1;
	}
}

void numMonsterSpawn()
{
	numMonster.push_back(0); //x coord
	numMonster.push_back(rand() % 10 + 3); //y coord
}

void greenMonsterSpawn()
{
	greenMonster.push_back(0); //x coord
	greenMonster.push_back(rand() % 10 + 3); //y coord
}

void blueMonsterSpawn()
{
	blueMonster.push_back(0); //x coord
	blueMonster.push_back(rand() % 10 + 3); //y coord
	blueMonster.push_back(2 + defendhp); //hp
}

void yellowMonsterSpawn()
{
	yellowMonster.push_back(0); //x coord
	yellowMonster.push_back(rand() % 10 + 3); //y coord
	yellowMonster.push_back(3 + defendhp); //hp
}

void redMonsterSpawn()
{
	redMonster.push_back(0); //x coord
	redMonster.push_back(rand() % 10 + 3); //y coord
	redMonster.push_back(5 + defendhp*2); //hp
}

void gameovernoHSDefend()
{
	Beep(784, 100);//show score and ask user to return
	Beep(698, 100);
	Beep(659, 100);
	Beep(567, 100);
	Beep(523, 100);
	Beep(493, 100);
	Beep(440, 100);
	Beep(392, 100);
	gamestate = DEFENDGAMEOVER;
}

void updateHSDefend()
{

	int Ranking = 11;
	if ( playerScoreDefend > ScoreDefend1 ) // 1
		Ranking = 1;
	if ( playerScoreDefend > ScoreDefend2 && Ranking == 11) // 2
		Ranking = 2;
	if ( playerScoreDefend > ScoreDefend3 && Ranking == 11) // 3
		Ranking = 3;
	if ( playerScoreDefend > ScoreDefend4 && Ranking == 11) // 4
		Ranking = 4;
	if ( playerScoreDefend > ScoreDefend5 && Ranking == 11) // 5
		Ranking = 5;
	if ( playerScoreDefend > ScoreDefend6 && Ranking == 11) // 6
		Ranking = 6;
	if ( playerScoreDefend > ScoreDefend7 && Ranking == 11) // 7
		Ranking = 7;
	if ( playerScoreDefend > ScoreDefend8 && Ranking == 11) // 8
		Ranking = 8;
	if ( playerScoreDefend > ScoreDefend9 && Ranking == 11) // 9
		Ranking = 9;
	if ( playerScoreDefend > ScoreDefend10 && Ranking == 11) // 10
		Ranking = 10;
	// Ranking = your rank ~~
	if ( Ranking == 1 )
	{
		ScoreDefend10 = ScoreDefend9;
		ScoreDefend10N = ScoreDefend9N;

		ScoreDefend9 = ScoreDefend8;
		ScoreDefend9N = ScoreDefend8N;

		ScoreDefend8 = ScoreDefend7;
		ScoreDefend8N = ScoreDefend7N;

		ScoreDefend7 = ScoreDefend6;
		ScoreDefend7N = ScoreDefend6N;

		ScoreDefend6 = ScoreDefend5;
		ScoreDefend6N = ScoreDefend5N;

		ScoreDefend5 = ScoreDefend4;
		ScoreDefend5N = ScoreDefend4N;

		ScoreDefend4 = ScoreDefend3;
		ScoreDefend4N = ScoreDefend3N;

		ScoreDefend3 = ScoreDefend2;
		ScoreDefend3N = ScoreDefend2N;

		ScoreDefend2 = ScoreDefend1;
		ScoreDefend2N = ScoreDefend1N;

		ScoreDefend1 = playerScoreDefend;
		ScoreDefend1N = playerName;
	}
	else if ( Ranking == 2 )
	{

		ScoreDefend10 = ScoreDefend9;
		ScoreDefend10N = ScoreDefend9N;

		ScoreDefend9 = ScoreDefend8;
		ScoreDefend9N = ScoreDefend8N;

		ScoreDefend8 = ScoreDefend7;
		ScoreDefend8N = ScoreDefend7N;

		ScoreDefend7 = ScoreDefend6;
		ScoreDefend7N = ScoreDefend6N;

		ScoreDefend6 = ScoreDefend5;
		ScoreDefend6N = ScoreDefend5N;

		ScoreDefend5 = ScoreDefend4;
		ScoreDefend5N = ScoreDefend4N;

		ScoreDefend4 = ScoreDefend3;
		ScoreDefend4N = ScoreDefend3N;

		ScoreDefend3 = ScoreDefend2;
		ScoreDefend3N = ScoreDefend2N;

		ScoreDefend2 = playerScoreDefend;
		ScoreDefend2N = playerName;
	}
	else if ( Ranking == 3 )
	{
		ScoreDefend10 = ScoreDefend9;
		ScoreDefend10N = ScoreDefend9N;

		ScoreDefend9 = ScoreDefend8;
		ScoreDefend9N = ScoreDefend8N;

		ScoreDefend8 = ScoreDefend7;
		ScoreDefend8N = ScoreDefend7N;

		ScoreDefend7 = ScoreDefend6;
		ScoreDefend7N = ScoreDefend6N;

		ScoreDefend6 = ScoreDefend5;
		ScoreDefend6N = ScoreDefend5N;

		ScoreDefend5 = ScoreDefend4;
		ScoreDefend5N = ScoreDefend4N;

		ScoreDefend4 = ScoreDefend3;
		ScoreDefend4N = ScoreDefend3N;

		ScoreDefend3 = playerScoreDefend;
		ScoreDefend3N = playerName;
	}
	else if ( Ranking == 4 )
	{
		ScoreDefend10 = ScoreDefend9;
		ScoreDefend10N = ScoreDefend9N;

		ScoreDefend9 = ScoreDefend8;
		ScoreDefend9N = ScoreDefend8N;

		ScoreDefend8 = ScoreDefend7;
		ScoreDefend8N = ScoreDefend7N;

		ScoreDefend7 = ScoreDefend6;
		ScoreDefend7N = ScoreDefend6N;

		ScoreDefend6 = ScoreDefend5;
		ScoreDefend6N = ScoreDefend5N;

		ScoreDefend5 = ScoreDefend4;
		ScoreDefend5N = ScoreDefend4N;

		ScoreDefend4 = playerScoreDefend;
		ScoreDefend4N = playerName;
	}
	else if ( Ranking == 5 )
	{
		ScoreDefend10 = ScoreDefend9;
		ScoreDefend10N = ScoreDefend9N;

		ScoreDefend9 = ScoreDefend8;
		ScoreDefend9N = ScoreDefend8N;

		ScoreDefend8 = ScoreDefend7;
		ScoreDefend8N = ScoreDefend7N;

		ScoreDefend7 = ScoreDefend6;
		ScoreDefend7N = ScoreDefend6N;

		ScoreDefend6 = ScoreDefend5;
		ScoreDefend6N = ScoreDefend5N;

		ScoreDefend5 = playerScoreDefend;
		ScoreDefend5N = playerName;
	}
	else if ( Ranking == 6 )
	{
		ScoreDefend10 = ScoreDefend9;
		ScoreDefend10N = ScoreDefend9N;

		ScoreDefend9 = ScoreDefend8;
		ScoreDefend9N = ScoreDefend8N;

		ScoreDefend8 = ScoreDefend7;
		ScoreDefend8N = ScoreDefend7N;

		ScoreDefend7 = ScoreDefend6;
		ScoreDefend7N = ScoreDefend6N;

		ScoreDefend6 = playerScoreDefend;
		ScoreDefend6N = playerName;
	}
	else if ( Ranking == 7 )
	{
		ScoreDefend10 = ScoreDefend9;
		ScoreDefend10N = ScoreDefend9N;

		ScoreDefend9 = ScoreDefend8;
		ScoreDefend9N = ScoreDefend8N;

		ScoreDefend8 = ScoreDefend7;
		ScoreDefend8N = ScoreDefend7N;

		ScoreDefend7 = playerScoreDefend;
		ScoreDefend7N = playerName;
	}
	else if ( Ranking == 8 )
	{
		ScoreDefend10 = ScoreDefend9;
		ScoreDefend10N = ScoreDefend9N;

		ScoreDefend9 = ScoreDefend8;
		ScoreDefend9N = ScoreDefend8N;

		ScoreDefend8 = playerScoreDefend;
		ScoreDefend8N = playerName;
	}
	else if ( Ranking == 9 )
	{
		ScoreDefend10 = ScoreDefend9;
		ScoreDefend10N = ScoreDefend9N;

		ScoreDefend9 = playerScoreDefend;
		ScoreDefend9N = playerName;
	}
	else if ( Ranking == 10 )
	{
		ScoreDefend10 = playerScoreDefend;
		ScoreDefend10N = playerName;
	}

	savescoresDefend();
	gamestate = DEFENDGAMEOVER;
}

void initDefendMenu()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set character location
    charLocation.X = 31;
    charLocation.Y = 13;

    elapsedTime = 0.0;
}

void renderDefendMenu()
{
	// clear previous screen
	colour(0x0F);
    cls();

	// render options
	colour(0x0F);

	gotoXY(32, 13);
	std::cout << "Play Defend!";

	gotoXY(32, 16);
	std::cout << "Instructions";

	gotoXY(32, 19);
	std::cout << "Title Screen";

	gotoXY(32, 22);
	std::cout << "High Scores";

	// render ASCII title screen
	gotoXY(17, 2);
	std::cout << "    ____  ___________________   ______     __";

	gotoXY(17, 3);
	std::cout << "   / __ \\/ ____/ ____/ ____/ | / / __ \\   / /";

	gotoXY(17, 4);
	std::cout << "  / / / / __/ / /_  / __/ /  |/ / / / /  / / ";

	gotoXY(17, 5);
	std::cout << " / /_/ / /___/ __/ / /___/ /|  / /_/ /  /_/ ";

	gotoXY(17, 6);
	std::cout << "/_____/_____/_/   /_____/_/ |_/_____/  (_)   ";

	// render cursor
    gotoXY(charLocation);
    colour(0x0C);
    std::cout << (char)16;

}

void updateDefendMenu(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

    // Updating the location of the cursor
    if (keyPressed[K_UP] && charLocation.Y != 13) // Move Up.
    {
        Beep(700, 30);
        charLocation.Y -= 3; 
    }

    if (keyPressed[K_DOWN] && charLocation.Y != 22) // Move Down.
    {
		Beep(700, 30);
		charLocation.Y += 3;
    }

	if (keyPressed[K_ENTER] )
	{
		Beep(4000, 30);
		if ( charLocation.Y == 16) // Instructions
			gamestate = DEFENDINSTRUCTION1;
		if ( charLocation.Y == 13) // Play!
		{
			if ( isFirstTimeEnter == 0 )
				gamestate = DEFENDINTRODUCTION;
			else
				gamestate = DEFENDPLAY;
		}
		if ( charLocation.Y == 19) // Exit to game title
			gamestate = MENU;
		if ( charLocation.Y == 22)
			gamestate = DEFENDHIGHSCORE;
	}

    if (keyPressed[K_ESCAPE])
	{ 
	}
}

void initDefendIntroduction()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set character location
    charLocation.X = 31;
    charLocation.Y = 13;

    elapsedTime = 0.0;
	enterIntro = 0;
	typewriter = 0;
	isFirstTimeEnter = 1;
}

void renderDefendIntroduction()
{
	// clear previous screen
	colour(0x0F);
	if ( enterIntro == 0 )
	{
		cls();
		enterIntro = 1;
	}

	// render options
	colour(0x0F);


	//typewriter effect
	//render story
	if ( typewriter == 0 )
	{
		gotoXY(1, 2);
		for ( unsigned int i = 0; i < DLine1.size(); i++ )
		{
			std::cout << DLine1[i];
			Sleep(30);
		}
		Sleep(300);
		gotoXY(1, 4);
		for ( unsigned int i = 0; i < DLine2.size(); i++ )
		{
			std::cout << DLine2[i];
			Sleep(30);
		}
		Sleep(300);
		gotoXY(1, 5);
		for ( unsigned int i = 0; i < DLine3.size(); i++ )
		{
			std::cout << DLine3[i];
			Sleep(30);
		}
		Sleep(300);
		gotoXY(1, 7);
		for ( unsigned int i = 0; i < DLine4.size(); i++ )
		{
			std::cout << DLine4[i];
			Sleep(30);
		}
	
		gotoXY(1, 8);
		for ( unsigned int i = 0; i < DLine5.size(); i++ )
		{
			std::cout << DLine5[i];
			Sleep(30);
		}
		Sleep(300);
		gotoXY(1, 9);
		for ( unsigned int i = 0; i < DLine6.size(); i++ )
		{
			std::cout << DLine6[i];
			Sleep(30);
		}

		gotoXY(1, 10);
		for ( unsigned int i = 0; i < DLine7.size(); i++ )
		{
			std::cout << DLine7[i];
			Sleep(30);
		}
		Sleep(300);
		gotoXY(1, 11);
		for ( unsigned int i = 0; i < DLine8.size(); i++ )
		{
			std::cout << DLine8[i];
			Sleep(30);
		}
		Sleep(300);
		gotoXY(1, 13);
		for ( unsigned int i = 0; i < DLine10.size(); i++ )
		{
			std::cout << DLine10[i];
			Sleep(30);
		}
		Sleep(300);
		gotoXY(1, 14);
		for ( unsigned int i = 0; i < DLine11.size(); i++ )
		{
			std::cout << DLine11[i];
			Sleep(30);
		}
		Sleep(300);
		gotoXY(1, 15);
		for ( unsigned int i = 0; i < DLine12.size(); i++ )
		{
			std::cout << DLine12[i];
			Sleep(30);
		}
		Sleep(300);
		gotoXY(1, 16);
		for ( unsigned int i = 0; i < DLine13.size(); i++ )
		{
			std::cout << DLine13[i];
			Sleep(30);
		}
		Sleep(300);
		gotoXY(1, 18);
		for ( unsigned int i = 0; i < DLine14.size(); i++ )
		{
			std::cout << DLine14[i];
			Sleep(30);
		}
	
		gotoXY(1, 19);
		for ( unsigned int i = 0; i < DLine15.size(); i++ )
		{
			std::cout << DLine15[i];
			Sleep(30);
		}
		Sleep(300);
		gotoXY(1, 20);
		for ( unsigned int i = 0; i < DLine16.size(); i++ )
		{
			std::cout << DLine16[i];
			Sleep(30);
		}

		gotoXY(1, 21);
		for ( unsigned int i = 0; i < DLine17.size(); i++ )
		{
			std::cout << DLine17[i];
			Sleep(30);
		}
		Sleep(300);
		typewriter = 1;
	}

	if ( typewriter == 1 )
	{
		gotoXY(50, 22);
		std::cout << "Press Enter to Continue...";
		gotoXY(76, 22);
	}

	if ( typewriter == 2 )
	{
		cls();
		gotoXY(1, 2);
		for ( unsigned int i = 0; i < DLine18.size(); i++ )
		{
			std::cout << DLine18[i];
			Sleep(30);
		}
		Sleep(300);
		gotoXY(1, 3);
		for ( unsigned int i = 0; i < DLine19.size(); i++ )
		{
			std::cout << DLine19[i];
			Sleep(30);
		}
		Sleep(300);
		gotoXY(1, 4);
		for ( unsigned int i = 0; i < DLine20.size(); i++ )
		{
			std::cout << DLine20[i];
			Sleep(30);
		}

		gotoXY(1, 5);
		for ( unsigned int i = 0; i < DLine21.size(); i++ )
		{
			std::cout << DLine21[i];
			Sleep(30);
		}
	
		gotoXY(1, 7);
		for ( unsigned int i = 0; i < DLine22.size(); i++ )
		{
			std::cout << DLine22[i];
			Sleep(30);
		}
		Sleep(300);
		gotoXY(1, 8);
		for ( unsigned int i = 0; i < DLine23.size(); i++ )
		{
			std::cout << DLine23[i];
			Sleep(30);
		}

		gotoXY(1, 10);
		for ( unsigned int i = 0; i < DLine24.size(); i++ )
		{
			std::cout << DLine24[i];
			Sleep(30);
		}
		Sleep(300);
		gotoXY(1, 11);
		for ( unsigned int i = 0; i < DLine25.size(); i++ )
		{
			std::cout << DLine25[i];
			Sleep(30);
		}
		Sleep(300);
		gotoXY(1, 13);
		for ( unsigned int i = 0; i < DLine26.size(); i++ )
		{
			std::cout << DLine26[i];
			Sleep(30);
		}
		Sleep(300);
		gotoXY(1, 14);
		for ( unsigned int i = 0; i < DLine27.size(); i++ )
		{
			std::cout << DLine27[i];
			Sleep(30);
		}
		Sleep(300);
		gotoXY(1, 15);
		for ( unsigned int i = 0; i < DLine28.size(); i++ )
		{
			std::cout << DLine28[i];
			Sleep(30);
		}
		Sleep(300);
		gotoXY(1, 16);
		for ( unsigned int i = 0; i < DLine29.size(); i++ )
		{
			std::cout << DLine29[i];
			Sleep(30);
		}
		Sleep(300);
		gotoXY(1, 18);
		for ( unsigned int i = 0; i < DLine30.size(); i++ )
		{
			std::cout << DLine30[i];
			Sleep(30);
		}
	
		gotoXY(1, 20);
		for ( unsigned int i = 0; i < DLine31.size(); i++ )
		{
			std::cout << DLine31[i];
			Sleep(30);
			typewriter = 3;
		}
		Sleep(300);
	}

	if ( typewriter == 3 )
	{
		gotoXY(50, 22);
		std::cout << "Press Enter to Continue...";
		gotoXY(76, 22);
	}

	if ( typewriter == 4 )
	{
		cls();
		gotoXY(1, 2);
		for ( unsigned int i = 0; i < DLine32.size(); i++ )
		{
			std::cout << DLine32[i];
			Sleep(30);
		}
		Sleep(300);
		gotoXY(1, 5);
		for ( unsigned int i = 0; i < DLine33.size(); i++ )
		{
			std::cout << DLine33[i];
			Sleep(30);
		}
		Sleep(300);
		gotoXY(1, 7);
		for ( unsigned int i = 0; i < DLine34.size(); i++ )
		{
			std::cout << DLine34[i];
			Sleep(30);
		}
		Sleep(300);
		gotoXY(1, 9);
		for ( unsigned int i = 0; i < DLine35.size(); i++ )
		{
			std::cout << DLine35[i];
			Sleep(30);
		}
		Sleep(300);
		gotoXY(1, 11);
		for ( unsigned int i = 0; i < DLine36.size(); i++ )
		{
			std::cout << DLine36[i];
			Sleep(30);
		}
	
		gotoXY(1, 12);
		for ( unsigned int i = 0; i < DLine37.size(); i++ )
		{
			std::cout << DLine37[i];
			Sleep(30);
		}
		Sleep(300);
		gotoXY(1, 14);
		for ( unsigned int i = 0; i < DLine38.size(); i++ )
		{
			std::cout << DLine38[i];
			Sleep(30);
		}
		Sleep(300);
		gotoXY(1, 15);
		for ( unsigned int i = 0; i < DLine39.size(); i++ )
		{
			std::cout << DLine39[i];
			Sleep(30);
			typewriter = 5;
		}
	}

	if ( typewriter == 5 )
	{
		gotoXY(46, 22);
		std::cout << "Press Enter to start the game!";
		gotoXY(76, 22);
	}
}

void updateDefendIntroduction(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

    // Updating the location of the cursor

	if (keyPressed[K_ENTER] )
	{
		if ( typewriter == 1 )
			typewriter = 2;
		if ( typewriter == 3 )
			typewriter = 4;
		if ( typewriter == 5 )
			gamestate = DEFENDPLAY;
	}

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
	{
		gamestate = DEFENDMENU; 
	}
}

void initDefendInstructions1()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set character location
    charLocation.X = 00;
    charLocation.Y = 00;

	instructionClear = 0;
}

void renderDefendInstructions1()
{
	// clear previous screen
	colour(0x0F);
	if ( instructionClear == 0 )
	{
		cls();
		instructionClear = 1;
	}

	// render options
	colour(0x0F);

	gotoXY(25, 2);
	std::cout << "Defend! Instructions: The Story";

	gotoXY(2, 4);
	std::cout << "Its a wonderful day! You wake up to the melodious chirping of birds,";

	gotoXY(2, 5);
	std::cout << "inhaling deeply the crisp air with the smell of morning dew.";

	gotoXY(2, 6);
	std::cout << "Propelling yourself out of the bed, you walk towards the mirror in";

	gotoXY(2, 7);
	std::cout << "your room with a spring in your step, smiling radiantly.";

	gotoXY(2, 8);
	std::cout << "As you practice making photogenic faces in front of the mirror,";

	gotoXY(2, 9);
	std::cout << "you hear commotion coming from outside your home.";

	gotoXY(2, 10);
	std::cout << "'Must be the milkman!' you thought to yourself, as you hurriedly";

	gotoXY(2, 11);
	std::cout << "brushed your hair with your hand and tried to straighten out";

	gotoXY(2, 12);
	std::cout << "the creases on your shirt, heading for the door.";

	gotoXY(2, 14);
	std::cout << "Just kidding. You're a survivor of a stereotypical zombie outbreak";

	gotoXY(2, 15);
	std::cout << "that happens in games and movies. Armed with infinite ammo and a";

	gotoXY(2, 16);
	std::cout << "variety of guns, prevent your home from being overrun by the zombies!";

	gotoXY(2, 18);
	std::cout << "How long will you be able to last?";

	gotoXY(30, 21);
	std::cout << "Press ENTER to return";

	gotoXY(65, 21);
	std::cout << " >NEXT";

}

void updateDefendInstructions1(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

    // Updating the location of the cursor
    if (keyPressed[K_RIGHT] ) // Page 2
    {
        Beep(700, 30);
        gamestate = DEFENDINSTRUCTION2;
    }

	if (keyPressed[K_ENTER] ) // Return to Defend! Menu
	{
		Beep(4000, 30);
		gamestate = DEFENDMENU;
	}

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
	{
		Beep(4000, 30);
		gamestate = DEFENDMENU;   
	}
}

void initDefendInstructions2()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set character location
    charLocation.X = 00;
    charLocation.Y = 00;

	instructionClear = 0;
}

void renderDefendInstructions2()
{
	// clear previous screen
	colour(0x0F);

	if ( instructionClear == 0 )
	{
		cls();
		instructionClear = 1;
	}

	// render options
	colour(0x0F);

	gotoXY(25, 2);
	std::cout << "Defend! Instructions:  Controls";

	gotoXY(2, 4);
	std::cout << "UP Arrow Key    - Move Up             ESCAPE Key  - Quit to Title Screen";

	gotoXY(2, 6);
	std::cout << "DOWN Arrow Key  - Move down           INSERT Key  - Obtain an extra life,";

	gotoXY(2, 7);
	std::cout << "                                                    but disable highscores.";

	gotoXY(2, 8);
	std::cout << "LEFT Arrow Key  - Shoot                            ";

	gotoXY(2, 10);
	std::cout << "RIGHT Arrow Key - Cycle Weapons       X Key       - Bomb";

	gotoXY(2, 12);
	std::cout << "==========================================================================";

	gotoXY(2, 14);
	std::cout << "Weapons Available: ";

	gotoXY(2, 16);
	std::cout << "Pistol, Shotgun, Machinegun";

	gotoXY(2, 21);
	std::cout << "PREVIOUS<";

	gotoXY(30, 21);
	std::cout << "Press ENTER to return";

	gotoXY(65, 21);
	std::cout << " >NEXT";

}

void updateDefendInstructions2(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

    // Updating the location of the cursor
    if (keyPressed[K_RIGHT] ) // Page 3
    {
        Beep(700, 30);
        gamestate = DEFENDINSTRUCTION3;
    }

	    if (keyPressed[K_LEFT] ) // Page 1
    {
        Beep(700, 30);
        gamestate = DEFENDINSTRUCTION1;
    }

	if (keyPressed[K_ENTER] ) // Return to Defend! Menu
	{
		Beep(4000, 30);
		gamestate = DEFENDMENU;
	}

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
	{
		Beep(4000, 30);
		gamestate = DEFENDMENU;   
	}
}

void initDefendInstructions3()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set character location
    charLocation.X = 00;
    charLocation.Y = 00;

	instructionClear = 0;
}

void renderDefendInstructions3()
{
	// clear previous screen
	colour(0x0F);

	if ( instructionClear == 0 )
	{
		cls();
		instructionClear = 1;
	}

	// render options
	colour(0x0F);

	gotoXY(25, 2);
	std::cout << "Defend! Instructions:  Monsters";

	gotoXY(2, 4);
	std::cout << (char)2 << "    - Your typical weak zombie often with missing body parts.";
	gotoXY(2, 5);
	std::cout << "       Speed: Slow          Health: Low";

	gotoXY(2, 7);
	colour(0x02);
	std::cout << (char)2;
	colour(0x0F);
	std::cout << "    - The zombies that somehow are still able to run with decaying legs";
	gotoXY(2, 8);
	std::cout << "       Speed: Normal        Health: Low";

	gotoXY(2, 10);
	colour(0x01);
	std::cout << (char)2;
	colour(0x0F);
	std::cout << "    - The zombies that put on weight and now can absorb more bullets";
	gotoXY(2, 11);
	std::cout << "       Speed: Slow          Health: Normal";

	gotoXY(2, 13);
	colour(0x0E);
	std::cout << (char)2;
	colour(0x0F);
	std::cout << "    - Zombies that can run and take more than one bullet...";
	gotoXY(2, 14);
	std::cout << "       Speed: Medium        Health: Normal";

	gotoXY(2, 16);
	colour(0x04);
	std::cout << "===" << (char)2;
	colour(0x0F);
	std::cout << " - Big bad boss zombie with a tail. ";
	gotoXY(2, 17);
	std::cout << "       Speed: Normal        Health: ????";

	gotoXY(2, 21);
	std::cout << "PREVIOUS<";

	gotoXY(30, 21);
	std::cout << "Press ENTER to return";

}

void updateDefendInstructions3(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

    // Updating the location of the cursor
    if (keyPressed[K_LEFT] ) // Page 2
    {
        Beep(700, 30);
		gamestate = DEFENDINSTRUCTION2;    
    }

	if (keyPressed[K_ENTER] ) // Return to Defend! Menu
	{
		Beep(4000, 30);
		gamestate = DEFENDMENU;
	}

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
	{
		Beep(4000, 30);
        gamestate = DEFENDMENU;    
	}
}

void initDefendGO()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set character location
    charLocation.X = 00;
    charLocation.Y = 00;
}

void renderDefendGO()
{
	// clear previous screen
	colour(0x0F);
    cls();

	// render time taken to calculate this frame
    gotoXY(70, 0);
    colour(0x1A);
    std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
    gotoXY(0, 0);
    colour(0x59);
    std::cout << elapsedTime << "secs" << std::endl;

	// render options
	colour(0x0F);

	gotoXY(12, 2);
	std::cout << "   _________    __  _____________ _    ____________     ";

	gotoXY(12, 3);
	std::cout << "  / ____/   |  /  |/  / ____/ __ \\ |  / / ____/ __ \\    ";

	gotoXY(12, 4);
	std::cout << " / / __/ /| | / /|_/ / __/ / / / / | / / __/ / /_/ /    ";

	gotoXY(12, 5);
	std::cout << "/ /_/ / ___ |/ /  / / /___/ /_/ /| |/ / /___/ _, _/ _ _ ";

	gotoXY(12, 6);
	std::cout << "\\____/_/  |_/_/  /_/_____/\\____/ |___/_____/_/ |_(_|_|_)";

	gotoXY(35, 15);
	std::cout << "Score: " << playerScoreDefend;

	gotoXY(30, 21);
	std::cout << "Press ENTER to return";

}

void updateDefendGO(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

	if (keyPressed[K_ENTER] ) // Return to Defend! Menu
	{
		Beep(4000, 30);
		gamestate = DEFENDHIGHSCORE;
	}

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
	{
		Beep(4000, 30);
		gamestate = DEFENDMENU;
	}
}

void initDefendHS()
{
	loadscoresDefend(); //load high scores
	
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set character location
    charLocation.X = 00;
    charLocation.Y = 00;
}

void renderDefendHS()
{
	// clear previous screen
	colour(0x0F);
    cls();

	// render time taken to calculate this frame
    gotoXY(70, 0);
    colour(0x1A);
    std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
    gotoXY(0, 0);
    colour(0x59);
    std::cout << elapsedTime << "secs" << std::endl;

	// render options
	colour(0x0F);

	gotoXY(17, 2);
	std::cout << "    ____  ___________________   ______     __";

	gotoXY(17, 3);
	std::cout << "   / __ \\/ ____/ ____/ ____/ | / / __ \\   / /";

	gotoXY(17, 4);
	std::cout << "  / / / / __/ / /_  / __/ /  |/ / / / /  / / ";

	gotoXY(17, 5);
	std::cout << " / /_/ / /___/ __/ / /___/ /|  / /_/ /  /_/ ";

	gotoXY(17, 6);
	std::cout << "/_____/_____/_/   /_____/_/ |_/_____/  (_)   ";

	gotoXY(22, 10);
	std::cout << "RANK         SCORE            NAME";

	gotoXY(22, 11);
	colour(0x04);
	std::cout << "1ST         " << ScoreDefend1 << "           ";
	gotoXY(52, 11);
	std::cout << ScoreDefend1N;

	gotoXY(22, 12);
	colour(0x0C);
	std::cout << "2ND         " << ScoreDefend2 << "           ";
	gotoXY(52, 12);
	std::cout << ScoreDefend2N;

	gotoXY(22, 13);
	colour(0x0E);
	std::cout << "3RD         " << ScoreDefend3 << "           ";
	gotoXY(52, 13);
	std::cout << ScoreDefend3N;

	gotoXY(22, 14);
	colour(0x0F);
	std::cout << "4TH         " << ScoreDefend4 << "           ";
	gotoXY(52, 14);
	std::cout << ScoreDefend4N;

	gotoXY(22, 15);
	std::cout << "5TH         " << ScoreDefend5 << "           ";
	gotoXY(52, 15);
	std::cout << ScoreDefend5N;

	gotoXY(22, 16);
	std::cout << "6TH         " << ScoreDefend6 << "           ";
	gotoXY(52, 16);
	std::cout << ScoreDefend6N;

	gotoXY(22, 17);
	std::cout << "7TH         " << ScoreDefend7 << "           ";
	gotoXY(52, 17);
	std::cout << ScoreDefend7N;

	gotoXY(22, 18);
	std::cout << "8TH         " << ScoreDefend8 << "           ";
	gotoXY(52, 18);
	std::cout << ScoreDefend8N;

	gotoXY(22, 19);
	std::cout << "9TH         " << ScoreDefend9 << "           ";
	gotoXY(52, 19);
	std::cout << ScoreDefend9N;

	gotoXY(22, 20);
	std::cout << "10TH        " << ScoreDefend10 << "           ";
	gotoXY(52, 20);
	std::cout << ScoreDefend10N;

	gotoXY(30, 22);
	std::cout << "Press ENTER to return";

}

void updateDefendHS(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

	if (keyPressed[K_ENTER] ) // Return to Defend! Menu
	{
		Beep(4000, 30);
		gamestate = DEFENDMENU;
	}

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
	{
		Beep(4000, 30);
		gamestate = DEFENDMENU;
	}
}

void initDefendUpgrade()
{	
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set character location
    charLocation.X = 64;
    charLocation.Y = 7;

	//make sure game is empty c_C

	numBullet.clear();
	clearMonster();
}

void renderDefendUpgrade()
{
	// clear previous screen if input
	colour(0x0F);

    if ( clsUpgrade == 0 )
	{
		cls();
		clsUpgrade = 1;
		//render continue

		gotoXY(65, 23);
		std::cout << "Continue";

		//render instructions
		gotoXY(40, 2);
		std::cout << "You have survived the night.";
		gotoXY(40, 3);
		std::cout << "Spend EXP Points to upgrade!";
		gotoXY(40, 4);
		std::cout << "Press ENTER Key to choose.";
		//outer border
		gotoXY(0, 0);
		std::cout << (char)201;

		for ( int i = 1; i < 24; i++)
		{
			gotoXY(0, i);
			std::cout << (char)186;
		}

		gotoXY(0, 24);
		std::cout << (char)200;

		for ( int i = 1; i < 79; i++)
		{
			gotoXY(i, 0);
			std::cout << (char)205;
		}

		gotoXY(0, 79);
		std::cout << (char)187;

		for ( int i = 1; i < 24; i++)
		{
			gotoXY(79, i);
			std::cout << (char)186;
		}

		for ( int i = 1; i < 79; i++)
		{
			gotoXY(i, 24);
			std::cout << (char)205;
		}

		gotoXY(79, 24);
		std::cout << (char)188;
		//border done

		//render UPGRADE and box around it
		gotoXY(2, 1);
		std::cout << "      __   __   __        __   ___";
		gotoXY(2, 2);
		std::cout << "|  | |__) / _` |__)  /\\  |  \\ |__ ";
		gotoXY(2, 3);
		std::cout << "|__| |    \\__> |  \\ /~~\\ |__/ |___";

		//render pistol

		gotoXY(3, 7);
		std::cout << "  _______.";
		gotoXY(3, 8);
		std::cout << "~(_]-----'";
		gotoXY(3, 9);
		std::cout << "/_(";

		//render box around pistol
		for ( int i = 2; i < 14; i++)
		{
			gotoXY(i, 6);
			std::cout << (char)196;
			gotoXY(i, 11);
			std::cout << (char)196;
		}
		for ( int i = 7; i < 11; i++)
		{
			gotoXY(1, i);
			std::cout << (char)179;
			gotoXY(14, i);
			std::cout << (char)179;
		}
		gotoXY(1, 6);
		std::cout << (char)218;
		gotoXY(1, 11);
		std::cout << (char)192;
		gotoXY(14, 6);
		std::cout << (char)191;
		gotoXY(14, 11);
		std::cout << (char)217;

		//render shotgun
		gotoXY(2, 13);
		std::cout << "  ,________,__";
		gotoXY(2, 14);
		std::cout << " / __.---===--'";
		gotoXY(2, 15);
		std::cout << "/#(-'";
		gotoXY(2, 16);
		std::cout << "`''";

		//render box around shotgun
		for ( int i = 2; i < 17; i++)
		{
			gotoXY(i, 12);
			std::cout << (char)196;
			gotoXY(i, 17);
			std::cout << (char)196;
		}
		for ( int i = 12; i < 17; i++)
		{
			gotoXY(1, i);
			std::cout << (char)179;
			gotoXY(17, i);
			std::cout << (char)179;
		}
		gotoXY(1, 12);
		std::cout << (char)218;
		gotoXY(1, 17);
		std::cout << (char)192;
		gotoXY(17, 12);
		std::cout << (char)191;
		gotoXY(17, 17);
		std::cout << (char)217;

		//render machinegun
		gotoXY(3, 19);
		std::cout << "\\__-)==/______,_";
		gotoXY(3, 20);
		std::cout << " / .-^-||`'    ";
		gotoXY(3, 21);
		std::cout << "/_/    ||      ";

		//render box around machinegun
		for ( int i = 2; i < 19; i++)
		{
			gotoXY(i, 18);
			std::cout << (char)196;
			gotoXY(i, 22);
			std::cout << (char)196;
		}
		for ( int i = 18; i < 22; i++)
		{
			gotoXY(1, i);
			std::cout << (char)179;
			gotoXY(19, i);
			std::cout << (char)179;
		}
		gotoXY(1, 18);
		std::cout << (char)218;
		gotoXY(1, 22);
		std::cout << (char)192;
		gotoXY(19, 18);
		std::cout << (char)191;
		gotoXY(19, 22);
		std::cout << (char)217;

		//render shop text
		gotoXY(20, 6);
		std::cout << "Pistol:      ";

		gotoXY(20, 12);
		std::cout << "Shotgun:";
		gotoXY(20, 18);
		std::cout << "Machine Gun:";

		//buy option for upgrades
		gotoXY(60, 7);
		std::cout << "Buy";
		gotoXY(60, 9);
		std::cout << "Buy";
		gotoXY(60, 12);
		std::cout << "Buy";
		gotoXY(60, 13);
		std::cout << "Buy";
		gotoXY(60, 15);
		std::cout << "Buy";
		gotoXY(60, 18);
		std::cout << "Buy";
		gotoXY(60, 19);
		std::cout << "Buy";
		gotoXY(60, 21);
		std::cout << "Buy";

		// render cursor
		gotoXY(charLocation);
		colour(0x0C);
		std::cout << (char)17;

		// render options
		colour(0x0F);

		// render experience
		gotoXY(40, 1);
		std::cout << "Experience: " << expDefend;

		gotoXY(20, 7);
		std::cout << "Increase Magazine Size: " << pistolBulletUp;
		gotoXY(20, 8);
		std::cout << "Current Magazine Size: " << pistolCap;
		gotoXY(20, 9);
		std::cout << "Decrease Reload Time: " << pistolReloadDown;
		gotoXY(20, 10);
		std::cout << "Current Reload Time: " << pistolReload;
		gotoXY(20, 13);
		std::cout << "Increase Magazine Size: " << shotgunBulletUp;
		gotoXY(20, 14);
		std::cout << "Current Magazine Size: " << shotgunCap;
		gotoXY(20, 15);
		std::cout << "Decrease Reload Time: " << shotgunReloadDown;
		gotoXY(20, 16);
		std::cout << "Current Reload Time: " << shotgunReload;
		gotoXY(20, 19);
		std::cout << "Increase Magazine Size: " << mgunBulletUp;
		gotoXY(20, 20);
		std::cout << "Current Magazine Size: " << mgunCap;
		gotoXY(20, 21);
		std::cout << "Decrease Reload Time: " << mgunReloadDown;
		gotoXY(20, 22);
		std::cout << "Current Reload Time: " << mgunReload;
		//check if gun has been purchased
		gotoXY(34, 6);
		std::cout << "Unlocked!";
		gotoXY(34, 12);
		std::cout << ShotgunBought;
		gotoXY(34, 18);
		std::cout << MgunBought;
		gotoXY(73, 23);
	}
}

void updateDefendUpgrade(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

	if (keyPressed[K_DOWN])
	{
		if ( charLocation.Y == 7 )
		{
			Beep(1000, 100);
			charLocation.Y = 9;
		}
		else if ( charLocation.Y == 9 )
		{
			Beep(1000, 100);
			charLocation.Y = 12;
		}
		else if ( charLocation.Y == 12 )
		{
			Beep(1000, 100);
			charLocation.Y = 13;
		}
		else if ( charLocation.Y == 13 )
		{
			Beep(1000, 100);
			charLocation.Y = 15;
		}
		else if ( charLocation.Y == 15 )
		{
			Beep(1000, 100);
			charLocation.Y = 18;
		}
		else if ( charLocation.Y == 18 )
		{
			Beep(1000, 100);
			charLocation.Y = 19;
		}
		else if ( charLocation.Y == 19 )
		{
			Beep(1000, 100);
			charLocation.Y = 21;
		}
		else if ( charLocation.Y == 21 )
		{
			Beep(1000, 100);
			charLocation.Y = 23;
			charLocation.X = 74;
		}

		clsUpgrade = 0;
	}

	if (keyPressed[K_UP])
	{
		if ( charLocation.Y == 7 )
		{
		}
		else if ( charLocation.Y == 9 )
		{
			Beep(1000, 100);
			charLocation.Y = 7;
		}
		else if ( charLocation.Y == 12 )
		{
			Beep(1000, 100);
			charLocation.Y = 9;
		}
		else if ( charLocation.Y == 13 )
		{
			Beep(1000, 100);
			charLocation.Y = 12;
		}
		else if ( charLocation.Y == 15 )
		{
			Beep(1000, 100);
			charLocation.Y = 13;
		}
		else if ( charLocation.Y == 18 )
		{
			Beep(1000, 100);
			charLocation.Y = 15;
		}
		else if ( charLocation.Y == 19 )
		{
			Beep(1000, 100);
			charLocation.Y = 18;
		}
		else if ( charLocation.Y == 21 )
		{
			Beep(1000, 100);
			charLocation.Y = 19;
		}
		else if ( charLocation.Y = 23 )
		{
			Beep(1000, 100);
			charLocation.Y = 21;
			charLocation.X = 64;
		}

		clsUpgrade = 0;
	}

	if (keyPressed[K_ENTER] )
	{
		if ( charLocation.Y == 7 )
		{
			if ( expDefend >= 200 && pistolCap != 12)
			{
				Beep(4000, 100);
				expDefend -= 200;
				pistolCap += 2;
			}
			else
			{
				Beep(400, 100);
				Beep(200, 300);
			}
		}
		if ( charLocation.Y == 9 )
		{
			if ( expDefend >= 500 && pistolReload >= 1.6)
			{
				Beep(4000, 100);
				expDefend -= 500;
				pistolReload -= 0.3;
			}
			else
			{
				Beep(400, 100);
				Beep(200, 300);
			}
		}
		if ( charLocation.Y == 12 )
		{
			if ( expDefend >= 5000 && shotgunBought == 0)
			{
				Beep(4000, 100);
				expDefend -= 5000;
				ShotgunBought = "Unlocked!";
				shotgunBought = 1;
			}
			else
			{
				Beep(400, 100);
				Beep(200, 300);
			}
		}
		if ( charLocation.Y == 13 )
		{
			if ( expDefend >= 400 && shotgunCap != 6 && shotgunBought == 1 )
			{
				Beep(4000, 100);
				expDefend -= 400;
				shotgunCap += 2;
				
			}
			else
			{
				Beep(400, 100);
				Beep(200, 300);
			}
		}
		if ( charLocation.Y == 15 )
		{ 
			if ( expDefend >= 1000 && shotgunReload >= 2.0 && shotgunBought == 1 )
			{
				Beep(4000, 100);
				expDefend -= 1000;
				shotgunReload -= 0.5;
			}
			else
			{
				Beep(400, 100);
				Beep(200, 300);
			}
		}
		if ( charLocation.Y == 18 )
		{
			if ( expDefend >= 7500 && mgunBought == 0)
			{
				Beep(4000, 100);
				expDefend -= 7500;
				MgunBought = "Unlocked!";
				mgunBought = 1;
			}
			else
			{
				Beep(400, 100);
				Beep(200, 300);
			}
		}
		if ( charLocation.Y == 19 )
		{
			if ( expDefend >= 900 && mgunCap != 40 && mgunBought == 1 )
			{
				Beep(4000, 100);
				expDefend -= 900;
				mgunCap += 10;
				
			}
			else
			{
				Beep(400, 100);
				Beep(200, 300);
			}
		}
		if ( charLocation.Y == 21 )
		{ 
			if ( expDefend >= 1000 && mgunReload >= 4.0 && mgunBought == 1 )
			{
				Beep(4000, 100);
				expDefend -= 1000;
				mgunReload -= 1.0;
			}
			else
			{
				Beep(400, 100);
				Beep(200, 300);
			}
		}

		clsUpgrade = 0;

		if ( charLocation.Y == 23 )
		{
			Beep(4000, 100);
			numBullet.clear();
			charLocation.X = 69;
			charLocation.Y = 7;
			clsGame = 0;
			pistolMag = pistolCap;
			shotgunMag = shotgunCap;
			mgunMag = mgunCap;
			gamestate = DEFENDPLAY;
		}
	}

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
	{
		Beep(4000, 30);
		gamestate = DEFENDMENU;
	}

	if (keyPressed[K_X])
	{
	}
}

//TMB Functions
void flagcleared()
{
	Beep(392, 100);
	Beep(440, 100);
	Beep(493, 100);
	Beep(523, 100);
	Beep(567, 100);
	Beep(659, 100);
	Beep(698, 100);
	Beep(784, 100);
}

void initTMBMenu()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set character location
    charLocation.X = 29;
    charLocation.Y = 13;

    elapsedTime = 0.0;
}

void renderTMBMenu()
{
	// clear previous screen
	colour(0x0F);
    cls();

	// render time taken to calculate this frame
    gotoXY(70, 0);
    colour(0x1A);
    std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
    gotoXY(0, 0);
    colour(0x59);
    std::cout << elapsedTime << "secs" << std::endl;

	// render options
	colour(0x0F);

	gotoXY(30, 13);
	std::cout << "Play Too Many Bullets";

	gotoXY(30, 16);
	std::cout << "Instructions";

	gotoXY(30, 19);
	std::cout << "Title Screen";

	gotoXY(30, 22);
	std::cout << "High Scores";

	// render ASCII title screen
	gotoXY(1, 2);
	std::cout << "   ___   __  ______    _   ___  __   ____  __  ____    __    _________________";

	gotoXY(1, 3);
	std::cout << "  |__ \\ /  |/  /   |  / | / | \\/ /  / __ )/ / / / /   / /   / ____/_  __/ ___/";

	gotoXY(1, 4);
	std::cout << "  __/ // /|_/ / /| | /  |/ / \\  /  / __  / / / / /   / /   / __/   / /  \\__ \\ ";

	gotoXY(1, 5);
	std::cout << " / __// /  / / ___ |/ /|  /  / /  / /_/ / /_/ / /___/ /___/ /___  / /  ___/ / ";

	gotoXY(1, 6);
	std::cout << "/____/_/  /_/_/  |_/_/ |_/  /_/  /_____/\\____/_____/_____/_____/ /_/  /____/  ";

	// render cursor
    gotoXY(charLocation);
    colour(0x0C);
    std::cout << (char)16;

}

void updateTMBMenu(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

    // Updating the location of the cursor
    if (keyPressed[K_UP] && charLocation.Y != 13) // Move Up.
    {
        Beep(700, 30);
        charLocation.Y -= 3; 
    }

    if (keyPressed[K_DOWN] && charLocation.Y != 22) // Move Down.
    {
		Beep(700, 30);
		charLocation.Y += 3;
    }

	if (keyPressed[K_ENTER] )
	{
		Beep(4000, 30);
		if ( charLocation.Y == 16) // Instructions
			gamestate = TMBINSTRUCTION1;
		if ( charLocation.Y == 13) // Play!
			gamestate = TMBPLAY;
		if ( charLocation.Y == 19) // Exit to game title
			gamestate = MENU;
		if ( charLocation.Y == 22)
			gamestate = TMBHIGHSCORE;
	}

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
	{
		gotoXY(0, 1);
        g_quitGame = true;    
	}
}

void initTMBInstructions1()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set character location
    charLocation.X = 00;
    charLocation.Y = 00;
}

void renderTMBInstructions1()
{
	// clear previous screen
	colour(0x0F);
    cls();

	// render time taken to calculate this frame
    gotoXY(70, 0);
    colour(0x1A);
    std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
    gotoXY(0, 0);
    colour(0x59);
    std::cout << elapsedTime << "secs" << std::endl;

	// render options
	colour(0x0F);

	gotoXY(20, 2);
	std::cout << "Too Many Bullets Instructions: The Story";

	gotoXY(2, 4);
	std::cout << "It's the year 1337, and the surface of Earth as we know today has been fully";

	gotoXY(2, 5);
	std::cout << "submerged. Global warming has melted all the ice at the poles, and Earth is";

	gotoXY(2, 6);
	std::cout << "now completely blue.";

	gotoXY(2, 8);
	std::cout << "However, this did not bring about the extinction of mankind. With decades";

	gotoXY(2, 9);
	std::cout << "of researching, humans have finally managed to produce an energy-absorbing";

	gotoXY(2, 10);
	std::cout << "material known as Haxonite. With this material, mankind managed to create";

	gotoXY(2, 11);
	std::cout << "a vast network of floating islands, powered entirely by the sun. Population";

	gotoXY(2, 12);
	std::cout << "of man has dropped to a few millions, and there were no animals. Planes ";

	gotoXY(2, 13);
	std::cout << "and other aircrafts were your only means of travelling around. A country's";

	gotoXY(2, 14);
	std::cout << "strength was solely determined by the size of their Air Force.";

	gotoXY(2, 16);
	std::cout << "You are a madman, and you decide to start attacking others.";

	gotoXY(2, 17);
	std::cout << "Will you be able to destroy what is left of the humans?";

	gotoXY(30, 21);
	std::cout << "Press ENTER to return";

	gotoXY(65, 21);
	std::cout << " >NEXT";

}

void updateTMBInstructions1(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

    // Updating the location of the cursor
    if (keyPressed[K_RIGHT] ) // Page 2
    {
        Beep(700, 30);
        gamestate = TMBINSTRUCTION2;
    }

	if (keyPressed[K_ENTER] ) // Return to TMB! Menu
	{
		Beep(4000, 30);
		gamestate = TMBMENU;
	}

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
	{
		gotoXY(0, 1);
        g_quitGame = true;    
	}
}

void initTMBInstructions2()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set character location
    charLocation.X = 00;
    charLocation.Y = 00;
}

void renderTMBInstructions2()
{
	// clear previous screen
	colour(0x0F);
    cls();

	// render time taken to calculate this frame
    gotoXY(70, 0);
    colour(0x1A);
    std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
    gotoXY(0, 0);
    colour(0x59);
    std::cout << elapsedTime << "secs" << std::endl;


	// render options
	colour(0x0F);

	gotoXY(20, 2);
	std::cout << "Too Many Bullets Instructions:  Controls";

	gotoXY(1, 4);
	std::cout << "  _/^\\_   This is your plane. It's 3x3 big";

	gotoXY(1, 5);
	std::cout << "  >_X_<   But your hitbox is only the X in";

	gotoXY(1, 6);
	std::cout << "   '|`    the middle. So don't worry!";

	gotoXY(47, 4);
	colour(0x04);
	std::cout << "`";
	colour(0x0F);
	gotoXY(49, 4);
	std::cout << "This is a bullet. Don't let it";
	gotoXY(49, 5);
	std::cout << "touch the X in your plane!!";

	gotoXY(2, 8);
	std::cout << "LEFT Arrow Key  - Move Left        UP Arrow Key       - Move Up          ";

	gotoXY(2, 10);
	std::cout << "RIGHT Arrow Key - Move Right       DOWN Arrow Key     - Move Down        ";

	gotoXY(2, 12);
	std::cout << "==========================================================================";

	gotoXY(2, 14);
	std::cout << "Press SPACE to shoot. ";

	gotoXY(2, 16);
	std::cout << "Press the X key to detonate a bomb.";

	gotoXY(2, 17);
	std::cout <<"Bombs remove all bullets on the screen.";

	gotoXY(2, 21);
	std::cout << "PREVIOUS<";

	gotoXY(30, 21);
	std::cout << "Press ENTER to return";

	gotoXY(65, 21);
	std::cout << " >NEXT";

}

void updateTMBInstructions2(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

    // Updating the location of the cursor
    if (keyPressed[K_RIGHT] ) // Page 3
    {
        Beep(700, 30);
        gamestate = TMBINSTRUCTION3;
    }

	    if (keyPressed[K_LEFT] ) // Page 1
    {
        Beep(700, 30);
        gamestate = TMBINSTRUCTION1;
    }

	if (keyPressed[K_ENTER] ) // Return to TMB! Menu
	{
		Beep(4000, 30);
		gamestate = TMBMENU;
	}

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
	{
		gotoXY(0, 1);
        g_quitGame = true;    
	}
}

void initTMBInstructions3()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set character location
    charLocation.X = 00;
    charLocation.Y = 00;
}

void renderTMBInstructions3()
{
	// clear previous screen
	colour(0x0F);
    cls();

	// render time taken to calculate this frame
    gotoXY(70, 0);
    colour(0x1A);
    std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
    gotoXY(0, 0);
    colour(0x59);
    std::cout << elapsedTime << "secs" << std::endl;

	// render options
	colour(0x0F);

	gotoXY(20, 2);
	std::cout << "Too Many Bullets Instructions:  Monsters";

	gotoXY(2, 4);
	colour(0x02);
	std::cout << "     \\ . /      ";
	gotoXY(2, 5);
	std::cout << "o_____(*)_____o";

	gotoXY(2, 8);
	std::cout << "     __!__   ";
	gotoXY(2, 9);
	std::cout << "  -----o-----";
	gotoXY(2, 10);
	std::cout << "      " "    ";

	gotoXY(2, 12);
	std::cout << "      \\ /      ";
	gotoXY(2, 13);
	std::cout << "---==( o )==---";

	gotoXY(2, 16);
	std::cout << "     ?????     ";
	gotoXY(2, 17); 
	std::cout << "     ?????     ";
	gotoXY(2, 18);
	std::cout << "     ?????     ";

	colour(0x0F);
	gotoXY(20, 4);
	std::cout << " A basic drone that shoots bullet in a straight line.";
	gotoXY(20, 5); 
	std::cout << " Frequency and amount of bullets shot depends on level.";

	gotoXY(20, 8);
	std::cout << " A drone that shoots bullet in a small flower pattern.";
	gotoXY(20, 9); 
	std::cout << " Frequency of bullets depends on level.";

	gotoXY(20, 12);
	std::cout << " An annoying drone that shoots bullet in a circle.";
	gotoXY(20, 13); 
	std::cout << " Frequency and size of circle depends on level.";

	gotoXY(20, 16);
	std::cout << " Bosses shoot bullets based on patterns and health.";
	gotoXY(20, 17);
	std::cout << " Difficulty greatly increases with each boss. Good luck.";

	gotoXY(20, 19);
	std::cout << "Btw, you can only shoot the core of the monsters. (o & *)";

	gotoXY(2, 21);
	std::cout << "PREVIOUS<";

	gotoXY(30, 21);
	std::cout << "Press ENTER to return";

}

void updateTMBInstructions3(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

    // Updating the location of the cursor
    if (keyPressed[K_LEFT] ) // Page 2
    {
        Beep(700, 30);
		gamestate = TMBINSTRUCTION2;
         
    }

	if (keyPressed[K_ENTER] ) // Return to TMB! Menu
	{
		Beep(4000, 30);
		gamestate = TMBMENU;
	}

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
	{
		gotoXY(0, 1);
        g_quitGame = true;    
	}
}

void initTMB()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set character location
    charLocation.X = 30;
    charLocation.Y = 20;

    elapsedTime = 0.0;
	monsterShootDelay = 0.0;
	monster2ShootDelay = 0.0;
	monster3ShootDelay = 0.0;
	monster4ShootDelay = 0.0;

	stagehp = 1;
	bombsamtTMB = 5;
	livesamtTMB = 3;

	level1clear = 0;
	flag1clear = 0;
	flag2clear=0;
	flag3clear=0;
	flag4clear=0;
	flag5clear=0;
	flag6clear=0;
	flag7clear=0;
	flag8clear=0;
	flag9clear=0;
	flag10clear=0;
	level2clear = 0;
	level3clear = 0;
	level4clear = 0;

	//reset
	myBullets.clear();
	renderBullets.clear();
	monster1.clear();
	monster2.clear();
	monster3.clear();
	monsterBOSS.clear();
}

void renderTMB()
{
    // clear previous screen
    colour(0x0F);
    cls();

    //render the game
	//render walls
	for (int i = 0; i < 25; i++)
	{
		colour(0x02);
		gotoXY(0, i);
		std::cout << "||";
		gotoXY(78, i);
		std::cout << "||";
	}

	// render character
	colour(0x0C);
    gotoXY(charLocation.X-2, charLocation.Y-1);
    std::cout << "_/^\\_";
	gotoXY(charLocation.X-2, charLocation.Y);
	std::cout << ">_X_<" << std::endl;
	gotoXY(charLocation.X-1, charLocation.Y+1);
	std::cout << "'|`";

    // render time taken to calculate this frame
    gotoXY(70, 0);
    colour(0x1A);
    std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
    gotoXY(0, 0);
    colour(0x59);
    std::cout << elapsedTime << "secs" << std::endl;

	gotoXY(0, 1);
	std::cout << "Score: " << playerScoreTMB << std::endl;

	gotoXY(0, 2);
	std::cout << "Stage: " << stagehp << std::endl;

	gotoXY(0, 3);
	std::cout << "Wave: " << flagtrack << std::endl;

	gotoXY(0, 4);
	std::cout << "Bombs: " << bombsamtTMB << std::endl;

	gotoXY(0, 5);
	std::cout << "Lives: " << livesamtTMB << std::endl;

	if ( livesamtTMB <= 0 )
	{
		if ( playerScoreTMB > ScoreTMB10 )
		{
			updateHSTMB();
		}
		else
		{
			gameovernoHSTMB();
		}
	}

    // render bullets
    for ( unsigned int i = 0 ; i < renderBullets.size(); i+=2 )
	{
		colour(0x04);
		gotoXY(renderBullets[i], renderBullets[i+1]);
		std::cout << bullett;
		if ( renderBullets[i+1] >= 23 )
		{
			renderBullets.erase(renderBullets.begin());
			renderBullets.erase(renderBullets.begin());
			i -= 2;
		}
		else if ( renderBullets[i] == charLocation.X && renderBullets[i+1] == charLocation.Y )
		{
			renderBullets.erase(renderBullets.begin());
			renderBullets.erase(renderBullets.begin());
			i -= 2;
			--livesamtTMB;
		}
		else
		{
			++renderBullets[i+1];
		}
	}

	// render monster 1
	for ( unsigned int i = 0; i < monster1.size(); i+=3 )
	{
		colour(0x02);
		gotoXY(monster1[i]-1, monster1[i+1]-1);
		std::cout << "\\ . /" << std::endl;
		gotoXY(monster1[i]-6, monster1[i+1]);
		std::cout << "o_____(*)_____o";
		monstermovement = rand()%4; //randomize movement
		if ( monstermovement == 0 && monster1[i+1] > 2) //move up
			--monster1[i+1];
		else if ( monstermovement == 1 && monster1[i+1] < 15 ) //move down
			++monster1[i+1];
		else if ( monstermovement == 2 && monster1[i] < 70 ) //move right
			++monster1[i];
		else if ( monstermovement == 3 && monster1[i] > 10 ) //move left
			--monster1[i];

		if ( monsterShootDelay <= 0 ) //READY TO SHOOT
		{
			if ( level1clear == 0 ) //level 1 mob
			{
				for ( unsigned int j = 0; j < monster1.size(); j+=3 ) //all monsters shoot once
				{
					pattern5TMB(monster1[j], monster1[j+1]+1);
				}
					monsterShootDelay = 3.0;
			}
			else if ( level2clear == 0 ) //level 2 mob
			{
				for ( unsigned int j = 0; j < monster1.size(); j+=3 ) //all monsters shoot once
				{
					pattern5TMB(monster1[i]-1, monster1[i+1]+1);
					pattern5TMB(monster1[i]+1, monster1[i+1]+1);
				}
				
				monsterShootDelay = 2.5;
			}
			else if ( level2clear == 0 ) //level 3 mob
			{
				for ( unsigned int j = 0; j < monster1.size(); j+=3 ) //all monsters shoot once
				{
					pattern5TMB(monster1[i]-3, monster1[i+1]+1);
					pattern5TMB(monster1[i]-1, monster1[i+1]+1);
					pattern5TMB(monster1[i]+1, monster1[i+1]+1);
					pattern5TMB(monster1[i]+3, monster1[i+1]+1);
				}
				
				monsterShootDelay = 2.0;
			}
			else if ( level2clear == 0 ) //level 4 mob
			{
				for ( unsigned int j = 0; j < monster1.size(); j+=3 ) //all monsters shoot once
				{
					pattern5TMB(monster1[i]-5, monster1[i+1]+1);
					pattern5TMB(monster1[i]-3, monster1[i+1]+1);
					pattern5TMB(monster1[i]-1, monster1[i+1]+1);
					pattern5TMB(monster1[i]+1, monster1[i+1]+1);
					pattern5TMB(monster1[i]+3, monster1[i+1]+1);
					pattern5TMB(monster1[i]+5, monster1[i+1]+1);
				}
				
				monsterShootDelay = 1.5;
			}
			else if ( level2clear == 0 ) //level 5 mob
			{
				for ( unsigned int j = 0; j < monster1.size(); j+=3 ) //all monsters shoot once
				{
					pattern5TMB(monster1[i]-7, monster1[i+1]+1);
					pattern5TMB(monster1[i]-5, monster1[i+1]+1);
					pattern5TMB(monster1[i]-3, monster1[i+1]+1);
					pattern5TMB(monster1[i]-1, monster1[i+1]+1);
					pattern5TMB(monster1[i]+1, monster1[i+1]+1);
					pattern5TMB(monster1[i]+3, monster1[i+1]+1);
					pattern5TMB(monster1[i]+5, monster1[i+1]+1);
					pattern5TMB(monster1[i]+7, monster1[i+1]+1);
				}
				
				monsterShootDelay = 1.0;
			}
		}
	}

	//render monster 2
	for ( unsigned int i = 0; i < monster2.size(); i+=3 )
	{
		colour(0x02);
		gotoXY(monster2[i]-3, monster2[i+1]-1);
		std::cout << "__!__" << std::endl;
		gotoXY(monster2[i]-6, monster2[i+1]);
		std::cout << "-----o-----";
		monstermovement = rand()%4; //randomize movement
		if ( monstermovement == 0 && monster2[i+1] > 2) //move up
			--monster2[i+1];
		else if ( monstermovement == 1 && monster2[i+1] < 15 ) //move down
			++monster2[i+1];
		else if ( monstermovement == 2 && monster2[i] < 70 ) //move right
			++monster2[i];
		else if ( monstermovement == 3 && monster2[i] > 10 ) //move left
			--monster2[i];

		if ( monster2ShootDelay <= 0 ) //READY TO SHOOT
		{
			if ( level1clear == 0 ) //level 1 mob
			{
				for ( unsigned int j = 0; j < monster2.size(); j+=3 ) //all monsters shoot once
				{
					pattern1TMB(monster2[j], monster2[j+1]+2);
				}
					monster2ShootDelay = 3.0;
			}
			else if ( level2clear == 0 ) //level 2 mob
			{
				for ( unsigned int j = 0; j < monster2.size(); j+=3 ) //all monsters shoot once
				{
					pattern1TMB(monster2[i]-3, monster2[i+1]+2);
					pattern1TMB(monster2[i]+3, monster2[i+1]+2);
				}
				
				monster2ShootDelay = 2.5;
			}
			else if ( level2clear == 0 ) //level 3 mob
			{
				for ( unsigned int j = 0; j < monster2.size(); j+=3 ) //all monsters shoot once
				{
					pattern1TMB(monster2[i]-6, monster2[i+1]+2);
					pattern1TMB(monster2[i]-3, monster2[i+1]+2);
					pattern1TMB(monster2[i]+3, monster2[i+1]+2);
					pattern1TMB(monster2[i]+6, monster2[i+1]+2);
				}
				
				monster2ShootDelay = 2.0;
			}
			else if ( level2clear == 0 ) //level 4 mob
			{
				for ( unsigned int j = 0; j < monster2.size(); j+=3 ) //all monsters shoot once
				{
					pattern1TMB(monster2[i]-6, monster2[i+1]+2);
					pattern1TMB(monster2[i]-3, monster2[i+1]+2);
					pattern1TMB(monster2[i]+3, monster2[i+1]+2);
					pattern1TMB(monster2[i]+6, monster2[i+1]+2);
					pattern1TMB(monster2[i]-3, monster2[i+1]+4);
					pattern1TMB(monster2[i]+3, monster2[i+1]+4);
				}
				
				monster2ShootDelay = 1.5;
			}
			else if ( level2clear == 0 ) //level 5 mob
			{
				for ( unsigned int j = 0; j < monster2.size(); j+=3 ) //all monsters shoot once
				{
					pattern1TMB(monster2[i]-6, monster2[i+1]+2);
					pattern1TMB(monster2[i]-3, monster2[i+1]+2);
					pattern1TMB(monster2[i]+3, monster2[i+1]+2);
					pattern1TMB(monster2[i]+6, monster2[i+1]+2);
					pattern1TMB(monster2[i]-6, monster2[i+1]+4);
					pattern1TMB(monster2[i]-3, monster2[i+1]+4);
					pattern1TMB(monster2[i]+3, monster2[i+1]+4);
					pattern1TMB(monster2[i]+6, monster2[i+1]+4);
				}
				
				monster2ShootDelay = 1.0;
			}
		}
	}

	//render monster 3
	for ( unsigned int i = 0; i < monster3.size(); i+=3 )
	{
		colour(0x02);
		gotoXY(monster3[i]-1, monster3[i+1]-1);
		std::cout << "\\ /" << std::endl;
		gotoXY(monster3[i]-7, monster3[i+1]);
		std::cout << "---==( o )==---";
		monstermovement = rand()%4; //randomize movement
		if ( monstermovement == 0 && monster3[i+1] > 2) //move up
			--monster3[i+1];
		else if ( monstermovement == 1 && monster3[i+1] < 15 ) //move down
			++monster3[i+1];
		else if ( monstermovement == 2 && monster3[i] < 70 ) //move right
			++monster3[i];
		else if ( monstermovement == 3 && monster3[i] > 10 ) //move left
			--monster3[i];

		if ( monster3ShootDelay <= 0 ) //READY TO SHOOT
		{
			if ( level1clear == 0 ) //level 1 mob
			{
				for ( unsigned int j = 0; j < monster3.size(); j+=3 ) //all monsters shoot once
				{
					pattern2TMB(monster3[j], monster3[j+1]+2);
				}
					monster3ShootDelay = 3.0;
			}
			else if ( level2clear == 0 ) //level 2 mob
			{
				for ( unsigned int j = 0; j < monster3.size(); j+=3 ) //all monsters shoot once
				{
					pattern2TMB(monster3[i]-3, monster3[i+1]+2);
					pattern2TMB(monster3[i]+3, monster3[i+1]+2);
				}
				
				monster3ShootDelay = 2.5;
			}
			else if ( level2clear == 0 ) //level 3 mob
			{
				for ( unsigned int j = 0; j < monster3.size(); j+=3 ) //all monsters shoot once
				{
					pattern2TMB(monster3[i]-6, monster3[i+1]+2);
					pattern2TMB(monster3[i]-3, monster3[i+1]+2);
					pattern2TMB(monster3[i]+3, monster3[i+1]+2);
					pattern2TMB(monster3[i]+6, monster3[i+1]+2);
				}
				
				monster3ShootDelay = 2.0;
			}
			else if ( level2clear == 0 ) //level 4 mob
			{
				for ( unsigned int j = 0; j < monster3.size(); j+=3 ) //all monsters shoot once
				{
					pattern2TMB(monster3[i]-6, monster3[i+1]+2);
					pattern2TMB(monster3[i]-3, monster3[i+1]+2);
					pattern2TMB(monster3[i]+3, monster3[i+1]+2);
					pattern2TMB(monster3[i]+6, monster3[i+1]+2);
				}
				
				monster3ShootDelay = 1.5;
			}
			else if ( level2clear == 0 ) //level 5 mob
			{
				for ( unsigned int j = 0; j < monster3.size(); j+=3 ) //all monsters shoot once
				{
					pattern2TMB(monster3[i]-6, monster3[i+1]+2);
					pattern2TMB(monster3[i]-3, monster3[i+1]+2);
					pattern2TMB(monster3[i]+3, monster3[i+1]+2);
					pattern2TMB(monster3[i]+6, monster3[i+1]+2);
				}
				
				monster3ShootDelay = 1.0;
			}
		}
	}

	// Render the boss :D
	for ( unsigned int i = 0; i < monsterBOSS.size(); i+=3 )
	{
		colour(0x02);
		gotoXY(monsterBOSS[i]-5, monsterBOSS[i+1]-1);
		std::cout << "\\    _    /" << std::endl;
		gotoXY(monsterBOSS[i]-14, monsterBOSS[i+1]);
		std::cout << "*__________\\_(0)_/__________*" << std::endl;
		gotoXY(monsterBOSS[i]-10, monsterBOSS[i+1]+1);
		std::cout << "@  @  (](_o_)[)  @  @" << std::endl;
		gotoXY(monsterBOSS[i]-3, monsterBOSS[i+1]+2);
		std::cout << "o     o";

		monstermovement = rand()%4; //randomize movement
		if ( monstermovement == 0 && monsterBOSS[i+1] > 3) //move up
			--monsterBOSS[i+1];
		else if ( monstermovement == 1 && monsterBOSS[i+1] < 6 ) //move down
			++monsterBOSS[i+1];
		else if ( monstermovement == 2 && monsterBOSS[i] < 50 ) //move right
			++monsterBOSS[i];
		else if ( monstermovement == 3 && monsterBOSS[i] > 30 ) //move left
			--monsterBOSS[i];

		if ( monster4ShootDelay <= 0 ) //READY TO SHOOT
		{
			if ( level1clear == 0 ) //level 1 mob
			{
				for ( unsigned int j = 0; j < monsterBOSS.size(); j+=3 ) //all monsters shoot once
				{
					pattern4TMB(monsterBOSS[j], monsterBOSS[j+1]+3);
				}
					monster4ShootDelay = 3.0;
			}
			else if ( level2clear == 0 ) //level 2 mob
			{
				for ( unsigned int j = 0; j < monsterBOSS.size(); j+=3 ) //all monsters shoot once
				{
					pattern4TMB(monsterBOSS[j]-4, monsterBOSS[j+1]+3);
					pattern4TMB(monsterBOSS[j]+4, monsterBOSS[j+1]+3);
				}
				
				monster4ShootDelay = 2.5;
			}
			else if ( level2clear == 0 ) //level 3 mob
			{
				for ( unsigned int j = 0; j < monsterBOSS.size(); j+=3 ) //all monsters shoot once
				{
					pattern4TMB(monsterBOSS[j]-8, monsterBOSS[j+1]+3);
					pattern4TMB(monsterBOSS[j]-4, monsterBOSS[j+1]+3);
					pattern4TMB(monsterBOSS[j]+4, monsterBOSS[j+1]+3);
					pattern4TMB(monsterBOSS[j]+8, monsterBOSS[j+1]+3);
				}
				
				monster4ShootDelay = 2.0;
			}
			else if ( level2clear == 0 ) //level 4 mob
			{
				for ( unsigned int j = 0; j < monsterBOSS.size(); j+=3 ) //all monsters shoot once
				{
					pattern4TMB(monsterBOSS[j]-12, monsterBOSS[j+1]+3);
					pattern4TMB(monsterBOSS[j]-8, monsterBOSS[j+1]+3);
					pattern4TMB(monsterBOSS[j]-4, monsterBOSS[j+1]+3);
					pattern4TMB(monsterBOSS[j]+4, monsterBOSS[j+1]+3);
					pattern4TMB(monsterBOSS[j]+8, monsterBOSS[j+1]+3);
					pattern4TMB(monsterBOSS[j]+12, monsterBOSS[j+1]+3);
				}
				
				monster4ShootDelay = 1.5;
			}
			else if ( level2clear == 0 ) //level 5 mob
			{
				for ( unsigned int j = 0; j < monsterBOSS.size(); j+=3 ) //all monsters shoot once
				{
					pattern4TMB(monsterBOSS[j]-16, monsterBOSS[j+1]+3);
					pattern4TMB(monsterBOSS[j]-12, monsterBOSS[j+1]+3);
					pattern4TMB(monsterBOSS[j]-8, monsterBOSS[j+1]+3);
					pattern4TMB(monsterBOSS[j]-4, monsterBOSS[j+1]+3);
					pattern4TMB(monsterBOSS[j]+4, monsterBOSS[j+1]+3);
					pattern4TMB(monsterBOSS[j]+8, monsterBOSS[j+1]+3);
					pattern4TMB(monsterBOSS[j]+12, monsterBOSS[j+1]+3);
					pattern4TMB(monsterBOSS[j]+16, monsterBOSS[j+1]+3);
				}
				
				monster4ShootDelay = 1.0;
			}
		}
	}


	//render character's bullets

	for ( unsigned int i = 0; i < myBullets.size(); i+=2 )
	{
		colour(0x08);
		gotoXY(myBullets[i], myBullets[i+1]);
		if ( myBullets[i+1] < 0 ) //out of bounds
		{
			myBullets.erase(myBullets.begin());
			myBullets.erase(myBullets.begin());
			i -= 2;
			playerScoreTMB -= 1;
		}
		else
		{
			std::cout << mybullett;
			--myBullets[i+1];
		}
	}

	//check if character's bullets hit monster1

	for ( unsigned int i = 0; i + 1 < myBullets.size(); i += 2 )
	{
		for ( unsigned int j = 0; j + 1 < monster1.size(); j += 3 ) // Check if bullet hits a monster
		{
			if ( ( myBullets[i] == monster1[j] || myBullets[i]+1 == monster1[j] || myBullets[i]+2 == monster1[j] || myBullets[i]-1 == monster1[j] || myBullets[i]-2 == monster1[j] ) && myBullets[i+1] == monster1[j+1] ) // Hit!
			{
				// Remove bullet that hit
				myBullets.erase (myBullets.begin() + i); 
				myBullets.erase (myBullets.begin() + i);
				if ( monster1[j+2] <= 0 ) //no more HP
				{
				//Remove monster that died
				monster1.erase (monster1.begin() + j);
				monster1.erase (monster1.begin() + j); 
				monster1.erase (monster1.begin() + j); 
				playerScoreTMB += 250;
				}
				else
				{
					--monster1[j+2];
				}
				//Reset loop
				
				i = 0;
				j = 0;
			}
		}
	}

	//check if character's bullets hit monster2

	for ( unsigned int i = 0; i + 1 < myBullets.size(); i += 2 )
	{
		for ( unsigned int j = 0; j + 1 < monster2.size(); j += 3 ) // Check if bullet hits a monster
		{
			if ( ( myBullets[i] == monster2[j] || myBullets[i]+1 == monster2[j] || myBullets[i]+2 == monster2[j] || myBullets[i]-1 == monster2[j] || myBullets[i]-2 == monster2[j] ) && myBullets[i+1] == monster2[j+1] ) // Hit!
			{
				// Remove bullet that hit
				myBullets.erase (myBullets.begin() + i); 
				myBullets.erase (myBullets.begin() + i);
				if ( monster2[j+2] <= 0 ) //no more HP
				{
				//Remove monster that died
				monster2.erase (monster2.begin() + j);
				monster2.erase (monster2.begin() + j); 
				monster2.erase (monster2.begin() + j); 
				playerScoreTMB += 250;
				}
				else
				{
					--monster2[j+2];
				}
				//Reset loop
				
				i = 0;
				j = 0;
			}
		}
	}

	//check if character's bullets hit monster3

	for ( unsigned int i = 0; i + 1 < myBullets.size(); i += 2 )
	{
		for ( unsigned int j = 0; j + 1 < monster3.size(); j += 3 ) // Check if bullet hits a monster
		{
			if ( ( myBullets[i] == monster3[j] || myBullets[i]+1 == monster3[j] || myBullets[i]+2 == monster3[j] || myBullets[i]-1 == monster3[j] || myBullets[i]-2 == monster3[j] ) && myBullets[i+1] == monster3[j+1] ) // Hit!
			{
				// Remove bullet that hit
				myBullets.erase (myBullets.begin() + i); 
				myBullets.erase (myBullets.begin() + i);
				if ( monster3[j+2] <= 0 ) //no more HP
				{
				//Remove monster that died
				monster3.erase (monster3.begin() + j);
				monster3.erase (monster3.begin() + j); 
				monster3.erase (monster3.begin() + j); 
				playerScoreTMB += 250;
				}
				else
				{
					--monster3[j+2];
				}
				//Reset loop
				
				i = 0;
				j = 0;
			}
		}
	}

	
	//render boss HP bar
	if ( monsterBOSS.size() > 1 ) //boss exists
	{
		maxbosshpTMB = 0;
		if ( maxbosshpTMB == 0 )
		{
			maxbosshpTMB = monsterBOSS[2];
		}
		colour(0x0F);
		gotoXY(10, consoleSize.Y-1);
		std::cout << "Boss HP: ";
		gotoXY(20, consoleSize.Y-1);
		std::cout << "#" << bossHPbar;
		if ( bossdamagedTMB >= maxbosshpTMB/20 )
		{
			bossdamagedTMB = 0;
			if( bossHPbar.size() != 0 )
				bossHPbar.pop_back();
		}
	}

	if ( monsterBOSS.size() == 0 )
		bossHPbar = "####################";

	//check if bullet hits the boss -w-

	for ( unsigned int i = 0; i + 1 < myBullets.size(); i += 2 )
	{
		for ( unsigned int j = 0; j + 1 < monsterBOSS.size(); j += 3 ) // Check if bullet hits a monster
		{
			if ( ( myBullets[i] == monsterBOSS[j] || myBullets[i]+1 == monsterBOSS[j] || myBullets[i]+2 == monsterBOSS[j] || myBullets[i]-1 == monsterBOSS[j] || myBullets[i]-2 == monsterBOSS[j] ) && myBullets[i+1] == monsterBOSS[j+1] ) // Hit!
			{
				// Remove bullet that hit
				myBullets.erase (myBullets.begin() + i); 
				myBullets.erase (myBullets.begin() + i);
				bossdamagedTMB++;
				if ( monsterBOSS[j+2] <= 0 ) //no more HP
				{
				//Remove monster that died
				monsterBOSS.clear();
				playerScoreTMB += 5000;
				}
				else
				{
					Beep(4000, 30);
					--monsterBOSS[j+2];
				}
				//Reset loop
				
				i = 0;
				j = 0;
			}
		}
	}
    
}

void updateTMB(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;
	monsterShootDelay -= dt;
	monster2ShootDelay -= dt;
	monster3ShootDelay -= dt;
	monster4ShootDelay -= dt;

	stagehp = 1; //Stage 1.
	if ( elapsedTime > 3.0 && flag1clear == 0)
	{
		monster1TMB(10, 5);
		monster1TMB(23, 8);
		flag1clear = 1;
		flagtrack++;
	}
	if ( monster1.size() == 0 && flagtrack == 1 )
	{
		renderBullets.clear();
		myBullets.clear();
		flagcleared();
		flag2clear = 2;
	}
	//flag2
	if ( flag2clear == 2 )
	{
		monster1TMB(10, 5);
		monster1TMB(23, 8);
		monster1TMB(37, 11);
		monster1TMB(50, 5);
		flag2clear = 1;
		flagtrack++;
	}
	if ( monster1.size() == 0 && flagtrack == 2 )
	{
		renderBullets.clear();
		myBullets.clear();
		flagcleared();
		flag3clear = 3;
	}
	//flag3
	if ( flag3clear == 3 )
	{
		monster1TMB(10, 5);
		monster2TMB(23, 8);
		monster1TMB(37, 11);
		monster1TMB(50, 5);
		flag3clear = 2;
		flagtrack++;
	}
	if ( monster1.size() == 0 && monster2.size() == 0 && flagtrack == 3 )
	{
		renderBullets.clear();
		myBullets.clear();
		flagcleared();
		flag4clear = 4;
	}
	//flag4
	if ( flag4clear == 4 )
	{
		monster1TMB(10, 5);
		monster2TMB(23, 8);
		monster2TMB(37, 11);
		monster2TMB(50, 5);
		flag4clear = 3;
		flagtrack++;
	}
	if ( monster1.size() == 0 && monster2.size() == 0 && flagtrack == 4 )
	{
		renderBullets.clear();
		myBullets.clear();
		flagcleared();
		flag5clear = 5;
	}
	//flag5
	if ( flag5clear == 5 )
	{
		monster1TMB(10, 5);
		monster2TMB(23, 8);
		monster2TMB(37, 11);
		monster3TMB(50, 5);
		flag5clear = 4;
		flagtrack++;
	}
	if ( monster1.size() == 0 && monster2.size() == 0 && monster3.size() == 0 && flagtrack == 5 )
	{
		renderBullets.clear();
		myBullets.clear();
		flagcleared();
		flag6clear = 6;
	}
	//flag6
	if ( flag6clear == 6 )
	{
		monster1TMB(10, 5);
		monster1TMB(10, 10);
		monster2TMB(23, 8);
		monster3TMB(37, 11);
		monster3TMB(50, 5);
		flag6clear = 5;
		flagtrack++;
	}
	if ( monster1.size() == 0 && monster2.size() == 0 && monster3.size() == 0 && flagtrack == 6 )
	{
		renderBullets.clear();
		myBullets.clear();
		flagcleared();
		flag7clear = 7;
	}
	//flag7
	if ( flag7clear == 7 )
	{
		monster2TMB(10, 5);
		monster2TMB(10, 10);
		monster2TMB(23, 8);
		monster3TMB(37, 11);
		monster3TMB(50, 5);
		flag7clear = 6;
		flagtrack++;
	}
	if ( monster2.size() == 0 && monster3.size() == 0 && flagtrack == 7 )
	{
		renderBullets.clear();
		myBullets.clear();
		flagcleared();
		flag8clear = 8;
	}
	//flag8
	if ( flag8clear == 8 )
	{
		monster3TMB(23, 8);
		monster3TMB(37, 11);
		monster3TMB(50, 5);
		flag8clear = 7;
		flagtrack++;
	}
	if ( monster3.size() == 0 && flagtrack == 8 )
	{
		renderBullets.clear();
		myBullets.clear();
		flagcleared();
		flag9clear = 9;
	}
	//flag9
	if ( flag9clear == 9 )
	{
		monster3TMB(23, 8);
		monster3TMB(37, 11);
		monster3TMB(50, 5);
		monster3TMB(10, 7);
		flag9clear = 8;
		flagtrack++;
	}
	if ( monster3.size() == 0 && flagtrack == 9 )
	{
		renderBullets.clear();
		myBullets.clear();
		flagcleared();
		flag10clear = 10;
	}
	if ( flag10clear == 10 )
	{
		monsterBOSSTMB(30, 5);
		flag10clear = 9;
		flagtrack++;
	}
	if ( monsterBOSS.size() == 0 && flagtrack == 10 )
	{

		renderBullets.clear();
		myBullets.clear();
		flagcleared();
		flagcleared();
		++stagehp;
		flag1clear = 0;
		flagtrack = 0;
	}

    // Updating the location of the character based on the key press
    if (keyPressed[K_UP] && charLocation.Y > 17)
    {
        Beep(1440, 30);
        charLocation.Y--; 
    }
    if (keyPressed[K_LEFT] && charLocation.X > 5)
    {
        Beep(1440, 30);
        charLocation.X--; 
    }
    if (keyPressed[K_DOWN] && charLocation.Y < consoleSize.Y - 2)
    {
        Beep(1440, 30);
        charLocation.Y++; 
    }
    if (keyPressed[K_RIGHT] && charLocation.X < consoleSize.X - 5)
    {
        Beep(1440, 30);
        charLocation.X++; 
    }
	if (keyPressed[K_H])
	{
		monsterBOSSTMB(20, 5);
	}
	if (keyPressed[K_X])
	{
		if( bombsamtTMB > 0 )
		{
			Beep(250, 200);
			Beep(120, 500);
			renderBullets.clear();
			--bombsamtTMB;
			playerScoreTMB -= 2500;
		}

	}
	if (keyPressed[K_SPACE])
	{
		Beep(569, 30);
		myBullets.push_back(charLocation.X);
		myBullets.push_back(charLocation.Y-2);
	}

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
        gamestate = TMBMENU;    
}

void characterTMB(int posX, int posY)
{
	colour(0x0F);
	gotoXY(posX-2, posY-1);
	std::cout << "_/^\\_";
	gotoXY(posX-2, posY);
	std::cout << ">_X_<";
	gotoXY(posX-1, posY+1);
	std::cout << "'|`"; 

}

void monster1TMB(int posX, int posY)
{
	monster1.push_back(posX);
	monster1.push_back(posY);
	monster1.push_back(stagehp);

}

void monster2TMB(int posX, int posY)
{
	monster2.push_back(posX);
	monster2.push_back(posY);
	monster2.push_back(stagehp);
}

void monster3TMB(int posX, int posY)
{
	monster3.push_back(posX);
	monster3.push_back(posY);
	monster3.push_back(stagehp);
}

void monsterBOSSTMB(int posX, int posY)
{
	monsterBOSS.push_back(posX);
	monsterBOSS.push_back(posY);
	monsterBOSS.push_back(stagehp*40);
}

void pattern1TMB(int posX, int posY)
{
	renderBullets.push_back(posX);
	renderBullets.push_back(posY+1);
	renderBullets.push_back(posX-1);
	renderBullets.push_back(posY);
	renderBullets.push_back(posX+1);
	renderBullets.push_back(posY);
	renderBullets.push_back(posX);
	renderBullets.push_back(posY-1);

}

void pattern2TMB(int posX, int posY)
{
	renderBullets.push_back(posX-1);
	renderBullets.push_back(posY-2);
	renderBullets.push_back(posX);
	renderBullets.push_back(posY-2);
	renderBullets.push_back(posX+1);
	renderBullets.push_back(posY-2);
	renderBullets.push_back(posX-2);
	renderBullets.push_back(posY-1);
	renderBullets.push_back(posX+2);
	renderBullets.push_back(posY-1);
	renderBullets.push_back(posX-2);
	renderBullets.push_back(posY);
	renderBullets.push_back(posX+2);
	renderBullets.push_back(posY);
	renderBullets.push_back(posX-2);
	renderBullets.push_back(posY+1);
	renderBullets.push_back(posX+2);
	renderBullets.push_back(posY+1);
	renderBullets.push_back(posX-1);
	renderBullets.push_back(posY+2);
	renderBullets.push_back(posX);
	renderBullets.push_back(posY+2);
	renderBullets.push_back(posX+1);
	renderBullets.push_back(posY+2);

}

void pattern3TMB(int posX, int posY)
{
	renderBullets.push_back(posX-3);
	renderBullets.push_back(posY+1);
	renderBullets.push_back(posX);
	renderBullets.push_back(posY+1);
	renderBullets.push_back(posX+3);
	renderBullets.push_back(posY+1);
	renderBullets.push_back(posX-2);
	renderBullets.push_back(posY);
	renderBullets.push_back(posX-1);
	renderBullets.push_back(posY);
	renderBullets.push_back(posX+1);
	renderBullets.push_back(posY);
	renderBullets.push_back(posX+2);
	renderBullets.push_back(posY);

}

void pattern4TMB(int posX, int posY)
{
	renderBullets.push_back(posX-7);
	renderBullets.push_back(posY-3);
	renderBullets.push_back(posX-4);
	renderBullets.push_back(posY-3);
	renderBullets.push_back(posX);
	renderBullets.push_back(posY-3);
	renderBullets.push_back(posX+4);
	renderBullets.push_back(posY-3);
	renderBullets.push_back(posX+7);
	renderBullets.push_back(posY-3);
	renderBullets.push_back(posX-4);
	renderBullets.push_back(posY-1);
	renderBullets.push_back(posX-2);
	renderBullets.push_back(posY-1);
	renderBullets.push_back(posX+2);
	renderBullets.push_back(posY-1);
	renderBullets.push_back(posX+4);
	renderBullets.push_back(posY-1);
	renderBullets.push_back(posX-4);
	renderBullets.push_back(posY+1);
	renderBullets.push_back(posX-4);
	renderBullets.push_back(posY+1);
	renderBullets.push_back(posX);
	renderBullets.push_back(posY+1);
	renderBullets.push_back(posX+6);
	renderBullets.push_back(posY+1);
	renderBullets.push_back(posX+8);
	renderBullets.push_back(posY+1);
	renderBullets.push_back(posX-7);
	renderBullets.push_back(posY+3);
	renderBullets.push_back(posX-3);
	renderBullets.push_back(posY+3);
	renderBullets.push_back(posX+4);
	renderBullets.push_back(posY+3);
	renderBullets.push_back(posX+8);
	renderBullets.push_back(posY+3);
}

void pattern5TMB(int posX, int posY)
{
	renderBullets.push_back(posX);
	renderBullets.push_back(posY+1);
	renderBullets.push_back(posX);
	renderBullets.push_back(posY+2);
}

void gameovernoHSTMB()
{
	Beep(784, 100);//show score and ask user to return
	Beep(698, 100);
	Beep(659, 100);
	Beep(567, 100);
	Beep(523, 100);
	Beep(493, 100);
	Beep(440, 100);
	Beep(392, 100);
	gamestate = TMBGAMEOVER;
}

void updateHSTMB()
{

	int Ranking = 11;
	if ( playerScoreTMB > ScoreTMB1 ) // 1
		Ranking = 1;
	if ( playerScoreTMB > ScoreTMB2 && Ranking == 11) // 2
		Ranking = 2;
	if ( playerScoreTMB > ScoreTMB3 && Ranking == 11) // 3
		Ranking = 3;
	if ( playerScoreTMB > ScoreTMB4 && Ranking == 11) // 4
		Ranking = 4;
	if ( playerScoreTMB > ScoreTMB5 && Ranking == 11) // 5
		Ranking = 5;
	if ( playerScoreTMB > ScoreTMB6 && Ranking == 11) // 6
		Ranking = 6;
	if ( playerScoreTMB > ScoreTMB7 && Ranking == 11) // 7
		Ranking = 7;
	if ( playerScoreTMB > ScoreTMB8 && Ranking == 11) // 8
		Ranking = 8;
	if ( playerScoreTMB > ScoreTMB9 && Ranking == 11) // 9
		Ranking = 9;
	if ( playerScoreTMB > ScoreTMB10 && Ranking == 11) // 10
		Ranking = 10;
	// Ranking = your rank ~~
	if ( Ranking == 1 )
	{
		ScoreTMB10 = ScoreTMB9;
		ScoreTMB10N = ScoreTMB9N;

		ScoreTMB9 = ScoreTMB8;
		ScoreTMB9N = ScoreTMB8N;

		ScoreTMB8 = ScoreTMB7;
		ScoreTMB8N = ScoreTMB7N;

		ScoreTMB7 = ScoreTMB6;
		ScoreTMB7N = ScoreTMB6N;

		ScoreTMB6 = ScoreTMB5;
		ScoreTMB6N = ScoreTMB5N;

		ScoreTMB5 = ScoreTMB4;
		ScoreTMB5N = ScoreTMB4N;

		ScoreTMB4 = ScoreTMB3;
		ScoreTMB4N = ScoreTMB3N;

		ScoreTMB3 = ScoreTMB2;
		ScoreTMB3N = ScoreTMB2N;

		ScoreTMB2 = ScoreTMB1;
		ScoreTMB2N = ScoreTMB1N;

		ScoreTMB1 = playerScoreTMB;
		ScoreTMB1N = playerName;
	}
	else if ( Ranking == 2 )
	{

		ScoreTMB10 = ScoreTMB9;
		ScoreTMB10N = ScoreTMB9N;

		ScoreTMB9 = ScoreTMB8;
		ScoreTMB9N = ScoreTMB8N;

		ScoreTMB8 = ScoreTMB7;
		ScoreTMB8N = ScoreTMB7N;

		ScoreTMB7 = ScoreTMB6;
		ScoreTMB7N = ScoreTMB6N;

		ScoreTMB6 = ScoreTMB5;
		ScoreTMB6N = ScoreTMB5N;

		ScoreTMB5 = ScoreTMB4;
		ScoreTMB5N = ScoreTMB4N;

		ScoreTMB4 = ScoreTMB3;
		ScoreTMB4N = ScoreTMB3N;

		ScoreTMB3 = ScoreTMB2;
		ScoreTMB3N = ScoreTMB2N;

		ScoreTMB2 = playerScoreTMB;
		ScoreTMB2N = playerName;
	}
	else if ( Ranking == 3 )
	{
		ScoreTMB10 = ScoreTMB9;
		ScoreTMB10N = ScoreTMB9N;

		ScoreTMB9 = ScoreTMB8;
		ScoreTMB9N = ScoreTMB8N;

		ScoreTMB8 = ScoreTMB7;
		ScoreTMB8N = ScoreTMB7N;

		ScoreTMB7 = ScoreTMB6;
		ScoreTMB7N = ScoreTMB6N;

		ScoreTMB6 = ScoreTMB5;
		ScoreTMB6N = ScoreTMB5N;

		ScoreTMB5 = ScoreTMB4;
		ScoreTMB5N = ScoreTMB4N;

		ScoreTMB4 = ScoreTMB3;
		ScoreTMB4N = ScoreTMB3N;

		ScoreTMB3 = playerScoreTMB;
		ScoreTMB3N = playerName;
	}
	else if ( Ranking == 4 )
	{
		ScoreTMB10 = ScoreTMB9;
		ScoreTMB10N = ScoreTMB9N;

		ScoreTMB9 = ScoreTMB8;
		ScoreTMB9N = ScoreTMB8N;

		ScoreTMB8 = ScoreTMB7;
		ScoreTMB8N = ScoreTMB7N;

		ScoreTMB7 = ScoreTMB6;
		ScoreTMB7N = ScoreTMB6N;

		ScoreTMB6 = ScoreTMB5;
		ScoreTMB6N = ScoreTMB5N;

		ScoreTMB5 = ScoreTMB4;
		ScoreTMB5N = ScoreTMB4N;

		ScoreTMB4 = playerScoreTMB;
		ScoreTMB4N = playerName;
	}
	else if ( Ranking == 5 )
	{
		ScoreTMB10 = ScoreTMB9;
		ScoreTMB10N = ScoreTMB9N;

		ScoreTMB9 = ScoreTMB8;
		ScoreTMB9N = ScoreTMB8N;

		ScoreTMB8 = ScoreTMB7;
		ScoreTMB8N = ScoreTMB7N;

		ScoreTMB7 = ScoreTMB6;
		ScoreTMB7N = ScoreTMB6N;

		ScoreTMB6 = ScoreTMB5;
		ScoreTMB6N = ScoreTMB5N;

		ScoreTMB5 = playerScoreTMB;
		ScoreTMB5N = playerName;
	}
	else if ( Ranking == 6 )
	{
		ScoreTMB10 = ScoreTMB9;
		ScoreTMB10N = ScoreTMB9N;

		ScoreTMB9 = ScoreTMB8;
		ScoreTMB9N = ScoreTMB8N;

		ScoreTMB8 = ScoreTMB7;
		ScoreTMB8N = ScoreTMB7N;

		ScoreTMB7 = ScoreTMB6;
		ScoreTMB7N = ScoreTMB6N;

		ScoreTMB6 = playerScoreTMB;
		ScoreTMB6N = playerName;
	}
	else if ( Ranking == 7 )
	{
		ScoreTMB10 = ScoreTMB9;
		ScoreTMB10N = ScoreTMB9N;

		ScoreTMB9 = ScoreTMB8;
		ScoreTMB9N = ScoreTMB8N;

		ScoreTMB8 = ScoreTMB7;
		ScoreTMB8N = ScoreTMB7N;

		ScoreTMB7 = playerScoreTMB;
		ScoreTMB7N = playerName;
	}
	else if ( Ranking == 8 )
	{
		ScoreTMB10 = ScoreTMB9;
		ScoreTMB10N = ScoreTMB9N;

		ScoreTMB9 = ScoreTMB8;
		ScoreTMB9N = ScoreTMB8N;

		ScoreTMB8 = playerScoreTMB;
		ScoreTMB8N = playerName;
	}
	else if ( Ranking == 9 )
	{
		ScoreTMB10 = ScoreTMB9;
		ScoreTMB10N = ScoreTMB9N;

		ScoreTMB9 = playerScoreTMB;
		ScoreTMB9N = playerName;
	}
	else if ( Ranking == 10 )
	{
		ScoreTMB10 = playerScoreTMB;
		ScoreTMB10N = playerName;
	}

	savescoresTMB();
	gamestate = TMBGAMEOVER;
}

void initTMBHS()
{
	loadscoresTMB(); //load high scores
	
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set character location
    charLocation.X = 00;
    charLocation.Y = 00;
}

void renderTMBHS(){
	// clear previous screen
	colour(0x0F);
    cls();

	// render time taken to calculate this frame
    gotoXY(70, 0);
    colour(0x1A);
    std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
    gotoXY(0, 0);
    colour(0x59);
    std::cout << elapsedTime << "secs" << std::endl;

	// render options
	colour(0x0F);

	gotoXY(1, 2);
	std::cout << "   ___   __  ______    _   ___  __   ____  __  ____    __    _________________";

	gotoXY(1, 3);
	std::cout << "  |__ \\ /  |/  /   |  / | / | \\/ /  / __ )/ / / / /   / /   / ____/_  __/ ___/";

	gotoXY(1, 4);
	std::cout << "  __/ // /|_/ / /| | /  |/ / \\  /  / __  / / / / /   / /   / __/   / /  \\__ \\ ";

	gotoXY(1, 5);
	std::cout << " / __// /  / / ___ |/ /|  /  / /  / /_/ / /_/ / /___/ /___/ /___  / /  ___/ / ";

	gotoXY(1, 6);
	std::cout << "/____/_/  /_/_/  |_/_/ |_/  /_/  /_____/\\____/_____/_____/_____/ /_/  /____/  ";

	gotoXY(22, 10);
	std::cout << "RANK         SCORE            NAME";

	gotoXY(22, 11);
	colour(0x04);
	std::cout << "1ST         " << ScoreTMB1 << "           ";
	gotoXY(52, 11);
	std::cout << ScoreTMB1N;

	gotoXY(22, 12);
	colour(0x0C);
	std::cout << "2ND         " << ScoreTMB2 << "           ";
	gotoXY(52, 12);
	std::cout << ScoreTMB2N;

	gotoXY(22, 13);
	colour(0x0E);
	std::cout << "3RD         " << ScoreTMB3 << "           ";
	gotoXY(52, 13);
	std::cout << ScoreTMB3N;

	gotoXY(22, 14);
	colour(0x0F);
	std::cout << "4TH         " << ScoreTMB4 << "           ";
	gotoXY(52, 14);
	std::cout << ScoreTMB4N;

	gotoXY(22, 15);
	std::cout << "5TH         " << ScoreTMB5 << "           ";
	gotoXY(52, 15);
	std::cout << ScoreTMB5N;

	gotoXY(22, 16);
	std::cout << "6TH         " << ScoreTMB6 << "           ";
	gotoXY(52, 16);
	std::cout << ScoreTMB6N;

	gotoXY(22, 17);
	std::cout << "7TH         " << ScoreTMB7 << "           ";
	gotoXY(52, 17);
	std::cout << ScoreTMB7N;

	gotoXY(22, 18);
	std::cout << "8TH         " << ScoreTMB8 << "           ";
	gotoXY(52, 18);
	std::cout << ScoreTMB8N;

	gotoXY(22, 19);
	std::cout << "9TH         " << ScoreTMB9 << "           ";
	gotoXY(52, 19);
	std::cout << ScoreTMB9N;

	gotoXY(22, 20);
	std::cout << "10TH        " << ScoreTMB10 << "           ";
	gotoXY(52, 20);
	std::cout << ScoreTMB10N;

	gotoXY(30, 22);
	std::cout << "Press ENTER to return";

}

void updateTMBHS(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

	if (keyPressed[K_ENTER] ) // Return to TMB! Menu
	{
		Beep(4000, 30);
		gamestate = TMBMENU;
	}

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
	{
		gotoXY(0, 1);
        g_quitGame = true;    
	}
}

void initTMBGO()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set character location
    charLocation.X = 00;
    charLocation.Y = 00;
}

void renderTMBGO()
{
	// clear previous screen
	colour(0x0F);
    cls();

	// render time taken to calculate this frame
    gotoXY(70, 0);
    colour(0x1A);
    std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
    gotoXY(0, 0);
    colour(0x59);
    std::cout << elapsedTime << "secs" << std::endl;

	// render options
	colour(0x0F);

	gotoXY(12, 2);
	std::cout << "   _________    __  _____________ _    ____________     ";

	gotoXY(12, 3);
	std::cout << "  / ____/   |  /  |/  / ____/ __ \\ |  / / ____/ __ \\    ";

	gotoXY(12, 4);
	std::cout << " / / __/ /| | / /|_/ / __/ / / / / | / / __/ / /_/ /    ";

	gotoXY(12, 5);
	std::cout << "/ /_/ / ___ |/ /  / / /___/ /_/ /| |/ / /___/ _, _/ _ _ ";

	gotoXY(12, 6);
	std::cout << "\\____/_/  |_/_/  /_/_____/\\____/ |___/_____/_/ |_(_|_|_)";

	gotoXY(35, 15);
	std::cout << "Score: " << playerScoreTMB;

	gotoXY(30, 21);
	std::cout << "Press ENTER to return";

}

void updateTMBGO(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

	if (keyPressed[K_ENTER] ) // Return to TMB! Menu
	{
		Beep(4000, 30);
		gamestate = TMBHIGHSCORE;
	}

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
	{
		gotoXY(0, 1);
        g_quitGame = true;    
	}
}
//Highscore functions.
int loadscoresTMB()
{
	std::string data;
	double data2 = 0;
	std::fstream myScores;
	std::fstream myHighs;
	myScores.open("tmbScores.txt");

	getline(myScores, data);
	ScoreTMB1N = data;
	getline(myScores, data);
	ScoreTMB2N = data;
	getline(myScores, data);
	ScoreTMB3N = data;
	getline(myScores, data);
	ScoreTMB4N = data;
	getline(myScores, data);
	ScoreTMB5N = data;
	getline(myScores, data);
	ScoreTMB6N = data;
	getline(myScores, data);
	ScoreTMB7N = data;
	getline(myScores, data);
	ScoreTMB8N = data;
	getline(myScores, data);
	ScoreTMB9N = data;
	getline(myScores, data);
	ScoreTMB10N = data;
	
	myScores.close();

	myHighs.open("tmbHighs.txt");

	myHighs >> data2;
	ScoreTMB1 = data2;
	myHighs >> data2;
	ScoreTMB2 = data2;
	myHighs >> data2;
	ScoreTMB3 = data2;
	myHighs >> data2;
	ScoreTMB4 = data2;
	myHighs >> data2;
	ScoreTMB5 = data2;
	myHighs >> data2;
	ScoreTMB6 = data2;
	myHighs >> data2;
	ScoreTMB7 = data2;
	myHighs >> data2;
	ScoreTMB8 = data2;
	myHighs >> data2;
	ScoreTMB9 = data2;
	myHighs >> data2;
	ScoreTMB10 = data2;

	myHighs.close();
	return 0;
}

int savescoresTMB()
{
	std::string data;
	double data2 = 0;
	std::fstream myScores;
	myScores.open("tmbScores.txt");

	myScores << ScoreTMB1N << std::endl;
	myScores << ScoreTMB2N << std::endl;
	myScores << ScoreTMB3N << std::endl;
	myScores << ScoreTMB4N << std::endl;
	myScores << ScoreTMB5N << std::endl;
	myScores << ScoreTMB6N << std::endl;
	myScores << ScoreTMB7N << std::endl;
	myScores << ScoreTMB8N << std::endl;
	myScores << ScoreTMB9N << std::endl;
	myScores << ScoreTMB10N;

	myScores.close();

	std::fstream myHighs;
	myHighs.open("tmbHighs.txt");

	myHighs << ScoreTMB1 << std::endl;
	myHighs << ScoreTMB2 << std::endl;
	myHighs << ScoreTMB3 << std::endl;
	myHighs << ScoreTMB4 << std::endl;
	myHighs << ScoreTMB5 << std::endl;
	myHighs << ScoreTMB6 << std::endl;
	myHighs << ScoreTMB7 << std::endl;
	myHighs << ScoreTMB8 << std::endl;
	myHighs << ScoreTMB9 << std::endl;
	myHighs << ScoreTMB10;

	myHighs.close();
	return 0;
}