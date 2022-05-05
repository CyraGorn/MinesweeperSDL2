#include "InitGame.hpp"
#include "InGame.hpp"
#include "Action.hpp"

int main(int argc, char *argv[]) {
    if(init()) {
        loadScreen(InitScreen,1000,800);
        SDL_Delay(800);
        startGame(quit);
        SDL_Delay(500);
        do {
            bool lose = false;
            InGame ig;
            cont = 0;
            mode = 0;
            humanChooseMode(quit,mode);
            SDL_Delay(500);
            ig.initialize(mode);
			while(!quit) {
                showTmpMine(countTmpMine);
				int chooseRow = 0;
                int chooseCol = 0;
                humanInput(quit,chooseRow,chooseCol);
                ig.handleGame(chooseRow,chooseCol,quit,lose);
                showTmpMine(countTmpMine);
                if(lose) {
                    break;
                }
                if(ig.getMine() == 0){
                    SDL_Delay(1000);
                    break;
                }
			}
            if(!quit) {
                if(lose) {
                    ig.printAll();
                    SDL_Delay(500);
                    loadScreen(Lose,1000,800);
                    SDL_Delay(1000);
                } else {
                    loadScreen(Win,1000,800);
                    SDL_Delay(1000);
                }
                cont = continuePlay(quit);
            }
        } while(cont == 1 && quit == 0);
    }
    close();
    return 0;
}