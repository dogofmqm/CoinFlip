#include "selectscene.h"
#include <QPushButton>
#include <QPainter>
#include <QMenuBar>
#include "mypushbutton.h"
#include "playscene.h"
#include <QSound>

SelectScene::SelectScene(QWidget *parent) : MyMainWindow(parent)
{
    // 返回按钮
    MyPushButton *btnBack = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png" ,this);
    btnBack->resize(72,32);
    // 信号连接信号
    connect(btnBack,&MyPushButton::clicked,this,&SelectScene::backBtnClicked);

    btnBack->move(this->width()-btnBack->width(),this->height()-btnBack->height());

    // 创建关卡按钮20个
    const int colWidth = 70;
    const int rowHeight = 70;
    // x,y偏移量
    const int xOffset = 25;
    const int yOffset = 130;
    for(int i =0; i<20;i++)
    {
        // 当界面有任何改动的时候，都会调用paintEvent()函数
        MyPushButton *btn = new MyPushButton(":/res/LevelIcon.png",":/res/LevelIcon.png",this);
        btn->setText(QString::number(i+1));
        // 排列
        // 行 i / 4
        // 列 i % 4
        int row = i / 4;
        int col = i%4;
        // x 坐标 = 列数 * 列宽 + x偏移
        // y 坐标 = 行数 * 行高 + y偏移
        int x = col * colWidth + xOffset;
        int y = row * rowHeight + yOffset;
        btn->resize(57,57);
        btn->move(x,y);
        connect(btn,&MyPushButton::clicked,[=]()
        {
            // 添加点击按钮的音效
            QSound::play(":/res/TapButtonSound.wav");

            // 点击关卡按钮后打开一个新的场景PlayScene
            PlayScene *playScene = new PlayScene(i+1);
            // 设置playScene窗口关闭的时候自动释放
            playScene->setAttribute(Qt::WA_DeleteOnClose);

            playScene->move(this->pos());

            playScene->show();
            this->hide();

            connect(playScene,&PlayScene::backBtnClicked,[=]()
            {
                // 怎么通过任务管理器查看有没有内存泄漏：
                // 运行程序，每次点击一个按钮，任务管理器中的内存如果增加，则说明内存存在泄露

                QSound::play(":/res/BackButtonSound.wav");

                this->move(playScene->pos());

                this->show();
                //playScene->hide();
                // 这里不能使用hide，因为窗口关闭的话，setAttribute(Qt::WA_DeleteOnClose)这个函数会释放窗口
                playScene->close();
            });

        });

    }

}

void SelectScene::paintEvent(QPaintEvent *event)
{
    // 绘制背景图片
    QPainter painter(this);
    // 搬动画家到菜单栏下面
    painter.translate(0,this->menuBar()->height());
    // 画背景图
    QPixmap pix(":/res/OtherSceneBg.png");
    painter.drawPixmap(rect(),pix);
    // 画logo图
    pix.load(":/res/Title.png");
    painter.drawPixmap(0,0,pix);
}
