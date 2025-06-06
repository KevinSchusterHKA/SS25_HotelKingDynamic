#pragma once
#include <string>


using namespace std;

const int _dimX = 20;
const int _dimY = 8;
const float _factor = 1.02;

enum _fgcolor {
    fgred,
    fggreen,
    fgyellow,
    fgcyan,
    fgwhite
};
enum _bgcolor {
    bgred,
    bggreen,
    bgyellow,
    bgblue,
    bgmagenta,
    bgcyan,
    bgbrightblue,
    bgbrightmagenta,
    bgblack,
    bgbrightred,
    bgbrightgreen,
    bgbrightyellow,
    bgbrightcyan
};

const string _fgcolortable[] = { "\033[91m", "\033[92m", "\033[93m", "\033[96m", "\033[97m" };
const string _bgcolortable[] = { "\033[41m", "\033[42m", "\033[43m", "\033[44m", "\033[45m", "\033[46m", "\033[104m", "\033[105m", "\033[40m", "\033[101m", "\033[102m", "\033[103m", "\033[106m" };

enum _char {
    House,
    DAL,
    DAR,
    Coin,
    VL,
    HL,
    ULC,
    URC,
    LLC,
    LRC,
    T,
    IT,
    LT,
    RT,
    X,
    HF,
    PG,
    EQ,
    SP
};

const string _playerchars[] = { (string)(_fgcolortable[fgred] + (char)3 + _fgcolortable[fgwhite]), (string)(_fgcolortable[fggreen] + (char)4 + _fgcolortable[fgwhite]), (string)(_fgcolortable[fgyellow] + (char)5 + _fgcolortable[fgwhite]), (string)(_fgcolortable[fgcyan] + (char)6 + _fgcolortable[fgwhite]), " "};//♥♦♣♠
const char _symbolchars[] = {   (char)127, // ⌂
                                (char)174, // «
                                (char)175, // »
                                (char)184, // ©
                                (char)179, // │
                                (char)196, // ─
                                (char)218, // ┌
                                (char)191, // ┐
                                (char)192, // └
                                (char)217, // ┘
                                (char)193, // ┬
                                (char)194, // ┴
                                (char)195, // ├
								(char)180, // ┤
								(char)197, // ┼
								(char)1,   // ☺
                                (char)21,  // §
                                '=', 
                                ' '};

enum _type {
    TypeStreet,
    TypeStation,
    TypeTax,
    TypeChance,
    TypeChest,
    TypeGo,
    TypePrison,
    TypePark,
    TypeGTP
};

const int _designStreet[_dimY][_dimX] = {
    { ULC, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, URC},
    {  VL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    {  LT, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL,  RT},
    {  VL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    {  LT, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL,  RT},
    {  VL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    {  VL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    { LLC, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, LRC}
};

const int _designStation[_dimY][_dimX] = {
    { ULC, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, URC},
    {  VL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    {  LT, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL,  RT},
    {  VL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    {  LT, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL,  RT},
    {  VL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    {  VL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    { LLC, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, LRC}
};

const int _designTax[_dimY][_dimX] = {
    { ULC, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, URC},
    {  VL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    {  LT, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL,  RT},
    {  VL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    {  LT, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL,  RT},
    {  VL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    {  VL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    { LLC, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, LRC}
};

const int _designChance[_dimY][_dimX] = {
    { ULC, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, URC},
    {  VL, SP, SP, SP, SP, PG, SP, SP, PG, SP, SP, PG, SP, SP, PG, SP, SP, SP, SP,  VL},
    {  LT, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL,  RT},
    {  VL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    {  LT, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL,  RT},
    {  VL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    {  VL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    { LLC, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, LRC}
};

const int _designChest[_dimY][_dimX] = {
    { ULC, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, URC},
    {  VL, SP, SP, SP, SP, HF, SP, SP, HF, SP, SP, HF, SP, SP, HF, SP, SP, SP, SP,  VL},
    {  LT, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL,  RT},
    {  VL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    {  LT, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL,  RT},
    {  VL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    {  VL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    { LLC, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, LRC}
};

const int _designGo[_dimY][_dimX] = {
    { ULC, HL, HL, HL, HL, HL, HL, HL,  HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, URC},
    {  VL, SP, SP, SP, SP, SP, SP, SP,  SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    {  VL, SP, SP, SP, SP, SP, SP, DAL, EQ, EQ, EQ, EQ, SP, SP, SP, SP, SP, SP, SP,  VL},
    {  VL, SP, SP, SP, SP, SP, SP, SP,  SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    {  VL, SP, SP, SP, SP, SP, SP, SP,  SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    {  VL, SP, SP, SP, SP, SP, SP, SP,  SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    {  VL, SP, SP, SP, SP, SP, SP, SP,  SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    { LLC, HL, HL, HL, HL, HL, HL, HL,  HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, LRC}
};

const int _designPrison[_dimY][_dimX] = {
    { ULC, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, URC},
    {  VL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    {  VL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    {  VL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    {  LT, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL,  RT},
    {  VL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    {  VL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    { LLC, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, LRC}
};

const int _designPark[_dimY][_dimX] = {
    { ULC, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, URC},
    {  VL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    {  LT, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL,  RT},
    {  VL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    {  LT, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL,  RT},
    {  VL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    {  VL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    { LLC, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, LRC}
};

const int _designGTP[_dimY][_dimX] = {
    { ULC, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, URC},
    {  VL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    {  VL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    {  VL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    {  VL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    {  VL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    {  VL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP,  VL},
    { LLC, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, HL, LRC}
};

//const SpaceConfig _boardarr[40] = {
//    SpaceConfig("LOS", TypeGo, 200, bgblack),
//    SpaceConfig("Badstrasse", TypeStreet, 60, 50, new int[7] {2, 10, 30, 90, 160, 250}, bgmagenta),
//    SpaceConfig("Gemeinschafts-|feld", TypeChest, bgblack),
//    SpaceConfig("Turmstrasse", TypeStreet, 60, 50, new int[7] {4, 20, 60, 180, 320, 450}, bgmagenta),
//    SpaceConfig("Einkommensteuer", TypeTax, 200, bgblack),
//    SpaceConfig("Suedbahnhof", TypeStation, 200, bgblack),
//    SpaceConfig("Chausseestrasse", TypeStreet, 100, 50, new int[7] {6, 30, 90, 270, 400, 550}, bgcyan),
//    SpaceConfig("Ereignisfeld", TypeChance, bgblack),
//    SpaceConfig("Elisenstrasse", TypeStreet, 100, 50, new int[7] {6, 30, 90, 270, 400, 550}, bgcyan),
//    SpaceConfig("Poststrasse", TypeStreet, 120, 50, new int[7] {8, 40, 100, 300, 450, 600}, bgcyan),
//    SpaceConfig("Gefaengnis", TypePrison, bgblack),
//    SpaceConfig("Seestrasse", TypeStreet, 140, 100, new int[7] {10, 50, 150, 450, 625, 750}, bgbrightmagenta),
//    SpaceConfig("Elektrizi-|taetswerk", TypeStation, 150, bgblack),
//    SpaceConfig("Hafenstrasse", TypeStreet, 140, 100, new int[7] {10, 50, 150, 450, 625, 750}, bgbrightmagenta),
//    SpaceConfig("Neue Strasse", TypeStreet, 160, 100, new int[7] {12, 60, 180, 500, 700, 900}, bgbrightmagenta),
//    SpaceConfig("Westbahnhof", TypeStation, 200, bgblack),
//    SpaceConfig("Muenchener|Strasse", TypeStreet, 180, 100, new int[7] {14, 70, 200, 550, 750, 950}, bgblue),
//    SpaceConfig("Gemeinschafts-|feld", TypeChest, bgblack),
//    SpaceConfig("Wiener Strasse", TypeStreet, 180, 100, new int[7] {14, 70, 200, 550, 750, 950}, bgblue),
//    SpaceConfig("Berliner|Strasse", TypeStreet, 200, 100, new int[7] {16, 80, 220, 600, 800, 1000}, bgblue),
//    SpaceConfig("Freies Parken", TypePark, 0, bgblack),
//    SpaceConfig("Theaterstrasse", TypeStreet, 220, 150, new int[7] {18, 90, 250, 700, 875, 1050}, bgred),
//    SpaceConfig("Ereignisfeld", TypeChance, bgblack),
//    SpaceConfig("Museumstrasse", TypeStreet, 220, 150, new int[7] {18, 90, 250, 700, 875, 1050}, bgred),
//    SpaceConfig("Opernplatz", TypeStreet, 240, 150, new int[7] {20, 100, 300, 750, 925, 1100}, bgred),
//    SpaceConfig("Nordbahnhof", TypeStation, 200, bgblack),
//    SpaceConfig("Lessingstrasse", TypeStreet, 260, 150, new int[7] {22, 110, 330, 800, 975, 1150}, bgyellow),
//    SpaceConfig("Schillerstrasse", TypeStreet, 260, 150, new int[7] {22, 110, 330, 800, 975, 1150}, bgyellow),
//    SpaceConfig("Wasserwerk", TypeStation, 150, bgblack),
//    SpaceConfig("Goethestrasse", TypeStreet, 280, 150, new int[7] {24, 120, 360, 850, 1025, 1200}, bgyellow),
//    SpaceConfig("Gehen Sie in|das Gefaengnis", TypeGTP, bgblack),
//    SpaceConfig("Rathausplatz", TypeStreet, 300, 200, new int[7] {26, 130, 390, 900, 1100, 1275}, bggreen),
//    SpaceConfig("Hauptstrasse", TypeStreet, 300, 200, new int[7] {26, 130, 390, 900, 1100, 1275}, bggreen),
//    SpaceConfig("Gemeinschafts-|feld", TypeChest, bgblack),
//    SpaceConfig("Bahnhofstrasse", TypeStreet, 320, 200, new int[7] {28, 150, 450, 1000, 1200, 1400}, bggreen),
//    SpaceConfig("Hauptbahnhof", TypeStation, 200, bgblack),
//    SpaceConfig("Ereignisfeld", TypeChance, bgblack),
//    SpaceConfig("Parkstrasse", TypeStreet, 350, 200, new int[7] {35, 175, 500, 1100, 1300, 1500}, bgbrightblue),
//    SpaceConfig("Zusatzsteuer", TypeTax, 100, bgblack),
//    SpaceConfig("Schlossallee", TypeStreet, 400, 200, new int[7] {50, 200, 600, 1400, 1700, 2000}, bgbrightblue)
//};

const int _streetarr[8][3] = {
    {1,3,-1},
    {6,8,9},
    {11,13,14},
    {16,18,19},
    {21,23,24},
    {26,27,29},
    {31,32,34},
    {37,39,-1}
};

//const MapReturnObj _chestCards[] = {
//    MapReturnObj(0, -1, 0, 0, "Ruecke vor bis auf Los (Ziehe 200" + string(1, _symbolchars[Coin]) + " ein)"),
//    MapReturnObj(-1, -1, -200, 0, "Bankirrtum zu deinen Gunsten. Ziehe 200" + string(1, _symbolchars[Coin]) + " ein"),
//    MapReturnObj(-1, -1, 50, 0, "Arztkosten. Zahle 50" + string(1, _symbolchars[Coin]) + ""),
//    MapReturnObj(-1, -1, -50, 0, "Verkauf von Aktien bringt dir 50" + string(1, _symbolchars[Coin]) + ""),
//    MapReturnObj(-1, -1, 0, -1, "Du erhaeltst eine Freiheitskarte"),
//    MapReturnObj(10, -1, 0, 1, "Gehe ins Gefaengnis. Begib dich direkt dorthin. Gehe nicht ueber Los, ziehe nicht 200" + string(1, _symbolchars[Coin]) + " ein"),
//    MapReturnObj(-1, -1, -100, 0, "Dein Urlaubsfonds wird faellig. Ziehe 100" + string(1, _symbolchars[Coin]) + " ein"),
//    MapReturnObj(-1, -1, -20, 0, "Steuerrueckzahlung. Ziehe 20" + string(1, _symbolchars[Coin]) + " ein"),
//    MapReturnObj(-1, -2, -10, 0, "Es ist dein Geburtstag. Ziehe 10" + string(1, _symbolchars[Coin]) + " von jedem Spieler ein"),
//    MapReturnObj(-1, -1, -100, 0, "Deine Lebensversicherung wird faellig. Ziehe 100" + string(1, _symbolchars[Coin]) + " ein"),
//    MapReturnObj(-1, -1, 100, 0, "Krankenhausgebuehren. Zahle 100" + string(1, _symbolchars[Coin]) + ""),
//    MapReturnObj(-1, -1, 50, 0, "Schulgebuehren. Zahle 50" + string(1, _symbolchars[Coin]) + ""),
//    MapReturnObj(-1, -1, -25, 0, "Beratungshonorar. Ziehe 25" + string(1, _symbolchars[Coin]) + " ein"),
//    MapReturnObj(-1, -3, 40, 0, "Straßenreparaturkosten. Zahle 40" + string(1, _symbolchars[Coin]) + " pro Haus und 120" + string(1, _symbolchars[Coin]) + " pro Hotel"),
//    MapReturnObj(-1, -1, -10, 0, "Du hast den zweiten Preis in einem Schoenheitswettbewerb gewonnen. Ziehe 10" + string(1, _symbolchars[Coin]) + " ein"),
//    MapReturnObj(-1, -1, -100, 0, "Du hast geerbt. Ziehe 100" + string(1, _symbolchars[Coin]) + " ein"),
//};
//
//const MapReturnObj _chanceCards[] = {
//    MapReturnObj(0, -1, 0, 0, "Ruecke vor bis auf Los (Ziehe 200" + string(1, _symbolchars[Coin]) + " ein)"),
//    MapReturnObj(39, -1, 0, 0, "Ruecke vor bis zur Schlossallee. Falls du ueber Los kommst, ziehe 200" + string(1, _symbolchars[Coin]) + " ein"),
//    MapReturnObj(11, -1, 0, 0, "Ruecke vor bis zur Seestrasse. Falls du ueber Los kommst, ziehe 200" + string(1, _symbolchars[Coin]) + " ein"),
//    MapReturnObj(-1, -1, -50, 0, "Zahle 50" + string(1, _symbolchars[Coin]) + " Strafe"),
//    MapReturnObj(-1, -1, 0, -1, "Du erhaeltst eine Freiheitskarte"),
//    MapReturnObj(10, -1, 0, 1, "Gehe ins Gefaengnis. Begib dich direkt dorthin. Gehe nicht ueber Los, ziehe nicht 200" + string(1, _symbolchars[Coin]) + " ein"),
//    MapReturnObj(-1, -1, -150, 0, "Zahle eine Gebuehr von 150" + string(1, _symbolchars[Coin])),
//    MapReturnObj(-1, -1, -100, 0, "Zahle 100" + string(1, _symbolchars[Coin]) + " für Renovierungsarbeiten"),
//    MapReturnObj(-1, -1, -20, 0, "Ziehe 20" + string(1, _symbolchars[Coin]) + " ein"),
//    MapReturnObj(-1, -1, -50, 0, "Zahle 50" + string(1, _symbolchars[Coin]) + " fuer eine Feier"),
//    MapReturnObj(-1, -1, -25, 0, "Ziehe 25" + string(1, _symbolchars[Coin]) + " ein"),
//    MapReturnObj(-1, -3, 40, 0, "Straßenreparaturkosten. Zahle 40" + string(1, _symbolchars[Coin]) + " pro Haus und 120" + string(1, _symbolchars[Coin]) + " pro Hotel"),
//    MapReturnObj(-1, -1, -10, 0, "Du hast den zweiten Preis in einem Schoenheitswettbewerb gewonnen. Ziehe 10" + string(1, _symbolchars[Coin]) + " ein"),
//    MapReturnObj(-1, -1, -100, 0, "Du hast geerbt. Ziehe 100" + string(1, _symbolchars[Coin]) + " ein"),
//
//};