#include "weapon.h"

weapon::weapon()
{

}

void weapon::bossATK()
{
	setPos(x(), y() + 5);
    if(y() > 830) {
		this->scene()->removeItem(this);
		delete this;
	}
}

void weapon::bossLeftATK(){
    setPos(x()-3, y() + 5);
    if(y() > 830) {
        this->scene()->removeItem(this);
        delete this;
    }
}

void weapon::bossRightATK(){
    setPos(x()+3, y() + 5);
    if(y() > 830) {
        this->scene()->removeItem(this);
        delete this;
    }
}

