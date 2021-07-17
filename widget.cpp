#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_PlayRow = 0;
    current_item = m_PlayRow;

    mediaPlayer = new QMediaPlayer();

    playTimer = new QTimer();
    playTimer->setInterval(2000);
    playTimer->start();

    ui->verVolumeSlide->setVisible(false);     //音量拖动条初始不可见



    this->addMusic();
    //qDebug() << ui->musicList->currentItem()->text() << endl;
    QListWidgetItem *item = ui->musicList->item(m_PlayRow);
    mediaPlayer->setMedia(QUrl(primer_path + item->text()));
    mediaPlayer->setVolume(73);

}

Widget::~Widget()
{
    delete ui;
}


//播放和暂停
void Widget::on_btnPlay_clicked()
{

    if(QMediaPlayer:: PlayingState == mediaPlayer->state())
    {
        mediaPlayer->pause();
        ui->btnPlay->setText("播放");
    }

    else
    {
//        if(ui->musicList->count() == 0)
//        {
//            mediaPlayer->setMedia(QUrl("qrc:/new/prefix1/sounds/s1.mp3"));
//        }
//        else
//        {
//            QListWidgetItem *item = ui->musicList->item(m_PlayRow);
//            mediaPlayer->setMedia(QUrl(primer_path + item->text()));
//        }

        QListWidgetItem *item = ui->musicList->item(m_PlayRow);
        if(current_item != ui->musicList->row(item))
        {
            mediaPlayer->setMedia(QUrl(primer_path + item->text()));
            current_item = ui->musicList->row(item);
        }

        mediaPlayer->play();
        ui->btnPlay->setText("暂停");
        this->getduration();
    }

    connect(playTimer, &QTimer::timeout, this, &Widget::setHorSliderValue);
    connect(mediaPlayer, &QMediaPlayer::durationChanged, this, &Widget::getduration);
    connect(mediaPlayer, &QMediaPlayer::positionChanged, this, &Widget::setPlayTime);

}


//自动调整播放进度
void Widget::setHorSliderValue()
{
    ui->horPlayControlSlide->setValue(mediaPlayer->position() * 100 / mediaPlayer->duration());
    //进度条到顶自动播放下一首
    if(mediaPlayer->position() >= mediaPlayer->duration())
    {
        on_nextBtn_clicked();
    }
}


//垂直滑动条控制音量
void Widget::on_verVolumeSlide_sliderMoved(int position)
{
    mediaPlayer->setVolume(position);
}


//水平滑动条控制播放进度
/*
mediaPlayer->duration()：音频文件的总帧数（当然你理解成时长也可以）
position：是当前滑动条的位置，默认滑动条的总长度是0到99。
m_mediaPlayer.duration()*position/100：音频文件的第多少帧。
m_mediaPlayer.setPosition():设置从哪一帧开始播放。
*/
void Widget::on_horPlayControlSlide_sliderMoved(int position)
{
    mediaPlayer->setPosition(mediaPlayer->duration()*position/100);
}


void Widget::addMusic()
{
    //打开文件资源管理器自行选择音乐路径
    //QString fileName = QFileDialog::getExistingDirectory(NULL, "选择播放音乐路径", "../music_player/sounds", NULL);
    //qDebug() << fileName << endl;
    //QString fileName = "../music_player/sounds";
    QString fileName = ":/new/prefix1/sounds";
    QDir dir(fileName);
    //qDebug() << dir << endl;
    QStringList nameFilters;       //名字过滤器，只寻找mp3后缀的文件
    nameFilters << "*.mp3";
    QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);    //返回该目录找到的文件名，文件可读且根据名字排序
    ui->musicList->addItems(files);

    QListWidgetItem *item = ui->musicList->item(0);
    item->setSelected(true);

    my_play_path = fileName;
}


//双击选中音乐播放
void Widget::on_musicList_itemDoubleClicked(QListWidgetItem *item)
{
    m_PlayRow = ui->musicList->row(item);
    mediaPlayer->stop();
    mediaPlayer->setMedia(QUrl(primer_path + item->text()));
    mediaPlayer->play();
    ui->horPlayControlSlide->setValue(mediaPlayer->position());
}


//上一首
void Widget::on_preBtn_clicked()
{

    if(m_PlayRow == 0)
    {
        m_PlayRow = ui->musicList->count() - 1;  //倒数第一首
    }
    else
    {
        m_PlayRow--;
    }

    QListWidgetItem *item = ui->musicList->item(m_PlayRow);
    item->setSelected(true);
    mediaPlayer->stop();
    mediaPlayer->setMedia(QUrl(primer_path + item->text()));
    mediaPlayer->play();

}


//下一首
void Widget::on_nextBtn_clicked()
{
    if(m_PlayRow + 1 == ui->musicList->count())
    {
        m_PlayRow = 0;
    }
    else
    {
        m_PlayRow++;
    }

    QListWidgetItem *item = ui->musicList->item(m_PlayRow);
    item->setSelected(true);
    mediaPlayer->stop();
    mediaPlayer->setMedia(QUrl(primer_path + item->text()));
    mediaPlayer->play();
}


//音量拖动控制
void Widget::on_btnVolume_clicked()
{
    if(ui->verVolumeSlide->isVisible())
    {
        ui->verVolumeSlide->setVisible(false);
    }
    else
    {
        ui->verVolumeSlide->setVisible(true);
    }

}


//松开拖条块自动消失
void Widget::on_verVolumeSlide_sliderReleased()
{
    ui->verVolumeSlide->setVisible(false);
}


//选中歌名点播放
void Widget::on_musicList_itemClicked(QListWidgetItem *item)
{
    m_PlayRow = ui->musicList->row(item);
    qDebug() << m_PlayRow << endl;
}


//歌曲时间设置
QString Widget::settime(int time)
{
    int h,m,s;
    time /= 1000;  //获得的时间是以毫秒为单位的
    h = time/3600;
    m = (time-h*3600)/60;
    s = time-h*3600-m*60;
    return QString("%1:%2:%3").arg(h).arg(m).arg(s);
}



//获取歌曲总时长并显示
void Widget::getduration()
{
    int playtime;
    playtime = mediaPlayer->duration();
    ui->total_time_label->setText(settime(playtime));
}


//设置当前播放的时间
void Widget::setPlayTime()
{
    ui->current_time_label->setText(settime(mediaPlayer->position()));
}


