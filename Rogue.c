# include <stdio.h>
# include <ncurses.h>

typedef struct {
    int x, y;
} position;

void user_menu();

int main() {
    user_menu();
    return(0);
}



void user_menu() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    int width, height, starter_height, starter_width;
    
    getmaxyx(stdscr, height, width);

    const char *option[] = {"Sign up", "Log in", "Exit"};
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
                    // log_in();
                } else if (current_option == 1) {
                    // sign_up();
                } else if (current_option == (number_of_options - 1)) {
                    endwin();
                    return;
                }

        }
    }
}