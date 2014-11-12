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
    Q_INVOKABLE void setWindowWidth(int ww);
    Q_INVOKABLE void setWindowHeight(int wh);
    Q_INVOKABLE void setImageWidth(int iw);
    Q_INVOKABLE void setImageHeight(int ih);

	void checkPixel(QRgb bg,int x, int y);
	bool checkColor(QRgb rgb, QRgb base);

    int m_windowWidth;
    int m_windowHeight;
    int m_imageWidth;
    int m_imageHeight;
private:
	bool read;
	QImage image;

signals:
	void newFrameReceived();
};

#endif // COLORFILLER_H
