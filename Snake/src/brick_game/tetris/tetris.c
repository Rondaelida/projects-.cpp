#include "tetris.h"

#include <ncurses.h>
void init_game(Tetris *game) {
  game->score = 0;
  game->state = playing;
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      game->field.field[i][j] = 0;
    }
  }
  game->current_figure = generate_figure();
  game->next_figure = generate_figure();

  FILE *file = fopen("score.txt", "r");
  if (file == NULL) {
    perror("Файл не найден");
    game->max_score = 0;
  } else {
    if (fscanf(file, "%d", &(game->max_score)) != 1) {
      perror("Ошибка чтения файла");
      game->max_score = 0;
    }
    fclose(file);
  }
}

FigureInfo generate_figure() {
  FigureInfo figure;
  figure.type_f = rand() % 7;
  figure.rotation = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      figure.Position[i].x = figures[figure.type_f][figure.rotation][i].x;
      figure.Position[j].y = figures[figure.type_f][figure.rotation][j].y;
    }
  }
  return figure;
}

void rotate_figure(Tetris *game) {
  FigureInfo *figure = &game->current_figure;
  int new_rotation = (figure->rotation + 1) % 4;
  Position new_position[4];
  for (int i = 0; i < 4; i++) {
    new_position[i] = figures[figure->type_f][new_rotation][i];
    new_position[i].x += figure->Position[0].x;
    new_position[i].y += figure->Position[0].y;
  }
  // проверяем столкновения с границами игрового поля и другими фигурами
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (figures[figure->type_f][new_rotation][i].x + figure->Position[j].x <
              0 ||
          figures[figure->type_f][new_rotation][i].x + figure->Position[j].x >=
              WIDTH ||
          figures[figure->type_f][new_rotation][i].y + figure->Position[j].y <
              0 ||
          figures[figure->type_f][new_rotation][i].y + figure->Position[j].y >=
              HEIGHT ||
          game->field.field[figures[figure->type_f][new_rotation][i].y +
                            figure->Position[j].y]
                           [figures[figure->type_f][new_rotation][i].x +
                            figure->Position[j].x]) {
        return;
      }
    }
  }
  // если столкновений нет, то меняем позиции и угол поворота фигуры
  for (int i = 0; i < 4; i++) {
    figure->Position[i] = new_position[i];
  }
  figure->rotation = new_rotation;
}

void move_figure_left_right(Tetris *game, char vector) {
  FigureInfo *figure = &game->current_figure;
  Position new_position[4];
  int step = (vector == 'l') ? -1 : 1;
  for (int i = 0; i < 4; i++) {
    new_position[i].x = figure->Position[i].x + step;
    new_position[i].y = figure->Position[i].y;
    if (new_position[i].x < 0 || new_position[i].x >= WIDTH ||
        game->field.field[new_position[i].y][new_position[i].x]) {
      return;
    }
  }
  for (int i = 0; i < 4; i++) {
    figure->Position[i] = new_position[i];
  }
}

int move_figure_down(Tetris *game) {
  FigureInfo *figure = &game->current_figure;
  Position new_position[4];
  for (int i = 0; i < 4; i++) {
    new_position[i].x = figure->Position[i].x;
    new_position[i].y = figure->Position[i].y + 1;
    if (new_position[i].y >= HEIGHT ||
        game->field.field[new_position[i].y][new_position[i].x] == true) {
      return false;
    }
  }
  for (int i = 0; i < 4; i++) {
    figure->Position[i] = new_position[i];
  }
  return true;
}

void lock_figure(Tetris *game) {
  FigureInfo *figure = &game->current_figure;
  for (int i = 0; i < 4; i++) {
    int x = figure->Position[i].x;
    int y = figure->Position[i].y;
    game->field.field[y][x] = 1;
  }
}

void clear_lines(Tetris *game) {
  int streak = 0;
  for (int i = HEIGHT - 1; i >= 0; --i) {
    int full_line = true;
    for (int j = 0; j < WIDTH; ++j) {
      if (!game->field.field[i][j]) {
        full_line = false;
        break;
      }
    }
    if (full_line) {
      streak++;
      for (int k = i; k > 0; --k) {
        for (int j = 0; j < WIDTH; ++j) {
          game->field.field[k][j] = game->field.field[k - 1][j];
        }
      }
      for (int j = 0; j < WIDTH; ++j) {
        game->field.field[0][j] = false;
      }
      i++;
    }
  }
  switch (streak) {
    case 1:
      game->score += 100;
      break;
    case 2:
      game->score += 300;
      break;
    case 3:
      game->score += 700;
      break;
    case 4:
      game->score += 1500;
      break;

    default:
      break;
  }
  game->level = game->score / 600;
  if (game->level > 10) game->level = 10;
}

void spawn_new_figure(Tetris *game) {
  game->current_figure = game->next_figure;
  game->next_figure = generate_figure();
  for (int i = 0; i < 4; i++) {
    int x = game->current_figure.Position[i].x;
    int y = game->current_figure.Position[i].y;
    if (game->field.field[y][x]) {
      game->state = game_over;
      break;
    }
  }
}
void update_game(Tetris *game) {
  refresh();
  if (!move_figure_down(game)) {
    lock_figure(game);
    clear_lines(game);
    spawn_new_figure(game);
  }
}
