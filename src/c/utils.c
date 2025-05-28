#include "utils.h"

#include <string.h>
#include <assert.h>
#include <stdio.h>

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