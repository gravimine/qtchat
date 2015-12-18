#include "asound.h"
#include <QAudioOutput>
#include <QString>
#include <QFile>
using ACore::ASound;
ASound::ASound()
{

}
ASound::~ASound()
{
  if(audio) delete audio;
}
void ASound::SetPatch(QString file)
{
  patch=file;
}
void ASound::start()
{
  if(!audio) audio=new QAudioOutput();
  QFile file;
  file.setFileName(patch);
  file.open(QFile::ReadOnly);
  audio->start(&file);
}
