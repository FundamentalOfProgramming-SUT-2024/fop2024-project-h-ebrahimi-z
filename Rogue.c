# include <stdio.h>
# include <ncurses.h>
# include <string.h>
# include <stdlib.h>

# define FILE_OF_USERNAMES "users.txt"
# define MAX_LENGTH 50


typedef struct {
    int x, y;
} position;

typedef struct {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    char email[2 * MAX_LENGTH];
    int score;
    int games_played;
    int gold;
    int health;
    char weapon;
    char spell;
    int difficulty;
    int character_color;
} user;


user player;


void character_color(int);
void difficulty(int);
void start_menu(int);
int validate_user(char*, char*);
int username_existance(char *);
void sign_up();
void log_in();
void user_menu();





int main() {
    user_menu();
    return(0);
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
                        // start_new_game();
                    } else if (current_option == 2) {
                        // profile_status();
                    } else if (current_option == 3) {
                        // rankings();
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
                        // start_new_game();
                    } else if (current_option == 2) {
                        // profile_status();
                    } else if (current_option == 3) {
                        // rankings();
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
                        // start_new_game();
                    } else if (current_option == 2) {
                        // profile_status();
                    } else if (current_option == 3) {
                        // rankings();
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
    user new_user;
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
    new_user.character_color = 0;
    new_user.difficulty = 0;

    fprintf(users_file, "%s~%s~%s~%d~%d\n", new_user.username, new_user.password, new_user.email, new_user.character_color, new_user.difficulty);
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