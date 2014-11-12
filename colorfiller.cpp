#include "colorfiller.h"
#include <QPoint>
#include <QRgb>
#include <stdio.h>
#include <QColor>
#include <QtGui/QGuiApplication>


ImageProvider::ImageProvider() : QQuickImageProvider(QQmlImageProviderBase::Image)
{
	read = false;
    m_windowWidth = 1;
    m_windowHeight = 1;
    m_imageWidth = 1;
    m_imageHeight = 1;
}

void ImageProvider::fillColor(int x, int y)
{
    y -= (m_windowHeight - m_imageHeight) / 2;
    x = x * image.width() / m_imageWidth;
    y = y * image.height() / m_imageHeight;

    printf("image size: %d, %d (x, y): %d, %d\n", image.width(), image.height(), x, y);
    printf("image size: %d, %d (x, y): %d, %d\n", m_windowHeight, m_windowWidth, m_imageHeight, m_imageWidth);

    checkPixel(image.pixel(x, y),x, y);
	//fillColorRec(image.pixel(x, y),x,y);
	emit newFrameReceived();
}

void ImageProvider::setWindowWidth(int ww)
{
    m_windowWidth = ww;
}

void ImageProvider::setWindowHeight(int wh)
{
    m_windowHeight = wh;
}

void ImageProvider::setImageWidth(int iw)
{
    m_imageWidth = iw;
}

void ImageProvider::setImageHeight(int ih)
{
    m_imageHeight = ih;
}

bool ImageProvider::checkColor(QRgb rgb, QRgb base) {
    if (qRed(rgb) < qRed(base) + 5 && qRed(rgb) > qRed(base) - 5 &&
        qGreen(rgb) < qGreen(base) + 5 && qGreen(rgb) > qGreen(base) - 5 &&
        qBlue(rgb) < qBlue(base) + 5 && qBlue(rgb) > qBlue(base) - 5)
        return true;
    return false;
}

void ImageProvider::checkPixel(QRgb bg,int x, int y) {

    if (x < 1 || x > image.width()-1 || y < 1 || y > image.height()-1) return;
	QRgb  black = qRgb(0, 0, 0);
	QRgb rgb = image.pixel(x, y);
	QRgb color = qRgb(255, 0, 0);

	if (checkColor(rgb, black)) return;

	if (checkColor(rgb, color)) return;

	if (!checkColor(rgb, bg)) return;

	image.setPixel(x, y, color);

	checkPixel(bg,x+1, y);
	checkPixel(bg,x-1, y);
	checkPixel(bg,x, y+1);
	checkPixel(bg,x, y-1);
}

void ImageProvider::fillColorRec(QRgb bg,int x, int y) {
	QPoint p(x, y);
	QRgb rgb_b = image.pixel(p);
	QRgb color = qRgb(255, 0, 0);
	QRgb rgb = rgb_b;
    if (!checkColor(rgb, bg)) return;

	int left = x;
    while (checkColor(rgb, bg) && left > 0) {
		image.setPixel(p, color);
		left--;
		p.setX(left);
		rgb = image.pixel(p);
	}
	left++;
	rgb = rgb_b;
	int right = x;
    while (checkColor(rgb, bg) && right < image.width()) {
		image.setPixel(p, color);
		right++;
		p.setX(right);
		rgb = image.pixel(p);
	}
	right--;

    //Recursive
    int ii;
    //printf("left =%d, right=%d\n",left,right);
    for(ii = left; ii <= right; ii++) {
        //printf("ii =%d, y=%d\n",ii,y);
        if(y-1>0&&checkColor(image.pixel(ii,y-1), bg)) fillColorRec(image.pixel(ii,y-1),ii,y-1);
        if(y+1<image.height()&&checkColor(image.pixel(ii,y+1), bg)) fillColorRec(image.pixel(ii,y+1),ii,y+1);
    }
}

