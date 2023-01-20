#include "application.h"
#include "mainwindow.h"
#include <QTranslator>


int main( int argc, char *argv[] ) {
   Application a( argc, argv );
   MainWindow w;
   QTranslator translator;
   translator.load( QLocale(), QLatin1String( "hellocomputer" ), QLatin1String( "_" ), QLatin1String( ":/i18n" ) );
   a.installTranslator( &translator );
   #if defined(Q_OS_WIN32) || defined(Q_OS_WIN64) || defined(Q_OS_WIN) || defined(Q_OS_WINDOWS) || defined(Q_WS_WIN32) || defined(Q_OS_LINUX) || defined(Q_WS_X11)
   GlobalKeyBlocker blocker;
   blocker.block();
   #endif
   w.setWindowState( Qt::WindowFullScreen );
   w.show();
   return a.exec();
}
