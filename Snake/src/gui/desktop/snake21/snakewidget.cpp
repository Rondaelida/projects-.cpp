#include "snakewidget.h"

SnakeWidget::SnakeWidget(QWidget *parent)
    : QWidget(parent), snakeGame(), controller(&snakeGame) {
  timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &SnakeWidget::updateGame);
  timer->start(100);  // Установите интервал обновления
}

void SnakeWidget::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  // Рисуем змейку и яблоко
  for (const auto &segment : snakeGame.snake) {
    painter.fillRect(segment.x * 20, segment.y * 20, 20, 20, Qt::green);
  }
  auto apple = snakeGame.apple;
  painter.fillRect(apple.x * 20, apple.y * 20, 20, 20, Qt::red);
}

void SnakeWidget::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
    case Qt::Key_Up:
      controller.userInput(Up, false);
      break;
    case Qt::Key_Down:
      controller.userInput(Down, false);
      break;
    case Qt::Key_Left:
      controller.userInput(Left, false);
      break;
    case Qt::Key_Right:
      controller.userInput(Right, false);
      break;
    case Qt::Key_Space:
      controller.userInput(Action, true);
      break;
  }
}

void SnakeWidget::updateGame() {
  controller.updateCurrentState();
  update();
}
