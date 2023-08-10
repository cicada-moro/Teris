#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QObject>
#include <QWidget>
#include <QMap>
#include "item.h"
#include <QTimer>

class gameview:public QWidget
{
    Q_OBJECT
public:
    explicit gameview(QWidget *parent=nullptr);
public:
    void init();
    void begin();
    void pause();
    void restart();
    void draw_window();
    void draw_nowitem();
    void draw_downitem();
    bool left_col();
    bool right_col();
    bool bottom_col();
    bool top_col();
private:
    Item *now_item;//当前在运动的方块
    QMap<Item,double> down_item;//底下方块<方块，在第几行>
    QMap<double,int> line_count;//统计每行方块的数量<在第几行，数量>
    int time_id;
    QTimer time;

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;


    // QObject interface
protected:
    virtual void timerEvent(QTimerEvent *event) override;
};

#endif // GAMEVIEW_H
