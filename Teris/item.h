#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <QWidget>
#include <QVector>
#include <QPoint>

enum ITEM_TYPE{
    ITEM_1=0,
    ITEM_2,
    ITEM_3,
    ITEM_4,
    ITEM_5,
    ITEM_6
};

enum ITEM_STYLE{
    STYLE_1=1,
    STYLE_2,
    STYLE_3,
    STYLE_4
};

class Item:public QWidget
{
public:
    Item();
    Item(ITEM_TYPE type,ITEM_STYLE style);//按照方块类型和形状创建对象
    ~Item();

private:
    QVector<QPoint> all_point;//统计每个方块点的坐标
    ITEM_TYPE type;//方块类型
    ITEM_STYLE style;//方块种类

public:
    void InitItem(ITEM_TYPE type,ITEM_STYLE style);
    void Init_rand();
    void draw(QPainter &painter);
    void down_move(int y);

//    // QWidget interface
//protected:
    //    virtual void paintEvent(QPaintEvent *event) override;
    QVector<QPoint> getAll_point() const;
};

#endif // ITEM_H
