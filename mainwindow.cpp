#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "colorpalette.h"

#include <QTimer>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QtMath>
#include <QDebug>
#include <QtMultimedia/QAudioFormat>

MainWindow::MainWindow( QWidget *parent )
   : QMainWindow( parent )
   , ui( new Ui::MainWindow ) {
   ui->setupUi( this );
   QString Key1 = "Esc";
   QString Key2 = "Shift";
   QString Key3 = "$";
   ui->label->setText( tr( "Um das Programm zu beenden, drücken Sie die Tasten [%1] + [%2] + [%3] gleichzeitig." ).arg( Key1, Key2,
                       Key3 ) );
   ui->label->adjustSize();
   #ifdef QT_DEBUG
   ui->_debugColorValue->show();
   ui->_debugColorValue->setText( "ColorValue" );
   ui->_debugColorValue->adjustSize();
   #else
   ui->_debugColorValue->hide();
   ui->_debugColorValue->setText( "" );
   #endif
   #ifdef QT_DEBUG
   ui->_debugColorGroup->show();
   ui->_debugColorGroup->setText( "ColorGroup" );
   ui->_debugColorGroup->adjustSize();
   #else
   ui->_debugColorGroup->hide();
   ui->_debugColorGroup->setText( "" );
   #endif
   #ifdef QT_DEBUG
   ui->_debugKeyPress->show();
   ui->_debugKeyPress->setText( "KeyPress" );
   ui->_debugKeyPress->adjustSize();
   #else
   ui->_debugKeyPress->hide();
   ui->_debugKeyPress->setText( "" );
   #endif
   this->grabKeyboard();
   this->grabMouse();


   format.setCodec( "audio/pcm" );
   format.setSampleRate( 8000 );
   format.setChannelCount( 1 );
   format.setSampleSize( 16 );
   format.setByteOrder( QAudioFormat::LittleEndian );
   format.setSampleType( QAudioFormat::SignedInt );

   ctx.m_format = format;

   ctx.m_output_device_info = QAudioDeviceInfo::defaultOutputDevice();

   ctx.m_time_to_buffer = 1000; //Needed time in buffer before play(ms)

   ctx.m_duration_msecs = 20; //Duration of each tone(ms)

   ctx.m_frequency = 100; //Initial tone frequency(hz)

   init( &ctx );
}

MainWindow::~MainWindow() {
   delete ui;
   this->releaseKeyboard();
   this->releaseMouse();
}

void MainWindow::changeColor() {
   QString color;
   uint8_t randNum = QRandomGenerator::global()->bounded( 1, 10 );
   uint8_t randCol;

   if ( lastColorGroup == randNum ) {
      randNum++;

      if ( randNum > 10 ) {
         randNum = randNum - 2;
      }
   }

   switch ( randNum ) {
      case 1:
         randCol = QRandomGenerator::global()->bounded( 0, ( GROUP1.size() - 1 ) );
         color = GROUP1.at( randCol );
         break;

      case 2:
         randCol = QRandomGenerator::global()->bounded( 0, ( GROUP2.size() - 1 ) );
         color = GROUP2.at( randCol );
         break;

      case 3:
         randCol = QRandomGenerator::global()->bounded( 0, ( GROUP3.size() - 1 ) );
         color = GROUP3.at( randCol );
         break;

      case 4:
         randCol = QRandomGenerator::global()->bounded( 0, ( GROUP4.size() - 1 ) );
         color = GROUP4.at( randCol );
         break;

      case 5:
         randCol = QRandomGenerator::global()->bounded( 0, ( GROUP5.size() - 1 ) );
         color = GROUP5.at( randCol );
         break;

      case 6:
         randCol = QRandomGenerator::global()->bounded( 0, ( GROUP6.size() - 1 ) );
         color = GROUP6.at( randCol );
         break;

      case 7:
         randCol = QRandomGenerator::global()->bounded( 0, ( GROUP7.size() - 1 ) );
         color = GROUP7.at( randCol );
         break;

      case 8:
         randCol = QRandomGenerator::global()->bounded( 0, ( GROUP8.size() - 1 ) );
         color = GROUP8.at( randCol );
         break;

      case 9:
         randCol = QRandomGenerator::global()->bounded( 0, ( GROUP9.size() - 1 ) );
         color = GROUP9.at( randCol );
         break;

      case 10:
         randCol = QRandomGenerator::global()->bounded( 0, ( GROUP10.size() - 1 ) );
         color = GROUP10.at( randCol );
         break;

      default: // should never be reached!
         return;
         break;
   }

   ui->_debugKeyPress->setText( QString( "%1; %2" ).arg( randNum ).arg( randCol ) );
   lastColorGroup = randNum;
   this->setStyleSheet( QString( "background-color: %1;" ).arg( color ) );
}

void MainWindow::keyPressEvent( QKeyEvent *event ) {
   ui->_debugKeyPress->setText( QString( event->key() ) );
   this->changeColor();
   this->play( &ctx );
}

void MainWindow::closeEvent( QCloseEvent *event ) {
   event->ignore();
}

QByteArray MainWindow::toneGenerator( AudioContext *ctx ) {
   QByteArray data;

   QDataStream write_stream( &data, QIODevice::ReadWrite );
   write_stream.setVersion( QDataStream::Qt_5_0 ); //Protocol for version 5.0
   write_stream.setByteOrder( QDataStream::LittleEndian );

   //Tone generator from http://www.cplusplus.com/forum/general/129827/

   const uint samplerate = uint( ctx->m_format.sampleRate() );
   const uint channels = uint( ctx->m_format.channelCount() );

   const double pi = M_PI;
   const qint16 amplitude = INT16_MAX;

   const uint frequency = ctx->m_frequency;
   const uint n_msecs = ctx->m_duration_msecs;

   const int n_samples = int( channels * samplerate * ( n_msecs / double( 1000 ) ) );

   int index = n_samples;

   double freq = frequency;
   double d = ( samplerate / freq );
   int c = 0;

   for ( int j = 0; j < index; j++ ) {
      double deg = double( 360 ) / d;
      write_stream << qint16( qSin( ( c++ * double( deg ) ) * pi / double( 180 ) ) * amplitude );
   }

   return data;
}

void MainWindow::play( AudioContext *ctx ) {
   //Set that last async call was triggered
   ctx->m_play_called = false;

   while ( ctx->m_buffer.size() < ctx->m_size_to_buffer ) {
      QByteArray data = toneGenerator( ctx );

      //APPEND HERE YOUR DATA
      ctx->m_buffer.append( data );

      if ( !ctx->m_reverse ) {
         if ( ctx->m_frequency < 20 * 1000 )
         { ctx->m_frequency += 100; }

         else //Restart
         { ctx->m_reverse = !ctx->m_reverse; }

      } else {
         if ( ctx->m_frequency > 100 )
         { ctx->m_frequency -= 100; }

         else //Restart
         { ctx->m_reverse = !ctx->m_reverse; }
      }
   }

   int readlen = ctx->m_audio_output->periodSize();

   int chunks = ctx->m_audio_output->bytesFree() / readlen;

   //Play data while it's available in the output device
   while ( chunks ) {
      //Get chunk from the buffer
      QByteArray samples = ctx->m_buffer.mid( 0, readlen );
      int len = samples.size();
      ctx->m_buffer.remove( 0, len );

      //Write data to the output device after the volume was applied
      if ( len ) {
         ctx->m_output_device->write( samples );
      }

      //If chunk is smaller than the output chunk size, exit loop
      if ( len != readlen )
      { break; }

      //Decrease the available number of chunks
      chunks--;
   }
}

void MainWindow::preplay( AudioContext *ctx ) {
   //Verify if exists a pending call to play function
   //If not, call the play function async
   if ( !ctx->m_play_called ) {
      ctx->m_play_called = true;
      QTimer::singleShot( 0, [ = ] {play( ctx );} );
   }
}

void MainWindow::init( AudioContext *ctx ) {

   //Check if format is supported by the choosen output device
   if ( !ctx->m_output_device_info.isFormatSupported( ctx->m_format ) ) {
      qDebug() << "Format not supported by the output device";
      return;
   }

   //Initialize the audio output device
   ctx->m_audio_output = new QAudioOutput( ctx->m_output_device_info, ctx->m_format, qApp );

   //Compute the size in bytes to be buffered based on the current format
   ctx->m_size_to_buffer = int( timeToSize( ctx->m_time_to_buffer, ctx->m_format ) );

   ctx->m_output_device = ctx->m_audio_output->start();

   if ( !ctx->m_output_device ) {
      qDebug() << "Failed to open output audio device";
      return;
   }

}

