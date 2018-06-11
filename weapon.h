#ifndef WEAPON_H
#define WEAPON_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class weapon : public QObject, public QGraphicsPixmapItem
{
		Q_OBJECT
	public:
		weapon();

	public slots:
		void bossATK();
        void bossLeftATK();
        void bossRightATK();
};

#endif // WEAPON_H

