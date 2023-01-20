#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include "structs.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow {
   Q_OBJECT

public: MainWindow( QWidget *parent = nullptr );
   ~MainWindow();
   void changeColor( void );
   bool determineTextColor( QColor color );
   void settingsDlg( void );

protected:
   void keyPressEvent( QKeyEvent *event );
   void closeEvent( QCloseEvent *event );
   QByteArray toneGenerator( AudioContext *ctx );
   void play( AudioContext *ctx );
   void preplay( AudioContext *ctx );
   void init( AudioContext *ctx );

protected slots:
   void run( void );
   void quit( void );

private:
   Ui::MainWindow *ui;
   uint8_t lastColorGroup = 0;
   AudioContext ctx;
   QAudioFormat format;
   QDialog *settingsDialog;
   bool _hasStarted = false;
   bool _playSound = true;
};
#endif // MAINWINDOW_H
