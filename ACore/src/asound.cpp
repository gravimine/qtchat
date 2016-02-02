#include "asound.h"
#include <QString>
#include <QFile>
using ACore::ASound;
ASound::ASound()
{

}
ASound::~ASound()
{
}
void ASound::SetPatch(QString file)
{
  patch=file;
}
void ASound::start()
{
}
