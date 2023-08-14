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

void Item::setAll_point(const QVector<QPoint> &newAll_point)
{
    all_point = newAll_point;
}

ITEM_STYLE Item::getStyle() const
{
    return style;
}

void Item::setStyle(ITEM_STYLE newStyle)
{
    style = newStyle;
}

ITEM_TYPE Item::getType() const
{
    return type;
}

void Item::setType(ITEM_TYPE newType)
{
    type = newType;
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
            for(int i=0;i<2;i++){
                all_point.append(pt+QPoint(0,i*RECT_WIDTH));
            }
            for(int i=1;i<3;i++){
                all_point.append(pt+QPoint(RECT_WIDTH,i*RECT_WIDTH));
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
        case STYLE_2://竖状
            for(int i=1;i<3;i++){
                all_point.append(pt+QPoint(0,i*RECT_WIDTH));
            }
            for(int i=0;i<2;i++){
                all_point.append(pt+QPoint(RECT_WIDTH,i*RECT_WIDTH));
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
    for(auto p=all_point.begin();p<all_point.end();p++)
        painter.drawRect((*p).x(),(*p).y(),RECT_WIDTH,RECT_HEIGHT);

}

void Item::down_move(int y)//方块下降
{
    if(y==0){
        for(auto p=all_point.begin();p!=all_point.end();p++){
            p->setY(p->y()+RECT_HEIGHT);
        }
        return;
    }
    for(auto p=all_point.begin();p!=all_point.end();p++){
        p->setY(p->y()+y*10);
    }

}

void Item::line_move(int x)
{
    if(x==0){
        for(auto p=all_point.begin();p!=all_point.end();p++){
            p->setX(p->x()-RECT_WIDTH);

        }
    }
    if(x==1){
        for(auto p=all_point.begin();p!=all_point.end();p++){
            p->setX(p->x()+RECT_WIDTH);
        }
    }
}

void Item::defomation(Item *item)
{
    ITEM_TYPE type=item->getType();
    ITEM_STYLE style=item->getStyle();
    switch (type) {
    case ITEM_1://长条形
        switch(style){
        case STYLE_1://横状
            for(int i=1;i<4;i++){
                int x=all_point[i].x();
                int y=all_point[i].y();
                all_point[i].setX(x-RECT_WIDTH*i);
                all_point[i].setY(y+RECT_HEIGHT*i);
            }
            setStyle(STYLE_2);
            break;
        case STYLE_2://竖状
            for(int i=1;i<4;i++){
                int x=all_point[i].x();
                int y=all_point[i].y();
                all_point[i].setX(x+RECT_WIDTH*i);
                all_point[i].setY(y-RECT_HEIGHT*i);
            }
            setStyle(STYLE_1);
            break;
        default:
            break;
        }
        break;
    case ITEM_2://山字形
        switch(style){
        case STYLE_1:{//朝上
            QPoint p=QPoint(0,0)+all_point[0];
            all_point[0]=all_point[3];
            all_point[3]=p;
            all_point[2].setX(all_point[2].x()-RECT_WIDTH);
            all_point[2].setY(all_point[2].y()+RECT_HEIGHT);
            setStyle(STYLE_2);
            break;
        }
        case STYLE_2://朝左
            all_point[0].setX(all_point[0].x()-RECT_WIDTH);
            all_point[1].setY(all_point[1].y()-RECT_HEIGHT);
            all_point[2].setX(all_point[2].x()+RECT_WIDTH);
            all_point[2].setY(all_point[2].y()-RECT_HEIGHT*2);
            all_point[3].setX(all_point[3].x()+RECT_WIDTH);
            setStyle(STYLE_3);
            break;
        case STYLE_3://朝下
            all_point[0].setX(all_point[0].x()+RECT_WIDTH);
            all_point[1].setY(all_point[1].y()+RECT_HEIGHT);
            all_point[2].setX(all_point[2].x()-RECT_WIDTH);
            all_point[2].setY(all_point[2].y()+RECT_HEIGHT*2);
            all_point[3].setX(all_point[3].x()+RECT_WIDTH);
            setStyle(STYLE_4);
            break;
        case STYLE_4:{//朝右
            QPoint p=QPoint(0,0)+all_point[0];
            all_point[0]=all_point[3];
            all_point[3]=p;
            all_point[2]=all_point[0];
            all_point[0].setX(all_point[0].x()-RECT_WIDTH*2);
            setStyle(STYLE_1);
            break;
        }
        default:
            break;
        }
        break;
    case ITEM_3://手枪形
        switch(style){
        case STYLE_1://朝上
            all_point[0].setX(all_point[0].x()-RECT_WIDTH);
            all_point[0].setY(all_point[0].y()+RECT_HEIGHT);
            all_point[2].setX(all_point[2].x()+RECT_WIDTH);
            all_point[2].setY(all_point[2].y()-RECT_HEIGHT);
            all_point[3].setY(all_point[3].y()-RECT_HEIGHT*2);
            setStyle(STYLE_2);
            break;
        case STYLE_2://朝左
            all_point[0].setX(all_point[0].x()+RECT_WIDTH);
            all_point[0].setY(all_point[0].y()-RECT_HEIGHT);
            all_point[2].setX(all_point[2].x()-RECT_WIDTH);
            all_point[2].setY(all_point[2].y()+RECT_HEIGHT);
            all_point[3].setX(all_point[3].x()-RECT_WIDTH*2);
            setStyle(STYLE_3);
            break;
        case STYLE_3://朝下
            all_point[0].setX(all_point[0].x()-RECT_WIDTH);
            all_point[1].setY(all_point[1].y()-RECT_HEIGHT);
            all_point[2].setX(all_point[2].x()+RECT_WIDTH);
            all_point[2].setY(all_point[2].y()-RECT_HEIGHT*2);
            all_point[3].setY(all_point[3].y()+RECT_HEIGHT);
            setStyle(STYLE_4);
            break;
        case STYLE_4://朝右
            all_point[0].setX(all_point[0].x()+RECT_WIDTH);
            all_point[1].setY(all_point[1].y()+RECT_HEIGHT);
            all_point[2].setX(all_point[2].x()-RECT_WIDTH);
            all_point[2].setY(all_point[2].y()+RECT_HEIGHT*2);
            all_point[3].setX(all_point[3].x()+RECT_WIDTH*2);
            all_point[3].setY(all_point[3].y()+RECT_HEIGHT);
            setStyle(STYLE_1);
            break;
        default:
            break;
        }
        break;
    case ITEM_4://蛇形左凸1
        switch(style){
        case STYLE_1://横状
            all_point[1].setX(all_point[1].x()-RECT_WIDTH);
            all_point[1].setY(all_point[1].y()+RECT_HEIGHT);
            all_point[2].setX(all_point[2].x()+RECT_WIDTH*2);
            all_point[3].setX(all_point[3].x()+RECT_WIDTH);
            all_point[3].setY(all_point[3].y()+RECT_HEIGHT);
            setStyle(STYLE_2);
            break;
        case STYLE_2://竖状
            all_point[1].setX(all_point[1].x()+RECT_WIDTH);
            all_point[1].setY(all_point[1].y()-RECT_HEIGHT);
            all_point[2].setX(all_point[2].x()-RECT_WIDTH*2);
            all_point[3].setX(all_point[3].x()-RECT_WIDTH);
            all_point[3].setY(all_point[3].y()-RECT_HEIGHT);
            setStyle(STYLE_1);
            break;
        default:
            break;
        }
        break;
    case ITEM_5://蛇形右凸2
        switch(style){
        case STYLE_1://横状
            all_point[0].setX(all_point[0].x()+RECT_WIDTH);
            all_point[0].setY(all_point[0].y()+RECT_HEIGHT);
            all_point[1].setY(all_point[1].y()+RECT_HEIGHT*2);
            all_point[2].setX(all_point[2].x()+RECT_WIDTH);
            all_point[2].setY(all_point[2].y()-RECT_HEIGHT);
            setStyle(STYLE_2);
            break;
            break;
        case STYLE_2://竖状
            all_point[0].setX(all_point[0].x()-RECT_WIDTH);
            all_point[0].setY(all_point[0].y()-RECT_HEIGHT);
            all_point[1].setY(all_point[1].y()-RECT_HEIGHT*2);
            all_point[2].setX(all_point[2].x()-RECT_WIDTH);
            all_point[2].setY(all_point[2].y()+RECT_HEIGHT);
            setStyle(STYLE_1);
            break;
        default:
            break;
        }
        break;
    case ITEM_6://田字形
        break;
    default:
        break;
    }
}

//void Item::paintEvent(QPaintEvent *event)
//{
//    draw();
//    event->accept();
//}
