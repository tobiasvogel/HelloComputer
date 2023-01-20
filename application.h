#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QCloseEvent>
#include <QtMultimedia/QAudioFormat>
#include <QtMultimedia/QAudioOutput>
#include <QtMath>
#include <QDebug>


#if defined(Q_OS_WIN32) || defined(Q_OS_WIN64) || defined(Q_OS_WIN) || defined(Q_OS_WINDOWS) || defined(Q_WS_WIN32)
#include <windows.h>
#include <winuser.h>


class GlobalKeyBlocker {
public:
   GlobalKeyBlocker(): mHKeyboardHook( NULL ) {}
   //to avoid leaking the hook procedure handle
   ~GlobalKeyBlocker() { unblock(); }
   //hook callback function (called on every system-wide key press)
   static LRESULT CALLBACK LowLevelKeyboardProc( int nCode,
         WPARAM wParam, LPARAM lParam ) {
      if ( nCode == HC_ACTION ) {
         PKBDLLHOOKSTRUCT p = reinterpret_cast<PKBDLLHOOKSTRUCT>( lParam );

         if ( p->vkCode == VK_LWIN ) { return 1; } //block left win key

         if ( p->vkCode == VK_RWIN ) { return 1; } //block right win key
      }

      return CallNextHookEx( NULL, //ignored paramater
                             nCode,
                             wParam,
                             lParam );
   }
   void block() {
      mHKeyboardHook = SetWindowsHookEx( WH_KEYBOARD_LL, //low-level keyboard hool
                                         &LowLevelKeyboardProc, //callback
                                         GetModuleHandle( NULL ),
                                         0 );
   }
   void unblock() {
      if ( mHKeyboardHook ) { UnhookWindowsHookEx( mHKeyboardHook ); }

      mHKeyboardHook = NULL;
   }

private:
   HHOOK mHKeyboardHook;
};

#endif


#if defined(Q_OS_LINUX) || defined(Q_WS_X11)
#include <giomm/init.h>
#include <giomm/settings.h>

class GlobalKeyBlocker {
public:
   GlobalKeyBlocker() {
      Gio::init();
      s = Gio::Settings::create( "org.gnome.mutter" );
   };
   ~GlobalKeyBlocker() {
      this->unblock();
   };
   void block() {
      Glib::ustring key = "overlay-key";
      Glib::ustring empty = "";
      Glib::VariantBase value;
      s->get_value( key, value );
      restoreValue = QString::fromStdString( value.print() );

      if ( restoreValue.right( 1 ) == "'" || restoreValue.right( 1 ) == "\"" ) {
         restoreValue.chop( 1 );
      }

      if ( restoreValue.at( 0 ) == "'" || restoreValue.at( 0 ) == "\"" ) {
         restoreValue = restoreValue.right( restoreValue.length() - 1 );
      }

      if ( restoreValue.isEmpty() ) { return; }

      s->set_string( key, empty );
   }
   void unblock() {
      Glib::ustring key = "overlay-key";
      Glib::ustring previousValue = restoreValue.toStdString();
      s->set_string( key, previousValue );
   }
private:
   Glib::RefPtr<Gio::Settings> s;
   QString restoreValue;
};

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
