//
// Created by Fardeen Bablu on 7/18/24.
//

#ifndef QUIZLITE_ENTERSETPAGE_H
#define QUIZLITE_ENTERSETPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include <QPair>

class EnterSetPage : public QWidget {
Q_OBJECT
QPushButton *backToLibraryButton;

public:
    EnterSetPage(QWidget *parent = nullptr);

signals:
    void openSetClicked(const QString &setName);
    void backToLibraryClicked();

public slots:
    void addSet(const QString &setName);
    void setSetName(const QString &setName);
    void setQAList(const QString &setName);
    void clearAllEntries();
    void setupBackButton();

private:
    QVBoxLayout *ui;
    QLabel *setNameLabel;
    QLabel *pageLabel;
    QListWidget *qaListWidget;
    QPushButton *exitSet;
};

#endif //QUIZLITE_ENTERSETPAGE_H
