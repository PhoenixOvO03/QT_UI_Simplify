#include "tabel.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>

Tabel::Tabel(QWidget *parent)
    : QTableWidget{parent}
{
    setColumnCount(10); // 设置列数
    setRowCount(20); // 设置行数

    QStringList m_Header;
    m_Header<<QString("序号")<<QString("姓名")<<QString("性别")<<QString("地址");
    setHorizontalHeaderLabels(m_Header); // 添加横向表头

    for(int rows=0;rows<10;rows++)
    {
        for(int columns=0;columns<4;columns++)
        {
            if(columns==0)
            {
                setItem(rows,columns,new QTableWidgetItem("1"));
            }
            else if(columns==1)
            {
                setItem(rows,columns,new QTableWidgetItem("可乐"));
            }
            else if(columns==2)
            {
                setItem(rows,columns,new QTableWidgetItem("女"));
            }
            else
            {
                setItem(rows,columns,new QTableWidgetItem("成都"));
            }
        }
    }

    for(int rows=0;rows<10;rows++)
    {
        for(int columns=0;columns<4;columns++)
        {
            setColumnWidth(columns,125);
            setRowHeight(rows,30);
            item(rows,columns)->setTextAlignment(Qt::AlignCenter);//居中显示
            item(rows,columns)->setFont(QFont("Helvetica"));//设置字体为黑体
        }
    }
}
