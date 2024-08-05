#include "StudyingMethods/Flashcards.h"
#include "StudyingMethods/MultipleChoice.h"
#include "StudyingMethods/InverseMultipleChoice.h"
#include "Interface/MainWindow.h"
#include <QApplication>

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
