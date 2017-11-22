#pragma once

#include <string>

struct AudioComponent {
public:
  AudioComponent();

  // Pass in path to audio file, and length (in milliseconds)
  AudioComponent(std::string filePath, int length);

  const char* getFilePath() const;
  int getLength() const;
  int getId() const;
  void setId(int id);
  bool isEmpty();
  bool operator==(const AudioComponent &other) const;
private:
  std::string m_filePath;
  int m_length;
  int m_id;
};
