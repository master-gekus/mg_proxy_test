#include "main_window.h"
#include "./ui_main_window.h"

#include <QSettings>
#include <QSslSocket>
#include <QMessageBox>

#include "utils.h"

#define MAIN_WINDOW_GROUP QStringLiteral("Main Window")
#define GEOMETRY_KEY QStringLiteral("Geometry")
#define STATE_KEY QStringLiteral("State")

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow{parent}
  , ui{new Ui::MainWindow}
  , idle_handler_{this}
{
  ui->setupUi(this);

  ui->treeServers->setColumnWidth(0, 400);
  ui->treeServers->setColumnWidth(1, 150);

  QSettings settings;
  settings.beginGroup(MAIN_WINDOW_GROUP);
  restoreGeometry(settings.value(GEOMETRY_KEY).toByteArray());
  restoreState(settings.value(STATE_KEY).toByteArray());
  Utils::restoreElementsState(this, settings);
  settings.endGroup();

  connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::close);
  connect(&idle_handler_, &IdleHandler::idle, this, &MainWindow::idle_update_ui);

  if (!QSslSocket::supportsSsl()) {
    QMetaObject::invokeMethod(this, [this](){
      QMessageBox::critical(this, windowTitle(),
                            QStringLiteral("SSL support is not loaded, checking for HTTPS hosts will be disabled."));
    }, Qt::QueuedConnection);
  }
}

MainWindow::~MainWindow()
{
  QSettings settings;
  settings.beginGroup(MAIN_WINDOW_GROUP);
  settings.setValue(GEOMETRY_KEY, saveGeometry());
  settings.setValue(STATE_KEY, saveState());
  Utils::saveElementsState(this, settings);

  delete ui;
}

void MainWindow::idle_update_ui()
{
  ui->actionRemoveProxy->setEnabled(false);
  ui->actionCheckOne->setEnabled(false);
}
