#ifndef VOICE_ACTING_H
#define VOICE_ACTING_H

#include <QWidget>
#include <QTextToSpeech>

class QComboBox;
class QSlider;
class QLabel;
class QPushButton;
class QTextBrowser;
class QVBoxLayout;

class VOICE_ACTING : public QWidget{
    Q_OBJECT

private:
    QVBoxLayout *v_main_l = nullptr;

    QLabel *lab_volume = nullptr;
    QLabel *lab_speed= nullptr;
    //QLabel *lab_engine = nullptr;
    QLabel *lab_language = nullptr;
   // QLabel *lab_voice_name = nullptr;
    QSlider *sl_volume = nullptr;
    QSlider *sl_speed = nullptr;
    QPushButton *but_play = nullptr;
    QPushButton *but_pause = nullptr;
    QPushButton *but_resume = nullptr;
    QPushButton *but_stop = nullptr;
    QComboBox *box_language = nullptr;
    QTextBrowser *text_browser = nullptr;

    QTextToSpeech *speech = nullptr;
    QVector<QVoice> voices;

public:
    VOICE_ACTING(QWidget *parent = nullptr);

public slots:
    void Speak();
    void Stop();
    void Pause();
    void Resume();

    void SetSpeed(int);
    void SetVolume(int volume);

    void SetLanguage(int language);
    void SetVoice(int index);

    void LocaleChanged(const QLocale &locale);
};
#endif // VOICE_ACTING_H
