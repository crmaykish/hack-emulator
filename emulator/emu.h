int a_val(int opcode);

int c_a(int opcode);
int c_comp(int opcode);
int c_dest(int opcode);
int c_jump(int opcode);

int c0(int comp);
int c1(int comp);

void jump(int comp, int jump);
void dest(int val, int dest);
void cycle();

int load_rom();

void debug();

unsigned short from_bin(const char *s);