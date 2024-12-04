#include "startpage.h"
#include "ui_startpage.h"
#include <QPainter>

StartPage::StartPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StartPage)
{
    ui->setupUi(this);
    uiBackground = QPixmap(":/Images/background_level2.PNG");
    ui->gameNameLabel->setStyleSheet("font: 50px Courier;");
    ui->gameNameLabel->setAlignment(Qt::AlignCenter);

    ui->startButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #c1c19e;"  // Button background
        "   color: black;"              // Text color
        "   font: 18px Courier;"
        "   border: 2px solid #c1c19e;" // Border
        "   border-radius: 10px;"       // Rounded corners
        "}"
        );

    ui->instructionsButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #c1c19e;"  // Button background
        "   color: black;"              // Text color
        "   font: 18px Courier;"
        "   border: 2px solid #c1c19e;" // Border
        "   border-radius: 10px;"       // Rounded corners
        "}"
        );

    ui->girlScoutButton->hide();
    ui->girlScoutButton->setFixedSize(150, 50);
    ui->girlScoutButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #F2D2BD;"  // Button background
        "   color: black;"              // Text color
        "   font: 18px Courier;"
        "   border: 2px solid #F2D2BD;" // Border
        "   border-radius: 10px;"       // Rounded corners
        "}"
        );

    ui->boyScoutButton->hide();
    ui->boyScoutButton->setFixedSize(150, 50);
    ui->boyScoutButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #F2D2BD;"  // Button background
        "   color: black;"              // Text color
        "   font: 18px Courier;"
        "   border: 2px solid #F2D2BD;" // Border
        "   border-radius: 10px;"       // Rounded corners
        "}"
        );

    ui->nonBinaryScoutButton->hide();
    ui->nonBinaryScoutButton->setFixedSize(200, 50);
    ui->nonBinaryScoutButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #F2D2BD;"  // Button background
        "   color: black;"              // Text color
        "   font: 18px Courier;"
        "   border: 2px solid #F2D2BD;" // Border
        "   border-radius: 10px;"       // Rounded corners
        "}"
        );

    instructionsLabel = new QLabel(this);
}

StartPage::~StartPage()
{
    delete ui;
}

void StartPage::on_startButton_clicked()
{
    ui->startButton->hide();
    ui->instructionsButton->hide();
    instructionsLabel->hide();

    ui->girlScoutButton->show();
    girlScoutLabel = new QLabel(this);
    girlScoutLabel->show();
    girlScoutLabel->setStyleSheet(
        "background-color: #c1c19e;;"  // Set the background color
        "background-image: url(:/Images/girlScout.png);"
        "background-position: center;"
        );
    girlScoutLabel->setFixedSize(160, 200);
    girlScoutLabel->move(880, 390);

    ui->boyScoutButton->show();
    boyScoutLabel = new QLabel(this);
    boyScoutLabel->show();
    boyScoutLabel->setStyleSheet(
        "background-color: #c1c19e;;"  // Set the background color
        "background-image: url(:/Images/boyScout.png);"
        "background-position: center;"
        );
    boyScoutLabel->setFixedSize(150, 200);
    boyScoutLabel->move(425, 390);


    ui->nonBinaryScoutButton->show();
    nonBinaryScoutLabel = new QLabel(this);
    nonBinaryScoutLabel->show();
    nonBinaryScoutLabel->setStyleSheet(
        "background-color: #c1c19e;;"  // Set the background color
        "background-image: url(:/Images/nonBinaryScout.png);"
        "background-position: center;"
        "background-repeat: no-repeat;"
        );
    nonBinaryScoutLabel->setFixedSize(200, 200);
    nonBinaryScoutLabel->move(630, 390);

    ui->gameNameLabel->show();
}

// Girl Scout is 0, Boy Scout is 1, NonBinary Scout is 2
void StartPage::on_girlScoutButton_clicked()
{
    emit updateCharacterInfo(0);
    this->hide();
}


void StartPage::on_boyScoutButton_clicked()
{
    emit updateCharacterInfo(1);
    this->hide();
}

void StartPage::on_nonBinaryScoutButton_clicked()
{
    emit updateCharacterInfo(2);
    this->hide();
}

void StartPage::on_instructionsButton_clicked()
{
    ui->startButton->show();
    ui->startButton->move(650, 650);
    ui->instructionsButton->hide();
    ui->gameNameLabel->hide();

    instructionsLabel->resize(1000, 500);
    instructionsLabel->setAlignment(Qt::AlignCenter);
    instructionsLabel->setWordWrap(true);
    instructionsLabel->setStyleSheet("background: white");

    int x = (this->width() - instructionsLabel->width()) / 2;
    int y = (this->height() - instructionsLabel->height()) / 2;

    instructionsLabel->move(x, y);
    instructionsLabel->show();
    instructionsLabel->setText(
        "<div style='font-family:Times New Roman; font-size:20px; color:black;'>"
        "Hey there, adventurer! Welcome to the Wilderness Quest! Out here, it's all about brains and bravery. Your mission is to navigate this rugged terrain, answer 10 questions, and make it back to the tent without running into any bears!<br><br>"
        "<b>1.</b> Read the question at the top, then use the arrow keys to move your Scout, to the right platforms. Collect the right answer and another questions will appear. Don't worry, if you find the wrong answer you will survive! Remember, you are here to learn.<br>"
        "<b>2.</b> Once you have answered all 10 questions correctly, guide your scout to the tent to get to safety. Reaching the tent will advance you to the next level.<br>"
        "<b>3.</b> BEWARE OF BEARS. Bears are always in the wild. If you run into a bear, you loose a life. Loose all 3 lives and you loose! Jump to avoid them. Use the platforms strategically.<br><br><br>"
        "Finish all 4 levels to win! Have fun and good luck fearless Scout!"
        "</div>"
        );
}

void StartPage::updateWinScreen() {
    this->show();
    setBackground(":/Images/background_level1.PNG");

    ui->startButton->hide();
    ui->instructionsButton->hide();
    ui->girlScoutButton->hide();
    ui->boyScoutButton->hide();
    ui->nonBinaryScoutButton->hide();
    girlScoutLabel->hide();
    boyScoutLabel->hide();
    nonBinaryScoutLabel->hide();
    ui->gameNameLabel->setText("You Win!");
}

void StartPage::updateLoseScreen() {
    qDebug() << "Player Lost! Should display end screen.";
    this->show();
    setBackground(":/Images/background_level1.PNG");

    ui->startButton->hide();
    ui->instructionsButton->hide();
    ui->girlScoutButton->hide();
    ui->boyScoutButton->hide();
    ui->nonBinaryScoutButton->hide();
    girlScoutLabel->hide();
    boyScoutLabel->hide();
    nonBinaryScoutLabel->hide();
    ui->gameNameLabel->setText("You Lose!");
}

void StartPage::setBackground(const QString &imagePath) {
    QPixmap newBackground(imagePath);
    if (!newBackground.isNull()) {
        uiBackground = newBackground;
        update();
    }
}

void StartPage::paintEvent(QPaintEvent* event) {
    QPainter painter(this);

    if (!uiBackground.isNull()) {
        painter.drawPixmap(0, 0, this->width(), this->height(), uiBackground);
    }
    QWidget::paintEvent(event);
}

