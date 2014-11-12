#ifndef COLORFILLER_H
#define COLORFILLER_H

#include <QObject>
#include <QImage>
#include <stdio.h>

class ColorFiller : public QObject
{
	Q_OBJECT
public:
	explicit ColorFiller(QObject *parent = 0);
	Q_INVOKABLE void fillColor(QImage image, int x, int y);

signals:

public slots:

};



#include <QQuickImageProvider>

QT_BEGIN_NAMESPACE


class ImageProvider : public QObject, public QQuickImageProvider
{
	Q_OBJECT
public:
	explicit ImageProvider() : QQuickImageProvider(QQmlImageProviderBase::Image) {
		read = false;
	}
	virtual QImage requestImage(const QString &id, QSize *size, const QSize& requestedSize) {

		printf("REQUESTING IMAGE.................\n");

		if (read) {
			*size = this->image.size();
			printf("IMAGE EXISTS!!!!!!!!!!!!!!!!!!\n");
			return this->image;
		}
		read = true;
		QImage tmpimage(id);
		*size = tmpimage.size();
		printf("image id: %s size: %d, %d\n", qPrintable(id), tmpimage.size().width(), tmpimage.size().height());
		this->image = tmpimage;
		return tmpimage;

	}

	Q_INVOKABLE void fillColor(int x, int y);
    Q_INVOKABLE void fillColorRec(QRgb bg,int x, int y);
	void doLeftRight(int x, int y);
	void doTopBottom(int x, int y);
	void checkPixel(QRgb bg,int x, int y);
	bool checkColor(QRgb rgb, QRgb base);
private:
	bool read;
	QImage image;

signals:
	void newFrameReceived();
};

#endif // COLORFILLER_H
