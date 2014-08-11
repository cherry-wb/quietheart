#ifndef __MYLIST_H
#define __MYLIST_H
#include <QWidget>
#include <QLabel>
#include <QPainter>
class MyListItem:public QWidget
{
	Q_OBJECT
	public:
	MyListItem(const QString &filePath, const QString &text, 
		const QString &count, QWidget *parent = 0):
		QWidget(parent)
	{
		//init widgets
		iconLabel = new QLabel("",this);
		iconLabel->setPixmap(QPixmap(filePath));

		textLabel = new QLabel(text, this);

		countLabel = new QLabel(count, this);

		//do layouts
		updateLayout();
	}

	void setIcon(QString &filePath)
	{
		iconLabel->setPixmap(QPixmap(filePath));
	}
	void setCount(QString &count)
	{
		countLabel->setText(count);
	}
	void setText(QString &text)
	{
		textLabel->setText(text);
	}

	QString text() const
	{
		return textLabel->text();
	}

	signals:
	void clicked(MyListItem *item);

	protected:
	void mousePressEvent(QMouseEvent *)
	{
		emit clicked(this);
	}

	virtual void showEvent(QShowEvent *)
	{
		updateLayout();
	}

	void paintEvent(QPaintEvent *)
	{
		//under line
		QPainter painter(this);
		QLine line(textLabel->geometry().bottomLeft(),
			countLabel->geometry().bottomRight());
		painter.drawLine(line);
	}

	private:
	void updateLayout()
	{
		//do layouts
		if(iconLabel && textLabel && countLabel)
		{
			iconLabel->setGeometry(0,0,width()>>3,height());
			textLabel->setGeometry(width()>>3,0,(width()*3)>>2,height());
			countLabel->setGeometry(width() - (width()>>3),0,width()>>3,height());
		}
	}
	
	private:
	QLabel *iconLabel;
	QLabel *textLabel;
	QLabel *countLabel;
};

#define MY_TITLEHEIGHT 20
#define MY_LISTCOUNT 8
class MyListItem;
class MyList:public QWidget
{
	Q_OBJECT
	public:
	MyList(QWidget *parent = 0, Qt::WindowFlags f = Qt::FramelessWindowHint);

	void appentItem(MyListItem *item = 0);

	int iCount()const;

	public slots:
	void clickResponse(MyListItem *item);

	private:
	int itemCount;
};
#endif
