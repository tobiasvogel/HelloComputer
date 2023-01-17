#include "application.h"
#include <QEvent>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>


bool Application::eventFilter( QObject *object, QEvent *event ) {
   Q_UNUSED( object );

   if ( event->type() == QEvent::KeyPress ) {
      pressedKeys += ( ( QKeyEvent * )event )->key();

      if ( pressedKeys.contains( Qt::Key_Dollar ) && pressedKeys.contains( Qt::Key_Escape ) && pressedKeys.contains( Qt::Key_Shift ) ) {
         this->closeAllWindows();
         this->quit();
      }

      event->accept();

   } else if ( event->type() == QEvent::KeyRelease ) {
      pressedKeys -= ( ( QKeyEvent * )event )->key();
   }


   return false;
}
