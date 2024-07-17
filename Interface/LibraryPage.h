//
// Created by Fardeen Bablu on 7/13/24.
//

#ifndef QUIZLITE_LIBRARYPAGE_H
#define QUIZLITE_LIBRARYPAGE_H

#include "../Interface/MainWindow.h"

class LibraryPage : public QWidget {
	Q_OBJECT

public:
	LibraryPage(QWidget *parent = nullptr);

	//Im creating a "signal" label to do something when the "+ Create Set"
    // button is clicked.
signals:
	void createSetClicked();


private:
    //UI Stuff
    QVBoxLayout *ui;
    QLabel *pageLabel;
    QPushButton *createSetButton;

};
#endif //QUIZLITE_LIBRARYPAGE_H
