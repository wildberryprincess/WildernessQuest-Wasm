#include "startpage.h"
#include "ui_startpage.h"

StartPage::StartPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StartPage)
{
    ui->setupUi(this);
    ui->gameNameLabel->setStyleSheet("font: 30px Courier;");
    ui->gameNameLabel->setAlignment(Qt::AlignCenter);
    ui->girlScoutButton->hide();
    ui->boyScoutButton->hide();
    ui->nonBinaryScoutButton->hide();
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
    ui->boyScoutButton->show();
    ui->nonBinaryScoutButton->show();
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
    ui->startButton->move(680, 700);
    ui->instructionsButton->hide();
    ui->gameNameLabel->hide();

    instructionsLabel->resize(1000, 500);
    instructionsLabel->setAlignment(Qt::AlignCenter);
    instructionsLabel->setWordWrap(true);

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

