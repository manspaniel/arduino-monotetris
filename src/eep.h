#ifndef EEP_H
#define EEP_H

#define EEP_MUSIC_MUTED_ADDR    0x0
#define EEP_N_GAMES_PLAYED      0x1
#define EEP_N_SCORES_SAVED      0x3
#define EEP_SCORES_ADDR         0x5

#define EEP_TOTAL_HIGHSCORES    5

struct HighScore {
  char name[6];
  int score;
  HighScore() {
    name[0] = ' ';
    name[1] = ' ';
    name[2] = ' ';
    name[3] = ' ';
    name[4] = ' ';
    name[5] = ' ';
  }
};

HighScore getHighScore(int index);
// HighScore getScoreToBeat(int score);
void setHighScore(int index, HighScore entry);
void addHighScore(HighScore entry);
bool isHighScore(int score);
void eraseHighScores();

// Muting
bool isMuted();
void setMuted(bool val);

#endif