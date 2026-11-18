
#ifndef DIYAWIDGET_H
#define DIYAWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QLinearGradient>
#include <QRadialGradient>
#include "DiyaWidget.h"

class DiyaWidget : public QWidget
{
public:
    explicit DiyaWidget(QWidget *parent = nullptr)
        : QWidget(parent), isLit(false)
    {
        setFixedSize(220, 220);
        setCursor(Qt::PointingHandCursor);
        setToolTip("Click the diya to light it!");
    }

protected:

    void mousePressEvent(QMouseEvent *event) override
    {
        Q_UNUSED(event);

        isLit = !isLit;
        update();
    }

    void paintEvent(QPaintEvent *) override
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // Background
        painter.setBrush(QColor("#FFF4E5"));
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(rect(), 20, 20);

        // Golden glow
        if (isLit)
        {
            QRadialGradient glow(110, 85, 95);
            glow.setColorAt(0, QColor(255, 190, 50, 150));
            glow.setColorAt(0.5, QColor(255, 190, 50, 55));
            glow.setColorAt(1, QColor(255, 190, 50, 0));

            painter.setBrush(glow);
            painter.drawEllipse(15, 0, 190, 190);
        }

        // Diya bowl
        QLinearGradient bowlGradient(0, 130, 0, 180);
        bowlGradient.setColorAt(0, QColor("#D97935"));
        bowlGradient.setColorAt(1, QColor("#8D321F"));

        painter.setBrush(bowlGradient);
        painter.setPen(QPen(QColor("#87351F"), 2));

        QPainterPath bowl;
        bowl.moveTo(35, 135);
        bowl.quadTo(110, 205, 185, 135);
        bowl.quadTo(110, 155, 35, 135);

        painter.drawPath(bowl);

        // Oil
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor("#F6B94A"));
        painter.drawEllipse(75, 135, 70, 9);

        // Wick
        painter.setPen(QPen(QColor("#493025"), 4));
        painter.drawLine(110, 137, 110, 111);

        // Flame
        if (isLit)
        {
            QRadialGradient flameGlow(110, 85, 45);
            flameGlow.setColorAt(0, QColor(255, 255, 180, 230));
            flameGlow.setColorAt(0.5, QColor(255, 166, 35, 180));
            flameGlow.setColorAt(1, QColor(255, 120, 0, 0));

            painter.setPen(Qt::NoPen);
            painter.setBrush(flameGlow);
            painter.drawEllipse(65, 35, 90, 100);

            QLinearGradient flameGradient(0, 55, 0, 125);
            flameGradient.setColorAt(0, QColor("#FFF9B0"));
            flameGradient.setColorAt(0.5, QColor("#FFC12F"));
            flameGradient.setColorAt(1, QColor("#F26A21"));

            painter.setBrush(flameGradient);

            QPainterPath flame;
            flame.moveTo(110, 55);
            flame.cubicTo(75, 85, 95, 110, 110, 120);
            flame.cubicTo(135, 105, 145, 80, 110, 55);

            painter.drawPath(flame);
        }
        else
        {
            painter.setPen(Qt::NoPen);
            painter.setBrush(QColor("#B85A2B"));

            QPainterPath unlitFlame;
            unlitFlame.moveTo(110, 85);
            unlitFlame.quadTo(100, 100, 110, 112);
            unlitFlame.quadTo(120, 100, 110, 85);

            painter.drawPath(unlitFlame);
        }

        // Text
        painter.setPen(QColor("#87351F"));
        painter.setFont(QFont("Arial", 10, QFont::DemiBold));

        painter.drawText(
            QRect(10, 185, 200, 25),
            Qt::AlignCenter,
            isLit ? "Your diya is glowing!" : "Click to light the diya"
            );
    }

private:
    bool isLit;
};

#endif // DIYAWIDGET_H
