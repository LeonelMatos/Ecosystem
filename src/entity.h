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
    Rabbit = 'R',
    Fox = 'F',
    Tree = 'T',

} Type;

typedef struct {
	unsigned int x;
	unsigned int y;
} Position;

typedef struct{
    Position pos;
    Type type;

} Entity;

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
