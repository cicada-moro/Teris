#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui->centralwidget->setFixedSize(1000,800);
    this->ui->panel->setFixedSize(600,800);
    this->ui->panel->init();
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
}


void MainWindow::on_restart_clicked()
{
    this->ui->restart->setEnabled(false);
    this->ui->pause->setEnabled(true);
    this->ui->start->setEnabled(false);
    this->ui->panel->restart();
}


void MainWindow::on_pause_clicked()
{
    this->ui->start->setEnabled(true);
    this->ui->pause->setEnabled(false);
    this->ui->panel->pause();
}

