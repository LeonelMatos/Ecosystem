#include <stdio.h>
#include <string.h>

/// Warning
/// List of warning that don't break the program
/// but prohibits unrecommended actions.

/*DEFINES*/
#define RED "\x1B[0;31m"
#define GRN "\x1B[0;32m"
#define YEL "\x1B[0;33m"
#define BLU "\x1B[0;34m"
#define MAG "\x1B[0;35m"
#define CYN "\x1B[0;36m"
#define MR_WHITE "\x1B[0;37m"
#define RST "\x1B[0m" ///Reset (don't know what it does(resets?))
/*Bold*/
#define B_RED "\x1B[1;31m"
#define B_GRN "\x1B[1;32m"
#define B_YEL "\x1B[1;33m"
#define B_BLU "\x1B[1;34m"
#define B_MAG "\x1B[1;35m"
#define B_CYN "\x1B[1;36m"
#define B_MR_WHITE "\x1B[37m"

typedef enum
{
    ENTITIES_LIMIT = 1000,
    OUT_OF_BOUNDS,
    ENTITY_NOT_FOUND,
    WRONG_DIRECTION,

} Warning;

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
    default:
        return "Unexpected error. Please check if spelled correctly";
    }
}

void print_color (const char* color) {
    printf("%s", color);
}

void reset_color () {
    printf(MR_WHITE);
}
