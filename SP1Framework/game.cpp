// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>

double  g_dElapsedTime;
double  g_dDeltaTime;
SKeyEvent g_skKeyEvent[K_COUNT];
SMouseEvent g_mouseEvent;

// Game specific variables here
player PlayerChar; //create player object
maps Gamemap;
maps Entitylayer;
char spawnedmaps[3] = {' ', ' ', ' '}; //Keeps track to the current map to check if a new map has been loaded by the end of a function
SGameChar   g_sChar;
Pew g_pew;
Entity* amt[5] = { nullptr, nullptr, nullptr, nullptr, nullptr };

EGAMESTATES g_eGameState = S_MAINMENU; // initial state

// Console object
Console g_Console(80, 25, "SP1 Framework");
bool initialload = true; // The initial load of the map
bool isFiring = false;
bool bulletmoving = false;
bool spawned[5] = { false, false, false ,false, false };


//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init(void)
{
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


    g_pew.m_cLocation.X = PlayerChar.getXY().X + 1;
    g_pew.m_cLocation.Y = PlayerChar.getXY().Y;



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
    case S_MAINMENU: mainmenuKBHandler(keyboardEvent); // handle menu keyboard event
        break;
    case S_PAUSE: pausemenuKBHandler(keyboardEvent);
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

void mainmenuKBHandler(const KEY_EVENT_RECORD& keyboardEvent)  //KB inputs when inside main menu
{
    EKEYS key = K_COUNT;
    switch (keyboardEvent.wVirtualKeyCode)
    {
    case VK_SPACE: key = K_SPACE; break;
    case VK_ESCAPE: key = K_ESCAPE; break;
    }
    if (key != K_COUNT)
    {
        g_skKeyEvent[key].keyDown = keyboardEvent.bKeyDown;
        g_skKeyEvent[key].keyReleased = !keyboardEvent.bKeyDown;
    }
}

void pausemenuKBHandler(const KEY_EVENT_RECORD& keyboardEvent)  //KB inputs when inside pause menu
{
    EKEYS key = K_COUNT;
    switch (keyboardEvent.wVirtualKeyCode)
    {
    case VK_ESCAPE: key = K_ESCAPE; break;
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
    if (fmod(g_dElapsedTime,0.2) <= 0.02)
    {
        moveEnemy();
    }
    moveCharacter();    // moves the character, collision detection, physics, etc
    movePew();                    // sound can be played here too.
    //Charactergravity();

    if (isFiring==true)
    {
        renderPew();
        //g_pew.m_cLocation.X++;
    }
}

void updateMainMenu()
{
    if (g_skKeyEvent[K_SPACE].keyDown) //Inputs for main menu that makes it work
    {
        g_eGameState = S_GAME;
    }
    if (g_mouseEvent.mousePosition.X >= 38 && g_mouseEvent.mousePosition.X <= 42 && g_mouseEvent.mousePosition.Y == 11 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
    {
        g_eGameState = S_GAME;
    }
    if (g_mouseEvent.mousePosition.X >= 38 && g_mouseEvent.mousePosition.X <= 41 && g_mouseEvent.mousePosition.Y == 13 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
    {
        g_bQuitGame = true;
    }
    if (g_skKeyEvent[K_ESCAPE].keyReleased) //for quitting  //put it here just in case
    {
        g_bQuitGame = true;
    }
}

void updatePauseMenu()
{
    if (g_skKeyEvent[K_ESCAPE].keyReleased)
    {
        g_eGameState = S_GAME;
    }
    if (g_mouseEvent.mousePosition.X >= 36 && g_mouseEvent.mousePosition.X <= 43 && g_mouseEvent.mousePosition.Y == 11 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
    {
        g_eGameState = S_GAME;
    }
    if (g_mouseEvent.mousePosition.X >= 38 && g_mouseEvent.mousePosition.X <= 41 && g_mouseEvent.mousePosition.Y == 13 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
    {
        g_bQuitGame = true;
    }
}

void movePew()
{
    if (isFiring == true)
    {
    int iX = g_pew.m_cLocation.X;
    int iY = g_pew.m_cLocation.Y;

        if (Gamemap.getchar(iY,iX + 1) != ' ' && Gamemap.getchar(iY,iX + 1) != 'H')
        {
            isFiring = false;
            bulletmoving = false;
            g_pew.m_cLocation.X = PlayerChar.getXY().X + 1;
            g_pew.m_cLocation.Y = PlayerChar.getXY().Y;
        }
        else
        {
            g_pew.m_cLocation.X++;

        }
    }
    //Sleep(1000);
    //isFiring = false;
}

void moveEnemy()
{
    if (g_eGameState == S_GAME)
    {
        if (Gamemap.getmapno() == 0)
        {
            for (int i = 0; i < 2; i++)
            {
                if (amt[i] != nullptr)
                {
                    amt[i]->move('Z', Gamemap);
                }
            }
        }
        if (Gamemap.getmapno() == 1)
        {
            for (int i = 2; i < 5; i++)
            {
                if (amt[i] != nullptr)
                {
                    amt[i]->move('Z', Gamemap);
                }
            }
        }
        
    }
}

void moveCharacter()
{
    // Remnaints of the bullet code for salvageing 
    //===================================================
    
    //        if (g_skKeyEvent[K_SPACE].keyDown)
    //        {
    //            Beep(1000, 30);
    //            Beep(500, 50);
    //            Beep(1500, 20);
    //            g_sChar.m_bActive = !g_sChar.m_bActive;
    //            if (Gamemap[iY][iX + 1] == ' ')
    //            {
    //                if (bulletmoving!=true)
    //                {
    //                    g_pew.m_cLocation.X = g_sChar.m_cLocation.X + 1;
    //                    g_pew.m_cLocation.Y = g_sChar.m_cLocation.Y;
    //                }
    //                
    //            }
    //        }

    //        if (g_skKeyEvent[K_SPACE].keyReleased)
    //        {
    //            if (isFiring!=true)
    //            {
    //                isFiring = true;
    //                bulletmoving = true;

    //            }

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
        Beep(1000, 30);
        Beep(500, 50);
        Beep(1500, 20);

        int iX = g_sChar.m_cLocation.X;
        int iY = g_sChar.m_cLocation.Y;


        if (Gamemap.getchar(iY, iX + 1) == ' ')
        {
            if (bulletmoving != true)
            {
                g_pew.m_cLocation.X = PlayerChar.getXY().X + 1;
                g_pew.m_cLocation.Y = PlayerChar.getXY().Y;

                //PlayerChar.getXY().X;
            }

        }

        //isFiring = true;
        for (int i = 0; i < 5; i++)
        {
            if (amt[i] != nullptr)
            {
                Gamemap.setchar(' ', amt[i]->getXY().X, amt[i]->getXY().Y);
                delete amt[i];
                amt[i] = nullptr;
            }
        }
        //Potentially where the shooting code goes
        //You can but the direction facing in the above movement codes, make the faced direction a data member of the player object
    }
    if (g_skKeyEvent[K_SPACE].keyReleased)
    {
        if (isFiring != true)
        {
            isFiring = true;
            bulletmoving = true;

        }

    }
    if (PlayerChar.moveplayer(Gamemap, direction) || initialload) //This if statement is to check whether the is a map change since the map changing code is in the moveplayer code
    {                                               //Regardless of true or false, the character will still move
        spawnEnemy();
        if (initialload)
        {
            initialload = false; //Changes to false after the inital map load
        }
    }
    if (PlayerChar.collisioncheck(Gamemap) == 'Z') // collision work, just have to put something here
    {
        PlayerChar.setHP(PlayerChar.getHP() - 1);
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
    COORD c;
    c.Y = 9;
    c.X = g_Console.getConsoleSize().X / 2 - 6;
    g_Console.writeToBuffer(c, "Mask the World", 0x03);
    c.Y += 2;
    c.X = g_Console.getConsoleSize().X / 2 - 2;
    g_Console.writeToBuffer(c, "start", 0xF0);
    c.Y += 2;
    c.X = g_Console.getConsoleSize().X / 2 - 2;
    g_Console.writeToBuffer(c, "quit", 0xF0);
}

void renderPauseMenu()  // renders the main menu
{
    COORD c;
    c.Y = 9;
    c.X = g_Console.getConsoleSize().X / 2 - 2;
    g_Console.writeToBuffer(c, "Pause", 0x8F);
    c.Y = g_Console.getConsoleSize().Y / 2 - 1;
    c.X = g_Console.getConsoleSize().X / 2 - 4;
    g_Console.writeToBuffer(c, "continue", 0xF0);
    c.Y += 2;
    c.X = g_Console.getConsoleSize().X / 2 - 2;
    g_Console.writeToBuffer(c, "quit", 0xF0);
}
void renderGame()
{
    renderMap();        // renders the map to the buffer first
    renderCharacter();
    renderPlayerUI(PlayerChar);
    if (isFiring == true)
    {
        renderPew();

    }// renders the character into the buffer
}

void renderMap()
{
    //// Set up sample colours, and output shadings
    //const WORD colors[] = {
    //    0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
    //    0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6,
    //    0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
    //    0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
    //};

    COORD c;
    //for (int i = 0; i < 12; ++i)
    //{
    //    c.X = 5 * i;
    //    c.Y = i + 1;
    //    colour(colors[i]);
    //    g_Console.writeToBuffer(c, " ����", colors[i]);
    //}

    for (int i = 0; i < 80; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            c.X = i;
            c.Y = j;
            if (Gamemap.getchar(j,i) == '=') // '=' are coloured differently for the floor
            {
                g_Console.writeToBuffer(c, Gamemap.getchar(j,i), 0x0E);
            }
            else if (Gamemap.getchar(j,i) == 'H')
            {
                g_Console.writeToBuffer(c, Gamemap.getchar(j,i), 0x0C);
            }
            else if (Gamemap.getchar(j,i) == '1')
            {
                g_Console.writeToBuffer(c, Gamemap.getchar(j,i), 0x01);
            }
            else if (Gamemap.getchar(j, i) == 'Z')
            {
                g_Console.writeToBuffer(c, Gamemap.getchar(j, i), 0x09);
            }
            else if (Gamemap.getchar(j,i) == 'K')
            {
                g_Console.writeToBuffer(c, Gamemap.getchar(j,i), 0x0A);
            }
            else //Normal colour of black text with blue background
            {
                g_Console.writeToBuffer(c, Gamemap.getchar(j,i), 0x0F); //Btw after the 0x the first number is the background colour and the second is the text colour
            }//Black is 0, background blue is 1 and a kind of green is A, F is white
        }
    }
}

void renderCharacter()
{
    // Draw the location of the character
    WORD charColor = 0x0A;
    if (g_sChar.m_bActive)
    {
        charColor = 0x0F;
    }
    //g_Console.writeToBuffer(g_sChar.m_cLocation, (char)1, charColor);
    g_Console.writeToBuffer(PlayerChar.getXY(), char(1), 0x0F);
}

void renderPew()
{
    WORD charColor = 0x0F;

    g_Console.writeToBuffer(g_pew.m_cLocation, '-', charColor);
}

void spawnEnemy() //TODO: Set it so that when map changes, the enemies would be deleted and become nullptr for future use
//{  
//    if (g_eGameState == S_GAME)
//    {
//        if (Gamemap.getmapno() == 0 && spawnedmaps[0] == ' ')
//        {
//            for (int i = 0; i < 2; i++)
//            {
//                if (spawned[i] == false) //Only happen once
//                {
//                    amt[i] = new Entity;
//                    amt[i]->spawnEntity(2, 2);
//                    if (i == 0)
//                    {
//                        amt[i]->setX(32);
//                        amt[i]->setY(22);
//                    }
//                    if (i == 1)
//                    {
//                        amt[i]->setX(33);
//                        amt[i]->setY(22);
//                    }
//                    spawned[i] = true;
//                    amt[i]->addtomap('Z', Gamemap);
//                }
//            }
//            spawnedmaps[0] = '0';
//        }
//        if (Gamemap.getmapno() == 1 && spawnedmaps[1] == ' ')
//        {
//            for (int i = 2; i < 5; i++)
//            {
//                if (spawned[i] == false) //Only happen once
//                {
//                    amt[i] = new Entity;
//                    amt[i]->spawnEntity(2, 2);
//                    if (i == 2)
//                    {
//                        amt[i]->setX(31);
//                        amt[i]->setY(22);
//                    }
//                    if (i == 3)
//                    {
//                        amt[i]->setX(33);
//                        amt[i]->setY(22);
//                    }
//                    if (i == 4)
//                    {
//                        amt[i]->setX(35);
//                        amt[i]->setY(22);
//                    }
//                    amt[i]->addtomap('Z', Gamemap);
//                    spawned[i] = true; 
//                }
//            }
//            spawnedmaps[1] = '1';
//        }
//    }
//}

{  
    if (g_eGameState == S_GAME)
    {
        if (Gamemap.getmapno() == 0 && spawnedmaps[0] == ' ')
        {
            for (int i = 0; i < 2; i++)
            {
                if (amt[i] != nullptr)
                {
                    delete amt[i];
                    amt[i] = nullptr;
                }
                amt[i] = new Entity;
                amt[i]->spawnEntity(2, 2);
                if (i == 0)
                {
                    amt[i]->setX(32);
                    amt[i]->setY(22);
                }
                if (i == 1)
                {
                    amt[i]->setX(33);
                    amt[i]->setY(22);
                }
                amt[i]->addtomap('Z', Gamemap);
                //if (spawned[i] == false) //Only happen once
                //{
                //    amt[i] = new Entity;
                //    amt[i]->spawnEntity(2, 2);
                //    if (i == 0)
                //    {
                //        amt[i]->setX(32);
                //        amt[i]->setY(22);
                //    }
                //    if (i == 1)
                //    {
                //        amt[i]->setX(33);
                //        amt[i]->setY(22);
                //    }
                //    spawned[i] = true;
                //    amt[i]->addtomap('Z', Gamemap);
                //}
                if (i == 0)
                {
                    spawnedmaps[i] = '0';
                }
                else
                {
                    spawnedmaps[i] = ' ';
                }
            }
        }
        if (Gamemap.getmapno() == 1 && spawnedmaps[1] == ' ')
        {
            for (int i = 2; i < 5; i++)
            {
                for (int i = 0; i < 3; i++)
                {
                    if (i == 1)
                    {
                        spawnedmaps[i] = '1';
                    }
                    else
                    {
                        spawnedmaps[i] = ' ';
                    }
                }
                if (amt[i] != nullptr)
                {
                    delete amt[i];
                    amt[i] = nullptr;
                }
                else
                {
                    amt[i] = new Entity;
                    amt[i]->spawnEntity(2, 2);
                    if (i == 2)
                    {
                        amt[i]->setX(31);
                        amt[i]->setY(22);
                    }
                    if (i == 3)
                    {
                        amt[i]->setX(33);
                        amt[i]->setY(22);
                    }
                    if (i == 4)
                    {
                        amt[i]->setX(35);
                        amt[i]->setY(22);
                    }
                    amt[i]->addtomap('Z', Gamemap);
                }
            }
            for (int i = 0; i < 3; i++)
            {
                if (i == 1)
                {
                    spawnedmaps[i] = '1';
                }
                else
                {
                    spawnedmaps[i] = ' ';
                }
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
    if (amt[1] != nullptr)
    {
        ss << amt[1]->X();
        ss << amt[1]->Y();
    }
    c.X = 0;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str(), 0x59);
}

void renderPlayerUI(player player)
{
    COORD c;
    std::ostringstream ss;
    ss << "Health "<<(char)3<<":" << player.getHP() << " Ammo: " << player.get_ammo() << " Energy: " << player.getMP();
    c.X = 0;
    c.Y = g_Console.getConsoleSize().Y - 1;
    g_Console.writeToBuffer(c, ss.str());
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


