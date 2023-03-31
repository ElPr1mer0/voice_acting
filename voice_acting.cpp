#include "voice_acting.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextBrowser>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QComboBox>


VOICE_ACTING::VOICE_ACTING(QWidget *parent): QWidget(parent){
    v_main_l = new QVBoxLayout;
    VOICE_ACTING::setLayout(v_main_l);

    text_browser = new QTextBrowser;
    v_main_l->addWidget(text_browser);
    text_browser->insertPlainText("Грохочет гром\n"
                                  "Сверкает молния в ночи\n"
                                  "А на холме стоит безумец и кричит\n"
                                  "Сейчас поймаю тебя в сумку\n"
                                  "И сверкать ты будешь в ней\n"
                                  "Мне так хочется, чтоб стала ты моей!\n"
                                  "То парень к лесу мчится\n"
                                  "То к полю, то к ручью\n"
                                  "Всё поймать стремится\n"
                                  "Молнию!\n"
                                  "Весь сельский люд\n"
                                  "Смотреть на это выходил\n"
                                  "Как на холме безумец бегал и чудил\n"
                                  "Он, видно, в ссоре с головою\n"
                                  "Видно, сам себе он враг\n"
                                  "Надо-ж выдумать такое — во дурак!\n"
                                  "То парень к лесу мчится\n"
                                  "То к полю, то к ручью\n"
                                  "Всё поймать стремится\n"
                                  "Молнию!\n"
                                  "Утром по сельской дороге\n"
                                  "Медленно шёл ночной герой\n"
                                  "Весь лохматый и седой\n"
                                  "И улыбался\n"
                                  "То парень к лесу мчится\n"
                                  "То к полю, то к ручью\n"
                                  "Всё поймать стремится\n"
                                  "Молнию!\n");

    QHBoxLayout *h_volume_l = new QHBoxLayout;
    v_main_l->addLayout(h_volume_l);
    lab_volume = new QLabel("Громкость");
    sl_volume = new QSlider(Qt::Horizontal);
    h_volume_l->addWidget(lab_volume);
    h_volume_l->addWidget(sl_volume);

    QHBoxLayout *h_speed_l = new QHBoxLayout;
    v_main_l->addLayout(h_speed_l);
    lab_speed = new QLabel("Скорость");
    sl_speed = new QSlider(Qt::Horizontal);
    h_speed_l->addWidget(lab_speed);
    h_speed_l->addWidget(sl_speed);

    QHBoxLayout *h_language_l = new QHBoxLayout;
    v_main_l->addLayout(h_language_l);
    lab_language = new QLabel("Язык");
    box_language = new QComboBox;
    h_language_l->addWidget(lab_language);
    h_language_l->addWidget(box_language);

    QHBoxLayout *h_buttons_l = new QHBoxLayout;
    v_main_l->addLayout(h_buttons_l);
    but_play = new QPushButton("Включить");
    but_pause = new QPushButton("Пауза");
    but_resume = new QPushButton("Продолжить");
    but_stop = new QPushButton("Выключить");
    h_buttons_l->addWidget(but_play);
    h_buttons_l->addWidget(but_pause);
    h_buttons_l->addWidget(but_resume);
    h_buttons_l->addWidget(but_stop);


    connect(but_play, &QPushButton::clicked, this, &VOICE_ACTING::Speak);
    connect(sl_speed, &QSlider::valueChanged, this, &VOICE_ACTING::SetSpeed);
    connect(sl_volume, &QSlider::valueChanged, this, &VOICE_ACTING::SetVolume);

    speech = new QTextToSpeech(this);

    SetSpeed(sl_speed->value());
    SetVolume(sl_volume->value());
    connect(but_stop, &QPushButton::clicked, this, &VOICE_ACTING::Stop);
    connect(but_pause, &QPushButton::clicked,this, &VOICE_ACTING::Pause);
    connect(but_resume, &QPushButton::clicked, this, &VOICE_ACTING::Resume);

   // connect(speech, &QTextToSpeech::stateChanged, this, &VOICE_ACTING::LocaleChanged);
    connect(speech, &QTextToSpeech::localeChanged, this, &VOICE_ACTING::LocaleChanged);

    connect(box_language, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &VOICE_ACTING::SetLanguage);

    const QVector<QLocale> locales = speech->availableLocales();
    QLocale current = speech->locale();
    for (const QLocale &locale : locales) {
        QString name(QString("%1 (%2)")
                     .arg(QLocale::languageToString(locale.language()))
                     .arg(QLocale::countryToString(locale.country())));
        QVariant localeVariant(locale);
        box_language->addItem(name, localeVariant);
        if (locale.name() == current.name())
            current = locale;
    }
    LocaleChanged(current);
}

void VOICE_ACTING::Speak(){
    speech->say(text_browser->toPlainText());
}

void VOICE_ACTING::Stop(){
    speech->stop();
}

void VOICE_ACTING::Pause(){
    speech->pause();
}

void VOICE_ACTING::Resume(){
    speech->resume();
}

void VOICE_ACTING::SetSpeed(int speed){
    speech->setRate(speed / 10.0);
}

void VOICE_ACTING::SetVolume(int volume){
    speech->setVolume(volume / 100.0);
}

void VOICE_ACTING::SetLanguage(int language){
    QLocale locale = box_language->itemData(language).toLocale();
    speech->setLocale(locale);
}

void VOICE_ACTING::SetVoice(int index){
    speech->setVoice(voices.at(index));
}

void VOICE_ACTING::LocaleChanged(const QLocale &locale){
    QVariant localeVariant(locale);
    box_language->setCurrentIndex(box_language->findData(localeVariant));


//    voices = speech->availableVoices();
//    QVoice currentVoice = speech->voice();
//    for (const QVoice &voice : qAsConst(voices)) {
//        voice->addItem(QString("%1 - %2 - %3").arg(voice.name())
//                          .arg(QVoice::genderName(voice.gender()))
//                          .arg(QVoice::ageName(voice.age())));
//        if (voice.name() == currentVoice.name())
//            ui.voice->setCurrentIndex(ui.voice->count() - 1);
//    }
//    connect(ui.voice, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &MainWindow::voiceSelected);
}



