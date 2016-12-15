#ifndef EEP_H
#define EEP_H

struct HighScore {
  char name[3];
  int score;
  HighScore(char _name[], int _score) {
    name[0] = _name[0];
    name[1] = _name[1];
    name[2] = _name[2];
    score = _score;
  }
};

HighScore getHighScore(int index);

void addHighScore(char name[3], int score);

#endif