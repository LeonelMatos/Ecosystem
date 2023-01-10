#include <stdio.h>
#include <string.h>

/** \file warning.h
*  Warning\n
* List of warnings that don't break the program
* but prohibits unrecommended actions.
*/

/*DEFINES*/
///Red
#define RED "\x1B[0;31m"
///Green
#define GRN "\x1B[0;32m"
///Yellow
#define YEL "\x1B[0;33m"
///Blue
#define BLU "\x1B[0;34m"
///Magenta
#define MAG "\x1B[0;35m"
///Cyan
#define CYN "\x1B[0;36m"
///White
#define MR_WHITE "\x1B[0;37m"
///Reset
#define RST "\x1B[0m"
/*Bold*/
///Bold Red
#define B_RED "\x1B[1;31m"
///Bold Green
#define B_GRN "\x1B[1;32m"
///Bold Yellow
#define B_YEL "\x1B[1;33m"
///Bold Blue
#define B_BLU "\x1B[1;34m"
///Bold Magenta
#define B_MAG "\x1B[1;35m"
///Bold Cyan
#define B_CYN "\x1B[1;36m"
///Bold White
#define B_MR_WHITE "\x1B[37m"

/// @brief List of warning error names
typedef enum
{
    ENTITIES_LIMIT = 1000,
    OUT_OF_BOUNDS,
    ENTITY_NOT_FOUND,
    WRONG_DIRECTION,
    INVALID_ARGUMENT,

} Warning;

/// @brief Converts a warning type to its correspondent string
/// @param w warning type
/// @return string of the given warning
char * warning_to_string (const Warning w) {
    switch (w)
    {
    case ENTITIES_LIMIT:
        return "Too many entities. Cannot create new one";
    case OUT_OF_BOUNDS:
        return "Entity placed outside of map area";
    case ENTITY_NOT_FOUND:
        return "Entity not found with given parameters";
    case WRONG_DIRECTION:
        return "Invalid direction. Please check input";
    case INVALID_ARGUMENT:
        return "Given an invalid argument. Please check input";
    default:
        return "Unexpected error. Please check if spelled correctly";
    }
}

/// @brief Receives a string color and prints it to color the next prints
/// @param color color macros from warning.h
void print_color (const char* color) {
    printf("%s", color);
}

/// @brief Returns the print color to white
void reset_color () {
    printf(MR_WHITE);
}
