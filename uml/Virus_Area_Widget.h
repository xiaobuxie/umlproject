#ifndef VIRUS_AREA_H
#define VIRUS_AREA_H

#include <QWidget>
#include <QObjectUserData>
#include <QStandardItemModel>
#include <QStyledItemDelegate>
#include <QModelIndex>
#include <QSortFilterProxyModel>

struct Virus_Area_Item {
    QString area_name;
    int     area_existing;
    int     area_total;
    int     area_dead;
    int     area_cure;
    Virus_Area_Item();
    Virus_Area_Item(QString, int, int, int, int);
};
Q_DECLARE_METATYPE(Virus_Area_Item)

class Virus_Area_Delegate : public QStyledItemDelegate
{
    Q_OBJECT
signals:

public:
    explicit Virus_Area_Delegate(QObject* parent = Q_NULLPTR);
    ~Virus_Area_Delegate();

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const;
};

namespace Ui { class Virus_Area_Widget; };

class Virus_Area_Widget : public QWidget
{
    Q_OBJECT

public:
    Virus_Area_Widget(QWidget *parent = Q_NULLPTR);
    ~Virus_Area_Widget();
    void initData();

private:
    Ui::Virus_Area_Widget *ui;
    QStandardItemModel    *area_model;
    Virus_Area_Delegate   *area_delegate;
};

#endif // VIRUS_AREA_H
