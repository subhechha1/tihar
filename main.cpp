
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QFont>
#include <QGraphicsDropShadowEffect>

QLabel* createLabel(QString text, int size, QString color,
                    bool bold = false)
{
    QLabel* label = new QLabel(text);

    QFont font("Segoe UI", size);
    font.setBold(bold);

    label->setFont(font);
    label->setStyleSheet("color: " + color + ";");
    label->setAlignment(Qt::AlignCenter);

    return label;
}

QPushButton* createButton(QString text)
{
    QPushButton* button = new QPushButton(text);

    button->setStyleSheet(
        "QPushButton {"
        "background-color: #FFC52B;"
        "color: #211039;"
        "border-radius: 20px;"
        "padding: 12px 25px;"
        "font-size: 15px;"
        "font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "background-color: #FFE080;"
        "}"
    );

    return button;
}

QFrame* createCard(QString emoji, QString title, QString description)
{
    QFrame* card = new QFrame();

    card->setStyleSheet(
        "QFrame {"
        "background-color: #281844;"
        "border: 1px solid #3B285B;"
        "border-radius: 18px;"
        "}"
    );

    QVBoxLayout* layout = new QVBoxLayout(card);

    QLabel* icon = createLabel(emoji, 35, "#FFC52B");
    QLabel* heading = createLabel(title, 18, "#FFC52B", true);
    QLabel* desc = createLabel(description, 12, "#E6DDF4");

    desc->setWordWrap(true);

    layout->addWidget(icon);
    layout->addWidget(heading);
    layout->addWidget(desc);

    card->setMinimumHeight(170);

    return card;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Happy Tihar");
    window.resize(1200, 800);

    window.setStyleSheet(
        "QWidget {"
        "background-color: #190C2E;"
        "color: white;"
        "}"
    );

    QVBoxLayout* mainLayout = new QVBoxLayout(&window);
    mainLayout->setContentsMargins(45, 25, 45, 25);
    mainLayout->setSpacing(25);

    // NAVIGATION BAR
    QHBoxLayout* nav = new QHBoxLayout();

    QLabel* logo = createLabel("🪔 Tihar", 27, "#FFC52B", true);
    logo->setAlignment(Qt::AlignLeft);

    QPushButton* home = new QPushButton("Home");
    QPushButton* about = new QPushButton("About");
    QPushButton* traditions = new QPushButton("Traditions");
    QPushButton* gallery = new QPushButton("Gallery");

    QString navStyle =
        "QPushButton {"
        "background: transparent;"
        "color: white;"
        "border: none;"
        "font-size: 15px;"
        "padding: 10px;"
        "}"
        "QPushButton:hover {"
        "color: #FFC52B;"
        "}";

    home->setStyleSheet(navStyle);
    about->setStyleSheet(navStyle);
    traditions->setStyleSheet(navStyle);
    gallery->setStyleSheet(navStyle);

    nav->addWidget(logo);
    nav->addStretch();
    nav->addWidget(home);
    nav->addWidget(about);
    nav->addWidget(traditions);
    nav->addWidget(gallery);
    nav->addStretch();
    nav->addWidget(createButton("Celebrate Tihar ✨"));

    mainLayout->addLayout(nav);

    // HERO SECTION
    QVBoxLayout* hero = new QVBoxLayout();
    hero->setSpacing(15);

    hero->addWidget(
        createLabel("LIGHTS  •  LOVE  •  TOGETHERNESS",
                    13, "#D7C5E8"));

    QLabel* title = createLabel("Happy Tihar!", 55, "#FFC52B", true);

    QFont heroFont("Georgia", 55, QFont::Bold);
    title->setFont(heroFont);

    hero->addWidget(title);

    hero->addWidget(
        createLabel(
            "May the glow of Tihar bring happiness,\n"
            "prosperity and peace to you and your family.",
            17, "#E6DDF4"));

    hero->addSpacing(10);
    hero->addWidget(createButton("Explore the Festival  →"));

    mainLayout->addSpacing(20);
    mainLayout->addLayout(hero);
    mainLayout->addSpacing(20);

    // FESTIVAL HIGHLIGHTS
    mainLayout->addWidget(
        createLabel("Festival Highlights", 27, "#FFFFFF", true));

    QHBoxLayout* cards = new QHBoxLayout();
    cards->setSpacing(18);

    cards->addWidget(createCard(
        "🐦", "Kag Tihar",
        "Honoring crows, the messengers of good fortune."));

    cards->addWidget(createCard(
        "🐕", "Kukur Tihar",
        "Celebrating our loyal friends."));

    cards->addWidget(createCard(
        "🐄", "Gai Tihar",
        "Worshipping cows, the symbols of kindness."));

    cards->addWidget(createCard(
        "🪔", "Laxmi Puja",
        "Welcoming Goddess Laxmi for prosperity."));

    mainLayout->addLayout(cards);

    // ABOUT SECTION
    mainLayout->addSpacing(20);

    QHBoxLayout* aboutLayout = new QHBoxLayout();

    QLabel* diyaImage = createLabel("🪔 ✨ 🪔", 45, "#FFC52B");
    diyaImage->setMinimumWidth(300);

    QVBoxLayout* aboutText = new QVBoxLayout();

    aboutText->addWidget(
        createLabel("About Tihar", 28, "#FFC52B", true));

    aboutText->addWidget(
        createLabel(
            "Tihar is one of the most beautiful festivals "
            "of Nepal.\nIt celebrates lights, love, gratitude "
            "and family.\n\nLet's spread happiness and "
            "brightness everywhere!",
            14, "#E6DDF4"));

    aboutText->addWidget(createButton("Know More  →"));

    aboutLayout->addWidget(diyaImage);
    aboutLayout->addLayout(aboutText);

    mainLayout->addLayout(aboutLayout);

    // FOOTER
    mainLayout->addStretch();

    mainLayout->addWidget(
        createLabel("🪔  Happy Tihar!  ❤️", 16, "#FFC52B", true));

    mainLayout->addWidget(
        createLabel("Celebrate. Share. Be Happy.", 12, "#BCA9D8"));

    window.show();

    return app.exec();
}
