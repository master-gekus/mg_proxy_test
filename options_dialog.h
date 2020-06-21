#ifndef OPTIONS_DIALOG_H
#define OPTIONS_DIALOG_H

#include <QDialog>
#include <QUrl>
#include <QList>

namespace Ui {
class OptionsDialog;
}

class OptionsDialog : public QDialog
{
  Q_OBJECT

public:
  explicit OptionsDialog(QWidget *parent = nullptr);
  ~OptionsDialog();

public:
  static void saveUrls(const QList<QUrl>& urls);
  static QList<QUrl> loadUrls();

  void setUrls(const QList<QUrl>& urls);
  QList<QUrl> urls() const;

private slots:
  void on_treeHosts_itemSelectionChanged();
  void on_btnHostAdd_clicked();
  void on_btnHostRemove_clicked();

private:
  Ui::OptionsDialog *ui;
};

#endif // OPTIONS_DIALOG_H
