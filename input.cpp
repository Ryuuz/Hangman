#include "input.h"


Input::Input()
{
    read_file();
}


Input::~Input()
{
    allWords.clear();
    recentWords.clear();
    currentWord.clear();
}


//Reads in words from a file and puts them in a vector
//Makes all the words upper case for easier comparison later
void Input::read_file()
{
    QFile file(":/text/words.dat");

    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);

        while(!in.atEnd())
        {
            QString tempString;
            tempString = in.readLine();
            allWords.push_back(tempString.toUpper());
        }

        file.close();
    }
}


//Chooses a word from the list of possible words
int Input::choose_word()
{
    bool used;
    int index;

    if(!currentWord.isEmpty())
    {
        add_recent();
    }

    //Chooses a random word that has not been used recently
    do
    {
        used = false;
        index = rand() % allWords.size();

        for(auto const &word : recentWords)
        {
            if(allWords[index] == word)
            {
                used = true;
            }
        }
    }while(used);

    currentWord = allWords[index];

    return currentWord.size();
}


//Adds the word that was used last to the list of recently used words
void Input::add_recent()
{
    recentWords.push_back(currentWord);

    //Makes sure only a set amount of words are kept in memory at a time
    if(recentWords.size() > Constants::wordMemory)
    {
        recentWords.erase(recentWords.begin());
    }
}


//Checks if the word contains the chosen letter
bool Input::handle_input(QKeyEvent *event, QString &word)
{
    bool letterFound = false;

    for(int i = 0; i < currentWord.size(); i++)
    {
        if(event->text().at(0).toUpper() == currentWord[i])
        {
            word[i] = event->text().at(0).toUpper();
            letterFound = true;
        }
    }

    return letterFound;
}


//Returns true if the user has guessed the whole word
bool Input::check_word(QString word)
{
    if(word == currentWord)
    {
        return true;
    }

    return false;
}


QString Input::return_word()
{
    return currentWord;
}
