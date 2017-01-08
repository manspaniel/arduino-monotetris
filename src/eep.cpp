#include "eep.h"
#include <EEPROM.h>

HighScore getHighScore(int index) {
  HighScore entry;
  EEPROM.get((int)EEP_SCORES_ADDR + sizeof(HighScore) * index, entry);
  return entry;
}

void setHighScore(int index, HighScore entry) {
  EEPROM.put((int)EEP_SCORES_ADDR + sizeof(HighScore) * index, entry);
}

void addHighScore(HighScore newEntry) {
  int targetIndex = EEP_TOTAL_HIGHSCORES;
  for(int k = EEP_TOTAL_HIGHSCORES; k >= 0; k--) {
    HighScore entry = getHighScore(k);
    if(entry.score < newEntry.score) {
      // This score is LESS than the new score, so copy the score above into this one
      if(k > 0) {
        setHighScore(k, getHighScore(k-1));
      }
      // Set the target index for the new score to this item
      targetIndex = k;
    } else {
      // No more changes required
      break;
    }
  }
  // Add the new score at the target index
  setHighScore(targetIndex, newEntry);
}

void eraseHighScores() {
  
  for(int index = 0; index < EEP_TOTAL_HIGHSCORES; index++) {
    HighScore entry;
    entry.score = 0;
    EEPROM.put((int)EEP_SCORES_ADDR + sizeof(HighScore) * index, entry);
  }
}

bool isHighScore(int score) {
  
  // Otherwise, as long as the score is higher than the current 5th high score, then yep it's a high score
  HighScore lowestScore;
  EEPROM.get((int)EEP_SCORES_ADDR + sizeof(HighScore) * (EEP_TOTAL_HIGHSCORES - 1), lowestScore);
  if(score > lowestScore.score) {
    return true;
  } else {
    return false;
  }
  
}

// Mute/unmute
static bool _cachedMutedValue = false;
static bool _mutedValueIsCached = false;

bool isMuted() {
  if(!_mutedValueIsCached) {
    _mutedValueIsCached = true;
    _cachedMutedValue = EEPROM.read(EEP_MUSIC_MUTED_ADDR) ? true : false;
  }
  return _cachedMutedValue;
}

void setMuted(bool state) {
  _mutedValueIsCached = true;
  _cachedMutedValue = state;
  EEPROM.write(EEP_MUSIC_MUTED_ADDR, state ? 1 : 0);
}