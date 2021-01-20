// qframelesswidget.h
#ifndef QFRAMELESSWIDGET_H
#define QFRAMELESSWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QString>

class QPushButton;
class QLabel;
class QFramelessWidget : public QWidget
{
    Q_OBJECT
public:
    QFramelessWidget(QString icon = "",QString title = QString("qFramelseewidget"),QWidget *parent = 0);
    virtual ~QFramelessWidget();
private slots:
    void onMin( bool );
    void onMax(bool);
    void onClose( bool );
private:
    bool minOrNormal;//true表示当前窗口状态为normal，图标应显示为max
public:
    QPushButton* m_minOrNormalPushBtn; // 显示最大或者最小的图标
    QPushButton* m_maxPushBtn; // 最大化按钮
    QPushButton* m_closePushBtn;// 关闭按钮
    QLabel* m_label; // 图标
    QString m_icon; // m_label中图标路径
    QLabel* m_titlelabel; // 标题
    QString m_title;
    QWidget* titleWidget;
    QWidget* centerwidget;
    QImage image; // 背景图片
public:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent* event);
    /// 窗体移动事件的点
    QPoint windowPos;
    QPoint mousePos;
    QPoint dPos;
public:
    void setBackgroundImage(QString filename); // 设置背景图片
    bool hasBackgroundImage;
    void setIcon(QString icon); // 设置图标
    void setTittle(QString tittle); // 设置标题
protected:
    void initWindowTitle();
    void setThisLayout();
    void setThisStyle();
};

#endif // QFRAMELESSWIDGET_H

