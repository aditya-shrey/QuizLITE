#ifndef QUIZLITE_ENTERSETPAGE_H
#define QUIZLITE_ENTERSETPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include <QPair>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QLineEdit>
#include <map>

class EnterSetPage : public QWidget {
Q_OBJECT
    QPushButton *backToLibraryButton;

public:
    EnterSetPage(QWidget *parent = nullptr);

signals:
    void openSetClicked(const QString &setName);
    void backToLibraryClicked();
    void deleteSetClicked(const QString &setName);
    void deleteKeyValuePairClicked(const QString &setName, const QString &key);
    void adjustKeyValuePairClicked(const QString &setName, const QString &key, const QString &newValue);
    void confirmDeleteSet(const QString &setName);

public slots:
    void addSet(const QString &setName);
    void setSetName(const QString &setName);
    void setQAList(const QString &setName);
    void clearAllEntries();
    void setupBackButton();
    void showAddQuestionPage();
    void deleteSet(const QString &setName);
    void deleteKeyValuePair(const QString &setName, const QString &key);
    void adjustKeyValuePair(const QString &setName, const QString &key, const QString &newValue);

private:
    QVBoxLayout *ui;
    QLabel *setNameLabel;
    QLabel *pageLabel;
    QListWidget *qaListWidget;
    QString currentSetName;
    std::map<QString, QWidget*> setWidgets;
};

#endif // QUIZLITE_ENTERSETPAGE_H
