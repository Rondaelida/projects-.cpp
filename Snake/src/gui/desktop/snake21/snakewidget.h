#ifndef SNAKEWIDGET_H
#define SNAKEWIDGET_H

#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QWidget>

#include "../../../brick_game/snake/controller/controller.h"
#include "../../../brick_game/snake/model/model.h"

class SnakeWidget : public QWidget {
  Q_OBJECT

 public:
  explicit SnakeWidget(QWidget *parent = nullptr);

 protected:
  void paintEvent(QPaintEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;

 private slots:
  void updateGame();

 private:
  s21::SnakeGame snakeGame;
  s21::Controller controller;
  QTimer *timer;
};

#endif  // SNAKEWIDGET_H
