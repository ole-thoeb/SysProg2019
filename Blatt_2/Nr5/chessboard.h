struct board_t {
	int **fields;
	int curX;
	int curY;
	int n;
	int iteration;
};

void new_jump(struct board_t* b, int x, int y);
void remove_jump(struct board_t* b, int x, int y);
int isfree(struct board_t* b, int x, int y);
int visited_fields(struct board_t* b);
void print_board(struct board_t* b);
int init_board(struct board_t* b, int n, int x, int y);
void free_board(struct board_t *b);