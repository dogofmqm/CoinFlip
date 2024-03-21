#include "mypushbutton.h"
#include <QPainter>
#include <QPropertyAnimation>

MyPushButton::MyPushButton(QString normalImg, QString pressedImg, QWidget *parent)
    : QPushButton(parent)
    // 用参数列表将构造参数normalImg传入到成员变量
    , mNormalImg(normalImg)
    , mPressedImg(pressedImg)
{
    mStat=Normal;
}

void MyPushButton::moveDown()
{
    // 位置大小属性发生变化
    // 给定开始位置的大小属性
    // 给定结束位置的大小属性
    // 给定速度，就是给定动画时长
    // QPropertyAnimation 属性动画

    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry",this);
    // 设置按钮开始的位置
    animation->setStartValue(this->geometry());
    // 设置按钮结束的位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    // 动画持续的时间
    animation->setDuration(100); // 100ms

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MyPushButton::moveUp()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry",this);
    // 设置按钮开始的位置
    animation->setStartValue(this->geometry());
    // 设置按钮结束的位置
    animation->setEndValue(QRect(this->x(),this->y()-10,this->width(),this->height()));
    // 动画持续的时间
    animation->setDuration(100); // 100ms

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MyPushButton::paintEvent(QPaintEvent *ev)
{
    // 绘制按钮的图片
    QPainter painter(this);
    QPixmap pix;
    if(mStat == Normal)
    {
        pix.load(mNormalImg);
    }
    if(mStat == Pressed)
    {
        pix.load(mPressedImg);
    }

    painter.drawPixmap(rect(), pix);

    // 绘制按钮的文字 文字居中 Qt::AlignHCenter|Qt::AlignVCenter
    painter.drawText(0,0,this->width(),this->height()
                     ,Qt::AlignHCenter|Qt::AlignVCenter,this->text());
}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    // 先调用父类的mousePressEvent，保证信号和槽能够发送
    QPushButton::mousePressEvent(e);
    // 鼠标按下的时候状态切换到Pressed
    this->mStat = Pressed;
    update();

}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    // 保证信号和槽能够发送
    QPushButton::mouseReleaseEvent(e);
    // 鼠标按下的时候状态切换到Normal
    this->mStat = Normal;
    update();
}
