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

protected:
    void paintEvent(QPaintEvent *event) override;

signals:
    void updateCharacterInfo(int characterType);

public slots:
    void on_startButton_clicked();

    void on_girlScoutButton_clicked();

    void on_boyScoutButton_clicked();

    void on_instructionsButton_clicked();

    void on_nonBinaryScoutButton_clicked();

    void updateWinScreen();

    void updateLoseScreen();

private:
    Ui::StartPage *ui;

    QLabel* instructionsLabel;
    QPixmap uiBackground;
    QLabel* boyScoutLabel;
    QLabel* girlScoutLabel;
    QLabel* nonBinaryScoutLabel;

    void setBackground(const QString &imagePath);
};

#endif // STARTPAGE_H
