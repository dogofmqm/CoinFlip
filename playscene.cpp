#include "playscene.h"
#include "mypushbutton.h"
#include <QPainter>
#include <QMenuBar>
#include <QLabel>
#include "coinbutton.h"
#include "dataconfig.h"
#include <QMessageBox>
#include <QLabel>
#include <QPropertyAnimation>
#include <QSound>

PlayScene::PlayScene(int level,QWidget *parent) : MyMainWindow(parent)
{
    // 默认胜利状态是false
    mHasWin = false;

    // 返回按钮
    MyPushButton *btnBack = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png" ,this);
    btnBack->resize(72,32);
    // 信号连接信号
    connect(btnBack,&MyPushButton::clicked,this,&PlayScene::backBtnClicked);

    btnBack->move(this->width()-btnBack->width(),this->height()-btnBack->height());

    // 添加左下角的label
    QLabel *label = new QLabel(this);
    label->setText(QString("level: %1").arg(level));
    label->resize(150,50);
    // 设置字体和字体大小
    label->setFont(QFont("华文新魏", 20));
    // 移动到左下角
    label->move(30,this->height()-label->height());

    const int colWidth = 50;
    const int rowHeight = 50;
    const int xOffset = 57;
    const int yOffset = 200;

    // 取出第几关的二维数组数据
    dataConfig data;
    QVector <QVector<int>> dataArray = data.mData[level];

    // 16个硬币按钮
    for(int row=0;row<4; ++row)
    {
        for(int col = 0;col<4;++col)
        {
            CoinButton *btn = new CoinButton(this);
            // 存储按钮到第几行第几列
            mCoins[row][col] = btn;

            // x 坐标 = 列数 * 列宽 + x偏移
            // y 坐标 = 行数 * 行高 + y偏移
            int x = col * colWidth + xOffset;
            int y = row * rowHeight + yOffset;
            // setGeometry 就是设置 位置坐标和行宽列高
            btn->setGeometry(x,y,50,50);

            // 设置row行col列的值，从dataConfig的数据中获取
            btn->setStat(dataArray[row][col]);


            connect(btn,&CoinButton::clicked,[=]()
            {
                // 每次点击硬币的时候就改变状态，状态置反
                // btn->flip();
                this->flip(row,col);
            });
        }
    }
}

void PlayScene::flip(int row, int col)
{
    // 如果胜利了就直接返回
    if(mHasWin)
    {
        return;
    }
    this->mCoins[row][col]->flip();

    // 翻金币的音效
    QSound::play(":/res/ConFlipSound.wav");

    // 延时翻动上下左右硬币
    QTimer::singleShot(200,[=]()
    {
        // 翻动上下左右的硬币
        // 下一行的硬币
        if(row+1<4)
        {
            this->mCoins[row+1][col]->flip();
        }

        // 上一行的硬币
        if(row-1>=0)
        {
            this->mCoins[row-1][col]->flip();
        }

        // 左边的硬币
        if(col-1>=0)
        {
            this->mCoins[row][col-1]->flip();
        }

        // 右边的硬币
        if(col+1<4)
        {
            this->mCoins[row][col+1]->flip();
        }

        // 判断游戏是否胜利
        this->judegeWin();
    });


}

void PlayScene::judegeWin()
{
    // 16个硬币按钮状态判断都是1
    for(int row=0;row<4; ++row)
    {
        for(int col = 0;col<4;++col)
        {
            // 判断某个硬币是银币
            if(!this->mCoins[row][col]->stat())
            {
                // 只要有一个是银币，就返回，游戏继续
                return;
            }
        }
    }

    // 所有都是金币的情况下游戏结束
    //QMessageBox::information(this,"游戏胜利","你真是个大聪明！！！");
    mHasWin = true;

    // 播放胜利音效
    QSound::play(":/res/LevelWinSound.wav");

    // 播放胜利动画
    QLabel *labelWin = new QLabel(this);
    QPixmap pix = QPixmap(":/res/LevelCompletedDialogBg.png");
    // 这样也行  QPixmap pix(":/res/LevelCompletedDialogBg.png");

    // setPixmap函数是QLabel的槽函数，原型是 void setPixmap(const QPixmap &)
    labelWin->setPixmap(pix);
    labelWin->resize(pix.size());
    labelWin->show();
    labelWin->move((this->width()-labelWin->width())/2,-labelWin->height());

    QPropertyAnimation *animation = new QPropertyAnimation(labelWin,"geometry",this);
    animation->setStartValue(labelWin->geometry());
    animation->setEndValue(QRect(labelWin->x(),labelWin->y()+107.5,labelWin->width(),labelWin->height()));
    animation->setDuration(1000);
    // 设置动画的运动曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //动画播放完后自动删除动画对象
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void PlayScene::paintEvent(QPaintEvent *event)
{
    // 绘制背景图片
    QPainter painter(this);
    // 搬动画家到菜单栏下面
    painter.translate(0,this->menuBar()->height());
    // 画背景图
    QPixmap pix(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(rect(),pix);
    // 画logo图
    pix.load(":/res/Title.png");
    // 缩小logo
    pix = pix.scaled(pix.width()/2,pix.height()/2);
    painter.drawPixmap(0,0,pix);
}
