// mit Vector
//Config.cpp

#include "Config.h"


// Konfiguration laden
bool load_config(const std::string& filename, GameRules& rules) 
{
    std::ifstream file(filename);   // Datei zum Lesen öffnen
    if (!file.is_open()) return false;

    std::string line;
    while (std::getline(file, line)) // Zeilenweise lesen
    {
        auto pos = line.find('=');  // Trenne Schlüssel und Werte mit =
        if (pos == std::string::npos) continue; // überspringen von ungültigen Zeichen
        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);
        // Weisen dem passenden Attribut in GameRules den Wert zu
        if (key == "baseStreetPrice") rules.baseStreetPrice = std::stoi(value);
        else if (key == "baseHousePrice") rules.baseHousePrice = std::stoi(value);
        else if (key == "baseHotelPrice") rules.baseHotelPrice = std::stoi(value);
        else if (key == "priceIncreasePercent") rules.priceIncreasePercent = std::stof(value);
    }

    return true;
}

// Speichert die Spielregeln in einer Konfigurationsdatei
bool save_config(const std::string& filename, const GameRules& rules) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    // Schreibe Spielregeln in die Datei
    file << "baseStreetPrice=" << rules.baseStreetPrice << "\n";
    file << "baseHousePrice=" << rules.baseHousePrice << "\n";
    file << "baseHotelPrice=" << rules.baseHotelPrice << "\n";
    file << "priceIncreasePercent=" << rules.priceIncreasePercent << "\n";

    return true;
}

// Highscores laden
bool load_highscores(const std::string& filename, std::vector<HighscoreEntry>& highscores) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    highscores.clear();
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        HighscoreEntry entry;
        std::getline(iss, entry.playerName, ',');   // Name extrahieren
        std::string scoreStr;
        std::getline(iss, scoreStr);                // Punktzahl extrahieren
        entry.score = std::stoi(scoreStr);
        highscores.push_back(entry);
    }
    return true;
}

// Highscores speichern
bool save_highscores(const std::string& filename, const std::vector<HighscoreEntry>& highscores) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    for (const auto& entry : highscores) {
        file << entry.playerName << "," << entry.score << "\n";
    }
    return true;
}

// Highscores sortieren (absteigend)
void sort_highscores(std::vector<HighscoreEntry>& highscores) {
    std::sort(highscores.begin(), highscores.end(), [](const auto& a, const auto& b) {
        return a.score > b.score;                   // Größere Punktzahl zuerst
        });
}

// Aktion ins Log schreiben
bool log_action(const std::string& filename, const std::string& action) {
    std::ofstream file(filename, std::ios::app);      // An Datei anhängen
    if (!file.is_open()) return false;
    file << action << "\n";                           // Neue Aktion schreiben
    return true;
}

// Liest alle Logeinträge in einen Vektor
bool load_log(const std::string& filename, std::vector<std::string>& logLines) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    logLines.clear();       // Vektor leeren
    std::string line;
    while (std::getline(file, line)) {
        logLines.push_back(line);       // Zeile hinzufügen
    }
    return true;
}

// Spielstand speichern in eine Datei
bool save_game(const std::string& filename, const GameState& state) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    
    // Allgemeine Spielinformationen schreiben
    file << "roundCount=" << state.roundCount << "\n";
    file << "currentPlayerIndex=" << state.currentPlayerIndex << "\n";
    file << "playerCount=" << state.playerCount << "\n";
    file << "cpuCount=" << state.cpuCount << "\n";

    // Reihenfolge der Würfelwürfe schreiben
    file << "diceOrder=";
    for (size_t i = 0; i < state.diceOrder.size(); ++i) {
        file << state.diceOrder[i];
        if (i < state.diceOrder.size() - 1) file << ",";
    }
    file << "\n";
    
    // Spielzustand jedes Spielers speichern
    for (const auto& player : state.players) {
        
        file << "Player=" << player.name << "," << player.budget << "," << player.position
            << "," << player.inJail << "," << player.isHuman << "," << player.hasFreeJailCard <<"\n";

        // Gekaufte Objekte speichern
        file << "Owned=";
        for (size_t i = 0; i < player.ownedObjects.size(); ++i) {
            file << player.ownedObjects[i];
            if (i < player.ownedObjects.size() - 1) file << ",";
        }
        file << "\n";

        // Gebaute Objekte speichern
        file << "Built=";
        for (size_t i = 0; i < 40; ++i) {
        // Wenn der Vektor kürzer ist, nehmen wir 0
        int value = (i < player.builtObjects.size()) ? player.builtObjects[i] : 0;
        file << value;
        if (i < 39) file << ",";
}
file << "\n";
    }

    return true;
}

// Spielstand laden aus Datei
bool load_game(const std::string& filename, GameState& state) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string line;
    state.players.clear();      // Spielerinformationen leeren

    // Lese Zeile für Zeile
    while (std::getline(file, line))
    {
        if (line.find("roundCount=") == 0)
        {
            state.roundCount = std::stoi(line.substr(11));
        }
        else if (line.find("currentPlayerIndex=") == 0)
        {
            state.currentPlayerIndex = std::stoi(line.substr(19));
        }
        else if (line.find("playerCount=") == 0)
        {
            state.playerCount = std::stoi(line.substr(12));
        }
        else if (line.find("cpuCount=") == 0)
        {
            state.cpuCount = std::stoi(line.substr(9));
        }
        else if (line.find("diceOrder=") == 0)
        {
            state.diceOrder.clear();
            std::istringstream iss(line.substr(10));
            std::string token;
            while (std::getline(iss, token, ','))
            {
                state.diceOrder.push_back(std::stoi(token));
            }
        }
        else if (line.find("Player=") == 0)
        {
            PlayerState player;
            std::istringstream iss(line.substr(7));
            std::string token;
            std::getline(iss, player.name, ',');
            std::getline(iss, token, ','); player.budget = std::stoi(token);
            std::getline(iss, token, ','); player.position = std::stoi(token);
            std::getline(iss, token, ','); player.inJail = std::stoi(token);
            std::getline(iss, token);     player.hasFreeJailCard = std::stoi(token);
            std::getline(iss, token);      player.isHuman = std::stoi(token);
            state.players.push_back(player);
        }
        else if (line.find("Owned=") == 0)
        {
            std::istringstream iss(line.substr(6));
            std::string token;
            auto& owned = state.players.back().ownedObjects;
            while (std::getline(iss, token, ','))
            {
                if (!token.empty()) owned.push_back(std::stoi(token));
            }
        }
            
        else if (line.find("Built=") == 0) {
            std::istringstream iss(line.substr(6));
            std::string token;
            auto& built = state.players.back().builtObjects;
            built.clear();
            while (std::getline(iss, token, ',')) {
                if (!token.empty()) built.push_back(std::stoi(token));
            }
            // Auffüllen auf 40 Einträge
            while (built.size() < 40) {
                built.push_back(0);
            }
        }
    }

    return true;
}
