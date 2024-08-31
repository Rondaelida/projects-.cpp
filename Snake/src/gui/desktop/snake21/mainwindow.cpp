#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  snakeWidget = new SnakeWidget(this);

  // Создаем вертикальный макет
  verticalLayout = new QVBoxLayout(ui->centralwidget);

  // Добавляем виджет змейки в вертикальный макет
  verticalLayout->addWidget(snakeWidget);

  // Устанавливаем макет для центрального виджета
  ui->centralwidget->setLayout(verticalLayout);
}

MainWindow::~MainWindow() { delete ui; }
