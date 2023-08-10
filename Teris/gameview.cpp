#include "gameview.h"
#include <QPainter>
#include <QPaintEvent>
#include <QTimerEvent>
#include <QVector>
#include <QPoint>

#define RECT_COLUMES    30   //游戏区15个小格子宽
#define RECT_ROWS        40   //游戏区20个小格子高
#define RECT_WIDTH        20   //每个小格子40个像素宽
#define RECT_HEIGHT        20   //每个小格子40个像素高

gameview::gameview(QWidget *parent)
    :QWidget(parent)
{

}

void gameview::init()
{
    now_item=new Item();

}

void gameview::begin()
{
//    qDebug()<<"asdf";
    //设置间隔时间为400的计时器
    time_id=startTimer(400);
    time.start();
}

void gameview::pause()
{
    killTimer(time_id);
}

void gameview::restart()
{
    Item *item=new Item();
    now_item=item;
    //map的清空
    begin();
}

void gameview::draw_window()//绘制窗体边界
{
    QPainter painter(this);
    painter.setBrush(QColor("#D3D3D3"));
    painter.setPen("#D3D3D3");
    for(int i=0;i<RECT_ROWS;i++){
        for(int j=0;j<RECT_COLUMES;j++){
            if(i==0||j==0||i==RECT_ROWS-1||j==RECT_COLUMES-1)
                painter.drawRect(j*RECT_WIDTH,i*RECT_HEIGHT,RECT_WIDTH,RECT_HEIGHT);
        }
    }
}

void gameview::draw_nowitem()
{
    QPainter painter(this);
    now_item->draw(painter);
}

void gameview::draw_downitem()
{

}

bool gameview::left_col()
{
    QVector<QPoint> points=now_item->getAll_point();
    for(auto p=points.begin();p!=points.end();p++){
        if(p->x()<RECT_ROWS){
            return true;
        }
    }
    return false;
}

void gameview::paintEvent(QPaintEvent *event)//绘图事件，当窗体发生变更时，自动执行
{
    draw_window();
    draw_nowitem();
    draw_downitem();
    event->accept();
}

void gameview::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==time_id){//判断是哪个计时器
        now_item->down_move(1);
        repaint();//重绘
    }
}
