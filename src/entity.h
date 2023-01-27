/**
 * @brief Entity
 * Values and functions to manage and represent an entity
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

/// @brief Type of entity in char
typedef enum
{
    Rabbit = 'R',
    Fox = 'F',
    Tree = 'T',
    Grass = 'G',

} Type;

/// @brief Position of the entity
typedef struct {
	unsigned int x;
	unsigned int y;
} Position;

/// @brief Struct of entity with position and type
typedef struct{
    Position pos;
    Type type;

} Entity;

/// @brief Returns the color of the entity based on its type
/// @param type Type of entity in char
/// @return Color macro string
char* entity_color (Type type) {
    switch (type) {
        case Rabbit:
            return B_CYN;
        case Fox:
            return B_YEL;
        case Tree:
            return B_GRN;
        default:
            return B_MR_WHITE;
    }
}

/// @brief Returns the image as emoji of the entity based on its type
/// @param type Type of entity in char
/// @return emoji macro string
char* entity_image (Type type) {
    switch (type) {
        case Rabbit:
            return "🐰";
        case Fox:
            return "🦊";
        case Tree:
            return "🌲";
        default:
            return " ";
            
    }
}
