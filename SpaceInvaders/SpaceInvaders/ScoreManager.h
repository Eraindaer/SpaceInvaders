#pragma once
#include <string>
class ScoreManager {
public:
	ScoreManager(){}
	~ScoreManager(){}

	inline void AddScore(int x) { score += x; }
	inline void SetScore(int x) { score = x; }

	inline int GetScore() { return score; }

private:
	int score;
};