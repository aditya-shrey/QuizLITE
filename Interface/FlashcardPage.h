//
// Created by Fardeen Bablu on 7/30/24.
//

#ifndef FLASHCARD_PAGE_H
#define FLASHCARD_PAGE_H

#include "../StudyingMethods/Flashcards.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QResizeEvent>
#include <QApplication>
#include <QMessageBox>

/**
 * @class FlashcardPage
 * @brief A class to represent the Flashcard Quiz page in the QuizLite application.
 *
 * The FlashcardPage class handles the user interface and logic for conducting a flashcard quiz. It manages
 * the quiz lifecycle, including starting the session, displaying flashcards, toggling between questions and answers,
 * and finishing the session.
 */
class FlashcardPage : public QWidget {
Q_OBJECT

public:
    /**
     * @brief Constructs a FlashcardPage object.
     * @param parent The parent widget. Defaults to nullptr.
     */
    explicit FlashcardPage(QWidget *parent = nullptr);

    /**
     * @brief Starts a flashcard quiz using the specified set name.
     * @param setName The name of the set to be used for the quiz.
     */
    void startFlashcardQuiz(const QString &setName);

protected:
    /**
     * @brief Handles the resize event to adjust flashcard button size.
     * @param event The resize event.
     */
    void resizeEvent(QResizeEvent *event) override;

private:
    /**
     * @brief Sets up the user interface for the FlashcardPage.
     */
    void setupUI();

    /**
     * @brief Resets the flashcard session, clearing any current progress and preparing for a new session.
     */
    void resetFlashcardSession();

    /**
     * @brief Finishes the flashcard session and displays a completion message.
     */
    void finishFlashcardSession();

    /**
     * @brief Displays the next flashcard in the quiz.
     */
    void showNextFlashcard();

    /**
     * @brief Displays the previous flashcard in the quiz.
     */
    void showPreviousFlashcard();

    /**
     * @brief Toggles between displaying the question and the answer on the flashcard.
     */
    void toggleFlashcard();

    /**
     * @brief Sets up the "Back to Set" button and its click event.
     */
    void setupBackToSetButton();

    QVBoxLayout *ui;                   ///< The main layout for the page.
    QPushButton *flashcardButton;      ///< The button displaying the flashcard question/answer.
    QPushButton *nextButton;           ///< The button to proceed to the next flashcard.
    QPushButton *prevButton;           ///< The button to go back to the previous flashcard.
    QPushButton *finishButton;         ///< The button to finish the flashcard session.
    QPushButton *backToSetButton;      ///< The button to navigate back to the set screen.

    QString currentSetName;            ///< The name of the current set being used for the quiz.
    Flashcards *fc;                    ///< The flashcard logic handler.
    int currentIndex;                  ///< The current index of the flashcard being displayed.
    int totalFlashcards;               ///< The total number of flashcards in the set.
    bool isAnswerShown;                ///< A flag indicating whether the answer is currently shown.

signals:
    /**
     * @brief Signal emitted to navigate back to the set screen.
     */
    void backToSetClicked();
};

#endif // FLASHCARD_PAGE_H
