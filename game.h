#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>

#include "consts.h"
#include "input.h"
#include "button.h"

class Game : public QGraphicsView
{
    Q_OBJECT

    public:
        Game();
        ~Game();
        QPixmap* load_texture(QString path);
        void keyPressEvent(QKeyEvent *key);
        bool check_letter(QString letter);
        void place_word();
        void draw_letter(QString letter);
        void draw_hangman();

        void mousePressEvent(QMouseEvent *event);
        void game_finished();

        enum Parts
        {
            HEAD = 0,
            TORSO,
            RIGHT_ARM,
            LEFT_ARM,
            RIGHT_LEG,
            LEFT_LEG,
            ALL_PARTS
        };

    public slots:
        void start_menu();
        void start_game();

    private:
        bool won;
        int attempts;

        QGraphicsScene *scene;       

        QString guessedWord;
        QPoint letterPos;
        QFont textFont;
        std::vector<QString> usedLetters;
        QGraphicsTextItem *theWord;

        QPixmap *startScreen;
        QPixmap *playButton;
        QPixmap *menuButton;
        QPixmap *gallow;
        QPixmap *hangman[ALL_PARTS];

        Input *userInput;
};

#endif // GAME_H
