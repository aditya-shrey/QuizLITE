//
// Created by Fardeen Bablu on 7/17/24.
//

#ifndef QUIZLITE_ADDQUESTIONSPAGE_H
#define QUIZLITE_ADDQUESTIONSPAGE_H

#include <QMessageBox>
#include <QSet>
#include "MainWindow.h"
#include "CreateSetPage.h"

/**
 * @class AddQuestionsPage
 * @brief A widget for adding questions and answers to a quiz set.
 */
class AddQuestionsPage : public QWidget {
    Q_OBJECT
    QPushButton *backToLibraryButton;
public:
    /**
     * @brief Constructor for AddQuestionsPage.
     *
     * @param parent The parent widget.
     */
    AddQuestionsPage(QWidget *parent = nullptr);

    /**
     * @brief Getter for the QA list widget.
     *
     * @return Pointer to the QA list widget.
     */
    QListWidget *getQAListWidget() const { return qaListWidget; }

signals:
    /**
     * @brief Signal emitted when a question and answer are added to the set.
     *
     * @param question The question text.
     * @param answer The answer text.
     */
    void addToSetClicked(const QString &question, const QString &answer);

    /**
     * @brief Signal emitted when the finish button is clicked.
     */
    void finishedClicked();

    /**
     * @brief Signal emitted when the back to library button is clicked.
     */
    void backToLibraryClicked();

public slots:
    /**
    * @brief Sets up the back to library functionality.
    */
    void setupBackToLibrary();

private slots:
    /**
     * @brief Slot for adding a question and answer to the set.
     */
    void addToSet();

private:
    QVBoxLayout *ui;
    QLabel *pageLabel;
    QLineEdit *questionInput;
    QLineEdit *answerInput;
    QPushButton *addToSetButton;
    QPushButton *finishButton;
    QListWidget *qaListWidget;
    QSet<QString> *addedQuestions;
};

#endif //QUIZLITE_ADDQUESTIONSPAGE_H