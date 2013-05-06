/*
 -------------------------------------------------------------------------------
 ___FILENAME___
 ___PROJECTNAME___ Project
 
 Initially created by ___FULLUSERNAME___ (___WEBSITE___) on ___DATE___.
 
 Version 1.0
 -------------------------------------------------------------------------------
 */


/* ---------------------------------- NOTE -------------------------------------
 
 NEED TO ADD THE SDL.framework!!! 
 (I have not been able to figure out how to include it in the template.)
 
 Do this by:
 1. Click on your target to bring up the Build Settings/Build Phases/Build Rules tabs.
 2. In the Build Phases tab under Link Binary With Libraries click "Add Other...".
 3. Navigate to "/Library/Frameworks" directory.
 4. Open "SDL.framework"
 
 For more information see http://lazyfoo.net/SDL_tutorials/lesson01/mac/xcode/index.php
 
*/

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "SDL/SDL.h"

//------------------------------------------------------------------------------
// Global Varible Declarations
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Functions
//------------------------------------------------------------------------------

int main( int argc, char* args[] ) {
    
    //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );

    //Quit SDL
    SDL_Quit();

    return 0;
}