#include "button.h"


Button::Button(QPixmap *image)
{
    setPixmap(*image);
}


void Button::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    emit clicked();
}
