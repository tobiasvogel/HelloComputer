#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QCloseEvent>
#include <QtMultimedia/QAudioFormat>
#include <QtMultimedia/QAudioOutput>
#include <QtMath>
#include "structs.h"


class Application final : public QApplication {
public:
   Application( int &argc, char **argv ) : QApplication( argc, argv ) {
      this->installEventFilter( this );
   }
   bool eventFilter( QObject *object, QEvent *event );

private:
   QSet<int> pressedKeys;

};

#endif // APPLICATION_H
