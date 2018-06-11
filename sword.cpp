#include "sword.h"
#include<QDebug>

sword::sword()
{

}

void sword::fly()
{
	setPos(x(), y() - 3);
	if(y() < 0) {
		this->scene()->removeItem(this);
		delete this;
	}
}

void sword::golden_fly()
{
    setPos(x(), y() - 3);
    if(y() < 0) {
        this->scene()->removeItem(this);
        delete this;
    }
}

void sword::golden_L_fly()
{
    setPos(x()-4, y() - 3);
    if(y() < 0) {
        this->scene()->removeItem(this);
        delete this;
    }
}

void sword::golden_R_fly()
{
    setPos(x()+4, y() - 3);
    if(y() < 0) {
        this->scene()->removeItem(this);
        delete this;
    }
}
