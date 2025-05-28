#include "renderer.h"
#include <string.h>

// Positions where waiting vehicles should be shown
Position lane_position[4][4] = {
    {
        {0, 0},  // north - >north (not implemented)
        {4, 12}, // north -> east
        {4, 11}, // north -> south
        {4, 10}, // north -> west
    },
    {
        {6, 20},
        {0, 0},
        {8, 20},
        {7, 20},
    },
    {
        {14, 15},
        {14, 16},
        {0, 0},
        {14, 14},
    },
    {
        {10, 8},
        {11, 8},
        {12, 8},
        {0, 0},
    },
};

Position light_positions[4][4] = {{
                                      {0, 0},
                                      {5, 16},
                                      {5, 13},
                                      {5, 10},
                                  },
                                  {
                                      {6, 17},
                                      {0, 0},
                                      {8, 17},
                                      {7, 17},
                                  },
                                  {

                                      {13, 17},
                                      {13, 20},
                                      {0, 0},
                                      {13, 14},
                                  },
                                  {
                                      {10, 9},
                                      {11, 9},
                                      {12, 9},
                                      {0, 0},
                                  }};

                            
// Describes in which direction the vehicles should queue
Position lane_direction[4] = {
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1},
};

// Which light on the map corresponds to which lane of vehicles
Position lights_in_order[12] = {{0, 3}, {0, 2}, {0, 1}, {1, 0}, {1, 3}, {1, 2},
                                {3, 0}, {3, 1}, {3, 0}, {2, 3}, {2, 0}, {2, 1}};

void draw(simulation* sim){
	char map[HEIGHT+1][WIDTH+1]={
        "         |   |   |               ",
        "         |       |               ",
        "         |   |   |               ",
        "         |       |               ",
        "         |   |   |               ",
        "---------+C-RC-RC-R----+---------",
        "         |       C|R             ",
        "         |       C|R             ",
        "         |       C|R             ",
        "- - - - -|       |- - - - -      ",
        "         C|R       |             ",
        "         C|R       |             ",
        "         C|R       |             ",
        "---------+----C-RC-RC-R+---------",
        "         |   |   |               ",
        "         |       |               ",
        "         |   |   |               ",
        "         |       |               ",
        "         |   |   |               "
    };

  // Show last character of waiting vehicle's id on the map
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (i == j)
        continue; // not implemented
      int count = buf_count(&(sim->vehicles[i][j]));
      for (int k = 0; k < count; k++) {
        char c = buf_nth_v_id(&(sim->vehicles[i][j]), k);
        int col = lane_position[i][j].col + k * lane_direction[i].col;
        int row = lane_position[i][j].row + k * lane_direction[i].row;
        map[col][row] = c;
      }
    }
  }

  // print the map
  int n = 0;
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < strlen(map[i]); j++) {
      if (map[i][j] == 'C') { // set the character color the current light color
        state light =
            sim->lights[lights_in_order[n].col][lights_in_order[n].row];
        n++;
        char *color;
        switch (light) {
        case GREEN:
          color = GREEN_ANSI;
          break;
        case YELLOW:
        case REDYELLOW:
          color = YELLOW_ANSI;
          break;
        case RED:
          color = RED_ANSI;
          break;
        }
        dprintf(2, "%s", color);
        continue;
      }
      if (map[i][j] == 'R') { // reset color
        dprintf(2, RESET);
        continue;
      }
      dprintf(2, "%c", map[i][j]); // print map normally
    }
    dprintf(2, "\n");
  }
}

void check() {
  char map[HEIGHT+1][WIDTH+1]={
        "         |   |   |               ",
        "         |       |               ",
        "         |   |   |               ",
        "         |       |               ",
        "         |   |   |               ",
        "---------+C-RC-RC-R----+---------",
        "         |       C|R             ",
        "         |       C|R             ",
        "         |       C|R             ",
        "- - - - -|       |- - - - -      ",
        "         C|R       |             ",
        "         C|R       |             ",
        "         C|R       |             ",
        "---------+----C-RC-RC-R+---------",
        "         |   |   |               ",
        "         |       |               ",
        "         |   |   |               ",
        "         |       |               ",
        "         |   |   |               "
    };
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (i != j) {
        int col = light_positions[i][j].col;
        int row = light_positions[i][j].row;
        if (map[col][row] != 'C') {
          dprintf(2, "at %d %d expected %c got %c\n", col, row, 'C',
                  map[col][row]);
        }
        if (map[col][row + 2] != 'R') {
          dprintf(2, "at %d %d expected %c got %c\n", col, row + 2, 'R',
                  map[col][row + 2]);
        }
      }
    }
  }
  dprintf(2, "ok");
}
