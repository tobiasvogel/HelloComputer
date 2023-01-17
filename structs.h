#ifndef STRUCTS_H
#define STRUCTS_H

#include <QtMultimedia/QAudioOutput>
#include <QtMultimedia/QAudioDeviceInfo>

struct AudioContext {
   QAudioOutput *m_audio_output;
   QIODevice *m_output_device;

   QByteArray m_buffer;

   QAudioDeviceInfo m_output_device_info;
   QAudioFormat m_format;

   int m_time_to_buffer;

   int m_size_to_buffer;

   /*** Tone generator variables ***/
   uint m_frequency;

   uint m_duration_msecs;

   bool m_reverse = false;
   /*** Tone generator variables ***/

   bool m_play_called = false;
};

#endif // STRUCTS_H
