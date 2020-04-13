#include <QPainter>
#include <QStyledItemDelegate>
#include <QStyle>
#include <QEvent>
#include <QDebug>
#include <QString>
#include "Virus_Area_Widget.h"
#include "ui_Virus_Area_Widget.h"

Virus_Area_Item::Virus_Area_Item()
{
}

Virus_Area_Item::Virus_Area_Item(QString _name, int _total, int _existing, int _dead, int _cure)
    : area_name(_name)
    , area_existing(_existing)
    , area_total(_total)
    , area_dead(_dead)
    , area_cure(_cure)
{
}

Virus_Area_Delegate::Virus_Area_Delegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}
Virus_Area_Delegate::~Virus_Area_Delegate()
{
}
void Virus_Area_Delegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if (index.isValid()) {
        painter->save();

        QVariant variant = index.data(Qt::UserRole);
        Virus_Area_Item data = variant.value<Virus_Area_Item>();

        QRectF rect;
        rect.setX(option.rect.x());
        rect.setY(option.rect.y());
        rect.setWidth(option.rect.width() - 1.0);
        rect.setHeight(option.rect.height() - 1.0);

        //QPainterPath画圆角矩形
        const qreal radius = 7;
        QPainterPath path;
        path.moveTo(rect.topRight() - QPointF(radius, 0));
        path.lineTo(rect.topLeft() + QPointF(radius, 0));
        path.quadTo(rect.topLeft(), rect.topLeft() + QPointF(0, radius));
        path.lineTo(rect.bottomLeft() + QPointF(0, -radius));
        path.quadTo(rect.bottomLeft(), rect.bottomLeft() + QPointF(radius, 0));
        path.lineTo(rect.bottomRight() - QPointF(radius, 0));
        path.quadTo(rect.bottomRight(), rect.bottomRight() + QPointF(0, -radius));
        path.lineTo(rect.topRight() + QPointF(0, radius));
        path.quadTo(rect.topRight(), rect.topRight() + QPointF(-radius, -0));
        if (option.state.testFlag(QStyle::State_Selected)) //选中状态
        {
            painter->setPen(QPen(Qt::red));
            painter->setBrush(Qt::red);
            painter->drawPath(path);
        }
        else if (option.state.testFlag(QStyle::State_MouseOver))//鼠标划过状态
        {
            painter->setPen(QPen(Qt::red));
            painter->setBrush(Qt::NoBrush);
            painter->drawPath(path);
        }
        else {
            painter->setPen(QPen(Qt::gray));
            painter->setBrush(Qt::NoBrush);
            painter->drawPath(path);
        }

        //绘制数据位置
        QRect nameRect     = QRect(int(rect.left() + rect.width()*0/5 + 10), int(rect.top() + 10), int(rect.width()/5), 25);
        QRect existingRect = QRect(int(rect.left() + rect.width()*1/5 + 10), int(rect.top() + 10), int(rect.width()/5), 25);
        QRect totalRect    = QRect(int(rect.left() + rect.width()*2/5 + 10), int(rect.top() + 10), int(rect.width()/5), 25);
        QRect deadRect     = QRect(int(rect.left() + rect.width()*3/5 + 10), int(rect.top() + 10), int(rect.width()/5), 25);
        QRect cureRect     = QRect(int(rect.left() + rect.width()*4/5 + 10), int(rect.top() + 10), int(rect.width()/5), 25);

        painter->setPen(QPen(Qt::black));
        painter->setFont(QFont("Consolas", 14, QFont::Bold));
        painter->drawText(nameRect, Qt::AlignLeft, data.area_name);

        painter->setPen(QPen(Qt::black));
        painter->setFont(QFont("Times", 14));
        painter->drawText(existingRect, Qt::AlignLeft, QString::number(data.area_existing));

        painter->setPen(QPen(Qt::black));
        painter->setFont(QFont("Times", 14));
        painter->drawText(totalRect, Qt::AlignLeft, QString::number(data.area_total));

        painter->setPen(QPen(Qt::black));
        painter->setFont(QFont("Times", 14));
        painter->drawText(deadRect, Qt::AlignLeft, QString::number(data.area_dead));

        painter->setPen(QPen(Qt::black));
        painter->setFont(QFont("Times", 14));
        painter->drawText(cureRect, Qt::AlignLeft, QString::number(data.area_cure));

        painter->restore();
    }
}

QSize Virus_Area_Delegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    Q_UNUSED(index)
    return QSize(option.rect.width(), 50);
}

Virus_Area_Widget::Virus_Area_Widget(QWidget* parent)
    : QWidget(parent)
{
    ui = new Ui::Virus_Area_Widget();
    ui->setupUi(this);

    initData();

    area_delegate = new Virus_Area_Delegate(this);
    ui->lvw_area->setItemDelegate(area_delegate);
    ui->lvw_area->setModel(area_model);
    ui->lvw_area->setSpacing(5);
    ui->lvw_area->setDragEnabled(false);
}

Virus_Area_Widget::~Virus_Area_Widget()
{
    delete ui;
    delete area_model;
    delete area_delegate;
}

//数据接入模块
void Virus_Area_Widget::initData()
{
    QStringList area_name_model;
    area_name_model.push_back(tr("中国"));
    area_name_model.push_back(tr("广州"));
    ui->cbx_area->addItems(area_name_model);
    area_model = new QStandardItemModel(100, 1);
    int i = 0;
    for (int j = 0; j < 100; j++) {
        area_model->setData(area_model->index(i, 0), QVariant::fromValue(Virus_Area_Item(QString::number(j), j, j, j, j)), Qt::UserRole);
        i++;
    }
    qDebug() << " Hotspot_Detail_Widget" << "\n";
}
