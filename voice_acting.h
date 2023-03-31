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
    QLabel *lab_language = nullptr;
    QLabel *lab_pitch = nullptr;

    QSlider *sl_volume = nullptr;
    QSlider *sl_speed = nullptr;
    QSlider *sl_pitch = nullptr;

    QPushButton *but_play = nullptr;
    QPushButton *but_pause = nullptr;
    QPushButton *but_resume = nullptr;
    QPushButton *but_stop = nullptr;

    QComboBox *box_language = nullptr;

    QTextBrowser *text_browser = nullptr;

    QTextToSpeech *speech = nullptr;

public:
    VOICE_ACTING(QWidget *parent = nullptr);

public slots:
    void Speak();
    void Stop();
    void Pause();
    void Resume();

    void SetSpeed(int speed);
    void SetVolume(int volume);
    void SetPitch(double pitch);

    void SetLanguage(int language);

    void LocaleChanged(const QLocale &locale);
};
#endif // VOICE_ACTING_H
