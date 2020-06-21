#include "options_dialog.h"
#include "ui_options_dialog.h"

#include <QSettings>
#include <QStringList>

#define URLS_GROUP QStringLiteral("URLs")
#define URLS_KEY QStringLiteral("URLs")

OptionsDialog::OptionsDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::OptionsDialog)
{
  ui->setupUi(this);

  setWindowFlag(Qt::WindowContextHelpButtonHint, false);

  on_treeHosts_itemSelectionChanged();
}

OptionsDialog::~OptionsDialog()
{
  delete ui;
}

void OptionsDialog::on_treeHosts_itemSelectionChanged()
{
  ui->btnHostRemove->setEnabled(!ui->treeHosts->selectedItems().isEmpty());
}

void OptionsDialog::on_btnHostAdd_clicked()
{
  static int counter{0};
  QUrl url{QUrl::fromUserInput(QStringLiteral("host%1.com").arg(++counter))};
  Q_ASSERT(url.isValid());
  QTreeWidgetItem *url_item{new QTreeWidgetItem()};
  url_item->setText(0, url.toString());
  url_item->setFlags(url_item->flags() | Qt::ItemIsEditable);

  ui->treeHosts->addTopLevelItem(url_item);
  ui->treeHosts->scrollToItem(url_item);
  ui->treeHosts->setCurrentItem(url_item);
  url_item->setSelected(true);
  ui->treeHosts->editItem(url_item, 0);
}

void OptionsDialog::on_btnHostRemove_clicked()
{
  for (QTreeWidgetItem *item : ui->treeHosts->selectedItems()) {
    delete item;
  }
}

void OptionsDialog::saveUrls(const QList<QUrl>& urls)
{
  QStringList to_save;
  for (const QUrl& url : urls) {
    to_save.append(url.toString());
  }

  QSettings settings;
  settings.beginGroup(URLS_GROUP);
  settings.setValue(URLS_KEY, to_save);
}

QList<QUrl> OptionsDialog::loadUrls()
{
  QList<QUrl> result;
  QSettings settings;
  settings.beginGroup(URLS_GROUP);
  for (const QString& url_str : settings.value(URLS_KEY, QStringList{"yandex.ru", "google.com"}).toStringList()) {
    QUrl url{QUrl::fromUserInput(url_str)};
    if (url.isValid()) {
      result.append(url);
    }
  }
  return result;
}

void OptionsDialog::setUrls(const QList<QUrl>& urls)
{
  ui->treeHosts->clear();

  for (const QUrl& url : urls) {
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, url.toString());
    ui->treeHosts->addTopLevelItem(item);
  }
}

QList<QUrl> OptionsDialog::urls() const
{
  QList<QUrl> result;

  for (int i = 0; i < ui->treeHosts->topLevelItemCount(); ++i) {
    QUrl url{QUrl::fromUserInput(ui->treeHosts->topLevelItem(i)->text(0))};
    if (url.isValid()) {
      result.append(url);
    }
  }

  return result;
}
