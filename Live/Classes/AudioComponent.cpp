#include "AudioComponent.h"
#include "AudioManager.h"
#include <cctype>

AudioComponent::AudioComponent() {}

AudioComponent::AudioComponent(const std::string filePath, int length):
  m_filePath(filePath), m_length(length) {
  AudioManager::getInstance()->preloadEffect(*this);
}

const char* AudioComponent::getFilePath() const {
  return m_filePath.c_str();
}

int AudioComponent::getLength() const {
  return m_length;
}

int AudioComponent::getId() const {
  return m_id;
}

void AudioComponent::setId(int id) {
  m_id = id;
}

bool AudioComponent::isEmpty() {
  return m_filePath.empty();
}

bool AudioComponent::operator==(const AudioComponent &other) const {
  return m_filePath == other.getFilePath();
}
