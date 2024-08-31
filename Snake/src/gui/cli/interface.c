#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

#include "../../brick_game/tetris/tetris.h"

void init_ncurses() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);
  timeout(500);
}

void terminate_ncurses() { endwin(); }

void save_game(int max_score) {
  FILE *file = fopen("save.txt", "w");
  if (file == NULL) {
    perror("Ошибка при открытии файла");
    return;
  }
  // Сохраняем значение max_score в файл
  fprintf(file, "%d\n", max_score);

  fclose(file);
}

void draw_game(Tetris *game) {
  clear();
  refresh();
  // field
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      mvprintw(i + 1, j + 1, " ");
      if (game->field.field[i][j]) {
        mvprintw(i + 1, j + 1, "0");
      }
    }
  }

  // border
  for (int i = 0; i < HEIGHT; i++) {
    mvprintw(i + 1, 0, "|");
    mvprintw(i + 1, WIDTH + 1, "|");
  }
  for (int j = 0; j < WIDTH; j++) {
    mvprintw(0, j + 1, "-");
    mvprintw(HEIGHT + 1, j + 1, "-");
  }
  // current figure
  for (int i = 0; i < 4; i++) {
    int x = game->current_figure.Position[i].x;
    int y = game->current_figure.Position[i].y;
    mvprintw(y + 1, x + 1, "#");
  }
  // next figure
  mvprintw(0, WIDTH + 3, "MAX SCORE: %d", game->max_score);
  mvprintw(1, WIDTH + 3, "LEVEL: %d", game->level);
  mvprintw(2, WIDTH + 3, "Score: %d", game->score);
  mvprintw(3, WIDTH + 3, "Next:");
  for (int i = 0; i < 4; i++) {
    int x = game->next_figure.Position[i].x;
    int y = game->next_figure.Position[i].y;
    mvprintw(y + 4, x + WIDTH + 3, "#");
  }
  // load max score from file
  FILE *file = fopen("save.txt", "r");
  if (file != NULL) {
    fscanf(file, "%d", &(game->max_score));
    fclose(file);
  }
  refresh();
}

int main() {
  Tetris game = {
      .field = {{{0}}}, .current_figure = {{{0}}}, .next_figure = {{{0}}}};
  init_game(&game);
  init_ncurses();
  while (true) {
    int botton = getch();
    switch (botton) {
      case 'q':
        terminate_ncurses();
        exit(0);
        break;
      case 'p':
        if (game.state == playing) {
          game.state = playing;
        } else if (game.state == paused) {
          game.state = playing;
        }
        break;
      case KEY_LEFT:
        move_figure_left_right(&game, 'l');
        break;
      case KEY_RIGHT:
        move_figure_left_right(&game, 'r');
        break;
      case KEY_DOWN:
        move_figure_down(&game);
        break;
      case ' ':
        rotate_figure(&game);
        break;
    }
    update_game(&game);
    draw_game(&game);
    if (game.state == game_over) {
      if (game.score > game.max_score) {
        game.max_score = game.score;
        save_game(game.max_score);
      }
      mvprintw(10, 2, "GAMEOVER");
      refresh();
      sleep(3);
      terminate_ncurses();
      exit(0);
    }
    timeout(1100 - game.level * 100);
  }
  terminate_ncurses();
  return 0;
}
