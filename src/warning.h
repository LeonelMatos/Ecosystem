/// Warning
/// List of warning that don't break the program
/// but prohibits unrecommended actions.

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

typedef enum 
{
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    PURPLE,
    CYAN,
    MR_WHITE,

} Color;

void print_color (const Color color, const short int bold) {
    char cmd[11] = "\033[0;30m";
    if (bold) {
        cmd[5] = '1';
    }
    cmd[8] = color + 48;

    for (int i = 0; i < 10; i++) printf("%c", cmd[i]);
    printf("\n");
    printf("%s", cmd);

    /// @todo It was supposed to work, it doesn't. Fix it somehow!
}

void reset_color () {
    printf("\033[0m");
}