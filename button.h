#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPixmap>

class Button : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

    public:
        Button(QPixmap *image);
        void mousePressEvent(QGraphicsSceneMouseEvent *e);

    signals:
        void clicked();
};

#endif // BUTTON_H
