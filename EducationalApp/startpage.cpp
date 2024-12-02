#include "startpage.h"
#include "ui_startpage.h"

StartPage::StartPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StartPage)
{
    ui->setupUi(this);
    ui->girlScoutButton->hide();
    ui->boyScoutButton->hide();
}

StartPage::~StartPage()
{
    delete ui;
}

void StartPage::on_startButton_clicked()
{
    ui->startButton->hide();
    ui->instructionsButton->hide();
    ui->girlScoutButton->show();
    ui->boyScoutButton->show();
}

// Girl Scout is 0, Boy Scout is 1
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

