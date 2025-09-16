#include "audio_manager.h"

#include <cassert>

namespace Raykout {

  AudioManager* AudioManager::instance = nullptr;

  AudioManager::AudioManager() {
    assert(nullptr == instance);

    soloud_.init();
    samples_.reserve(RESERVED_SAMPLES);
  }

  AudioManager::~AudioManager() {}

  AudioManager& AudioManager::Instance() {
    if (nullptr == instance) {
      instance = new AudioManager();
    }
    return *instance;
  }

  SampleHandle AudioManager::load(const char* filename) {
    auto it = cache_.find(filename);
    if (cache_.end() != it) {
      return (SampleHandle)it->second;
    }

    SampleHandle result = (SampleHandle)samples_.size();
    samples_.emplace_back();
    samples_.back().load(filename);
    cache_[filename] = result;
    return result;
  }

  VoiceHandle AudioManager::play(SampleHandle sample_handle) {
    assert(0 <= sample_handle && samples_.size() > sample_handle);

    return (VoiceHandle) soloud_.play(samples_[sample_handle]);
  }

  void AudioManager::stop(VoiceHandle voice_handle) {
    soloud_.stop(voice_handle);
  }
}
