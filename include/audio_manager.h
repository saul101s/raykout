#pragma once

#include <vector>
#include <unordered_map>

#define SOLOUD_NO_ASSERTS // Avoid including windows.h
#include "soloud_wav.h"

namespace Raykout {

constexpr int RESERVED_SAMPLES = 64;

typedef unsigned int VoiceHandle;
typedef int SampleHandle;

class AudioManager {
  static AudioManager* instance;

 public:
  ~AudioManager();
  static AudioManager& Instance();

  SampleHandle load(const char* filename);
  VoiceHandle play(SampleHandle sample_handle);
  void stop(VoiceHandle voice_handle);

 private:
  AudioManager();

 private:
  SoLoud::Soloud soloud_;
  std::vector<SoLoud::Wav> samples_;
  std::unordered_map<const char*, SampleHandle> cache_;
};
}  // namespace Raykout
