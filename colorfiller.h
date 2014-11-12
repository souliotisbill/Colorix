#ifndef COLORFILLER_H
#define COLORFILLER_H

#include <QObject>
#include <QImage>
#include <stdio.h>

#include <QQuickImageProvider>

QT_BEGIN_NAMESPACE


class ImageProvider : public QObject, public QQuickImageProvider
{
	Q_OBJECT
public:
	explicit ImageProvider();

	virtual QImage requestImage(const QString &id, QSize *size, const QSize& requestedSize) {

		if (read) {
			*size = this->image.size();
			return this->image;
		}
		read = true;
		QImage tmpimage(id);
		*size = tmpimage.size();
		this->image = tmpimage;
		return tmpimage;
	}

	Q_INVOKABLE void fillColor(int x, int y);
    Q_INVOKABLE void fillColorRec(QRgb bg,int x, int y);
	void doLeftRight(int x, int y);
	void doTopBottom(int x, int y);
	void checkPixel(QRgb bg,int x, int y);
	bool checkColor(QRgb rgb, QRgb base);

	int windowWidth;
	int windowHeight;
	int imageWidth;
	int imageHeight;
private:
	bool read;
	QImage image;

signals:
	void newFrameReceived();
};

#endif // COLORFILLER_H
