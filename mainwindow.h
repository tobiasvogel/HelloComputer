#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "structs.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

static inline int timeToSize( int ms, const QAudioFormat &format ) {
   return ( ( format.channelCount() * ( format.sampleSize() / 8 ) * format.sampleRate() ) * ms / 1000 );
}

class MainWindow : public QMainWindow {
   Q_OBJECT

public:
   MainWindow( QWidget *parent = nullptr );
   ~MainWindow();
   void changeColor( void );
   bool determineTextColor( QColor color );

protected:
   void keyPressEvent( QKeyEvent *event );
   void closeEvent( QCloseEvent *event );
   QByteArray toneGenerator( AudioContext *ctx );
   void play( AudioContext *ctx );
   void preplay( AudioContext *ctx );
   void init( AudioContext *ctx );

private:
   Ui::MainWindow *ui;
   uint8_t lastColorGroup = 0;
   AudioContext ctx;
   QAudioFormat format;
   bool imageHidden = false;
};
#endif // MAINWINDOW_H
