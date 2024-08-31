#ifndef TETRIS_H
#define TETRIS_H

// #include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define WIDTH 10
#define HEIGHT 20

#define true 1
#define false 0

// координаты
typedef struct Position {
  int x;
  int y;
} Position;

// инф о фигуре
typedef struct FigureInfo {
  Position Position[4];
  int type_f;
  int rotation;
} FigureInfo;

// поле
typedef struct Field {
  int field[HEIGHT][WIDTH];
} Field;

static const Position figures[7][4][4] = {
    // figure I
    {{{0, 0}, {0, 1}, {0, 2}, {0, 3}},
     {{0, 0}, {1, 0}, {2, 0}, {3, 0}},
     {{0, 0}, {0, 1}, {0, 2}, {0, 3}},
     {{0, 0}, {1, 0}, {2, 0}, {3, 0}}},
    // figure L
    {{{0, 0}, {1, 0}, {1, 1}, {1, 2}},
     {{0, 0}, {0, 1}, {1, 0}, {2, 0}},
     {{0, 0}, {0, 1}, {0, 2}, {1, 2}},
     {{0, 1}, {1, 1}, {2, 0}, {2, 1}}},
    // figure J
    {{{0, 2}, {1, 0}, {1, 1}, {1, 2}},
     {{0, 0}, {1, 0}, {2, 0}, {2, 1}},
     {{0, 0}, {0, 1}, {0, 2}, {1, 0}},
     {{0, 0}, {0, 1}, {1, 1}, {2, 1}}},
    // figure 0
    {{{0, 0}, {0, 1}, {1, 0}, {1, 1}},
     {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
     {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
     {{0, 0}, {0, 1}, {1, 0}, {1, 1}}},
    // figure S
    {{{0, 1}, {0, 2}, {1, 0}, {1, 1}},
     {{0, 0}, {1, 0}, {1, 1}, {2, 1}},
     {{0, 1}, {0, 2}, {1, 0}, {1, 1}},
     {{0, 0}, {1, 0}, {1, 1}, {2, 1}}},
    // figure Z
    {{{0, 0}, {0, 1}, {1, 1}, {1, 2}},
     {{0, 1}, {1, 0}, {1, 1}, {2, 0}},
     {{0, 0}, {0, 1}, {1, 1}, {1, 2}},
     {{0, 1}, {1, 0}, {1, 1}, {2, 0}}},
    // figure T
    {{{0, 1}, {1, 0}, {1, 1}, {1, 2}},
     {{0, 0}, {1, 0}, {1, 1}, {2, 0}},
     {{0, 0}, {0, 1}, {0, 2}, {1, 1}},
     {{0, 1}, {1, 0}, {1, 1}, {2, 1}}}};

// состояние игры
typedef enum { menu, playing, paused, game_over } Gamestate;

// данные игры
typedef struct Tetris {
  Field field;
  FigureInfo current_figure;
  FigureInfo next_figure;
  int score;
  int level;
  int max_score;
  Gamestate state;
} Tetris;

// BACK
// генерация рандомной фигуры;
FigureInfo generate_figure();
// инициализация игры
void init_game(Tetris *game);
// вращение фигуры
void rotate_figure(Tetris *game);
// влево вправо
void move_figure_left_right(Tetris *game, char vector);
// вниз
int move_figure_down(Tetris *game);
// закрепить
void lock_figure(Tetris *game);
// очистить линию
void clear_lines(Tetris *game);
// спавн фигуры
void spawn_new_figure(Tetris *game);
// обновление игры
void update_game(Tetris *game);

#endif
