#include "font.h"

void Font::printChar(char c, u32 row)
{
    // 2D array representing character
    u32 ROWS = 5;
    u32 COLS = 5;
    char carr[ROWS][COLS];
    switch(c)
    {

        case 'A':
        {
            const char A [ROWS][COLS] = {
                {' ', '#','#', ' ', ' '},
                {'#', ' ', ' ', '#', ' '},
                {'#', '#', '#', '#', ' '},
                {'#', ' ', ' ', '#', ' '},
                {'#', ' ', ' ', '#', ' '}
            };
            std::memcpy(carr, A, sizeof(carr));
            break;
        }
        case 'B':
        {
            const char B [ROWS][COLS] = {
                {'#', '#','#', ' ', ' '},
                {'#', ' ', ' ', '#', ' '},
                {'#', '#', '#', ' ', ' '},
                {'#', ' ', ' ', '#', ' '},
                {'#', '#', '#', ' ', ' '}
            };
            std::memcpy(carr, B, sizeof(carr));
            break;
        }
        case 'C':
        {
            const char C [ROWS][COLS] = {
                {'#', '#','#', '#', ' ' },
                {'#', ' ', ' ', ' ', ' '},
                {'#', ' ', ' ', ' ', ' '},
                {'#', ' ', ' ', ' ', ' '},
                {'#', '#', '#', '#', ' '}
            };
            std::memcpy(carr, C, sizeof(carr));
            break;
        }
        case 'D':
        {
            const char D [ROWS][COLS] = {
                {'#', '#','#', ' ', ' '},
                {'#', ' ', ' ', '#', ' '},
                {'#', ' ', ' ', '#', ' '},
                {'#', ' ', ' ', '#', ' '},
                {'#', '#', '#', ' ', ' '}
            };
            std::memcpy(carr, D, sizeof(carr));
            break;
        }
        case 'E':
        {
            const char E [ROWS][COLS] = {
                {'#', '#','#', '#', ' '},
                {'#', ' ', ' ', ' ', ' '},
                {'#', '#', '#', ' ', ' '},
                {'#', ' ', ' ', ' ', ' '},
                {'#', '#', '#', '#', ' '}
            };
            std::memcpy(carr, E, sizeof(carr));
            break;
        }
        case 'F':
        {
            const char F [ROWS][COLS] = {
                {'#', '#','#', '#', ' '},
                {'#', ' ', ' ', ' ', ' '},
                {'#', '#', '#', ' ', ' '},
                {'#', ' ', ' ', ' ', ' '},
                {'#', ' ', ' ', ' ', ' '}
            };
            std::memcpy(carr, F, sizeof(carr));
            break;
        }
        case 'G':
        {
            const char G [ROWS][COLS] = {
                {' ', '#','#', '#', ' '},
                {'#', ' ', ' ', ' ', ' '},
                {'#', ' ', '#', '#', ' '},
                {'#', ' ', ' ', '#', ' '},
                {' ', '#','#', '#', ' '}
            };
            std::memcpy(carr, G, sizeof(carr));
            break;
        }
        case 'H':
        {
            const char H [ROWS][COLS] = {
                {'#', ' ', ' ', '#', ' '},
                {'#', ' ', ' ', '#', ' '},
                {'#', '#', '#', '#', ' '},
                {'#', ' ', ' ', '#', ' '},
                {'#', ' ', ' ', '#', ' '}
            };
            std::memcpy(carr, H, sizeof(carr));
            break;
        }
        case 'I':
        {
            const char I [ROWS][COLS] = {
                {'#', '#','#', '#', ' '},
                {' ', ' ', '#', ' ', ' '},
                {' ', ' ', '#', ' ', ' '},
                {' ', ' ', '#', ' ', ' '},
                {'#', '#','#', '#', ' '}
            };
            std::memcpy(carr, I, sizeof(carr));
            break;
        }
        case 'J':
        {
            const char J [ROWS][COLS] = {
                {' ', ' ', '#', '#', ' '},
                {' ', ' ', ' ', '#', ' '},
                {' ', ' ', ' ', '#', ' '},
                {'#', ' ', ' ', '#', ' '},
                {' ', '#','#', ' ', ' '}
            };
            std::memcpy(carr, J, sizeof(carr));
            break;
        }
        case 'K':
        {
            const char K [ROWS][COLS] = {
                {'#', ' ', ' ', '#', ' '},
                {'#', ' ', '#', ' ', ' '},
                {'#', ' ', '#', ' ', ' '},
                {'#', '#', ' ', ' ', ' '},
                {'#', ' ', '#', ' ', ' '},
                {'#', ' ', ' ', '#', ' '}
            };
            std::memcpy(carr, K, sizeof(carr));
            break;
        }
        case 'L':
        {
            const char L [ROWS][COLS] = {
                {'#', ' ', ' ', ' ', ' '},
                {'#', ' ', ' ', ' ', ' '},
                {'#', ' ', ' ', ' ', ' '},
                {'#', ' ', ' ', ' ', ' '},
                {'#', '#','#', '#', ' '}
            };
            std::memcpy(carr, L, sizeof(carr));
            break;
        }
        case 'M':
        {
            const char M [ROWS][COLS] = {
                {'#', ' ', ' ', ' ','#'},
                {'#', '#', ' ','#', '#'},
                {'#', ' ', '#', ' ', '#'},
                {'#', ' ', ' ', ' ', '#'},
                {'#', ' ', ' ', ' ', '#'}
            };
            std::memcpy(carr, M, sizeof(carr));
            break;
        }
        case 'N':
        {
            const char N [ROWS][COLS] = {
                {'#', ' ', ' ', '#', ' '},
                {'#', '#', ' ', '#', ' '},
                {'#', '#', ' ', '#', ' '},
                {'#', ' ', '#', '#', ' '},
                {'#', ' ', ' ', '#', ' '},
                {'#', ' ', ' ', '#', ' '}
            };
            std::memcpy(carr, N, sizeof(carr));
            break;
        }
        case 'O':
        {
            const char O [ROWS][COLS] = {
                {' ', '#','#', ' ', ' '},
                {'#', ' ', ' ', '#', ' '},
                {'#', ' ', ' ', '#', ' '},
                {'#', ' ', ' ', '#', ' '},
                {' ', '#','#', ' ', ' '}
            };
            std::memcpy(carr, O, sizeof(carr));
            break;
        }
        case 'P':
        {
            const char P [ROWS][COLS] = {
                {'#', '#','#', ' ', ' '},
                {'#', ' ', ' ', '#', ' '},
                {'#', '#','#', ' ', ' '},
                {'#', ' ', ' ', ' ', ' '},
                {'#', ' ', ' ', ' ', ' '}
            };
            std::memcpy(carr, P, sizeof(carr));
            break;
        }
        case 'Q':
        {
            const char Q [ROWS][COLS] = {
                {' ', '#','#', ' ', ' '},
                {'#', ' ', ' ', '#', ' '},
                {'#', ' ', ' ', '#', ' '},
                {'#', ' ', '#', ' ', ' '},
                {' ', '#','#', '#', ' '}
            };
            std::memcpy(carr, Q, sizeof(carr));
            break;
        }
        case 'R':
        {
            const char R [ROWS][COLS] = {
                {'#', '#','#', ' ', ' '},
                {'#', ' ', ' ', '#', ' '},
                {'#', '#','#', ' ', ' '},
                {'#', ' ', '#', ' ', ' '},
                {'#', ' ', ' ', '#', ' '}
            };
            std::memcpy(carr, R, sizeof(carr));
            break;
        }
        case 'S':
        {
            const char S [ROWS][COLS] = {
                {' ', '#','#', '#', ' '},
                {'#', ' ', ' ', ' ', ' '},
                {' ', '#','#', ' ', ' '},
                {' ', ' ', ' ', '#', ' '},
                {'#', '#','#', ' ', ' '}
            };
            std::memcpy(carr, S, sizeof(carr));
            break;
        }
        case 'T':
        {
            const char T [ROWS][COLS] = {
                {'#', '#','#', '#', ' '},
                {' ', ' ', '#', ' ', ' '},
                {' ', ' ', '#', ' ', ' '},
                {' ', ' ', '#', ' ', ' '},
                {' ', ' ', '#', ' ', ' '}
            };
            std::memcpy(carr, T, sizeof(carr));
            break;
        }
        case 'U':
        {
            const char U [ROWS][COLS] = {
                {'#', ' ', ' ', '#', ' '},
                {'#', ' ', ' ', '#', ' '},
                {'#', ' ', ' ', '#', ' '},
                {'#', ' ', ' ', '#', ' '},
                {' ', '#','#', ' ', ' '}
            };
            std::memcpy(carr, U, sizeof(carr));
            break;
        }
        case 'V':
        {
            const char V [ROWS][COLS] = {
                {'#', ' ', ' ', ' ', '#'},
                {'#', ' ', ' ', ' ', '#'},
                {'#', ' ', ' ', ' ', '#'},
                {' ', '#', ' ', '#', ' '},
                {' ', ' ', '#', ' ', ' '}
            };
            std::memcpy(carr, V, sizeof(carr));
            break;
        }
        case 'W':
        {
            const char W [ROWS][COLS] = {
                {'#', ' ', ' ', ' ', '#'},
                {'#', ' ', ' ', ' ', '#'},
                {'#', ' ', '#', ' ', '#'},
                {'#', '#', ' ', '#', '#'},
                {'#', ' ', ' ', ' ', '#'}
            };
            std::memcpy(carr, W, sizeof(carr));
            break;
        }
        case 'X':
        {
            const char X [ROWS][COLS] = {
                {'#', ' ', ' ', '#', ' '},
                {' ', '#', '#', ' ', ' '},
                {' ', ' ', '#', ' ', ' '},
                {' ', '#', '#', ' ', ' '},
                {'#', ' ', ' ', '#', ' '}
            };
            std::memcpy(carr, X, sizeof(carr));
            break;
        }
        case 'Y':
        {
            const char Y [ROWS][COLS] = {
                {'#', ' ', ' ', ' ', '#'},
                {' ', '#', '#', '#', ' '},
                {' ', ' ', '#', ' ', ' '},
                {' ', ' ', '#', ' ', ' '},
                {' ', ' ', '#', ' ', ' '}
            };
            std::memcpy(carr, Y, sizeof(carr));
            break;
        }
        case 'Z':
        {
            const char Z [ROWS][COLS] = {
                {'#', '#','#', '#', ' '},
                {' ', ' ', '#', ' ', ' '},
                {' ', '#', ' ', ' ', ' '},
                {'#', ' ', ' ', ' ', ' '},
                {'#', '#','#', '#', ' '}
            };
            std::memcpy(carr, Z, sizeof(carr));
            break;
        }
        case '1':
        {
            const char ONE [ROWS][COLS] = {
                {' ', ' ', '#', ' ', ' '},
                {' ', '#', '#', ' ', ' '},
                {' ', ' ', '#', ' ', ' '},
                {' ', ' ', '#', ' ', ' '},
                {' ', '#','#', '#', ' '}
            };
            std::memcpy(carr, ONE, sizeof(carr));
            break;
        }
        case '2':
        {
            const char TWO [ROWS][COLS] = {
                {' ', '#','#', '#', ' '},
                {'#', ' ', ' ', '#', ' '},
                {' ', ' ', '#', ' ', ' '},
                {' ', '#', ' ', ' ', ' '},
                {'#', '#','#', '#', ' '}
            };
            std::memcpy(carr, TWO, sizeof(carr));
            break;
        }
        case '3':
        {
            const char THREE [ROWS][COLS] = {
                {' ', '#','#', '#', ' '},
                {'#', ' ', ' ', '#', ' '},
                {' ', ' ', '#', '#', ' '},
                {'#', ' ', ' ', '#', ' '},
                {' ', '#','#', '#', ' '}
            };
            std::memcpy(carr, THREE, sizeof(carr));
            break;
        }
        case '.':
        {
            const char PER [ROWS][COLS] = {
                {' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' ', ' '},
                {' ', '#', ' ', ' ', ' '}
            };
            std::memcpy(carr, PER, sizeof(carr));
            break;
        }
        case ':':
        {
            const char COL [ROWS][COLS] = {
                {' ', ' ', ' ', ' ', ' '},
                {' ', '#', ' ', ' ', ' '},
                {' ', ' ', ' ', ' ', ' '},
                {' ', '#', ' ', ' ', ' '},
                {' ', ' ', ' ', ' ', ' '}
            };
            std::memcpy(carr, COL, sizeof(carr));
            break;
        }
        case '!':
        {
            const char EX [ROWS][COLS] = {
                {' ', '#', ' ', ' ', ' '},
                {' ', '#', ' ', ' ', ' '},
                {' ', '#', ' ', ' ', ' '},
                {' ', ' ', ' ', ' ', ' '},
                {' ', '#', ' ', ' ', ' '}
            };
            std::memcpy(carr, EX, sizeof(carr));
            break;
        }
        default:
            const char SP [ROWS][COLS] = {
                {' ', ' ',' ', ' ', ' '},
                {' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' ', ' '},
                {' ', ' ',' ', ' ', ' '}
            };
            std::memcpy(carr, SP, sizeof(carr)); 
            break;
    }
    for(u32 i = 0; i < ROWS; i++)
    {
        printw("%c", carr[row][i]);
    }
    
}

void Font::printText(std::string text)
{
    for(u32 row = 0; row < 5; row++)
    {
        for(const auto& c : text)
        {
            printChar(c, row);
            printw(" "); // Space between characters
        }
        printw("\n"); // New line after each row
    }
    printw("\n"); // Extra line after the text
    refresh();
}