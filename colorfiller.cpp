#include "colorfiller.h"
#include <QPoint>
#include <QRgb>
#include <stdio.h>
#include <QColor>
#include <QtGui/QGuiApplication>

ColorFiller::ColorFiller(QObject *parent) :
	QObject(parent)
{
}

void ColorFiller::fillColor(QImage image, int x, int y) {

	QPoint p(x, y);
	QRgb  black = qRgb(0, 0, 0);
	QRgb rgb = image.pixel(p);
	QRgb color = qRgb(255, 0, 0);

	if (rgb == black) {
		printf("ESCAPED!!!!!!\n");
		return;
	}

	QColor tmp;

	int left = x;
	while (rgb != black && left > 0) {
		image.setPixel(p, color);
		left--;
		p.setX(left);
		rgb = image.pixel(p);
		tmp = QColor(rgb);
	}
}


void ImageProvider::fillColor(int x, int y) {
	//doLeftRight(x, y);
	//doTopBottom(x, y);
    //checkPixel(image.pixel(x, y),x, y);
    fillColorRec(image.pixel(x, y),x,y);
	emit newFrameReceived();
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

void ImageProvider::doLeftRight(int x, int y) {
	QPoint p(x, y);
	QRgb rgb_b = image.pixel(p);
	QRgb  black = qRgb(0, 0, 0);
	QRgb color = qRgb(255, 0, 0);

	QRgb rgb = rgb_b;
	if (rgb == black) {
		printf("ESCAPED!!!!!!\n");
		return;
	}
	printf("Searching for edge...\n");

	QColor tmp;

	int left = x;
	while (rgb != black && left > 0) {
		image.setPixel(p, color);
		left--;
		p.setX(left);
		rgb = image.pixel(p);
		tmp = QColor(rgb);
	}
	rgb = rgb_b;
	int right = x;
	while (rgb != black && right < image.width()) {
		image.setPixel(p, color);
		right++;
		p.setX(right);
		rgb = image.pixel(p);
		tmp = QColor(rgb);
	}
}

void ImageProvider::doTopBottom(int x, int y) {
	QPoint p(x, y);
	QRgb rgb_b = image.pixel(p);
	QRgb rgb = rgb_b;
	QRgb  black = qRgb(0, 0, 0);

	int top = y;
	while (rgb != black && top > 0) {
		top--;
		doLeftRight(x,top);
	}
	rgb = rgb_b;
	int bot = y;
	while (rgb != black && bot < image.height()) {
		bot++;
		doLeftRight(x,bot);
	}
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

