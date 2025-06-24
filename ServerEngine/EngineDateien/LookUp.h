#pragma once
#include <string>
#include "SpaceConfig.h"
#include "MapReturnObj.h"


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

const string _fgcolortable[] = {"\033[91m", "\033[92m", "\033[93m", "\033[96m", "\033[97m"};
const string _bgcolortable[] = { "\033[41m", "\033[42m", "\033[43m", "\033[44m", "\033[45m", "\033[46m", "\033[104m", "\033[105m", "\033[40m", "\033[101m", "\033[102m", "\033[103m", "\033[106m"};

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
    SP,
    CR
};

const string _playerchars[] = { (string)(_fgcolortable[fgred] + 'A' + _fgcolortable[fgwhite]), (string)(_fgcolortable[fggreen] + 'B' + _fgcolortable[fgwhite]), (string)(_fgcolortable[fgyellow] + 'C' + _fgcolortable[fgwhite]), (string)(_fgcolortable[fgcyan] + 'D' + _fgcolortable[fgwhite]), " "};//♥♦♣♠ 3-6
const char _symbolchars[] = { (char)127, (char)174, (char)175, (char)184, (char)179, (char)196, (char)218, (char)191, (char)192, (char)217, (char)193, (char)194, (char)195, (char)180, (char)197, (char)1, (char)21, '=', ' '};//⌂(char)127 « » ©(char)184 │ ─ ┌ ┐└ ┘┬ ┴ ├ ┤ ┼ ☺(char)1 §(char)21 =

const char _symbolcharsControl[] = { (char)127,   // ⌂ 
                                (char)174, // « 1
                                (char)175, // » 2
                                (char)184, // © 3
                                (char)186, // │ 4
                                (char)205, // ─ 5
                                (char)201, // ┌ 6
                                (char)187, // ┐ 7

                                (char)200, // └ 8
                                (char)188, // ┘ 9
                                (char)202, // ┴ 10

                                (char)203, // ┬ 11

                                (char)204, // ├ 12

                                (char)185, // ┤ 13

                                (char)197, // ┼ 14
                                (char)1,   // ☺ 15
                                (char)21,  // § 16
                                '=',       // 17
                                ' ',       // 18
                                (char)111   //o 19
};
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

const SpaceConfig _boardarr[40] = {
    SpaceConfig("LOS", TypeGo, 200, bgblack),
    SpaceConfig("Oberreut|1", TypeStreet, 60, 50, new int[7] {2, 10, 30, 90, 160, 250}, bgmagenta),
    SpaceConfig("Gemeinschafts-|feld", TypeChest, bgblack),
    SpaceConfig("Gruenwinkel|3", TypeStreet, 80, 50, new int[7] {4, 20, 60, 180, 320, 450}, bgmagenta),
    SpaceConfig("Einkommensteuer", TypeTax, 200, bgblack),
    SpaceConfig("KIT Campus|-> Durlach BF", TypeStation, 50, bgblack),
    SpaceConfig("Neureut|6", TypeStreet, 100, 50, new int[7] {6, 30, 90, 270, 400, 550}, bgcyan),
    SpaceConfig("Ereignisfeld", TypeChance, bgblack),
    SpaceConfig("Waldstadt|8", TypeStreet, 100, 50, new int[7] {6, 30, 90, 270, 400, 550}, bgcyan),
    SpaceConfig("Hagsfeld|9", TypeStreet, 120, 50, new int[7] {8, 40, 100, 300, 450, 600}, bgcyan),
    SpaceConfig("Gefaengnis", TypePrison, bgblack),
    SpaceConfig("Palmbach|11", TypeStreet, 140, 100, new int[7] {10, 50, 150, 450, 625, 750}, bgbrightmagenta),
    SpaceConfig("Zuendhuetle|-> Entenfang", TypeStation, 50, bgblack),
    SpaceConfig("Stupferich|13", TypeStreet, 140, 100, new int[7] {10, 50, 150, 450, 625, 750}, bgbrightmagenta),
    SpaceConfig("Bergdoerfer|14", TypeStreet, 160, 100, new int[7] {12, 60, 180, 500, 700, 900}, bgbrightmagenta),
    SpaceConfig("Europaplatz|-> Hauptbahnhof", TypeStation, 80, bgblack),
    SpaceConfig("Rintheim|16", TypeStreet, 180, 100, new int[7] {14, 70, 200, 550, 750, 950}, bgblue),
    SpaceConfig("Gemeinschafts-|feld", TypeChest, bgblack),
    SpaceConfig("Rueppurr|18", TypeStreet, 180, 100, new int[7] {14, 70, 200, 550, 750, 950}, bgblue),
    SpaceConfig("Muehlburg|19", TypeStreet, 200, 100, new int[7] {16, 80, 220, 600, 800, 1000}, bgblue),
    SpaceConfig("Oststadtkreisel", TypePark, 0, bgblack),
    SpaceConfig("Nordstadt|21", TypeStreet, 220, 150, new int[7] {18, 90, 250, 700, 875, 1050}, bgred),
    SpaceConfig("Ereignisfeld", TypeChance, bgblack),
    SpaceConfig("Nordweststadt|23", TypeStreet, 220, 150, new int[7] {18, 90, 250, 700, 875, 1050}, bgred),
    SpaceConfig("Weststadt|24", TypeStreet, 240, 150, new int[7] {20, 100, 300, 750, 925, 1100}, bgred),
    SpaceConfig("Durlach BF|-> KIT Campus", TypeStation, 70, bgblack),
    SpaceConfig("Durlach|26", TypeStreet, 260, 150, new int[7] {22, 110, 330, 800, 975, 1150}, bgyellow),
    SpaceConfig("Suedstadt|27", TypeStreet, 260, 150, new int[7] {22, 110, 330, 800, 975, 1150}, bgyellow),
    SpaceConfig("Entenfang|-> Zuendhuetle", TypeStation, 70, bgblack),
    SpaceConfig("Oststadt|29", TypeStreet, 280, 150, new int[7] {24, 120, 360, 850, 1025, 1200}, bgyellow),
    SpaceConfig("Gehen Sie in|das Gefaengnis", TypeGTP, bgblack),
    SpaceConfig("Suedweststadt|31", TypeStreet, 300, 200, new int[7] {26, 130, 390, 900, 1100, 1275}, bggreen),
    SpaceConfig("Innenstadt Ost|32", TypeStreet, 300, 200, new int[7] {26, 130, 390, 900, 1100, 1275}, bggreen),
    SpaceConfig("Gemeinschafts-|feld", TypeChest, bgblack),
    SpaceConfig("Innenstadt West|34", TypeStreet, 320, 200, new int[7] {28, 150, 450, 1000, 1200, 1400}, bggreen),
    SpaceConfig("Hauptbahnhof|-> Europaplatz", TypeStation, 40, bgblack),
    SpaceConfig("Ereignisfeld", TypeChance, bgblack),
    SpaceConfig("Geigersberg|37", TypeStreet, 350, 200, new int[7] {35, 175, 500, 1100, 1300, 1500}, bgbrightblue),
    SpaceConfig("Zusatzsteuer", TypeTax, 100, bgblack),
    SpaceConfig("Schlossplatz|39", TypeStreet, 400, 200, new int[7] {50, 200, 600, 1400, 1700, 2000}, bgbrightblue)
};

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

const MapReturnObj _chestCards[] = {
    MapReturnObj(0, TypeGo, -1, 0, 0, "Ruecke vor bis auf Los (Ziehe 200" + string(1, _symbolchars[Coin]) + " ein)"),
    MapReturnObj(-1, TypeGo, -1, -200, 0, "Bankirrtum zu deinen Gunsten. Ziehe 200" + string(1, _symbolchars[Coin]) + " ein"),
    MapReturnObj(-1, TypeTax, -1, 50, 0, "Arztkosten. Zahle 50" + string(1, _symbolchars[Coin]) + ""),
    MapReturnObj(-1, TypeGo, -1, -50, 0, "Verkauf von Aktien bringt dir 50" + string(1, _symbolchars[Coin]) + ""),
    MapReturnObj(-1, TypeGo, -1, 0, 1, "Du erhaeltst eine Freiheitskarte"),
    MapReturnObj(10, TypeGo, -1, 0, -1, "Gehe ins Gefaengnis. Begib dich direkt dorthin. Gehe nicht ueber Los, ziehe nicht 200" + string(1, _symbolchars[Coin]) + " ein"),
    MapReturnObj(-1, TypeGo, -1, -100, 0, "Dein Urlaubsfonds wird faellig. Ziehe 100" + string(1, _symbolchars[Coin]) + " ein"),
    MapReturnObj(-1, TypeGo, -1, -20, 0, "Steuerrueckzahlung. Ziehe 20" + string(1, _symbolchars[Coin]) + " ein"),
    MapReturnObj(-1, TypeGo, -2, -10, 0, "Es ist dein Geburtstag. Ziehe 10" + string(1, _symbolchars[Coin]) + " von jedem Spieler ein"),
    MapReturnObj(-1, TypeGo, -1, -100, 0, "Deine Lebensversicherung wird faellig. Ziehe 100" + string(1, _symbolchars[Coin]) + " ein"),
    MapReturnObj(-1, TypeTax, -1, 100, 0, "Krankenhausgebuehren. Zahle 100" + string(1, _symbolchars[Coin]) + ""),
    MapReturnObj(-1, TypeTax, -1, 50, 0, "Schulgebuehren. Zahle 50" + string(1, _symbolchars[Coin]) + ""),
    MapReturnObj(-1, TypeGo, -1, -25, 0, "Beratungshonorar. Ziehe 25" + string(1, _symbolchars[Coin]) + " ein"),
    MapReturnObj(-1, TypeTax, -3, 40, 0, "Strassenreparaturkosten. Zahle 40" + string(1, _symbolchars[Coin]) + " pro Haus und 120" + string(1, _symbolchars[Coin]) + " pro Hotel"),
    MapReturnObj(-1, TypeGo, -1, -10, 0, "Du hast den zweiten Preis in einem Schoenheitswettbewerb gewonnen. Ziehe 10" + string(1, _symbolchars[Coin]) + " ein"),
    MapReturnObj(-1, TypeGo, -1, -100, 0, "Du hast geerbt. Ziehe 100" + string(1, _symbolchars[Coin]) + " ein"),
};

const MapReturnObj _chanceCards[] = {
    MapReturnObj(0, TypeGo, -1, 0, 0, "Ruecke vor bis auf Los (Ziehe 200" + string(1, _symbolchars[Coin]) + " ein)"),
    MapReturnObj(39, TypeGo, -1, 0, 0, "Ruecke vor bis zur Schlossallee. Falls du ueber Los kommst, ziehe 200" + string(1, _symbolchars[Coin]) + " ein"),
    MapReturnObj(11, TypeGo, -1, 0, 0, "Ruecke vor bis zur Seestrasse. Falls du ueber Los kommst, ziehe 200" + string(1, _symbolchars[Coin]) + " ein"),
    MapReturnObj(-1, TypeTax, -1, 50, 0, "Zahle 50" + string(1, _symbolchars[Coin]) + " Strafe"),
    MapReturnObj(-1, TypeGo, -1, 0, 1, "Du erhaeltst eine Freiheitskarte"),
    MapReturnObj(10, TypeGo, -1, 0, -1, "Gehe ins Gefaengnis. Begib dich direkt dorthin. Gehe nicht ueber Los, ziehe nicht 200" + string(1, _symbolchars[Coin]) + " ein"),
    MapReturnObj(-1, TypeTax, -1, 150, 0, "Zahle eine Gebuehr von 150" + string(1, _symbolchars[Coin])),
    MapReturnObj(-1, TypeTax, -1, 100, 0, "Zahle 100" + string(1, _symbolchars[Coin]) + " fuer Renovierungsarbeiten"),
    MapReturnObj(-1, TypeGo, -1, -20, 0, "Ziehe 20" + string(1, _symbolchars[Coin]) + " ein"),
    MapReturnObj(-1, TypeTax, -1, 50, 0, "Zahle 50" + string(1, _symbolchars[Coin]) + " fuer eine Feier"),
    MapReturnObj(-1, TypeGo, -1, -25, 0, "Ziehe 25" + string(1, _symbolchars[Coin]) + " ein"),
    MapReturnObj(-1, TypeTax, -3, 40, 0, "Strassenreparaturkosten. Zahle 40" + string(1, _symbolchars[Coin]) + " pro Haus und 120" + string(1, _symbolchars[Coin]) + " pro Hotel"),
    MapReturnObj(-1, TypeGo, -1, -10, 0, "Du hast den zweiten Preis in einem Schoenheitswettbewerb gewonnen. Ziehe 10" + string(1, _symbolchars[Coin]) + " ein"),
    MapReturnObj(-1, TypeGo, -1, -100, 0, "Du hast geerbt. Ziehe 100" + string(1, _symbolchars[Coin]) + " ein"),
};

const int _moveMatrix[40][40] = {
    {   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39 },
    {  39,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38 },
    {  38,  39,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37 },
    {  37,  38,  39,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36 },
    {  36,  37,  38,  39,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35 },
    {  15,  16,  17,  18,  19,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14 }, //Bahnhof
    {  34,  35,  36,  37,  38,  39,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33 },
    {  33,  34,  35,  36,  37,  38,  39,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32 },
    {  32,  33,  34,  35,  36,  37,  38,  39,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31 },
    {  31,  32,  33,  34,  35,  36,  37,  38,  39,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30 },
    {  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29 },
    {  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28 },
    {  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11 }, //Wasserwerk
    {  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26 },
    {  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25 },
    {   5,   6,   7,   8,   9,   0,  11,  12,  13,  14,  15,  16,  17,  18,  19,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,   0,   1,   2,   3,   4 }, //Bahnhof
    {  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23 },
    {  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22 },
    {  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21 },
    {  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20 },
    {  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19 },
    {  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18 },
    {  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17 },
    {  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16 },
    {  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15 },
    {  15,  16,  17,  18,  19,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14 }, //Bahnhof
    {  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13 },
    {  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12 },
    {  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,   15,  0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11 }, //E-Werk
    {  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10 },
    {  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9 },
    {   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,   0,   1,   2,   3,   4,   5,   6,   7,   8 },
    {   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,   0,   1,   2,   3,   4,   5,   6,   7 },
    {   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,   0,   1,   2,   3,   4,   5,   6 },
    {   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,   0,   1,   2,   3,   4,   5 },
    {   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,   0,   1,   2,   3,   4 }, //Bahnhof
    {   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,   0,   1,   2,   3 },
    {   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,   0,   1,   2 },
    {   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,   0,   1 },
    {   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,   0 }
};