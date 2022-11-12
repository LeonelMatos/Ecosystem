typedef enum
{
    Rabbit,
    Fox,

} Type;

typedef struct {
	int x;
	int y;
} Position;

typedef struct{
    Position pos;
    Type type;

} Entity;
