#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "idle_handler.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  void idle_update_ui();

private:
  Ui::MainWindow *ui;

private:
  IdleHandler idle_handler_;
};
#endif // MAINWINDOW_H
