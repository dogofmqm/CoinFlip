#include "coinbutton.h"
#include <QPainter>

CoinButton::CoinButton(QWidget *parent) : QPushButton(parent)
{
    // 初始状态设置为银币
    this->setStat(0);

    // 设置按钮不规则样式，就是去掉边框
    this->setStyleSheet("QPushButton{border:0px;}");

    // 动画定时器信号和槽的实现
    connect(&this->mTimer,&QTimer::timeout,[=]()
    {
        if(this->mStat)
        {
            //  mStat == 1, 银币翻金币
            this->mFrame--;
        }
        else
        {
            // mStat == 0,金币翻银币
            this->mFrame++;
        }

        // 加载相应帧的图片
        QString frameName = QString(":/res/Coin000%1.png").arg(this->mFrame);
        this->setIcon(QIcon(frameName));
        // 动画结束，停止计时器
        if(this->mFrame==8 || this->mFrame == 1)
        {
            this->mTimer.stop();
        }
    });

}

int CoinButton::stat() const
{
    return mStat;
}

void CoinButton::setStat(int stat)
{
    mStat = stat;
    if(this->mStat)
    {
        this->setIcon(QIcon(":/res/Coin0001.png"));
    }
    else
    {
        this->setIcon(QIcon(":/res/Coin0008.png"));
    }
    // 设置icon大小
    this->setIconSize(this->size());

}

// setStat带动画的函数
void CoinButton::setStatWithAnimation(int stat)
{
    this->mStat = stat;
    if(this->mStat)
    {
        // mStat == 1,表示银币翻转成金币
        this->mFrame = 8;
    }
    else
    {
        // 金币翻银币的过程
        this->mFrame = 1;

    }
    this->mTimer.start(35);

}
// 硬币反转函数
void CoinButton::flip()
{
    // this->setStat(!this->stat());
    this->setStatWithAnimation(!this->stat());
}

void CoinButton::paintEvent(QPaintEvent *ev)
{
    // 绘制按钮的图片
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/BoardNode.png");

    painter.drawPixmap(rect(), pix);

    // 调用父类的painEvent,将金币给画出来
    QPushButton::paintEvent(ev);
}
