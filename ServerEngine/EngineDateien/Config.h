// mit Vektor
#pragma once

#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>

// Maximale Werte
constexpr int MAX_HIGHSCORES = 10;   // Max Highscores
constexpr int MAX_NAME_LENGTH = 50;  // Max Länge eines Spielernamens
constexpr int MAX_OBJECTS = 40;       // Max Anzahl an Spielfeldern/Objekten
constexpr int MAX_PLAYERS = 4;        // Max Spieler

// Spielregeln (für Preise etc.)
struct GameRules {
    int baseStreetPrice = 0;
    int baseHousePrice = 0;
    int baseHotelPrice = 0;
    float priceIncreasePercent = 0.0f;
};

// Highscore-Eintrag
struct HighscoreEntry {
    std::string playerName;
    int score;
};

// Zustand eines einzelnen Spielers
struct PlayerState {
    std::string name;
    int budget = 0;
    int position = 0;
    bool inJail = false;
    bool hasFreeJailCard = false;
    std::vector<int> ownedObjects;
    std::vector<int> builtObjects;
};

// Gesamtspielstand
struct GameState {
    int roundCount = 0;
    int currentPlayerIndex = 0;
    std::vector<int> diceOrder;
    std::vector<PlayerState> players;
};

// Funktionsprototypen
bool load_config(const std::string& filename, GameRules& rules);
bool save_config(const std::string& filename, const GameRules& rules);

bool load_highscores(const std::string& filename, std::vector<HighscoreEntry>& highscores);
bool save_highscores(const std::string& filename, const std::vector<HighscoreEntry>& highscores);
void sort_highscores(std::vector<HighscoreEntry>& highscores);

bool log_action(const std::string& filename, const std::string& action);
bool load_log(const std::string& filename, std::vector<std::string>& logLines);

bool save_game(const std::string& filename, const GameState& state);
bool load_game(const std::string& filename, GameState& state);

#endif
