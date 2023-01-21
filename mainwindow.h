#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include "structs.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum Palette_t { COMPLETE, VIBRANT, PASTEL };

typedef enum Palette_t Palette;


class MainWindow : public QMainWindow {
   Q_OBJECT

public:
   MainWindow( QWidget *parent = nullptr );
   ~MainWindow();
   void changeColor( void );
   bool determineTextColor( QColor color );
   void settingsDlg( void );

   Q_ENUM( Palette );

protected:
   void keyPressEvent( QKeyEvent *event );
   void closeEvent( QCloseEvent *event );
   QByteArray toneGenerator( AudioContext *ctx );
   void play( AudioContext *ctx );
   void preplay( AudioContext *ctx );
   void init( AudioContext *ctx );

protected Q_SLOTS:
   void run( void );
   void quit( void );

private:
   Ui::MainWindow *ui;
   uint8_t lastColorGroup = 0;
   AudioContext ctx;
   QAudioFormat format;
   QDialog *settingsDialog;
   QTimer *delayTimer;
   Palette usePalette;
   uint16_t _delayDuration;
   bool _hasStarted = false;
   bool _playSound = true;
   bool _delayPaused = false;
};
#endif // MAINWINDOW_H
