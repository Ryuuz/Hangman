#include "game.h"


Game::Game() : won(true), attempts(0), letterPos(Constants::lettersX, Constants::lettersY), textFont("Arial", Constants::letterSize)
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, Constants::screenWidth, Constants::screenHeight);

    startScreen = load_texture(":/images/Hangman/startScreen.png");
    playButton = load_texture(":/images/Hangman/playButton.png");
    menuButton = load_texture(":/images/Hangman/menuButton.png");
    gallow = load_texture(":/images/Hangman/gallows.png");

    hangman[HEAD] = load_texture(":/images/Hangman/head.png");
    hangman[TORSO] = load_texture(":/images/Hangman/torso.png");
    hangman[RIGHT_ARM] = load_texture(":/images/Hangman/rightArm.png");
    hangman[LEFT_ARM] = load_texture(":/images/Hangman/leftArm.png");
    hangman[RIGHT_LEG] = load_texture(":/images/Hangman/rightLeg.png");
    hangman[LEFT_LEG] = load_texture(":/images/Hangman/leftLeg.png");

    userInput = new Input();

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(Constants::screenWidth, Constants::screenHeight);
    setWindowTitle("Hangman");
}


Game::~Game()
{
    scene->clear();
    usedLetters.clear();
    delete scene;
    delete userInput;
    delete theWord;

    delete gallow;
    delete startScreen;
    delete playButton;
    delete menuButton;

    for(auto part : hangman)
    {
        delete part;
    }
}


//Loads texture from path and returns it if successful
QPixmap* Game::load_texture(QString path)
{
    QPixmap *tempPixmap = new QPixmap(path);

    if(tempPixmap->isNull())
    {
        exit(0);
    }

    return tempPixmap;
}


//Registers key presses and acts accordingly
void Game::keyPressEvent(QKeyEvent *event)
{
    //Only accepts letters
    if(event->key() >= Qt::Key_A && event->key() <= Qt::Key_Z)
    {
        if(check_letter(event->text().toUpper()))
        {
            usedLetters.push_back(event->text().toUpper());

            //Checks if letter is in word
            if(userInput->handle_input(event, guessedWord))
            {
                place_word();

                if(userInput->check_word(guessedWord))
                {
                    won = true;
                    game_finished();
                }
            }
            else
            {
                draw_hangman();
            }

            draw_letter(event->text().toUpper());
        }
    }
}


//Checks if the letter has been used before
bool Game::check_letter(QString letter)
{
    bool available = true;
    for(auto const &used : usedLetters)
    {
        if(letter == used)
        {
            available = false;
        }
    }

    return available;
}


//Decrease the font size if the word gets too big for the screen
void Game::place_word()
{
    theWord->setPlainText(guessedWord);

    while(theWord->boundingRect().width() >= (Constants::screenWidth/2))
    {
        theWord->setFont(QFont(theWord->font().family(), theWord->font().pointSize() - 1));
    }

    theWord->setPos((((Constants::screenWidth/4)*3) - (theWord->boundingRect().width()/2)), (Constants::screenHeight - theWord->boundingRect().height()));
}


//Displays the letters that have been used already
void Game::draw_letter(QString letter)
{
    QGraphicsTextItem *showUsed = new QGraphicsTextItem(letter);

    showUsed->setFont(textFont);
    showUsed->setPos(letterPos);
    scene->addItem(showUsed);

    letterPos.rx() += (showUsed->boundingRect().width() + 5);

    if(letterPos.x() >= (Constants::screenWidth - 100))
    {
        letterPos.rx() = Constants::lettersX;
        letterPos.ry() += (showUsed->boundingRect().height());
    }
}


//Draws the different parts of the hangman as user guesses wrong letters
void Game::draw_hangman()
{
    QGraphicsPixmapItem *tempImage = scene->addPixmap(*hangman[attempts]);
    tempImage->setPos(Constants::hangmanX, Constants::hangmanY);
    attempts++;

    if(attempts == ALL_PARTS)
    {
        game_finished();
    }
}


void Game::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        QGraphicsView::mousePressEvent(event);
    }
}


//Is called when an end condition is met
void Game::game_finished()
{
    QGraphicsTextItem *result;

    if(won)
    {
        result = new QGraphicsTextItem("You won!");
    }
    else
    {
        result = new QGraphicsTextItem("You lost!");

        //Shows the word if the user failed to guess it
        theWord->setPlainText(userInput->return_word());
    }

    result->setFont(textFont);

    //x = 3/4 of the screen - half the width of the text
    result->setPos((((Constants::screenWidth/4)*3) - (result->boundingRect().width()/2)), (Constants::screenHeight/2));
    scene->addItem(result);

    //Button that takes the user back to the start menu
    Button *restartButton = new Button(menuButton);
    restartButton->setPos((((Constants::screenWidth/4)*3) - (Constants::buttonWidth/2)), ((Constants::screenHeight/2) + Constants::buttonHeight));
    connect(restartButton, SIGNAL(clicked()), this, SLOT(start_menu()));
    scene->addItem(restartButton);
}


//Displays the start menu
void Game::start_menu()
{
    scene->clear();
    QGraphicsPixmapItem *tempImage = scene->addPixmap(*startScreen);
    tempImage->setPos(0, 0);

    Button *startButton = new Button(playButton);
    startButton->setPos(((Constants::screenWidth/4) - (Constants::buttonWidth/2)), ((Constants::screenHeight - Constants::buttonHeight) - 20));
    connect(startButton, SIGNAL(clicked()), this, SLOT(start_game()));
    scene->addItem(startButton);
}


//Sets up the variables for a new playthrough
void Game::start_game()
{
    scene->clear();
    usedLetters.clear();
    won = false;
    attempts = 0;
    letterPos.setX(Constants::lettersX);
    letterPos.setY(Constants::lettersY);
    guessedWord.fill('?', userInput->choose_word());

    theWord = new QGraphicsTextItem(guessedWord);
    theWord->setFont(textFont);
    theWord->setPos((((Constants::screenWidth/4)*3) - (theWord->boundingRect().width()/2)), (Constants::screenHeight - theWord->boundingRect().height()));
    scene->addItem(theWord);

    QGraphicsPixmapItem *tempImage = scene->addPixmap(*gallow);
    tempImage->setPos(0, 0);
}
