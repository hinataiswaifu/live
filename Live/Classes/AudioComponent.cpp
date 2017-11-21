#include "AudioComponent.h"

AudioComponent(const char* filePath, const int length): filePath(filePath), length(length) {}

const char* getFilePath() {
  return m_filePath;
}

const int getLength() {
  return m_length;
}

const int getId() {
  return m_id;
}

void setId(int id) {
  m_id = id;
}

bool AudioComponent::operator==(const AudioComponent &other) const {
  return m_filePath == other.getFilePath();
}
