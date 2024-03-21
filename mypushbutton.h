#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    enum MyPushButtonStat
    {
        Normal,
        Pressed
    };
    // 修改后的构造函数
    MyPushButton(QString normalImg, QString pressedImg, QWidget *parent = nullptr);

    // 往下和往上的动画函数
    void moveDown();
    void moveUp();

protected:
    void paintEvent(QPaintEvent *ev);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:

private:
    // 正常状态的图片和鼠标按下的图片
    QString mNormalImg;
    QString mPressedImg;
    // 按钮状态
    MyPushButtonStat mStat;
};

#endif // MYPUSHBUTTON_H
