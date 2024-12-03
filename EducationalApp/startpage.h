#ifndef STARTPAGE_H
#define STARTPAGE_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class StartPage;
}

class StartPage : public QWidget
{
    Q_OBJECT

public:
    explicit StartPage(QWidget *parent = nullptr);
    ~StartPage();

signals:
    void updateCharacterInfo(int characterType);

private slots:
    void on_startButton_clicked();

    void on_girlScoutButton_clicked();

    void on_boyScoutButton_clicked();

    void on_instructionsButton_clicked();

    void on_nonBinaryScoutButton_clicked();

private:
    Ui::StartPage *ui;

    QLabel* instructionsLabel;
};

#endif // STARTPAGE_H
