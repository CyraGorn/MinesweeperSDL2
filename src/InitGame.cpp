#include "InitGame.hpp"
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_events.h>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
string TITLE = "Minesweeper";
int WIDTH = 1000;
int HEIGHT = 800;
SDL_Texture *StartGameDefault, *StartGame1, *StartGame2;
SDL_Texture *modeEasy, *modeMed, *modeHard, *ChooseMode;
SDL_Texture *Easy, *Medium, *Hard;
SDL_Texture *Flag, *Square, *Mine, *Blank;
SDL_Texture *Win, *Lose, *continueGame, *buttonContinueGame;
SDL_Texture *Num[9];
SDL_Texture *numMine[11];
bool cont = 0;
bool quit = 0;
int mode = 0;
int startX = 0;
int startY = 0;
int endX = 0;
int endY = 0;
int stepX = 28;
int stepY = 26;
int Row = 0;
int Column = 0;
int countTmpMine = 0;

bool init() {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cout << "Initialize error\n";
        return 0;
    }
    window = SDL_CreateWindow(
        TITLE.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );
    if(window == NULL) {
        cout << "Create window failed\n";
        return 0;
    } else {
        renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
        if(renderer == NULL) {
            cout << "Renderer create failed\n";
            return 0;
        }
        SDL_RenderSetLogicalSize(renderer,WIDTH,HEIGHT);
    }
    if(!loadImage()) {
        cout << "Load image failed\n";
        return 0;
    }
    return 1;
}

bool loadImage() {
    bool success = 1;
    StartGameDefault = loadTexture("images/startgame/StartGameDefault.png");
    StartGame1 = loadTexture("images/startgame/StartGame1.png");
    StartGame2 = loadTexture("images/startgame/StartGame2.png");
    ChooseMode = loadTexture("images/mode/ChooseModeDefault.png");
    modeEasy = loadTexture("images/mode/modeE.png");
    modeMed = loadTexture("images/mode/modeM.png");
    modeHard = loadTexture("images/mode/modeH.png");
    Blank = loadTexture("images/countmine/Blank.png");
    Easy = loadTexture("images/Easy.png");
    Medium = loadTexture("images/Medium.png");
    Hard = loadTexture("images/Hard.png");
    Flag = loadTexture("images/Flag.png");
    Mine = loadTexture("images/Mine.png");
    Square = loadTexture("images/Square.png");
    Win = loadTexture("images/endgame/Win.png");
    Lose = loadTexture("images/endgame/Lose.png");
    continueGame = loadTexture("images/endgame/ContinueGame.png");
    buttonContinueGame = loadTexture("images/endgame/buttonContinueGame.png");
    for(int i = 0; i < 9; i++) {
        Num[i] = loadTexture("images/" + to_string(i) + ".png");
        if(Num[i] == NULL) {
            success = 0;
            cout << "File missing\n";
            break;
        }
    }
    for(int i = 0; i < 11; i++) {
        numMine[i] = loadTexture("images/countmine/m" + to_string(i) + ".png");
        if(numMine[i] == NULL) {
            success = 0;
            cout << "File missing\n";
            break;
        }
    }
    
    // if(StartGameDefault == NULL || Easy == NULL  || Medium == NULL || Hard == NULL 
    //     || ChooseMode == NULL || Win == NULL ||  Lose == NULL || Square == NULL 
    //     || Flag == NULL || Mine == NULL) {
	// 	cout << "There's something missing\n";
	// 	success = 0;
	// }
    return success;
}


SDL_Texture *loadTexture(string path) {
    SDL_Surface *image = IMG_Load(path.c_str());
    SDL_Texture *tmp = NULL;
    if(image == NULL) {
        cout << "Image missing\n";
    } else {
        tmp = SDL_CreateTextureFromSurface(renderer,image);
        SDL_FreeSurface(image);
        if(tmp == NULL) {
            cout << "Load image failed\n";
        }
    }
    return tmp;
}

void renderTexture(SDL_Texture *img, int startX, int startY, int width, int height) {
    SDL_Rect frame = {startX,startY,width,height};
    SDL_RenderCopy(renderer,img,NULL,&frame);
    SDL_RenderPresent(renderer);
}

void close() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(Easy);
    SDL_DestroyTexture(Medium);
    SDL_DestroyTexture(Hard);
    SDL_DestroyTexture(ChooseMode);
	SDL_DestroyTexture(StartGameDefault);
    SDL_DestroyTexture(StartGame1);
    SDL_DestroyTexture(StartGame2);
	SDL_DestroyTexture(Win);
	SDL_DestroyTexture(Lose);
    SDL_DestroyTexture(Flag);
    SDL_DestroyTexture(Square);
    SDL_DestroyTexture(Mine);
	IMG_Quit();
	SDL_Quit();
}

void loadScreen(SDL_Texture *img, int width, int height) {
    SDL_RenderClear(renderer);
    SDL_SetWindowSize(window,width,height);
    SDL_RenderSetLogicalSize(renderer,width,height);
	renderTexture(img,0,0,width,height);
	SDL_RenderPresent(renderer);
}