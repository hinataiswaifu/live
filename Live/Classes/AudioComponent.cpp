#include "AudioComponent.h"
#include "AudioManager.h"

AudioComponent::AudioComponent(const string filePath, const int length): m_filePath(filePath), m_length(length) {
  AudioManager::getInstance()->preloadEffect(this);
}

const char* AudioComponent::getFilePath() const {
  return m_filePath.c_str();
}

const int AudioComponent::getLength() {
  return m_length;
}

const int AudioComponent::getId() {
  return m_id;
}

void AudioComponent::setId(int id) {
  m_id = id;
}

bool AudioComponent::isEmpty() {
  return m_filePath == nullptr;
}

bool AudioComponent::operator==(const AudioComponent &other) const {
  return m_filePath == other.getFilePath();
}

AudioComponent& AudioComponent::operator=(const AudioComponent& a) {
  m_filePath = a.getFilePath();
  m_length = a.getLength();
  m_id = a.getId();

  return *this
}
