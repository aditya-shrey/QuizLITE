#ifndef LIBRARYPAGE_H
#define LIBRARYPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QList>

class LibraryPage : public QWidget {
Q_OBJECT

public:
    explicit LibraryPage(QWidget *parent = nullptr);

signals:
    void createSetClicked();
    void openSetClicked(const QString &setName);

public slots:
    void populateLibrary();
    void addSetButton(const QString &setName);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QVBoxLayout *ui;
    QLabel *pageLabel;
    QPushButton *createSetButton;
    QLabel *yourSetsLabel;
    QGridLayout *setButtonsLayout;
    QList<QPushButton *> setButtons;

    void updateSetButtonsLayout();
};

#endif // LIBRARYPAGE_H
