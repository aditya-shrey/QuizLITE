//
// Created by Fardeen Bablu on 7/30/24.
//

#ifndef QUIZLITE_INVERSEMCPAGE_H
#define QUIZLITE_INVERSEMCPAGE_H

#include "EnterSetPage.h"
#include "../StudyingMethods/InverseMultipleChoice.h"
#include <QtWidgets>
#include <QtCore>
#include <QMessageBox>

/**
 * @class InverseMCPage
 * @brief A class to represent the Inverse Multiple Choice Quiz page in the QuizLite application.
 *
 * The InverseMCPage class handles the user interface and logic for conducting an inverse multiple choice quiz. It manages
 * the quiz lifecycle, including starting the quiz, displaying questions, checking answers, and finishing the quiz.
 */
class InverseMCPage : public QWidget {
Q_OBJECT

public:
    /**
     * @brief Constructs an InverseMCPage object.
     * @param parent The parent widget. Defaults to nullptr.
     */
    explicit InverseMCPage(QWidget *parent = nullptr);

public slots:
    /**
     * @brief Starts an inverse multiple choice quiz using the specified set name.
     * @param setName The name of the set to be used for the quiz.
     */
    void startInverseMCQuiz(const QString &setName);

    /**
     * @brief Resets the quiz state, clearing any current progress and preparing for a new quiz.
     */
    void resetQuiz();

private slots:
    /**
     * @brief Sets up the user interface for the InverseMCPage.
     */
    void setupUI();

    /**
     * @brief Displays the next question in the quiz.
     */
    void showQuestion();

    /**
     * @brief Checks the selected answer and updates the quiz state accordingly.
     */
    void checkAnswer();

    /**
    * @brief Displays the next question after the current question has been answered.
    */
    void showNextQuestion();

    /**
     * @brief Finishes the quiz and displays the user's score and accuracy.
     */
    void finishQuiz();

    /**
    * @brief Sets up the "Back to Set" button and its click event.
    */
    void setupBackToSetButton();

signals:
    /**
     * @brief Signal emitted to navigate back to the set screen.
     */
    void backToSetClicked();

private:
    QVBoxLayout *ui;                    ///< The main layout for the page.
    QLabel *questionLabel;              ///< The label displaying the current question.
    QButtonGroup *answerGroup;          ///< The button group managing the answer buttons.
    QVector<QRadioButton*> answerButtons; ///< A vector of radio buttons for displaying answer options.
    QPushButton *submitButton;          ///< The button to submit an answer.
    QPushButton *nextButton;            ///< The button to proceed to the next question.
    QPushButton *finishButton;          ///< The button to finish the quiz.
    QPushButton *backToSetButton;       ///< The button to navigate back to the set screen.

    InverseMultipleChoice *imc;         ///< The inverse multiple choice quiz logic handler.
    QString currentSetName;             ///< The name of the current set being used for the quiz.
    int currentScore;                   ///< The current score of the user.
    int totalQuestions;                 ///< The total number of questions asked.
    int setSize;                        ///< The size of the study set.
};

#endif // INVERSE_MC_PAGE_H