#include "item.h"
#include <QPainter>
#include <QPaintEvent>
#include <QRect>
#include <QTime>

#define RECT_WIDTH        20   //每个小格子40个像素宽
#define RECT_HEIGHT        20   //每个小格子40个像素高

Item::Item()
{
    Init_rand();
    InitItem(type,style);
}

Item::~Item()
{

}

QVector<QPoint> Item::getAll_point() const
{
    return all_point;
}

void Item::InitItem(ITEM_TYPE type, ITEM_STYLE style)
{
    QPoint pt(5*RECT_WIDTH,RECT_HEIGHT);
    switch (type) {
    case ITEM_1://长条形
        switch(style){
        case STYLE_1://横状
            for(int i=0;i<4;i++){
                all_point.append(pt+QPoint(i*RECT_WIDTH,0));
            }
            break;
        case STYLE_2://竖状
            for(int i=0;i<4;i++){
                all_point.append(pt+QPoint(0,i*RECT_HEIGHT));
            }
            break;
        default:
            break;
        }
        break;
    case ITEM_2://山字形
        switch(style){
        case STYLE_1://朝上
            for(int i=0;i<3;i++){
                all_point.append(pt+QPoint(i*RECT_WIDTH,RECT_HEIGHT));
            }
            all_point.append(pt+QPoint(RECT_WIDTH,0));
            break;
        case STYLE_2://朝左
            for(int i=0;i<3;i++){
                all_point.append(pt+QPoint(RECT_HEIGHT,i*RECT_WIDTH));
            }
            all_point.append(pt+QPoint(0,RECT_HEIGHT));
            break;
        case STYLE_3://朝下
            for(int i=0;i<3;i++){
                all_point.append(pt+QPoint(i*RECT_WIDTH,0));
            }
            all_point.append(pt+QPoint(RECT_WIDTH,RECT_HEIGHT));
            break;
        case STYLE_4://朝右
            for(int i=0;i<3;i++){
                all_point.append(pt+QPoint(0,i*RECT_WIDTH));
            }
            all_point.append(pt+QPoint(RECT_WIDTH,RECT_HEIGHT));
            break;
        default:
            break;
        }
        break;
    case ITEM_3://手枪形
        switch(style){
        case STYLE_1://朝上
            for(int i=0;i<3;i++){
                all_point.append(pt+QPoint(0,i*RECT_WIDTH));
            }
            all_point.append(pt+QPoint(RECT_WIDTH,RECT_HEIGHT*2));
            break;
        case STYLE_2://朝左
            for(int i=0;i<3;i++){
                all_point.append(pt+QPoint(i*RECT_WIDTH,RECT_HEIGHT));
            }
            all_point.append(pt+QPoint(RECT_WIDTH*2,0));
            break;
        case STYLE_3://朝下
            for(int i=0;i<3;i++){
                all_point.append(pt+QPoint(RECT_WIDTH,i*RECT_WIDTH));
            }
            all_point.append(pt+QPoint(0,0));
            break;
        case STYLE_4://朝右
            for(int i=0;i<3;i++){
                all_point.append(pt+QPoint(i*RECT_WIDTH,0));
            }
            all_point.append(pt+QPoint(0,RECT_HEIGHT));
            break;
        default:
            break;
        }
        break;
    case ITEM_4://蛇形左凸1
        switch(style){
        case STYLE_1://横状
            for(int i=1;i<3;i++){
                all_point.append(pt+QPoint(i*RECT_WIDTH,0));
            }
            for(int i=0;i<2;i++){
                all_point.append(pt+QPoint(i*RECT_WIDTH,RECT_HEIGHT));
            }
            break;
        case STYLE_2://竖状
            for(int i=1;i<3;i++){
                all_point.append(pt+QPoint(RECT_WIDTH,i*RECT_WIDTH));
            }
            for(int i=0;i<2;i++){
                all_point.append(pt+QPoint(0,i*RECT_WIDTH));
            }
            break;
        default:
            break;
        }
        break;
    case ITEM_5://蛇形右凸2
        switch(style){
        case STYLE_1://横状
            for(int i=0;i<2;i++){
                all_point.append(pt+QPoint(i*RECT_WIDTH,0));
            }
            for(int i=1;i<3;i++){
                all_point.append(pt+QPoint(i*RECT_WIDTH,RECT_HEIGHT));
            }
            break;
            break;
        case STYLE_2://竖状
            for(int i=0;i<2;i++){
                all_point.append(pt+QPoint(RECT_WIDTH,i*RECT_WIDTH));
            }
            for(int i=1;i<3;i++){
                all_point.append(pt+QPoint(0,i*RECT_WIDTH));
            }
            break;
        default:
            break;
        }
        break;
    case ITEM_6://田字形
            for(int i=0;i<2;i++){
                all_point.append(pt+QPoint(i*RECT_WIDTH,0));
                all_point.append(pt+QPoint(i*RECT_WIDTH,RECT_HEIGHT));
            }
            break;
    default:
        break;
    }
}

void Item::Init_rand()//随机方块类型和种类
{
    srand(QTime::currentTime().msec());//按当前时间设置种子
    type=(ITEM_TYPE)(rand()%(ITEM_6+1));//随机类型
    style=(ITEM_STYLE)(rand()%(STYLE_4+1));//随机种类
    if(type==ITEM_1||type==ITEM_4||type==ITEM_5){//当随机到只有两种种类的方块，重新随机
        while(true){
            if(style==STYLE_1||style==STYLE_2)
                break;
            style=(ITEM_STYLE)(rand()%(STYLE_4+1));
        }
    }
}

void Item::draw(QPainter &painter)
{
    Q_UNUSED(painter);
    for(auto p=all_point.begin();p<all_point.end();p++)
        painter.drawRect((*p).x(),(*p).y(),RECT_WIDTH,RECT_HEIGHT);

}

void Item::down_move(int y)//方块下降
{
    for(auto p=all_point.begin();p!=all_point.end();p++){
        p->setY(p->y()+y*10);
    }
}

//void Item::paintEvent(QPaintEvent *event)
//{
//    draw();
//    event->accept();
//}
