#include "gameview.h"
#include <QPainter>
#include <QPaintEvent>
#include <QTimerEvent>
#include <QVector>
#include <QPoint>
#include <QMap>
#include <QMultiMap>
#include <QMapIterator>
#include <QMessageBox>

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
    //初始化top_item
    QPoint p(RECT_WIDTH,(RECT_ROWS-1)*RECT_HEIGHT);
    for(int i=0;i<RECT_COLUMES-2;i++){
        QPoint pt(0,0);
        pt.setX(p.x()+i*RECT_WIDTH);
        pt.setY(p.y());
        top_item.append(pt);
    }
    for(int i=0;i<(RECT_COLUMES-2)*(RECT_ROWS-1);i++){
        QPoint pt(-1,-1);
        top_item.append(pt);
    }
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
    delete(now_item);


    //map和vector的清空
    down_item.clear();
    line_count.clear();
    top_item.clear();
    killTimer(time_id);
    init();
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
    if(down_item.isEmpty())
        return;
    QPainter painter(this);
    QList<QPoint> list=down_item.values();
    for(int i=0;i<list.size();i++){
        painter.drawRect(list[i].x(),list[i].y(),RECT_WIDTH,RECT_HEIGHT);
    }
}

void gameview::add_downitem()//更新底部方块群
{
    QVector<QPoint> points=now_item->getAll_point();
    //加入底部方块群
    for(int i=0;i<points.size();i++){
        const QPoint p=points[i];
        down_item.insert(p.y(),p);

        int count=line_count.value(p.y());
        line_count.insert(p.y(),count+=1);
    }
//    QMap<int, int>::Iterator iter;
//    for(iter = line_count.begin(); iter != line_count.end(); ++iter)
//    {
//        qDebug()<< "for   ==number==" << iter.key() << " name==" << iter.value();
//    }
}

bool gameview::left_col()//是否左碰壁
{
    QVector<QPoint> points=now_item->getAll_point();
    QList<QPoint> dp=down_item.values();
    for(auto p=points.begin();p!=points.end();p++){
//        qDebug()<<p->x();
        if(p->x()<=RECT_WIDTH){//边界碰壁
            return true;
        }
        for(int i=0;i<dp.size();i++){//方块碰壁
            if((p->x()-RECT_WIDTH)<=dp[i].x()&&abs(p->y()-dp[i].y())<RECT_HEIGHT&&p->x()>dp[i].x()){
                return true;
            }
        }
    }
    return false;
}

bool gameview::right_col()//是否右碰壁
{
    QVector<QPoint> points=now_item->getAll_point();
    QList<QPoint> dp=down_item.values();
    for(auto p=points.begin();p!=points.end();p++){
        if((RECT_WIDTH*RECT_COLUMES-p->x())<=RECT_ROWS){//边界碰壁
            return true;
        }
        for(int i=0;i<dp.size();i++){//方块碰壁
            if((p->x()+RECT_WIDTH)>=dp[i].x()&&abs(p->y()-dp[i].y())<RECT_HEIGHT&&p->x()<dp[i].x()){
                return true;
            }
        }
    }
    return false;
}

bool gameview::bottom_col()//是否底部碰壁
{
    QVector<QPoint> points=now_item->getAll_point();
    for(auto p=points.begin();p!=points.end();p++){
        for(auto dp=top_item.begin();dp!=top_item.end();dp++){
            if((p->y()+RECT_HEIGHT)==dp->y()&&p->x()==dp->x()){
                return true;
            }
        }
    }
    return false;
}

bool gameview::top_col()
{
    for(int i=0;i<top_item.size();i++){
        if(top_item[i]==QPoint(-1,-1)||top_item[i].y()==(RECT_ROWS-1)*RECT_HEIGHT){
            continue;
        }
        if(top_item[i].y()==RECT_HEIGHT){
            return true;
        }
    }
    return false;
}

void gameview::move(const QString &button)//移动方块
{
    if(bottom_col()){//方块到底部则不能移动
        return;
    }
    if(button=="left"){//左移
        if(left_col()){
            return;
        }
        now_item->line_move(0);
        repaint();
    }
    else if(button=="right"){//右移
        if(right_col()){
            return;
        }
        now_item->line_move(1);
        repaint();
    }
    else if(button=="down"){//加速下移
        now_item->down_move(1);
        qDebug()<<now_item;
        repaint();
    }
    else if(button=="space"){//直接到底
        while(true){
            if(bottom_col()){
                break;
            }
            now_item->down_move(1);
        }
    }
}

void gameview::update_topitem()
{
    QList<QPoint> list=down_item.values();

    for(int i=0;i<top_item.size();i++){
        if(top_item[i]==QPoint(-1,-1)||top_item[i].y()==(RECT_ROWS-1)*RECT_HEIGHT)
            continue;
        if(!list.contains(top_item[i])){
            int x=i%(RECT_COLUMES-2);
            top_item[i]=QPoint((x+1)*RECT_WIDTH,0);
        }
    }
    for(int i=0;i<list.size();i++){
        bool flag=false;//判断方块正上方是否有方块
        int max_y=list[i].y();
        QPoint pt=list[i];
        for(int j=0;j<list.size();j++){
            if(pt.y()==list[j].y()&&pt.x()==list[j].x())//等于原来的顶部方块
                continue;
            if(((pt.y()-RECT_HEIGHT)==list[j].y())&&pt.x()==list[j].x()){//方块的正上方有方块
                flag=true;
                break;
            }
            if(max_y>list[j].y()&&pt.x()==list[j].x()){
                flag=true;
                break;
            }
        }

        if(!flag){//更新顶部方块
            int x=(pt.x()-RECT_WIDTH)/RECT_WIDTH;
            top_item[x]=pt;
        }

    }
    bool num_topitem=false;//判断是否有中间缝隙方块
    Q_UNUSED(num_topitem);
    for(int i=0;i<top_item.size();i++){
        int num=0;//计算数量
        if(top_item[i]==QPoint(-1,-1)||top_item[i].y()==(RECT_ROWS-1)*RECT_HEIGHT){
            continue;
        }
        topnum_item(top_item[i],num);//计算中间缝隙或底部边界的正上方有几个方块

//        if(num_topitem){//更新中间缝隙方块或底部边界
//            int x=(top_item[i].x()-RECT_WIDTH)/RECT_WIDTH+num*RECT_COLUMES-2;
//            qDebug()<<num<<x;
//            top_item[x]=top_item[i];
//        }
    }
//    foreach (QPoint p, top_item) {
//        if(p!=QPoint(-1,-1))
//            qDebug()<<p;
//    }
}

int gameview::topnum_item(QPoint &pt,int &num)//算最顶端方块正下有几个有缝隙的方块，并加入顶部群
{
    QList<QPoint> list=down_item.values();
    QPoint p(pt.x(),(RECT_ROWS-1)*RECT_HEIGHT);
    for(int j=0;j<list.size();j++){
        if(pt.y()<list[j].y()&&pt.x()==list[j].x()){

            if(!list.contains(list[j]-QPoint(0,RECT_HEIGHT))){
                num++;
                int x=(pt.x()-RECT_WIDTH)/RECT_WIDTH+num*(RECT_COLUMES-2);
//                qDebug()<<x;

                top_item[x]=list[j];
            }
        }

//        if(pt.y()==list[j].y()&&pt.x()==list[j].x())//等于原来的顶部方块
//            continue;
//        for(int i=2;i<=38;i++){
//            if(((pt.y()-RECT_HEIGHT*i)==list[j].y())&&pt.x()==list[j].x()){//判断中间缝隙中的方块正上方有几个方块
//                if(!list.contains(list[j]-QPoint(RECT_HEIGHT,0)))
//                    num++;
//            }
//            QPoint p((i-1)*RECT_WIDTH,(RECT_ROWS-1)*RECT_HEIGHT);
//            if(((p.y()-RECT_HEIGHT*i)==list[j].y())&&p.x()==list[j].x()){//判断底部边界正上方有几个方块
//                if(!list.contains(list[j]-QPoint(RECT_HEIGHT,0)))
//                    num++;
//            }
//        }
    }
    if(!list.contains(p-QPoint(0,RECT_HEIGHT))){
        num++;
        int x=(pt.x()-RECT_WIDTH)/RECT_WIDTH+num*(RECT_COLUMES-2);
//        qDebug()<<pt.x()<<x;

        top_item[x]=p;
    }
    return num;
}

int gameview::clear_downitem(int num)
{
    line_count[num]=0;
    down_item.remove(num);

    QMap<int, int>::Iterator iter;
    QList<int> line=line_count.keys();
    for(int i=0;i<line.size();i++){
        if(line[i]<num){
            QList<QPoint> pts=down_item.values(line[i]);
            down_item.remove(line[i]);
            for(int j=0;j<pts.size();j++){
                QPoint pt=pts[j]+QPoint(0,RECT_HEIGHT);
                down_item.insert(pt.y(),pt);
            }
        }
    }
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
        if(bottom_col()){//方块到底部
            int count=0;
            add_downitem();//把方块加入底部方块群
            QMap<int, int>::Iterator iter;
            for(iter = line_count.begin(); iter != line_count.end(); ++iter)
            {
                if(iter.value()==RECT_COLUMES-2){
                    clear_downitem(iter.key());
                    count+=1;
                }
            }




            update_topitem();
            //游戏结束
            if(top_col()){
                QMessageBox::information(this,"游戏状态","游戏结束！",QMessageBox::Ok);
                delete(now_item);


                //map和vector的清空
                down_item.clear();
                line_count.clear();
                top_item.clear();
                killTimer(time_id);
                //发送游戏结束信号
                emit(is_gameover(true));
                return;
            }
            qDebug()<<"yes";
            now_item=new Item();//重新生成新的方块
        }
        else{
            now_item->down_move(1);
        }
        update();//重绘
    }
}
