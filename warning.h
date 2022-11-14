/// Warning
/// List of warning that don't break the program
/// but prohibits unrecommended actions.

typedef enum
{
    ENTITIES_LIMIT = 1000,
    OUT_OF_BOUNDS,

} Warning;

char * warning_to_string (Warning w) {
    switch (w)
    {
    case ENTITIES_LIMIT:
        return "Too many entities. Cannot create new one";
    case OUT_OF_BOUNDS:
        return "Entity placed outside of map area";
    default:
        return "Unexpected error. Please check if spelled correctly";
    }
}