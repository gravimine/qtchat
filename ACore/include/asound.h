#ifndef ASOUND_H
#define ASOUND_H
//#include <QAudioOutput>
#include <QString>
namespace ACore
{
class ASound
{
private:
  QString patch;
public:
  ASound();
  ~ASound();
  void SetPatch(QString file);
  void start();
};
}

#endif // ASOUND_H
