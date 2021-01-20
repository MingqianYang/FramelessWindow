// qframelesswidget.cpp
#include "qframelesswidget.h"
#include <QPushButton>
#include <QLabel>
#include <QIcon>
#include <QStyle>
#include <QVBoxLayout>

#define BTNSIZE 30

QFramelessWidget::QFramelessWidget(QString icon, QString title, QWidget *parent)
    :m_icon(icon),m_title(title),QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint |Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    initWindowTitle (); // 初始化窗体
    setIcon (m_icon);// 设置图标
    setTittle (m_title);// 设置标题
    hasBackgroundImage = false; // 默认无背景图片
}

QFramelessWidget::~QFramelessWidget(){}

void QFramelessWidget::setIcon(QString icon){
    QPixmap pixmap(icon);
    m_label->setPixmap (pixmap);
    m_label->setScaledContents(true);
}
void QFramelessWidget::setTittle(QString tittle){
     m_titlelabel->setText (tittle);
}

void QFramelessWidget::setBackgroundImage(QString filename)
{
    hasBackgroundImage = true;

    image.load (filename);
    setAutoFillBackground (true);
    QPalette pal(palette());
    pal.setBrush(QPalette::Window,
                 QBrush(image.scaled(size(), Qt::IgnoreAspectRatio,
                                     Qt::SmoothTransformation)));
    setPalette(pal);
}

void QFramelessWidget::initWindowTitle()
{
    this->resize (500,300); /// 默认设置大小为500*300
    minOrNormal = true; /// 默认显示普通大小窗体
    titleWidget = new QWidget(this);
    m_minOrNormalPushBtn = new QPushButton(titleWidget);
    m_maxPushBtn = new QPushButton(titleWidget);
    m_closePushBtn = new QPushButton(titleWidget);
    m_label = new QLabel(titleWidget);
    m_titlelabel = new QLabel(titleWidget);
    centerwidget = new QWidget(this); /// 主窗体，所有继承于QFramelessWidget的子类，其父对象为centerwidget
    /// 设置布局器
    QVBoxLayout* vlayout = new QVBoxLayout(this);
    vlayout->addWidget (titleWidget);
    vlayout->addWidget (centerwidget);
    this->setLayout (vlayout);
    /// 设置控件位置和风格样式
    setThisLayout ();
    setThisStyle ();

    connect (m_closePushBtn,SIGNAL(clicked(bool)),SLOT(onClose(bool)));
    connect (m_maxPushBtn,SIGNAL(clicked(bool)),SLOT(onMax(bool)));
    connect (m_minOrNormalPushBtn,SIGNAL(clicked(bool)),SLOT(onMin(bool)));
}

void QFramelessWidget::setThisStyle(){
    /// 默认为扁平风格
    m_closePushBtn->setFlat(true);
    m_minOrNormalPushBtn->setFlat(true);
    m_maxPushBtn->setFlat (true);

    m_closePushBtn->setStyleSheet("QPushButton{border-style: none/*;border-top-right-radius:5px*/}"
                                  "QPushButton:hover{background-color:red;color: white;}"
                                  "QPushButton:pressed{background-color:rgba(85, 170, 255,200); border-style: inset; }");
    m_minOrNormalPushBtn->setStyleSheet("QPushButton{border-style: none;}"
                                        "QPushButton:hover{background-color:lightgray; color: white;}"
                                        "QPushButton:pressed{background-color:rgb(85, 170, 255); border-style: inset; }");
    m_maxPushBtn->setStyleSheet("QPushButton{border-style: none;}"
                                "QPushButton:hover{background-color:lightgray; color: white;}"
                                "QPushButton:pressed{background-color:rgb(85, 170, 255); border-style: inset; }");


    m_closePushBtn->setCursor(Qt::PointingHandCursor);
    m_maxPushBtn->setCursor(Qt::PointingHandCursor);
    m_minOrNormalPushBtn->setCursor(Qt::PointingHandCursor);
    QIcon icon;
    if( minOrNormal ){/// true means normal
        /// normal时显示最小化图标
        icon = style()->standardIcon( QStyle::SP_TitleBarMinButton );
        m_minOrNormalPushBtn->setIcon( icon );
        m_minOrNormalPushBtn->setToolTip(QObject::tr("Min"));

        icon = style()->standardIcon (QStyle::SP_TitleBarMaxButton);
        m_maxPushBtn->setIcon( icon );
        m_maxPushBtn->setToolTip(QObject::tr("Max"));
    }
    icon = style()->standardIcon( QStyle::SP_TitleBarCloseButton );
    m_closePushBtn->setIcon( icon );
    m_closePushBtn->setToolTip(QObject::tr("Quit"));
}

void QFramelessWidget::setThisLayout(){
    centerwidget->setGeometry (0,BTNSIZE,width (),height ()-BTNSIZE);
    titleWidget->setGeometry (0,0,width (),BTNSIZE);
    m_label->setGeometry (0,0,BTNSIZE,BTNSIZE);
    m_titlelabel->setGeometry (BTNSIZE+5,0,titleWidget->width ()-4*BTNSIZE -5,BTNSIZE);
    m_closePushBtn->setGeometry (titleWidget->width () - BTNSIZE,0,BTNSIZE,BTNSIZE);
    m_maxPushBtn->setGeometry (titleWidget->width () - 2*BTNSIZE,0,BTNSIZE,BTNSIZE);
    m_minOrNormalPushBtn->setGeometry (titleWidget->width () - 3*BTNSIZE,0,BTNSIZE,BTNSIZE);
}


void QFramelessWidget::mousePressEvent(QMouseEvent *event)
{
    this->windowPos = this->pos();           // 获得部件当前位置
    this->mousePos = event->globalPos();     // 获得鼠标位置
    this->dPos = mousePos - windowPos;       // 移动后部件所在的位置
}

void QFramelessWidget::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos() - this->dPos);
}

void QFramelessWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    /// 控件位置调整
    setThisLayout ();

    /// 背景图片缩放
    if(hasBackgroundImage){
        QPalette pal(palette());
        pal.setBrush(QPalette::Window,QBrush(image.scaled(event->size(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
        setPalette(pal);
    }
}

void QFramelessWidget::onMin(bool)
{
    if( windowState() != Qt::WindowMinimized ){
        setWindowState( Qt::WindowMinimized );
    }
}

void QFramelessWidget::onMax(bool)
{
    if( windowState() != Qt::WindowMaximized ){
        setWindowState( Qt::WindowMaximized );
    }else{
        setWindowState( Qt::WindowNoState );
    }
}

void QFramelessWidget::onClose(bool)
{
    emit close();
}

