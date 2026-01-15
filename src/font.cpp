#include "font.h"

void Font::printChar(char c)
{
    // 2D array representing character
    u32 ROWS = 5;
    u32 COLS = 4;
    char carr[ROWS][COLS];
    switch(c)
    {

        case 'A':
        {
            const char A [ROWS][COLS] = {
                {' ', '#','#', ' '},
                {'#', ' ', ' ', '#'},
                {'#', '#', '#', '#'},
                {'#', ' ', ' ', '#'},
                {'#', ' ', ' ', '#'}
            };
            std::memcpy(carr, A, sizeof(carr));
            break;
        }
        default:
            std::cerr << "Character " << c << " not defined in font.\n"; 
            break;
    }
    for(u32 i = 0; i < ROWS; i++)
    {
        for(u32 j = 0; j < COLS; j++)
        {
            std::cout << carr[i][j];
        }
        std::cout << "\n";
    }
    
}