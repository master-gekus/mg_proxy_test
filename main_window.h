#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUrl>
#include <QList>

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

private slots:
  void on_actionOptions_triggered();

private:
  Ui::MainWindow *ui;

private:
  IdleHandler idle_handler_;
  QList<QUrl> urls_;
};
#endif // MAINWINDOW_H
