#include <stdio.h>
#include <windows.h>
#include <conio.h>

#define UP 72
#define DOWN 80
#define ENTER 13
#define BACKSPACE 8

void gotoxy(int x, int y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void set_color(int fg, int bg) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bg << 4) | fg);
}

void draw_box(int x, int y, int w, int h) {
    gotoxy(x, y); printf("+");
    for (int i = 0; i < w-2; i++) printf("-");
    printf("+");
    for (int i = 1; i < h-1; i++) {
        gotoxy(x, y+i); printf("|");
        gotoxy(x+w-1, y+i); printf("|");
        for (int j = 1; j < w-1; j++) { gotoxy(x+j, y+i); printf(" "); }
    }
    gotoxy(x, y+h-1); printf("+");
    for (int i = 0; i < w-2; i++) printf("-");
    printf("+");
}

void draw_menu(char *options[], int n, int x, int y, int w, int h, int selected) {
    draw_box(x, y, w, h);
    for (int i = 0; i < n; i++) {
        gotoxy(x+1, y+1+i);
        if (i == selected) set_color(0, 15);
        else set_color(15, 0);
        printf("%-*.*s", w-2, w-2, options[i]);
        set_color(15, 0);
    }
}

void draw_textfield(int x, int y, int w, char *buffer) {
    draw_box(x, y, w, 3);
    gotoxy(x+1, y+1);
    set_color(0, 15);
    printf("%-*.*s", w-2, w-2, buffer);
    gotoxy(x+1, y+1);
    set_color(15, 0);
}

void textfield_input(int x, int y, int w, char *buffer, int max_len) {
    int pos = 0;
    buffer[0] = '\0';
    while (1) {
        gotoxy(x+1+pos, y+1);
        int ch = _getch();
        if (ch == ENTER) break;
        else if (ch == BACKSPACE) {
            if (pos > 0) {
                pos--;
                buffer[pos] = '\0';
                draw_textfield(x, y, w, buffer);
            }
        } else if (ch >= 32 && ch <= 126) {
            if (pos < max_len-1 && pos < w-3) {
                buffer[pos++] = ch;
                buffer[pos] = '\0';
                draw_textfield(x, y, w, buffer);
            }
        }
    }
}

int main() {
    system("cls");
    char *menu[] = {"Start Game", "Options", "Enter Name", "Exit"};
    int n = sizeof(menu)/sizeof(menu[0]);
    int selected = 0;
    char name[30];

    while (1) {
        draw_menu(menu, n, 10, 2, 30, n+2, selected);
        int ch = _getch();
        if (ch == 0 || ch == 224) {
            ch = _getch();
            if (ch == UP) selected--;
            if (ch == DOWN) selected++;
            if (selected < 0) selected = n-1;
            if (selected >= n) selected = 0;
        } else if (ch == ENTER) {
            if (selected == 2) {
                draw_textfield(45, 2, 30, name);
                textfield_input(45, 2, 30, name, 30);
            } else {
                gotoxy(0, 15);
                printf("You selected: %s\n", menu[selected]);
                break;
            }
        }
    }

    set_color(15,0);
    gotoxy(0,20);
    return 0;
}
