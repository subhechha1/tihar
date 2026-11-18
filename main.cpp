
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFrame>
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QLinearGradient>
#include <QRadialGradient>
#include <QPainterPath>
#include <QStringList>
// ---------------- INTERACTIVE DIYA ----------------

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
        painter.setBrush(QColor("#392052"));
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(rect(), 20, 20);

        // Golden glow when diya is lit
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

        // Oil inside the diya
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

        // Instruction
        painter.setPen(QColor("#87351F"));
        QFont font("Arial", 10, QFont::DemiBold);
        painter.setFont(font);

        painter.drawText(QRect(10, 185, 200, 25),
                         Qt::AlignCenter,
                         isLit ? "Your diya is glowing!" : "Click to light the diya");
    }

private:
    bool isLit;
};

// ---------------- INFORMATION CARD ----------------

QFrame* createCard(QString emoji, QString heading, QString description)
{
    QFrame *card = new QFrame;
    card->setStyleSheet(
        "QFrame { background-color: #FFF9F1;"
        "border: 1px solid #E8D7C5;"
        "border-radius: 15px; }");

    QVBoxLayout *layout = new QVBoxLayout(card);
    layout->setContentsMargins(18, 18, 18, 18);

    QLabel *icon = new QLabel(emoji);
    icon->setStyleSheet("font-size: 30px; border: none;");

    QLabel *title = new QLabel(heading);
    title->setStyleSheet(
        "font-size: 18px; font-weight: bold;"
        "color: #A83F35; border: none;");

    QLabel *detail = new QLabel(description);
    detail->setWordWrap(true);
    detail->setStyleSheet(
        "font-size: 13px; color: #594A40; border: none;");

    layout->addWidget(icon);
    layout->addWidget(title);
    layout->addWidget(detail);
    layout->addStretch();

    return card;
}

// ---------------- MAIN WINDOW ----------------

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Tihar Festival");
    window.resize(1100, 850);
    window.setStyleSheet(
        "QWidget { background-color: #F8F1E8;"
        "font-family: Arial; }");

    QVBoxLayout *mainLayout = new QVBoxLayout(&window);
    mainLayout->setContentsMargins(35, 20, 35, 20);
    mainLayout->setSpacing(22);

    // Navigation bar
    QHBoxLayout *navLayout = new QHBoxLayout;

    QLabel *logo = new QLabel("🪔 TIHAR");
    logo->setStyleSheet(
        "font-size: 25px; font-weight: bold;"
        "color: #A83F35;");

    navLayout->addWidget(logo);
    navLayout->addStretch();

    QStringList navItems = {"Home", "About", "Celebrations", "Contact"};

    for (const QString &item : navItems)
    {
        QPushButton *button = new QPushButton(item);
        button->setCursor(Qt::PointingHandCursor);
        button->setStyleSheet(
            "QPushButton { background: transparent;"
            "color: #594A40; border: none;"
            "font-size: 14px; padding: 8px; }"
            "QPushButton:hover { color: #A83F35; }");

        navLayout->addWidget(button);
    }

    mainLayout->addLayout(navLayout);

    // Hero section
    QFrame *hero = new QFrame;
    hero->setStyleSheet(
        "QFrame { background-color: #F0DFCD;"
        "border-radius: 22px; }");

    QHBoxLayout *heroLayout = new QHBoxLayout(hero);
    heroLayout->setContentsMargins(35, 30, 35, 30);

    QVBoxLayout *heroText = new QVBoxLayout;

    QLabel *welcome = new QLabel("THE FESTIVAL OF LIGHTS");
    welcome->setStyleSheet(
        "color: #52704C; font-size: 13px;"
        "font-weight: bold; border: none;");

    QLabel *heading = new QLabel("Celebrate the\nSpirit of Tihar");
    heading->setStyleSheet(
        "color: #8E352F; font-size: 38px;"
        "font-weight: bold; border: none;");

    QLabel *description = new QLabel(
        "A beautiful celebration of lights, love,\n"
        "family, and togetherness. Let every diya\n"
        "brighten your home and heart.");
    description->setStyleSheet(
        "color: #594A40; font-size: 15px;"
        "line-height: 1.5; border: none;");

    QPushButton *exploreButton = new QPushButton("Explore Tihar");
    exploreButton->setFixedSize(145, 42);
    exploreButton->setCursor(Qt::PointingHandCursor);
    exploreButton->setStyleSheet(
        "QPushButton { background-color: #A83F35;"
        "color: white; border-radius: 10px;"
        "font-weight: bold; }"
        "QPushButton:hover { background-color: #873128; }");

    QObject::connect(exploreButton, &QPushButton::clicked,
                     [&window]() {
                         QMessageBox::information(&window, "Tihar",
                                                  "Welcome to the world of Tihar!");
                     });

    heroText->addWidget(welcome);
    heroText->addSpacing(12);
    heroText->addWidget(heading);
    heroText->addSpacing(12);
    heroText->addWidget(description);
    heroText->addSpacing(18);
    heroText->addWidget(exploreButton);
    heroText->addStretch();

    DiyaWidget *diya = new DiyaWidget;

    heroLayout->addLayout(heroText, 2);
    heroLayout->addWidget(diya, 1, Qt::AlignCenter);

    mainLayout->addWidget(hero);

    // Festival highlights
    QLabel *highlightsTitle = new QLabel("Experience the Celebrations");
    highlightsTitle->setStyleSheet(
        "font-size: 25px; font-weight: bold;"
        "color: #8E352F;");

    mainLayout->addWidget(highlightsTitle);

    QGridLayout *cardsLayout = new QGridLayout;
    cardsLayout->setSpacing(15);

    cardsLayout->addWidget(
        createCard("🐦", "Kag Tihar",
                   "The first day is dedicated to crows, messengers of good news."),
        0, 0);

    cardsLayout->addWidget(
        createCard("🐕", "Kukur Tihar",
                   "Dogs are worshipped and celebrated for their loyalty."),
        0, 1);

    cardsLayout->addWidget(
        createCard("🐄", "Gai Tihar",
                   "Cows are honoured as symbols of prosperity and abundance."),
        0, 2);

    cardsLayout->addWidget(
        createCard("🪔", "Laxmi Puja",
                   "Homes are decorated with lights to welcome Goddess Laxmi."),
        1, 0);

    cardsLayout->addWidget(
        createCard("🎊", "Bhai Tika",
                   "A special day celebrating the beautiful bond between siblings."),
        1, 1);

    mainLayout->addLayout(cardsLayout);

    // About section
    QFrame *aboutBox = new QFrame;
    aboutBox->setStyleSheet(
        "QFrame { background-color: #52704C;"
        "border-radius: 15px; }");

    QVBoxLayout *aboutLayout = new QVBoxLayout(aboutBox);
    aboutLayout->setContentsMargins(22, 18, 22, 18);

    QLabel *aboutTitle = new QLabel("The Beauty of Tihar");
    aboutTitle->setStyleSheet(
        "color: white; font-size: 22px;"
        "font-weight: bold; border: none;");

    QLabel *aboutText = new QLabel(
        "Tihar is one of Nepal's most loved festivals. "
        "It brings families and communities together "
        "through lights, music, traditions, and joy.");
    aboutText->setWordWrap(true);
    aboutText->setStyleSheet(
        "color: #FFF5E8; font-size: 14px; border: none;");

    aboutLayout->addWidget(aboutTitle);
    aboutLayout->addWidget(aboutText);

    mainLayout->addWidget(aboutBox);

    // Footer
    QLabel *footer = new QLabel(
        "Made with love for the festival of lights  🪔");
    footer->setAlignment(Qt::AlignCenter);
    footer->setStyleSheet(
        "color: #A83F35; font-size: 13px; padding: 8px;");

    mainLayout->addWidget(footer);

    window.show();

    return app.exec();
}






