#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QObject>
#include <QWidget>
#include "item.h"
#include <QTimer>
#include <QMap>
#include <QMultiMap>
#include <QPoint>
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
    void add_downitem();
    bool left_col();
    bool right_col();
    bool bottom_col();
    bool top_col();
    void move(const QString &button);
    void update_topitem();
    int topnum_item(QPoint &pt,int &num);
    int clear_downitem(int num);
signals:
    void is_gameover(bool is);
private:
    Item *now_item;//当前在运动的方块
    QMultiMap<int,QPoint> down_item;//底下方块<方块，在第几行>
    QMap<int,int> line_count;//统计每行方块的数量<在第几行，数量>
    QVector<QPoint> top_item;//统计底部方块区域中最上面的方块坐标
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
