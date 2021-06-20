#include<stdio.h>
#include<stdlib.h>
#include<ncurses.h>

typedef struct Player {
    int x;
    int y;
    char* direction;
    char* avatar;
} Player;

int screenSetup();
int mapSetup();
Player *playerSetup();
int handleInput(int input, Player * user);
int checkPosition(int newY, int newX, Player * user);
int playerMove(int y, int x, Player * user);

int main(int argc, char* argv[]) {
    Player * user;
    int ch;
    screenSetup();
    mapSetup();
    user = playerSetup();

    while ((ch = getch()) != 'q') {
        handleInput(ch, user);
    }

    endwin();

    return 0;
}

int screenSetup() {
    initscr();
    printw("hello, use hjkl to move, space to remove a block");
    noecho();
    curs_set(0);
    refresh();

    return 0;
}

Player * playerSetup() {
    Player * newPlayer;
    newPlayer = malloc(sizeof(Player));

    newPlayer->x = 10;
    newPlayer->y = 10;
    newPlayer->direction = "k";
    newPlayer->avatar = "*";

    playerMove(14, 14, newPlayer);
    mvprintw(newPlayer->x, newPlayer->y, newPlayer->avatar);

    return newPlayer;
}

int mapSetup() {
    mvprintw(13, 13, "----------------");
    mvprintw(14, 13, "|              |");
    mvprintw(15, 13, "|         .    |");
    mvprintw(16, 13, "|         .    |");
    mvprintw(17, 13, "|         .    |");
    mvprintw(18, 13, "-- -------------");

    mvprintw(3, 40, "------------");
    mvprintw(4, 40, "|..........|");
    mvprintw(5, 40, "|..........|");
    mvprintw(6, 40, "|..........|");
    mvprintw(7, 40, "|..........|");
    mvprintw(8, 40, "------------");

    return 0;
}

int handleInput(int input, Player * user) {
    int newY, newX;

    switch (input) {
        case ' ':
            switch (*user->direction) {
                case 'k': mvprintw(user->y - 1, user->x, " "); break;
                case 'j': mvprintw(user->y + 1, user->x, " "); break;
                case 'h': mvprintw(user->y, user->x - 1, " "); break;
                case 'l': mvprintw(user->y, user->x + 1, " "); break;
                default: break;
            }
            return 0;
            break;
        case 'k':
            user->direction = "k";
            newY = user->y - 1;
            newX = user->x;
            break;
        case 'j':
            user->direction = "j";
            newY = user->y + 1;
            newX = user->x;
            break;
        case 'h':
            user->direction = "h";
            newY = user->y;
            newX = user->x - 1;
            break;
        case 'l':
            user->direction = "l";
            newY = user->y;
            newX = user->x + 1;
            break;
    }

    checkPosition(newY, newX, user);
}

int checkPosition(int newY, int newX, Player * user) {
    int space;
    switch (mvinch(newY, newX)) {
        case ' ':
            playerMove(newY, newX, user);
            break;
        default:
            break;
    }
}

int playerMove(int y, int x, Player * user) {
    mvprintw(user->y, user->x, " ");
    user->x = x;
    user->y = y;

    mvprintw(user->y, user->x, user->avatar);
    move(user->x, user->y);
}
