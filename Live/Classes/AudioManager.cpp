

void changeBackgroundMusic(AudioComponent bgm) {
  m_game_bg_music = bgm;
  stopBackgroundMusic();
  playBackgroundMusic(bgm.getFilePath(), true);
}

void changeWeatherSFX(AudioComponent bgm) {
  if ( m_weather_bg_music != NULL )
    stopEffect(m_weather_bg_music.getId());
  m_weather_bg_music = bgm;
  m_weather_bg_music.setId(playEffect(bgm.getFilePath(), true));
}

void enqueueRandomSFX(AudioComponent[] clips, int size) {
  m_audio_queue.push(clips[rand()%size]);
  dequeueSFXIfAvailable();
}

void enqueueSFX(AudioComponent clip) {
  m_audio_queue.push(clip);
  dequeueSFXIfAvailable();
}

void dequeueSFXIfAvailable() {
  if (m_audio_queue.size() == 0) {
    playEffect(m_audio_queue.front(), false);
    m_audio_queue.pop();
  }
}

AudioManager* AudioManager::getInstance() {
    if (!AudioManager::instance)
        AudioManager::instance = new AudioManager();
    return AudioManager::instance;
}

AudioManager* AudioManager::instance = nullptr;
