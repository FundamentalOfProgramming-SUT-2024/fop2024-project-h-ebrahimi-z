# include <stdio.h>
# include <ncurses.h>
# include <string.h>
# include <stdlib.h>

typedef struct {
    int x, y;
} position;

void sign_up();
void user_menu();

int main() {
    user_menu();
    return(0);
}


void sign_up() {
    clear();
    initscr();
    cbreak();
    echo();
    keypad(stdscr, TRUE);
    curs_set(1);

    int width, height, starter_height, starter_width;

    getmaxyx(stdscr, height, width);

    const char *input_options[] = {"Username : ", "Email : ", "Password : ", "Confirm : "};
    int number_of_inputs = sizeof(input_options) / sizeof(input_options[0]);

    int current_input = 0;
    char username[50], email[100], password[50], confirm[50];


    box(stdscr, 0, 0);
    starter_height = (height/2) - (number_of_inputs/2);
    starter_width = (width/2) - 10;

    box(stdscr, 0, 0);


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


        // if(strchr(username, file_of_usernames)) {
        //     mvprintw(starter_height + 10, starter_width, "USERNAME ALREADY EXSISTS.");
        //     refresh();
        //     napms(6000);
        //     continue;
        // }

        // to validate email
        char *atsign = strchr(email, '@');
        char *dot = strrchr(email, '.');

        if((!(atsign)) || (!(dot)) || (!(dot > atsign))) {
            mvprintw(starter_height + 10, starter_width, "INVALID EMAIL.");
            refresh();
            napms(6000);
            continue;
        }

        int uppercase = 0, lowercase = 0, number = 0; 

        for(int i = 0; i < strlen(password); i++) {
            if((password[i] >= 'A') && (password[i] <= 'Z')) uppercase += 1;
            else if ((password[i] >= 'a') && (password[i] <= 'z')) lowercase += 1;
            else if ((password[i] >= '0') && (password[i] <= '9')) number += 1;
        }

        if((!uppercase) || (!lowercase) || (!number) || (!(strlen(password) > 7))) {
            mvprintw(starter_height + 10, starter_width, "PASSWORD MUST BE AT LEAST 8 CHARACTERS,");
            mvprintw(starter_height + 11, starter_width, "CONTAIN AN UPPERCASE,");
            mvprintw(starter_height + 12, starter_width, "A LOWERCASE,");
            mvprintw(starter_height + 13, starter_width, "AND A NUMBER.");
            refresh();
            napms(6000);
            continue;
        }

        if ((strcmp(password, confirm))) {
            mvprintw(starter_height + 10, starter_width, "PASSWORD DO NOT MATCH.");
            refresh();
            napms(6000);
            continue;
        }  

        break;
    }

    clear();
    box(stdscr, 0, 0);
    mvprintw(starter_height, starter_width + 5, "Signed up!");
    refresh();
    napms(2000);
}


void user_menu() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    int width, height, starter_height, starter_width;
    
    getmaxyx(stdscr, height, width);

    const char *option[] = {"Log in", "Sign up", "Exit"};
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
                    sign_up();
                } else if (current_option == (number_of_options - 1)) {
                    endwin();
                    return;
                }

        }
    }
}