#include "AudioComponent.h"

AudioComponent::AudioComponent(const char* filePath, const int length): m_filePath(filePath), m_length(length) {}

const char* AudioComponent::getFilePath() {
  return m_filePath;
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

bool AudioComponent::operator==(const AudioComponent &other) const {
  return m_filePath == other.getFilePath();
}
