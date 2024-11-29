#include "view.h"
#include "ui_view.h"

View::View(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::View)
{
    ui->setupUi(this);

   //connect( view signal "sendModel" to gameWorld "setModel" slot)
    connect ()
    //setUpModel();

}

void View::setUpInitialGameModel() {
    emit setUpModel(1);
}

View::~View()
{
    delete ui;
}
