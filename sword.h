#ifndef SWORD_H
#define SWORD_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class sword : public QObject, public QGraphicsPixmapItem
{
		Q_OBJECT
	public:
		sword();

	public slots:
		void fly();
        void golden_fly();
        void golden_L_fly();
        void golden_R_fly();
};

#endif // SWORD_H
