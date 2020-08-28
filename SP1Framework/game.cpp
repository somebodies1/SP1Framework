// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <random>
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <sstream>

double  g_dElapsedTime;
double  g_dDeltaTime;
SKeyEvent g_skKeyEvent[K_COUNT];
SMouseEvent g_mouseEvent;

// Game specific variables here
player PlayerChar; //create player object
maps Gamemap;     //Layer for the map
maps Entitylayer; //Layer for the enitites so they can overlap with map objects
int enemyno = 0;  //index of enemy spawned per map, set to 0 and increased for each enemy spawned per map. Reset to 0 when it enters a new map
char spawnedmaps[10] = {' ',' ',' ',' ',' ',' ',' ',' ', ' ',' '}; //Keeps track to the current map to check if a new map has been loaded by the end of a function
SGameChar   g_sChar;
Boss* boss = nullptr;
Entity* amt[10][50]; // can be increased and the adding of nullptr can be a for loop
bullet* bulletlist[50]; // maximum of 50 bullets at a time
int menupointer = 0; //initialise the menu pointer that allows the keyboard menu interaction
EGAMESTATES g_eGameState = S_MAINMENU; // initial state

// Console object
Console g_Console(80, 25, "Mask the World");
bool initialload = true; // The initial load of the map
//bool spawned[5] = { false, false, false ,false, false };


//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init(void)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            amt[i][j] = nullptr;
        }
    }
    // Set precision for floating point output
    g_dElapsedTime = 0.0;

    // sets the initial state for the game
    g_eGameState = S_MAINMENU;

    //Previous code for the spawning of the character put it in the middle of the console
    //g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
    //g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y / 2;

    g_sChar.m_cLocation.X = 1;
    g_sChar.m_cLocation.Y = 22;
    g_sChar.m_bActive = true;


    //g_pew.m_cLocation.X = PlayerChar.getXY().X + 1;
    //g_pew.m_cLocation.Y = PlayerChar.getXY().Y;



    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");

    // remember to set your keyboard handler, so that your functions can be notified of input events
    g_Console.setKeyboardHandler(keyboardHandler);
    g_Console.setMouseHandler(mouseHandler);
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown(void)
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    //Preventing memory leaks
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            if (amt[i][j] != nullptr)
            {
                delete amt[i][j];
                amt[i][j] = nullptr;
            }
        }
    }
    for (int i = 0; i < 50; i++) //deletes bullet pointers
    {
        if (bulletlist[i] != nullptr)
        {
            delete bulletlist[i];
            bulletlist[i] = nullptr;
        }
    }
    g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Get all the console input events
//            This function sets up the keyboard and mouse input from the console.
//            We will need to reset all the keyboard status, because no events will be sent if no keys are pressed.
//
//            Remember to set the handlers for keyboard and mouse events.
//            The function prototype of the handler is a function that takes in a const reference to the event struct
//            and returns nothing. 
//            void pfKeyboardHandler(const KEY_EVENT_RECORD&);
//            void pfMouseHandlerconst MOUSE_EVENT_RECORD&);
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput(void)
{
    // resets all the keyboard events
    memset(g_skKeyEvent, 0, K_COUNT * sizeof(*g_skKeyEvent));
    // then call the console to detect input from user
    g_Console.readConsoleInput();
}

//--------------------------------------------------------------
// Purpose  : This is the handler for the keyboard input. Whenever there is a keyboard event, this function will be called.
//            Ideally, you should pass the key event to a specific function to handle the event.
//            This is because in some states, some keys would be disabled. Hence, to reduce your code complexity, 
//            it would be wise to split your keyboard input handlers separately.
//            
//            The KEY_EVENT_RECORD struct has more attributes that you can use, if you are adventurous enough.
//
//            In this case, we are not handling any keyboard event in the Splashscreen state
//            
// Input    : const KEY_EVENT_RECORD& keyboardEvent - reference to a key event struct
// Output   : void
//--------------------------------------------------------------
void keyboardHandler(const KEY_EVENT_RECORD& keyboardEvent)
{
    switch (g_eGameState)
    {
        //case S_SPLASHSCREEN: // don't handle anything for the splash screen
        //    break;
    case S_MAINMENU: menuKBHandler(keyboardEvent); // handle menu keyboard event (Escape and space)
        break;
    case S_PAUSE: menuKBHandler(keyboardEvent);
        break;
    case S_GAMEOVER:menuKBHandler(keyboardEvent);
        break;
    case S_STAGECOMPLETE: menuKBHandler(keyboardEvent);
        break;
    case S_CREDIT: menuKBHandler(keyboardEvent);
        break;
    case S_LEVEL: menuKBHandler(keyboardEvent);
        break;
    case S_GAME: gameplayKBHandler(keyboardEvent); // handle gameplay keyboard event 
        break;
    }
}

//--------------------------------------------------------------
// Purpose  : This is the handler for the mouse input. Whenever there is a mouse event, this function will be called.
//            Ideally, you should pass the key event to a specific function to handle the event.
//            This is because in some states, some keys would be disabled. Hence, to reduce your code complexity, 
//            it would be wise to split your keyboard input handlers separately.
//            
//            For the mouse event, if the mouse is not moved, no event will be sent, hence you should not reset the mouse status.
//            However, if the mouse goes out of the window, you would not be able to know either. 
//
//            The MOUSE_EVENT_RECORD struct has more attributes that you can use, if you are adventurous enough.
//
//            In this case, we are not handling any mouse event in the Splashscreen state
//            
// Input    : const MOUSE_EVENT_RECORD& mouseEvent - reference to a mouse event struct
// Output   : void
//--------------------------------------------------------------
void mouseHandler(const MOUSE_EVENT_RECORD& mouseEvent)
{
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: // don't handle anything for the splash screen
        break;
    case S_MAINMENU: gameplayMouseHandler(mouseEvent);
        break;
    case S_PAUSE: gameplayMouseHandler(mouseEvent);
        break;
    case S_GAMEOVER: gameplayMouseHandler(mouseEvent);
        break;
    case S_LEVEL: gameplayMouseHandler(mouseEvent);
        break;
    case S_STAGECOMPLETE: gameplayMouseHandler(mouseEvent);
        break;
    case S_CREDIT: gameplayMouseHandler(mouseEvent);
        break;
    case S_GAME: gameplayMouseHandler(mouseEvent); // handle gameplay mouse event
        break;
    }
}

//--------------------------------------------------------------
// Purpose  : This is the keyboard handler in the game state. Whenever there is a keyboard event in the game state, this function will be called.
//            
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : const KEY_EVENT_RECORD& keyboardEvent
// Output   : void
//--------------------------------------------------------------
void gameplayKBHandler(const KEY_EVENT_RECORD& keyboardEvent)
{
    // here, we map the key to our enums
    EKEYS key = K_COUNT;
    switch (keyboardEvent.wVirtualKeyCode)
    {
    case 0x57: key = K_UP; break;
    case 0x53: key = K_DOWN; break;
    case 0x41: key = K_LEFT; break;
    case 0x44: key = K_RIGHT; break;
    case VK_SPACE: key = K_SPACE; break;
    case VK_ESCAPE: key = K_ESCAPE; break;
    }
    // a key pressed event would be one with bKeyDown == true
    // a key released event would be one with bKeyDown == false
    // if no key is pressed, no event would be fired.
    // so we are tracking if a key is either pressed, or released
    if (key != K_COUNT)
    {
        g_skKeyEvent[key].keyDown = keyboardEvent.bKeyDown;
        g_skKeyEvent[key].keyReleased = !keyboardEvent.bKeyDown;
    }
}

void menuKBHandler(const KEY_EVENT_RECORD& keyboardEvent)  //KB inputs when inside main menu
{
    EKEYS key = K_COUNT;
    switch (keyboardEvent.wVirtualKeyCode)
    {
    case VK_SPACE: key = K_SPACE; break;
    case VK_ESCAPE: key = K_ESCAPE; break;
    case 0x57: key = K_UP; break;
    case 0x53: key = K_DOWN; break;
    }
    if (key != K_COUNT)
    {
        g_skKeyEvent[key].keyDown = keyboardEvent.bKeyDown;
        g_skKeyEvent[key].keyReleased = !keyboardEvent.bKeyDown;
    }
}


//--------------------------------------------------------------
// Purpose  : This is the mouse handler in the game state. Whenever there is a mouse event in the game state, this function will be called.
//            
//            If mouse clicks are detected, the corresponding bit for that mouse button will be set.
//            mouse wheel, 
//            
// Input    : const KEY_EVENT_RECORD& keyboardEvent
// Output   : void
//--------------------------------------------------------------
void gameplayMouseHandler(const MOUSE_EVENT_RECORD& mouseEvent)
{
    if (mouseEvent.dwEventFlags & MOUSE_MOVED) // update the mouse position if there are no events
    {
        g_mouseEvent.mousePosition = mouseEvent.dwMousePosition;
    }
    g_mouseEvent.buttonState = mouseEvent.dwButtonState;
    g_mouseEvent.eventFlags = mouseEvent.dwEventFlags;
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
    // get the delta time
    g_dElapsedTime += dt;
    g_dDeltaTime = dt;

    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: splashScreenWait(); // game logic for the splash screen
        break;
    case S_MAINMENU: updateMainMenu();
        break;
    case S_PAUSE: updatePauseMenu();
        break;
    case S_GAMEOVER: updateGameover();
        break;
    case S_CREDIT: updateCredit();
        break;
    case S_LEVEL: updateLevelselect();
        break;
    case S_STAGECOMPLETE: updateStagecomplete();
        break;
    case S_CREDIT: updateCredit();
        break;
    case S_GAME: updateGame(g_dElapsedTime); // gameplay logic when we are in the game
        break;
    }
}

void splashScreenWait()    // waits for time to pass in splash screen
{
    if (g_dElapsedTime > 3.0) // wait for 3 seconds to switch to game mode, else do nothing
        g_eGameState = S_GAME;
}

void updateGame(double g_dElapsedTime)       // gameplay logic
{
    renderMap();
    processUserInput(); // checks if you should change  states or do something else with the game, e.g. pause, exit
    moveEntities(g_dElapsedTime);
    moveCharacter();    // moves the character, collision detection, physics, etc       
                        // sound can be played here too.

    if (PlayerChar.getHP() <= 0)
    {
        g_eGameState = S_GAMEOVER;       
    }
    if (Gamemap.getstageno() == 5 && Gamemap.getmapno() == 3)
    {
            updateBoss(g_dElapsedTime);
    }
}

void updateMainMenu()
{
    if (g_skKeyEvent[K_UP].keyReleased) // moves the menu cursor
    {
        menupointer -= 1;
        if (menupointer < 0 )
        {
            menupointer = 3;
        }
    }
    if (g_skKeyEvent[K_DOWN].keyReleased) // moves the menu cursor
    {
        menupointer += 1;
        if (menupointer > 3)
        {
            menupointer = 0;
        }
    }
    if (g_mouseEvent.mousePosition.X >= 38 && g_mouseEvent.mousePosition.X <= 42 && g_mouseEvent.mousePosition.Y == 19 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED || menupointer == 0 && g_skKeyEvent[K_SPACE].keyReleased)
    {
        g_eGameState = S_GAME;
    }
    if (g_mouseEvent.mousePosition.X >= 37 && g_mouseEvent.mousePosition.X <= 42 && g_mouseEvent.mousePosition.Y == 20 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED || menupointer == 1 && g_skKeyEvent[K_SPACE].keyReleased)
    {
        menupointer = 0;
        g_eGameState = S_LEVEL;
    }
    if (g_mouseEvent.mousePosition.X >= 38 && g_mouseEvent.mousePosition.X <= 41 && g_mouseEvent.mousePosition.Y == 21 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED || menupointer == 2 && g_skKeyEvent[K_SPACE].keyReleased || g_skKeyEvent[K_ESCAPE].keyReleased)
    {
        g_bQuitGame = true;
    }
    if (g_mouseEvent.mousePosition.X >= 37 && g_mouseEvent.mousePosition.X <= 43 && g_mouseEvent.mousePosition.Y == 24 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED || menupointer == 3 && g_skKeyEvent[K_SPACE].keyReleased)
    {
        menupointer = 0;
        g_eGameState = S_CREDIT;
    }
}

void updatePauseMenu()
{
    if (g_skKeyEvent[K_UP].keyReleased) // moves the menu cursor
    {
        menupointer -= 1;
        if (menupointer < 0)
        {
            menupointer = 2;
        }
    }
    if (g_skKeyEvent[K_DOWN].keyReleased) // moves the menu cursor
    {
        menupointer += 1;
        if (menupointer > 2)
        {
            menupointer = 0;
        }
    }
    if (g_mouseEvent.mousePosition.X >= 36 && g_mouseEvent.mousePosition.X <= 43 && g_mouseEvent.mousePosition.Y == 18 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED || g_skKeyEvent[K_SPACE].keyReleased && menupointer == 1)
    {
        Reset();
        g_eGameState = S_MAINMENU;
    }
    if (g_mouseEvent.mousePosition.X >= 36 && g_mouseEvent.mousePosition.X <= 44 && g_mouseEvent.mousePosition.Y == 16 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED || g_skKeyEvent[K_SPACE].keyReleased && menupointer == 0 || g_skKeyEvent[K_ESCAPE].keyReleased)
    {
        g_eGameState = S_GAME;
    }
    if (g_mouseEvent.mousePosition.X >= 38 && g_mouseEvent.mousePosition.X <= 41 && g_mouseEvent.mousePosition.Y == 20 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED || g_skKeyEvent[K_SPACE].keyReleased && menupointer == 2)
    {
        g_bQuitGame = true;
    }
}

void updateGameover()
{
    if (g_skKeyEvent[K_UP].keyReleased) // moves the menu cursor
    {
        menupointer -= 1;
        if (menupointer < 0)
        {
            menupointer = 2;
        }
    }
    if (g_skKeyEvent[K_DOWN].keyReleased) // moves the menu cursor
    {
        menupointer += 1;
        if (menupointer > 2)
        {
            menupointer = 0;
        }
    }
    if (g_mouseEvent.mousePosition.X >= 34 && g_mouseEvent.mousePosition.X <= 44 && g_mouseEvent.mousePosition.Y == 20 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED || g_skKeyEvent[K_SPACE].keyReleased && menupointer == 1)
    {
        Reset();
        g_eGameState = S_MAINMENU;
    }
    if (g_mouseEvent.mousePosition.X >= 36 && g_mouseEvent.mousePosition.X <= 41 && g_mouseEvent.mousePosition.Y == 18 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED || g_skKeyEvent[K_SPACE].keyReleased && menupointer == 0)
    {
        Reset();
        g_eGameState = S_GAME;
    }
    if (g_mouseEvent.mousePosition.X >= 36 && g_mouseEvent.mousePosition.X <= 40 && g_mouseEvent.mousePosition.Y == 22 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED || g_skKeyEvent[K_SPACE].keyReleased && menupointer == 2 || g_skKeyEvent[K_ESCAPE].keyReleased)
    {
        g_bQuitGame = true;
    }
}

void updateLevelselect()
{
    if (g_skKeyEvent[K_UP].keyReleased) // moves the menu cursor
    {
        menupointer -= 1;
        if (menupointer < 0)
        {
            menupointer = 6;
        }
    }
    if (g_skKeyEvent[K_DOWN].keyReleased) // moves the menu cursor
    {
        menupointer += 1;
        if (menupointer > 6)
        {
            menupointer = 0;
        }
    }
    if (g_mouseEvent.mousePosition.X >= 36 && g_mouseEvent.mousePosition.X <= 43 && g_mouseEvent.mousePosition.Y == 13 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED || g_skKeyEvent[K_SPACE].keyReleased && menupointer == 0)
    {
        Gamemap.setstage(0);
        Entitylayer.setstage(0);
        Reset();
        g_eGameState = S_GAME;
    }
    if (g_mouseEvent.mousePosition.X >= 36 && g_mouseEvent.mousePosition.X <= 43 && g_mouseEvent.mousePosition.Y == 15 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED || g_skKeyEvent[K_SPACE].keyReleased && menupointer == 1)
    {
        Gamemap.setstage(1);
        Entitylayer.setstage(1);
        Reset();
        g_eGameState = S_GAME;
    }
    if (g_mouseEvent.mousePosition.X >= 36 && g_mouseEvent.mousePosition.X <= 43 && g_mouseEvent.mousePosition.Y == 16 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED || g_skKeyEvent[K_SPACE].keyReleased && menupointer == 2)
    {
        Gamemap.setstage(2);
        Entitylayer.setstage(2);
        Reset();
        g_eGameState = S_GAME;
    }
    if (g_mouseEvent.mousePosition.X >= 36 && g_mouseEvent.mousePosition.X <= 43 && g_mouseEvent.mousePosition.Y == 17 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED || g_skKeyEvent[K_SPACE].keyReleased && menupointer == 3)
    {
        Gamemap.setstage(3);
        Entitylayer.setstage(3);
        Reset();
        g_eGameState = S_GAME;
    }
    if (g_mouseEvent.mousePosition.X >= 36 && g_mouseEvent.mousePosition.X <= 43 && g_mouseEvent.mousePosition.Y == 18 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED || g_skKeyEvent[K_SPACE].keyReleased && menupointer == 4)
    {
        Gamemap.setstage(4);
        Entitylayer.setstage(4);
        Reset();
        g_eGameState = S_GAME;
    }
    if (g_mouseEvent.mousePosition.X >= 36 && g_mouseEvent.mousePosition.X <= 43 && g_mouseEvent.mousePosition.Y == 19 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED || g_skKeyEvent[K_SPACE].keyReleased && menupointer == 5)
    {
        Gamemap.setstage(5);
        Entitylayer.setstage(5);
        Reset();
        g_eGameState = S_GAME;
    }
    if (g_mouseEvent.mousePosition.X >= 37 && g_mouseEvent.mousePosition.X <= 40 && g_mouseEvent.mousePosition.Y == 22 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED || g_skKeyEvent[K_ESCAPE].keyReleased || g_skKeyEvent[K_SPACE].keyReleased && menupointer == 6)
    {
        g_eGameState = S_MAINMENU;
    }
}

void updateStagecomplete()
{
    if (g_skKeyEvent[K_UP].keyReleased) // moves the menu cursor
    {
        menupointer -= 1;
        if (menupointer < 0)
        {
            menupointer = 2;
        }
    }
    if (g_skKeyEvent[K_DOWN].keyReleased) // moves the menu cursor
    {
        menupointer += 1;
        if (menupointer > 2)
        {
            menupointer = 0;
        }
    }
    if (g_mouseEvent.mousePosition.X >= 36 && g_mouseEvent.mousePosition.X <= 46 && g_mouseEvent.mousePosition.Y == 18 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED || g_skKeyEvent[K_SPACE].keyReleased && menupointer == 1)
    {
        Reset();
        g_eGameState = S_MAINMENU;
    }
    if (g_mouseEvent.mousePosition.X >= 38 && g_mouseEvent.mousePosition.X <= 42 && g_mouseEvent.mousePosition.Y == 17 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED || g_skKeyEvent[K_SPACE].keyReleased && menupointer == 0)
    {
        Reset();
        if (Gamemap.getstageno() < 5)
        {
            Gamemap.setstage(Gamemap.getstageno() + 1);
            Entitylayer.setstage(Entitylayer.getstageno() + 1);
            g_eGameState = S_GAME;
        }
        else
        {
            menupointer = 0;
            g_eGameState = S_CREDIT;
        }
    }
    if (g_mouseEvent.mousePosition.X >= 38 && g_mouseEvent.mousePosition.X <= 42 && g_mouseEvent.mousePosition.Y == 19 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED || g_skKeyEvent[K_ESCAPE].keyDown || g_skKeyEvent[K_SPACE].keyReleased && menupointer == 2)
    {
        g_bQuitGame = true;
    }
}

void updateCredit()
{
    menupointer = 0;
    if (g_mouseEvent.mousePosition.X >= 36 && g_mouseEvent.mousePosition.X <= 45 && g_mouseEvent.mousePosition.Y == 22 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED || g_skKeyEvent[K_SPACE].keyReleased && menupointer == 0)
    {
        Reset();
        g_eGameState = S_MAINMENU;
    }
}


void Reset() {
    for (int i = 0; i < 10; i++) //reset spawned map status
    {
        spawnedmaps[i] = ' ';
        
    }
    initialload = true; //resets variable that loads the initial map once
    for (int i = 0; i < 10; i++) // reset enemies
    {
        for (int j = 0; j < 50; j++)
        {
            if (amt[i][j] != nullptr)
            {
                delete amt[i][j];
                amt[i][j] = nullptr;
            }
        }
    }
    for (int i = 0; i < 50; i++) //resets bullets
    {
        if (bulletlist[i] != nullptr)
        {
            delete bulletlist[i];
            bulletlist[i] = nullptr;
        }
    }
    Gamemap.setmapno(0);
    Entitylayer.setmapno(0);
    PlayerChar  = player();
}

void Printtxt(string file, WORD colour)
{
    string line;
    COORD c;
    ifstream mapfile(file);
    for (int i = 0; i < 25; i++)
    {
        getline(mapfile, line);
        char linearray[200];
        strcpy(linearray, line.c_str());
        for (int j = 0; j < 80; j++)
        {
            c.X = j;
            c.Y = i;
            g_Console.writeToBuffer(c, linearray[j], colour);
        }
    }
}

void moveEntities(double g_dElapsedTime)
{
    if (g_eGameState == S_GAME)
    {   //bullet moves first
        char bullethit; //What the bullet hits, may be ' ' when nothing
        if (true)//speed for bullets here
        {
            for (int i = 0; i < 50; i++)
            {
                if (bulletlist[i] != nullptr)
                {
                    bullethit = bulletlist[i]->move(g_dElapsedTime, '-', Entitylayer); //This function also causes the bullet to move so it can only be called once
                    if (bullethit == 'Z' || bullethit == 'K' || bullethit == 'F' || bullethit == 'L')
                    {
                        for (int enemyindex = 0; enemyindex < 50; enemyindex++)
                        {
                            if (amt[Entitylayer.getmapno()][enemyindex] != nullptr) // When the indexes before are nullptr, it crashes, so this line is added
                            {
                                if (bulletlist[i]->getdirection() == 1)
                                {
                                    if (amt[Entitylayer.getmapno()][enemyindex]->getXY().X == bulletlist[i]->getXY().X - 1 && amt[Entitylayer.getmapno()][enemyindex]->getXY().Y == bulletlist[i]->getXY().Y) // If statement find the enitity that the bullet collides with
                                    {
                                        //delete amt[Entitylayer.getmapno()][enemyindex];
                                        //amt[Entitylayer.getmapno()][enemyindex] = nullptr;
                                        //Entitylayer.setchar(' ', bulletlist[i]->getXY().X - 1, bulletlist[i]->getXY().Y);
                                        Entitylayer.setchar(' ', bulletlist[i]->getXY().X, bulletlist[i]->getXY().Y);
                                        delete bulletlist[i];
                                        bulletlist[i] = nullptr;
                                        amt[Entitylayer.getmapno()][enemyindex]->setHP(amt[Entitylayer.getmapno()][enemyindex]->getHP()-1); //Reduces health by one
                                        break;
                                    }
                                }
                                else if (bulletlist[i]->getdirection() == 2)
                                {
                                    if (amt[Entitylayer.getmapno()][enemyindex]->getXY().X == bulletlist[i]->getXY().X + 1 && amt[Entitylayer.getmapno()][enemyindex]->getXY().Y == bulletlist[i]->getXY().Y)
                                    {
                                        Entitylayer.setchar(' ', bulletlist[i]->getXY().X, bulletlist[i]->getXY().Y);
                                        delete bulletlist[i];
                                        bulletlist[i] = nullptr;
                                        amt[Entitylayer.getmapno()][enemyindex]->setHP(amt[Entitylayer.getmapno()][enemyindex]->getHP()-1);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    if (bullethit == '|' || bullethit == '\\' || bullethit == '/')
                    {
                        Entitylayer.setchar(' ', bulletlist[i]->getXY().X, bulletlist[i]->getXY().Y);
                        delete bulletlist[i];
                        bulletlist[i] = nullptr;
                        if (boss != nullptr)
                        {
                            boss->setHP(boss->getHP() - 1);
                        }
                    }
                    if ( bullethit == '=' || bullethit == '1' || bullethit == '<' || bullethit == '>')
                    {

                        Entitylayer.setchar(' ', bulletlist[i]->getXY().X, bulletlist[i]->getXY().Y);
                        delete bulletlist[i];
                        bulletlist[i] = nullptr;
                    }
                    
                }
            }
        }
        for (int i = 0; i < 50; i++) //For loop that loops though all the enemy types for the movement
        {
            if (amt[Entitylayer.getmapno()][i] != nullptr)
            {
                if (amt[Entitylayer.getmapno()][i]->getHP() > 0)
                {
                    amt[Entitylayer.getmapno()][i]->move(g_dElapsedTime, amt[Entitylayer.getmapno()][i]->gettype(), Entitylayer, PlayerChar.getXY()); //This move function is using polymorphism and moving based on the move code of the child class
                }                                              //Move also can return a char, although it doesn't return anything now
                else                                           // deletes enemies when their healh goes below 0
                {
                    int chance = rand() % 100 + 1; //srand is in main
                    Entitylayer.setchar(' ', amt[Entitylayer.getmapno()][i]->getXY().X, amt[Entitylayer.getmapno()][i]->getXY().Y);
                    if (chance > 70 || (chance > 10 && PlayerChar.get_ammo() < 10)) // ~30% chance or 90% when low on ammo
                    {
                        for (int j = 0; j < 50; j++) 
                        {
                            if (amt[Entitylayer.getmapno()][j] == nullptr)
                            {
                                amt[Entitylayer.getmapno()][j] = new Ammobox;
                                amt[Entitylayer.getmapno()][j]->spawnEntity(amt[Entitylayer.getmapno()][i]->getXY().X, amt[Entitylayer.getmapno()][i]->getXY().Y); //Spawns ammobox where enemy died
                                break;
                            }
                        }
                    }
                    else if (chance < 10) // ~10% chance
                    {
                        for (int j = 0; j < 50; j++)
                        {
                            if (amt[Entitylayer.getmapno()][j] == nullptr)
                            {
                                amt[Entitylayer.getmapno()][j] = new Health;
                                amt[Entitylayer.getmapno()][j]->spawnEntity(amt[Entitylayer.getmapno()][i]->getXY().X, amt[Entitylayer.getmapno()][i]->getXY().Y); //Spawns ammobox where enemy died
                                break;
                            }
                        }
                    }
                    delete amt[Entitylayer.getmapno()][i];
                    amt[Entitylayer.getmapno()][i] = nullptr;
                }
            }                                                                                                                 
        }
    }
}

void moveCharacter()
{
    int direction = 0;
    if (g_skKeyEvent[K_UP].keyDown)
    {
        direction = 1;
    }
    if (g_skKeyEvent[K_LEFT].keyDown)
    {
        direction = 2;
    }    
    if (g_skKeyEvent[K_DOWN].keyDown)
    {
        direction = 3;
    }
    if (g_skKeyEvent[K_RIGHT].keyDown)
    {
        direction = 4;
    }
    if (g_skKeyEvent[K_SPACE].keyDown)
    {
        if (PlayerChar.get_ammo()>=1)
        {
            Beep(1500, 10);
            PlayerChar.set_ammo(PlayerChar.get_ammo() - 1);
            //Beep(500, 50);
            //Beep(1500, 20);
            int iX = g_sChar.m_cLocation.X;
            int iY = g_sChar.m_cLocation.Y;
            for (int i = 0; i < 50; i++)
            {
                if (bulletlist[i] == nullptr)
                {
                    if (PlayerChar.getdirection() == 1 && Entitylayer.getchar(PlayerChar.getXY().Y, PlayerChar.getXY().X - 1) == ' ' || Entitylayer.getchar(PlayerChar.getXY().Y, PlayerChar.getXY().X - 1) == 'H')
                    {
                        bulletlist[i] = new bullet(PlayerChar.getdirection(), PlayerChar.getXY().X, PlayerChar.getXY().Y);
                        Entitylayer.setchar('-', PlayerChar.getXY().X, PlayerChar.getXY().Y);
                        g_Console.writeToBuffer(bulletlist[i]->getXY(), '-', 0x06);
                    }
                    if (PlayerChar.getdirection() == 2 && Entitylayer.getchar(PlayerChar.getXY().Y, PlayerChar.getXY().X + 1) == ' ' || Entitylayer.getchar(PlayerChar.getXY().Y, PlayerChar.getXY().X + 1) == 'H')
                    {
                        bulletlist[i] = new bullet(PlayerChar.getdirection(), PlayerChar.getXY().X , PlayerChar.getXY().Y);
                        Entitylayer.setchar('-', PlayerChar.getXY().X, PlayerChar.getXY().Y);
                        g_Console.writeToBuffer(bulletlist[i]->getXY(), '-', 0x06);
                    }
                    break;
                }
            }

        }
    }
    char mapaction = PlayerChar.moveplayer(Gamemap, Entitylayer, direction);
    if (mapaction =='M' || initialload) //This if statement is to check whether the is a map change since the map changing code is in the moveplayer code
    {              //M for change in map                         //Regardless of true or false, the character will still move
        enemyno = 0; // set the enenmy index to zero when a new map is loaded
        for (int i = 0; i < 50; i++) //destroys all bullets when switching maps and fills the initial list with nullptr
        {
            //if (bulletlist[i] != nullptr)
            //{
            //    if (Entitylayer.getchar(bulletlist[i]->getXY().Y, bulletlist[i]->getXY().X) == '-')
            //    {
            //        g_Console.writeToBuffer(bulletlist[i]->getXY(), ' ', 0x01);
            //    }
            //}
            delete bulletlist[i];
            bulletlist[i] = nullptr;
        }
        if (spawnedmaps[Gamemap.getmapno()] == ' ')
        {
            spawnedmaps[Gamemap.getmapno()] = 'X';
            Gamemap.setinitial(Gamemap.getmapno());
            Entitylayer.setinitial(Entitylayer.getmapno());
            spawnEnemy();
            if (Gamemap.getstageno() == 5 && (Gamemap.getmapno() == 3))
            {
                if (boss != nullptr)
                {
                    delete boss;
                    boss = nullptr;
                }
                boss = new Boss;
                boss->moveboss(0, Entitylayer);
            }
        }
        if (initialload)
        {
            initialload = false; //Changes to false after the inital map load
        }
    }
    else if (mapaction == 'S') // S for stage change
    {
        g_eGameState = S_STAGECOMPLETE;
    }
    else if (mapaction == 'C')
    {
        g_eGameState = S_CREDIT;
    }
    if (PlayerChar.collisioncheck(Entitylayer) == 'Z' || PlayerChar.collisioncheck(Entitylayer) == 'K' 
        || PlayerChar.collisioncheck(Entitylayer) == 'F' || PlayerChar.collisioncheck(Entitylayer) == 'L') // collision work, just have to put something here
    {
        PlayerChar.setHP(PlayerChar.getHP() - 1);
    }
    else if (PlayerChar.collisioncheck(Entitylayer) == '%')
    {
        for (int i = 0; i < 50; i++) //For loop that loops though all the entites
        {
            if (amt[Entitylayer.getmapno()][i] != nullptr)
            {
                if (amt[Entitylayer.getmapno()][i]->gettype() == '%' && (amt[Entitylayer.getmapno()][i]->getXY().X <= PlayerChar.getXY().X + 1 && amt[Entitylayer.getmapno()][i]->getXY().X >= PlayerChar.getXY().X - 1) && (amt[Entitylayer.getmapno()][i]->getXY().Y <= PlayerChar.getXY().Y + 1 && amt[Entitylayer.getmapno()][i]->getXY().Y >= PlayerChar.getXY().Y - 1))
                {
                    PlayerChar.set_ammo(PlayerChar.get_ammo() + 10);
                    if (PlayerChar.get_ammo() > 50)
                        PlayerChar.set_ammo(50);
                    Entitylayer.setchar(' ', amt[Entitylayer.getmapno()][i]->getXY().X, amt[Entitylayer.getmapno()][i]->getXY().Y);
                    Beep(2000, 50);
                    delete amt[Entitylayer.getmapno()][i];
                    amt[Entitylayer.getmapno()][i] = nullptr;
                    break;
                }
            }
        }
    }
    else if (PlayerChar.collisioncheck(Entitylayer) == '+')
    {
        for (int i = 0; i < 50; i++)
        {
            if (amt[Entitylayer.getmapno()][i] != nullptr)
            {
                if (amt[Entitylayer.getmapno()][i]->gettype() == '+' && (amt[Entitylayer.getmapno()][i]->getXY().X <= PlayerChar.getXY().X + 1 && amt[Entitylayer.getmapno()][i]->getXY().X >= PlayerChar.getXY().X - 1) && (amt[Entitylayer.getmapno()][i]->getXY().Y <= PlayerChar.getXY().Y + 1 && amt[Entitylayer.getmapno()][i]->getXY().Y >= PlayerChar.getXY().Y - 1))
                {
                    PlayerChar.setHP(PlayerChar.getHP() + 20);
                    if (PlayerChar.getHP() > 100)
                        PlayerChar.setHP(100);
                    Entitylayer.setchar(' ', amt[Entitylayer.getmapno()][i]->getXY().X, amt[Entitylayer.getmapno()][i]->getXY().Y);
                    Beep(2000, 50);
                    delete amt[Entitylayer.getmapno()][i];
                    amt[Entitylayer.getmapno()][i] = nullptr;
                    break;
                }
            }
        }
    }
    if (PlayerChar.getXY().Y >= 24) //If the player falls of the map, it dies
    {
        PlayerChar.setHP(0);
    }
}


void processUserInput()
{
    // Pauses the game if player hits the escape key
    if (g_skKeyEvent[K_ESCAPE].keyReleased)
        g_eGameState = S_PAUSE;
}

//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
    clearScreen();      // clears the current screen and draw from scratch 
    switch (g_eGameState)
    {
        //case S_SPLASHSCREEN: renderSplashScreen();
        //    break;
    case S_MAINMENU: renderMainMenu();
        break;
    case S_PAUSE: renderPauseMenu();
        break;
    case S_GAMEOVER: renderGameover();
        break;
    case S_LEVEL: renderLevelselect();
        break;
    case S_STAGECOMPLETE: renderStagecomplete();
        break; 
    case S_CREDIT: renderCredit();
        break;
    case S_GAME:  renderGame();
        break;
    }
    renderFramerate();      // renders debug information, frame rate, elapsed time, etc
    renderToScreen();       // dump the contents of the buffer to the screen, one frame worth of game
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(0x1F);
}

void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}

void renderSplashScreen()  // renders the splash screen
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X / 2 - 9;
    g_Console.writeToBuffer(c, "A game in 3 seconds", 0x03);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 20;
    g_Console.writeToBuffer(c, "Press <Space> to change character colour", 0x09);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
    g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);
}

void renderMainMenu()  // renders the main menu
{
    Printtxt("Mainmenu.txt", 0x0B);
    if (menupointer == 0)
    {
        g_Console.writeToBuffer(36,19,'>', 0x0C);
    }
    else if (menupointer == 1)
    {
        g_Console.writeToBuffer(35, 20, '>', 0x0C);
    }
    else if (menupointer == 2)
    {
        g_Console.writeToBuffer(36, 21, '>', 0x0C);
    }
    else if (menupointer == 3)
    {
        g_Console.writeToBuffer(35, 24, '>', 0x0C);
    }
}

void renderPauseMenu()  // renders the main menu
{
    Printtxt("Pausemenu.txt", 0x0B);
    if (menupointer == 0)
    {
        g_Console.writeToBuffer(34, 16, '>', 0x0C);
    }
    else if (menupointer == 1)
    {
        g_Console.writeToBuffer(34, 18, '>', 0x0C);
    }
    else if (menupointer == 2)
    {
        g_Console.writeToBuffer(36, 20, '>', 0x0C);
    }
}
void renderGameover()
{
    Printtxt("Gameover.txt", 0x0C);
    if (menupointer == 0)
    {
        g_Console.writeToBuffer(34, 18, '>', 0x0C);
    }
    else if (menupointer == 1)
    {
        g_Console.writeToBuffer(32, 20, '>', 0x0C);
    }
    else if (menupointer == 2)
    {
        g_Console.writeToBuffer(34, 22, '>', 0x0C);
    }
}
void renderLevelselect()
{
    Printtxt("Levelselect.txt",0x0A);
    if (menupointer == 0)
    {
        g_Console.writeToBuffer(34, 13, '>', 0x0C);
    }
    else if (menupointer >= 1 && menupointer <= 5)
    {
        g_Console.writeToBuffer(34, 14 + menupointer, '>', 0x0C);
    }
    else if (menupointer == 6)
    {
        g_Console.writeToBuffer(35,22, '>', 0x0C);
    }
}
void renderStagecomplete()
{
    Printtxt("StageComplete.txt",0x0B);
    COORD c;
    std::ostringstream ss;
    c.X = 42;
    c.Y = 15;
    ss << PlayerChar.getscore();
    g_Console.writeToBuffer(c, ss.str(), 0x0C);
    if (menupointer == 0)
    {
        g_Console.writeToBuffer(36, 17, '>', 0x0C);
    }
    else if (menupointer == 1)
    {
        g_Console.writeToBuffer(34, 18 , '>', 0x0C);
    }
    else if (menupointer == 2)
    {
        g_Console.writeToBuffer(36, 19, '>', 0x0C);
    }
}
void renderCredit()
{
    Printtxt("Credit.txt",0x08);
    if (menupointer == 0)
    {
        g_Console.writeToBuffer(34, 22, '>', 0x0C);
    }
}
void renderGame()
{
    renderMap();        // renders the map to the buffer first
    renderEntities();   // renders the entities a layer above
    renderCharacter();  // renders the player a layer above
    renderPlayerUI(PlayerChar); //renders the resource indicators a layer above
}

void renderMap()
{
    COORD c;
    for (int i = 0; i < 80; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            c.X = i;
            c.Y = j;
            if (Gamemap.getchar(j, i) == '=') // '=' are coloured differently for the floor
            {
                g_Console.writeToBuffer(c, Gamemap.getchar(j, i), 0x0E);
            }
            else if (Gamemap.getchar(j, i) == 'H')
            {
                g_Console.writeToBuffer(c, Gamemap.getchar(j, i), 0x0C);
            }
            else if (Gamemap.getchar(j, i) == '1')
            {
                g_Console.writeToBuffer(c, Gamemap.getchar(j, i), 0x01);
            }
            else if (Gamemap.getchar(j, i) == 'Z' || Gamemap.getchar(j, i) == 'K' 
                || Gamemap.getchar(j,i) == 'F' || Gamemap.getchar(j,i) == 'L') // add the rest of the entities here in with or statments
            {
                Gamemap.setchar(' ', i, j);
                g_Console.writeToBuffer(c, ' ', 0x0F);
            }
            else if (Gamemap.getchar(j, i) == '%')
            {
                Gamemap.setchar(' ', i, j);
                g_Console.writeToBuffer(c, ' ', 0x0F);
            }
            else if (Gamemap.getchar(j, i) == '+')
            {
                Gamemap.setchar(' ', i, j);
                g_Console.writeToBuffer(c, ' ', 0x0F);
            }
            else //Normal colour of black text with blue background
            {
                g_Console.writeToBuffer(c, Gamemap.getchar(j, i), 0x0F); 
            }
        }
    }
}

void renderCharacter()
{
    WORD charColor = 0x0A;
    if (g_sChar.m_bActive)
    {
        charColor = 0x0F;
    }
    g_Console.writeToBuffer(PlayerChar.getXY(), char(1), 0x0F);
}

void updateBoss(double time)
{
    if (boss != nullptr)
    {
        int currentphase = boss->getsprite();
        int chance = rand() % 1000;
        if (fmod(time, 0.2) < 0.01 && boss->getphase() == 1) //phase 1 speed and movement
        {
            if (boss != nullptr)
            {
                if (boss->getXY().Y <= 2)
                {
                    boss->setdirection(3);
                }
                else if (boss->getXY().Y >= 20)
                {
                    boss->setdirection(1);
                }
                //int bossdirect = rand() % 4 - 1;
                boss->moveboss(1, Entitylayer);
            }
        }
        if (fmod(time, 0.2) < 0.04 && boss->getphase() == 2) //Phase 2 the boss will move in more erratic directions
        {
            if (boss != nullptr)
            {
                if (boss->getXY().Y <= 2)
                {
                    boss->setdirection(3);
                }
                else if (boss->getXY().Y >= 20)
                {
                    boss->setdirection(1);
                }
                //int bossdirect = rand() % 4 - 1;
                boss->moveboss(1, Entitylayer);
            }
            if (chance > 950)
            {
                if (boss->getdirection() == 1)
                {
                    boss->setdirection(3);
                }
                else
                {
                    boss->setdirection(1);
                }
            }
        }
        if (fmod(time, 0.2) < 0.06 && boss->getphase() == 3) //Move faster and more eratically
        {
            if (boss != nullptr)
            {
                if (boss->getXY().Y <= 2)
                {
                    boss->setdirection(3);
                }
                else if (boss->getXY().Y >= 20)
                {
                    boss->setdirection(1);
                }
                boss->moveboss(1, Entitylayer);
            }
            if (chance > 850)
            {
                if (boss->getdirection() == 1)
                {
                    boss->setdirection(3);
                }
                else
                {
                    boss->setdirection(1);
                }
            }
        }
        if (boss->getphase() >= 3 && fmod(time, 0.2) < 0.008) //Phase 3 spawns enemies in the lane of the player
        {
            if (boss->getXY().Y == PlayerChar.getXY().Y - 2) //when boss is in the same lane as player
            {
                bossSpawn(); // increase the chance of spawning to guarenteed
            }
        }
        if (fmod(time, 0.2) < 0.004) //Enemy spawning timer here
        {
            if (chance > 500);
            {
                bossSpawn();
                boss->setsprite(currentphase);
            }
        }
        if (boss->getHP() <= 20)
        {
            boss->setsprite(4);
            boss->setphase(2);
        }
        if (boss->getHP() <= 10)
        {
            boss->setsprite(5);
            boss->setphase(3);
        }
        if (boss->getHP() <= 0)
        {
            boss->setsprite(3);
            boss->setdirection(3);
            while (boss->getXY().Y < 23)
            {             
                boss->moveboss(1, Entitylayer);
                Beep(1500, 20);
                Beep(2000, 50);
                Sleep(240 - boss->getXY().Y*10);
            }
            boss->printboss(Gamemap);
            delete boss;
            boss = nullptr;
            //Boss kills all other mobs when it dies
            for (int i = 0; i < 10; i++)
            {
                for (int j = 0; j < 50; j++)
                {
                    if (amt[i][j] != nullptr)
                    {
                        Entitylayer.setchar(' ', amt[i][j]->getXY().X, amt[i][j]->getXY().Y);
                        delete amt[i][j];
                        amt[i][j] = nullptr;
                    }
                }
            }
        }
    }
}

void bossSpawn()
{
    COORD c;
    int iX = boss->getXY().X - 2;
    int iY = boss->getXY().Y + 1;
    c.X = iX;
    c.Y = iY;
    int type = rand() % 3 + 1;
    for (int i = 0; i < 50; i++)
    {
        if (Entitylayer.getchar(iY, iX) == ' ')
        {
            if (boss->getphase() >= 1 && type == 1)
            {
                if (amt[Entitylayer.getmapno()][i] == nullptr) //if the index is empty, fill it
                {
                    Beep(2000, 100);
                    amt[Entitylayer.getmapno()][i] = new Mob;
                    amt[Entitylayer.getmapno()][i]->spawnEntity(iX, iY);
                    break;
                }
            }
            if (boss->getphase() >= 2 && type == 2)
            {
                if (amt[Entitylayer.getmapno()][i] == nullptr) //if the index is empty, fill it
                {
                    Beep(3000, 100);
                    amt[Entitylayer.getmapno()][i] = new SpeedyMob;
                    amt[Entitylayer.getmapno()][i]->spawnEntity(iX, iY);
                    break;
                }
            }
            if (boss->getphase() >= 2 && type == 3)
            {
                if (amt[Entitylayer.getmapno()][i] == nullptr) //if the index is empty, fill it
                {
                    Beep(1000, 100);
                    amt[Entitylayer.getmapno()][i] = new SlowMob;
                    amt[Entitylayer.getmapno()][i]->spawnEntity(iX, iY);
                    break;
                }
            }
        }
    }
    enemyno++;
}

void spawnEnemy() //TODO: Set it so that when map changes, the enemies would be deleted and become nullptr for future use
{  
    COORD c;
    for (int i = 0; i < 80; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            if (Entitylayer.getchar(j, i) == 'Z')
            {
                c.X = i;
                c.Y = j;
                if (amt[Entitylayer.getmapno()][enemyno] == nullptr) //if the index is empty, fill it
                {
                    amt[Entitylayer.getmapno()][enemyno] = new Mob;
                    amt[Entitylayer.getmapno()][enemyno]->spawnEntity(i, j);
                    g_Console.writeToBuffer(c, Entitylayer.getchar(j, i), 0x08);
                    Entitylayer.setchar(' ', i, j);
                }
                enemyno++;
            }
            if (Entitylayer.getchar(j, i) == 'K')
            {
                c.X = i;
                c.Y = j;
                if (amt[Entitylayer.getmapno()][enemyno] == nullptr) //if the index is empty, fill it
                {
                    amt[Entitylayer.getmapno()][enemyno] = new SpeedyMob;
                    amt[Entitylayer.getmapno()][enemyno]->spawnEntity(i, j);
                    g_Console.writeToBuffer(c, Entitylayer.getchar(j, i), 0x0C);
                    Entitylayer.setchar(' ', i, j);
                }
                enemyno++;
            }
            if (Entitylayer.getchar(j, i) == 'F')
            {
                c.X = i;
                c.Y = j;
                if (amt[Entitylayer.getmapno()][enemyno] == nullptr) //if the index is empty, fill it
                {
                    amt[Entitylayer.getmapno()][enemyno] = new SlowMob;
                    amt[Entitylayer.getmapno()][enemyno]->spawnEntity(i, j);
                    g_Console.writeToBuffer(c, Entitylayer.getchar(j, i), 0x0C);
                    Entitylayer.setchar(' ', i, j);
                }
                enemyno++;
            }
            if (Entitylayer.getchar(j, i) == 'L')
            {
                c.X = i;
                c.Y = j;
                if (amt[Entitylayer.getmapno()][enemyno] == nullptr) //if the index is empty, fill it
                {
                    amt[Entitylayer.getmapno()][enemyno] = new StationaryMob;
                    amt[Entitylayer.getmapno()][enemyno]->spawnEntity(i, j);
                    g_Console.writeToBuffer(c, Entitylayer.getchar(j, i), 0x0C);
                    Entitylayer.setchar(' ', i, j);
                }
                enemyno++;
            }
            if (Entitylayer.getchar(j, i) == '%')
            {
                c.X = i;
                c.Y = j;
                if (amt[Entitylayer.getmapno()][enemyno] == nullptr) //if the index is empty, fill it
                {
                    amt[Entitylayer.getmapno()][enemyno] = new Ammobox;
                    amt[Entitylayer.getmapno()][enemyno]->spawnEntity(i, j);
                    g_Console.writeToBuffer(c, Entitylayer.getchar(j, i), 0x0C);
                    Entitylayer.setchar(' ', i, j);
                }
                enemyno++;
            }

            if (Entitylayer.getchar(j, i) == '+')
            {
                c.X = i;
                c.Y = j;
                if (amt[Entitylayer.getmapno()][enemyno] == nullptr) //if the index is empty, fill it
                {
                    amt[Entitylayer.getmapno()][enemyno] = new Health;
                    amt[Entitylayer.getmapno()][enemyno]->spawnEntity(i, j);
                    g_Console.writeToBuffer(c, Entitylayer.getchar(j, i), 0x0C);
                    Entitylayer.setchar(' ', i, j);
                }
                enemyno++;
            }
        }
    }
}

void renderFramerate()
{
    COORD c;
    // displays the framerate
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << 1.0 / g_dDeltaTime << "fps";
    c.X = g_Console.getConsoleSize().X - 9;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());

    // displays the elapsed time
    ss.str("");
    ss << g_dElapsedTime << "secs";
    if (bulletlist[3] != nullptr)
    {
        ss << bulletlist[3]->X();
        ss << bulletlist[3]->Y();
    }
    c.X = 0;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str(), 0x59);
}

void renderPlayerUI(player player)
{
    COORD c;
    std::ostringstream ss;
    ss << "Health "<<(char)3<<":" << player.getHP() << " Ammo: " << player.get_ammo() << " Score: " << player.getscore();
    c.X = 0;
    c.Y = g_Console.getConsoleSize().Y - 1;
    g_Console.writeToBuffer(c, ss.str());
}

void renderEntities()
{
    COORD c;
    for (int i = 0; i < 80; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            c.X = i;
            c.Y = j; 
            if (Entitylayer.getchar(j, i) == 'Z')
            {
                g_Console.writeToBuffer(c, Entitylayer.getchar(j, i), 0x0B);
            }
            if (Entitylayer.getchar(j, i) == 'K')
            {
                g_Console.writeToBuffer(c, Entitylayer.getchar(j, i), 0x0B);
            }
            if (Entitylayer.getchar(j, i) == 'F')
            {
                g_Console.writeToBuffer(c, Entitylayer.getchar(j, i), 0x0B);
            }
            if (Entitylayer.getchar(j, i) == 'L')
            {
                g_Console.writeToBuffer(c, Entitylayer.getchar(j, i), 0x0B);
            }
            if (Entitylayer.getchar(j, i) == '%')
            {
                g_Console.writeToBuffer(c, Entitylayer.getchar(j, i), 0x0F);
            }
            if (Entitylayer.getchar(j, i) == '+')
            {
                g_Console.writeToBuffer(c, Entitylayer.getchar(j, i), 0x0F);
            }
            //Add more if statments for the other type of enemies, and make the other enemies different letters
            if(Entitylayer.getchar(j, i) == '-')
            {
                g_Console.writeToBuffer(c, Entitylayer.getchar(j, i), 0x0F);
            }
            else if (Entitylayer.getchar(j, i) == 'o' || Entitylayer.getchar(j, i) == '/' ||
                Entitylayer.getchar(j, i) == '|' || Entitylayer.getchar(j, i) == '\\' ||
                Entitylayer.getchar(j, i) == '<' || Entitylayer.getchar(j, i) == ':' ||
                Entitylayer.getchar(j, i) == 'D' || Entitylayer.getchar(j, i) == '(' ||
                Entitylayer.getchar(j, i) == 'O' || Entitylayer.getchar(j, i) == ')' ||
                Entitylayer.getchar(j, i) == '_' || Entitylayer.getchar(j, i) == ':' || 
                Entitylayer.getchar(j, i) == '`' || Entitylayer.getchar(j, i) == 'X') //Boss characters
            {
                g_Console.writeToBuffer(c, Entitylayer.getchar(j, i), 0x0F);
            }
        }
    }
}


// this is an example of how you would use the input events
void renderInputEvents()
{
    // keyboard events
    COORD startPos = { 50, 2 };
    std::ostringstream ss;
    std::string key;
    for (int i = 0; i < K_COUNT; ++i)
    {
        ss.str("");
        switch (i)
        {
        case K_UP: key = "UP";
            break;
        case K_DOWN: key = "DOWN";
            break;
        case K_LEFT: key = "LEFT";
            break;
        case K_RIGHT: key = "RIGHT";
            break;
        case K_SPACE: key = "SPACE";
            break;
        default: continue;
        }
        if (g_skKeyEvent[i].keyDown)
            ss << key << " pressed";
        else if (g_skKeyEvent[i].keyReleased)
            ss << key << " released";
        else
            ss << key << " not pressed";

        COORD c = { startPos.X, startPos.Y + i };
        //g_Console.writeToBuffer(c, ss.str(), 0x17);
    }

    // mouse events    
    //ss.str("");
    //ss << "Mouse position (" << g_mouseEvent.mousePosition.X << ", " << g_mouseEvent.mousePosition.Y << ")";
    //g_Console.writeToBuffer(g_mouseEvent.mousePosition, ss.str(), 0x59);
    //ss.str("");
    //switch (g_mouseEvent.eventFlags)
    //{
    //case 0:
    //    if (g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
    //    {
    //        ss.str("Left Button Pressed");
    //        g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 1, ss.str(), 0x59);
    //    }
    //    else if (g_mouseEvent.buttonState == RIGHTMOST_BUTTON_PRESSED)
    //    {
    //        ss.str("Right Button Pressed");
    //        g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 2, ss.str(), 0x59);
    //    }
    //    else
    //    {
    //        ss.str("Some Button Pressed");
    //        g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 3, ss.str(), 0x59);
    //    }
    //    break;
    //case DOUBLE_CLICK:
    //    ss.str("Double Clicked");
    //    g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 4, ss.str(), 0x59);
    //    break;        
    //case MOUSE_WHEELED:
    //    if (g_mouseEvent.buttonState & 0xFF000000)
    //        ss.str("Mouse wheeled down");
    //    else
    //        ss.str("Mouse wheeled up");
    //    g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 5, ss.str(), 0x59);
    //    break;
    //default:        
    //    break;
    //}

}


