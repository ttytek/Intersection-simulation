#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define ID_LEN 32
#define BUFFER_SIZE 32
#define STATES 9

/*
Stany świateł
0 stan -wszyscy czerwone
1,2,3,4 n-1 kierunek ma wszystkie swiatla zielone

5-8 ponizej
\     |  |  |
     |     |
     |  |  |
     |     |
     |  |  |
-----+-----+-----
     |<  ^ |     
- - -| | | |- - -
     | v  >|     
-----+-----+-----
     |  |  |
     |     |
     |  |  |
     |     |
     |  |  |

	 |  |  |
     |     |
     |  |  |
     |     |
     |  |  |
-----+-----+-----
     | <- ^|     
- - -|     |- - -
     |v  ->|     
-----+-----+-----
     |  |  |
     |     |
     |  |  |
     |     |
     |  |  |

     |  |  |
     |     |
     |  |  |
     |     |
     |  |  |
-----+-----+-----
     |<   ^|     
- - -| \ \ |- - -
     |v   >|     
-----+-----+-----
     |  |  |
     |     |
     |  |  |
     |     |
     |  |  |

     |  |  |
     |     |
     |  |  |
     |     |
     |  |  |
-----+-----+-----
     |<  ^ |     
- - -|  // |- - -
     |  v >|     
-----+-----+-----
     |  |  |
     |     |
     |  |  |
     |     |
     |  |  |


*/

const bool states[9][4][4]= {
	{
		{false, false, false, false},
		{false, false, false, false},
		{false, false, false, false},
		{false, false, false, false},
	},
	{
		{true, true, true, true},
		{false, false, false, false},
		{false, false, false, false},
		{false, false, false, false},
	},
	{
		{false, false, false, false},
		{true, true, true, true},
		{false, false, false, false},
		{false, false, false, false},
	},
	{
		{false, false, false, false},
		{false, false, false, false},
		{true, true, true, true},
		{false, false, false, false},
	},
	{
		{false, false, false, false},
		{false, false, false, false},
		{false, false, false, false},
		{true, true, true, true},
	},
	{ // na wprost
		{false, false, true, true},
		{false, false, false, false},
		{true, true, false, false},
		{false, false, false, false},
	},
	{ // na wprost
		{false, false, false, false},
		{true, false, false, true},
		{false, false, false, false},
		{false, true, true, false},
	},
	{ // w lewo/zawracanie
		{true, true, false, false},
		{false, false, false, false},
		{false, false, true, true},
		{false, false, false, false},
	},
	{ // w lewo/zawracanie
		{false, false, false, false},
		{false, true, true, false},
		{false, false, false, false},
		{true, false, false, true},
	},

};


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

typedef struct dir_lights{
	state left;
	state straight;
	state right;
} dir_lights;

void buf_init(v_buffer* buf){
	buf->head = buf->tail = buf->count = 0;
}

int buf_push(v_buffer* buf, const vehicle* v) {
    if (buf->count == BUFFER_SIZE) return 0; // bufor pełny
    buf->vs[buf->head] = *v;  // struktura kopiowana
    buf->head = (buf->head + 1) % BUFFER_SIZE;
    buf->count++;
    return 1;
}

int buf_pop(v_buffer* buf, vehicle* out) {
    if (buf->count == 0) return 0; // bufor pusty
    *out = buf->vs[buf->tail];
    buf->tail = (buf->tail + 1) % BUFFER_SIZE;
    buf->count--;
    return 1;
}

int buf_count(v_buffer* buf){
	return buf->count;
}

int buf_first(v_buffer* buf, vehicle* out){
	if (buf->count == 0) return 0; // bufor pusty
	*out = buf->vs[buf->tail];
	return 1;
}

typedef struct simulation{
	v_buffer vehicles[4][4];
	bool interim;
	int mode;
	state lights[4][4];
} simulation;

void simulation_init(simulation* sim){
	sim->interim=false;
	sim->mode=0;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			buf_init(&(sim->vehicles[i][j]));
			sim->lights[i][j]=RED;
		}
	}
}

int calculate_state_value(simulation* sim, int n){
	int v=0;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(states[n][i][j])
				v+=buf_count(&(sim->vehicles[i][j]));
		}
	}
	return v;
}

int calculate_optimal_state(simulation* sim){
	int opt=0;

	int opt_val=0;
	for(int i=0;i<STATES;i++){
		int v=calculate_state_value(sim, i);
		if(v>opt_val){
			opt=i;
			opt_val=v;
		}
	}
	return opt;
}

direction stringToDir(char* s){
	if (strcmp(s, "north")==0){
		return NORTH;
	}
	if (strcmp(s, "south")==0){
		return SOUTH;
	}
	if (strcmp(s, "east")==0){
		return EAST;
	}
	if (strcmp(s, "west")==0){
		return WEST;
	}
	assert(false);
	return NORTH;
}

int dir_string_to_int(char* s){
	if (strcmp(s, "north")==0){
		return 0;
	}
	if (strcmp(s, "east")==0){
		return 1;
	}
	if (strcmp(s, "south")==0){
		return 2;
	}
	if (strcmp(s, "west")==0){
		return 3;
	}
	assert(false);
	return 0;
}

bool collision(vehicle v1, vehicle v2){
	direction start1=v1.start;
	direction end1=v1.end;
	direction start2=v2.start;
	direction end2=v2.end;
	if(end1==end2)	return true;
		
	if((((end1-start1)+4)%4)==1){ //skret w prawo
		return false;
	}
	if((((end1-start1)+4)%4)==2){ //jazda prosto
		if (((start2-start1)+4)%4==1) { // z lewej
			if((start2-end2+4)%4==2)	return true;
		}
		if(((start1-start2+4)%4)==2){ //z naprzeciwka
			if((end2-start2+4)%4==1) return true;
		}
		if ((((start1-start2)+4)%4)==1) return true; //2-gi z prawej strony
	}
	
	if(((end1-start1)+4)%4==1){ // skret w lewo
		if (((start2-start1)+4)%4==1) { // z lewej
			if (((start2-end2+4)%4==2) || (((start2-end2+4)%4)==3))	return true;
		}
		if(((start1-start2+4)%4)==2){ //z naprzeciwka
			if((end2-start2+4)%4==1) return true;
		}
		if ((((start1-start2)+4)%4)==1) { //2-gi z prawej strony
			if((end2-start2+4)%4==1) return true;
		}
	}
	
	if(start1==end1){ //zawracanie
				if (((start2-start1)+4)%4==1) { // z lewej
			if ((start2-end2+4)%4==2)	return true;
		}
	}
	return false;	
}

void set_lights(simulation* sim, int mode){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(states[mode][i][j]){
				sim->lights[i][j]=GREEN;
			}else{
				sim->lights[i][j]=RED;
			}
		}
	}
}

void set_lights_interim(simulation* sim, int prev, int mode){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			if((states[prev][i][j]) && (states[mode][i][j]))	sim->lights[i][j]=GREEN;
			if((!states[prev][i][j]) && (states[mode][i][j]))	sim->lights[i][j]=REDYELLOW;
			if((states[prev][i][j]) && (!states[mode][i][j]))	sim->lights[i][j]=YELLOW;
			if((!states[prev][i][j]) && (!states[mode][i][j]))	sim->lights[i][j]=RED;
		}
	}
}

int sim_step(simulation* sim, vehicle* left){
	if(sim->interim){
		set_lights(sim, sim->mode);
		sim->interim=false;
	}else{
		int opt_mode=calculate_optimal_state(sim);
		if(opt_mode!=sim->mode){
			set_lights_interim(sim, sim->mode, opt_mode);
			sim->interim=true;
			sim->mode=opt_mode;
		}
	}
	

	int n=0;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if((sim->lights[i][j]==GREEN) || (sim->lights[i][j]==YELLOW)){
				if(buf_pop(&(sim->vehicles[i][j]), &(left[n])))
					n++;
			}
		}
	}
	return n;
}

void print_step_result(int fd, int n, vehicle* left){
	dprintf(fd, "step_result ");
    for(int i=0;i<n;i++){
		dprintf(fd, "%s ", left[i].id);
	}
	dprintf(fd, "\n");
}

void print_sim_status(int fd, simulation* sim){
	dprintf(fd,"i %d m %d\n",sim->interim ? 1 : 0, sim->mode);
}

int main(){

    char command[16];
	simulation sim;
	simulation_init(&sim);
	print_sim_status(2, &sim);

    while (scanf("%s", command) == 1){
    	if(strcmp(command, "addVehicle") == 0){
    		char start[16];
    		char end[16];
    		vehicle v;
    		if(!scanf("%s %s %s", v.id, start, end)){
				break;
			}
    		v.start=stringToDir(start);
    		v.end=stringToDir(end);
    		buf_push(&(sim.vehicles[v.start][v.end]), &v);
    		dprintf(2, "added %s %d %d\n", v.id, v.start, v.end);
    		continue;
    	}
		vehicle left[8];
    	if(strcmp(command, "step") == 0){
    		int n = sim_step(&sim, left);
    			
			print_step_result(1, n, left);
			print_sim_status(2, &sim);
    	}
    }
}
