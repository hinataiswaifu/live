#pragma once

#include <string>

struct AudioComponent {
public:
  AudioComponent(const string filePath, const int length);
  const char* getFilePath() const;
  const int getLength();
  const int getId();
  void setId(int id);
  bool isEmpty();
  bool operator==(const AudioComponent &other) const;
  AudioComponent& operator=(const AudioComponent&);
private:
  const string m_filePath;
  const int m_length;
  int m_id;
};
