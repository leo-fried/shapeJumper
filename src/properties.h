#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <cstdlib> // For general purpose functions
#include <iostream>
#include <ncurses.h> // Set up ternminal for game interface
#include <string>

// Type Definitions
using u8 = unsigned char;
using u16 = short unsigned int;
using u32 = unsigned int;
using u64 = long long unsigned int;

using s8 = char;
using s16 = short int;
using s32 = int;
using s64 = long long int;

extern bool g_debug; // For debug mode

/**
 * @brief Initializes the terminal for ncurses mode.
 */
void initTerminal();
/**
 * @brief Shuts down ncurses mode and restores the terminal.
 */
void shutdownTerminal();

#endif // PROPERTIES_H