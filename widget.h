#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTimer>
#include <QString>
#include <QDir>
#include <QStringList>
#include <QFileDialog>
#include <QDebug>
#include <QListWidgetItem>


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    QMediaPlayer *mediaPlayer;

    QTimer *playTimer;
    QString my_play_path;
    QString primer_path = "qrc:/new/prefix1/sounds/";



    QString settime(int time);

    int m_PlayRow;

    int current_item;    //记录当前播放的曲子编号

    ~Widget();

private slots:
    void on_btnPlay_clicked();

    void on_verVolumeSlide_sliderMoved(int position);

    void on_horPlayControlSlide_sliderMoved(int position);

    void setHorSliderValue();

    void on_musicList_itemDoubleClicked(QListWidgetItem *item);

    void on_preBtn_clicked();

    void on_nextBtn_clicked();

    void on_btnVolume_clicked();

    void on_verVolumeSlide_sliderReleased();

    void on_musicList_itemClicked(QListWidgetItem *item);

    void getduration();

    void setPlayTime();

private:
    Ui::Widget *ui;


    void addMusic();
};

#endif // WIDGET_H
