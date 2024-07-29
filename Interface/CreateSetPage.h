//
// Created by Fardeen Bablu on 7/13/24.
//

#ifndef QUIZLITE_CREATESETPAGE_H
#define QUIZLITE_CREATESETPAGE_H

#include "MainWindow.h"
#include "../User/UserSession.h"

/**
 * @class CreateSetPage
 *
 * @brief A widget for creating a new quiz set.
 */
class CreateSetPage : public QWidget {
    Q_OBJECT
    QPushButton *backToLibraryButton;

public:
    /**
     * @brief Constructor for CreateSetPage.
     *
     * @param parent The parent widget.
     */
    CreateSetPage(QWidget *parent = nullptr);

signals:
    /**
     * @brief Signal emitted when the set name is confirmed.
     *
     * @param setName The confirmed set name.
     */
    void setNameConfirmed(const QString &setName);

    /**
     * @brief Signal emitted when the back to library button is clicked.
     */
    void backToLibraryClicked();

public slots:
    /**
     * @brief Sets up the back to library functionality.
     */
    void setupBackToLibrary();

private:
    QVBoxLayout *ui;
    QLabel *pageLabel;
    QLabel *setNameLabel;
    QLineEdit *setNameInput;
    QPushButton *confirmButton;
};
#endif //QUIZLITE_CREATESETPAGE_H