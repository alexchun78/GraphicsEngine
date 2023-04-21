#include <iostream>
#include "MainGame.h"

int main(int argc, char** argv)
{
    MainGame mainGame;
    mainGame.Run();

    std::cout << "Enter any key to quit...";
    int a;
    std::cin >> a;
    return 0;
}