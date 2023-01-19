#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QCloseEvent>
#include <QtMultimedia/QAudioFormat>
#include <QtMultimedia/QAudioOutput>
#include <QtMath>

#if defined(Q_OS_WIN32) || defined(Q_OS_WIN64) || defined(Q_OS_WIN) || defined(Q_OS_WINDOWS) || defined(Q_WS_WIN32)
#include <windows.h>
#include <winuser.h>

//FIXME: include hook to catch Windows-key

#endif


#if defined(Q_OS_LINUX) || defined(Q_WS_X11)

//FIXME: include hook to catch Meta/Super-key

#endif

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
