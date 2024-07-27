#ifndef LIBRARYPAGE_H
#define LIBRARYPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QList>
#include <QWidgetItem>
#include <QResizeEvent>
#include <QPushButton>
#include <algorithm>
#include "../User/UserSession.h"

/**
 * @class LibraryPage
 * @brief A widget for displaying and managing quiz sets in the library.
 */
class LibraryPage : public QWidget {
Q_OBJECT

public:
    /**
     * @brief Constructor for LibraryPage.
     * @param parent The parent widget.
     */
    explicit LibraryPage(QWidget *parent = nullptr);

signals:
    /**
     * @brief Signal emitted when the create set button is clicked.
     */
    void createSetClicked();

    /**
     * @brief Signal emitted when a set is opened.
     *
     * @param setName The name of the set to be opened.
     */
    void openSetClicked(const QString &setName);

public slots:
    /**
     * @brief Populates the library with existing sets.
     */
    void populateLibrary();

    /**
     * @brief Adds a new set button to the library.
     *
     * @param setName The name of the set to be added.
     */
    void addSetButton(const QString &setName);

protected:
    /**
     * @brief Handles resize events to update the layout of set buttons.
     *
     * @param event The resize event.
     */
    void resizeEvent(QResizeEvent *event) override;

private:
    QVBoxLayout *ui;
    QLabel *pageLabel;
    QPushButton *createSetButton;
    QLabel *yourSetsLabel;
    QLabel *logoLabel;
    QGridLayout *setButtonsLayout;
    QList<QPushButton *> setButtons;

    /**
     * @brief Updates the layout of set buttons based on the current window size.
     */
    void updateSetButtonsLayout();
};

#endif // LIBRARYPAGE_H
