#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameview.h"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui->centralwidget->setFixedSize(1000,800);
    this->ui->panel->setFixedSize(600,800);
    this->move(250,0);
    setFocusPolicy(Qt::StrongFocus);
//    this->ui->panel->installEventFilter(this);
    this->ui->panel->init();

    connect(this->ui->panel,SIGNAL(is_gameover(bool)),this,SLOT(game_over(bool)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_start_clicked()
{
    this->ui->restart->setEnabled(true);
    this->ui->pause->setEnabled(true);
    this->ui->start->setEnabled(false);
    this->ui->panel->begin();
    is_pause=false;
}


void MainWindow::on_restart_clicked()
{
    this->ui->pause->setEnabled(true);
    this->ui->start->setEnabled(false);
    this->ui->panel->restart();
    is_pause=false;
}


void MainWindow::on_pause_clicked()
{
    this->ui->start->setEnabled(true);
    this->ui->pause->setEnabled(false);
    this->ui->panel->pause();
    is_pause=true;
}

void MainWindow::game_over(bool is)
{
    if(is){
        this->ui->start->setEnabled(true);
        this->ui->pause->setEnabled(false);
        this->ui->restart->setEnabled(false);
        this->ui->panel->init();
    }
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched==this->ui->panel){
        if(event->type()!=QEvent::KeyPress){
            return false;
        }
        QKeyEvent *key_event=static_cast<QKeyEvent *>(event);
        if(key_event->key()==Qt::Key_Left){
            qDebug()<<1;
            this->ui->panel->move("left");
        }
        else if(key_event->key()==Qt::Key_Right){
            this->ui->panel->move("right");
        }
        else if(key_event->key()==Qt::Key_Down){
            this->ui->panel->move("down");
        }
        else if(key_event->key()==Qt::Key_Space){
            this->ui->panel->move("space");
        }
        return true;
    }
    else
        return false;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(is_pause==true){
        event->ignore();
        return;
    }
    if(event->key()==Qt::Key_Left){
        qDebug()<<1;
        this->ui->panel->move("left");
    }
    else if(event->key()==Qt::Key_Right){
        qDebug()<<is_pause;
        this->ui->panel->move("right");
    }
    else if(event->key()==Qt::Key_Down){
        this->ui->panel->move("down");
    }
    else if(event->key()==Qt::Key_Space){
        this->ui->panel->move("space");
    }
}

