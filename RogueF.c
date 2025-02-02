# include <stdio.h>
# include <ncurses.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>

# define FILE_OF_USERNAMES "users.txt"
# define MAX_LENGTH 50
# define MAX_HEIGHT 50
# define MAX_WIDTH 200


typedef struct {
    int special;
    int normal;
} Food;

typedef struct {
    int H;
    int G;
    int S;
} Spell;

typedef struct {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    char email[2 * MAX_LENGTH];
    char stage_1[MAX_HEIGHT][MAX_WIDTH];
    char stage_2[MAX_HEIGHT][MAX_WIDTH];
    char stage_3[MAX_HEIGHT][MAX_WIDTH];
    char stage_4[MAX_HEIGHT][MAX_WIDTH];
    int score;
    int games_played;
    int gold;
    int health;
    int power;
    char weapon;
    char spell;
    int level;
    int difficulty;
    int character_color;
    Food food_bar;
    Spell spell_bar;
} User;

typedef struct {
    int x, y;
    int color;
    int difficulty;
    char previous_char;
} Character;


User player;


int stage_1_c[MAX_HEIGHT][MAX_WIDTH];
int stage_2_c[MAX_HEIGHT][MAX_WIDTH];  
int stage_3_c[MAX_HEIGHT][MAX_WIDTH];  
int stage_4_c[MAX_HEIGHT][MAX_WIDTH];

int m_count = 0;
int food_f = 0;
int spell_f = 0;
int spell_h;
int spell_s;
int spell_g;
int spell_hc = 0;
int spell_sc = 0;
int spell_gc = 0;
int pace = 1;
int pace_count_1 = 0;
int pace_count_2 = 0;



void character_color(int);
void difficulty(int);
void start_menu(int);
int validate_user(char*, char*);
int username_existance(char *);
void sign_up();
void log_in();
void user_menu();
void rankings();
void profile_status();
void eexit();
void save_user();
void play_as_guest();
void start_new_game();
void continue_last_game();
void show_score_table();
void show_profile_status();
void settings_menu();
void start_new_game();
void start_level2();
void start_level3();
void start_level4();
void show_profile_status(); 
int create_map_1();
int create_map_2();
int create_map_3();
int create_map_4();
void generate_corridor(int x1, int y1, int x2, int y2,char map[MAX_HEIGHT][MAX_WIDTH]);
void generate_character(Character *Char);
int get_input(Character *Char);
void clear_character(Character *Char);
int movement_validate(int x, int y,char map[MAX_HEIGHT][MAX_WIDTH]);
void generate_map(int player_x, int player_y,int memory_map[MAX_HEIGHT][MAX_WIDTH],char map[MAX_HEIGHT][MAX_WIDTH]);
void update_map_c(int player_x, int player_y,int memory_map[MAX_HEIGHT][MAX_WIDTH]);
int room_validate(int x, int y);
int room_number(int x, int y);
void refresh_map(Character *Char,int memory_map[MAX_HEIGHT][MAX_WIDTH],char map[MAX_HEIGHT][MAX_WIDTH]);
void show_map_temporarily(Character *Char);
char *generate_code();
void show_code(const char *code);
char *enter_code();
int check_code(const char *entered_code, const char *correct_code);
void generate_bar(int y, int x, int width, int value, int max_value, const char* label);
int food_manager(char food);
void foods();
int golds(char gold);
int validate_spell(char spell);
int spells();
char message(int height, int width);


int main() {
    initscr();        
    noecho();       
    cbreak();         
    keypad(stdscr, TRUE);
    start_color();
    srand(time(NULL));
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7,COLOR_CYAN,COLOR_BLACK);
    user_menu();
    return(0);
}





void start_new_game(){
    clear();
    player.level=1;
    player.gold = 0;
    player.health=10000;
    player.power=100;
    player.food_bar.normal=0;
    player.food_bar.special=0;
    player.spell_bar.H=0;
    player.spell_bar.S=0;
    player.spell_bar.G=0;
    memset(stage_1_c,0,sizeof(stage_1_c));
    create_map_1();  
    Character Char = {5, 4, '.'};
    refresh_map(&Char,stage_1_c,player.stage_1);  

    while (1) {
        get_input(&Char);
    }
}

void start_level2(){
    clear();
    m_count = 0;
    player.level=2;
    pace_count_2=0;
    memset(stage_2_c,0,sizeof(stage_2_c));
    create_map_2();  
    Character Char = {12,10, '.'};
    refresh_map(&Char,stage_2_c,player.stage_2);  

    while (1) {
        get_input(&Char);
    }
}


void start_level3(){
    clear();
    m_count = 0;
    player.level=3;
    pace_count_2=0;
    memset(stage_3_c,0,sizeof(stage_3_c)); 
    create_map_3();  
    Character Char = {20,26, '.'};
    refresh_map(&Char,stage_3_c,player.stage_3);  

    while (1) {
        get_input(&Char);
    }
}


void start_level4(){
    clear();
    m_count = 0;
    pace_count_2=0;
    player.level=4;
    memset(stage_4_c,0,sizeof(stage_4_c));
    create_map_4();  
    Character Char = {48,35, '.'};
    refresh_map(&Char,stage_4_c,player.stage_4);  

    while (1) {
        get_input(&Char);
    }
}


char *generate_code() {
    static char code[5];
    const char digits[] = "0123456789";
    for (int i = 0; i < 4; i++) {
        code[i] = digits[rand() % 10];
    }
    code[4] = '\0';
    return code;
}


void show_code(const char *code) {
    attron(COLOR_PAIR(2));
    mvprintw(LINES/2-2,COLS/2-22,"==============================");
    mvprintw(LINES/2+2,COLS/2-22,"==============================");
    for(int i = LINES/2-2 ; i <= LINES/2+2 ;i++){
        mvprintw(i,COLS/2-23,"||");
        mvprintw(i,COLS/2+8,"||");
    }
    attroff(COLOR_PAIR(2));
    mvprintw(LINES/2-1, COLS/2-16, "CODE IS: %s", code);
}


char *enter_code() {
    static char input[5];
    echo();
    curs_set(1);
    mvprintw(LINES/2,COLS/2-16, "ENTER PASS:");
    getstr(input);
    noecho();
    curs_set(0);
    return(input);
}

int check_code(const char *entered_code, const char *correct_code) {
    char real_code[5];
    for(int i = 3; i >= 0 ;i--){
        real_code[3-i] = entered_code[i];
    }
    if (strcmp(real_code, correct_code) == 0) {
        mvprintw(LINES/2+1, COLS/2-16, "DOOR OPENED!");
        getch();
        move(LINES/2-2,COLS/2-23);
        clrtoeol();
        move(LINES/2-1,COLS/2-23);
        clrtoeol();
        move(LINES/2,COLS/2-23);
        clrtoeol();
        move(LINES/2+1,COLS/2-23);
        clrtoeol();
        move(LINES/2+2,COLS/2-23);
        clrtoeol();
        return 1;
    } else {
        mvprintw(LINES/2+1, COLS/2-16, "Wrong Pass!");
        getch();
        getch();
        move(LINES/2-2,COLS/2-23);
        clrtoeol();
        move(LINES/2-1,COLS/2-23);
        clrtoeol();
        move(LINES/2,COLS/2-23);
        clrtoeol();
        move(LINES/2+1,COLS/2-23);
        clrtoeol();
        move(LINES/2+2,COLS/2-23);
        clrtoeol();
        return(0);
    }
}


void generate_bar(int y, int x, int width, int value, int max_value, const char* label) {
    if (strcmp(label,"Gold") == 0) {
        mvprintw(y, x, "%s: ", label);

        int bar_length = (value * width) / max_value;

        attron(COLOR_PAIR(1) | A_REVERSE); 
        for (int i = 0; i < bar_length; i++) {
            mvaddch(y, x + strlen(label) + 2 + i, ' '); 
        }
        attroff(COLOR_PAIR(1) | A_REVERSE);

        for (int i = bar_length; i < width; i++) {
            mvaddch(y, x + strlen(label) + 2 + i, ' '); 
        }
        mvprintw(y, x + strlen(label) + 2 + width + 1, " %d/%d", value, max_value);
    } else {
        mvprintw(y, x, "%s: ", label);

        int bar_length = (value * width) / max_value;

        attron(COLOR_PAIR(3) | A_REVERSE); 
        for (int i = 0; i < bar_length; i++) {
            mvaddch(y, x + strlen(label) + 2 + i, ' '); 
        }
        attroff(COLOR_PAIR(3) | A_REVERSE);

        attron(COLOR_PAIR(2) | A_REVERSE);
        for (int i = bar_length; i < width; i++) {
            mvaddch(y, x + strlen(label) + 2 + i, ' '); 
        }
        attroff(COLOR_PAIR(2) | A_REVERSE);
        mvprintw(y, x + strlen(label) + 2 + width + 1, " %d/%d", value, max_value);
    }
}


int food_manager(char food){
    if(food=='%'){
        if(player.food_bar.normal+player.food_bar.special>=5){
            food_f = 1;
            attron(COLOR_PAIR(2));
            mvprintw(0,0,"not enough space to restore food!");
            attroff(COLOR_PAIR(2));
            getch();
            mvprintw(0,0,"                                 ");
        } else {
            food_f = 0;
            player.food_bar.normal += 1;
        }
    } else if (food == 'X') {
        if (player.food_bar.normal+player.food_bar.special >= 5) {
            food_f = 1;
            attron(COLOR_PAIR(2));
            mvprintw(0,0,"not enough space to restore food!");
            attroff(COLOR_PAIR(2));
            getch();
            mvprintw(0,0,"                                 ");
        } else {
            food_f=0;
            player.food_bar.special += 1;
        }
    }
}

void foods() {
    clear();
    mvprintw(LINES/2-6,COLS/2-20,"      normal food : %d",player.food_bar.normal);
    mvprintw(LINES/2-5,COLS/2-20,"      special food : %d",player.food_bar.special);
    mvprintw(LINES/2-4,COLS/2-50,"press n to consume normal food or press s to consume special food,to quit press any key");
    int index = getch();
    int x = rand() % 5;
    int add1 = 10;
    int add2 = 80;
    if ((spell_h == 1) && (spell_hc < 10)) {
        add1 = 20;
        add2 = 160;
    }
    switch (index){
        case 'n' :
            if (x) {
                if (player.food_bar.normal > 0) {
                    if(player.health>=9990&&spell_h==0||player.health>=9980&&spell_h==1){
                        mvprintw(LINES/2-3,COLS/2-20,"           Full!");
                        getch();
                        clear();
                    } else {
                        player.food_bar.normal--;
                        player.health+=add1;
                        mvprintw(LINES/2-3,COLS/2-20,"            Nice!");
                        getch();
                        clear();
                    }
                } else {
                    mvprintw(LINES/2-3,COLS/2-20,"You have no normal food");
                    getch();
                    clear();
                }
                break;
            } else {
                player.health -= 6;
                mvprintw(LINES/2-3,COLS/2-20,"         Noooooope!");
                getch();
                clear();
            }
            break;
        case 's' :
            if (player.food_bar.special > 0) {
                if(player.health>=9920&&spell_h==0||player.health>=9840&&spell_h==1){
                    mvprintw(LINES/2-3,COLS/2-20,"           FULL!");
                    getch();
                    clear();
                } else {
                    player.food_bar.special--;
                    player.health += add2;
                    mvprintw(LINES/2-3,COLS/2-20,"        Great!");
                    getch();
                    clear();
                }
            } else {
                mvprintw(LINES/2-3,COLS/2-20,"You have no special food");
                getch();
                clear();
            }
            break;
        default :
            clear();
            break;
    }
}



int golds(char gold){
    if (gold == 'T') {
        player.gold += 5;
    } else {
        player.gold+=30;
    }
}


int validate_spell(char spell){
    if (player.spell_bar.H+player.spell_bar.S+player.spell_bar.G >= 15) {
        spell_f=1;
        attron(COLOR_PAIR(2));
        mvprintw(0,0,"not enough space for spell!");
        attroff(COLOR_PAIR(2));
        getch();
        mvprintw(0,0,"                                 ");
    } else {
        spell_f=0;
        if(spell=='H'){
            player.spell_bar.H++;
        }
        else if(spell=='S'){
            player.spell_bar.S++;
        }
        else if(spell=='8'){
            player.spell_bar.G++;
        } 
    }
}


int spells(){
    clear();
    mvprintw(LINES/2-4,COLS/2-27,"Health spell : %d press h to consume Health spell",player.spell_bar.H);
    mvprintw(LINES/2-3,COLS/2-27,"Speed  spell : %d press s to consume Speed  spell",player.spell_bar.S);
    mvprintw(LINES/2-2,COLS/2-27,"Power  spell : %d press p to consume Power  spell",player.spell_bar.G);
    mvprintw(LINES/2,COLS/2-27,"            press any other key to quit");
    int index = getch();
    switch(index){
        case 'h' :
            if (player.spell_bar.H <= 0) {
                mvprintw(LINES/2+2,COLS/2-27,"               not enough spell!");
                getch();
                clear();
                break;
            } else {
                mvprintw(LINES/2+1,COLS/2-27,"                    Healthy!");
                player.spell_bar.H--;
                spell_h=1;
                spell_hc=0;
                getch();
                clear();
                break;
            }    
        case 's' :
            if (player.spell_bar.S <= 0) {
                mvprintw(LINES/2+2,COLS/2-27,"               not enough spell!");
                getch();
                clear();
                break;
            } else {
                mvprintw(LINES/2+1,COLS/2-27,"                    Flash!!!!");
                player.spell_bar.S--;
                spell_s=1;
                spell_sc=0;
                getch();
                clear();
                break;
            }
        case 'p':
            if (player.spell_bar.G <= 0) {
                mvprintw(LINES/2+2,COLS/2-27,"               not enough spell!");
                getch();
                clear();
                break;
            } else {
                mvprintw(LINES/2+1,COLS/2-27,"                   Powerful!");
                player.spell_bar.G--;
                spell_g=1;
                spell_gc=0;
                getch();
                clear();
                break;
            } 
        default :
            clear();    
            break;
    }
}


char message(int height, int width){
    int y_max, x_max;
    getmaxyx(stdscr, y_max, x_max);
    int startY = (y_max - height) / 2;
    int startX = (x_max - width) / 2;
    
    for (int i = 0; i < width; i++) {
        mvaddch(startY, startX + i, '-');
        mvaddch(startY + height - 1, startX + i, '-');
    }
    for (int i = 0; i < height; i++) {
        mvaddch(startY + i, startX, '|');
        mvaddch(startY + i, startX + width - 1, '|');
    }
    mvaddch(startY, startX, '+');
    mvaddch(startY, startX + width - 1, '+');
    mvaddch(startY + height - 1, startX, '+');
    mvaddch(startY + height - 1, startX + width - 1, '+');
    attron(COLOR_PAIR(4));
    mvprintw(startY, startX + (width - 10) / 2, "CHOOSE :)");
    mvprintw(startY + height / 2 - 1, startX + 2, "                   ");
    mvprintw(startY + height / 2, startX + (width - 18) / 2-2, "press ENTER to pick");
    mvprintw(startY + height / 2 + 1, startX + 2, "                   ");
    attroff(COLOR_PAIR(4));
    int index = getch();

    if (index == '\n') {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                mvaddch(startY + i, startX + j, ' ');
            }
        }
        return '\n';
    } else {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                mvaddch(startY + i, startX + j, ' ');
            }
        }
        return'a';
    }
}



void show_map_temporarily(Character *Character) {
    if (player.level == 1) {
        for (int i = 0; i < MAX_HEIGHT; i++) {
            for (int j = 0; j < MAX_WIDTH; j++) {
                mvaddch(i, j, player.stage_1[i][j]);
            }
        }
        refresh();
        timeout(4000);
        int index = getch();
        if (index == 'm') {
            clear();
            refresh_map(Character, stage_1_c, player.stage_1);
        } else {
            clear();
            refresh_map(Character,stage_1_c,player.stage_1);
        }
        timeout(-1);
    } else if (player.level == 2) {
        for (int i = 0; i < MAX_HEIGHT; i++) {
            for (int j = 0; j < MAX_WIDTH; j++) {
                mvaddch(i, j, player.stage_2[i][j]);
            }
        }
        refresh();
        timeout(4000);
        int index = getch();
        if (index == 'm') {
            clear();
            refresh_map(Character, stage_2_c, player.stage_2);
        } else {
            clear();
            refresh_map(Character, stage_2_c, player.stage_2);
        }
        timeout(-1);
    } else if (player.level == 3) {
        for (int i = 0; i < MAX_HEIGHT; i++) {
            for (int j = 0; j < MAX_WIDTH; j++) {
                mvaddch(i, j, player.stage_3[i][j]);
            }
        }
        refresh();
        timeout(4000);
        int index = getch();
        if (index == 'm') {
            clear();
            refresh_map(Character,stage_3_c,player.stage_3);
        } else {
            clear();
            refresh_map(Character,stage_3_c,player.stage_3); 
        }
        timeout(-1);
    } else if (player.level == 4) {
        for (int i = 0; i < MAX_HEIGHT; i++) {
            for (int j = 0; j < MAX_WIDTH; j++) {
                mvaddch(i, j, player.stage_4[i][j]);
            }
        }
        refresh();
        timeout(4000);
        int index = getch();
        if (index == 'm') {
            clear();
            refresh_map(Character,stage_4_c,player.stage_4);
        } else {
            clear();
            refresh_map(Character,stage_4_c,player.stage_4);
        }
        timeout(-1);
    }
}


int room_number(int x, int y) {
    if(player.level==1){
        if (x >= 4 && x <= 23 && y >= 4 && y <= 10) return 1;
        if (x >= 51 && x <= 65 && y >= 7 && y <= 20) return 2;
        if (x >= 101 && x <= 111 && y >= 7 && y <= 16) return 3;
        if (x >= 151 && x <= 159 && y >= 21 && y <= 29) return 4;
        if (x >= 95 && x <= 110 && y >= 31 && y <= 35) return 5;
        if (x >= 11 && x <= 20 && y >= 29 && y <= 37) return 6;
        return 0;
    }
    else if(player.level==2){
        if (y >= 6 && y <= 14 && x >= 10 && x <= 18) return 1;   
        if (y >= 5 && y <= 13 && x >= 35 && x <= 48) return 2;   
        if (y >= 3 && y <= 12 && x >= 120 && x <= 135) return 3;   
        if (y >= 30 && y <= 41 && x >= 160 && x <= 175) return 4;   
        if (y >= 30 && y <= 35 && x >= 94 && x <= 110) return 5;   
        if (y >= 15 && y <= 22 && x >= 50 && x <= 60) return 6;   
        if (y >= 28 && y <= 32 && x >= 11 && x <= 26) return 7;    
        return 0;
    }
    else if(player.level==3){
        if (x >= 35 && x <= 41 && y >= 6 && y <= 15) return 1;  
        if (x >= 70 && x <= 84 && y >= 12 && y <= 16) return 2;  
        if (x >= 125 && x <= 145 && y >= 6 && y <= 20) return 3;  
        if (x >= 160 && x <= 175 && y >= 30 && y <= 41) return 4;  
        if (x >= 84 && x <= 100 && y >= 30 && y <= 35) return 5;  
        if (x >= 12 && x <= 26 && y >= 21 && y <= 35) {
            return 6;
            }  
        return 0;
    }
    else if(player.level==4){
        if (x >= 10 && x <= 18 && y >= 6 && y <= 14) return 1;  
        if (x >= 35 && x <= 48 && y >= 5 && y <= 13) return 2;  
        if (x >= 120 && x <= 135 && y >= 3 && y <= 12) return 3;  
        if (x >= 160 && x <= 175 && y >= 30 && y <= 41) return 4;  
        if (x >= 94 && x <= 110 && y >= 30 && y <= 35) return 5;  
        if (x >= 50 && x <= 60 && y >= 15 && y <= 22) return 6;  
        if (x >= 11 && x <= 26 && y >= 28 && y <= 32) return 7;  
        if (x >= 45 && x <= 60 && y >= 30 && y <= 41)return 8; 
        return 0;
    }
}



int room_validate(int x, int y) {
    if(player.level == 1){
        if (((x >= 3) && (x <= 23) && (y >= 3) && (y <= 9)) || ((x >= 50) && (x <= 65) && (y >= 7) && (y <= 20)) || ((x >= 100) && (x <= 111) && (y >= 6) && (y <= 16)) || ((x >= 150) && (x <= 159) && (y >= 20) && (y <= 29)) || ((x >= 94) && (x <= 110) && (y >= 30) && (y <= 35)) || ((x >= 10) && (x <= 20) && (y >= 28) && (y <= 37))) {
        return(1);
        }
        return(0);
    } else if (player.level == 2) {
        if (((y >= 6) && (y <= 14) && (x >= 10) && (x <= 18)) || ((y >= 5) && (y <= 13) && (x >= 35) && (x <= 48)) || ((y >= 3) && (y <= 12) && (x >= 120) && (x <= 135)) || ((y >= 30) && (y <= 41) && (x >= 160) && (x <= 175)) || ((y >= 30) && (y <= 35) && (x >= 94) && (x <= 110)) || ((y >= 15) && (y <= 22) && (x >= 50) && (x <= 60)) || ((y >= 28) && (y <= 32) && (x >= 11) && (x <= 26))) {   
        return(1);
        }
        return(0);
    } else if (player.level == 3){
        if (((x >= 35) && (x <= 41) && (y >= 6) && (y <= 15)) || ((x >= 70) && (x <= 84) && (y >= 12) && (y <= 16)) || ((x >= 125) && (x <= 145) && (y >= 5) && (y <= 19)) || ((x >= 160) && (x <= 175) && (y >= 30) && (y <= 41)) || ((x >= 84) && (x <= 100) && (y >= 30) && (y <= 35)) || ((x >= 12) && (x <= 25) && (y >= 21) && (y <= 35))) {   
            return(1);
        }
        return(0);
    } else if (player.level == 4) {
        if (((x >= 10) && (x <= 18) && (y >= 6) && (y <= 14)) || ((x >= 35) && (x <= 48) && (y >= 5) && (y <= 13)) || ((x >= 120) && (x <= 135) && (y >= 3) && (y <= 12)) || ((x >= 160) && (x <= 175) && (y >= 30) && (y <= 41)) || ((x >= 94) && (x <= 110) && (y >= 30) && (y <= 35)) || ((x >= 50) && (x <= 60) && (y >= 15) && (y <= 22)) || ((x >= 11) && (x <= 26) && (y >= 28) && (y <= 32)) || ((x >= 45) && (x <= 60) && (y >= 30) && (y <= 41))) {   
            return(1);
        }
        return(0);
    }
}


void update_map_c(int player_x, int player_y,int memory_map[MAX_HEIGHT][MAX_WIDTH]) {
    if (player.level == 1) {
        if (room_validate(player_x,player_y)) {
            if (room_number(player_x,player_y) == 1) {
                for (int i = 3; i <= 9; i++) {
                    for (int j = 3; j <= 23; j++) {
                        memory_map[i][j] = 1;  
                    }
                }
            } else if (room_number(player_x,player_y) == 2) {
                for (int i = 7; i <= 20; i++) {
                    for (int j = 50 ; j <= 65 ; j++) {
                        memory_map[i][j] = 1;
                    }
                }
            } else if (room_number(player_x,player_y) == 3) {
                for (int i = 6; i <= 16; i++) {
                    for (int j = 100; j <= 111; j++) {
                        memory_map[i][j] = 1;
                    }
                }
            } else if (room_number(player_x,player_y) == 4) {
                for (int i = 20; i <= 29; i++) {
                    for (int j = 150; j <= 159; j++) {
                        memory_map[i][j] = 1;
                    }
                }
            } else if (room_number(player_x,player_y) == 5) {
                for (int i = 30; i <= 35; i++) {
                    for (int j = 94; j <= 110; j++) {
                        memory_map[i][j] = 1;
                    }
                }
            } else if (room_number(player_x,player_y) == 6) {
                for (int i = 28; i <= 37; i++) {
                    for (int j = 10; j <= 20; j++) {
                        memory_map[i][j] = 1;
                    }
                }
            }
        } else {
            int view_distance = 3;  

            for (int y = player_y - view_distance; y <= player_y + view_distance; y++) {
                for (int x = player_x - view_distance; x <= player_x + view_distance; x++) {
                    if ((x >= 0) && (x < MAX_WIDTH) && (y >= 0) && (y < MAX_HEIGHT)) {
                        memory_map[y][x] = 1;  
                    }
                }
            }
        }
    } else if (player.level == 2) {
        if (room_validate(player_x, player_y)) {
            if (room_number(player_x, player_y) == 1) {
                for (int i = 6; i <= 14; i++) {
                    for (int j = 10; j <= 18; j++) {
                        memory_map[i][j] = 1;
                    }
                }
            } else if (room_number(player_x, player_y) == 2) {
                for (int i = 5; i <= 13; i++) {
                    for (int j = 35; j <= 48; j++) {
                        memory_map[i][j] = 1;
                    }
                }
            } else if (room_number(player_x, player_y) == 3) {
                for (int i = 3; i <= 12; i++) {
                    for (int j = 120; j <= 135; j++) {
                        memory_map[i][j] = 1;
                    }
                }
            } else if (room_number(player_x, player_y) == 4) {
                for (int i = 30; i <= 41; i++) {
                    for (int j = 160; j <= 175; j++) {
                        memory_map[i][j] = 1;
                    }
                }
            } else if (room_number(player_x, player_y) == 5) {
                for (int i = 30; i <= 35; i++) {
                    for (int j = 94; j <= 110; j++) {
                        memory_map[i][j] = 1;
                    }
                }
            } else if (room_number(player_x, player_y) == 6) {
                for (int i = 15; i <= 22; i++) {
                    for (int j = 50; j <= 60; j++) {
                        memory_map[i][j] = 1;
                    }
                }
            } else if (room_number(player_x, player_y) == 7) {
                for (int i = 28; i <= 32; i++) {
                    for (int j = 11; j <= 26; j++) {
                        memory_map[i][j] = 1;
                    }
                }
            }
        } else {
            int view_distance = 3;  

            for (int y = player_y - view_distance; y <= player_y + view_distance; y++) {
                for (int x = player_x - view_distance; x <= player_x + view_distance; x++) {
                    if ((x >= 0) && (x < MAX_WIDTH) && (y >= 0) && (y < MAX_HEIGHT)) {
                        memory_map[y][x] = 1;
                    }
                }
            }
        }
    } else if (player.level == 3) {
        if (room_validate(player_x, player_y)) {
            if (room_number(player_x, player_y) == 1) {
                for (int i = 6; i <= 15; i++) {  
                    for (int j = 35; j <= 41; j++) {  
                        memory_map[i][j] = 1;
                    }
                }
            } else if (room_number(player_x, player_y) == 2) {
                for (int i = 12; i <= 16; i++) {  
                    for (int j = 70; j <= 84; j++) {  
                        memory_map[i][j] = 1;
                    }
                }
            } else if (room_number(player_x, player_y) == 3) {
                for (int i = 5; i <= 20; i++) {  
                    for (int j = 125; j <= 145; j++) {  
                        memory_map[i][j] = 1;
                    }
                }
            } else if (room_number(player_x, player_y) == 4) {
                for (int i = 30; i <= 41; i++) {  
                    for (int j = 160; j <= 175; j++) {  
                        memory_map[i][j] = 1;
                    }
                }
            } else if (room_number(player_x, player_y) == 5) {
                for (int i = 30; i <= 35; i++) {  
                    for (int j = 84; j <= 100; j++) {  
                        memory_map[i][j] = 1;
                    }
                }
            } else if (room_number(player_x, player_y) == 6) {
                for (int i = 21; i <= 35; i++) {  
                    for (int j = 12; j <= 26; j++) {  
                        memory_map[i][j] = 1;
                    }
                }
            }
        } else {
            int view_distance = 3;  

            for (int y = player_y - view_distance; y <= player_y + view_distance; y++) {
                for (int x = player_x - view_distance; x <= player_x + view_distance; x++) {
                    if (x >= 0 && x < MAX_WIDTH && y >= 0 && y < MAX_HEIGHT) {
                        memory_map[y][x] = 1;  
                    }
                }
            }
        }
    } else if (player.level == 4) {
        if (room_validate(player_x, player_y)) {
            if (room_number(player_x, player_y) == 1) {
                for (int i = 6; i <= 14; i++) {  
                    for (int j = 10; j <= 18; j++) {  
                        memory_map[i][j] = 1;
                    }
                }
            } else if (room_number(player_x, player_y) == 2) {
                for (int i = 5; i <= 13; i++) {  
                    for (int j = 35; j <= 48; j++) {  
                        memory_map[i][j] = 1;
                    }
                }
            } else if (room_number(player_x, player_y) == 3) {
                for (int i = 3; i <= 12; i++) {  
                    for (int j = 120; j <= 135; j++) {  
                        memory_map[i][j] = 1;
                    }
                }
            } else if (room_number(player_x, player_y) == 4) {
                for (int i = 30; i <= 41; i++) {  
                    for (int j = 160; j <= 175; j++) {  
                        memory_map[i][j] = 1;
                    }
                }
            } else if (room_number(player_x, player_y) == 5) {
                for (int i = 30; i <= 35; i++) {  
                    for (int j = 94; j <= 110; j++) {  
                        memory_map[i][j] = 1;
                    }
                }
            } else if (room_number(player_x, player_y) == 6) {
                for (int i = 15; i <= 22; i++) {  
                    for (int j = 50; j <= 60; j++) {  
                        memory_map[i][j] = 1;
                    }
                }
            } else if (room_number(player_x, player_y) == 7) {
                for (int i = 28; i <= 32; i++) {  
                    for (int j = 11; j <= 26; j++) {  
                        memory_map[i][j] = 1;
                    }
                }
            } else if (room_number(player_x, player_y) == 8) {
                for (int i = 30; i <= 41; i++) {  
                    for (int j = 45; j <= 60; j++) {  
                        memory_map[i][j] = 1;
                    }
                }
            }
        } else {
            int view_distance = 3;  

            for (int y = player_y - view_distance; y <= player_y + view_distance; y++) {
                for (int x = player_x - view_distance; x <= player_x + view_distance; x++) {
                    if (x >= 0 && x < MAX_WIDTH && y >= 0 && y < MAX_HEIGHT) {
                        memory_map[y][x] = 1;  
                    }
                }
            }
        }
    }
}



void refresh_map(Character *Char,int memory_map[MAX_HEIGHT][MAX_WIDTH],char map[MAX_HEIGHT][MAX_WIDTH]) {
    update_map_c(Char->x, Char->y,memory_map);
    generate_map(Char->x, Char->y,memory_map,map);
    generate_character(Char);
    generate_bar(LINES-2, 12, 20, player.health, 10000, "Health");
    generate_bar(LINES-2, 72, 20, player.power, 100, "Power");
    generate_bar(LINES-2, 132, 20, player.gold, 10000, "Gold");
    refresh();  
}


void generate_map(int player_x, int player_y,int memory_map[MAX_HEIGHT][MAX_WIDTH],char map[MAX_HEIGHT][MAX_WIDTH]) {
    for (int i = 0; i < MAX_HEIGHT; i++) {
        for (int j = 0; j < MAX_WIDTH; j++) {
            if (memory_map[i][j]){
                if (map[i][j] == '@') {
                        attron(COLOR_PAIR(2));
                        mvaddch(i, j, '@');
                        attroff(COLOR_PAIR(2));
                } else if (map[i][j] == 'G') {
                        attron(COLOR_PAIR(3));
                        mvaddch(i, j,map[i][j]);
                        attroff(COLOR_PAIR(3));
                } else if ((map[i][j] == '|') || (map[i][j] == '-')) {
                    attron(COLOR_PAIR(7));
                    mvaddch(i, j,map[i][j]);
                    attroff(COLOR_PAIR(7));
                } else {
                    mvaddch(i, j,map[i][j]);
                }
            }
        }
    }
}


void generate_corridor(int x1, int y1, int x2, int y2,char map[MAX_HEIGHT][MAX_WIDTH]) {
    int cx = x1, cy = y1;

    while (cx != x2 || cy != y2) {
        map[cy][cx] = '#';

        int dx = (cx < x2) - (cx > x2);
        int dy = (cy < y2) - (cy > y2);

        if ((rand() % 2 == 0) && (map[cy][cx + dx] != '|') && (map[cy][cx + dx] != '-')) {
            cx += dx;
        } else if ((map[cy + dy][cx] != '|') && (map[cy + dy][cx] != '-')) {
            cy += dy;
        } else if ((map[cy + dy][cx + dx] != '|') && (map[cy + dy][cx + dx] != '-')) {
            cx += dx;
            cy += dy;
        } else {
            break;
        }
    }
}

// Generating maps

int create_map_1() {
    memset(player.stage_1, ' ', sizeof(player.stage_1));


    //Generating first room

    int n1 = rand() % 5 + 3;
    int t1 = rand() % 3 + 1;
    int q1 = rand() % 3 ;

    player.stage_1[5][23] = '+';
    player.stage_1[7][5] = 'o';
    player.stage_1[5][15] = 'o';
    player.stage_1[8][9] = '<';

    for (int i = 4; i < 9; i++) {
        player.stage_1[i][3] = '|';
        player.stage_1[i][23] = '|';
    }
    for (int i = 3; i <= 23; i++) {
        player.stage_1[3][i] = '-';
        player.stage_1[9][i] = '-';
    }
    for (int i = 4; i < 9; i++) {
        for (int j = 4; j < 23; j++) {
            player.stage_1[i][j] = '.';
        }
    }
    for (int i = 0 ; i < n1 ;i++){
        int x = rand() % 5 + 4;
        int y = rand() % 19 + 4;
        if(player.stage_1[x][y]!='.'){
            continue;
        }
        player.stage_1[x][y]='%';
    }
    for (int i = 0 ; i < t1 ;i++){
        int x = rand() % 5 + 4;
        int y = rand() % 19 + 4;
        if(player.stage_1[x][y]!='.'){
            continue;
        }
        player.stage_1[x][y]='T';
    }
    for (int i = 0 ; i < q1 ;i++){
        int x = rand() % 5 + 4;
        int y = rand() % 19 + 4;
        int p = rand()%3;
        if(player.stage_1[x][y]!='.'){
            continue;
        }
        if (p == 0) {
            player.stage_1[x][y]='S';
        } else if (p == 1) {
            player.stage_1[x][y]='H';
        } else if (p == 2) {
            player.stage_1[x][y]='8';
        }
    }

    //Generating room 2

    int q2 = rand() % 3 ;
    int n2 = rand() % 5 + 4;
    int m2 = rand() % 3;


    player.stage_1[7][58] = '+';
    player.stage_1[18][65] = '+';
    player.stage_1[6][45] = 'o';
    player.stage_1[8][41] = 'o';

    for (int i = 8; i < 20; i++) {
        player.stage_1[i][50] = '|';
        player.stage_1[i][65] = '|';
    }
    for (int i = 50; i <= 65; i++) {
        player.stage_1[7][i] = '-';
        player.stage_1[20][i] = '-';
    }
    for (int i = 8; i <= 19; i++) {
        for (int j = 51; j < 65; j++) {
            player.stage_1[i][j] = '.';
        }
    }
    for (int i = 0 ; i < n2 ;i++){
        int x = rand() % 12 + 8;
        int y = rand() % 14 + 51;
        if(player.stage_1[x][y]!='.'){
            continue;
        }
        player.stage_1[x][y]='%';
    }
    for(int i = 0 ; i < 3;i++){
        int x = rand() % 12 + 8;
        int y = rand() % 14 + 51;
        player.stage_1[x][y]='^';
    }
    for (int i = 0 ; i < m2 ;i++){
        int x = rand() % 12 + 8;
        int y = rand() % 14 + 51;
        if(player.stage_1[x][y]!='.'){
            continue;
        }
        player.stage_1[x][y]='T';
    }
    for (int i = 0 ; i < q2 ;i++){
        int x = rand() % 12 + 8;
        int y = rand() % 14 + 51;
        int p = rand()%3;
        if (player.stage_1[x][y] != '.') {
            continue;
        }
        if (p == 0) {
            player.stage_1[x][y]='S';
        } else if (p == 1) {
            player.stage_1[x][y]='H';
        } else if (p == 2) {
            player.stage_1[x][y]='8';
        }
    }

    //Generating room 3

    int n3 = rand() % 4 + 3;
    int m3 = rand() % 3;
    int q3 = rand() % 3;

    player.stage_1[9][100] = '+';
    player.stage_1[10][105] = 'o';
    player.stage_1[14][102] = 'o';
    player.stage_1[15][109] = 'o';

    for (int i = 6; i < 17; i++) {
        player.stage_1[i][100] = '|';
        player.stage_1[i][111] = '|';
    }
    for (int i = 100; i <= 111; i++) {
        player.stage_1[6][i] = '-';
        player.stage_1[16][i] = '-';
    }
    for (int i = 7; i < 16; i++) {
        for (int j = 101; j < 111; j++) {
            player.stage_1[i][j] = '.';
        }
    }
    for (int i = 0 ; i < n3 ;i++){
        int x = rand() % 9 + 7;
        int y = rand() % 10 + 101;
        if(player.stage_1[x][y]!='.'){
            continue;
        }
        player.stage_1[x][y]='%';
    }
    for (int i = 0 ; i < m3 ;i++){
        int x = rand() % 9 + 7;
        int y = rand() % 10 + 101;
        if(player.stage_1[x][y]!='.'){
            continue;
        }
        player.stage_1[x][y]='T';
    }
    for (int i = 0 ; i < q3 ;i++){
        int x = rand() % 9 + 7;
        int y = rand() % 10 + 101;
        int p = rand()%3;
        if (player.stage_1[x][y] != '.') {
            continue;
        }
        if(p == 0) {
            player.stage_1[x][y]='S';
        } else if (p == 1) {
            player.stage_1[x][y]='H';
        } else if (p == 2) {
            player.stage_1[x][y]='8';
        }
    }
    for(int i = 0 ;i<2;i++){
        int x = rand() % 9 + 7;
        int y = rand() % 10 + 101;
        player.stage_1[x][y]='^';
    }

    // Generating room 4

    int n4 = rand() % 4 + 3;
    int a4 = rand() % 2 + 2;
    int m4 = rand() % 3;
    int q4 = rand() % 2 + 1;

    player.stage_1[28][158] = '&';
    player.stage_1[20][152] = '+';
    player.stage_1[25][150] = '@';
    player.stage_1[22][152] = 'o';
    player.stage_1[28][156] = 'o';


    for (int i = 20; i < 30; i++) {
        player.stage_1[i][150] = '|';
        player.stage_1[i][159] = '|';
    }
    for (int i = 150; i <= 159; i++) {
        player.stage_1[20][i] = '-';
        player.stage_1[29][i] = '-';
    }
    for (int i = 21; i < 29; i++) {
        for (int j = 151; j < 159; j++) {
            player.stage_1[i][j] = '.';
        }
    }
    for (int i = 0 ; i < n4 ;i++){
        int x = rand() % 8 + 21;
        int y = rand() % 8 + 151;
        if(player.stage_1[x][y]!='.'){
            continue;
        }
        player.stage_1[x][y]='%';
    }
    for (int i = 0 ; i < m4 ;i++){
        int x = rand() % 8 + 21;
        int y = rand() % 8 + 151;
        if(player.stage_1[x][y]!='.'){
            continue;
        }
        player.stage_1[x][y]='T';
    }
    for (int i = 0 ; i < a4 ;i++){
        int x = rand() % 8 + 21;
        int y = rand() % 8 + 151;
        if(player.stage_1[x][y]!='.'){
            continue;
        }
        player.stage_1[x][y]='X';
    }
    for (int i = 0 ; i < q4 ;i++){
        int x = rand() % 8 + 21;
        int y = rand() % 8 + 151;
        int p = rand()%3;
        if(player.stage_1[x][y]!='.'){
            continue;
        }
        if (p == 0) {
            player.stage_1[x][y]='S';
        } else if (p == 1) {
            player.stage_1[x][y]='H';
        } else if (p == 2) {
            player.stage_1[x][y]='8';
        }
    }

    // Generating room 5

    int m5 = rand() % 3;
    int n5 = rand() % 3 + 3;
    int q5 = rand() % 3 + 4;
    int x = rand() % 4 + 31;
    int y = rand() % 15 + 95;

    player.stage_1[x][y]='^';
    player.stage_1[34][110] = '+';
    player.stage_1[31][99] = 'o';
    player.stage_1[33][107] = 'o';

    for (int i = 30; i < 36; i++) {
        player.stage_1[i][94] = '|';
        player.stage_1[i][110] = '|';
    }
    for (int i = 94; i <= 110; i++) {
        player.stage_1[30][i] = '-';
        player.stage_1[35][i] = '-';
    }
    for (int i = 31; i < 35; i++) {
        for (int j = 95; j < 110; j++) {
            player.stage_1[i][j] = '.';
        }
    }
    for (int i = 0 ; i < n5 ;i++){
        int x = rand() % 4 + 31;
        int y = rand() % 15 + 95;
        if(player.stage_1[x][y]!='.'){
            continue;
        }
        player.stage_1[x][y]='%';
    }
    for (int i = 0 ; i < m5 ;i++){
        int x = rand() % 4 + 31;
        int y = rand() % 15 + 95;
        if(player.stage_1[x][y]!='.'){
            continue;
        }
        player.stage_1[x][y]='T';
    }
    for (int i = 0 ; i < q5 ;i++){
        int x = rand() % 4 + 31;
        int y = rand() % 15 + 95;
        int p = rand()%3;
        if(player.stage_1[x][y]!='.'){
            continue;
        }
        if (p == 0) {
            player.stage_1[x][y]='S';
        } else if (p == 1) {
            player.stage_1[x][y]='H';
        } else if (p == 2) {
            player.stage_1[x][y]='8';
        }
    }

    // Generating room 6
    
    int n6 = rand() % 3 + 2;
    int m6 = rand() % 2 + 1;
    int q6 = rand() % 3 + 4;

    player.stage_1[30][20] = '+';
    player.stage_1[30][12] = 'o';
    player.stage_1[36][17] = 'o';
    player.stage_1[36][13] = '<';

    for (int i = 28; i < 38; i++) {
        player.stage_1[i][10] = '|';
        player.stage_1[i][20] = '|';
    }
    for (int i = 10; i <= 20; i++) {
        player.stage_1[28][i] = '-';
        player.stage_1[37][i] = '-';
    }
    for (int i = 29; i < 37; i++) {
        for (int j = 11; j < 20; j++) {
            player.stage_1[i][j] = '.';
        }
    }
    for (int i = 0 ; i < n6 ;i++){
        int x = rand() % 8 + 29;
        int y = rand() % 9 + 11;
        if(player.stage_1[x][y]!='.'){
            continue;
        }
        player.stage_1[x][y]='%';
    }
    for (int i = 0 ; i < m6 ;i++){
        int x = rand() % 8 + 29;
        int y = rand() % 9 + 11;
        if(player.stage_1[x][y]!='.'){
            continue;
        }
        player.stage_1[x][y]='Z';
    }
    for (int i = 0 ; i < q6 ;i++){
        int x = rand() % 8 + 29;
        int y = rand() % 9 + 11;
        int p = rand() % 2 + 1;
        if(player.stage_1[x][y]!='.'){
            continue;
        }
        if (p == 0) {
            player.stage_1[x][y]='S';
        } else if (p == 1) {
            player.stage_1[x][y]='H';
        } else if (p == 2) {
            player.stage_1[x][y]='8';
        }
    }
    for(int i = 0 ; i < 2 ; i++){
        int x = rand() % 8 + 29;
        int y = rand() % 9 + 11;
        player.stage_1[x][y]='^';
    }

    generate_corridor(24, 5, 59, 6,player.stage_1);
    generate_corridor(66,18, 100, 9,player.stage_1);
    generate_corridor(112, 14, 153, 19,player.stage_1);
    generate_corridor(149, 25, 110, 34,player.stage_1);
    generate_corridor(93, 32, 20, 30,player.stage_1);

    return(0);
}


int create_map_2() {
    memset(player.stage_2, ' ', sizeof(player.stage_2));

    //Room 1

    int q1 = rand() % 3 + 7;

    player.stage_2[10][12] = 'o';
    player.stage_2[8][16] = 'o';
    player.stage_2[9][17] = '<';

    for (int i = 6; i < 15; i++) {
        player.stage_2[i][10] = '|';
        player.stage_2[i][18] = '|';
    }
    for (int i = 10; i <= 18; i++) {
        player.stage_2[6][i] = '-';
        player.stage_2[14][i] = '-';
    }
    for (int i = 7; i < 14; i++) {
        for (int j = 11; j < 18; j++) {
            player.stage_2[i][j] = '.';
        }
    }
    for (int i = 0 ; i < q1 ;i++){
        int x = rand() % 7 + 7;
        int y = rand() % 7 + 11;
        int p = rand()%3;
        if (player.stage_2[x][y] != '.') {
            continue;
        }
        if (p == 0) {
            player.stage_2[x][y]='S';
        } else if (p == 1) {
            player.stage_2[x][y]='H';
        } else if (p == 2) {
            player.stage_2[x][y]='8';
        }
    }

    //Room 2

    int n1 = rand() % 3 + 4;
    int t1 = rand() % 2 + 1;

    player.stage_2[6][36] = '&';
    player.stage_2[12][35] = '+';
    player.stage_2[9][48] = '@';
    player.stage_2[11][45] = 'o';
    player.stage_2[9][37] = 'o';

    for (int i = 5; i < 14; i++) {
        player.stage_2[i][35] = '|';
        player.stage_2[i][48] = '|';
    }
    for (int i = 35; i <= 48; i++) {
        player.stage_2[5][i] = '-';
        player.stage_2[13][i] = '-';
    }
    for (int i = 6; i < 13; i++) {
        for (int j = 36; j < 48; j++) {
            player.stage_2[i][j] = '.';
        }
    }
    for (int i = 0 ; i < n1 ;i++){
        int x = rand() % 7 + 6;
        int y = rand() % 12 + 36;
        if (player.stage_2[x][y] != '.') {
            continue;
        }
        player.stage_2[x][y]='%';
    }
    for (int i = 0 ; i < t1 ;i++){
        int x = rand() % 7 + 6;
        int y = rand() % 12 + 36;
        if (player.stage_2[x][y] != '.') {
            continue;
        }
        player.stage_2[x][y]='T';
    }

    //Room 3
    
    int n3 = rand() % 3 + 4;
    int q3 = rand() % 3 + 2;

    player.stage_2[7][120] = '+';
    player.stage_2[5][126] = 'o';
    player.stage_2[6][131] = 'o';
    player.stage_2[11][122] = 'o';

    for (int i = 3; i < 13; i++) {
        player.stage_2[i][120] = '|';
        player.stage_2[i][135] = '|';
    }
    for (int i = 120; i <= 135; i++) {
        player.stage_2[3][i] = '-';
        player.stage_2[12][i] = '-';
    }
    for (int i = 4; i < 12; i++) {
        for (int j = 121; j < 135; j++) {
            player.stage_2[i][j] = '.';
        }
    }
    for (int i = 0 ; i < n3 ;i++){
        int x = rand() % 8 + 4;
        int y = rand() % 14 + 121;
        if (player.stage_2[x][y] != '.') {
            continue;
        }
        player.stage_2[x][y]='%';
    }
    for (int i = 0 ; i < q3 ;i++){
        int x = rand() % 8 + 4;
        int y = rand() % 14 + 121;
        int p = rand()%3;
        if (player.stage_2[x][y] != '.') {
            continue;
        }
        if (p == 0) {
            player.stage_2[x][y]='S';
        } else if (p == 1) {
            player.stage_2[x][y]='H';
        } else if (p == 2) {
            player.stage_2[x][y]='8';
        }
    }

    //Room 4

    int n2 = rand() % 3 + 2;
    int t2 = rand() % 2 + 2;
    int q4 = rand() % 3 + 1;

    player.stage_2[30][167] = '+';
    player.stage_2[39][160] = '+';
    player.stage_2[35][169] = 'o';
    player.stage_2[40][163] = 'o';

    for (int i = 30; i < 42; i++) {
        player.stage_2[i][160] = '|';
        player.stage_2[i][175] = '|';
    }
    for (int i = 160; i <= 175; i++) {
        player.stage_2[30][i] = '-';
        player.stage_2[41][i] = '-';
    }
    for (int i = 31; i < 41; i++) {
        for (int j = 161; j < 175; j++) {
            player.stage_2[i][j] = '.';
        }
    }
    for (int i = 0 ; i < n2 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 161;
        if(player.stage_2[x][y]!='.'){
            continue;
        }
        player.stage_2[x][y]='%';
    }
    for (int i = 0 ; i < t2 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 161;
        if (player.stage_2[x][y] != '.') {
            continue;
        }
        player.stage_2[x][y]='T';
    }
    for (int i = 0 ; i < q4 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 161;
        int p = rand()%3;
        if (player.stage_2[x][y] != '.') {
            continue;
        }
        if (p == 0) {
            player.stage_2[x][y]='S';
        } else if (p == 1) {
            player.stage_2[x][y]='H';
        } else if (p == 2) {
            player.stage_2[x][y]='8';
        }
    }

    //Room 5

    int n5 = rand() % 3 + 3;
    int q5 = rand() % 3 + 5;

    player.stage_2[33][108] = '&';
    player.stage_2[32][94] = '@';
    player.stage_2[34][110] = '+';
    player.stage_2[31][99] = 'o';
    player.stage_2[33][107] = 'o';

    for (int i = 30; i < 36; i++) {
        player.stage_2[i][94] = '|';
        player.stage_2[i][110] = '|';
    }
    for (int i = 94; i <= 110; i++) {
        player.stage_2[30][i] = '-';
        player.stage_2[35][i] = '-';
    }
    for (int i = 31; i < 35; i++) {
        for (int j = 95; j < 110; j++) {
            player.stage_2[i][j] = '.';
        }
    }
    for (int i = 0 ; i < n5 ;i++){
        int x = rand() % 4 + 31;
        int y = rand() % 15 + 95;
        if (player.stage_2[x][y] != '.') {
            continue;
        }
        player.stage_2[x][y]='%';
    }
    for (int i = 0 ; i < q5 ;i++){
        int x = rand() % 4 + 31;
        int y = rand() % 15 + 95;
        int p = rand()%3;
        if(player.stage_2[x][y]!='.'){
            continue;
        }
        if (p == 0) {
            player.stage_2[x][y]='S';
        } else if (p == 1) {
            player.stage_2[x][y]='H';
        } else if (p == 2) {
            player.stage_2[x][y]='8';
        }
    }

    //Room 6

    int n6 = rand() % 3 + 2;
    int t3 = rand() % 2 + 1;
    int q6 = rand() % 3 + 1;

    player.stage_2[17][60] = '+';
    player.stage_2[20][53] = 'o';
    player.stage_2[19][57] = 'o';

    for (int i = 15; i < 23; i++) {
        player.stage_2[i][50] = '|';
        player.stage_2[i][60] = '|';
    }
    for (int i = 50; i <= 60; i++) {
        player.stage_2[15][i] = '-';
        player.stage_2[22][i] = '-';
    }
    for (int i = 16; i < 22; i++) {
        for (int j = 51; j < 60; j++) {
            player.stage_2[i][j] = '.';
        }
    }
    for (int i = 0 ; i < n6 ;i++){
        int x = rand() % 6 + 16;
        int y = rand() % 9 + 51;
        if(player.stage_2[x][y]!='.'){
            continue;
        }
        player.stage_2[x][y]='%';
    }
    for (int i = 0 ; i < t3 ;i++){
        int x = rand() % 6 + 166;
        int y = rand() % 9 + 51;
        if(player.stage_2[x][y]!='.'){
            continue;
        }
        player.stage_2[x][y]='T';
    }
    for (int i = 0 ; i < q6 ;i++){
        int x = rand() % 6 + 166;
        int y = rand() % 9 + 51;
        int p = rand()%3;
        if(player.stage_2[x][y]!='.'){
            continue;
        }
        if (p == 0) {
            player.stage_2[x][y]='S';
        } else if (p == 1) {
            player.stage_2[x][y]='H';
        } else if (p == 2) {
            player.stage_2[x][y]='8';
        }
    }

    //Room 7

    int q7 = rand() % 3 ;
    int n7 = rand() % 3 + 2;

    player.stage_2[28][20] = '+';
    player.stage_2[30][12] = 'o';
    player.stage_2[29][17] = 'o';

    for (int i = 28; i < 33; i++) {
        player.stage_2[i][11] = '|';
        player.stage_2[i][26] = '|';
    }
    for (int i = 11; i <= 26; i++) {
        player.stage_2[28][i] = '-';
        player.stage_2[32][i] = '-';
    }
    for (int i = 29; i < 32; i++) {
        for (int j = 12; j < 26; j++) {
            player.stage_2[i][j] = '.';
        }
    }
    for (int i = 0 ; i < q7 ;i++){
        int x = rand() % 3 + 29;
        int y = rand() % 14 + 12;
        int p = rand()%3;
        if (player.stage_2[x][y] != '.') {
            continue;
        }
        if (p == 0) {
            player.stage_2[x][y]='S';
        } else if (p == 1) {
            player.stage_2[x][y]='H';
        } else if (p == 2) {
            player.stage_2[x][y]='8';
        }
    }
    for (int i = 0 ; i < n7 ;i++){
        int x = rand() % 3 + 29;
        int y = rand() % 14 + 12;
        if(player.stage_2[x][y] != '.'){
            continue;
        }
        player.stage_2[x][y]='%';
    }

    generate_corridor(19, 7, 35, 12,player.stage_2);
    generate_corridor(49, 9, 120, 7,player.stage_2);
    generate_corridor(127, 13, 168, 29,player.stage_2);
    generate_corridor(159, 39, 110, 34,player.stage_2);
    generate_corridor(93, 32, 60, 17,player.stage_2);
    generate_corridor(49, 21, 19, 27,player.stage_2);
}


int create_map_3() {
    memset(player.stage_3, ' ', sizeof(player.stage_3));

    //Room 1

    int n3 = rand() % 3 + 1;
    int t3 = rand() % 2 + 1;
    int m3 = rand() % 2 + 1;
    int q1 = rand() % 4;

    player.stage_3[12][41] = '+';
    player.stage_3[11][40] = 'o';
    player.stage_3[9][37] = 'o';

    for (int i = 6; i < 16; i++) {
        player.stage_3[i][35] = '|';
        player.stage_3[i][41] = '|';
    }
    for (int i = 35; i <= 41; i++) {
        player.stage_3[6][i] = '-';
        player.stage_3[15][i] = '-';
    }
    for (int i = 7; i < 15; i++) {
        for (int j = 36; j < 41; j++) {
            player.stage_3[i][j] = '.';
        }
    }
    for (int i = 0 ; i < n3 ;i++){
        int x = rand() % 8 + 7;
        int y = rand() % 5 + 36;
        if (player.stage_3[x][y] != '.') {
            continue;
        }
        player.stage_3[x][y]='%';
    }
    for (int i = 0 ; i < t3 ;i++){
        int x = rand() % 8 + 7;
        int y = rand() % 5 + 36;
        if(player.stage_3[x][y]!='.'){
            continue;
        }
        player.stage_3[x][y]='T';
    }
    for (int i = 0 ; i < m3 ;i++){
        int x = rand() % 8 + 7;
        int y = rand() % 5 + 36;
        if(player.stage_3[x][y]!='.'){
            continue;
        }
        player.stage_3[x][y]='X';
    }
    for (int i = 0 ; i < q1 ;i++){
        int x = rand() % 8 + 7;
        int y = rand() % 5 + 36;
        int p = rand()%3;
        if (player.stage_3[x][y] != '.') {
            continue;
        }
        if (p == 0) {
            player.stage_3[x][y]='S';
        } else if (p == 1) {
            player.stage_3[x][y]='H';
        } else if (p == 2) {
            player.stage_3[x][y]='8';
        }
    }

    //Room 2

    int n9 = rand() % 4 + 2;
    int t9 = rand() % 4 + 2;
    int q2 = rand() % 3 + 1;

    player.stage_3[15][72] = '&';
    player.stage_3[13][70] = '@';
    player.stage_3[14][84] = '+';
    player.stage_3[13][75] = 'o';
    player.stage_3[15][80] = 'o';

    for (int i = 12; i < 17; i++) {
        player.stage_3[i][70] = '|';
        player.stage_3[i][84] = '|';
    }
    for (int i = 70; i <= 84; i++) {
        player.stage_3[12][i] = '-';
        player.stage_3[16][i] = '-';
    }
    for (int i = 13; i < 16; i++) {
        for (int j = 71; j < 84; j++) {
            player.stage_3[i][j] = '.';
        }
    }
    for (int i = 0 ; i < n9 ;i++){
        int x = rand() % 3 + 13;
        int y = rand() % 13 + 71;
        if(player.stage_3[x][y]!='.'){
            continue;
        }
        player.stage_3[x][y]='%';
    }
    for (int i = 0 ; i < t9 ;i++){
        int x = rand() % 3 + 13;
        int y = rand() % 13 + 71;
        if(player.stage_3[x][y]!='.'){
            continue;
        }
        player.stage_3[x][y]='t';
    }
    for (int i = 0 ; i < q2 ;i++){
        int x = rand() % 3 + 13;
        int y = rand() % 13 + 71;
        int p = rand()%3;
        if (player.stage_3[x][y] != '.') {
            continue;
        }
        if (p == 0) {
            player.stage_3[x][y]='S';
        } else if (p == 1) {
            player.stage_3[x][y]='H';
        } else if (p == 2) {
            player.stage_3[x][y]='8';
        }
    }

    //Room 3

    int n1 = rand() % 3 + 3;
    int t1 = rand() % 5 + 3;
    int m1 = rand() % 2+1;
    int q3 = rand() % 3 + 1;

    player.stage_3[19][132] = '+';
    player.stage_3[10][140] = 'o';
    player.stage_3[15][136] = 'o';
    player.stage_3[18][130] = 'o';

    for (int i = 5; i < 20; i++) {
        player.stage_3[i][125] = '|';
        player.stage_3[i][145] = '|';
    }
    for (int i = 125; i <= 145; i++) {
        player.stage_3[5][i] = '-';
        player.stage_3[19][i] = '-';
    }
    for (int i = 6; i < 19; i++) {
        for (int j = 126; j < 145; j++) {
            player.stage_3[i][j] = '.';
        }
    }
    for (int i = 0 ; i < n1 ;i++){
        int x = rand() % 13 + 6;
        int y = rand() % 9 + 126;
        if (player.stage_3[x][y] != '.') {
            continue;
        }
        player.stage_3[x][y]='%';
    }
    for (int i = 0 ; i < t1 ;i++){
        int x = rand() % 13 + 6;
        int y = rand() % 9 + 126;
        if (player.stage_3[x][y] != '.') {
            continue;
        }
        player.stage_3[x][y]='T';
    }
    for (int i = 0 ; i < t3 ;i++){
        int x = rand() % 13 + 6;
        int y = rand() % 9 + 126;
        if(player.stage_3[x][y]!='.'){
            continue;
        }
        player.stage_3[x][y]='X';
    }
    for (int i = 0 ; i < q3 ;i++){
        int x = rand() % 13 + 6;
        int y = rand() % 9 + 126;
        int p = rand()%3;
        if (player.stage_3[x][y] != '.') {
            continue;
        }
        if (p == 0) {
            player.stage_3[x][y]='S';
        } else if (p == 1) {
            player.stage_3[x][y]='H';
        } else if (p == 2) {
            player.stage_3[x][y]='8';
        }
    }

    //Room 4

    int n2 = rand() % 3 + 4;
    int t2 = rand() % 5 + 3;
    int m2 = rand() % 2 + 1;
    int q4 = rand() % 3;

    player.stage_3[39][160] = '+';
    player.stage_3[35][169] = 'o';
    player.stage_3[40][163] = 'o';

    for (int i = 30; i < 42; i++) {
        player.stage_3[i][160] = '|';
        player.stage_3[i][175] = '|';
    }
    for (int i = 160; i <= 175; i++) {
        player.stage_3[30][i] = '-';
        player.stage_3[41][i] = '-';
    }
    for (int i = 31; i < 41; i++) {
        for (int j = 161; j < 175; j++) {
            player.stage_3[i][j] = '.';
        }
    }
    for (int i = 0 ; i < n2 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 161;
        if (player.stage_3[x][y] != '.') {
            continue;
        }
        player.stage_3[x][y]='%';
    }
    for (int i = 0 ; i < t2 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 161;
        if (player.stage_3[x][y] != '.') {
            continue;
        }
        player.stage_3[x][y]='T';
    }
    for (int i = 0 ; i < m2 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 161;
        if (player.stage_3[x][y] != '.') {
            continue;
        }
        player.stage_3[x][y]='Z';
    }
    for (int i = 0 ; i < q4 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 161;
        int p = rand()%3;
        if (player.stage_3[x][y] != '.') {
            continue;
        }
        if (p == 0) {
            player.stage_3[x][y]='S';
        } else if (p == 1) {
            player.stage_3[x][y]='H';
        } else if (p == 2) {
            player.stage_3[x][y]='8';
        }
    }

    //Room 5

    int n5 = rand() % 5 + 3;
    int t5 = rand() % 5 + 3;
    int q5 = rand() % 3+2;
    int a5 = rand() % 2 + 1;

    player.stage_3[34][87] = '&';
    player.stage_3[32][84] = '+';
    player.stage_3[34][100] = '@';
    player.stage_3[31][99] = 'o';
    player.stage_3[33][86] = 'o';

    for (int i = 30; i < 36; i++) {
        player.stage_3[i][84] = '|';
        player.stage_3[i][100] = '|';
    }
    for (int i = 84; i <= 100; i++) {
        player.stage_3[30][i] = '-';
        player.stage_3[35][i] = '-';
    }
    for (int i = 31; i < 35; i++) {
        for (int j = 85; j < 100; j++) {
            player.stage_3[i][j] = '.';
        }
    }
    for (int i = 0 ; i < t5 ;i++){
        int x = rand() % 4 + 31;
        int y = rand() % 15 + 85;
        if(player.stage_3[x][y]!='.'){
            continue;
        }
        player.stage_3[x][y]='T';
    }
    for (int i = 0 ; i < a5 ;i++){
        int x = rand() % 4 + 31;
        int y = rand() % 15 + 85;
        if(player.stage_3[x][y]!='.'){
            continue;
        }
        player.stage_3[x][y]='Z';
    }
    for (int i = 0 ; i < n5 ;i++){
        int x = rand() % 4 + 31;
        int y = rand() % 15 + 85;
        if (player.stage_3[x][y] != '.') {
            continue;
        }
        player.stage_3[x][y]='%';
    }
    for (int i = 0 ; i < q5 ;i++){
        int x = rand() % 4 + 31;
        int y = rand() % 15 + 85;
        int p = rand()%3;
        if (player.stage_3[x][y] != '.') {
            continue;
        }
        if (p == 0) {
            player.stage_3[x][y]='S';
        } else if (p == 1) {
            player.stage_3[x][y]='H';
        } else if (p == 2) {
            player.stage_3[x][y]='8';
        }
    }

    //Room 6

    int n7 = rand() % 5 + 4;
    int t7 = rand() % 3 + 2;
    int q6 = rand() % 7 + 4;

    player.stage_3[22][26] = '+';
    player.stage_3[30][20] = 'o';
    player.stage_3[30][20] = '<';

    for (int i = 21; i < 35; i++) {
        player.stage_3[i][12] = '|';
        player.stage_3[i][26] = '|';
    }
    for (int i = 12; i <= 26; i++) {
        player.stage_3[21][i] = '-';
        player.stage_3[34][i] = '-';
    }
    for (int i = 22; i < 34; i++) {
        for (int j = 13; j < 26; j++) {
            player.stage_3[i][j] = '.';
        }
    }
    for (int i = 0 ; i < n7 ;i++){
        int x = rand() % 12 + 22;
        int y = rand() % 13 + 13;
        if(player.stage_3[x][y]!='.'){
            continue;
        }
        player.stage_3[x][y]='%';
    }
    for (int i = 0 ; i < t7 ;i++){
        int x = rand() % 12 + 22;
        int y = rand() % 13 + 13;
        if(player.stage_3[x][y]!='.'){
            continue;
        }
        player.stage_3[x][y]='T';
    }
    for (int i = 0 ; i < q6 ;i++){
        int x = rand() % 12 + 22;
        int y = rand() % 13 + 13;
        int p = rand()%3;
        if (player.stage_3[x][y] != '.') {
            continue;
        }
        if (p == 0) {
            player.stage_3[x][y]='S';
        } else if (p == 1) {
            player.stage_3[x][y]='H';
        } else if (p == 2) {
            player.stage_3[x][y]='8';
        }
    }

    generate_corridor(27, 22, 84, 32,player.stage_3);
    generate_corridor(101, 34, 160, 39,player.stage_3);
    generate_corridor(167, 29, 131, 20,player.stage_3);
    generate_corridor(124, 7, 84, 14,player.stage_3);
    generate_corridor(69, 13, 41, 12,player.stage_3);
}



int create_map_4() {
    memset(player.stage_4, ' ', sizeof(player.stage_4));

    //Room 1

    int n0 = rand() % 3+3;
    int t0 = rand() % 4+4;
    int a1 = rand() % 5+6;

    player.stage_4[7][18] = '+';
    player.stage_4[10][12] = 'o';
    player.stage_4[8][16] = 'o';

    for (int i = 6; i < 15; i++) {
        player.stage_4[i][10] = '|';
        player.stage_4[i][18] = '|';
    }
    for (int i = 10; i <= 18; i++) {
        player.stage_4[6][i] = '-';
        player.stage_4[14][i] = '-';
    }
    for (int i = 7; i < 14; i++) {
        for (int j = 11; j < 18; j++) {
            player.stage_4[i][j] = '.';
        }
    }
    for (int i = 0 ; i < n0 ;i++){
        int x = rand() % 7 + 7;
        int y = rand() % 7 + 11;
        if (player.stage_4[x][y] != '.') {
            continue;
        }
        player.stage_4[x][y]='%';
    }
    for (int i = 0 ; i < t0 ;i++){
        int x = rand() % 7 + 7;
        int y = rand() % 7 + 11;
        if (player.stage_4[x][y] != '.') {
            continue;
        }
        player.stage_4[x][y]='Z';
    }
    for (int i = 0 ; i < a1 ;i++){
        int x = rand() % 7 + 7;
        int y = rand() % 7 + 11;
        if (player.stage_4[x][y] != '.') {
            continue;
        }
        player.stage_4[x][y]='T';
    }

    //Room 2

    int n1 = rand() % 3 + 3;
    int t1 = rand() % 2 + 3;
    int q2 = rand() % 3 + 2;

    player.stage_4[6][37] = '&';
    player.stage_4[12][35] = '@';
    player.stage_4[9][48] = '+';
    player.stage_4[11][45] = 'o';
    player.stage_4[9][37] = 'o';

    for (int i = 5; i < 14; i++) {
        player.stage_4[i][35] = '|';
        player.stage_4[i][48] = '|';
    }
    for (int i = 35; i <= 48; i++) {
        player.stage_4[5][i] = '-';
        player.stage_4[13][i] = '-';
    }
    for (int i = 6; i < 13; i++) {
        for (int j = 36; j < 48; j++) {
            player.stage_4[i][j] = '.';
        }
    }
    for (int i = 0 ; i < n1 ;i++){
        int x = rand() % 7 + 6;
        int y = rand() % 12 + 36;
        if (player.stage_4[x][y] != '.') {
            continue;
        }
        player.stage_4[x][y]='%';
    }
    for (int i = 0 ; i < t1 ;i++){
        int x = rand() % 7 + 6;
        int y = rand() % 12 + 36;
        if (player.stage_4[x][y] != '.') {
            continue;
        }
        player.stage_4[x][y]='T';
    }
    for (int i = 0 ; i < q2 ;i++){
        int x = rand() % 7 + 6;
        int y = rand() % 12 + 36;
        int p = rand()%3;
        if (player.stage_4[x][y] != '.') {
            continue;
        }
        if (p == 0) {
            player.stage_4[x][y]='S';
        } else if (p == 1) {
            player.stage_4[x][y]='H';
        } else if (p == 2) {
            player.stage_4[x][y]='8';
        }
    }

    //Room 3

    int n5 = rand() % 3 + 4;
    int t5 = rand() % 2+2;
    int m5 = rand() % 2+1;
    int q3 = rand() % 5 + 5 ;

    player.stage_4[12][127] = '+';
    player.stage_4[5][126] = 'o';
    player.stage_4[6][131] = 'o';
    player.stage_4[11][122] = 'o';

    for (int i = 3; i < 13; i++) {
        player.stage_4[i][120] = '|';
        player.stage_4[i][135] = '|';
    }
    for (int i = 120; i <= 135; i++) {
        player.stage_4[3][i] = '-';
        player.stage_4[12][i] = '-';
    }
    for (int i = 4; i < 12; i++) {
        for (int j = 121; j < 135; j++) {
            player.stage_4[i][j] = '.';
        }
    }
    for (int i = 0 ; i < n5 ;i++){
        int x = rand() % 8 + 4;
        int y = rand() % 14 + 121;
        if (player.stage_4[x][y] != '.') {
            continue;
        }
        player.stage_4[x][y]='%';
    }
    for (int i = 0 ; i < t5 ;i++){
        int x = rand() % 8 + 4;
        int y = rand() % 14 + 121;
        if (player.stage_4[x][y] != '.') {
            continue;
        }
        player.stage_4[x][y]='T';
    }
    for (int i = 0 ; i < m5 ;i++){
        int x = rand() % 8 + 4;
        int y = rand() % 14 + 121;
        if (player.stage_4[x][y] != '.') {
            continue;
        }
        player.stage_4[x][y]='Z';
    }
    for (int i = 0 ; i < q3 ;i++){
        int x = rand() % 8 + 4;
        int y = rand() % 14 + 121;
        int p = rand()%3;
        if (player.stage_4[x][y] != '.') {
            continue;
        }
        if (p == 0) {
            player.stage_4[x][y]='S';
        } else if (p == 1) {
            player.stage_4[x][y]='H';
        } else if (p == 2) {
            player.stage_4[x][y]='8';
        }
    }

    //Room 4

    int n2 = rand() % 3+2;
    int t2 = rand() % 2+4;
    int m2 = rand() % 2;
    int q4 = rand() % 2 + 2 ;

    player.stage_4[40][174] = '&';
    player.stage_4[30][167] = '@';
    player.stage_4[39][160] = '+';
    player.stage_4[35][169] = 'o';
    player.stage_4[40][163] = 'o';

    for (int i = 30; i < 42; i++) {
        player.stage_4[i][160] = '|';
        player.stage_4[i][175] = '|';
    }
    for (int i = 160; i <= 175; i++) {
        player.stage_4[30][i] = '-';
        player.stage_4[41][i] = '-';
    }
    for (int i = 31; i < 41; i++) {
        for (int j = 161; j < 175; j++) {
            player.stage_4[i][j] = '.';
        }
    }
    for (int i = 0 ; i < n2 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 161;
        if(player.stage_4[x][y]!='.'){
            continue;
        }
        player.stage_4[x][y]='%';
    }
    for (int i = 0 ; i < t2 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 161;
        if(player.stage_4[x][y]!='.'){
            continue;
        }
        player.stage_4[x][y]='T';
    }
    for (int i = 0 ; i < m2 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 161;
        if(player.stage_4[x][y]!='.'){
            continue;
        }
        player.stage_4[x][y]='X';
    }
    for (int i = 0 ; i < q4 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 161;
        int p = rand() % 3;
        if (player.stage_4[x][y] != '.') {
            continue;
        }
        if (p == 0) {
            player.stage_4[x][y]='S';
        } else if (p == 1) {
            player.stage_4[x][y]='H';
        } else if (p == 2) {
            player.stage_4[x][y]='8';
        }
    }

    //Room 5

    int n3 =rand() % 2 + 3;
    int t3 = rand() % 2;
    int m3 = rand() % 2 + 1;
    int q5 = rand() % 2 + 2 ;

    player.stage_4[32][94] = '+';
    player.stage_4[31][99] = 'o';
    player.stage_4[33][107] = 'o';

    for (int i = 30; i < 36; i++) {
        player.stage_4[i][94] = '|';
        player.stage_4[i][110] = '|';
    }
    for (int i = 94; i <= 110; i++) {
        player.stage_4[30][i] = '-';
        player.stage_4[35][i] = '-';
    }
    for (int i = 31; i < 35; i++) {
        for (int j = 95; j < 110; j++) {
            player.stage_4[i][j] = '.';
        }
    }
    for (int i = 0 ; i < n3 ;i++){
        int x = rand() % 4 + 31;
        int y = rand() % 15 + 95;
        if (player.stage_4[x][y] != '.') {
            continue;
        }
        player.stage_4[x][y]='%';
    }
    for (int i = 0 ; i < t3 ;i++){
        int x = rand() % 4 + 31;
        int y = rand() % 15 + 95;
        if (player.stage_4[x][y] != '.') {
            continue;
        }
        player.stage_4[x][y]='T';
    }
    for (int i = 0 ; i < m3 ;i++){
        int x = rand() % 4 + 31;
        int y = rand() % 15 + 95;
        if (player.stage_4[x][y] != '.') {
            continue;
        }
        player.stage_4[x][y]='X';
    }
    for (int i = 0 ; i < q5 ;i++){
        int x = rand() % 4 + 31;
        int y = rand() % 15 + 95;
        int p = rand() % 3;
        if (player.stage_4[x][y] != '.') {
            continue;
        }
        if (p == 0) {
            player.stage_4[x][y]='S';
        } else if (p == 1) {
            player.stage_4[x][y]='H';
        } else if (p == 2) {
            player.stage_4[x][y]='8';
        }
    }

    //Room 6

    int t6 = rand() % 3 ;
    int q6 = rand() % 5 + 4 ;
    int n6 = rand() % 3 ;

    player.stage_4[16][52] = '&';
    player.stage_4[17][60] = '@';
    player.stage_4[21][50] = '+';
    player.stage_4[20][53] = 'o';
    player.stage_4[19][57] = 'o';

    for (int i = 15; i < 23; i++) {
        player.stage_4[i][50] = '|';
        player.stage_4[i][60] = '|';
    }
    for (int i = 50; i <= 60; i++) {
        player.stage_4[15][i] = '-';
        player.stage_4[22][i] = '-';
    }
    for (int i = 16; i < 22; i++) {
        for (int j = 51; j < 60; j++) {
            player.stage_4[i][j] = '.';
        }
    }
    for (int i = 0 ; i < t6 ;i++){
        int x = rand() % 6 + 16;
        int y = rand() % 9 + 51;
        if (player.stage_4[x][y] != '.') {
            continue;
        }
        player.stage_4[x][y]='T';
    }
    for (int i = 0 ; i < n6 ;i++){
        int x = rand() % 6 + 16;
        int y = rand() % 9 + 51;
        if (player.stage_4[x][y] != '.') {
            continue;
        }
        player.stage_4[x][y]='%';
    }
    for (int i = 0 ; i < q6 ;i++){
        int x = rand() % 6 + 16;
        int y = rand() % 9 + 51;
        int p = rand() % 3;
        if (player.stage_4[x][y] != '.') {
            continue;
        }
        if (p == 0) {
            player.stage_4[x][y]='S';
        } else if (p == 1) {
            player.stage_4[x][y]='H';
        } else if (p == 2) {
            player.stage_4[x][y]='8';
        }
    }

    //Room 7

    int m7 = rand() % 2 + 1;
    int t7 = rand() % 3 ;
    int n7 = rand() % 3 + 1 ;
    int q7 = rand() % 2 + 2 ;

    player.stage_4[28][20] = '+';
    player.stage_4[32][24] = '+';
    player.stage_4[30][12] = 'o';
    player.stage_4[29][17] = 'o';

    for (int i = 28; i < 33; i++) {
        player.stage_4[i][11] = '|';
        player.stage_4[i][26] = '|';
    }
    for (int i = 11; i <= 26; i++) {
        player.stage_4[28][i] = '-';
        player.stage_4[32][i] = '-';
    }
    for (int i = 29; i < 32; i++) {
        for (int j = 12; j < 26; j++) {
            player.stage_4[i][j] = '.';
        }
    }
    for (int i = 0 ; i < m7 ;i++){
        int x = rand() % 3 + 29;
        int y = rand() % 14 + 12;
        if (player.stage_4[x][y] != '.') {
            continue;
        }
        player.stage_4[x][y]='Z';
    }
    for (int i = 0 ; i < t7 ;i++){
        int x = rand() % 3 + 29;
        int y = rand() % 14 + 12;
        if (player.stage_4[x][y] != '.') {
            continue;
        }
        player.stage_4[x][y]='T';
    }
    for (int i = 0 ; i < n7 ;i++){
        int x = rand() % 3 + 29;
        int y = rand() % 14 + 12;
        if(player.stage_4[x][y]!='.'){
            continue;
        }
        player.stage_4[x][y]='%';
    }
    for (int i = 0 ; i < q7 ;i++){
        int x = rand() % 3 + 29;
        int y = rand() % 14 + 12;
        int p = rand()%3;
        if (player.stage_4[x][y] != '.') {
            continue;
        }
        if (p == 0) {
            player.stage_4[x][y]='S';
        } else if (p == 1) {
            player.stage_4[x][y]='H';
        } else if (p == 2) {
            player.stage_4[x][y]='8';
        }
    }

    //Room 8

    int m8 = rand() % 2 + 1 ;
    int t8 = rand() % 3 + 3 ;
    int q8 = rand() % 5 + 5 ;
    int n8 = rand() % 3 + 3 ;

    player.stage_4[33][55] = 'o';
    player.stage_4[34][56] = 'o';

    for (int i = 30; i < 42; i++) {
        player.stage_4[i][45] = '|';
        player.stage_4[i][60] = '|';
    }
    for (int i = 45; i <= 60; i++) {
        player.stage_4[30][i] = '-';
        player.stage_4[41][i] = '-';
    }
    for (int i = 31; i < 41; i++) {
        for (int j = 46; j < 60; j++) {
            player.stage_4[i][j] = '.';
        }
    }
    for (int i = 0 ; i < m8 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 46;
        if (player.stage_4[x][y] != '.') {
            continue;
        }
        player.stage_4[x][y]='Z';
    }
    for (int i = 0 ; i < t8 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 46;
        if (player.stage_4[x][y] != '.') {
            continue;
        }
        player.stage_4[x][y]='T';
    }
    for (int i = 0 ; i < n8 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 46;
        if (player.stage_4[x][y] != '.') {
            continue;
        }
        player.stage_4[x][y]='%';
    }
    for (int i = 0 ; i < q8 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 46;
        int p = rand()%3;
        if (player.stage_4[x][y] != '.') {
            continue;
        }
        if (p == 0) {
            player.stage_4[x][y]='S';
        } else if (p == 1) {
            player.stage_4[x][y]='H';
        } else if (p == 2) {
            player.stage_4[x][y]='8';
        }
    }

    generate_corridor(34, 12, 18, 7,player.stage_4);
    generate_corridor(119, 7, 48, 9,player.stage_4);
    generate_corridor(167, 29, 126, 13,player.stage_4);
    generate_corridor(111, 34, 160, 39,player.stage_4);
    generate_corridor(61, 17, 94, 32,player.stage_4);
    generate_corridor(20, 27, 50, 21,player.stage_4);
    generate_corridor(44, 37, 23, 33,player.stage_4);
}


int get_input(Character *character) {
    if (player.health <= 0) {
        clear();
        mvprintw(17, 80,"YOU LOST");
        mvprintw(18, 80,"PRESS ANY KEY TO RETURN TO MAIN MENU");
        getch();
        main_menu();
    }
    if (player.level == 1) {
        int index = getch();
        if((index == '1') || (index == '2') || (index == '3') || (index == '4') || (index == '6') || (index == '7') || (index == '8') || (index == '9')) {
            if (spell_h == 1) {
                spell_hc++;
            }
            if ((spell_s == 1) && (spell_sc <= 10)) {
                pace = 2;
                spell_sc++;
            }
            if (spell_g == 1) {
                spell_gc++;
            }
            pace_count_1++;
            if (player.difficulty == 0) {
                player.health -= 5;
            } else if (player.difficulty == 1) {
                player.health -= 10;
            } else if (player.difficulty == 2) {
                player.health -= 20;
            }
            
        }
        int new_x = character->x, new_y = character->y;
        if ((index == 's') && (pace_count_2<5)) {
            pace = 2;
            pace_count_1 = 0;
            pace_count_2++;
        }
        if ((pace_count_1 >= 5) && (spell_sc >= 10)) {
            pace = 1;
        }
        switch (index) {
        case '1': 
            new_x -= pace;
            new_y += pace;
            break;
        case '2': 
            new_y += pace;
            break;
        case '3': 
            new_x += pace;
            new_y += pace;
            break;
        case '4': 
            new_x -= pace;
            break;
        case '6':
            new_x += pace;
            break;
        case '7':
            new_x -= pace;
            new_y -= pace;
            break;
        case '8':
            new_y -= pace;
            break;
        case '9':
            new_x += pace;
            new_y -= pace;
            break;
        case 'e':
            foods();
            refresh_map(character, stage_1_c, player.stage_1);
            break;
        case 'q':
            main_menu();
        case 'm':
            m_count++;
            if (m_count >= 4) {
                clear();
                attron(COLOR_PAIR(2));
                mvprintw(22, 80, "YOU LOST");
                getch();
                endwin();
                exit(0);
            }
            show_map_temporarily(character);
            break;
        case 'p': spells();
            refresh_map(character,stage_1_c,player.stage_1);
            break;
        }

        if (movement_validate(new_x, new_y,player.stage_1) && (player.stage_1[new_y][new_x]!='<')) {
            clear_character(character);

            character->previous_char = player.stage_1[new_y][new_x];  
            character->x = new_x;
            character->y = new_y;
            if ((new_x == 110) && (new_y == 14)) {
                player.stage_1[14][111]='+';
            } else if ((new_x == 95) && (new_y == 32)) {
                player.stage_1[32][94]='+'; 
            } else if (player.stage_1[new_y][new_x]=='&') {
                char *code = generate_code();
                show_code(code);
                char *entered_code = enter_code();
                if (check_code(entered_code, code)) {
                    player.stage_1[28][158] = '.';
                    player.stage_1[25][150] = 'G';
                }
            } else if ((player.stage_1[new_y][new_x]=='%') || (player.stage_1[new_y][new_x]=='X')) {
                if (message(5,40) == '\n') { 
                    food_manager(player.stage_1[new_y][new_x]);
                    if (food_f == 0) {
                        player.stage_1[new_y][new_x]='.';
                    }   
                }
            } else if ((player.stage_1[new_y][new_x]=='T') || (player.stage_1[new_y][new_x]=='Z')) {
                golds(player.stage_1[new_y][new_x]);
                player.stage_1[new_y][new_x]='.';
            } else if (player.stage_1[new_y][new_x] == '^') {
                player.health-=10;
            } else if ((player.stage_1[new_y][new_x] == 'H') || (player.stage_1[new_y][new_x]=='S') || (player.stage_1[new_y][new_x]=='8')) {
                if (message(5,40) == '\n') {
                    validate_spell(player.stage_1[new_y][new_x]);
                    if (spell_f == 0) {
                        player.stage_1[new_y][new_x]='.';
                    } 
                }
            }

            refresh_map(character,stage_1_c,player.stage_1);  
        } else if (player.stage_1[new_y][new_x] == '<') {
            start_level2();
        }       
    } else if (player.level == 2) {
        int index = getch();
        int new_x = character->x, new_y = character->y;
        if ((index == '1') || (index == '2') || (index == '3') || (index == '4') || (index == '6') || (index == '7') || (index == '8') || (index == '9')) {
            if (spell_h == 1) {
                spell_hc++;
            }
            if ((spell_s == 1) && (spell_sc <= 10)) {
                pace = 2;
                spell_sc++;
            }
            if (spell_g == 1) {
                spell_gc++;
            }
            if (player.difficulty == 0) {
                player.health -= 5;
            }
            if (player.difficulty == 1) {
                player.health -= 10;
            }
            if (player.difficulty == 2) {
                player.health-=20;
            }
            pace_count_1++;
        }
        if ((index == 's') && (pace_count_2 < 5)) {
            pace=2;
            pace_count_1=0;
            pace_count_2++;
        }
        if ((pace_count_1 >= 5) && (spell_sc >= 10)){
            pace = 1;
        }
        switch (index) {
        case '1':
            new_x -= pace;
            new_y += pace;
            break;
        case '2':
            new_y += pace;
            break;
        case '3':
            new_x += pace;
            new_y += pace;
            break;
        case '4': 
            new_x -= pace;
            break;
        case '6':
            new_x += pace;
            break;
        case '7':
            new_x -= pace;
            new_y -= pace;
            break;
        case '8':
            new_y -= pace;
            break;
        case '9':
            new_x += pace;
            new_y -= pace;
            break;
            case 'e':
                foods();
                refresh_map(character,stage_2_c,player.stage_2);
                break;
            case 'q':
                main_menu();
            case 'm':        
                m_count++;
                if (m_count >= 4) {
                    clear();
                    attron(COLOR_PAIR(2));
                    mvprintw(22,82,"YOU LOST");
                    getch();
                    endwin();
                    exit(0);
                }
                show_map_temporarily(character);
                break;
            case 'p':
                spells();
                refresh_map(character, stage_2_c, player.stage_2);
                break;
        }

        if (movement_validate(new_x, new_y,player.stage_2) && (player.stage_2[new_y][new_x] != '<')) {
            clear_character(character);

            character->previous_char = player.stage_2[new_y][new_x];  
            character->x = new_x;
            character->y = new_y;
            if ((new_x == 17) && (new_y == 7)) {
                player.stage_2[7][18]='+';
            } else if ((new_x == 128) && (new_y == 11)) {
                player.stage_2[12][128]='+';
            } else if ((new_x == 51) && (new_y == 21)) {
                player.stage_2[21][50]='+';
            } else if ((player.stage_2[new_y][new_x] == '&') && (room_number(new_x,new_y) == 2)) {
                char *code = generate_code();
                show_code(code);
                char *entered_code = enter_code();
                if (check_code(entered_code, code)) {
                    player.stage_2[6][36] = '.';
                    player.stage_2[9][48] = 'G';
                }
            } else if ((player.stage_2[new_y][new_x] == '&') && (room_number(new_x,new_y) == 5)) {
                char *code = generate_code();
                show_code(code);
                char *entered_code = enter_code();
                if (check_code(entered_code, code)) {
                    player.stage_2[33][108] = '.';
                    player.stage_2[32][94] = 'G';
                }
            } else if ((player.stage_2[new_y][new_x]=='%') || (player.stage_2[new_y][new_x]=='X')) {
                if (message(5,40) == '\n') {
                    food_manager(player.stage_2[new_y][new_x]);
                    if (food_f == 0) {
                        player.stage_2[new_y][new_x]='.';
                    }
                }
            } else if ((player.stage_2[new_y][new_x]=='T') || (player.stage_2[new_y][new_x]=='Z')) {
                golds(player.stage_2[new_y][new_x]);
                player.stage_2[new_y][new_x]='.';
            } else if (player.stage_2[new_y][new_x] == '^') {
                player.health-=10;
            } else if ((player.stage_2[new_y][new_x] == 'H') || (player.stage_2[new_y][new_x] == 'S') || (player.stage_2[new_y][new_x] == '8')) {
                if (message(5,40) == '\n') {
                    validate_spell(player.stage_2[new_y][new_x]);
                    if (spell_f == 0) {
                        player.stage_2[new_y][new_x]='.';
                    } 
                }
            }
            refresh_map(character,stage_2_c,player.stage_2);
        } else if (player.stage_2[new_y][new_x] == '<') {
            start_level3();
        }
    } else if (player.level == 3) {
        int index = getch();
        int new_x = character->x, new_y = character->y;
        if ((index == '1') || (index == '2') || (index == '3') || (index == '4') || (index == '6') || (index == '7') || (index == '8') || (index == '9')) {
            if (spell_h == 1) {
                spell_hc++;
            }
            if ((spell_s==1) && (spell_sc <= 10)) {
                pace = 2;
                spell_sc++;
            }
            if (spell_g == 1) {
                spell_gc++;
            }
            pace_count_1++;
            if (player.difficulty == 0) {
                player.health -= 5;
            }
            if (player.difficulty == 1) {
                player.health -= 10;
            }
            if (player.difficulty == 2) {
                player.health -= 20;
            }
        }
        if ((index == 's') && (pace_count_2 < 5)) {
            pace = 2;
            pace_count_1 = 0;
            pace_count_2++;
        }
        if((pace_count_1>=5) && (spell_sc >= 10)) {
            pace = 1;
        }
        switch (index) {
        case '1': new_x -= pace; new_y += pace; break;
        case '2': new_y += pace; break;
        case '3': new_x += pace; new_y += pace; break;
        case '4': new_x -= pace; break;
        case '6': new_x += pace; break;
        case '7': new_x -= pace; new_y -= pace; break;
        case '8': new_y -= pace; break;
        case '9': new_x += pace; new_y -= pace; break;
        case 'e': foods();
            refresh_map(character,stage_3_c,player.stage_3);
            break;
        case 'q':
            main_menu();
        case 'm':            
            m_count++;
            if (m_count >= 4) {
                clear();
                attron(COLOR_PAIR(2));
                mvprintw(22,82,"YOU LOST");
                getch();
                endwin();
                exit(0);
            }
            show_map_temporarily(character);
            break;
            case 'p':
                spells();
                refresh_map(character, stage_3_c, player.stage_3);
                break;
        }
        if (movement_validate(new_x, new_y,player.stage_3)&& player.stage_3[new_y][new_x]!='<') {
            clear_character(character);

            character->previous_char = player.stage_3[new_y][new_x];  
            character->x = new_x;
            character->y = new_y;
            if ((new_x == 167) && (new_y == 31)) {
                player.stage_3[30][167]='+';
            } else if ((new_x == 126) && (new_y == 7)) {
                player.stage_3[7][125]='+';
            } else if ((player.stage_3[new_y][new_x] == '&') && (room_number(new_x,new_y) == 5)) {
                char *code = generate_code();
                show_code(code);
                char *entered_code = enter_code();
                if (check_code(entered_code, code)) {
                    player.stage_3[34][87] = '.';
                    player.stage_3[34][100] = 'G';
                }
            }
            else if(player.stage_3[new_y][new_x]=='&' && room_number(new_x,new_y)==2){
                char *code = generate_code();
                show_code(code);
                char *entered_code = enter_code();
                if (check_code(entered_code, code)) {
                    player.stage_3[15][72] = '.';
                    player.stage_3[13][70] = 'G';
                }
            } else if ((player.stage_3[new_y][new_x]=='%') || (player.stage_3[new_y][new_x] == 'X')) {
                if (message(5,40) == '\n') {
                    food_manager(player.stage_3[new_y][new_x]);
                    if (food_f == 0) {
                        player.stage_3[new_y][new_x]='.';
                    }
                }
            } else if ((player.stage_3[new_y][new_x] == 'T') || (player.stage_3[new_y][new_x] == 'Z')) {
                golds(player.stage_3[new_y][new_x]);
                player.stage_3[new_y][new_x]='.';
            } else if (player.stage_3[new_y][new_x] == '^') {
                player.health -= 10;
            } else if ((player.stage_3[new_y][new_x] == 'H') || (player.stage_3[new_y][new_x] == 'S') || (player.stage_3[new_y][new_x] == '8')) {
                if (message(5,40) == '\n') {
                    validate_spell(player.stage_3[new_y][new_x]);
                    if (spell_f == 0) {
                        player.stage_3[new_y][new_x]='.';
                    } 
                }
            }
            refresh_map(character,stage_3_c,player.stage_3);  
        } else if (player.stage_3[new_y][new_x] == '<') {
            start_level4();
        }
    } else if (player.level == 4) {
        int index = getch();
        int new_x = character->x, new_y = character->y;
        if ((index == '1') || (index == '2') || (index == '3') || (index == '4') || (index == '6') || (index == '7') || (index == '8') || (index == '9')) {
            pace_count_1++;
            if (spell_h == 1) {
                spell_hc++;
            }
            if ((spell_s == 1) && (spell_sc <= 10)) {
                pace = 2;
                spell_sc++;
            }
            if (spell_g == 1) {
                spell_gc++;
            }
            if (player.difficulty == 0) {
                player.health-=5;
            }
            if (player.difficulty == 1) {
                player.health-=10;
            }
            if (player.difficulty == 2) {
                player.health-=20;
            }
        }
        if ((index == 's') && (pace_count_2 < 5)) {
            pace = 2;
            pace_count_1 = 0;
            pace_count_2++;
        }
        if ((pace_count_1 >= 5) && (spell_sc >= 10)) {
            pace = 1;
        }
        switch (index) {
        case '1':
            new_x -= pace;
            new_y += pace;
            break;
        case '2':
            new_y += pace;
            break;
        case '3':
            new_x += pace;
            new_y += pace;
            break;
        case '4':
            new_x -= pace;
            break;
        case '6':
            new_x += pace;
            break;
        case '7':
            new_x -= pace;
            new_y -= pace;
            break;
        case '8':
            new_y -= pace;
            break;
        case '9':
            new_x += pace;
            new_y -= pace;
            break;
        case 'e':
            foods();
            refresh_map(character,stage_4_c,player.stage_4);
            break;
        case 'q':
            main_menu();
        case 'm':
            m_count++;
            if (m_count >= 4) {
                clear();
                attron(COLOR_PAIR(2));
                mvprintw(22,82,"YOU LOST");
                getch();
                endwin();
                exit(0);
            }
            show_map_temporarily(character);
            break;
            case 'p':
                spells();
                refresh_map(character,stage_4_c,player.stage_4);
                break;
        }
        if (movement_validate(new_x, new_y,player.stage_4)) {
            clear_character(character);
            character->previous_char = player.stage_4[new_y][new_x];  
            character->x = new_x;
            character->y = new_y;
            if ((new_x == 109) && (new_y == 34)) {
                player.stage_4[34][110]='+';
            } else if ((new_x == 121) && (new_y == 7)) {
                player.stage_4[7][120]='+';
            } else if ((new_x == 46) && (new_y == 37)) {
                player.stage_4[37][45]='+';
            } else if ((player.stage_4[new_y][new_x] == '&') && (room_number(new_x,new_y)==6)){
                char *code = generate_code();
                show_code(code);
                char *entered_code = enter_code();
                if (check_code(entered_code, code)) {
                    player.stage_4[16][52] = '.';
                    player.stage_4[17][60] = 'G';
                }
            } else if ((player.stage_4[new_y][new_x] == '&') && (room_number(new_x,new_y) == 4)) {
                char *code = generate_code();
                show_code(code);
                char *entered_code = enter_code();
                if (check_code(entered_code, code)) {
                    player.stage_4[40][174] = '.';
                    player.stage_4[30][167] = 'G';
                }
            } else if ((player.stage_4[new_y][new_x] == '&') && (room_number(new_x,new_y) == 2)) {
                char *code = generate_code();
                show_code(code);
                char *entered_code = enter_code();
                if (check_code(entered_code, code)) {
                    player.stage_4[6][37] = '.';
                    player.stage_4[12][35] = 'G';
                }
            } else if ((player.stage_4[new_y][new_x] == '%') || (player.stage_4[new_y][new_x] == 'X')) {
                if(message(5,40)=='\n'){
                    food_manager(player.stage_4[new_y][new_x]);
                    if (food_f == 0) {
                        player.stage_4[new_y][new_x]='.';
                    } 
                }           
            } else if ((player.stage_4[new_y][new_x] == 'T') || (player.stage_4[new_y][new_x] == 'Z')) {
                golds(player.stage_4[new_y][new_x]);
                player.stage_4[new_y][new_x]='.';
            } else if (player.stage_4[new_y][new_x] == '^') {
                player.health-=10;
            } else if ((player.stage_4[new_y][new_x] == 'H') || (player.stage_4[new_y][new_x] == 'S') || (player.stage_4[new_y][new_x] == '8')) {
                if (message(5,40) == '\n') {
                    validate_spell(player.stage_4[new_y][new_x]);
                    if (spell_f == 0) {
                        player.stage_4[new_y][new_x]='.';
                    } 
                }
            }
            refresh_map(character,stage_4_c,player.stage_4);  
        }
    }
}









void play_as_guest(){
    clear();
    player.level = 1;
    player.gold = 0;
    player.health = 10000;
    player.power = 100;
    player.difficulty = 1;
    player.food_bar.normal = 0;
    player.food_bar.special = 0;
    player.spell_bar.H = 0;
    player.spell_bar.S = 0;
    player.spell_bar.G = 0;
    memset(stage_1_c,0,sizeof(stage_1_c));
    create_map_1();  
    Character Char = {5, 4, '.'};
    refresh_map(&Char,stage_1_c,player.stage_1);  

    while (1) {
        get_input(&Char);
    }
}







void profile_status(){
    attron(COLOR_PAIR(4));
    mvprintw(5, 40,"Name: %s", player.username);
    mvprintw(6, 40,"Password: %s", player.password);
    mvprintw(7, 40,"Email: %s", player.email);
    mvprintw(8, 40,"Score: %d", player.score);
    mvprintw(9, 40,"Gold: %d", player.gold);
    mvprintw(10, 40,"Game-played: %d", player.games_played);
    attroff(COLOR_PAIR(4));

    while(1) {
        int index = getch();
        if(index=='\n'){
            return;
        }
    }
}

void rankings() {
    clear;
    mwprintw(1, 90, "Rankings:");
    FILE *file = fopen(FILE_OF_USERNAMES, "r");

    if (!file) {
        mvprintf(3, 90, "Server does not respond!");
        getch();
        return;
    }

    int user_count;
    User users[100];

    while (fscanf(file, "%s~%s~%s~%d~%d~%d~%d~%d", users[user_count].username, users[user_count].password, users[user_count].email, &users[user_count].score, &users[user_count].gold, &users[user_count].games_played, &users[user_count].character_color, &users[user_count].difficulty) != EOF) {
        user_count++;
    }
    fclose(file);

    for (int i = 0; i < user_count - 1; i++) {
        for (int j = 0; j < user_count - i - 1; j++) {
            if (users[j].score < users[j + 1].score) {
                User temp = users[j];
                users[j] = users[j + 1];
                users[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < user_count; i++) {
        if(!strcmp(users[i].username, player.username)){
            attron(COLOR_PAIR(2));
        } if (i == 0) {
            attron(A_BOLD);
            mvprintw(5 + i, 40, "%d. %s - Score: %d gold %d: game-played: %d(THE GOAT)", i + 1, users[i].username, users[i].score, users[i].gold, users[i].games_played);
            attroff(A_BOLD);
        } else if (i == 1) {
            attron(A_BOLD);
            mvprintw(5 + i, 40, "%d. %s - Score: %d gold %d: game-played: %d(ALMOST GOAT)", i + 1, users[i].username, users[i].score, users[i].gold, users[i].games_played);
            attroff(A_BOLD);
        } else if(i == 2) {
            attron(A_BOLD);
            mvprintw(5 + i, 40, "%d. %s - Score: %d gold %d: game-played: %d(SEMI GOAT)", i + 1, users[i].username, users[i].score, users[i].gold, users[i].games_played);
            attroff(A_BOLD);
        } else {
            mvprintw(5 + i, 40, "%d. %s - Score: %d gold %d: game-played: %d", i + 1, users[i].username, users[i].score, users[i].gold, users[i].games_played);
        }
        if(!strcmp(users[i].username, player.username)){
            attroff(COLOR_PAIR(2));
        }
    }

    while(1) {
        int index = getch();
        if(index=='\n'){
            return;
        }
    }
}


void character_color(int appearance) {
    initscr();
    start_color();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    int width, height, starter_height, starter_width;
    
    getmaxyx(stdscr, height, width);

    const char *option[] = {"White", "Blue", "Green", "Red", "Yello", "Purple", "Back"};
    int number_of_options = sizeof(option) / sizeof(option[0]);

    int current_option = 0;

    box(stdscr, 0, 0);
    starter_height = (height/2) - (number_of_options/2);
    starter_width = (width/2) - 4;

    while(1) {
        clear();
        box(stdscr, 0, 0);
        for(int i = 0; i < number_of_options; i++) {
            if (i == current_option) {
                attron(A_REVERSE);
                mvprintw(starter_height + i, starter_width, "%s", option[i]);
                attroff(A_REVERSE);
            } else {
                mvprintw(starter_height + i, starter_width, "%s", option[i]);
            }

            if (player.character_color == i) {
                mvprintw(starter_height + i, starter_width + strlen(option[player.character_color]), "  (selected)");
            }
        }

        int input;
        input = getch();

        switch(input) {
            case(KEY_UP) :
                if (current_option == 0) {
                    current_option = (number_of_options - 1);
                } else {
                    current_option -= 1;
                }
                break;
            
            case(KEY_DOWN) :
                if (current_option == (number_of_options - 1)) {
                    current_option = 0;
                } else {
                    current_option += 1;
                }
                break;
            
            case (10) :
                if (current_option == 0) {
                    player.character_color = 0;
                } else if (current_option == 1) {
                    player.character_color = 1;
                } else if (current_option == 2) {
                    player.character_color = 2;
                } else if (current_option == 3) {
                    player.character_color = 3;
                } else if (current_option == 4) {
                    player.character_color = 4;
                } else if (current_option == 5) {
                    player.character_color = 5;
                } else if (current_option == (number_of_options - 1)) {
                    start_menu(appearance);
                }
        }
    }
}


void difficulty(int appearance) {
    initscr();
    start_color();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    int width, height, starter_height, starter_width;
    
    getmaxyx(stdscr, height, width);

    const char *option[] = {"Easy", "Medium", "Hard", "Back"};
    int number_of_options = sizeof(option) / sizeof(option[0]);

    int current_option = 0;

    box(stdscr, 0, 0);
    starter_height = (height/2) - (number_of_options/2);
    starter_width = (width/2) - 4;

    while(1) {
        clear();
        box(stdscr, 0, 0);
        for(int i = 0; i < number_of_options; i++) {
            if (i == current_option) {
                attron(A_REVERSE);
                mvprintw(starter_height + i, starter_width, "%s", option[i]);
                attroff(A_REVERSE);
            } else {
                mvprintw(starter_height + i, starter_width, "%s", option[i]);
            }

            if (player.difficulty == i) {
                mvprintw(starter_height + i, starter_width + strlen(option[player.difficulty]), "  (selected)");
            }
        }

        int input;
        input = getch();

        switch(input) {
            case(KEY_UP) :
                if (current_option == 0) {
                    current_option = (number_of_options - 1);
                } else {
                    current_option -= 1;
                }
                break;
            
            case(KEY_DOWN) :
                if (current_option == (number_of_options - 1)) {
                    current_option = 0;
                } else {
                    current_option += 1;
                }
                break;
            
            case (10) :
                if (current_option == 0) {
                    player.difficulty = 0;
                } else if (current_option == 1) {
                    player.difficulty = 1;
                } else if (current_option == 2) {
                    player.difficulty = 2;
                } else if (current_option == (number_of_options - 1)) {
                    start_menu(appearance);
                }
        }
    }
}


void settings(int appearance) {
    initscr();
    start_color();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    int width, height, starter_height, starter_width;
    
    getmaxyx(stdscr, height, width);

    const char *option[] = {"Change character color", "Change game difficulty", "Back"};
    int number_of_options = sizeof(option) / sizeof(option[0]);

    int current_option = 0;

    box(stdscr, 0, 0);
    starter_height = (height/2) - (number_of_options/2);
    starter_width = (width/2) - 4;

    while(1) {
        clear();
        box(stdscr, 0, 0);
        for(int i = 0; i < number_of_options; i++) {
            if (i == current_option) {
                attron(A_REVERSE);
                mvprintw(starter_height + i, starter_width, "%s", option[i]);
                attroff(A_REVERSE);
            } else {
                mvprintw(starter_height + i, starter_width, "%s", option[i]);
            }
        }

        int input;
        input = getch();

        switch(input) {
            case(KEY_UP) :
                if (current_option == 0) {
                    current_option = (number_of_options - 1);
                } else {
                    current_option -= 1;
                }
                break;
            
            case(KEY_DOWN) :
                if (current_option == (number_of_options - 1)) {
                    current_option = 0;
                } else {
                    current_option += 1;
                }
                break;
            
            case (10) :
                if (current_option == 0) {
                    character_color(appearance);
                } else if (current_option == 1) {
                    difficulty(appearance);
                } else if (current_option == (number_of_options - 1)) {
                    start_menu(appearance);
                }
        }
    }

}


void start_menu(int appearance) {
    initscr();
    start_color();
    init_color(3, 700,700,700);
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    int width, height, starter_height, starter_width;
    
    getmaxyx(stdscr, height, width);

    const char *option[] = {"Load game", "Start a new game", "Profile status", "Rankings", "Settings"};
    int number_of_options = sizeof(option) / sizeof(option[0]);

    int current_option = 0;

    box(stdscr, 0, 0);
    starter_height = (height/2) - (number_of_options/2);
    starter_width = (width/2) - 4;

    if (appearance == 0) {
        while(1) {
            clear();
            box(stdscr, 0, 0);
            for(int i = 0; i < number_of_options; i++) {
                if (i == current_option) {
                    attron(A_REVERSE);
                    mvprintw(starter_height + i, starter_width, "%s", option[i]);
                    attroff(A_REVERSE);
                } else {
                    mvprintw(starter_height + i, starter_width, "%s", option[i]);
                }
            }

            int input;
            input = getch();

            switch(input) {
                case(KEY_UP) :
                    if (current_option == 0) {
                        current_option = (number_of_options - 1);
                    } else {
                        current_option -= 1;
                    }
                    break;

                case(KEY_DOWN) :
                    if (current_option == (number_of_options - 1)) {
                        current_option = 0;
                    } else {
                        current_option += 1;
                    }
                    break;

                case (10) :
                    if (current_option == 0) {
                        // load_game();
                    } else if (current_option == 1) {
                        start_new_game();
                    } else if (current_option == 2) {
                        profile_status();
                    } else if (current_option == 3) {
                        rankings();
                    } else if (current_option == (number_of_options - 1)) {
                        settings(appearance);
                    }
            }
        }
    } else if (appearance == 1) {
        while(1) {
            clear();
            box(stdscr, 0, 0);
            init_pair(2, 8, COLOR_BLACK);

            attron(COLOR_PAIR(2));
            mvprintw(starter_height, starter_width, "%s", option[0]);
            attroff(COLOR_PAIR(2));

            for(int i = 1; i < number_of_options; i++) {
                if (i == current_option) {
                    attron(A_REVERSE);
                    mvprintw(starter_height + i, starter_width, "%s", option[i]);
                    attroff(A_REVERSE);
                } else {
                    mvprintw(starter_height + i, starter_width, "%s", option[i]);
                }
            }

            int input;
            input = getch();

            switch(input) {
                case(KEY_UP) :
                    if (current_option == 1) {
                        current_option = (number_of_options - 1);
                    } else {
                        current_option -= 1;
                    }
                    break;

                case(KEY_DOWN) :
                    if (current_option == (number_of_options - 1)) {
                        current_option = 1;
                    } else {
                        current_option += 1;
                    }
                    break;

                case (10) :
                    if (current_option == 0) {
                        // load_game();
                    } else if (current_option == 1) {
                        start_new_game();
                    } else if (current_option == 2) {
                        profile_status();
                    } else if (current_option == 3) {
                        rankings();
                    } else if (current_option == (number_of_options - 1)) {
                        settings(appearance);
                    }
            }
        }
    }  else if (appearance == 2) {
        while(1) {
            clear();
            box(stdscr, 0, 0);
            init_pair(2, 8, COLOR_BLACK);

            attron(COLOR_PAIR(2));
            mvprintw(starter_height, starter_width, "%s", option[0]);
            attroff(COLOR_PAIR(2));

            for(int i = 1; i < number_of_options; i++) {
                if (i == current_option) {
                    attron(A_REVERSE);
                    mvprintw(starter_height + i, starter_width, "%s", option[i]);
                    attroff(A_REVERSE);
                } else if (i == 2) {
                    attron(COLOR_PAIR(2));
                    mvprintw(starter_height + i, starter_width, "%s", option[i]);
                    attroff(COLOR_PAIR(2));
                } else {
                    mvprintw(starter_height + i, starter_width, "%s", option[i]);
                }
            }

            int input;
            input = getch();

            switch(input) {
                case(KEY_UP) :
                    if (current_option == 1) {
                        current_option = (number_of_options - 1);
                    } else if (current_option == 3) {
                        current_option -= 2; 
                    } else {
                        current_option -= 1;
                    }
                    break;

                case(KEY_DOWN) :
                    if (current_option == (number_of_options - 1)) {
                        current_option = 1;
                    } else if (current_option == 1) {
                        current_option += 2; 
                    }  else {
                        current_option += 1;
                    }
                    break;

                case (10) :
                    if (current_option == 0) {
                        // load_game();
                    } else if (current_option == 1) {
                        play_as_guest();
                    } else if (current_option == 2) {
                        // profile_status();
                    } else if (current_option == 3) {
                        rankings();
                    } else if (current_option == (number_of_options - 1)) {
                        settings(appearance);
                    }
            }
        }
    }
}




void log_in() {
    FILE *users_file;
    char information[200];
    char *temp, *file_username, *file_password;
    users_file = fopen(FILE_OF_USERNAMES, "r");
    

    clear();
    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    cbreak();
    echo();
    keypad(stdscr, TRUE);
    curs_set(1);

    int width, height, starter_height, starter_width;

    getmaxyx(stdscr, height, width);

    const char *input_options[] = {"Username : ", "Password : "};
    int number_of_inputs = sizeof(input_options) / sizeof(input_options[0]);

    char username[50], password[50];

    box(stdscr, 0, 0);
    starter_height = (height/2) - (number_of_inputs/2);
    starter_width = (width/2) - 10;

    while(1) {
        clear();
        int flag = 0;
        box(stdscr, 0, 0);
        for(int i = 0; i < number_of_inputs; i++) {
            mvprintw(starter_height + i, starter_width, "%s", input_options[i]);
        }
        refresh();
    
        move(starter_height + 0 ,starter_width + strlen(input_options[0]));
        getnstr(username, 50);
                
        move(starter_height + 1 ,starter_width + strlen(input_options[1]));
        getnstr(password, 50);

        int result = validate_user(username, password);

        switch (result) {
            case 0:
                break;
            case 1:
                attron(COLOR_PAIR(1));
                mvprintw(starter_height + 10, starter_width, "INCORRECT PASSWORD!"); 
                attroff(COLOR_PAIR(1));
                flag = 1;
                refresh();
                napms(6000);
                break;
            case 2:
                attron(COLOR_PAIR(1));
                mvprintw(starter_height + 10, starter_width, "USERNAME NOT FOUND!"); 
                attroff(COLOR_PAIR(1));
                flag = 1;
                refresh();
                napms(6000);
                break;
        }

        if (flag == 1) {
            continue;
        }

        break;
    }

    strcpy(player.username, username);
    strcpy(player.password, password);
    clear();
    box(stdscr, 0, 0);
    mvprintw(starter_height, starter_width + 5, "Logged in!");
    refresh();
    napms(2000);
    
    start_menu(0);
}


void sign_up() {
    User new_user;
    FILE *users_file;
    users_file = fopen(FILE_OF_USERNAMES, "a");    

    clear();
    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    cbreak();
    echo();
    keypad(stdscr, TRUE);
    curs_set(1);

    int width, height, starter_height, starter_width;

    getmaxyx(stdscr, height, width);

    const char *input_options[] = {"Username : ", "Email : ", "Password : ", "Confirm : "};
    int number_of_inputs = sizeof(input_options) / sizeof(input_options[0]);

    // int current_input = 0;
    char username[50], email[100], password[50], confirm[50];


    box(stdscr, 0, 0);
    starter_height = (height/2) - (number_of_inputs/2);
    starter_width = (width/2) - 10;

    while(1) {
        clear();
        box(stdscr, 0, 0);

        for(int i = 0; i < number_of_inputs; i++) {
            mvprintw(starter_height + i, starter_width, "%s", input_options[i]);
        }
        refresh();
    
        move(starter_height + 0 ,starter_width + strlen(input_options[0]));
        getnstr(username, 50);
        
        move(starter_height + 1 ,starter_width + strlen(input_options[1]));
        getnstr(email, 100);
        
        move(starter_height + 2 ,starter_width + strlen(input_options[2]));
        getnstr(password, 50);
        
        move(starter_height + 3 ,starter_width + strlen(input_options[3]));
        getnstr(confirm, 50);

        if(username_existance(username)) {
            mvprintw(starter_height + 10, starter_width, "USERNAME ALREADY EXSISTS.");
            refresh();
            napms(6000);
            continue;
        }

        // to validate email
        char *atsign = strchr(email, '@');
        char *dot = strrchr(email, '.');

        if((!(atsign)) || (!(dot)) || (!(dot > atsign))) {
            attron(COLOR_PAIR(1));
            mvprintw(starter_height + 10, starter_width, "INVALID EMAIL.");
            refresh();
            napms(6000);
            attroff(COLOR_PAIR(1));
            continue;
        }

        int uppercase = 0, lowercase = 0, number = 0; 

        for(int i = 0; i < strlen(password); i++) {
            if((password[i] >= 'A') && (password[i] <= 'Z')) uppercase += 1;
            else if ((password[i] >= 'a') && (password[i] <= 'z')) lowercase += 1;
            else if ((password[i] >= '0') && (password[i] <= '9')) number += 1;
        }

        if((!uppercase) || (!lowercase) || (!number) || (!(strlen(password) > 7))) {
            attron(COLOR_PAIR(1));
            mvprintw(starter_height + 10, starter_width, "PASSWORD MUST BE AT LEAST 8 CHARACTERS,");
            mvprintw(starter_height + 11, starter_width, "CONTAIN AN UPPERCASE,");
            mvprintw(starter_height + 12, starter_width, "A LOWERCASE,");
            mvprintw(starter_height + 13, starter_width, "AND A NUMBER.");
            refresh();
            napms(6000);
            attroff(COLOR_PAIR(1));
            continue;
        }

        if ((strcmp(password, confirm))) {
            attron(COLOR_PAIR(1));
            mvprintw(starter_height + 10, starter_width, "PASSWORD DO NOT MATCH.");
            refresh();
            napms(6000);
            attroff(COLOR_PAIR(1));
            continue;
        }  

        break;
    }

    strcpy(new_user.username, username);
    strcpy(new_user.password, password);
    strcpy(new_user.email, email);
    new_user.score = 0;
    new_user.games_played = 0;
    new_user.gold = 0;
    new_user.character_color = 0;
    new_user.difficulty = 0;

    fprintf(users_file, "%s~%s~%s~%d~%d~%d~%d~%d\n", new_user.username, new_user.password, new_user.email, new_user.score, new_user.gold, new_user.games_played, new_user.character_color, new_user.difficulty);
    fclose(users_file);

    strcpy(player.username, username);
    strcpy(player.password, password);

    clear();
    box(stdscr, 0, 0);
    mvprintw(starter_height, starter_width + 5, "Signed up!");
    refresh();
    napms(2000);

    start_menu(1);
}


void user_menu() {
    initscr();
    start_color();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    int width, height, starter_height, starter_width;
    
    getmaxyx(stdscr, height, width);

    const char *option[] = {"Log in", "Guest", "Sign up", "Exit"};
    int number_of_options = sizeof(option) / sizeof(option[0]);

    int current_option = 0;

    box(stdscr, 0, 0);
    starter_height = (height/2) - (number_of_options/2);
    starter_width = (width/2) - 4;

    while(1) {
        clear();
        box(stdscr, 0, 0);
        for(int i = 0; i < number_of_options; i++) {
            if (i == current_option) {
                attron(A_REVERSE);
                mvprintw(starter_height + i, starter_width, "%s", option[i]);
                attroff(A_REVERSE);
            } else {
                mvprintw(starter_height + i, starter_width, "%s", option[i]);
            }
        }

        int input;
        input = getch();

        switch(input) {
            case(KEY_UP) :
                if (current_option == 0) {
                    current_option = (number_of_options - 1);
                } else {
                    current_option -= 1;
                }
                break;
            
            case(KEY_DOWN) :
                if (current_option == (number_of_options - 1)) {
                    current_option = 0;
                } else {
                    current_option += 1;
                }
                break;
            
            case (10) :
                if (current_option == 0) {
                    log_in();
                } else if (current_option == 1) {
                    start_menu(2);
                } else if (current_option == 2) {
                    sign_up();
                } else if (current_option == (number_of_options - 1)) {
                    endwin();
                    return;
                }
        }
    }
}

int username_existance(char *username) {
    FILE *users_file;
    char information[200];
    char *temp, *file_username;

    users_file = fopen(FILE_OF_USERNAMES, "r");

    while (fgets(information, sizeof(information), users_file)) {
        information[strcspn(information, "\n")] = '\0';
        temp = strtok(information, "~");
        file_username = temp;

        if (strcmp(username, file_username) == 0) {
            fclose(users_file);
            return 1;
        }
    }

    fclose(users_file);
    return 0;
}

int validate_user(char *username, char *password) {
    FILE *users_file;
    char information[200];
    char *temp, *file_username, *file_password;

    users_file = fopen(FILE_OF_USERNAMES, "r");

    while (fgets(information, sizeof(information), users_file)) {
        information[strcspn(information, "\n")] = '\0';
        temp = strtok(information, "~");
        file_username = temp;
        temp = strtok(NULL, "~");
        file_password = temp;

        if (strcmp(username, file_username) == 0) {
            if (strcmp(password, file_password) == 0) {
                fclose(users_file);
                return 0;
            } else {
                fclose(users_file);
                return 1;
            }
        }
    }

    fclose(users_file);
    return 2;
}