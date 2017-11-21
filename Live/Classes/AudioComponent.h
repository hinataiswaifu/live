#pragma once

class AudioComponent {
public:
  AudioComponent(const char* filePath, const int length);
  const char* getFilePath() const;
  const int getLength();
  const int getId();
  void setId(int id);
  bool operator==(const AudioComponent &other) const;
private:
  const char* m_filePath;
  const int m_length;
  int m_id;
};
