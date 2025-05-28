

#define WIDTH 27
#define HEIGHT 19

    const char *template[] = {
        "         |   |   |         ",
        "         |       |         ",
        "         |   |   |         ",
        "         |       |         ",
        "         |   |   |         ",
        "---------+-------+---------",
        "         |       |         ",
        "         |       |         ",
        "         |       |         ",
        "- - - - -|       |- - - - -",
        "         |       |         ",
        "         |       |         ",
        "         |       |         ",
        "---------+-------+---------",
        "         |   |   |         ",
        "         |       |         ",
        "         |   |   |         ",
        "         |       |         ",
        "         |   |   |         "
    };


typedef struct {
    int row;
    int col;
} Position;

Position lane_position[4][4] = {
    {
        {0,0}, // north->north not implemented
        {4,12}, //north - east
        {4,11}, //north south
        {4,10}, //north west
    },
    {
        {10,18},
        {0,0},
        {12,18},
        {11,18},
    },
    {
        {15,14},
        {16,14},
        {0,0},
        {14,14},
    },
    {
        {10,8},
        {11,8},
        {12,8},
        {0,0},
    },
}

Position lane_direction[4] = {
    {-1,0},
    {0,1},
    {1,0},
    {0,-1},
}

void draw(simulation* sim){
    char[HEIGHT][WIDTH] map={
        "         |   |   |         ",
        "         |       |         ",
        "         |   |   |         ",
        "         |       |         ",
        "         |   |   |         ",
        "---------+-------+---------",
        "         |       |         ",
        "         |       |         ",
        "         |       |         ",
        "- - - - -|       |- - - - -",
        "         |       |         ",
        "         |       |         ",
        "         |       |         ",
        "---------+-------+---------",
        "         |   |   |         ",
        "         |       |         ",
        "         |   |   |         ",
        "         |       |         ",
        "         |   |   |         "
    };


    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            int count=buf_count(&(sim->vs[i][j]));
            for(int k=0;k<count;k++){
                char c = buf_nth_v_id(&(sim->vs[i][j]), k);
                int col = lane_position[i][j].col+k*lane_direction[i];
                int row = lane_position[i][j].row+k*lane_direction[i];
                map[col][row]=c;
            }
        }
    }
    for(int i=0;i<HEIGHT;i++){
        printf("%s\n",map[HEIGHT]);
    }
}