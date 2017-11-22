#pragma once

#include <string>

struct AudioComponent {
public:
  AudioComponent();
  AudioComponent(const std::string filePath, const int length);
  const char* getFilePath() const;
  int getLength() const;
  int getId() const;
  void setId(int id);
  bool isEmpty();
  bool operator==(const AudioComponent &other) const;
  // AudioComponent& operator=(const AudioComponent&);
private:
  const std::string m_filePath;
  const int m_length;
  int m_id;
};
