/// Warning
/// List of warning that don't break the program
/// but prohibits unrecommended actions.

typedef enum
{
    ENTITIES_LIMIT = 1000,

} Warning;

char * warning_to_string (Warning w) {
    switch (w)
    {
    case ENTITIES_LIMIT:
        return "Too many entities. Cannot create new one";
    default:
        return "Unexpected error. Please check if spelled correctly.";
    }
}