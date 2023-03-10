#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_settingsdialog.h"
#include "colorpalette.h"

#include <QTimer>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QtMath>
#include <QDebug>
#include <QScreen>
#include <QGraphicsView>
#include <QGraphicsScene>
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

   QScreen *screen = QGuiApplication::primaryScreen();

   ui->copyrightLabel->setText( QString( "%1 2023 Tobias X. Vogel" ).arg( QString::fromWCharArray( L"\x00A9" ) ) );
   ui->copyrightLabel->adjustSize();
   ui->copyrightLabel->setGeometry( ( screen->geometry().width() - ui->copyrightLabel->width() - 20 ),
                                    ( screen->geometry().height() - ui->copyrightLabel->height() - 12 ),
                                    ui->copyrightLabel->width(),
                                    ui->copyrightLabel->height() );

   delayTimer = new QTimer( this );
   delayTimer->setSingleShot( true );
   delayTimer->setInterval( 330 );

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

   settingsDlg();

   #ifdef QT_DEBUG
   qDebug() << "Palette \"complete\" contains " << get_palette_size_complete() << " colors.";
   qDebug() << "Palette \"vibrant\" contains " << get_palette_size_vibrant() << " colors.";
   qDebug() << "Palette \"pastel\" contains " << get_palette_size_pastel() << " colors.";
   #endif
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
         switch ( usePalette ) {
            case COMPLETE:
               if ( GROUP1_complete.size() == 1 ) {
                  randCol = 0;

               } else {
                  randCol = QRandomGenerator::global()->bounded( 0, ( GROUP1_complete.size() - 1 ) );
               }

               color = GROUP1_complete.at( randCol );
               break;

            case VIBRANT:
               if ( GROUP1_vibrant.size() == 1 ) {
                  randCol = 0;

               } else {
                  randCol = QRandomGenerator::global()->bounded( 0, ( GROUP1_vibrant.size() - 1 ) );
               }

               color = GROUP1_vibrant.at( randCol );
               break;

            case PASTEL:
               if ( GROUP1_pastel.size() == 1 ) {
                  randCol = 0;

               } else {
                  randCol = QRandomGenerator::global()->bounded( 0, ( GROUP1_pastel.size() - 1 ) );
               }

               color = GROUP1_pastel.at( randCol );
               break;

            default:
               break;
         }

         break;

      case 2:
         switch ( usePalette ) {
            case COMPLETE:
               if ( GROUP2_complete.size() == 1 ) {
                  randCol = 0;

               } else {
                  randCol = QRandomGenerator::global()->bounded( 0, ( GROUP2_complete.size() - 1 ) );
               }

               color = GROUP2_complete.at( randCol );
               break;

            case VIBRANT:
               if ( GROUP2_vibrant.size() == 1 ) {
                  randCol = 0;

               } else {
                  randCol = QRandomGenerator::global()->bounded( 0, ( GROUP2_vibrant.size() - 1 ) );
               }

               color = GROUP2_vibrant.at( randCol );
               break;

            case PASTEL:
               if ( GROUP2_pastel.size() == 1 ) {
                  randCol = 0;

               } else {
                  randCol = QRandomGenerator::global()->bounded( 0, ( GROUP2_pastel.size() - 1 ) );
               }

               color = GROUP2_pastel.at( randCol );
               break;

            default:
               break;
         }

         break;

      case 3:
         switch ( usePalette ) {
            case COMPLETE:
               if ( GROUP3_complete.size() == 1 ) {
                  randCol = 0;

               } else {
                  randCol = QRandomGenerator::global()->bounded( 0, ( GROUP3_complete.size() - 1 ) );
               }

               color = GROUP3_complete.at( randCol );
               break;

            case VIBRANT:
               if ( GROUP3_vibrant.size() == 1 ) {
                  randCol = 0;

               } else {
                  randCol = QRandomGenerator::global()->bounded( 0, ( GROUP3_vibrant.size() - 1 ) );
               }

               color = GROUP3_vibrant.at( randCol );
               break;

            case PASTEL:
               if ( GROUP3_pastel.size() == 1 ) {
                  randCol = 0;

               } else {
                  randCol = QRandomGenerator::global()->bounded( 0, ( GROUP3_pastel.size() - 1 ) );
               }

               color = GROUP3_pastel.at( randCol );
               break;

            default:
               break;
         }

         break;

      case 4:
         switch ( usePalette ) {
            case COMPLETE:
               if ( GROUP4_complete.size() == 1 ) {
                  randCol = 0;

               } else {
                  randCol = QRandomGenerator::global()->bounded( 0, ( GROUP4_complete.size() - 1 ) );
               }

               color = GROUP4_complete.at( randCol );
               break;

            case VIBRANT:
               if ( GROUP4_vibrant.size() == 1 ) {
                  randCol = 0;

               } else {
                  randCol = QRandomGenerator::global()->bounded( 0, ( GROUP4_vibrant.size() - 1 ) );
               }

               color = GROUP4_vibrant.at( randCol );
               break;

            case PASTEL:
               if ( GROUP4_pastel.size() == 1 ) {
                  randCol = 0;

               } else {
                  randCol = QRandomGenerator::global()->bounded( 0, ( GROUP4_pastel.size() - 1 ) );
               }

               color = GROUP4_pastel.at( randCol );
               break;

            default:
               break;
         }

         break;

      case 5:
         switch ( usePalette ) {
            case COMPLETE:
               if ( GROUP5_complete.size() == 1 ) {
                  randCol = 0;

               } else {
                  randCol = QRandomGenerator::global()->bounded( 0, ( GROUP5_complete.size() - 1 ) );
               }

               color = GROUP5_complete.at( randCol );
               break;

            case VIBRANT:
               if ( GROUP5_vibrant.size() == 1 ) {
                  randCol = 0;

               } else {
                  randCol = QRandomGenerator::global()->bounded( 0, ( GROUP5_vibrant.size() - 1 ) );
               }

               color = GROUP5_vibrant.at( randCol );
               break;

            case PASTEL:
               if ( GROUP5_pastel.size() == 1 ) {
                  randCol = 0;

               } else {
                  randCol = QRandomGenerator::global()->bounded( 0, ( GROUP5_pastel.size() - 1 ) );
               }

               color = GROUP5_pastel.at( randCol );
               break;

            default:
               break;
         }

         break;

      case 6:
         switch ( usePalette ) {
            case COMPLETE:
               if ( GROUP6_complete.size() == 1 ) {
                  randCol = 0;

               } else {
                  randCol = QRandomGenerator::global()->bounded( 0, ( GROUP6_complete.size() - 1 ) );
               }

               color = GROUP6_complete.at( randCol );
               break;

            case VIBRANT:
               if ( GROUP6_vibrant.size() == 1 ) {
                  randCol = 0;

               } else {
                  randCol = QRandomGenerator::global()->bounded( 0, ( GROUP6_vibrant.size() - 1 ) );
               }

               color = GROUP6_vibrant.at( randCol );
               break;

            case PASTEL:
               if ( GROUP6_pastel.size() == 1 ) {
                  randCol = 0;

               } else {
                  randCol = QRandomGenerator::global()->bounded( 0, ( GROUP6_pastel.size() - 1 ) );
               }

               color = GROUP6_pastel.at( randCol );
               break;

            default:
               break;
         }

         break;

      case 7:
         switch ( usePalette ) {
            case COMPLETE:
               if ( GROUP7_complete.size() == 1 ) {
                  randCol = 0;

               } else {
                  randCol = QRandomGenerator::global()->bounded( 0, ( GROUP7_complete.size() - 1 ) );
               }

               color = GROUP7_complete.at( randCol );
               break;

            case VIBRANT:
               if ( GROUP7_vibrant.size() == 1 ) {
                  randCol = 0;

               } else {
                  randCol = QRandomGenerator::global()->bounded( 0, ( GROUP7_vibrant.size() - 1 ) );
               }

               color = GROUP7_vibrant.at( randCol );
               break;

            case PASTEL:
               if ( GROUP7_pastel.size() == 1 ) {
                  randCol = 0;

               } else {
                  randCol = QRandomGenerator::global()->bounded( 0, ( GROUP7_pastel.size() - 1 ) );
               }

               color = GROUP7_pastel.at( randCol );
               break;

            default:
               break;
         }

         break;

      case 8:
         switch ( usePalette ) {
            case COMPLETE:
               if ( GROUP8_complete.size() == 1 ) {
                  randCol = 0;

               } else {
                  randCol = QRandomGenerator::global()->bounded( 0, ( GROUP8_complete.size() - 1 ) );
               }

               color = GROUP8_complete.at( randCol );
               break;

            case VIBRANT:
               if ( GROUP8_vibrant.size() == 1 ) {
                  randCol = 0;

               } else {
                  randCol = QRandomGenerator::global()->bounded( 0, ( GROUP8_vibrant.size() - 1 ) );
               }

               color = GROUP8_vibrant.at( randCol );
               break;

            case PASTEL:
               if ( GROUP8_pastel.size() == 1 ) {
                  randCol = 0;

               } else {
                  randCol = QRandomGenerator::global()->bounded( 0, ( GROUP8_pastel.size() - 1 ) );
               }

               color = GROUP8_pastel.at( randCol );
               break;

            default:
               break;
         }

         break;

      case 9:
         switch ( usePalette ) {
            case COMPLETE:
               if ( GROUP9_complete.size() == 1 ) {
                  randCol = 0;

               } else {
                  randCol = QRandomGenerator::global()->bounded( 0, ( GROUP9_complete.size() - 1 ) );
               }

               color = GROUP9_complete.at( randCol );
               break;

            case VIBRANT:
               if ( GROUP9_vibrant.size() == 1 ) {
                  randCol = 0;

               } else {
                  randCol = QRandomGenerator::global()->bounded( 0, ( GROUP9_vibrant.size() - 1 ) );
               }

               color = GROUP9_vibrant.at( randCol );
               break;

            case PASTEL:
               if ( GROUP9_pastel.size() == 1 ) {
                  randCol = 0;

               } else {
                  randCol = QRandomGenerator::global()->bounded( 0, ( GROUP9_pastel.size() - 1 ) );
               }

               color = GROUP9_pastel.at( randCol );
               break;

            default:
               break;
         }

         break;

      case 10:
         switch ( usePalette ) {
            case COMPLETE:
               if ( GROUP10_complete.size() == 1 ) {
                  randCol = 0;

               } else {
                  randCol = QRandomGenerator::global()->bounded( 0, ( GROUP10_complete.size() - 1 ) );
               }

               color = GROUP10_complete.at( randCol );
               break;

            case VIBRANT:
               if ( GROUP10_vibrant.size() == 1 ) {
                  randCol = 0;

               } else {
                  randCol = QRandomGenerator::global()->bounded( 0, ( GROUP10_vibrant.size() - 1 ) );
               }

               color = GROUP10_vibrant.at( randCol );
               break;

            case PASTEL:
               if ( GROUP10_pastel.size() == 1 ) {
                  randCol = 0;

               } else {
                  randCol = QRandomGenerator::global()->bounded( 0, ( GROUP10_pastel.size() - 1 ) );
               }

               color = GROUP10_pastel.at( randCol );
               break;

            default:
               return;
               break;
         }

         break;

      default: // should never be reached!
         return;
         break;
   }

   ui->_debugKeyPress->setText( QString( "%1; %2" ).arg( randNum ).arg( randCol ) );
   lastColorGroup = randNum;
   this->setStyleSheet( QString( "background-color: %1;" ).arg( color ) );

   QColor _color;
   _color.setNamedColor( color );

   if ( determineTextColor( _color ) == 0 ) {
      ui->label->setStyleSheet( "color: #000000;" );
      ui->copyrightLabel->setStyleSheet( "color: #000000;" );

   } else {
      ui->label->setStyleSheet( "color: #ffffff;" );
      ui->copyrightLabel->setStyleSheet( "color: #ffffff;" );
   }
}

bool MainWindow::determineTextColor( QColor color ) { // as in http://www.w3.org/TR/AERT#color-contrast
   // if zero is returned, text should be black, otherwise white for readability
   int brightness = qRound( ( float )( ( color.red() * 299 ) + ( color.green() * 587 ) + ( color.blue() * 114 ) ) / 1000 );

   if ( brightness > 125 ) {
      return 0;

   } else {
      return 1;
   }
}

void MainWindow::settingsDlg() {
   settingsDialog = new QDialog( this, 0 );
   Ui_Dialog dialogUi;
   dialogUi.setupUi( settingsDialog );

   dialogUi.startBtn->setIcon( QIcon( ":run.png" ) );
   dialogUi.startBtn->setIconSize( QSize( 24, 24 ) );
   dialogUi.quitBtn->setIcon( QIcon( ":quit.png" ) );
   dialogUi.quitBtn->setIconSize( QSize( 24, 24 ) );

   QObject::connect( dialogUi.quitBtn, SIGNAL( clicked() ), this, SLOT( quit() ) );
   QObject::connect( dialogUi.startBtn, SIGNAL( clicked() ), this, SLOT( run() ) );
   QObject::connect( dialogUi.volumeSettingSlider, &QAbstractSlider::valueChanged, [this, dialogUi]( int value ) { dialogUi.volumeSettingPercentageLabel->setText( QString( "%1%" ).arg( value ) ); _volume = value; } );
   QObject::connect( dialogUi.soundSettingCheckbox, &QCheckBox::stateChanged, [ this ]( int value ) { if ( value == Qt::Checked ) { _playSound = true; } else { _playSound = false; } } );
   QObject::connect( dialogUi.frequencySettingSpinBox, QOverload<int>::of( &QSpinBox::valueChanged ), [ this ]( int value ) { if ( value > 99 && value < 3001 ) { _delayDuration = value; } } );

   QString clrGrpStr_complete( tr( "Komplett (%1 Farben)" ).arg( get_palette_size_complete() ) );
   QString clrGrpStr_vibrant( tr( "Bunt (%1 Farben)" ).arg( get_palette_size_vibrant() ) );
   QString clrGrpStr_pastel( tr( "Pastell (%1 Farben" ).arg( get_palette_size_pastel() ) );
   dialogUi.colorSettingComboBox->addItem( clrGrpStr_complete, COMPLETE );
   dialogUi.colorSettingComboBox->addItem( clrGrpStr_vibrant, VIBRANT );
   dialogUi.colorSettingComboBox->addItem( clrGrpStr_pastel, PASTEL );

   graphicsScene = new QGraphicsScene( settingsDialog );
   graphicsView = new QGraphicsView( graphicsScene, dialogUi.settingsGrpBox );

   QScreen *screen = QGuiApplication::primaryScreen();

   int x = ( screen->geometry().width() - settingsDialog->width() ) / 2;
   int y = ( screen->geometry().height() - settingsDialog->height() ) / 2;
   settingsDialog->move( x, y );

   settingsDialog->show();

   settingsDialog->setModal( true );

   QPixmap pixm = QPixmap( ":banner.png" );
   int pixm_w = dialogUi.graphicLabel->width() - 8;
   int pixm_h = dialogUi.graphicLabel->height() - 8;
   dialogUi.graphicLabel->setPixmap( pixm.scaled( pixm_w, pixm_h, Qt::KeepAspectRatio ) );

   int gv_X = dialogUi.colorSettingLabel->x();
   int gv_Y = dialogUi.colorSettingComboBox->pos().y() + dialogUi.colorSettingComboBox->height() + 10;
   int gv_W = dialogUi.colorSettingComboBox->pos().x() + dialogUi.colorSettingComboBox->width() - gv_X;
   int gv_H = dialogUi.settingsGrpBox->height() - gv_Y - 14;

   graphicsView->setGeometry( gv_X, gv_Y, gv_W, gv_H );

   graphicsRect = graphicsView->rect();

   this->renderColorPreview( usePalette, graphicsView->rect() );

   QObject::connect( dialogUi.colorSettingComboBox, QOverload<int>::of( &QComboBox::currentIndexChanged ), [this, dialogUi]( int index ) {
      if ( dialogUi.colorSettingComboBox->itemData( index ) == COMPLETE ) { usePalette = COMPLETE; this->renderColorPreview( usePalette, graphicsRect ); }

      if ( dialogUi.colorSettingComboBox->itemData( index ) == VIBRANT ) { usePalette = VIBRANT; this->renderColorPreview( usePalette, graphicsRect ); }

      if ( dialogUi.colorSettingComboBox->itemData( index ) == PASTEL ) { usePalette = PASTEL; this->renderColorPreview( usePalette, graphicsRect ); }
   } );

}

void MainWindow::keyPressEvent( QKeyEvent *event ) {
   if ( !_hasStarted ) { return; }

   if ( _delayPaused ) { return; }

   #ifdef QT_DEBUG
   ui->_debugKeyPress->setText( QString( event->key() ) );
   #endif
   this->changeColor();

   _delayPaused = true;
   delayTimer->singleShot( _delayDuration, [ = ] { _delayPaused = false; } );

   if ( _playSound ) {
      this->play( &ctx );
   }
}

void MainWindow::closeEvent( QCloseEvent *event ) {
   event->ignore();
}


static inline int timeToSize( int ms, const QAudioFormat &format ) {
   return ( ( format.channelCount() * ( format.sampleSize() / 8 ) * format.sampleRate() ) * ms / 1000 );
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

   ctx->m_audio_output->setVolume( ( ( float ) _volume ) / 100 );

   //Compute the size in bytes to be buffered based on the current format
   ctx->m_size_to_buffer = int( timeToSize( ctx->m_time_to_buffer, ctx->m_format ) );

   ctx->m_output_device = ctx->m_audio_output->start();

   if ( !ctx->m_output_device ) {
      qDebug() << "Failed to open output audio device";
      return;
   }

}

void MainWindow::renderColorPreview( Palette p, QRect rect ) {
   QVector<QColor> colorList;

   graphicsScene->clear();

   if ( p == COMPLETE ) {
      Q_FOREACH ( QString str, GROUP1_complete ) {
         colorList.append( QColor( str ) );
      }

      Q_FOREACH ( QString str, GROUP2_complete ) {
         colorList.append( QColor( str ) );
      }

      Q_FOREACH ( QString str, GROUP3_complete ) {
         colorList.append( QColor( str ) );
      }

      Q_FOREACH ( QString str, GROUP4_complete ) {
         colorList.append( QColor( str ) );
      }

      Q_FOREACH ( QString str, GROUP5_complete ) {
         colorList.append( QColor( str ) );
      }

      Q_FOREACH ( QString str, GROUP6_complete ) {
         colorList.append( QColor( str ) );
      }

      Q_FOREACH ( QString str, GROUP7_complete ) {
         colorList.append( QColor( str ) );
      }

      Q_FOREACH ( QString str, GROUP8_complete ) {
         colorList.append( QColor( str ) );
      }

      Q_FOREACH ( QString str, GROUP9_complete ) {
         colorList.append( QColor( str ) );
      }

      Q_FOREACH ( QString str, GROUP10_complete ) {
         colorList.append( QColor( str ) );
      }

   } else if ( p == VIBRANT ) {
      Q_FOREACH ( QString str, GROUP1_vibrant ) {
         colorList.append( QColor( str ) );
      }

      Q_FOREACH ( QString str, GROUP2_vibrant ) {
         colorList.append( QColor( str ) );
      }

      Q_FOREACH ( QString str, GROUP3_vibrant ) {
         colorList.append( QColor( str ) );
      }

      Q_FOREACH ( QString str, GROUP4_vibrant ) {
         colorList.append( QColor( str ) );
      }

      Q_FOREACH ( QString str, GROUP5_vibrant ) {
         colorList.append( QColor( str ) );
      }

      Q_FOREACH ( QString str, GROUP6_vibrant ) {
         colorList.append( QColor( str ) );
      }

      Q_FOREACH ( QString str, GROUP7_vibrant ) {
         colorList.append( QColor( str ) );
      }

      Q_FOREACH ( QString str, GROUP8_vibrant ) {
         colorList.append( QColor( str ) );
      }

      Q_FOREACH ( QString str, GROUP9_vibrant ) {
         colorList.append( QColor( str ) );
      }

      Q_FOREACH ( QString str, GROUP10_vibrant ) {
         colorList.append( QColor( str ) );
      }

   } else if ( p == PASTEL ) {
      Q_FOREACH ( QString str, GROUP1_pastel ) {
         colorList.append( QColor( str ) );
      }

      Q_FOREACH ( QString str, GROUP2_pastel ) {
         colorList.append( QColor( str ) );
      }

      Q_FOREACH ( QString str, GROUP3_pastel ) {
         colorList.append( QColor( str ) );
      }

      Q_FOREACH ( QString str, GROUP4_pastel ) {
         colorList.append( QColor( str ) );
      }

      Q_FOREACH ( QString str, GROUP5_pastel ) {
         colorList.append( QColor( str ) );
      }

      Q_FOREACH ( QString str, GROUP6_pastel ) {
         colorList.append( QColor( str ) );
      }

      Q_FOREACH ( QString str, GROUP7_pastel ) {
         colorList.append( QColor( str ) );
      }

      Q_FOREACH ( QString str, GROUP8_pastel ) {
         colorList.append( QColor( str ) );
      }

      Q_FOREACH ( QString str, GROUP9_pastel ) {
         colorList.append( QColor( str ) );
      }

      Q_FOREACH ( QString str, GROUP10_pastel ) {
         colorList.append( QColor( str ) );
      }

   } else {
      return;
   }

   int i = 0;
   int j = 0;
   int w = ( rect.width() / 33 );
   int h = ( rect.height() / 4 ) - 4;

   Q_FOREACH ( QColor color, colorList ) {
#if defined(Q_OS_LINUX) || defined(Q_WS_X11)
      graphicsScene->addRect( 2 + ( i * w ) + i, 2 + ( h * j ) + ( j * 2 ), w, h, QPen( Qt::transparent ), QBrush( QColor( color ) ) );
#else
      graphicsScene->addRect( 2 + ( i * w ), 2 + ( h * j ) + ( j * 2 ), w, h, QPen( Qt::transparent ), QBrush( QColor( color ) ) );
#endif
      i++;

      if ( i % 32 == 0 ) {
         j++;
         i = 0;
      }
   }
}

void MainWindow::run() {
   qApp->setOverrideCursor( QCursor( Qt::BlankCursor ) );
   settingsDialog->hide();
   this->grabKeyboard();
   this->grabMouse();

   init( &ctx );

   _delayPaused = false;
   _hasStarted = true;
}

void MainWindow::quit() {
   qApp->closeAllWindows();
   qApp->quit();
}

