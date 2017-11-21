class AudioComponent {
public:
  AudioComponent(const char* filePath, const int length);
  const char* getFilePath();
  const int getLength();
  const int getId();
  void setId();

private:
  const char* m_filePath;
  const int m_length;
  int m_id;
}
