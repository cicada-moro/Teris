#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool is_pause=true;

private slots:
    void on_start_clicked();

    void on_restart_clicked();

    void on_pause_clicked();

    void game_over(bool is);
private:
    Ui::MainWindow *ui;

    // QObject interface
public:
    virtual bool eventFilter(QObject *watched, QEvent *event) override;


    // QWidget interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};
#endif // MAINWINDOW_H
