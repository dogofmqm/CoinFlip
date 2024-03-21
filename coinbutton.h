#ifndef COINBUTTON_H
#define COINBUTTON_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QTimer>

class CoinButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CoinButton(QWidget *parent = nullptr);

    int stat() const;
    void setStat(int stat);

    // setStat带动画的函数
    void setStatWithAnimation(int stat);

    // 硬币反转函数
    void flip();

    // 记录当前动画帧数
    int mFrame;
    // 定时器
    QTimer mTimer;

signals:

protected:
    void paintEvent(QPaintEvent *ev);

private:
    // 硬币状态：0表示银币 1表示金币
    int mStat; // alt + 回车：会出现上述stat()和setStat代码


};

#endif // COINBUTTON_H
