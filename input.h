#ifndef INPUT_H
#define INPUT_H

#include <QString>
#include <vector>
#include <QFile>
#include <QKeyEvent>
#include <QTextStream>
#include <cstdlib>

#include "consts.h"

class Input
{
    public:
        Input();
        ~Input();
        void read_file();
        int choose_word();
        void add_recent();
        bool handle_input(QKeyEvent *event, QString &word);
        bool check_word(QString word);
        QString return_word();

    private:
        QString currentWord;
        std::vector<QString> allWords;
        std::vector<QString> recentWords;
};

#endif // INPUT_H
