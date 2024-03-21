#include "startscene.h"
#include <QPushButton>
#include "mypushbutton.h"
#include <QTimer>
#include <QSound>

StartScene::StartScene(QWidget *parent) : MyMainWindow(parent)
{
    this->setWindowTitle("Play Game");

    MyPushButton *btnStart = new MyPushButton(":/res/MenuSceneStartButton.png",
                                              ":/res/MenuSceneStartButton.png",this);
    btnStart->resize(114,114);
    // 按钮水平居中，垂直方向在窗口的3/4位置
    btnStart->move((this->width()-btnStart->width())/2, this->height()*3/4-btnStart->height()/2);

    // 第二个窗口的返回按钮被点击
    connect(&this->mSelectScene,&SelectScene::backBtnClicked,[=]()
    {
        QSound::play(":/res/BackButtonSound.wav");

        // 当第二个窗口的返回按钮点击的时候,显示当前窗口，隐藏第二个窗口
        this->show();
        this->mSelectScene.hide();
        this->move(this->mSelectScene.pos());

     });

    // 开始按钮被点击
    connect(btnStart,&MyPushButton::clicked,[=]()
    {
        // 点击开始按钮的音效
        QSound::play(":/res/TapButtonSound.wav");

        // 将按钮设置为不可用
        btnStart->setEnabled(false);
        // 播放向下的动画
        btnStart->moveDown();

        // 播放向上的动画
        // 要等待之前动画播放完再调用
        QTimer::singleShot(150,[=]()  // QTimer的成员函数，延时150ms
        {
            btnStart->moveUp();
        });
        QTimer::singleShot(300,[=]()  // QTimer的成员函数，延时300ms
        {
            // 将按钮设置为可用
            btnStart->setEnabled(true);

            // 场景转换
            // 隐藏当前窗口
            this->hide();
            // 显示第二个窗口
            this->mSelectScene.show();

            // 将窗口移动到当前窗口的位置
            this->mSelectScene.move(this->pos());
        });


    });
}
