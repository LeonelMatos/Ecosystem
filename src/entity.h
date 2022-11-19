typedef enum
{
    Rabbit='R',
    Fox='F',
    Grass='.',

} Type;

typedef struct {
	unsigned int x;
	unsigned int y;
} Position;

typedef struct{
    Position pos;
    Type type;

} Entity;
