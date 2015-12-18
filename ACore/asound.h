#ifndef ASOUND_H
#define ASOUND_H
#include <QAudioOutput>
#include <QString>
namespace ACore
{
class ASound
{
private:
  QString patch;
public:
  QAudioOutput *audio;
  QAudioFormat format;
  ASound();
  ~ASound();
  void SetPatch(QString file);
  void start();
};
}

#endif // ASOUND_H
