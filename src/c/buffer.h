#ifndef BUFFER_H
#define BUFFER_H

#define ID_LEN 32
#define BUFFER_SIZE 32

typedef enum direction{
	NORTH,
	EAST,
	SOUTH,
	WEST
} direction;

typedef enum state{
	RED,
	REDYELLOW,
	GREEN,
	YELLOW
}state;

typedef struct vehicle{
	char id[ID_LEN+1];
	direction start;
	direction end;
} vehicle;

typedef struct v_buffer{
	vehicle vs[BUFFER_SIZE];
	int head;
	int tail;
	int count;
} v_buffer;

void buf_init(v_buffer* buf);

int buf_push(v_buffer* buf, const vehicle* v);

int buf_pop(v_buffer* buf, vehicle* out);

int buf_count(v_buffer* buf);

int buf_first(v_buffer* buf, vehicle* out);

char buf_nth_v_id(v_buffer* buf, int n);

#endif // BUFFER_H