#include <iostream>
#include <cstdlib>
#include <vector>
#include <deque>
#include <set>
#include <list>
#include <map>
#include <string>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <bitset>
#include <iomanip>
#include <fstream>

#include <gtkmm.h>
#include <gtkmm\buttonbox.h>
#include <gtkmm-2.4\gtkmm\buttonbox.h>
#include <gtkmm-2.4\gtkmm\texttag.h>
#include <gtkmm-2.4\gtkmm\label.h>
#include <gtkmm\image.h>
#include <gtkmm\textbuffer.h>
#include <gtkmm\textview.h>
#include <gtkmm\main.h>
#include <pangomm-1.4\pangomm.h>
#include <pangomm.h>

#include <gtkmm-2.4\gtkmm\box.h>
#include <gtkmm\label.h>
#include <gtkmm\window.h>
#include <gtkmm\button.h>

#include <gdk/gdkkeysyms.h>

using namespace std;

const string RootDirectory = "C:/Users/Ian Hemenway SSD/Desktop/Trajan images/";
const string defaultFont = "Verdana";

typedef pair<int, int> Coordinate;

const double SCALE = 1.0;
const double SHEET_SCALE = 1.0;

const size_t BOARD_WIDTH  = 720 * SCALE;
const size_t BOARD_HEIGHT = 929 * SCALE;

const Coordinate   I_CENTER = make_pair(325 * SHEET_SCALE, 100 * SHEET_SCALE);	
const Coordinate  II_CENTER = make_pair(413 * SHEET_SCALE, 100 * SHEET_SCALE);	
const Coordinate III_CENTER = make_pair(457 * SHEET_SCALE, 176 * SHEET_SCALE);	
const Coordinate  IV_CENTER = make_pair(413 * SHEET_SCALE, 251 * SHEET_SCALE);	
const Coordinate   V_CENTER = make_pair(325 * SHEET_SCALE, 251 * SHEET_SCALE);	
const Coordinate  VI_CENTER = make_pair(282 * SHEET_SCALE, 176 * SHEET_SCALE);	

const double TRAY_RADIUS = 40.0 * SHEET_SCALE;

const size_t TRAJAN_TILE_WIDTH  = 63 * SCALE;
const size_t TRAJAN_TILE_HEIGHT = TRAJAN_TILE_WIDTH; //square
const double TRAJAN_ROTATED_TILE_WIDTH  = 86.06 * SCALE;
const double TRAJAN_ROTATED_TILE_HEIGHT = TRAJAN_ROTATED_TILE_WIDTH;

const Coordinate TRAJAN_ANCHOR_1 = make_pair<int, int>( 76 * SCALE, 564 * SCALE); //1  4
const Coordinate TRAJAN_ANCHOR_2 = make_pair<int, int>( 76 * SCALE, 631 * SCALE); //2  5
const Coordinate TRAJAN_ANCHOR_3 = make_pair<int, int>( 76 * SCALE, 698 * SCALE); //3  6
const Coordinate TRAJAN_ANCHOR_4 = make_pair<int, int>(204 * SCALE, 564 * SCALE);
const Coordinate TRAJAN_ANCHOR_5 = make_pair<int, int>(204 * SCALE, 631 * SCALE);
const Coordinate TRAJAN_ANCHOR_6 = make_pair<int, int>(204 * SCALE, 698 * SCALE);

const size_t BOAT_WIDTH  = 115 * SCALE;
const size_t BOAT_HEIGHT =  85 * SCALE; 

const Coordinate    TOP_BOAT_ANCHOR = make_pair<int, int>(225 * SCALE, 310 * SCALE);
const Coordinate MIDDLE_BOAT_ANCHOR = make_pair<int, int>(118 * SCALE, 375 * SCALE);
const Coordinate BOTTOM_BOAT_ANCHOR = make_pair<int, int>( 10 * SCALE, 439 * SCALE);

const Coordinate  LEFT_SENATE_CARD_ANCHOR = make_pair<int, int>(545 * SCALE, 809 * SCALE);
const Coordinate RIGHT_SENATE_CARD_ANCHOR = make_pair<int, int>(627 * SCALE, 809 * SCALE);
const size_t SENATE_CARD_WIDTH  =  61 * SCALE;
const size_t SENATE_CARD_HEIGHT = 107 * SCALE;

const size_t FORUM_TILE_WIDTH  = 42 * SCALE;
const size_t FORUM_TILE_HEIGHT = FORUM_TILE_WIDTH;
const Coordinate TOP_LEFT_FORUM_ANCHOR = make_pair<int, int>(428 * SCALE, 586 * SCALE);
const size_t FORUM_STEP_RIGHT  = 52 * SCALE;
const size_t FORUM_STEP_DOWN   = 49 * SCALE;

const size_t CONSTRUCTION_TILE_WIDTH  = 38 * SCALE;
const size_t CONSTRUCTION_TILE_HEIGHT = 39 * SCALE;
const Coordinate TOP_LEFT_CONSTRUCTION_ANCHOR = make_pair<int, int>(431 * SCALE, 311 * SCALE);
const size_t CONSTRUCTION_TILE_STEP_RIGHT = 59 * SCALE;
const size_t CONSTRUCTION_TILE_STEP_DOWN  = 58 * SCALE; 

const size_t CARD_WIDTH  =  80;
const size_t CARD_HEIGHT = 125;

const size_t SHEET_WIDTH  = 571;
const size_t SHEET_HEIGHT = 362;

struct Hotzone
{
	Coordinate anchor;
	size_t width;
	size_t height;

	Hotzone()
		:anchor(Coordinate(0, 0)), width(0), height(0) {}
	Hotzone(Coordinate topLeft, size_t _width, size_t _height)
		:anchor(topLeft), width(_width), height(_height) {}

	bool contains(int x, int y) const {
		return anchor.first <= x && x <= anchor.first + width && anchor.second <= y && y <= anchor.second + height;
	}
	bool contains(Coordinate c) const {
		return anchor.first <= c.first && c.first  <= anchor.first + width && anchor.second <= c.second && c.second <= anchor.second + height;
	}
};

/*
struct Color{
	enum pegColor {
		_blue,
		_yellow,
		_light_green,
		_orange,
		_pink,
		_white
	};
private:
	int _id;
public:
	Color(pegColor c)
	{
		switch (c) {
		case _blue:
			_id = 0;
			break;
		case _yellow:
			_id = 1;
			break;
		case _light_green:
			_id = 2;
			break;
		case _orange:
			_id = 3;
			break;
		case _pink:
			_id = 4;
			break;
		case _white:
			_id = 5;
			break;
		}
	}
	bool operator==(const Color& rhs) {
		return _id == rhs._id;
	}
	bool is(const Color& rhs) {
		return _id == rhs._id;
	}
};

const Color BLUE        (Color::_blue);
const Color YELLOW      (Color::_yellow);
const Color LIGHT_GREEN (Color::_light_green);
const Color ORANGE      (Color::_orange);
const Color PINK        (Color::_pink);
const Color WHITE       (Color::_white);
*/
enum Color {
	 BLUE,
	 YELLOW,
	 LIGHT_GREEN,
	 ORANGE,
	 PINK,
	 WHITE       
};
struct Peg
	:public Glib::RefPtr<Gdk::Pixbuf>
{
	Color color;
	Peg(Color c)
		:color (c)
	{
		if      (c == BLUE       ) Glib::RefPtr<Gdk::Pixbuf>::operator=(Gdk::Pixbuf::create_from_file(RootDirectory + "p5.png"));
		else if (c == YELLOW     ) Glib::RefPtr<Gdk::Pixbuf>::operator=(Gdk::Pixbuf::create_from_file(RootDirectory + "p2.png"));
		else if (c == LIGHT_GREEN) Glib::RefPtr<Gdk::Pixbuf>::operator=(Gdk::Pixbuf::create_from_file(RootDirectory + "p4.png"));
		else if (c == ORANGE     ) Glib::RefPtr<Gdk::Pixbuf>::operator=(Gdk::Pixbuf::create_from_file(RootDirectory + "p1.png"));
		else if (c == PINK       ) Glib::RefPtr<Gdk::Pixbuf>::operator=(Gdk::Pixbuf::create_from_file(RootDirectory + "p0.png"));
		else if (c == WHITE      ) Glib::RefPtr<Gdk::Pixbuf>::operator=(Gdk::Pixbuf::create_from_file(RootDirectory + "p3.png"));
		else {
			cout << "Invalid peg color.\n";
			exit(EXIT_FAILURE);
		}
	}
	bool operator==(const Peg& rhs) {
		return color == rhs.color;
	}

	bool operator==(Color c) {
		return color == c;
	}

	bool is(Color c) {
		return color == c;
	}
};

typedef vector<Coordinate> CoordinateList;

class Tray
	:public vector<Peg>
{
public:
	
	Tray()
	{ }

	sigc::signal<void> changedSignal;

	void push_back(const Peg& p) {
		vector<Peg>::push_back(p);
		changedSignal.emit();
	}

	void pop_back() {
		remove(back());
		changedSignal.emit();
	}

	void add(const Peg& p) {
		vector<Peg>::push_back(p);
		changedSignal.emit();
	}
	void add(Color c) {
		vector<Peg>::push_back(Peg(c));
		changedSignal.emit();
	}
	void remove(const Peg& p) {
		if (find(begin(), end(), p) != end()) {
			erase(find(begin(), end(), p));
			changedSignal.emit();
		}
	}
	void remove(Color c) {
		if (find(begin(), end(), Peg(c)) != end()) {
			erase(find(begin(), end(), Peg(c)));
			changedSignal.emit();
		}
	}

	void removeAll() {
		clear();
		changedSignal.emit();
	}
	
};

class Wheel
	:public vector<Tray>
{
public:
	enum RomanNumeral {
		I,
		II,
		III,
		IV,
		V,
		VI
	};

	Wheel()	{
		resize(6);
		
		vector<Peg> shuffler;
		for (auto i = 0; i < 2; ++i) {
			shuffler.push_back(Peg(BLUE));
			shuffler.push_back(Peg(YELLOW));
			shuffler.push_back(Peg(LIGHT_GREEN));
			shuffler.push_back(Peg(ORANGE));
			shuffler.push_back(Peg(PINK));
			shuffler.push_back(Peg(WHITE));
		}
		random_shuffle(shuffler.begin(), shuffler.end());
		for (auto i = begin(); !shuffler.empty(); ) {
			i->add(shuffler.back());
			shuffler.pop_back();
			++i;
			if (i == end())
				i = begin();
		}
	}
	Wheel& operator=(const Wheel& rhs) {
		this->vector<Tray>::operator=(rhs);
		return *this;
	}
};

class Player;

struct Tile
	:public Glib::RefPtr<Gdk::Pixbuf> 
{
	Tile(const string& filename)
		: Glib::RefPtr<Gdk::Pixbuf>(Gdk::Pixbuf::create_from_file(filename)){ }
	virtual ~Tile() {}
	virtual void awardTo(Player& player) const = 0;
};

enum PlayerColor
{
	DARK_BLUE,
	RED,
	GREEN,
	BROWN
};

enum DemandType {
	BREAD,
	FIRE,
	HELMET
};

enum MainActionType {
	MAIN_SEAPORT,
	MAIN_FORUM,
	MAIN_MILITARY,
	MAIN_SENATE,
	MAIN_TRAJAN,
	MAIN_CONSTRUCTION,
};

enum ConstructionType {
	STEPS,
	DOOR,
	FOUNTAIN,
	ROOF,
	WINDOW
};

struct ConstructionTile
	:public Tile 
{
	sigc::signal<void, MainActionType> firstConstructionSignal;
	size_t VP;
	ConstructionTile(size_t _VP, const string& filename = RootDirectory + "p1.png")
		: VP(_VP), Tile(filename)	{ }
	
	virtual ConstructionType getType() const = 0;
	size_t getVP() const {return VP;}
	
};

enum TrajanTileType
{
	TRAJAN_BREAD,
	TRAJAN_FIRE,
	TRAJAN_HELMET,
	TRAJAN_CONSTRUCTION_ONE,
	TRAJAN_CONSTRUCTION_TWO,
	TRAJAN_MILITARY_ONE,
	TRAJAN_MILITARY_TWO,
	TRAJAN_NINE_VP,
	TRAJAN_PLUS_TWO,
	TRAJAN_TWO_CARDS
};

class Player;

struct TrajanTile 
	:public Tile
{
	size_t VP;
	Color colorOne;
	Color colorTwo;
	Glib::RefPtr<Gdk::Pixbuf> rotatedLeftPixbuf;
	Glib::RefPtr<Gdk::Pixbuf> rotatedRightPixbuf;
	sigc::signal<void, Player&> awardedSignal;
	sigc::signal<void> hideSignal;
	sigc::signal<void, const Player&, Glib::RefPtr<Gdk::Pixbuf>, const string&> historySignal;
	bool hidden;

	TrajanTile(size_t _VP, Color one, Color two, const string& filename, const string& rotatedFilename)
		: VP(_VP), colorOne(one), colorTwo(two), Tile(RootDirectory + "trajanTilesPlain/" + filename), hidden(false)	{
			Glib::RefPtr<Gdk::Pixbuf>::operator=((*this)->scale_simple(TRAJAN_TILE_WIDTH, TRAJAN_TILE_HEIGHT, Gdk::INTERP_HYPER));
			rotatedLeftPixbuf  = Gdk::Pixbuf::create_from_file(RootDirectory + "trajanTilesRotateA/" + rotatedFilename, TRAJAN_ROTATED_TILE_WIDTH, TRAJAN_ROTATED_TILE_HEIGHT, true);
			rotatedRightPixbuf = Gdk::Pixbuf::create_from_file(RootDirectory + "trajanTilesRotateB/" + rotatedFilename, TRAJAN_ROTATED_TILE_WIDTH, TRAJAN_ROTATED_TILE_HEIGHT, true);
			hideSignal.connect(sigc::bind(sigc::mem_fun(*this, &TrajanTile::setAsHidden), true));
	}
	virtual ~TrajanTile() {}
	bool hasColor(Color c) const { return colorOne == c || colorTwo == c;}
	bool hasBothColors(Color first, Color second) const {
		return (first == colorOne && second == colorTwo) || (first == colorTwo && second == colorOne);
	}
	bool trayHasMatch(const Tray& tray) const {
		if (tray.size() < 2)
			return false;
		for (auto i = 0; i < tray.size() - 1; ++i) {
			for (auto j = i + 1; j < tray.size(); ++j) {
				if (hasBothColors(tray[i].color, tray[j].color))
					return true;
			}
		}
		return false;
	}

	void awardTo(Player& player) const;

	void setAsHidden(bool shouldHide = true) {
		hidden = shouldHide;
	}
	void sendHistoryMessage(const Player& player, const string& s) const {
		historySignal.emit(player, *this, "TRAJAN TILE: " + s + " (" + to_string(long long (VP)) + " VP)");
	}

	virtual TrajanTileType getType() const = 0;
	

};

enum Commodity {
	COLUMNS,
	FURS,
	SCROLLS,
	OILS,
	FRUIT,
	CERAMICS,
	WINE,
	FISH,
	JEWELRY,
	GEMS,
	CATTLE,
	WHEAT,
	WILD
};

struct CommodityCard
	:public Tile
{
	Commodity commodity;
	CommodityCard(Commodity c, const string& filename)
		:Tile(filename), commodity(c) {
			//Glib::RefPtr<Gdk::Pixbuf>::operator=((*this)->scale_simple((*this)->get_width() * .8, (*this)->get_height() * .8, Gdk::INTERP_HYPER));
	}
	
	bool operator==(const CommodityCard& rhs) const {
		return commodity == rhs.commodity;
	}

	string asString() const {
		switch (commodity) {
		case COLUMNS:  return "COLUMNS";
		case FURS:     return "FURS";
		case SCROLLS:  return "SCROLLS";
		case OILS:     return "OILS";
		case FRUIT:    return "FRUIT";
		case CERAMICS: return "CERAMICS";
		case WINE:     return "WINE";
		case FISH:     return "FISH";
		case JEWELRY:  return "JEWELRY";
		case GEMS:     return "GEMS";
		case CATTLE:   return "CATTLE";
		case WHEAT:    return "WHEAT";
		case WILD:     return "WILD";
		}
	}

	void awardTo(Player& player) const { 
		;
	}

	bool isWild() const {
		return commodity == WILD;
	}


	
};

bool lessThan(const CommodityCard& lhs, const CommodityCard& rhs) {
	return lhs.commodity < rhs.commodity;
}


class Game;
class SenateCard
{
	Glib::RefPtr<Gdk::Pixbuf> _goldSidePixbuf;
	Glib::RefPtr<Gdk::Pixbuf> _silverSidePixbuf;
	bool _goldSideUp;
	size_t _ID;
	size_t (SenateCard::*scoreFunctionPtr)(const Game&, const Player&) const;
public:
	
	SenateCard(size_t ID, const string& filenameGold, const string& filenameSilver)
		: _ID(ID),
	     _goldSidePixbuf  (Gdk::Pixbuf::create_from_file(filenameGold)),
		 _silverSidePixbuf(Gdk::Pixbuf::create_from_file(filenameSilver)),
		 _goldSideUp(true)
	{
		switch(_ID) {
		case  0: scoreFunctionPtr = &SenateCard::getSenateCardScore00; break;
		case  1: scoreFunctionPtr = &SenateCard::getSenateCardScore01; break;
		case  2: scoreFunctionPtr = &SenateCard::getSenateCardScore02; break;
		case  3: scoreFunctionPtr = &SenateCard::getSenateCardScore03; break;
		case  4: 
		case  5: 
		case  6: 
		case  7: 
		case  8: 
		case  9: scoreFunctionPtr = &SenateCard::getSenateCardScoreCommodity; break;
		case 10: scoreFunctionPtr = &SenateCard::getSenateCardScore10; break;
		case 11: scoreFunctionPtr = &SenateCard::getSenateCardScore11; break;
		default:
			cout << "Invalid ID for senate card:\n" << ID << endl;
			exit(EXIT_FAILURE);
		}
		
	}
		
	Glib::RefPtr<Gdk::Pixbuf> getPixbuf() const {
		if (_goldSideUp)
			return _goldSidePixbuf;
		else
			return _silverSidePixbuf;
	}

	bool isGoldSideUp() const {return _goldSideUp;}
	void flipDown() {_goldSideUp = false;}

	bool hasDemandBonus() const       { return _ID <=  2; }
	bool hasConstructionBonus() const { return _ID ==  3; }
	bool hasCommodityBonus() const    { return 4 <= _ID && _ID <= 9; }
	bool hasMilitaryBonus() const     { return _ID == 10; }
	bool hasSenateCardBonus() const   { return _ID == 11; }

	pair<int, int> getCommodityBonuses() const {
		if (!hasCommodityBonus())
			return make_pair(-1, -1);
		else
			switch(_ID) {
			case 4: return make_pair(COLUMNS, FURS);
			case 5: return make_pair(SCROLLS, OILS);
			case 6: return make_pair(FRUIT, CERAMICS);
			case 7: return make_pair(WINE, FISH);
			case 8: return make_pair(JEWELRY, GEMS);
			case 9: return make_pair(CATTLE, WHEAT);
			default: return make_pair(-1, -1);
		}
	}
	int getDemandBonus() const {
		switch(_ID) {
		case 0:
			return BREAD;
		case 1:
			return HELMET;
		case 2:
			return FIRE;
		default:
			return -1;
		}
	}

	size_t getSenateCardScore00(const Game& game, const Player& player) const;
	size_t getSenateCardScore01(const Game& game, const Player& player) const;
	size_t getSenateCardScore02(const Game& game, const Player& player) const;
	size_t getSenateCardScore03(const Game& game, const Player& player) const;
	size_t getSenateCardScoreCommodity(const Game& game, const Player& player) const;
	size_t getSenateCardScore10(const Game& game, const Player& player) const;
	size_t getSenateCardScore11(const Game& game, const Player& player) const;

	size_t getScore(const Game& game, const Player& player) const;
	
};

class SenateCardDeck
	:public vector<const SenateCard*>
{
	SenateCard senateCard00;
	SenateCard senateCard01;
	SenateCard senateCard02;
	SenateCard senateCard03;
	SenateCard senateCard04;
	SenateCard senateCard05;
	SenateCard senateCard06;
	SenateCard senateCard07;
	SenateCard senateCard08;
	SenateCard senateCard09;
	SenateCard senateCard10;
	SenateCard senateCard11;
public:
	SenateCardDeck() :
		senateCard00( 0, RootDirectory +  "ts0a.png", RootDirectory +  "ts0b.png"),
		senateCard01( 1, RootDirectory +  "ts1a.png", RootDirectory +  "ts1b.png"),
		senateCard02( 2, RootDirectory +  "ts2a.png", RootDirectory +  "ts2b.png"),
		senateCard03( 3, RootDirectory +  "ts3a.png", RootDirectory +  "ts3b.png"),
		senateCard04( 4, RootDirectory +  "ts4a.png", RootDirectory +  "ts4b.png"),
		senateCard05( 5, RootDirectory +  "ts5a.png", RootDirectory +  "ts5b.png"),
		senateCard06( 6, RootDirectory +  "ts6a.png", RootDirectory +  "ts6b.png"),
		senateCard07( 7, RootDirectory +  "ts7a.png", RootDirectory +  "ts7b.png"),
		senateCard08( 8, RootDirectory +  "ts8a.png", RootDirectory +  "ts8b.png"),
		senateCard09( 9, RootDirectory +  "ts9a.png", RootDirectory +  "ts9b.png"),
		senateCard10(10, RootDirectory + "ts10a.png", RootDirectory + "ts10b.png"),
		senateCard11(11, RootDirectory + "ts11a.png", RootDirectory + "ts11b.png")
	{
		push_back(&senateCard00);
		push_back(&senateCard01);
		push_back(&senateCard02);
		push_back(&senateCard03);
		push_back(&senateCard04);
		push_back(&senateCard05);
		push_back(&senateCard06);
		push_back(&senateCard07);
		push_back(&senateCard08);
		push_back(&senateCard09);
		push_back(&senateCard10);
		push_back(&senateCard11);
		random_shuffle(begin(), end());
	}
};

enum ProvinceName {
	MILITARY_CAMP,
	ALPES,
	RAETIA,
	NORICUM,
	NARBONENSIS,
	LUGUDUNENSIS,
	BELGICA,
	GERMANIA_SUPERIOR,
	AQUITANIA,
	BRITANNIA,
	GERMANIA_INFERIOR
};

struct Province
{
private:
	size_t VP;
public:
	ProvinceName name;
	const Tile* tilePtr;
	Coordinate tileAnchor;
	
	vector<PlayerColor> generals;
	vector<PlayerColor> legionnaires;
	vector<size_t> campAmounts;
	vector<Coordinate> generalAnchors;
	vector<Coordinate> legionnaireAnchors;
	Hotzone generalHotzone;
	Hotzone legionnaireHotzone;
	vector<Province*> adjacents;

	static vector< Glib::RefPtr<Gdk::Pixbuf> > generalPixbufs;
	static vector< Glib::RefPtr<Gdk::Pixbuf> > legionnairePixbufs;
	
	Province(ProvinceName _name)
		:name(_name), tilePtr(NULL)
	{
		size_t side = 40;
		switch(name) {
		case MILITARY_CAMP:
			VP = 0;
			legionnaireHotzone = Hotzone(Coordinate(439, 261), side, side);
			generalAnchors.push_back(Coordinate(503, 220));
			legionnaireAnchors.push_back(Coordinate(450, 250));
			campAmounts.resize(4, 0);
			break;
		case ALPES:
			VP = 3;
			legionnaireHotzone = Hotzone(Coordinate(302, 212), side, side);
			tileAnchor = (Coordinate(261, 187));
			generalAnchors.push_back(Coordinate(240, 227));
			legionnaireAnchors.push_back(Coordinate(310, 211));
			break;
		case RAETIA:
			VP = 3;
			legionnaireHotzone = Hotzone(Coordinate(525, 167), side, side);
			tileAnchor = (Coordinate(486, 141));
			generalAnchors.push_back(Coordinate(450, 142));
			legionnaireAnchors.push_back(Coordinate(536, 167));
			break;
		case NORICUM:
			VP = 5;
			legionnaireHotzone = Hotzone(Coordinate(661, 185), side, side);
			tileAnchor = (Coordinate(622, 157));
			generalAnchors.push_back(Coordinate(584, 159));
			legionnaireAnchors.push_back(Coordinate(671, 185));
			break;
		case NARBONENSIS:
			VP = 6;
			legionnaireHotzone = Hotzone(Coordinate(142, 267), side, side);
			tileAnchor = (Coordinate(102, 240));
			generalAnchors.push_back(Coordinate( 57, 244));
			legionnaireAnchors.push_back(Coordinate(153, 264));
			break;
		case LUGUDUNENSIS:
			VP = 6;
			legionnaireHotzone = Hotzone(Coordinate(222, 140), side, side);
			tileAnchor = (Coordinate(181, 116));
			generalAnchors.push_back(Coordinate(143, 101));
			legionnaireAnchors.push_back(Coordinate(233, 141));
			break;
		case BELGICA:
			VP = 6;
			legionnaireHotzone = Hotzone(Coordinate(354, 120), side, side);
			tileAnchor = (Coordinate(312,  94));
			generalAnchors.push_back(Coordinate(286,  65));
			legionnaireAnchors.push_back(Coordinate(364, 122));
			break;
		case GERMANIA_SUPERIOR:
			VP = 6;
			legionnaireHotzone = Hotzone(Coordinate(622,  99), side, side);
			tileAnchor = (Coordinate(581,  78));
			generalAnchors.push_back(Coordinate(550,  82));
			legionnaireAnchors.push_back(Coordinate(631, 101));
			break;
		case AQUITANIA:
			VP = 10;
			legionnaireHotzone = Hotzone(Coordinate( 95, 182), side, side);
			tileAnchor = (Coordinate( 55, 153));
			generalAnchors.push_back(Coordinate( 24, 155));
			legionnaireAnchors.push_back(Coordinate(106, 179));
			break;
		case BRITANNIA:
			VP = 10;
			legionnaireHotzone = Hotzone(Coordinate(219,  41), side, side);
			tileAnchor = (Coordinate(180,  14));
			generalAnchors.push_back(Coordinate(144,  18));
			legionnaireAnchors.push_back(Coordinate(229, 39));
			break;
		case GERMANIA_INFERIOR:
			VP = 10;
			legionnaireHotzone = Hotzone(Coordinate(480,  72), side, side);
			tileAnchor = (Coordinate(440,  50));
			generalAnchors.push_back(Coordinate(412,  25));
			legionnaireAnchors.push_back(Coordinate(491,  70));
			break;
		default:
			cout << "Province name not found\n";
			exit(EXIT_FAILURE);
		}

		generalHotzone = legionnaireHotzone;
		generalHotzone.anchor.first -= 50;
		
		for (auto i = 1; i < 4; ++i) {
			generalAnchors.push_back(generalAnchors.back());
			generalAnchors.back().first += 20;
		}

		legionnaireAnchors.resize(4, legionnaireAnchors.front());
		legionnaireAnchors[1].first  += 24;
		legionnaireAnchors[2].second -= 32;
		legionnaireAnchors[3].first  += 24;
		legionnaireAnchors[3].second -= 32;
	}

	size_t getVP() const {
		if (legionnaires.size() * 3 >= VP)
			return 0;
		else
			return VP - (legionnaires.size() * 3);
	}

	bool operator==(const Province& rhs) const {
		return name == rhs.name;
	}

	bool isAdjacentTo(const Province& rhs) const {
		for (auto i = 0; i < adjacents.size(); ++i) {
			if (*adjacents[i] == rhs)
				return true;
		}
		return false;
	}

	string getString() const {
		switch (name) {
		case MILITARY_CAMP:     return "Military camp";
		case ALPES:             return "Alpes";
		case RAETIA:            return "Raetia";
		case NORICUM:           return "Noricum";
		case NARBONENSIS:       return "Narbonensis";
		case LUGUDUNENSIS:      return "Lugudunensis";
		case BELGICA:           return "Belgica";
		case GERMANIA_SUPERIOR: return "Germania Superior";
		case AQUITANIA:         return "Aquitania";
		case BRITANNIA:         return "Britannia";
		case GERMANIA_INFERIOR: return "Germania Inferior";
		}
	}

	bool needsTile() const {
		return name != MILITARY_CAMP && tilePtr == NULL && generals.empty() && legionnaires.empty();
	}

	bool hasTile() const {
		return tilePtr;
	}

	bool hasGeneralOfColor(PlayerColor color) const {
		return (find(generals.begin(), generals.end(), color) != generals.end());
	}

	void addGeneral(PlayerColor color) {
		if (find(generals.begin(), generals.end(), color) == generals.end()) {
			generals.push_back(color);
		}
		else {
			cout << "Province::addGeneral(): duplicate found\n";
			exit(EXIT_FAILURE);
		}
	}

	void removeGeneral(PlayerColor color) {
		if (find(generals.begin(), generals.end(), color) != generals.end()) {
			generals.erase(find(generals.begin(), generals.end(), color));
		} 
		else {
			cout << "Province::removeGeneral(): color not found\n";
			exit(EXIT_FAILURE);
		}
	}

	bool hasLegionnaireOfColor(PlayerColor color) const {
		return (find(legionnaires.begin(), legionnaires.end(), color) != legionnaires.end());
	}

	void addLegionnaire(PlayerColor color) {
		if (name == MILITARY_CAMP) {
			//legionnaires.push_back(color);
			++campAmounts[color];
			return;
		}
		if (find(legionnaires.begin(), legionnaires.end(), color) == legionnaires.end()) {
			legionnaires.push_back(color);
		}
		else {
			cout << "Province::addLegionnaire(): duplicate found\n";
			exit(EXIT_FAILURE);
		}
	}

	void removeLegionnaire(PlayerColor color) {
		if (name != MILITARY_CAMP) { 
			cout << "Cannot remove legionnaire from non-camp province\n";
			exit(EXIT_FAILURE);
		}
		if (campAmounts[color] == 0) {
			cout << "Camp has no legionnaires of color " << int(color) << endl;
			exit(EXIT_FAILURE);
		}
		--campAmounts[color];
		//if (campAmounts[color] == 0) {
		//	legionnaires.erase(find(legionnaires.begin(), legionnaires.end(), color));
		//}
	}

	
};

class Continent
	:public vector<Province>
{
public:
	Continent() {
		push_back(Province(MILITARY_CAMP));
		push_back(Province(ALPES));
		push_back(Province(RAETIA));
		push_back(Province(NORICUM));
		push_back(Province(NARBONENSIS));
		push_back(Province(LUGUDUNENSIS));
		push_back(Province(BELGICA));
		push_back(Province(GERMANIA_SUPERIOR));
		push_back(Province(AQUITANIA));
		push_back(Province(BRITANNIA));
		push_back(Province(GERMANIA_INFERIOR));

		at(MILITARY_CAMP).adjacents.push_back(&at(ALPES));
		at(MILITARY_CAMP).adjacents.push_back(&at(RAETIA));
		at(MILITARY_CAMP).adjacents.push_back(&at(NORICUM));

		at(ALPES).adjacents.push_back(&at(NARBONENSIS));
		at(ALPES).adjacents.push_back(&at(LUGUDUNENSIS));
		at(ALPES).adjacents.push_back(&at(BELGICA));
		at(ALPES).adjacents.push_back(&at(RAETIA));

		at(RAETIA).adjacents.push_back(&at(ALPES));
		at(RAETIA).adjacents.push_back(&at(BELGICA));
		at(RAETIA).adjacents.push_back(&at(GERMANIA_SUPERIOR));
		at(RAETIA).adjacents.push_back(&at(NORICUM));

		at(NORICUM).adjacents.push_back(&at(RAETIA));
		
		at(NARBONENSIS).adjacents.push_back(&at(AQUITANIA));
		at(NARBONENSIS).adjacents.push_back(&at(LUGUDUNENSIS));
		at(NARBONENSIS).adjacents.push_back(&at(ALPES));

		at(LUGUDUNENSIS).adjacents.push_back(&at(BRITANNIA));
		at(LUGUDUNENSIS).adjacents.push_back(&at(AQUITANIA));
		at(LUGUDUNENSIS).adjacents.push_back(&at(NARBONENSIS));
		at(LUGUDUNENSIS).adjacents.push_back(&at(ALPES));
		at(LUGUDUNENSIS).adjacents.push_back(&at(BELGICA));

		at(BELGICA).adjacents.push_back(&at(BRITANNIA));
		at(BELGICA).adjacents.push_back(&at(LUGUDUNENSIS));
		at(BELGICA).adjacents.push_back(&at(GERMANIA_INFERIOR));
		at(BELGICA).adjacents.push_back(&at(GERMANIA_SUPERIOR));
		at(BELGICA).adjacents.push_back(&at(ALPES));
		at(BELGICA).adjacents.push_back(&at(RAETIA));

		at(GERMANIA_SUPERIOR).adjacents.push_back(&at(BELGICA));
		at(GERMANIA_SUPERIOR).adjacents.push_back(&at(GERMANIA_INFERIOR));
		at(GERMANIA_SUPERIOR).adjacents.push_back(&at(RAETIA));

		at(AQUITANIA).adjacents.push_back(&at(LUGUDUNENSIS));
		at(AQUITANIA).adjacents.push_back(&at(NARBONENSIS));
		
		at(BRITANNIA).adjacents.push_back(&at(LUGUDUNENSIS));
		at(BRITANNIA).adjacents.push_back(&at(BELGICA));
		at(BRITANNIA).adjacents.push_back(&at(GERMANIA_INFERIOR));

		at(GERMANIA_INFERIOR).adjacents.push_back(&at(BRITANNIA));
		at(GERMANIA_INFERIOR).adjacents.push_back(&at(BELGICA));
		at(GERMANIA_INFERIOR).adjacents.push_back(&at(GERMANIA_SUPERIOR));

	}

	const Province& findGeneral(PlayerColor color) const {
		for (auto i = 0; i < size(); ++i) {
			for (auto j = 0; j < at(i).generals.size(); ++j) {
				if (at(i).generals[j] == color)
					return at(i);
			}
		}
		cout << "General of color number " << int(color) << " not found.\n";
		exit(EXIT_FAILURE);
	}

	Province& findGeneral(PlayerColor color) {
		for (auto i = 0; i < size(); ++i) {
			for (auto j = 0; j < at(i).generals.size(); ++j) {
				if (at(i).generals[j] == color)
					return at(i);
			}
		}
		cout << "General of color number " << int(color) << " not found.\n";
		exit(EXIT_FAILURE);
	}

	vector<Province*> adjacentToGeneralList() const {
		for (auto i = 0; i < size(); ++i) {

		}
	}

	//bool generalCanMoveTo(PlayerColor color, ProvinceName name) const {
	//	for (
	//}
	
	void moveGeneral(PlayerColor color, ProvinceName name) {
		if (!findGeneral(color).isAdjacentTo(at(name))) {
			cout << "Nonadjacent movement of general\n";
			cout << findGeneral(color).getString() << " to " << at(name).getString() << endl;
			exit(EXIT_FAILURE);
		}
		findGeneral(color).removeGeneral(color);
		at(name).addGeneral(color);
	}
	
	void addLegionnaire(PlayerColor color, ProvinceName name) {
		if (name != MILITARY_CAMP) {
			at(MILITARY_CAMP).removeLegionnaire(color);
		}
		at(name).addLegionnaire(color);
	}

	void setNumberOfPlayers(size_t n) {
		n = (n > 4 ? 4 : n < 2 ? 2 : n);
		at(MILITARY_CAMP).campAmounts.resize(n);
	}
	
};

enum NumeralType {
	NUMERAL_NONE,
	NUMERAL_CONSTRUCTION,
	NUMERAL_TRAJAN_DEMAND,
	NUMERAL_FORUM_DEMAND,
	NUMERAL_EXTRA_ACTION,
	NUMERAL_WILD_CARD
};

struct OwnedTile {

	Glib::RefPtr<Gdk::Pixbuf> pixbuf;
	Coordinate anchor;
	Coordinate numeralAnchor;
	NumeralType type;
	size_t amount;
	Glib::RefPtr<Pango::Layout> layout;
	Pango::FontDescription font;
	OwnedTile()
		:amount (0), type(NUMERAL_NONE)
	{
		
		
	}

	void setup(const Glib::RefPtr<Gdk::Pixbuf>& _pixbuf, const Coordinate& _anchor, NumeralType _type = NUMERAL_NONE) {
		pixbuf = _pixbuf;
		anchor = _anchor;
		type   = _type;
		
		font.set_weight(Pango::WEIGHT_ULTRABOLD);
		font.set_family("Times New Roman");
		font.set_size(PANGO_SCALE * 22);
		
		Gtk::Button button;
		layout = Pango::Layout::create(button.get_pango_context());
		layout->set_font_description(font);
		layout->set_text("0");
		int w, h;
		layout->get_pixel_size(w, h);  
		numeralAnchor = anchor;
		numeralAnchor.first  += (pixbuf->get_width() / 2) - (w / 2);
		numeralAnchor.second += 2;
	}

	void replacePixbuf(const Glib::RefPtr<Gdk::Pixbuf>& _pixbuf) {
		pixbuf = _pixbuf;
	}

	int operator++() {                ++amount; return amount;}
	int operator--() {if (amount > 0) --amount; return amount;}

	string getNumeral() const {
		return to_string(long long (amount));
	}

	void drawOnWindow(Gtk::EventBox& box) {
		if (amount == 0) 
			return;
		box.get_window()->draw_pixbuf(pixbuf, 0, 0, anchor.first, anchor.second, pixbuf->get_width(), pixbuf->get_height(), Gdk::RGB_DITHER_MAX, 0, 0);
		
		if (type != NUMERAL_NONE) {
			layout->set_text(getNumeral()); 
			box.get_window()->draw_layout(box.get_style()->get_black_gc(), numeralAnchor.first + 1, numeralAnchor.second + 1, layout);
			box.get_window()->draw_layout(box.get_style()->get_white_gc(), numeralAnchor.first    , numeralAnchor.second    , layout);
		
		}
	}


};

class Viewer;
class Player 
	:public Gtk::EventBox
{
	PlayerColor color;
	Gdk::Color gdkColor;
	Wheel _wheel;
	vector<Peg> _hand;
	int _points;
	size_t _citizens;
	size_t _votes;
	Gtk::Image childImage;
	Glib::RefPtr<Gdk::Pixbuf> childPixbuf;
	size_t archPosition;
	vector<Coordinate> trajanTileAnchors;
	vector<Coordinate> archAnchors;
	vector<Coordinate> plusTwoAnchors;
	bitset<6> _extraActionsActive;
	bool _wildActionActive;
	bool _plusTwosActive;
	bool _wildCommodityActive;
	Glib::RefPtr<Gdk::GC> borderGC;
public:
	friend class Viewer;
	vector<CommodityCard> cardsInHand;
	vector<CommodityCard> cardsInPlay;
	vector<SenateCard> senateCards;
	Gtk::HBox cardsInHand_HBox;
	Gtk::HBox cardsInPlay_HBox;
	Gtk::HBox senateCards_HBox;
	vector<const TrajanTile*> trajanTiles;

	Glib::RefPtr<Gdk::Pixbuf> generalMarker;
	Glib::RefPtr<Gdk::Pixbuf> citizenMarker;
	Glib::RefPtr<Gdk::Pixbuf> senateMarker;
	static vector<vector <CoordinateList> > anchors;            //pegs
	static vector<vector <CoordinateList> > initializeAnchors();
	static Glib::RefPtr<Gdk::Pixbuf> arch023Pixbuf;
	static Glib::RefPtr<Gdk::Pixbuf> arch145Pixbuf;
	static Glib::RefPtr<Gdk::Pixbuf> plusTwoPixbuf;

	OwnedTile stepsConstructionTile;
	OwnedTile doorConstructionTile;
	OwnedTile fountainConstructionTile;
	OwnedTile roofConstructionTile;
	OwnedTile windowConstructionTile;
	
	OwnedTile breadTrajanTile;
	OwnedTile fireTrajanTile;
	OwnedTile helmetTrajanTile;

	OwnedTile breadForumTile;
	OwnedTile fireForumTile;
	OwnedTile helmetForumTile;

	OwnedTile wildActionTile;
	OwnedTile wildCommodityTile;
	OwnedTile wildDemandTile;
	OwnedTile wildConstructionTile;

	OwnedTile seaportExtraActionTile;
	OwnedTile forumExtraActionTile;
	OwnedTile militaryExtraActionTile;
	OwnedTile trajanExtraActionTile;
	OwnedTile senateExtraActionTile;
	OwnedTile constructionExtraActionTile;
		
	bitset<6> plusTwoTiles;
	
	vector<OwnedTile> senateTiles;

	vector<OwnedTile*> ownedTilePointers;
	
	sigc::signal<void, string&> pointsChangedSignal;

	sigc::signal<void, const Player&, size_t, Glib::RefPtr<Gdk::Pixbuf> > trajanTakenSignal;
	sigc::signal<void, const Player&, size_t> archMovedSignal;
	sigc::signal<void, const Player&, Glib::RefPtr<Gdk::Pixbuf>, bool> extraActionSignal;
	sigc::signal<void, const Player&, vector<Glib::RefPtr<Gdk::Pixbuf> >& > demandsMetSignal;

	//computer main action signal? here or in Viewer
	
	Player(PlayerColor c)
		:_points(0), color(c), _citizens(15), _votes(0), archPosition(0), trajanTiles(6, NULL), borderGC(NULL), _wildActionActive(false), _plusTwosActive(false), _wildCommodityActive(false)

	{   	
		
		switch(color) {																							
		case DARK_BLUE:
			childPixbuf = Gdk::Pixbuf::create_from_file(RootDirectory + "pJ1.jpg");
			generalMarker = Gdk::Pixbuf::create_from_file(RootDirectory + "general1.png");
			citizenMarker = Gdk::Pixbuf::create_from_file(RootDirectory + "legionnaire1.png");
			senateMarker  = Gdk::Pixbuf::create_from_file(RootDirectory + "s1.png");
			gdkColor = Gdk::Color("#0064B1"); 
			break;
		case RED:
			childPixbuf = Gdk::Pixbuf::create_from_file(RootDirectory + "pJ0.jpg");
			generalMarker = Gdk::Pixbuf::create_from_file(RootDirectory + "general0.png");
			citizenMarker = Gdk::Pixbuf::create_from_file(RootDirectory + "legionnaire0.png");
			senateMarker  = Gdk::Pixbuf::create_from_file(RootDirectory + "s0.png");
			gdkColor = Gdk::Color("#D71920");
			break;
		case GREEN:
			childPixbuf = Gdk::Pixbuf::create_from_file(RootDirectory + "pJ2.jpg");
			generalMarker = Gdk::Pixbuf::create_from_file(RootDirectory + "general2.png");
			citizenMarker = Gdk::Pixbuf::create_from_file(RootDirectory + "legionnaire2.png");
			senateMarker  = Gdk::Pixbuf::create_from_file(RootDirectory + "s2.png");
			gdkColor = Gdk::Color("#00AA4F");
			break;
		case BROWN:
			childPixbuf = Gdk::Pixbuf::create_from_file(RootDirectory + "pJ3.jpg");
			generalMarker = Gdk::Pixbuf::create_from_file(RootDirectory + "general3.png");
			citizenMarker = Gdk::Pixbuf::create_from_file(RootDirectory + "legionnaire3.png");
			senateMarker  = Gdk::Pixbuf::create_from_file(RootDirectory + "s3.png");
			gdkColor = Gdk::Color("#824817");
			break;
		}
	
		childImage.set(childPixbuf);
		add(childImage);
		
		modify_bg(Gtk::STATE_NORMAL, Gdk::Color("#4F4F4F"));
		senateCards_HBox.set_size_request(-1, 107);

		stepsConstructionTile   .setup(Gdk::Pixbuf::create_from_file(RootDirectory + "tc32.png", CONSTRUCTION_TILE_WIDTH, CONSTRUCTION_TILE_HEIGHT, true), Coordinate( 13,   9), NUMERAL_CONSTRUCTION);
		doorConstructionTile    .setup(Gdk::Pixbuf::create_from_file(RootDirectory + "tc42.png", CONSTRUCTION_TILE_WIDTH, CONSTRUCTION_TILE_HEIGHT, true), Coordinate( 13,  60), NUMERAL_CONSTRUCTION);
		fountainConstructionTile.setup(Gdk::Pixbuf::create_from_file(RootDirectory + "tc22.png", CONSTRUCTION_TILE_WIDTH, CONSTRUCTION_TILE_HEIGHT, true), Coordinate( 13, 111), NUMERAL_CONSTRUCTION);
		roofConstructionTile    .setup(Gdk::Pixbuf::create_from_file(RootDirectory + "tc12.png", CONSTRUCTION_TILE_WIDTH, CONSTRUCTION_TILE_HEIGHT, true), Coordinate( 13, 162), NUMERAL_CONSTRUCTION);
		windowConstructionTile  .setup(Gdk::Pixbuf::create_from_file(RootDirectory + "tc02.png", CONSTRUCTION_TILE_WIDTH, CONSTRUCTION_TILE_HEIGHT, true), Coordinate( 13, 213), NUMERAL_CONSTRUCTION);

		breadTrajanTile .setup(Gdk::Pixbuf::create_from_file(RootDirectory + "trajanTilesPlain/tt50.jpg", TRAJAN_TILE_WIDTH, TRAJAN_TILE_HEIGHT, true), Coordinate( 63, 5), NUMERAL_TRAJAN_DEMAND);
		fireTrajanTile  .setup(Gdk::Pixbuf::create_from_file(RootDirectory + "trajanTilesPlain/tt45.jpg", TRAJAN_TILE_WIDTH, TRAJAN_TILE_HEIGHT, true), Coordinate(127, 5), NUMERAL_TRAJAN_DEMAND);
		helmetTrajanTile.setup(Gdk::Pixbuf::create_from_file(RootDirectory + "trajanTilesPlain/tt51.jpg", TRAJAN_TILE_WIDTH, TRAJAN_TILE_HEIGHT, true), Coordinate(190, 5), NUMERAL_TRAJAN_DEMAND);

		breadForumTile .setup(Gdk::Pixbuf::create_from_file(RootDirectory + "tf4.jpg", FORUM_TILE_WIDTH, FORUM_TILE_HEIGHT, true), Coordinate( 74, 69), NUMERAL_FORUM_DEMAND);
		fireForumTile  .setup(Gdk::Pixbuf::create_from_file(RootDirectory + "tf5.jpg", FORUM_TILE_WIDTH, FORUM_TILE_HEIGHT, true), Coordinate(138, 69), NUMERAL_FORUM_DEMAND);
		helmetForumTile.setup(Gdk::Pixbuf::create_from_file(RootDirectory + "tf6.jpg", FORUM_TILE_WIDTH, FORUM_TILE_HEIGHT, true), Coordinate(200, 69), NUMERAL_FORUM_DEMAND);

		wildActionTile      .setup(Gdk::Pixbuf::create_from_file(RootDirectory + "tf15.jpg", FORUM_TILE_WIDTH, FORUM_TILE_HEIGHT, true), Coordinate( 88, 139), NUMERAL_WILD_CARD);
		wildCommodityTile  .setup(Gdk::Pixbuf::create_from_file(RootDirectory + "tf13.jpg", FORUM_TILE_WIDTH, FORUM_TILE_HEIGHT, true), Coordinate(130, 139), NUMERAL_WILD_CARD);
		wildDemandTile      .setup(Gdk::Pixbuf::create_from_file(RootDirectory + "tf14.jpg", FORUM_TILE_WIDTH, FORUM_TILE_HEIGHT, true), Coordinate( 88, 181), NUMERAL_WILD_CARD);
		wildConstructionTile.setup(Gdk::Pixbuf::create_from_file(RootDirectory + "tf16.jpg", FORUM_TILE_WIDTH, FORUM_TILE_HEIGHT, true), Coordinate(130, 181), NUMERAL_WILD_CARD); 

		seaportExtraActionTile     .setup(Gdk::Pixbuf::create_from_file(RootDirectory +  "tf8.jpg", FORUM_TILE_WIDTH, FORUM_TILE_HEIGHT, true), Coordinate(9 + (FORUM_TILE_WIDTH * 0), 274), NUMERAL_EXTRA_ACTION);
		forumExtraActionTile       .setup(Gdk::Pixbuf::create_from_file(RootDirectory +  "tf7.jpg", FORUM_TILE_WIDTH, FORUM_TILE_HEIGHT, true), Coordinate(9 + (FORUM_TILE_WIDTH * 1), 274), NUMERAL_EXTRA_ACTION);
		militaryExtraActionTile    .setup(Gdk::Pixbuf::create_from_file(RootDirectory +  "tf9.jpg", FORUM_TILE_WIDTH, FORUM_TILE_HEIGHT, true), Coordinate(9 + (FORUM_TILE_WIDTH * 2), 274), NUMERAL_EXTRA_ACTION);
		trajanExtraActionTile      .setup(Gdk::Pixbuf::create_from_file(RootDirectory + "tf10.jpg", FORUM_TILE_WIDTH, FORUM_TILE_HEIGHT, true), Coordinate(9 + (FORUM_TILE_WIDTH * 3), 274), NUMERAL_EXTRA_ACTION);
		senateExtraActionTile      .setup(Gdk::Pixbuf::create_from_file(RootDirectory + "tf11.jpg", FORUM_TILE_WIDTH, FORUM_TILE_HEIGHT, true), Coordinate(9 + (FORUM_TILE_WIDTH * 4), 274), NUMERAL_EXTRA_ACTION);
		constructionExtraActionTile.setup(Gdk::Pixbuf::create_from_file(RootDirectory + "tf12.jpg", FORUM_TILE_WIDTH, FORUM_TILE_HEIGHT, true), Coordinate(9 + (FORUM_TILE_WIDTH * 5), 274), NUMERAL_EXTRA_ACTION);

		plusTwoAnchors.push_back(seaportExtraActionTile.anchor);
		plusTwoAnchors.push_back(forumExtraActionTile.anchor);
		plusTwoAnchors.push_back(militaryExtraActionTile.anchor);
		plusTwoAnchors.push_back(senateExtraActionTile.anchor);
		plusTwoAnchors.push_back(trajanExtraActionTile.anchor);
		plusTwoAnchors.push_back(constructionExtraActionTile.anchor);
		for (auto i = 0; i < plusTwoAnchors.size(); ++i) {
			plusTwoAnchors[i].second += FORUM_TILE_HEIGHT + 2;
		}


		trajanTileAnchors.push_back(Coordinate(257,   6));
		trajanTileAnchors.push_back(Coordinate(411,   6));
		trajanTileAnchors.push_back(Coordinate(501, 150));
		trajanTileAnchors.push_back(Coordinate(411, 271));
		trajanTileAnchors.push_back(Coordinate(257, 271));
		trajanTileAnchors.push_back(Coordinate(191, 150));
		

		archAnchors.push_back(Coordinate(277,   8));
		archAnchors.push_back(Coordinate(428,   9));
		archAnchors.push_back(Coordinate(508, 138));
		archAnchors.push_back(Coordinate(432, 275));
		archAnchors.push_back(Coordinate(271, 279));
		archAnchors.push_back(Coordinate(195, 138));
		
		ownedTilePointers.push_back(&stepsConstructionTile   );
		ownedTilePointers.push_back(&doorConstructionTile    );
		ownedTilePointers.push_back(&fountainConstructionTile);
		ownedTilePointers.push_back(&roofConstructionTile    );
		ownedTilePointers.push_back(&windowConstructionTile  );

		ownedTilePointers.push_back(&breadTrajanTile         );
		ownedTilePointers.push_back(&fireTrajanTile          );
		ownedTilePointers.push_back(&helmetTrajanTile        );
														     
		ownedTilePointers.push_back(&breadForumTile          );
		ownedTilePointers.push_back(&fireForumTile           );
		ownedTilePointers.push_back(&helmetForumTile         );

		ownedTilePointers.push_back(&wildActionTile          );
		ownedTilePointers.push_back(&wildCommodityTile      );
		ownedTilePointers.push_back(&wildDemandTile          );
		ownedTilePointers.push_back(&wildConstructionTile    );

		ownedTilePointers.push_back(&seaportExtraActionTile     );
		ownedTilePointers.push_back(&forumExtraActionTile       );
		ownedTilePointers.push_back(&militaryExtraActionTile    );
		ownedTilePointers.push_back(&trajanExtraActionTile      );
		ownedTilePointers.push_back(&senateExtraActionTile      );
		ownedTilePointers.push_back(&constructionExtraActionTile);

		signal_expose_event().connect(sigc::mem_fun(*this, &Player::onExpose));

	}

	Player(const Player& another) 
		
	{
		color = another.color;

		_wheel = another._wheel;
		_hand = another._hand;
		_points = another._points;
		_citizens = another._citizens;
		_votes = another._votes;
		archPosition = another.archPosition;
		_extraActionsActive = another._extraActionsActive;
		_wildActionActive    = another._wildActionActive;
		_plusTwosActive      = another._plusTwosActive;
		_wildCommodityActive = another._wildCommodityActive;
		cardsInHand = another.cardsInHand;
		cardsInPlay = another.cardsInPlay;
		senateCards = another.senateCards;
		trajanTiles = another.trajanTiles; 

		stepsConstructionTile = 	  another.stepsConstructionTile; 
		doorConstructionTile = 		  another.doorConstructionTile; 
		fountainConstructionTile = 	  another.fountainConstructionTile; 
		roofConstructionTile = 		  another.roofConstructionTile; 
		windowConstructionTile = 	  another.windowConstructionTile; 
									 
		breadTrajanTile = 			  another.breadTrajanTile; 
		fireTrajanTile = 			  another.fireTrajanTile; 
		helmetTrajanTile = 			  another.helmetTrajanTile; 
									
		breadForumTile = 			  another.breadForumTile; 
		fireForumTile = 			  another.fireForumTile; 
		helmetForumTile = 			  another.helmetForumTile; 
									
		wildActionTile = 			  another.wildActionTile; 
		wildCommodityTile = 		  another.wildCommodityTile; 
		wildDemandTile = 			  another.wildDemandTile; 
		wildConstructionTile = 		  another.wildConstructionTile; 
									 
		seaportExtraActionTile = 	  another.seaportExtraActionTile; 
		forumExtraActionTile = 		  another.forumExtraActionTile; 
		militaryExtraActionTile = 	  another.militaryExtraActionTile; 
		trajanExtraActionTile = 	  another.trajanExtraActionTile; 
		senateExtraActionTile = 	  another.senateExtraActionTile; 
		constructionExtraActionTile = another.constructionExtraActionTile; 

		plusTwoTiles = another.plusTwoTiles;
		senateTiles = another.senateTiles;


	}

	PlayerColor getColor() const {return color;}
	const Gdk::Color& getGdkColor() const {return gdkColor;}
	string getString() const {
		switch (color) {
		case DARK_BLUE: return "Blue";
		case RED:       return "Red";
		case GREEN:     return "Green";
		case BROWN:     return "Brown"; 
		default: return "WTF";
		}
	}
	Hotzone getTileZone(const OwnedTile& ownedTile) const {
		return Hotzone(Coordinate(ownedTile.anchor.first, ownedTile.anchor.second), FORUM_TILE_WIDTH, FORUM_TILE_HEIGHT);
	}
	void drawBorder(const OwnedTile& ownedTile) {
		get_window()->draw_rectangle(borderGC, false, getTileZone(ownedTile).anchor.first, getTileZone(ownedTile).anchor.second, getTileZone(ownedTile).width, getTileZone(ownedTile).height);
		//queue_draw();
	}
	void drawBorder(const Coordinate& anchor) {
		get_window()->draw_rectangle(borderGC, false, anchor.first, anchor.second, FORUM_TILE_WIDTH, FORUM_TILE_HEIGHT);
		//queue_draw();
	}

	void setExtraActionActive(int action) {
		if (action == -1)
			setExtraActionActive(false);
		else if (action < _extraActionsActive.size()) {
			if (hasExtraActionFor(action)) {
				_extraActionsActive[action] = true;
			}
			else if (hasWildActionTile()) {
				setWildActionActive(true);
			}
		}
		queue_draw();
	}

	void setExtraActionActive(bool setting) {
		if (!setting) {
			_extraActionsActive.reset();
			setWildActionActive(false);
			queue_draw();
		}
	}
	void setWildActionActive(bool setting)    { _wildActionActive = setting;    }
	void setPlusTwosActive(bool setting)      { _plusTwosActive = setting;      }
	void setWildCommodityActive(bool setting) { _wildCommodityActive = setting; }

	const Wheel& getWheel() const {return _wheel;}

	void earnPoints(int points) {
		_points += points;
		
		string result(to_string(long long (_points)));
		while (result.length() < 3)
			result.insert(0, " ");
		pointsChangedSignal.emit(result);
	}
	int getPoints() const       {return _points;}
	
	void addVotes(size_t votes) { _votes += votes;}
	size_t getVotes() const     { return _votes;}
	void clearVotes() {
		_votes = 0;
		senateTiles.clear();
	}

	void sendCitizens(size_t number = 1) {
		if (number > _citizens) {
			cout << "Not enough citzens to send. Citizens == " << _citizens << "  number == " << number << endl;
			exit(EXIT_FAILURE);
		}
		_citizens -= number;
	}
	size_t getCitizens() const { return _citizens;}

	void spendsExtraActionTileFor(size_t type) {
		if (type > 5) {
			cout << "ERROR: spendsExtraActionTileFor: " << type << " too high\n";
			exit(EXIT_FAILURE);
		}
		if (!hasExtraActionFor(type)) {
			cout << "ERROR: spendsExtraActionTileFor: " << type << " not found\n";
			exit(EXIT_FAILURE);
		}
		Glib::RefPtr<Gdk::Pixbuf> tilePixbuf;
		switch (type) {
		case MAIN_SEAPORT:      
			--seaportExtraActionTile.amount;       
			tilePixbuf = seaportExtraActionTile.pixbuf;
			break;
		case MAIN_FORUM:
			--forumExtraActionTile.amount;		   
			tilePixbuf = forumExtraActionTile.pixbuf;
			break;
		case MAIN_MILITARY:
			--militaryExtraActionTile.amount;
			tilePixbuf = militaryExtraActionTile.pixbuf;
			break;
		case MAIN_SENATE:       
			--senateExtraActionTile.amount; 	   
			tilePixbuf = senateExtraActionTile.pixbuf;
			break;
		case MAIN_TRAJAN:       
			--trajanExtraActionTile.amount;	       
			tilePixbuf = trajanExtraActionTile.pixbuf;
			break;
		case MAIN_CONSTRUCTION: 
			--constructionExtraActionTile.amount;  
			tilePixbuf = constructionExtraActionTile.pixbuf;
			break;
		}
		extraActionSignal.emit(*this, tilePixbuf, hasPlusTwoTileFor(type));
	}

	void spendsWildActionTile(size_t type) {
		extraActionSignal.emit(*this, wildActionTile.pixbuf, hasPlusTwoTileFor(type));
		--wildActionTile.amount;       
	}

	bool hasExtraActionFor(size_t type) const {
		if (type > 5) {
			cout << "ERROR: hasExtraActionFor: " << type << " too high\n";
			exit(EXIT_FAILURE);
		}
		switch (type) {
		case MAIN_SEAPORT:      return seaportExtraActionTile.amount > 0;
		case MAIN_FORUM:        return forumExtraActionTile.amount > 0;
		case MAIN_MILITARY:     return militaryExtraActionTile.amount > 0;
		case MAIN_SENATE:       return senateExtraActionTile.amount > 0;
		case MAIN_TRAJAN:       return trajanExtraActionTile.amount > 0;
		case MAIN_CONSTRUCTION: return constructionExtraActionTile.amount > 0;
		}
	}
	bool hasPlusTwoTileFor(size_t type) const {
		if (type > 5) {
			cout << "ERROR: hasPlusTwoTileFor: " << type << " too high\n";
			exit(EXIT_FAILURE);
		}
		return plusTwoTiles[type];
	}
	bool hasWildActionTile() const {
		return wildActionTile.amount > 0;
	}
	bool hasWildCommodityTile() const {
		return wildCommodityTile.amount > 0;
	}

	bool hasWildConstructionTile() const {
		return wildConstructionTile.amount > 0;
	}

	bool hasWildDemandTile() const {
		return wildDemandTile.amount > 0;
	}

	void takeTile(const Tile& tile) {
		tile.awardTo(*this);
	}

	void advanceArch() {
		if (!spaceForTrajanTileAvailable())
			archPosition = trajanTiles.size();
		else {
			while (trajanTiles[archPosition] != NULL) {
				++archPosition;
				if (archPosition == trajanTiles.size())
					archPosition = 0;
			}
		}
		archMovedSignal.emit(*this, archPosition);
	}

	bool spaceForTrajanTileAvailable() const {
		for (auto i = 0; i < trajanTiles.size(); ++i) {
			if (trajanTiles[i] == NULL)
				return true;
		}
		return false;
	}

	void placeTrajanTileOnWheel(vector<TrajanTile*>& pile) {
		if (archPosition == trajanTiles.size() || pile.empty())
			return;
		trajanTiles[archPosition] = pile.back();
		trajanTakenSignal.emit(*this, archPosition, *pile.back());
		pile.pop_back();
		advanceArch();
	}

	void winTrajanTile(size_t position) {
		if (archPosition == trajanTiles.size()) {
			archPosition = position;
			archMovedSignal.emit(*this, archPosition);
		}
		trajanTiles[position]->awardTo(*this);
		trajanTiles[position] = NULL;
		
	}

	void moveGeneral(Continent& _continent, ProvinceName name) const {
		_continent.moveGeneral(color, name);
	}

	void addLegionnaireTo(Continent& _continent, ProvinceName name) {
		if (name == MILITARY_CAMP) {
			if (_citizens == 0) {
				cout << "Player " << getString() << " out of citizens\n";
				return;
			} 
			--_citizens;
		}
		_continent.addLegionnaire(color, name);
	}

	bool onExpose(GdkEventExpose* e) {
		if (borderGC == NULL) {
			borderGC = Gdk::GC::create(get_window());
			borderGC->set_rgb_fg_color(Gdk::Color("#FFFF00")); //yellow
			borderGC->set_line_attributes(2, Gdk::LineStyle::LINE_ON_OFF_DASH, Gdk::CapStyle::CAP_ROUND, Gdk::JoinStyle::JOIN_ROUND);
		}
		for (int i = 0; i < _wheel.size(); ++i) {
			if (_wheel[i].empty()) 
				continue;
			CoordinateList current = Player::anchors[i][_wheel[i].size()];
			for (auto p = 0; p < current.size(); ++p) { 
				get_window()->draw_pixbuf(_wheel[i][p], 0, 0, current[p].first, current[p].second, _wheel[i][p]->get_width(), _wheel[i][p]->get_height(), Gdk::RGB_DITHER_MAX, 0, 0);
			}
		}

		for (auto i = 0; i < ownedTilePointers.size(); ++i) {
			ownedTilePointers[i]->drawOnWindow(*this);
		}
		for (auto i = 0; i < senateTiles.size(); ++i) {
			senateTiles[i].drawOnWindow(*this);
		}
		for (auto i = 0; i < trajanTiles.size(); ++i) {
			if (trajanTiles[i] && !trajanTiles[i]->hidden) {
				if (i == 0 || i == 3) {
					get_window()->draw_pixbuf(trajanTiles[i]->rotatedLeftPixbuf , 0, 0, trajanTileAnchors[i].first, trajanTileAnchors[i].second, trajanTiles[i]->rotatedLeftPixbuf->get_width(), trajanTiles[i]->rotatedLeftPixbuf->get_height(), Gdk::RGB_DITHER_MAX, 0, 0);
				}
				else if (i == 1 || i == 4) {
					get_window()->draw_pixbuf(trajanTiles[i]->rotatedRightPixbuf, 0, 0, trajanTileAnchors[i].first, trajanTileAnchors[i].second, trajanTiles[i]->rotatedRightPixbuf->get_width(), trajanTiles[i]->rotatedRightPixbuf->get_height(), Gdk::RGB_DITHER_MAX, 0, 0);
				}
				else if (i == 2 || i == 5) {
					get_window()->draw_pixbuf(*trajanTiles[i], 0, 0, trajanTileAnchors[i].first, trajanTileAnchors[i].second, (*trajanTiles[i])->get_width(), (*trajanTiles[i])->get_height(), Gdk::RGB_DITHER_MAX, 0, 0);
				}
			}
			else if (i == archPosition) {
				if (i == 0 || i == 2 || i == 3) 
					get_window()->draw_pixbuf(arch023Pixbuf, 0, 0, archAnchors[i].first, archAnchors[i].second, arch023Pixbuf->get_width(), arch023Pixbuf->get_height(), Gdk::RGB_DITHER_MAX, 0, 0);
				else
					get_window()->draw_pixbuf(arch145Pixbuf, 0, 0, archAnchors[i].first, archAnchors[i].second, arch145Pixbuf->get_width(), arch145Pixbuf->get_height(), Gdk::RGB_DITHER_MAX, 0, 0);
			}
		}

		for (auto i = 0; i < plusTwoTiles.size(); ++i) {
			if (plusTwoTiles[i])
				get_window()->draw_pixbuf(plusTwoPixbuf, 0, 0, plusTwoAnchors[i].first, plusTwoAnchors[i].second, plusTwoPixbuf->get_width(), plusTwoPixbuf->get_height(), Gdk::RGB_DITHER_MAX, 0, 0);
		}

		Glib::RefPtr<Pango::Layout> tempLayout = breadTrajanTile.layout->copy();
		Pango::FontDescription tempFont = breadTrajanTile.font;
		tempFont.set_size(PANGO_SCALE * 20);
		tempLayout->set_font_description(tempFont);
		tempLayout->set_text(to_string(long long (_citizens)));
		int x;
		if (_citizens >= 10)
			x = 516;
		else
			x = 524;
		get_window()->draw_layout(get_style()->get_black_gc(), x + 1, 61 + 1, tempLayout);
		get_window()->draw_layout(get_style()->get_white_gc(), x    , 61    , tempLayout);

		if (_extraActionsActive.any()) {
			if (_extraActionsActive[MAIN_SEAPORT])       { drawBorder(seaportExtraActionTile);      }
			if (_extraActionsActive[MAIN_FORUM])         { drawBorder(forumExtraActionTile);        }
			if (_extraActionsActive[MAIN_MILITARY])      { drawBorder(militaryExtraActionTile);     }
			if (_extraActionsActive[MAIN_SENATE])        { drawBorder(senateExtraActionTile);       }
			if (_extraActionsActive[MAIN_TRAJAN])        { drawBorder(trajanExtraActionTile);       }
			if (_extraActionsActive[MAIN_CONSTRUCTION])  { drawBorder(constructionExtraActionTile); }
		}
		if (_wildActionActive) {
			drawBorder(wildActionTile);
		}
		if (_wildCommodityActive) {
			drawBorder(wildCommodityTile);
		}
		if (_plusTwosActive) {
			for (auto i = 0; i < plusTwoTiles.size(); ++i) {
				if (!plusTwoTiles[i]) 
					drawBorder(plusTwoAnchors[i]); //draw border around empty +2 spaces
			}
		}
		queue_draw();
		return false;
	}

	void endOfRoundDemands(multiset<DemandType>& list) {
		int neededBread   = list.count(BREAD); 	
		int neededFire    = list.count(FIRE);	
		int neededHelmets = list.count(HELMET);	
		
		vector<Glib::RefPtr<Gdk::Pixbuf> > pixbufs;

		if (neededBread + neededFire + neededHelmets != 3)
			cout << "Error endOfRoundDemands totals at " << neededBread + neededFire + neededHelmets << endl;
		
		for (int i = 1; i <= neededBread; ++i) { //one trajanTile pixbuf put in vector for each needed bread
			if (i <= breadTrajanTile.amount) {
				pixbufs.push_back(breadTrajanTile.pixbuf);
			}
		}
		neededBread -= breadTrajanTile.amount;
		neededBread = max(neededBread, 0);
		while (neededBread > 0 && breadForumTile.amount > 0) {
			--breadForumTile.amount;
			--neededBread;
			pixbufs.push_back(breadForumTile.pixbuf);
		}

		for (int i = 1; i <= neededFire; ++i) { 
			if (i <= fireTrajanTile.amount) {
				pixbufs.push_back(fireTrajanTile.pixbuf);
			}
		}

		neededFire -= fireTrajanTile.amount;
		neededFire = max(neededFire, 0);
		while (neededFire > 0 && fireForumTile.amount > 0) {
			--fireForumTile.amount;
			--neededFire;
			pixbufs.push_back(fireForumTile.pixbuf);
		}

		for (int i = 1; i <= neededHelmets; ++i) { 
			if (i <= helmetTrajanTile.amount) {
				pixbufs.push_back(helmetTrajanTile.pixbuf);
			}
		}
		neededHelmets -= helmetTrajanTile.amount;
		neededHelmets = max(neededHelmets, 0);
		while (neededHelmets > 0 && helmetForumTile.amount > 0) {
			--helmetForumTile.amount;
			--neededHelmets;
			pixbufs.push_back(helmetForumTile.pixbuf);
		}

		size_t totalRemainingNeeds = neededBread + neededFire + neededHelmets;
	
		while (totalRemainingNeeds > 0 && wildDemandTile.amount > 0) {
			--wildDemandTile.amount;
			--totalRemainingNeeds;
			pixbufs.push_back(wildDemandTile.pixbuf);
		}
		demandsMetSignal.emit(*this, pixbufs);
		switch(totalRemainingNeeds) {
		case 3:
			earnPoints(-15);
			break;
		case 2:
			earnPoints(-9);
			break;
		case 1:
			earnPoints(-4);
			break;
		}
	}

	void takeSenateCard(const SenateCard& card, bool isGold = true) {
		senateCards.push_back(card);
		if (!isGold)
			senateCards.back().flipDown();
		senateCards_HBox.pack_start(*Gtk::manage(new Gtk::Image(senateCards.back().getPixbuf())), Gtk::PACK_SHRINK);
		senateCards_HBox.show_all();
	}

	//good to keep this as a function for AI
	//as in: how much is a wild card worth to keep vs to play on a ship?
	int getWildCommodityBonusValue() const { 
		for (int i = 0; i < senateCards.size(); ++i) {
			if (senateCards[i].hasCommodityBonus()) {
				if (senateCards[i].isGoldSideUp())
					return 3;
				else
					return 2;
			}
		}
		return 0;
	}
	
	int getTotalWildDemandBonus() const {
		if (wildDemandTile.amount == 0)
			return 0;
		if (breadForumTile.amount > 0 && helmetForumTile.amount > 0 && fireForumTile.amount > 0)
			return 0;

		int goldDemandsUnmet = 0;
		int silverDemandsUnmet = 0;
		
		int result = 0;

		for (int i = 0; i < senateCards.size(); ++i) {
			if (senateCards[i].getDemandBonus() == BREAD && breadForumTile.amount == 0) {
				if (senateCards[i].isGoldSideUp()) 
					++goldDemandsUnmet;
				else
					++silverDemandsUnmet;
			}
			else if (senateCards[i].getDemandBonus() == HELMET && helmetForumTile.amount == 0) {
				if (senateCards[i].isGoldSideUp()) 
					++goldDemandsUnmet;
				else
					++silverDemandsUnmet;
			}
			else if (senateCards[i].getDemandBonus() == FIRE && fireForumTile.amount == 0) {
				if (senateCards[i].isGoldSideUp()) 
					++goldDemandsUnmet;
				else
					++silverDemandsUnmet;
			}
		}
		if (goldDemandsUnmet == 0 && silverDemandsUnmet == 0)
			return 0;

		int wildDemandsToCount = wildDemandTile.amount;
		while (wildDemandsToCount > 0) {
			if (goldDemandsUnmet > 0) {
				--goldDemandsUnmet;
				--wildDemandsToCount;
				result += 9;
			}
			else if (silverDemandsUnmet > 0) {
				--silverDemandsUnmet;
				--wildDemandsToCount;
				result += 6;
			}
		}
	
		return result;
	}


	int getNumberOfTrajanTiles() const {
		int count = 0;
		for (auto i = 0; i < trajanTiles.size(); ++i) {
			if (trajanTiles[i] != NULL && !trajanTiles[i]->hidden)
				++count;
		}
		return count;
	}

	int getConstructionBonus() const {
		int bonus = 0;
		int wildsToUse = wildConstructionTile.amount;
		
		vector<int> amounts;
		amounts.push_back(stepsConstructionTile.amount);
		amounts.push_back(doorConstructionTile.amount);
		amounts.push_back(fountainConstructionTile.amount);
		amounts.push_back(roofConstructionTile.amount);
		amounts.push_back(windowConstructionTile.amount);

		for (auto i = 0; i < amounts.size(); ++i) {
			if (amounts[i] == 4)
				bonus += 20;
			else if (amounts[i] == 3) {
				if (wildsToUse >= 1) {
					--wildsToUse;
					bonus += 20;
				}
				else
					bonus += 10;
			}
			else if (amounts[i] == 2) {
				if (wildsToUse == 2) {
					wildsToUse -= 2;
					bonus += 20;
				}
				else if (wildsToUse >=1) {
					--wildsToUse;
					bonus += 10;
				}
			}
		}

		return bonus;
	}



	//Computer functions

	bool computerCanTakeAction(MainActionType type) const {
		int target = int(type) - 1;
		if (target < 0)
			target = 5;
		for (size_t i = 0; i < _wheel.size(); ++i) {
			if (_wheel[target].size() > 0 && _wheel[target].size() % 6 == i + 1)
				return true;
			--target;
			if (target < 0)
				target = 5;
		}
		return false;
	}

	size_t computerPlacePegsForAction(MainActionType type) {
		int sourceTray = int(type) - 1;
		if (sourceTray < 0)
			sourceTray = 5;

		for (size_t i = 0; i < _wheel.size(); ++i) {
			if (_wheel[sourceTray].size() > 0 && _wheel[sourceTray].size() % 6 == i + 1)
				break;
			--sourceTray;
			if (sourceTray < 0)
				sourceTray = 5;
		}

		//	cout << "computerPlacePegsForAction() " << endl;
		//	cout << "type == " << int(type) << " : sourceTray == " << sourceTray << endl;

		_hand = _wheel[sourceTray];
		size_t result = _hand.size();// emit ?
		_wheel[sourceTray].clear();
		//check trajan tiles in order to try to win one
		while(!_hand.empty()) {
			++sourceTray;
			if (sourceTray > 5)
				sourceTray = 0;
			_wheel[sourceTray].add(_hand.back());
			_hand.pop_back();
		}
		
		//timer signal here
		if (trajanTiles[sourceTray] && trajanTiles[sourceTray]->trayHasMatch(_wheel[sourceTray])) {
			winTrajanTile(sourceTray);
		}
		return result;
		
	}

};

vector< vector<CoordinateList> > Player::anchors = Player::initializeAnchors();
vector< vector<CoordinateList> > Player::initializeAnchors() {
	vector<vector <CoordinateList> > resultVector; 
	
	vector <CoordinateList> result;
	CoordinateList current;
	int x, y;
	vector<Coordinate> centers;
	centers.push_back(  I_CENTER);
	centers.push_back( II_CENTER);
	centers.push_back(III_CENTER);
	centers.push_back( IV_CENTER);
	centers.push_back(  V_CENTER);
	centers.push_back( VI_CENTER);

	for (int i = 0; i < 6; ++i) {
		x = centers[i].first;
		y = centers[i].second;
		current.push_back(Coordinate(x + 8, y + 6)); //true center (used for mouse clicks)
		result.push_back(current);
		current.clear();

		current.push_back(Coordinate(x, y)); //1 peg
		result.push_back(current);
		current.clear();

		current.push_back(Coordinate(-13 + x,   6 + y)); //2 pegs, etc
		current.push_back(Coordinate( 11 + x, -18 + y));
		result.push_back(current);
		current.clear();

		current.push_back(Coordinate(-14 + x,   6 + y)); 
		current.push_back(Coordinate(  0 + x, -18 + y));
		current.push_back(Coordinate( 14 + x,   6 + y));
		result.push_back(current);
		current.clear();

		current.push_back(Coordinate(  2 + x, -20 + y));
		current.push_back(Coordinate(-16 + x,  -2 + y));
		current.push_back(Coordinate(  2 + x,  16 + y));
		current.push_back(Coordinate( 20 + x,  -2 + y));
		result.push_back(current);
		current.clear();

		current.push_back(Coordinate(-12 + x, -20 + y));
		current.push_back(Coordinate( 12 + x, -20 + y));
		current.push_back(Coordinate( 21 + x,   2 + y));
		current.push_back(Coordinate(-22 + x,   2 + y));
		current.push_back(Coordinate(  0 + x,  18 + y));
		result.push_back(current);
		current.clear();

		current.push_back(Coordinate(-12 + x, -20 + y));
		current.push_back(Coordinate( 12 + x, -20 + y));
		current.push_back(Coordinate(  0 + x,  -2 + y));
		current.push_back(Coordinate( 21 + x,   2 + y));
		current.push_back(Coordinate(-22 + x,   2 + y));
		current.push_back(Coordinate(  0 + x,  18 + y));
		result.push_back(current);
		current.clear();

		current.push_back(Coordinate(-12 + x, -20 + y));
		current.push_back(Coordinate( 12 + x, -20 + y));
		current.push_back(Coordinate(-22 + x,  -2 + y));
		current.push_back(Coordinate(  0 + x,  -2 + y));
		current.push_back(Coordinate( 21 + x,  -2 + y));
		current.push_back(Coordinate(-12 + x,  18 + y));
		current.push_back(Coordinate( 12 + x,  18 + y));
		result.push_back(current);
		current.clear();

		current.push_back(Coordinate(-17 + x, -19 + y));
		current.push_back(Coordinate(  0 + x, -15 + y));
		current.push_back(Coordinate( 17 + x, -19 + y));
		current.push_back(Coordinate( 13 + x,   0 + y));
		current.push_back(Coordinate(-13 + x,   0 + y));
		current.push_back(Coordinate( 17 + x,  19 + y));
		current.push_back(Coordinate(  0 + x,  13 + y));
		current.push_back(Coordinate(-17 + x,  19 + y));
		result.push_back(current);
		current.clear();

		current.push_back(Coordinate(-17 + x, -19 + y));
		current.push_back(Coordinate(  0 + x, -19 + y));
		current.push_back(Coordinate( 17 + x, -19 + y));
		current.push_back(Coordinate( 17 + x,   0 + y));
		current.push_back(Coordinate(  0 + x,   0 + y));
		current.push_back(Coordinate(-17 + x,   0 + y));
		current.push_back(Coordinate(-17 + x,  19 + y));
		current.push_back(Coordinate(  0 + x,  19 + y));
		current.push_back(Coordinate( 17 + x,  19 + y));
		result.push_back(current);
		current.clear();

		current.push_back(Coordinate(-17 + x, -19 + y));
		current.push_back(Coordinate(  0 + x, -15 + y));
		current.push_back(Coordinate( 17 + x, -19 + y));
		current.push_back(Coordinate( 28 + x,   0 + y));
		current.push_back(Coordinate( 12 + x,   0 + y));
		current.push_back(Coordinate(-12 + x,   0 + y));
		current.push_back(Coordinate(-28 + x,   0 + y));
		current.push_back(Coordinate(-17 + x,  19 + y));
		current.push_back(Coordinate(  0 + x,  13 + y));
		current.push_back(Coordinate( 17 + x,  19 + y));
		result.push_back(current);
		current.clear();

		current.push_back(Coordinate(  0 + x, -32 + y));
		current.push_back(Coordinate(-17 + x, -19 + y));
		current.push_back(Coordinate(  0 + x, -15 + y));
		current.push_back(Coordinate( 17 + x, -19 + y));
		current.push_back(Coordinate( 28 + x,   0 + y));
		current.push_back(Coordinate( 12 + x,   0 + y));
		current.push_back(Coordinate(-12 + x,   0 + y));
		current.push_back(Coordinate(-28 + x,   0 + y));
		current.push_back(Coordinate(-17 + x,  19 + y));
		current.push_back(Coordinate(  0 + x,  13 + y));
		current.push_back(Coordinate( 17 + x,  19 + y));
		result.push_back(current);
		current.clear();

		current.push_back(Coordinate(  0 + x, -32 + y));
		current.push_back(Coordinate(-17 + x, -19 + y));
		current.push_back(Coordinate(  0 + x, -15 + y));
		current.push_back(Coordinate( 17 + x, -19 + y));
		current.push_back(Coordinate( 28 + x,   0 + y));
		current.push_back(Coordinate( 12 + x,   0 + y));
		current.push_back(Coordinate(-12 + x,   0 + y));
		current.push_back(Coordinate(-28 + x,   0 + y));
		current.push_back(Coordinate(-17 + x,  19 + y));
		current.push_back(Coordinate(  0 + x,  13 + y));
		current.push_back(Coordinate( 17 + x,  19 + y));
		current.push_back(Coordinate(  0 + x,  30 + y));
		result.push_back(current);
		current.clear();

		resultVector.push_back(result);
		result.clear();
	}
	
	return resultVector;
}
Glib::RefPtr<Gdk::Pixbuf> Player::arch023Pixbuf;
Glib::RefPtr<Gdk::Pixbuf> Player::arch145Pixbuf;
Glib::RefPtr<Gdk::Pixbuf> Player::plusTwoPixbuf;



void TrajanTile::awardTo(Player& player) const {
	player.earnPoints(TrajanTile::VP);
	TrajanTile::hideSignal.emit();
	TrajanTile::awardedSignal.emit(player);
}

class StepsConstructionTile
	:public ConstructionTile
{
public:
	StepsConstructionTile(size_t _VP, const string& filename = RootDirectory + "p1.png")
		: ConstructionTile(_VP, filename) { }

	void awardTo(Player& player) const {
		player.earnPoints(VP);
		if (player.stepsConstructionTile.amount == 0) {
			firstConstructionSignal.emit(MAIN_FORUM);
		}
		++player.stepsConstructionTile;
		player.stepsConstructionTile.replacePixbuf(*this);
	}
	ConstructionType getType() const { return STEPS; }
};
class DoorConstructionTile
	:public ConstructionTile
{
public:
	DoorConstructionTile(size_t _VP, const string& filename = RootDirectory + "p1.png")
		: ConstructionTile(_VP, filename) { }

	void awardTo(Player& player) const {
		player.earnPoints(VP);
		if (player.doorConstructionTile.amount == 0) {
			firstConstructionSignal.emit(MAIN_SENATE);
		}
		++player.doorConstructionTile;
		player.doorConstructionTile.replacePixbuf(*this);
	}
	ConstructionType getType() const { return DOOR; }
};
class FountainConstructionTile
	:public ConstructionTile
{
public:
	FountainConstructionTile(size_t _VP, const string& filename = RootDirectory + "p1.png")
		: ConstructionTile(_VP, filename) { }

	void awardTo(Player& player) const {
		player.earnPoints(VP);
		if (player.fountainConstructionTile.amount == 0) {
			firstConstructionSignal.emit(MAIN_SEAPORT);
		}
		++player.fountainConstructionTile;
		player.fountainConstructionTile.replacePixbuf(*this);
	}
	ConstructionType getType() const { return FOUNTAIN; }
};
class RoofConstructionTile
	:public ConstructionTile
{
public:
	RoofConstructionTile(size_t _VP, const string& filename = RootDirectory + "p1.png")
		: ConstructionTile(_VP, filename) { }

	void awardTo(Player& player) const {
		player.earnPoints(VP);
		if (player.roofConstructionTile.amount == 0) {
			firstConstructionSignal.emit(MAIN_TRAJAN);
		}
		++player.roofConstructionTile;
		player.roofConstructionTile.replacePixbuf(*this);
	}
	ConstructionType getType() const { return ROOF; }
};
class WindowConstructionTile
	:public ConstructionTile
{
public:
	WindowConstructionTile(size_t _VP, const string& filename = RootDirectory + "p1.png")
		: ConstructionTile(_VP, filename) { }

	void awardTo(Player& player) const {
		player.earnPoints(VP);
		if (player.windowConstructionTile.amount == 0) {
			firstConstructionSignal.emit(MAIN_MILITARY);
		}
		++player.windowConstructionTile;
		player.windowConstructionTile.replacePixbuf(*this);
	}
	ConstructionType getType() const { return WINDOW; }
};

class ConstructionTileDeck
	:public vector<ConstructionTile* >
{
	WindowConstructionTile	   window2	;
	WindowConstructionTile	   window3	;
	WindowConstructionTile	   window4	;
	WindowConstructionTile	   window5	;
	RoofConstructionTile	   roof2	;
	RoofConstructionTile	   roof3	;
	RoofConstructionTile	   roof4	;
	RoofConstructionTile	   roof5	;
	FountainConstructionTile   fountain2;
	FountainConstructionTile   fountain3;
	FountainConstructionTile   fountain4;
	FountainConstructionTile   fountain5;
	StepsConstructionTile	   steps2	;
	StepsConstructionTile	   steps3	;
	StepsConstructionTile	   steps4	;
	StepsConstructionTile	   steps5	;
	DoorConstructionTile	   door2	;
	DoorConstructionTile	   door3	;
	DoorConstructionTile	   door4	;
	DoorConstructionTile	   door5	;
public:
	ConstructionTileDeck()
		:window2 (2, RootDirectory + "tc02.png"),
		 window3 (3, RootDirectory + "tc03.png"),
		 window4 (4, RootDirectory + "tc04.png"),
		 window5 (5, RootDirectory + "tc05.png"),
		 roof2	 (2, RootDirectory + "tc12.png"),
		 roof3	 (3, RootDirectory + "tc13.png"),
		 roof4	 (4, RootDirectory + "tc14.png"),
		 roof5	 (5, RootDirectory + "tc15.png"),
		 fountain2 (2, RootDirectory + "tc22.png"),
		 fountain3 (3, RootDirectory + "tc23.png"),
		 fountain4 (4, RootDirectory + "tc24.png"),
		 fountain5 (5, RootDirectory + "tc25.png"),
		 steps2	 (2, RootDirectory + "tc32.png"),
		 steps3	 (3, RootDirectory + "tc33.png"),
		 steps4	 (4, RootDirectory + "tc34.png"),
		 steps5	 (5, RootDirectory + "tc35.png"),
		 door2	 (2, RootDirectory + "tc42.png"),
		 door3	 (3, RootDirectory + "tc43.png"),
		 door4	 (4, RootDirectory + "tc44.png"),
		 door5	 (5, RootDirectory + "tc45.png")
	{
		push_back(&window2);
		push_back(&window3);
		push_back(&window4);
		push_back(&window5);
		push_back(&roof2);
		push_back(&roof3);
		push_back(&roof4);
		push_back(&roof5);
		push_back(&fountain2);
		push_back(&fountain3);
		push_back(&fountain4);
		push_back(&fountain5);
		push_back(&steps2);
		push_back(&steps3);
		push_back(&steps4);
		push_back(&steps5);
		push_back(&door2);
		push_back(&door3);
		push_back(&door4);
		push_back(&door5);
		random_shuffle(begin(), end());
	}
};

enum ForumType {
	DEMAND_BREAD,
	DEMAND_FIRE,
	DEMAND_HELMET,
	DEMAND_WILD,
	ACTION_SEAPORT,
	ACTION_FORUM,
	ACTION_MILITARY,
	ACTION_SENATE,
	ACTION_TRAJAN,
	ACTION_CONSTRUCTION,
	ACTION_WILD,
	VOTES_2,
	VOTES_3,
	VOTES_4,
	VOTES_5,
	CONSTRUCTION_TILE_WILD,
	COMMODITY_WILD,
};

struct ForumTile
	:public Tile
{
public:
	ForumTile(const string& filename)
		:Tile(filename) { 
			Glib::RefPtr<Gdk::Pixbuf>::operator=((*this)->scale_simple(FORUM_TILE_WIDTH, FORUM_TILE_HEIGHT, Gdk::INTERP_HYPER));
	}

	void awardTo(Player& player) const {;}
	virtual ForumType getType() const = 0;
};

struct SenateVoteForumTile
	:public ForumTile
{
	size_t votes;
	SenateVoteForumTile(size_t _votes, const string& filename)
		:ForumTile(filename), votes(_votes) { }
	void awardTo(Player& player) const {
		player.addVotes(votes);
		OwnedTile t;
		Coordinate c;
		c.first =  520 - ((player.senateTiles.size() / 3) * 23);
		c.second = 222 + ((player.senateTiles.size() % 3) * 44);
		t.setup(*this, c, NUMERAL_NONE);
		player.senateTiles.push_back(t);
		++player.senateTiles.back();
	}
	ForumType getType() const {
		switch(votes) {
		case 2:
			return VOTES_2;
		case 3:
			return VOTES_3;
		case 4:
			return VOTES_4;
		case 5:
			return VOTES_5;
		default:
			cout << "SenateVoteForumTile getType error: invalid parameter: " << votes << endl;
			cin >> *(new int);
			exit(EXIT_FAILURE);
		}
	}
};

struct DemandForumTile
	:public ForumTile
{
	DemandForumTile(const string& filename)
		:ForumTile(filename){ };
	void awardTo(Player& player) const {;}
};
struct BreadDemandForumTile
	:public DemandForumTile
{
	BreadDemandForumTile(const string& filename)
		:DemandForumTile(filename){ };
	void awardTo(Player& player) const {
		++player.breadForumTile;
	}
	ForumType getType() const {return DEMAND_BREAD;}
};
struct FireDemandForumTile
	:public DemandForumTile
{
	FireDemandForumTile(const string& filename)
		:DemandForumTile(filename){ };
	void awardTo(Player& player) const {
		++player.fireForumTile;
	}
	ForumType getType() const {return DEMAND_FIRE;}
};
struct HelmetDemandForumTile
	:public DemandForumTile
{
	HelmetDemandForumTile(const string& filename)
		:DemandForumTile(filename){ };
	void awardTo(Player& player) const {
		++player.helmetForumTile;
	}
	ForumType getType() const {return DEMAND_HELMET;}
};

struct ExtraActionTile
	:public ForumTile
{
	ExtraActionTile(const string& filename)
		: ForumTile(filename) {}
	//void awardTo(Player& player) const {;}
};
struct ExtraSeaportActionTile
	:public ExtraActionTile
{

	ExtraSeaportActionTile(const string& filename)
		: ExtraActionTile(filename) { }
	void awardTo(Player& player) const {
		++player.seaportExtraActionTile;
	}
	ForumType getType() const {return ACTION_SEAPORT;}
};
struct ExtraForumActionTile
	:public ExtraActionTile
{

	ExtraForumActionTile(const string& filename)
		: ExtraActionTile(filename) {}
	void awardTo(Player& player) const {
		++player.forumExtraActionTile;
	}
	ForumType getType() const {return ACTION_FORUM;}
};
struct ExtraMilitaryActionTile
	:public ExtraActionTile
{

	ExtraMilitaryActionTile(const string& filename)
		: ExtraActionTile(filename) {}
	void awardTo(Player& player) const {
		++player.militaryExtraActionTile;
	}
	ForumType getType() const {return ACTION_MILITARY;}
};
struct ExtraSenateActionTile
	:public ExtraActionTile
{

	ExtraSenateActionTile(const string& filename)
		: ExtraActionTile(filename) {}
	void awardTo(Player& player) const {
		++player.senateExtraActionTile;
	}
	ForumType getType() const {return ACTION_SENATE;}
};
struct ExtraTrajanActionTile
	:public ExtraActionTile
{

	ExtraTrajanActionTile(const string& filename)
		: ExtraActionTile(filename) {}
	void awardTo(Player& player) const {
		++player.trajanExtraActionTile;
	}
	ForumType getType() const {return ACTION_TRAJAN;}
};
struct ExtraConstructionActionTile
	:public ExtraActionTile
{

	ExtraConstructionActionTile(const string& filename)
		: ExtraActionTile(filename) {}
	void awardTo(Player& player) const {
		++player.constructionExtraActionTile;
	}
	ForumType getType() const {return ACTION_CONSTRUCTION;}
};

struct WildActionTile
	:public ForumTile
{
	WildActionTile(const string& filename)
		:ForumTile(filename) {}
	void awardTo(Player& player) const {
		++player.wildActionTile;
	}
	ForumType getType() const {return ACTION_WILD;}
};
struct WildCommodityTile
	:public ForumTile
{
	WildCommodityTile(const string& filename)
		:ForumTile(filename) {}
	void awardTo(Player& player) const {
		++player.wildCommodityTile;
	}
	ForumType getType() const {return COMMODITY_WILD;}

};
struct WildDemandTile
	:public ForumTile
{
	WildDemandTile(const string& filename)
		:ForumTile(filename) {}
	void awardTo(Player& player) const {
		++player.wildDemandTile;
	}
	ForumType getType() const {return DEMAND_WILD;}

};
struct WildConstructionTile
	:public ForumTile
{
	WildConstructionTile(const string& filename)
		:ForumTile(filename) {}
	void awardTo(Player& player) const {
		++player.wildConstructionTile;
	}
	ForumType getType() const {return CONSTRUCTION_TILE_WILD;}
};

class ForumTileDeck
	:public vector<const ForumTile*>
{
	SenateVoteForumTile senate2;
	SenateVoteForumTile senate3;
	SenateVoteForumTile senate4;
	SenateVoteForumTile senate5;
	BreadDemandForumTile  breadTile;
	FireDemandForumTile   fireTile;
	HelmetDemandForumTile helmetTile;
	ExtraSeaportActionTile  extraSeaportTile;
	ExtraForumActionTile    extraForumActionTile;
	ExtraMilitaryActionTile extraMilitaryActionTile;
	ExtraSenateActionTile   extraSenateActionTile;
	ExtraTrajanActionTile   extraTrajanActionTile;
	ExtraConstructionActionTile extraConstructionActionTile;
	WildActionTile		   wildActionTile;
	WildCommodityTile	   wildCommodityTile;
	WildDemandTile		   wildDemandTile;
	WildConstructionTile   wildConstructionTile;
public:
	vector<const ForumTile*> extraActionDeck;
	ForumTileDeck()
		: senate2(2, RootDirectory + "tf0.jpg"),
		  senate3(3, RootDirectory + "tf1.jpg"),
		  senate4(4, RootDirectory + "tf2.jpg"),
		  senate5(5, RootDirectory + "tf3.jpg"),
		  breadTile (RootDirectory + "tf4.jpg"),
		  fireTile  (RootDirectory + "tf5.jpg"),
		  helmetTile(RootDirectory + "tf6.jpg"),
		  extraSeaportTile       (RootDirectory + "tf8.jpg"),
		  extraForumActionTile   (RootDirectory + "tf7.jpg"),
		  extraMilitaryActionTile(RootDirectory + "tf9.jpg"),
		  extraSenateActionTile  (RootDirectory + "tf11.jpg"),
		  extraTrajanActionTile  (RootDirectory + "tf10.jpg"),
		  extraConstructionActionTile (RootDirectory + "tf12.jpg"),
		  wildActionTile       (RootDirectory + "tf15.jpg"),
		  wildCommodityTile    (RootDirectory + "tf13.jpg"),
		  wildDemandTile       (RootDirectory + "tf14.jpg"), 
		  wildConstructionTile (RootDirectory + "tf16.jpg")
	{
		for (int i = 0; i < 3; ++i) {
			push_back(&senate2);
			push_back(&senate3);
			push_back(&senate4);
			push_back(&senate5);
		}
		for (int i = 0; i < 14; ++i) {
			push_back(&breadTile);
			push_back(&fireTile);
			push_back(&helmetTile);
		}
		for (int i = 0; i < 2; ++i) {
			push_back(&wildActionTile);
			push_back(&wildCommodityTile);
			push_back(&wildDemandTile);
			push_back(&wildConstructionTile);
		}
		push_back(&wildCommodityTile); //total of 3
		push_back(&wildDemandTile);    //total of 3
		push_back(&extraSeaportTile           );
		push_back(&extraForumActionTile       );
		push_back(&extraMilitaryActionTile    );
		push_back(&extraSenateActionTile      );
		push_back(&extraTrajanActionTile      );
		push_back(&extraConstructionActionTile);

		for (int i = 0; i < 2; ++i) {
			extraActionDeck.push_back(&extraSeaportTile           );
			extraActionDeck.push_back(&extraForumActionTile       );
			extraActionDeck.push_back(&extraMilitaryActionTile    );
			extraActionDeck.push_back(&extraSenateActionTile      );
			extraActionDeck.push_back(&extraTrajanActionTile      );
			extraActionDeck.push_back(&extraConstructionActionTile);
		}
		random_shuffle(begin(), end());
		random_shuffle(extraActionDeck.begin(), extraActionDeck.end());
	}


};

struct TwoCardsTrajanTile
	:public TrajanTile
{
	
	TwoCardsTrajanTile(Color one, Color two, const string& filename, const string& rotatedFilename) 
		:TrajanTile(3, one, two, filename, rotatedFilename)
	{
		
	}

	void awardTo(Player& player) const {
		sendHistoryMessage(player, "DRAW TWO CARDS");
		TrajanTile::awardTo(player);
	}

	TrajanTileType getType() const {return TRAJAN_TWO_CARDS;}
};

struct NineVPTrajanTile
	:public TrajanTile
{
	NineVPTrajanTile(Color one, Color two, const string& filename, const string& rotatedFilename) 
		:TrajanTile(9, one, two, filename, rotatedFilename)
	{
		
	}
	void awardTo(Player& player) const {
		sendHistoryMessage(player, "VICTORY POINTS");
		TrajanTile::awardTo(player);
	}

	TrajanTileType getType() const {return TRAJAN_NINE_VP;}
};

struct ConstructionOneTrajanTile
	:public TrajanTile
{
	ConstructionOneTrajanTile(Color one, Color two, const string& filename, const string& rotatedFilename) 
		:TrajanTile(5, one, two, filename, rotatedFilename)
	{
		
	}
	void awardTo(Player& player) const {
		sendHistoryMessage(player, "ONE CITIZEN TO WORKER CAMP");
		TrajanTile::awardTo(player);
	}
	TrajanTileType getType() const {return TRAJAN_CONSTRUCTION_ONE;}
};

struct ConstructionTwoTrajanTile
	:public TrajanTile
{
	ConstructionTwoTrajanTile(Color one, Color two, const string& filename, const string& rotatedFilename) 
		:TrajanTile(2, one, two, filename, rotatedFilename)
	{
		
	}
	void awardTo(Player& player) const {
		sendHistoryMessage(player, "TWO CITIZENS TO WORKER CAMP");
		TrajanTile::awardTo(player);
	}
	TrajanTileType getType() const {return TRAJAN_CONSTRUCTION_TWO;}
};

struct MilitaryOneTrajanTile
	:public TrajanTile
{
	MilitaryOneTrajanTile(Color one, Color two, const string& filename, const string& rotatedFilename) 
		:TrajanTile(5, one, two, filename, rotatedFilename)
	{
		
	}
	void awardTo(Player& player) const {
		sendHistoryMessage(player, "ONE CITIZEN TO MILITARY CAMP");
		TrajanTile::awardTo(player);
	}
	TrajanTileType getType() const {return TRAJAN_MILITARY_ONE;}
};

struct MilitaryTwoTrajanTile
	:public TrajanTile
{
	MilitaryTwoTrajanTile(Color one, Color two, const string& filename, const string& rotatedFilename) 
		:TrajanTile(2, one, two, filename, rotatedFilename)
	{
		
	}
	void awardTo(Player& player) const {
		sendHistoryMessage(player, "TWO CITIZENS TO MILITARY CAMP");
		TrajanTile::awardTo(player);
	}
	TrajanTileType getType() const {return TRAJAN_MILITARY_TWO;}
};

struct PlusTwoTrajanTile
	:public TrajanTile
{
	
	PlusTwoTrajanTile(Color one, Color two, const string& filename, const string& rotatedFilename) 
		:TrajanTile(4, one, two, filename, rotatedFilename)
	{
		
	}
	void awardTo(Player& player) const {
		sendHistoryMessage(player, "+2 MARKER");
		TrajanTile::awardTo(player);
	}
	TrajanTileType getType() const {return TRAJAN_PLUS_TWO;}
};


struct BreadTrajanTile
	:public TrajanTile
{
	BreadTrajanTile( Color one, Color two, const string& filename, const string& rotatedFilename) 
		:TrajanTile(1, one, two, filename, rotatedFilename)
	{
		
	}
	void awardTo(Player& player) const {
		++player.breadTrajanTile.amount;
		sendHistoryMessage(player, "PEOPLE'S DEMAND TILE -- Bread");
		TrajanTile::awardTo(player);
	}
	TrajanTileType getType() const {return TRAJAN_BREAD;}
};

struct FireTrajanTile
	:public TrajanTile
{
	FireTrajanTile(Color one, Color two, const string& filename, const string& rotatedFilename) 
		:TrajanTile(1, one, two, filename, rotatedFilename)
	{
		
	}
	void awardTo(Player& player) const {
		++player.fireTrajanTile.amount;
		sendHistoryMessage(player, "PEOPLE'S DEMAND TILE -- Religion");
		TrajanTile::awardTo(player);
	}
	TrajanTileType getType() const {return TRAJAN_FIRE;}
};

struct HelmetTrajanTile
	:public TrajanTile
{
	HelmetTrajanTile(Color one, Color two, const string& filename, const string& rotatedFilename) 
		:TrajanTile(1, one, two, filename, rotatedFilename)
	{
		
	}
	void awardTo(Player& player) const {
		++player.helmetTrajanTile.amount;
		sendHistoryMessage(player, "PEOPLE'S DEMAND TILE -- Games");
		TrajanTile::awardTo(player);
	}
	TrajanTileType getType() const {return TRAJAN_HELMET;}
};


class TrajanTileDeck
{
	TwoCardsTrajanTile tt0;
	TwoCardsTrajanTile tt1;
	TwoCardsTrajanTile tt2;
	TwoCardsTrajanTile tt3;
	TwoCardsTrajanTile tt4;
	TwoCardsTrajanTile tt5;
	TwoCardsTrajanTile tt6;
	TwoCardsTrajanTile tt7;
	TwoCardsTrajanTile tt8;

	MilitaryOneTrajanTile tt9;
	MilitaryOneTrajanTile tt10;
	MilitaryTwoTrajanTile tt11;
	MilitaryTwoTrajanTile tt12;
	MilitaryOneTrajanTile tt13;
	MilitaryTwoTrajanTile tt14;
	MilitaryOneTrajanTile tt15;
	MilitaryOneTrajanTile tt16;
	MilitaryTwoTrajanTile tt17;

	ConstructionOneTrajanTile tt18;
	ConstructionTwoTrajanTile tt19;
	ConstructionTwoTrajanTile tt20;
	ConstructionOneTrajanTile tt21;
	ConstructionOneTrajanTile tt22;
	ConstructionTwoTrajanTile tt23;
	ConstructionOneTrajanTile tt24;
	ConstructionTwoTrajanTile tt25;
	ConstructionOneTrajanTile tt26;

	PlusTwoTrajanTile tt27;
	PlusTwoTrajanTile tt28;
	PlusTwoTrajanTile tt29;
	PlusTwoTrajanTile tt30;
	PlusTwoTrajanTile tt31;
	PlusTwoTrajanTile tt32;
	PlusTwoTrajanTile tt33;
	PlusTwoTrajanTile tt34;
	PlusTwoTrajanTile tt35;

	NineVPTrajanTile tt36;
	NineVPTrajanTile tt37;
	NineVPTrajanTile tt38;
	NineVPTrajanTile tt39;
	NineVPTrajanTile tt40;
	NineVPTrajanTile tt41;
	NineVPTrajanTile tt42;
	NineVPTrajanTile tt43;
	NineVPTrajanTile tt44;

	FireTrajanTile   tt45;
	FireTrajanTile   tt46;
	BreadTrajanTile  tt47;
	HelmetTrajanTile tt48;
	FireTrajanTile   tt49;
	BreadTrajanTile  tt50;
	HelmetTrajanTile tt51;
	BreadTrajanTile  tt52;
	HelmetTrajanTile tt53;
	
public:
	vector<TrajanTile*> deck1;
	vector<TrajanTile*> deck2;
	vector<TrajanTile*> deck3;
	vector<TrajanTile*> deck4;
	vector<TrajanTile*> deck5;
	vector<TrajanTile*> deck6;
	
	TrajanTileDeck() 
		:tt0(ORANGE,      ORANGE, "tt0.jpg",  "tt_000.png"),
		 tt1(BLUE,          BLUE, "tt1.jpg",  "tt_001.png"),
		 tt2(YELLOW, LIGHT_GREEN, "tt2.jpg",  "tt_002.png"),
		 tt3(YELLOW,      YELLOW, "tt3.jpg",  "tt_003.png"),
		 tt4(PINK,         WHITE, "tt4.jpg",  "tt_004.png"),
		 tt5(LIGHT_GREEN,   PINK, "tt5.jpg",  "tt_005.png"),
		 tt6(WHITE,         BLUE, "tt6.jpg",  "tt_006.png"),
		 tt7(ORANGE,      YELLOW, "tt7.jpg",  "tt_007.png"),
		 tt8(BLUE,        ORANGE, "tt8.jpg",  "tt_008.png"),

		 tt9 (YELLOW,        BLUE, "tt9.jpg",  "tt_009.png"),
		 tt10(BLUE,          BLUE, "tt10.jpg", "tt_010.png"),
		 tt11(WHITE,       YELLOW, "tt11.jpg", "tt_011.png"),
		 tt12(LIGHT_GREEN, YELLOW, "tt12.jpg", "tt_012.png"),
		 tt13(PINK,          BLUE, "tt13.jpg", "tt_013.png"),
		 tt14(PINK,        YELLOW, "tt14.jpg", "tt_014.png"),
		 tt15(WHITE,         BLUE, "tt15.jpg", "tt_015.png"),
		 tt16(LIGHT_GREEN,   BLUE, "tt16.jpg", "tt_016.png"),
		 tt17(ORANGE,        BLUE, "tt17.jpg", "tt_017.png"),

		 tt18(YELLOW,      ORANGE, "tt18.jpg", "tt_018.png"),
		 tt19(YELLOW,      YELLOW, "tt19.jpg", "tt_019.png"),
		 tt20(BLUE,        YELLOW, "tt20.jpg", "tt_020.png"),
		 tt21(PINK,        ORANGE, "tt21.jpg", "tt_021.png"),
		 tt22(WHITE,       ORANGE, "tt22.jpg", "tt_022.png"),
		 tt23(ORANGE,      YELLOW, "tt23.jpg", "tt_023.png"),
		 tt24(LIGHT_GREEN, ORANGE, "tt24.jpg", "tt_024.png"),
		 tt25(ORANGE,      ORANGE, "tt25.jpg", "tt_025.png"),
		 tt26(BLUE,   LIGHT_GREEN, "tt26.jpg", "tt_026.png"),

		 tt27(LIGHT_GREEN,  WHITE, "tt27.jpg", "tt_027.png"),
		 tt28(YELLOW,        PINK, "tt28.jpg", "tt_028.png"),
		 tt29(WHITE,         PINK, "tt29.jpg", "tt_029.png"),
		 tt30(ORANGE,        PINK, "tt30.jpg", "tt_030.png"),
		 tt31(PINK,          PINK, "tt31.jpg", "tt_031.png"),
		 tt32(LIGHT_GREEN,   PINK, "tt32.jpg", "tt_032.png"),
		 tt33(WHITE,        WHITE, "tt33.jpg", "tt_033.png"),
		 tt34(BLUE,          PINK, "tt34.jpg", "tt_034.png"),
		 tt35(PINK,         WHITE, "tt35.jpg", "tt_035.png"),

		 tt36(ORANGE,           ORANGE, "tt36.jpg", "tt_036.png"),
		 tt37(BLUE,               BLUE, "tt37.jpg", "tt_037.png"),
		 tt38(YELLOW,           YELLOW, "tt38.jpg", "tt_038.png"),
		 tt39(LIGHT_GREEN, LIGHT_GREEN, "tt39.jpg", "tt_039.png"),
		 tt40(ORANGE,            WHITE, "tt40.jpg", "tt_040.png"),
		 tt41(PINK,               PINK, "tt41.jpg", "tt_041.png"),
		 tt42(WHITE,             WHITE, "tt42.jpg", "tt_042.png"),
		 tt43(YELLOW,            WHITE, "tt43.jpg", "tt_043.png"),
		 tt44(BLUE,              WHITE, "tt44.jpg", "tt_044.png"),

		 tt45(WHITE,       LIGHT_GREEN, "tt45.jpg", "tt_045.png"),
		 tt46(WHITE,             WHITE, "tt46.jpg", "tt_046.png"),
		 tt47(PINK,               PINK, "tt47.jpg", "tt_047.png"),
		 tt48(LIGHT_GREEN, LIGHT_GREEN, "tt48.jpg", "tt_048.png"),
		 tt49(BLUE,             ORANGE, "tt49.jpg", "tt_049.png"),
		 tt50(LIGHT_GREEN, LIGHT_GREEN, "tt50.jpg", "tt_050.png"),
		 tt51(YELLOW,      LIGHT_GREEN, "tt51.jpg", "tt_051.png"),
		 tt52(ORANGE,      LIGHT_GREEN, "tt52.jpg", "tt_052.png"),
		 tt53(PINK,        LIGHT_GREEN, "tt53.jpg", "tt_053.png")

	{
		deck1.push_back(&tt0);
		deck1.push_back(&tt1);
		deck1.push_back(&tt2);
		deck1.push_back(&tt3);
		deck1.push_back(&tt4);
		deck1.push_back(&tt5);
		deck1.push_back(&tt6);
		deck1.push_back(&tt7);
		deck1.push_back(&tt8);

		deck4.push_back(&tt9);
		deck4.push_back(&tt10);
		deck4.push_back(&tt11);
		deck4.push_back(&tt12);
		deck4.push_back(&tt13);
		deck4.push_back(&tt14);
		deck4.push_back(&tt15);
		deck4.push_back(&tt16);
		deck4.push_back(&tt17);

		deck3.push_back(&tt18);
		deck3.push_back(&tt19);
		deck3.push_back(&tt20);
		deck3.push_back(&tt21);
		deck3.push_back(&tt22);
		deck3.push_back(&tt23);
		deck3.push_back(&tt24);
		deck3.push_back(&tt25);
		deck3.push_back(&tt26);

		deck5.push_back(&tt27);
		deck5.push_back(&tt28);
		deck5.push_back(&tt29);
		deck5.push_back(&tt30);
		deck5.push_back(&tt31);
		deck5.push_back(&tt32);
		deck5.push_back(&tt33);
		deck5.push_back(&tt34);
		deck5.push_back(&tt35);

		deck2.push_back(&tt36);
		deck2.push_back(&tt37);
		deck2.push_back(&tt38);
		deck2.push_back(&tt39);
		deck2.push_back(&tt40);
		deck2.push_back(&tt41);
		deck2.push_back(&tt42);
		deck2.push_back(&tt43);
		deck2.push_back(&tt44);

		deck6.push_back(&tt45);
		deck6.push_back(&tt46);
		deck6.push_back(&tt47);
		deck6.push_back(&tt48);
		deck6.push_back(&tt49);
		deck6.push_back(&tt50);
		deck6.push_back(&tt51);
		deck6.push_back(&tt52);
		deck6.push_back(&tt53);

		random_shuffle(deck1.begin(), deck1.end());
		random_shuffle(deck2.begin(), deck2.end());
		random_shuffle(deck3.begin(), deck3.end());
		random_shuffle(deck4.begin(), deck4.end());
		random_shuffle(deck5.begin(), deck5.end());
		random_shuffle(deck6.begin(), deck6.end());
	}
	
	
};

Gtk::TextView& operator<<(Gtk::TextView& view, const string& stream) {
	view.get_buffer()->insert_at_cursor(stream); 
	return view;
}
Gtk::TextView& operator<<(Gtk::TextView& view, int i) {
	ostringstream oss;
	oss << i;
	view.get_buffer()->insert_at_cursor(oss.str());
	return view;
}
Gtk::TextView& operator<<(Gtk::TextView& view, size_t i) {
	ostringstream oss;
	oss << i;
	view.get_buffer()->insert_at_cursor(oss.str());
	return view;
}
Gtk::TextView& operator<<(Gtk::TextView& view, double d) {
	ostringstream oss;
	oss << d;
	view.get_buffer()->insert_at_cursor(oss.str());
	return view;
}
Gtk::TextView& operator<<(Gtk::TextView& view, const char* _ch) {
	string s(_ch);
	view.get_buffer()->insert_at_cursor(s);
	return view;
}

class DebugWindow 
	:public Gtk::Window 
{
	
	Gtk::ScrolledWindow _scrolledWindow;
	Gtk::VButtonBox vbuttonbox;
	Gtk::Table table;
	Gtk::Image testImage;
public:
	Gtk::TextView _textView;
	Gtk::Button button1;
	Gtk::Button button2;
	Gtk::Button button3;
	Gtk::Button button4;
	Gtk::Button button5;
	Gtk::Button button6;
	DebugWindow() {
		_textView.set_editable(false);
		_textView.set_wrap_mode(Gtk::WRAP_WORD);
		Pango::FontDescription font = get_style()->get_font();
		font.set_size(PANGO_SCALE * 16);
		_textView.modify_font(font);
		//_textView.set_justification(Gtk::JUSTIFY_CENTER);
		_scrolledWindow.add(_textView);
		_scrolledWindow.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS);
		
		vbuttonbox.pack_start(button1);
		vbuttonbox.pack_start(button2);
		vbuttonbox.pack_start(button3);
		vbuttonbox.pack_start(button4);
		vbuttonbox.pack_start(button5);
		vbuttonbox.pack_start(button6);
		
		table.attach(_scrolledWindow, 0, 1, 0, 1);
		table.attach(vbuttonbox, 0, 1, 1, 2);
		add(table); 

		testImage.set(RootDirectory + "ddp2.png");
		testImage.show_all();
		//show_all();

		//button1.signal_clicked().connect(sigc::mem_fun(*this, &DebugWindow::scrollToBegin));
		//button2.signal_clicked().connect(sigc::mem_fun(*this, &DebugWindow::addChild));
		//button3.signal_clicked().connect(sigc::mem_fun(*this, &DebugWindow::removeChild));
	}

	void print(const string& message) {
		_textView.get_buffer()->insert_at_cursor(message + '\n');
		_scrolledWindow.get_vadjustment()->set_value(_scrolledWindow.get_vadjustment()->get_upper());

	}

	void print(ostringstream& oss) {
		_textView.get_buffer()->insert_at_cursor(oss.str() + '\n');
		oss.str("");
		_scrolledWindow.get_vadjustment()->set_value(_scrolledWindow.get_vadjustment()->get_upper());
	}

	void scrollToBegin() {
		_scrolledWindow.get_vadjustment()->set_value(_scrolledWindow.get_vadjustment()->get_lower());
	}

	void scrollToEnd() {
		_scrolledWindow.get_vadjustment()->set_value(_scrolledWindow.get_vadjustment()->get_upper() - _scrolledWindow.get_vadjustment()->get_page_size());
		
	}

};

class PegButton
	:public Gtk::Button
{
public:
	Color color;
	static const size_t buttonSize = 32;
	sigc::signal<void> pegSignal;
	PegButton(const Peg& peg)
		:color (peg.color)
	{
		set_relief(Gtk::RELIEF_NONE);
		set_can_focus(false);
		Gtk::Image* childImage = Gtk::manage(new Gtk::Image);
		childImage->set(peg);
		add(*childImage); 
		set_size_request(buttonSize, buttonSize);
		signal_clicked().connect(sigc::mem_fun(*this, &PegButton::sendPegSignal));
		show_all();
	}

	void sendPegSignal() {
		pegSignal.emit();
	}

};

class SuperButton
	:public Gtk::EventBox
{
public:
	Gtk::Image image;
	Glib::RefPtr<Gdk::Pixbuf> normal;
	Glib::RefPtr<Gdk::Pixbuf> highlighted;
	Glib::RefPtr<Gdk::Pixbuf> pressed;

	SuperButton()
		: normal(Gdk::Pixbuf::create_from_file(RootDirectory + "normal.png")), 
		  highlighted(Gdk::Pixbuf::create_from_file(RootDirectory + "highlighted.png")),
		  pressed(Gdk::Pixbuf::create_from_file(RootDirectory + "pressed2.png"))
	{
		add(image);
		image.set(normal);
		signal_enter_notify_event().connect(  sigc::mem_fun(*this, &SuperButton::onMouseOver));
		signal_leave_notify_event().connect(  sigc::mem_fun(*this, &SuperButton::onMouseOver));
		signal_button_press_event().connect(  sigc::mem_fun(*this, &SuperButton::onClick));
		signal_button_release_event().connect(sigc::mem_fun(*this, &SuperButton::onRelease));
	}

	bool onMouseOver(GdkEventCrossing* e) {
		if (e->type == GDK_ENTER_NOTIFY)
			image.set(highlighted);
		else 
			image.set(normal);
		return false;
	}

	bool onClick(GdkEventButton* e) {
		if (e->button != 1 || e->type != GDK_BUTTON_PRESS)
			return false;
		image.set(pressed);
		return false;
	}


	bool onRelease(GdkEventButton* e) {
		//if (e->type == GDK_ENTER_NOTIFY)
		//	image.set(highlighted);
		////if (e->button != 1 || e->type != GDK_BUTTON_RELEASE)
		//else
			image.set(highlighted);
		return false;
	}

};

class Viewer
	:public Gtk::VBox
{
public:
	
	Gtk::Notebook notebook;
	
	Player darkbluePlayer;
	Player redPlayer;
	Player greenPlayer;
	Player brownPlayer;

	Player& humanPlayer;

	Gtk::HButtonBox hButtonBox;
	Gtk::Button randomButton;
	Gtk::Button cancelButton;
	Gtk::Label randomButtonLabel;
	Gtk::Label cancelButtonLabel;
	
	Gtk::Image filler;
	Gtk::Table handTable;
	vector<Peg> hand;
	size_t timeAdvancedThisTurn;
	
	Wheel& _wheel;
	Wheel backUpWheel;

	Wheel::iterator highlightedTrayIter;
	Glib::RefPtr<Gdk::Pixbuf> highlight;

	vector<Hotzone> extraActionZones;
	vector<Hotzone> plusTwoZones;
	Hotzone wildActionZone;
	Hotzone wildCommodityZone;

	sigc::signal<void, size_t> traySignal;
	sigc::signal<void, size_t> extraActionSignal;
	sigc::signal<void, size_t> plusTwoSignal;
	sigc::signal<void> wildActionSignal;
	sigc::signal<void> wildCommoditySignal;
	
	sigc::signal<void, guint> pageSignal;

	sigc::connection traysClickable;

	sigc::signal<void, size_t> timerSignal;

	sigc::signal<void, size_t> mainActionSignal;
	sigc::signal<void, const string&> textSignal;
	
	sigc::signal<void, size_t> partialAdvanceSignal;
	sigc::signal<void> resetSignal;
	
	Viewer()
		: _wheel(humanPlayer._wheel),
	      highlightedTrayIter(_wheel.end()),
		  darkbluePlayer(DARK_BLUE),
		  redPlayer(RED),
		  greenPlayer(GREEN),
		  brownPlayer(BROWN),
		  humanPlayer(darkbluePlayer)
		
	{
		notebook.set_can_focus(false);
		
		
		
		traySignal.connect(sigc::mem_fun(*this, &Viewer::takeTrayToHand));
		traysClickable = humanPlayer.signal_button_press_event().connect(sigc::mem_fun(*this, &Viewer::onPlayerClick));
		traysClickable.block();
		humanPlayer.signal_button_press_event().connect(sigc::mem_fun(*this, &Viewer::onMiscClick));
		
		randomButton.set_can_focus(false); 
		cancelButton.set_can_focus(false);
		randomButton.set_relief(Gtk::RELIEF_NONE);
		cancelButton.set_relief(Gtk::RELIEF_NONE);	
		randomButtonLabel.set_markup("<span font_family = \"" + defaultFont + "\" size=\"9216\" foreground=\"#FAEBD7\" weight=\"600\">Random</span>");
		cancelButtonLabel.set_markup("<span font_family = \"" + defaultFont + "\" size=\"9216\" foreground=\"#FAEBD7\" weight=\"600\">Cancel</span>");
		randomButton.add(randomButtonLabel);
		cancelButton.add(cancelButtonLabel);
		
		hButtonBox.set_layout(Gtk::BUTTONBOX_CENTER);
		hButtonBox.pack_start(randomButton);
		hButtonBox.pack_start(cancelButton);
		randomButton.signal_clicked().connect(sigc::mem_fun(*this, &Viewer::placeAllAtRandom));
		cancelButton.signal_clicked().connect(sigc::mem_fun(*this, &Viewer::reset));
		
		handTable.set_size_request(-1, PegButton::buttonSize);
		handTable.resize(1, 13); //12 pegs + filler
		
		filler.set(Gdk::Pixbuf::create(Gdk::COLORSPACE_RGB, true, 8, 300, 32));
		filler.get_pixbuf()->fill(00000000);
		handTable.attach(filler, 0, 1, 0, 1, Gtk::SHRINK, Gtk::SHRINK);

		highlight = Gdk::Pixbuf::create_from_file(RootDirectory + "trayHighlight.png");
		
		notebook.append_page(humanPlayer, "Blue", "blue menu");
		notebook.append_page(redPlayer, "Red", "red menu");
		notebook.append_page(greenPlayer, "Green", "green menu");
		notebook.append_page(brownPlayer, "Brown", "brown menu");
		dynamic_cast<Gtk::Label*>(notebook.get_tab_label(humanPlayer))->set_markup   ("<span font_family = \"" + defaultFont + "\" size=\"10240\" foreground=\"#0064B1\" weight=\"600\">  Blue  </span>");
		dynamic_cast<Gtk::Label*>(notebook.get_tab_label(redPlayer))->set_markup     ("<span font_family = \"" + defaultFont + "\" size=\"10240\" foreground=\"#D71920\" weight=\"600\">  Red  </span>");
		dynamic_cast<Gtk::Label*>(notebook.get_tab_label(greenPlayer))->set_markup   ("<span font_family = \"" + defaultFont + "\" size=\"10240\" foreground=\"#00AA4F\" weight=\"600\">  Green  </span>");
		dynamic_cast<Gtk::Label*>(notebook.get_tab_label(brownPlayer))->set_markup   ("<span font_family = \"" + defaultFont + "\" size=\"10240\" foreground=\"#824817\" weight=\"600\">  Brown  </span>");
					
		pack_start(notebook);
		pack_start(handTable);
		pack_start(hButtonBox);
		show_all();
				
		notebook.signal_switch_page().connect(sigc::hide<0>(sigc::mem_fun(*this, &Viewer::sendPageNumber)));
		
		humanPlayer.signal_expose_event().connect(sigc::mem_fun(*this, &Viewer::onExpose));

		extraActionZones.push_back(humanPlayer.getTileZone(humanPlayer.seaportExtraActionTile)); 
		extraActionZones.push_back(humanPlayer.getTileZone(humanPlayer.forumExtraActionTile));
		extraActionZones.push_back(humanPlayer.getTileZone(humanPlayer.militaryExtraActionTile));
		extraActionZones.push_back(humanPlayer.getTileZone(humanPlayer.senateExtraActionTile)); //keep in same order as enums
		extraActionZones.push_back(humanPlayer.getTileZone(humanPlayer.trajanExtraActionTile));
		extraActionZones.push_back(humanPlayer.getTileZone(humanPlayer.constructionExtraActionTile));

		plusTwoZones = extraActionZones;

		for (auto i = 0; i < extraActionZones.size(); ++i) {
			plusTwoZones[i].anchor.second += FORUM_TILE_HEIGHT + 2;
		}

		wildActionZone = humanPlayer.getTileZone(humanPlayer.wildActionTile);
		wildCommodityZone = humanPlayer.getTileZone(humanPlayer.wildCommodityTile);

	}

	void startOfGame() {
		randomButton.hide();
		cancelButton.hide();
	}

	void startTurn() {
		textSignal.emit("Select a tray.");
		//if (!traysClickable.blocked()) {
		//	return;
		//}
		randomButton.hide();
		cancelButton.hide();
		traysClickable.unblock();
		update();
	}

	void sendPageNumber(guint page) { 
		pageSignal.emit(page);
	}

	size_t getTimeAdvancedThisTurn() const {
		return timeAdvancedThisTurn;
	}

	bool isWithinCircle(int clicked_x, int clicked_y, size_t wheelNumber) {
		int center_x = Player::anchors[wheelNumber][0][0].first;
		int center_y = Player::anchors[wheelNumber][0][0].second;
		int x = clicked_x - center_x;
		int y = clicked_y - center_y;
		return (x * x) + (y * y) < TRAY_RADIUS * TRAY_RADIUS;
	}

	bool onPlayerClick(GdkEventButton* e) {
		if (e->button != 1 || e->type != GDK_BUTTON_PRESS)
			return false;
		for (auto i = 0; i < _wheel.size(); ++i) {
			if (isWithinCircle(e->x, e->y, i)) {
				traySignal.emit(i);
				return true;
			}
		}
		return false;
	}

	bool onMiscClick(GdkEventButton* e) {
		if (e->button != 1 || e->type != GDK_BUTTON_PRESS)
			return false;
		
		for (auto i = 0; i < extraActionZones.size(); ++i) {
			if (extraActionZones[i].contains(e->x, e->y)) {
				extraActionSignal.emit(i);
				return true;
			}
			if (plusTwoZones[i].contains(e->x, e->y)) {
				plusTwoSignal.emit(i);
				return true;
			}
			if (wildCommodityZone.contains(e->x, e->y)) {
				wildCommoditySignal.emit();
				return true;
			}
			if (wildActionZone.contains(e->x, e->y)) {
				wildActionSignal.emit();
				return true;
			}
		}
	}
	
	void update() {
		queue_draw();
	}

	bool onExpose(GdkEventExpose* e) {

		if (!traysClickable.blocked()) {
			if (hand.empty()) {
				for (int i = 0; i < _wheel.size(); ++i) {
					if (!_wheel[i].empty()) {
						Coordinate anchor(Player::anchors[i][0][0].first - (highlight->get_width() / 2), Player::anchors[i][0][0].second - (highlight->get_height() / 2));
						humanPlayer.get_window()->draw_pixbuf(highlight, 0, 0, anchor.first, anchor.second, highlight->get_width(), highlight->get_height(), Gdk::RGB_DITHER_MAX, 0, 0);
					}
				}
			}
			else  { 
				int i = highlightedTrayIter - _wheel.begin(); 
				Coordinate anchor(Player::anchors[i][0][0].first - (highlight->get_width() / 2), Player::anchors[i][0][0].second - (highlight->get_height() / 2));
				humanPlayer.get_window()->draw_pixbuf(highlight, 0, 0, anchor.first, anchor.second, highlight->get_width(), highlight->get_height(), Gdk::RGB_DITHER_MAX, 0, 0);
			}
		}
		Player* currentPlayer = dynamic_cast<Player*>(notebook.get_nth_page(notebook.get_current_page()));
		currentPlayer->onExpose(e);
		update();
		return false;
	}

	void takeTrayToHand(size_t trayNumber) {
		
		if (!hand.empty()) 
			return;
		if (_wheel[trayNumber].empty())
			return;

		textSignal.emit("");
		randomButton.show_all();
		cancelButton.show_all();
		backUpWheel = _wheel;
		hand = _wheel[trayNumber];
		timeAdvancedThisTurn = hand.size();
		
		for (auto i = 0; i < _wheel[trayNumber].size(); ++i) {
			PegButton* p = Gtk::manage(new PegButton(_wheel[trayNumber][i].color));
			handTable.attach(*p, i + 1, i + 2, 0, 1, Gtk::SHRINK, Gtk::SHRINK, 5, 5);
			p->pegSignal.connect(sigc::bind<PegButton&>(sigc::mem_fun(*this, &Viewer::onPegButtonClick), *p));
		}
		_wheel[trayNumber].clear();
		filler.set_size_request((SHEET_WIDTH - ((PegButton::buttonSize + 10) * hand.size())) / 2, PegButton::buttonSize - 1);
		handTable.show_all();
		highlightedTrayIter = _wheel.begin() + trayNumber;
		nextTray();
		update();
		partialAdvanceSignal.emit(hand.size());
	}

	void reset() {
		_wheel = backUpWheel;
		hand.clear();
		vector<Widget*> vec =  handTable.get_children();
		for (auto i = 0; i < vec.size(); ++i) {
			handTable.remove(*vec[i]);
		}
		handTable.attach(filler, 0, 1, 0, 1, Gtk::SHRINK, Gtk::SHRINK);
		startTurn();
		update();
		resetSignal.emit();
	}

	void placeAllAtRandom() {
		random_shuffle(hand.begin(), hand.end());
		while (!hand.empty()) {
			highlightedTrayIter->add(hand.back());
			hand.pop_back();
			if (!hand.empty())
				nextTray();
		}
		vector<Widget*> vec =  handTable.get_children();
		for (auto i = 0; i < vec.size(); ++i) {
			handTable.remove(*vec[i]);
		}
		handTable.attach(filler, 0, 1, 0, 1, Gtk::SHRINK, Gtk::SHRINK);
		traysClickable.block();
		randomButton.hide();
		cancelButton.hide();
		update();
		size_t trayNumber = highlightedTrayIter - _wheel.begin();
		timerSignal.emit(trayNumber);
		if (humanPlayer.trajanTiles[trayNumber] && humanPlayer.trajanTiles[trayNumber]->trayHasMatch(*highlightedTrayIter)) {
			humanPlayer.winTrajanTile(trayNumber);
		}
		mainActionSignal.emit(trayNumber);
		highlightedTrayIter = _wheel.end();
		update();
		
	}

	Glib::RefPtr<Gdk::Pixbuf> newFiller() {
		Glib::RefPtr<Gdk::Pixbuf> result = Gdk::Pixbuf::create(Gdk::COLORSPACE_RGB, true, 8, ((SHEET_WIDTH - ((PegButton::buttonSize + 10) * hand.size())) / 2), PegButton::buttonSize - 1);
		result->fill(00000000);  
		return result;
	}

	void onPegButtonClick(PegButton& p) {
		highlightedTrayIter->add(p.color);
		handTable.remove(p);
		hand.erase(find(hand.begin(), hand.end(), p.color));
		if (hand.empty()) {
			traysClickable.block();
			randomButton.hide();
			cancelButton.hide();
			update();
			size_t trayNumber = highlightedTrayIter - _wheel.begin();
			timerSignal.emit(trayNumber);
			if (humanPlayer.trajanTiles[trayNumber] && humanPlayer.trajanTiles[trayNumber]->trayHasMatch(*highlightedTrayIter)) {
				humanPlayer.winTrajanTile(trayNumber);
			}
			mainActionSignal.emit(trayNumber);
			highlightedTrayIter = _wheel.end();
			update();
			
		}
		else {
			nextTray();
			queue_draw();
		}
	}
	
	void nextTray() {
		++highlightedTrayIter;
		if (highlightedTrayIter == _wheel.end())
			highlightedTrayIter = _wheel.begin();
	}

};

class CommodityCardDrawDeck
	:public vector<CommodityCard>
{
	
public:
	vector<CommodityCard> leftDiscardPile;
	vector<CommodityCard> rightDiscardPile;

	Gtk::EventBox drawPileEventBox;
	Gtk::EventBox leftDiscardPileEventBox;
	Gtk::EventBox rightDiscardPileEventBox;
	Gtk::Image drawPileImage;
	Gtk::Image leftDiscardPileImage;
	Gtk::Image rightDiscardPileImage;
	
	static Glib::RefPtr<Gdk::Pixbuf> cardBackPixbuf;

	sigc::signal<void> drawPileClickedSignal;
	sigc::signal<void> leftDiscardPileClickedSignal;
	sigc::signal<void> rightDiscardPileClickedSignal;
	
	CommodityCardDrawDeck()
	{
		for (auto i = 0; i < 5; ++i) {
			push_back(CommodityCard(COLUMNS,  RootDirectory + "c0.png"));
			push_back(CommodityCard(FURS,     RootDirectory + "c1.png"));
			push_back(CommodityCard(SCROLLS,  RootDirectory + "c2.png")); 
			push_back(CommodityCard(OILS,     RootDirectory + "c3.png"));
			push_back(CommodityCard(FRUIT,    RootDirectory + "c4.png"));
			push_back(CommodityCard(CERAMICS, RootDirectory + "c5.png"));
			push_back(CommodityCard(WINE,     RootDirectory + "c6.png"));
			push_back(CommodityCard(FISH,     RootDirectory + "c7.png"));
			push_back(CommodityCard(JEWELRY,  RootDirectory + "c8.png"));
			push_back(CommodityCard(GEMS,     RootDirectory + "c9.png"));
			push_back(CommodityCard(CATTLE,   RootDirectory + "c10.png"));
			push_back(CommodityCard(WHEAT,    RootDirectory + "c11.png"));
		}
		random_shuffle(begin(), end());
		leftDiscardPile.push_back(back());
		pop_back();
		rightDiscardPile.push_back(back());
		pop_back();

		drawPileEventBox.        signal_button_press_event().connect(sigc::mem_fun(*this, &CommodityCardDrawDeck::onDrawPileClicked));
		leftDiscardPileEventBox. signal_button_press_event().connect(sigc::mem_fun(*this, &CommodityCardDrawDeck::onLeftDiscardPileClicked));
		rightDiscardPileEventBox.signal_button_press_event().connect(sigc::mem_fun(*this, &CommodityCardDrawDeck::onRightDiscardPileClicked));

		drawPileEventBox.        modify_bg(Gtk::STATE_NORMAL, Gdk::Color("#4F4F4F"));
		leftDiscardPileEventBox. modify_bg(Gtk::STATE_NORMAL, Gdk::Color("#4F4F4F"));
		rightDiscardPileEventBox.modify_bg(Gtk::STATE_NORMAL, Gdk::Color("#4F4F4F"));

		drawPileEventBox.set_has_tooltip();
		leftDiscardPileEventBox.set_has_tooltip();
		rightDiscardPileEventBox.set_has_tooltip();
		drawPileEventBox.signal_query_tooltip().connect(sigc::mem_fun(*this, &CommodityCardDrawDeck::onDrawPileTooltip));
		leftDiscardPileEventBox.signal_query_tooltip().connect(sigc::mem_fun(*this, &CommodityCardDrawDeck::onLeftDiscardPileTooltip));
		rightDiscardPileEventBox.signal_query_tooltip().connect(sigc::mem_fun(*this, &CommodityCardDrawDeck::onRightDiscardPileTooltip));
		
		drawPileEventBox        .add(drawPileImage);
		leftDiscardPileEventBox .add(leftDiscardPileImage); 
		rightDiscardPileEventBox.add(rightDiscardPileImage);
		update();
		drawPileEventBox        .show_all();
		leftDiscardPileEventBox .show_all();
		rightDiscardPileEventBox.show_all();
		
	}

	void update() {
		if (!empty())
			drawPileImage.set(cardBackPixbuf);
		else
			drawPileImage.clear();
		if (!leftDiscardPile.empty())
			leftDiscardPileImage.set(leftDiscardPile.back());
		else
			leftDiscardPileImage.clear();
		if (!rightDiscardPile.empty())
			rightDiscardPileImage.set(rightDiscardPile.back());
		else
			rightDiscardPileImage.clear();
	}

	bool onDrawPileTooltip(int, int, bool, const Glib::RefPtr<Gtk::Tooltip>& tooltip) {
		if (empty())
			return false;
		ostringstream oss; 
		oss << size() << " card" << (size() != 1 ? "s" : "") << " left";
		tooltip->set_text(oss.str());
		return true;
	}

	bool onLeftDiscardPileTooltip(int, int, bool, const Glib::RefPtr<Gtk::Tooltip>& tooltip) {
		if (leftDiscardPile.empty())
			return false;
		Glib::RefPtr<Gdk::Pixbuf> icon = Gdk::Pixbuf::create(Gdk::COLORSPACE_RGB, true, 8, leftDiscardPile.front()->get_width(),
			leftDiscardPile.front()->get_height() + ((leftDiscardPile.empty() ? 0 : leftDiscardPile.size () - 1) * 23));
		icon->fill(00000000);
		Gtk::VBox* iconbox = Gtk::manage(new Gtk::VBox);
		for (auto i = 0; i < leftDiscardPile.size(); ++i) {
			leftDiscardPile[i]->composite(icon, 0, 23 * i, leftDiscardPile.front()->get_width(), leftDiscardPile.front()->get_height(), 0, 23 * i, 1, 1, Gdk::INTERP_HYPER, 255);
			Gtk::Image* tempimage = Gtk::manage(new Gtk::Image(leftDiscardPile[i]));
			tempimage->set_alignment(0.5, 0.0);
			iconbox->pack_start(*tempimage);
			if (i != leftDiscardPile.size() - 1)
				tempimage->set_size_request(-1, 23);
		}
		iconbox->set_border_width(5);
		iconbox->show_all();
		iconbox->set_size_request(icon->get_width() + 10, icon->get_height() + 10);
		
		tooltip->set_custom(*iconbox);
		return true; 
	}
		
	bool onRightDiscardPileTooltip(int, int, bool, const Glib::RefPtr<Gtk::Tooltip>& tooltip) {
		if (rightDiscardPile.empty())
			return false; 
		Glib::RefPtr<Gdk::Pixbuf> icon = Gdk::Pixbuf::create(Gdk::COLORSPACE_RGB, true, 8, rightDiscardPile.front()->get_width(),
			rightDiscardPile.front()->get_height() + ((rightDiscardPile.empty() ? 0 : rightDiscardPile.size () - 1) * 23));
		icon->fill(00000000);
		Gtk::VBox* iconbox = Gtk::manage(new Gtk::VBox);
		for (auto i = 0; i < rightDiscardPile.size(); ++i) {
			rightDiscardPile[i]->composite(icon, 0, 23 * i, rightDiscardPile.front()->get_width(), rightDiscardPile.front()->get_height(),  0, 23 * i, 1, 1, Gdk::INTERP_HYPER, 255);
			Gtk::Image* tempimage = Gtk::manage(new Gtk::Image(rightDiscardPile[i]));
			tempimage->set_alignment(0.5, 0.0);
			iconbox->pack_start(*tempimage);
			if (i != rightDiscardPile.size() - 1)
				tempimage->set_size_request(-1, 23);
		}
		iconbox->set_border_width(5);
		iconbox->show_all();
		iconbox->set_size_request(icon->get_width() + 10, icon->get_height() + 10);
		
		tooltip->set_custom(*iconbox);

		return true;
	}

	bool onDrawPileClicked(GdkEventButton* e) const {
		if (e->type != GDK_BUTTON_PRESS || e->button != 1)
			return false;
		drawPileClickedSignal.emit();
		return true;
	}
	
	bool onLeftDiscardPileClicked(GdkEventButton* e) const {
		if (e->type != GDK_BUTTON_PRESS || e->button != 1)
			return false;
		leftDiscardPileClickedSignal.emit();
		return true;
	}
	
	bool onRightDiscardPileClicked(GdkEventButton* e) const {
		if (e->type != GDK_BUTTON_PRESS || e->button != 1)
			return false;
		rightDiscardPileClickedSignal.emit();
		return true;
	}

	CommodityCard drawCard() {
		CommodityCard drawn = back();
		pop_back();
		update();
		return drawn;
	}

	CommodityCard drawFromLeftDiscard() {
		CommodityCard drawn = leftDiscardPile.back();
		leftDiscardPile.pop_back();
		if (leftDiscardPile.empty() && !empty()) {
			leftDiscardPile.push_back(drawCard());
		}
		update();
		return drawn;
	}

	CommodityCard drawFromRightDiscard() {
		CommodityCard drawn = rightDiscardPile.back();
		rightDiscardPile.pop_back();
		if (rightDiscardPile.empty() && !empty()) {
			rightDiscardPile.push_back(drawCard());
		}
		update();
		return drawn;
	}
};

Glib::RefPtr<Gdk::Pixbuf> CommodityCardDrawDeck::cardBackPixbuf;

class Boat
{
	Glib::RefPtr<Gdk::Pixbuf> _frontPixbuf;
	Glib::RefPtr<Gdk::Pixbuf> _backPixbuf;
	bool _faceUp;
	vector< pair<size_t, size_t> > _scores;

public:
	Boat(const string& front, const string& back, size_t type)
		:_faceUp(true), _frontPixbuf(Gdk::Pixbuf::create_from_file(front)), _backPixbuf(Gdk::Pixbuf::create_from_file(back))
	{
		setType(type);
	}

	void flipUp()   {
		_faceUp = true;
	}
	void flipDown() {
		_faceUp = false;
	}

	bool isFaceUp() const {return _faceUp;}

	Glib::RefPtr<Gdk::Pixbuf> getPixbuf() const {
		if (_faceUp)
			return _frontPixbuf;
		else
			return _backPixbuf;
	}

	void setType(size_t type) {
		switch (type) {
		case 2: //top
			_scores.push_back(make_pair(0, 0)); //dummy
			_scores.push_back(make_pair( 5,  1));
			_scores.push_back(make_pair(10,  6));
			_scores.push_back(make_pair(15, 11));
			break;
		case 1: //top
			_scores.push_back(make_pair(0, 0)); //dummy
			_scores.push_back(make_pair(2,  0)); 
			_scores.push_back(make_pair(4,  1));
			_scores.push_back(make_pair(6,  3));
			_scores.push_back(make_pair(8,  5));
			break;
		case 0: //top
			_scores.push_back(make_pair(0, 0)); //dummy
			_scores.push_back(make_pair( 2,  0)); 
			_scores.push_back(make_pair( 6,  1));
			_scores.push_back(make_pair(12,  7));
			_scores.push_back(make_pair(20, 15));
			break;
		}
	}

	size_t getScore(size_t amountPlayed) const {
		amountPlayed = min(amountPlayed, _scores.size() - 1);
		vector< pair<size_t, size_t> >::const_iterator it = _scores.begin() + amountPlayed;
		if (_faceUp)
			return it->first;
		if (!_faceUp)
			return it->second;
	}
};



class Highlighter
	:public Gtk::Image
{
	Glib::RefPtr<Gdk::Pixbuf> _childPixbuf;
	Glib::RefPtr<Gdk::Pixbuf> _withBorder;
public:
	void set(Glib::RefPtr<Gdk::Pixbuf>& p) {
		_childPixbuf = p->copy();
		_withBorder = p->copy();
		Glib::RefPtr<Gdk::Pixbuf> pixel = Gdk::Pixbuf::create(Gdk::COLORSPACE_RGB, true, 8, 1, 1);
		pixel->fill(0xFFFF00FF);
		for (auto x = 0; x < p->get_width(); ++x) {
			for (auto y = 0; y < p->get_height(); ++y) {
				if (x < 5 || p->get_width() - 5 < x || y < 5 || p->get_height() - 5 < y)
					pixel->composite(_withBorder, x, y, 1, 1, x, y, 1, 1, Gdk::INTERP_HYPER, 255);
			}
		}
		Gtk::Image::set(_childPixbuf);
	}
	void highlight(bool shouldHighlight = true) {
		if (shouldHighlight) {
		//	_border->composite(get_pixbuf(), 0, 0, get_pixbuf()->get_width(), get_pixbuf()->get_height(), 0, 0, 1, 1, Gdk::INTERP_HYPER, 255);
			Gtk::Image::set(_withBorder);
		}
		else
			Gtk::Image::set(_childPixbuf);
	}
};

class CommodityCardSelector
	:public Gtk::EventBox
{
	Glib::RefPtr<Gdk::Pixbuf> childPixbuf;
	
	bool _selected;
	bool _isValidChoice;
	
public:
	bool _isWildTile;
	Gtk::Image childImage;
	static Glib::RefPtr<Gdk::Pixbuf> border; //the blue "selection" border
	static Glib::RefPtr<Gdk::Pixbuf> yellowBorder; //the gold, dotted-line border that indicates a valid choice
	static Glib::RefPtr<Gdk::Pixbuf> wildTileBorderPixbuf;
	CommodityCardSelector()
		:_selected(false), _isValidChoice(false), _isWildTile(false)
	{
		add(childImage);
		show_all();
	}

	void setCard(const CommodityCard& card) {
		childPixbuf = card->copy();
		childImage.set(childPixbuf);
	}

	void setAsWildTile(bool shouldSet = true) {
		_isWildTile = shouldSet;
	}

	void select() {
		_selected = true;
		childImage.set(childPixbuf->copy());
		if (_isWildTile)
			wildTileBorderPixbuf->composite(childImage.get_pixbuf(), 0, 0, wildTileBorderPixbuf->get_width(), wildTileBorderPixbuf->get_height(), 0, 0, 1, 1, Gdk::INTERP_HYPER, 255);
		else
			border->composite(childImage.get_pixbuf(), 0, 0, CARD_WIDTH, CARD_HEIGHT, 0, 0, 1, 1, Gdk::INTERP_HYPER, 255);
		childImage.set(childImage.get_pixbuf());
	}
	void unselect() {
		_selected = false;
		childImage.set(childPixbuf);
	}

	void validate() { 
		_isValidChoice = true;
		if (_isWildTile)
			return;
		childImage.set(childPixbuf->copy());
		yellowBorder->composite(childImage.get_pixbuf(), 0, 0, CARD_WIDTH, CARD_HEIGHT, 0, 0, 1, 1, Gdk::INTERP_HYPER, 255);
		childImage.set(childImage.get_pixbuf());
	}

	void invalidate() {
		_isValidChoice = false;
		update();
	}

	bool isSelected()    const { return _selected;}
	bool isValidChoice() const { return _isValidChoice;}

	void update() {
		
		if (!_selected) {
			
			if (!_isValidChoice) 
				childImage.set(childPixbuf);
			else 
				validate();
			
			int x, y;
			get_pointer(x, y);
			if (0 < x && x < get_width() && 0 < y && y < get_height())
				childImage.set_alignment(0.0, 0.0);
			else
				childImage.set_alignment(0.0, 1.0);
		}
		else
			select();
	}

};

Glib::RefPtr<Gdk::Pixbuf> CommodityCardSelector::border;
Glib::RefPtr<Gdk::Pixbuf> CommodityCardSelector::yellowBorder;
Glib::RefPtr<Gdk::Pixbuf> CommodityCardSelector::wildTileBorderPixbuf;

class CardManager
{
	vector<Player*> players;
public:
	Player* currentPlayer;
	CommodityCardDrawDeck deck;
	Gtk::HBox drawDeckHBox;

	CommodityCard wildTileCard;

	vector <CommodityCard> choices; //human player only
	vector<CommodityCardSelector*> cardsInHandSelectors; //human player only
	
	vector <vector<Gtk::Image*> > cardsInHandImageVectors; //0 will be dummy, 
	Gtk::HBox cardsInHandMainBox;
	
	vector <vector<Gtk::Image*> > cardsInPlayImageVectors;
	Gtk::HBox cardsInPlayMainBox;

	Gtk::VBox rightSideVBox;
	
	Boat topBoat;
	Boat middleBoat;
	Boat bottomBoat;

	Gtk::Image selectedBoat;
	Gtk::Button confirmButton;
	Gtk::Button cancelShippingButton;
	Gtk::Label confirmButtonLabel;
	Gtk::Label cancelShippingButtonLabel;
	Gtk::Table boatAndButtonsTable;

	Gtk::Image cardsinhandTitleImage;
	Gtk::Image cardsinplayTitleImage;

	Glib::RefPtr<Gdk::GC> borderGC;
	
	sigc::signal <void, const string&> textSignal;
	sigc::signal <void> actionCompleteSignal;
	sigc::signal <void> updateBordersSignal;

	sigc::signal <void, const Player&, const string&, Gtk::HBox*, bool> historySignal;
	sigc::signal <void, const Player&> noActionTakenSignal;

	enum ShippingState {
		NONE,
		AWAITING_CHOICE,
		DISCARDING_FROM_HAND,
		DISCARDING_TO_PILE,
		PLAYING,
		SHIPPING_TOP,
		SHIPPING_MIDDLE,
		SHIPPING_BOTTOM,
		COMPUTER_TURN
	} actionState;

	CardManager() : 
	    cardsinhandTitleImage(RootDirectory + "en_mainJ.png"), 
		cardsinplayTitleImage(RootDirectory + "en_cartesposeesJ.png"), 
		topBoat   (RootDirectory + "nav21.png", RootDirectory + "nav20.png", 2),
		middleBoat(RootDirectory + "nav11.png", RootDirectory + "nav10.png", 1),
		bottomBoat(RootDirectory + "nav01.png", RootDirectory + "nav00.png", 0),
		actionState(NONE),
		borderGC(Gdk::GC::create()),
		wildTileCard(WILD, RootDirectory + "cwildt.png")
	{
		confirmButton.set_can_focus(false);
		cancelShippingButton.set_can_focus(false);
		confirmButton.set_relief(Gtk::RELIEF_NONE);
		cancelShippingButton.set_relief(Gtk::RELIEF_NONE);	
		confirmButtonLabel.set_markup("<span font_family = \"" + defaultFont + "\" size=\"9216\" foreground=\"#FAEBD7\" weight=\"600\">Confirm</span>");
		cancelShippingButtonLabel.set_markup("<span font_family = \"" + defaultFont + "\" size=\"9216\" foreground=\"#FAEBD7\" weight=\"600\">Cancel</span>");
		confirmButton.add(confirmButtonLabel);
		cancelShippingButton.add(cancelShippingButtonLabel);

		selectedBoat.set_alignment(0.0, 0.5);
		selectedBoat.set_size_request(203, -1);
		confirmButton.set_size_request(83, 25);
		cancelShippingButton.set_size_request(83, 25);

		boatAndButtonsTable.attach(selectedBoat, 0, 1, 0, 1, Gtk::SHRINK, Gtk::SHRINK);
		boatAndButtonsTable.attach(confirmButton, 1, 2, 0, 1, Gtk::SHRINK, Gtk::SHRINK, 0, 31);
		boatAndButtonsTable.attach(cancelShippingButton, 2, 3, 0, 1, Gtk::SHRINK, Gtk::SHRINK, 0, 31);
		
		confirmButton.signal_clicked().connect(sigc::mem_fun(*this, &CardManager::confirm));
		cancelShippingButton.signal_clicked().connect(sigc::mem_fun(*this, &CardManager::reset));
		
		drawDeckHBox.pack_start(deck.leftDiscardPileEventBox,  Gtk::PACK_SHRINK);
		drawDeckHBox.pack_start(deck.drawPileEventBox,         Gtk::PACK_SHRINK, 6);
		drawDeckHBox.pack_start(deck.rightDiscardPileEventBox, Gtk::PACK_SHRINK);
		
		deck.leftDiscardPileClickedSignal. connect(sigc::mem_fun(*this, &CardManager::onLeftDiscardPileClicked));
		deck.drawPileClickedSignal.        connect(sigc::mem_fun(*this, &CardManager::humanPlayerDrawsTwoCards));
		deck.rightDiscardPileClickedSignal.connect(sigc::mem_fun(*this, &CardManager::onRightDiscardPileClicked));
		
		cardsinhandTitleImage.set_alignment(0.0);
		cardsinplayTitleImage.set_alignment(0.0);
		rightSideVBox.pack_start(cardsinhandTitleImage, Gtk::PACK_SHRINK);
		rightSideVBox.pack_start(cardsInHandMainBox,    Gtk::PACK_EXPAND_WIDGET);
		rightSideVBox.pack_start(cardsinplayTitleImage, Gtk::PACK_SHRINK);
		rightSideVBox.pack_start(cardsInPlayMainBox,    Gtk::PACK_EXPAND_WIDGET);
		cardsInHandMainBox.   set_size_request(SHEET_WIDTH, CARD_HEIGHT + 12);
		cardsInPlayMainBox.   set_size_request(SHEET_WIDTH, CARD_HEIGHT);

		drawDeckHBox.signal_expose_event().connect(sigc::mem_fun(*this, &CardManager::onExpose));
		
	}

	void drawCardBorder(Gtk::EventBox& eventBox) {
		eventBox.get_parent_window()->draw_rectangle(borderGC, false, eventBox.get_allocation().get_x() - 1, eventBox.get_allocation().get_y() - 1, eventBox.get_width() + 2, eventBox.get_height() + 2);
	}

	bool onExpose (GdkEventExpose* e) {
		if (actionState == AWAITING_CHOICE) {
			drawCardBorder(deck.leftDiscardPileEventBox);
			drawCardBorder(deck.drawPileEventBox);
			drawCardBorder(deck.rightDiscardPileEventBox);
		}
		if (actionState == DISCARDING_TO_PILE) {
			drawCardBorder(deck.leftDiscardPileEventBox);
			drawCardBorder(deck.rightDiscardPileEventBox);
		}
		return true;
	}

	void setPlayersVector(const vector<Player*>& gameVector) {
		players = gameVector;
		cardsInHandImageVectors.resize(players.size());
		cardsInPlayImageVectors.resize(players.size());

		for (auto i = 0; i < players.size(); ++i) {
			players[i]->cardsInHand_HBox.show_all();
			players[i]->cardsInPlay_HBox.show_all();
		}

		cardsInHandMainBox.pack_start(players.front()->cardsInHand_HBox, Gtk::PACK_SHRINK);
		cardsInPlayMainBox.pack_start(players.front()->cardsInPlay_HBox, Gtk::PACK_SHRINK);

		currentPlayer = players.front();
	}

	size_t currentPlayerNumber() const {
		for (size_t i = 0; i < players.size(); ++i) {
			if (players[i] == currentPlayer)
				return i;
		}
		return players.size();
	}

	//when integrating into the board, functions will be the same, just have a "currentPlayerPtr"
	/*
	void playerDrawCard(int sourcePile) {
		cout << "draw two\n";
		return;
		//if (deck.size() % 2 == 0) {
		//	mainTable.get_window()->set_cursor(Gdk::Cursor(mainTable.get_display(), Gdk::Pixbuf::create_from_file(RootDirectory + "hand.png"), 0, 0));
		//}
		//else {
		//	mainTable.get_window()->set_cursor();
		//}
		switch (sourcePile) {
		case 0:
			playerHand.push_back(deck.drawFromLeftDiscard());
			break;
		case 1:
			playerHand.push_back(deck.drawCard());
			if (!deck.empty())
				playerHand.push_back(deck.drawCard());
			break;
		case 2:
			playerHand.push_back(deck.drawFromRightDiscard());
			break;
		default:
			cout << "No sourcePile selected (playerDrawCard)\n";
			exit(EXIT_FAILURE);
		}
		if (deck.empty()) 
			drawTwoSignal.disconnect();
		if (deck.leftDiscardPile.empty())
			drawLeftSignal.disconnect();
		if (deck.rightDiscardPile.empty())
			drawRightSignal.disconnect();

		sort(playerHand.begin(), playerHand.end(), lessThan);
		cardsInHandImages.push_back(Gtk::manage(new Gtk::Image));
		cardsInHandImages.back()->set_alignment(0.0, 0.5);
		Gtk::EventBox* tempEventBox = Gtk::manage(new Gtk::EventBox);
		tempEventBox->add(*cardsInHandImages.back());
		tempEventBox->modify_bg(Gtk::STATE_NORMAL, Gdk::Color("#4F4F4F"));
		tempEventBox->signal_enter_notify_event().connect(sigc::bind<Gtk::Image*>(sigc::mem_fun(*this, &CardManager::onMouseOverCardInHand), cardsInHandImages.back()));
		tempEventBox->signal_leave_notify_event().connect(sigc::bind<Gtk::Image*>(sigc::mem_fun(*this, &CardManager::onMouseOverCardInHand), cardsInHandImages.back()));
		cardsInHandBox.pack_start(*tempEventBox, Gtk::PACK_SHRINK);
		
		for (auto i = 0; i < playerHand.size(); ++i) {
			cardsInHandImages[i]->set_size_request(min(playerHand[i]->get_width(), 571  / int(playerHand.size())), -1);
			cardsInHandImages[i]->set(playerHand[i]);
			
		}
		update();
	}
	*/

	void playerGetsNewCard(CommodityCard& card) { //human player
		if (currentPlayer == players.front()) {  // if player is human 
			currentPlayer->cardsInHand.push_back(card);
			cardsInHandSelectors.push_back(Gtk::manage(new CommodityCardSelector));
			cardsInHandSelectors.back()->childImage.set_alignment(0.0, 1.0);
			cardsInHandSelectors.back()->modify_bg(Gtk::STATE_NORMAL, Gdk::Color("#4F4F4F"));
			cardsInHandSelectors.back()->signal_enter_notify_event().connect(sigc::bind<CommodityCardSelector*>(sigc::mem_fun(*this, &CardManager::onMouseOverCardInHand), cardsInHandSelectors.back()));
			cardsInHandSelectors.back()->signal_leave_notify_event().connect(sigc::bind<CommodityCardSelector*>(sigc::mem_fun(*this, &CardManager::onMouseOverCardInHand), cardsInHandSelectors.back()));
			cardsInHandSelectors.back()->signal_button_press_event().connect(sigc::bind(sigc::mem_fun(*this, &CardManager::submitCardAsChoice), currentPlayer->cardsInHand.size() - 1));  
			currentPlayer->cardsInHand_HBox.pack_start(*cardsInHandSelectors.back(), Gtk::PACK_SHRINK);
		}
		else { 
			currentPlayer->cardsInHand.push_back(card);
			cardsInHandImageVectors[currentPlayerNumber()].push_back(Gtk::manage(new Gtk::Image));
			cardsInHandImageVectors[currentPlayerNumber()].back()->set_alignment(0.0, 1.0);
			currentPlayer->cardsInHand_HBox.pack_start(*cardsInHandImageVectors[currentPlayerNumber()].back(), Gtk::PACK_SHRINK);
		}
		update();
	}

	void playerWinsTwoCards() {
		playerGetsNewCard(deck.drawCard());
		playerGetsNewCard(deck.drawCard());
	}

	void playerPutsNewCardInPlay(const CommodityCard& card) {
		if (!card.isWild()) {
			currentPlayer->cardsInPlay.push_back(card);
			cardsInPlayImageVectors[currentPlayerNumber()].push_back(Gtk::manage(new Gtk::Image));
			cardsInPlayImageVectors[currentPlayerNumber()].back()->set_alignment(0.0, 1.0);
			currentPlayer->cardsInPlay_HBox.pack_start(*cardsInPlayImageVectors[currentPlayerNumber()].back(), Gtk::PACK_SHRINK);
		}
		update();
	}

	void onWildCommodityTileClicked() {
		if (!shipping())
			return;
		if (!players.front()->hasWildCommodityTile())
			return;

		switch (actionState) {
		case SHIPPING_TOP:
			if (players.front()->wildCommodityTile.amount >=2) {
				addWildToChoices();
				addWildToChoices();
				players.front()->setWildCommodityActive(false); //will always be invalid for Top Boat shipping after choosing once, since only 3 wilds exist in game
			}
			break;
		case SHIPPING_MIDDLE:
			addWildToChoices();
			players.front()->setWildCommodityActive(players.front()->wildCommodityTile.amount >= 1 && choices.size() < 4);
			break;
		case SHIPPING_BOTTOM:
			addWildToChoices();
			players.front()->setWildCommodityActive(players.front()->wildCommodityTile.amount >= 1 && choices.size() < 4);
			break;
		}

	}

	void moveAllChoicesToInPlay() {
		for (auto i = 0; i < choices.size(); ++i)
			playerPutsNewCardInPlay(choices[i]);
		clearOutChoicesBox();
		update();
		actionState = NONE;
	}
	
	void startAction() {
		if (actionState != NONE)
			return;
		if (currentPlayer->cardsInHand.empty() && deck.empty() && deck.leftDiscardPile.empty() && deck.rightDiscardPile.empty() && !currentPlayer->hasWildCommodityTile()) {
			playerTakesNoAction();
		}
		else {
			actionState = AWAITING_CHOICE;  
			textSignal.emit("Draw two cards form the deck, draw one from either discard pile, play cards, or ship cards.");
			boatAndButtonsTable.show_all();
			confirmButton.hide();
			cancelShippingButton.hide();
			validateAll(); 
			updateBorders();
		}
	}

	void humanPlayerDrawsTwoCards() {
		if (actionState != AWAITING_CHOICE || deck.empty())
			return;
		Gtk::HBox* rightHBox = Gtk::manage(new Gtk::HBox(false, 2));
		string message;
		if (deck.size() >= 2) {
			rightHBox->pack_start(*Gtk::manage(new Gtk::Image(deck.cardBackPixbuf)), Gtk::PACK_SHRINK);
			rightHBox->pack_start(*Gtk::manage(new Gtk::Image(deck.cardBackPixbuf)), Gtk::PACK_SHRINK);
			message = "DRAWS TWO COMMODITY CARDS";
		}
		else if (deck.size() == 1) {
			rightHBox->pack_start(*Gtk::manage(new Gtk::Image(deck.cardBackPixbuf)), Gtk::PACK_SHRINK);
			message = "DRAWS ONE COMMODITY CARD";
		}
		historySignal.emit(*currentPlayer, message, rightHBox, false);

		playerGetsNewCard(deck.drawCard());
		
		if (!deck.empty()) {
			playerGetsNewCard(deck.drawCard());
			textSignal.emit("Choose a card to discard.");
			actionState = DISCARDING_FROM_HAND; 
			validateAll();
			updateBorders();
		}
		else {
			actionState = NONE; 
			updateBorders();
			invalidateAll();
			actionCompleteSignal.emit();
		}
	}
	void computerPlayerDrawsTwoCards() {
		Gtk::HBox* rightHBox = Gtk::manage(new Gtk::HBox(false, 2));
		string message;
		if (deck.size() >= 2) {
			rightHBox->pack_start(*Gtk::manage(new Gtk::Image(deck.cardBackPixbuf)), Gtk::PACK_SHRINK);
			rightHBox->pack_start(*Gtk::manage(new Gtk::Image(deck.cardBackPixbuf)), Gtk::PACK_SHRINK);
			message = "DRAWS TWO COMMODITY CARDS";
		}
		else if (deck.size() == 1) {
			rightHBox->pack_start(*Gtk::manage(new Gtk::Image(deck.cardBackPixbuf)), Gtk::PACK_SHRINK);
			message = "DRAWS ONE COMMODITY CARD";
		}
		historySignal.emit(*currentPlayer, message, rightHBox, false);
		if (!deck.empty())
			playerGetsNewCard(deck.drawCard());

		if (!deck.empty()) 
			playerGetsNewCard(deck.drawCard());
	}

	void onLeftDiscardPileClicked() {
		if (actionState == AWAITING_CHOICE) {
			if (deck.leftDiscardPile.empty())
				return;
			Gtk::HBox* rightHBox = Gtk::manage(new Gtk::HBox(false, 2));
			rightHBox->pack_start(*Gtk::manage(new Gtk::Image(deck.leftDiscardPile.back())), Gtk::PACK_SHRINK);
			historySignal.emit(*currentPlayer, "DRAWS FROM LEFT DISCARD PILE", rightHBox, false);
			playerGetsNewCard(deck.drawFromLeftDiscard());
			actionState = NONE; 
			updateBorders();
			invalidateAll();
			actionCompleteSignal.emit();
		}
		else if (actionState == DISCARDING_TO_PILE) {
			if (choices.empty())
				return;
			deck.leftDiscardPile.push_back(choices.front());
			Gtk::HBox* rightHBox = Gtk::manage(new Gtk::HBox(false, 2));
			rightHBox->pack_start(*Gtk::manage(new Gtk::Image(deck.leftDiscardPile.back())), Gtk::PACK_SHRINK);
			historySignal.emit(*currentPlayer, "DISCARDS TO LEFT DISCARD PILE", rightHBox, false);
			clearOutChoicesBox();
			actionState = NONE;
			updateBorders();
			invalidateAll();
			actionCompleteSignal.emit();
		}
		else
			return;
		update();
	}
	void onRightDiscardPileClicked() {
		if (actionState == AWAITING_CHOICE) {
			if (deck.rightDiscardPile.empty())
				return;
			Gtk::HBox* rightHBox = Gtk::manage(new Gtk::HBox(false, 2));
			rightHBox->pack_start(*Gtk::manage(new Gtk::Image(deck.rightDiscardPile.back())), Gtk::PACK_SHRINK);
			historySignal.emit(*currentPlayer, "DRAWS FROM RIGHT DISCARD PILE", rightHBox, false);
			playerGetsNewCard(deck.drawFromRightDiscard());
			actionState = NONE;
			updateBorders();
			invalidateAll();
			actionCompleteSignal.emit();
		}
		else if (actionState == DISCARDING_TO_PILE) {
			if (choices.empty())
				return;
			deck.rightDiscardPile.push_back(choices.front());
			Gtk::HBox* rightHBox = Gtk::manage(new Gtk::HBox(false, 2));
			rightHBox->pack_start(*Gtk::manage(new Gtk::Image(deck.rightDiscardPile.back())), Gtk::PACK_SHRINK);
			historySignal.emit(*currentPlayer, "DISCARDS TO RIGHT DISCARD PILE", rightHBox, false);
			clearOutChoicesBox();
			actionState = NONE; 
			updateBorders();
			invalidateAll();
			actionCompleteSignal.emit();
		}
		else
			return;
		update();
	}

	void computerPlayerDrawsFromDiscard(bool leftPile = true); //TODO: define
	void computerPlayerDiscards(size_t cardNumber, bool leftPile = true) {
		if (cardNumber >= currentPlayer->cardsInHand.size()) {
			cout << "computerPlayerDiscards: cardNumber " << cardNumber << " too large for Player " << currentPlayerNumber() << "'s hand size: " << currentPlayer->cardsInHand.size() << endl;
			exit(EXIT_FAILURE);
		}
		if (leftPile) {
			deck.leftDiscardPile.push_back(currentPlayer->cardsInHand[cardNumber]);
			currentPlayer->cardsInHand.pop_back();
			Gtk::HBox* rightHBox = Gtk::manage(new Gtk::HBox(false, 2));
			rightHBox->pack_start(*Gtk::manage(new Gtk::Image(deck.leftDiscardPile.back())), Gtk::PACK_SHRINK);
			historySignal.emit(*currentPlayer, "DISCARDS TO LEFT DISCARD PILE", rightHBox, false);
		}
		else {
			deck.rightDiscardPile.push_back(currentPlayer->cardsInHand[cardNumber]);
			Gtk::HBox* rightHBox = Gtk::manage(new Gtk::HBox(false, 2));
			rightHBox->pack_start(*Gtk::manage(new Gtk::Image(deck.rightDiscardPile.back())), Gtk::PACK_SHRINK);
			historySignal.emit(*currentPlayer, "DISCARDS TO RIGHT DISCARD PILE", rightHBox, false);
			currentPlayer->cardsInHand.pop_back();
		}
		update();
	}
	
	void clearOutChoicesBox() {
		for (int i = 0; i < choices.size(); ++i) {
			if (choices[i].isWild()) {
				choices.erase(choices.begin() + i);
				i = i - 1;
			}
			else {
				players.front()->cardsInHand_HBox.remove(*cardsInHandSelectors.back()); 
				cardsInHandSelectors.resize(cardsInHandSelectors.size() - 1);
			}
		}
		auto iter = players.front()->cardsInHand.begin();
		while (!choices.empty()) {
			if (*iter == choices.back())  {
				iter = players.front()->cardsInHand.erase(iter);
				choices.pop_back();
			}
			else
				++iter;
			if (iter == players.front()->cardsInHand.end())
				iter = players.front()->cardsInHand.begin();
		}
		for (auto i = 0; i < cardsInHandSelectors.size(); ++i) {
			cardsInHandSelectors[i]->unselect();
			cardsInHandSelectors[i]->setAsWildTile(false);
		}
		choices.clear();
		update();
	}

	void clearWildTilesFromCardsInHandSelectors() {
		for (auto i = players.front()->cardsInHand.begin(); i !=  players.front()->cardsInHand.end(); ) {
			if (i->isWild()) {
				i = players.front()->cardsInHand.erase(i);
				players.front()->cardsInHand_HBox.remove(*cardsInHandSelectors.back()); 
				cardsInHandSelectors.resize(cardsInHandSelectors.size() - 1);
			}
			else
				++i;
		}

		for (auto i = 0; i < cardsInHandSelectors.size(); ++i) {
			cardsInHandSelectors[i]->unselect();
			cardsInHandSelectors[i]->setAsWildTile(false);
		}
		update();
	}

	void reset() {
		clearWildTilesFromCardsInHandSelectors();
		for (auto i = 0; i < cardsInHandSelectors.size(); ++i) {
			cardsInHandSelectors[i]->unselect();
		}
		for (auto i = 0; i < choices.size(); ++i) {
			if (choices[i].isWild())
				++currentPlayer->wildCommodityTile.amount;
		}
		choices.clear();
		selectedBoat.clear();
		confirmButton.hide();
		cancelShippingButton.hide();
		actionState = AWAITING_CHOICE;
		validateAll();
		textSignal.emit("Draw two cards form the deck, draw one from either discard pile, play cards, or ship cards.");
		updateBorders();
		update();
	}
		
	void addSingleCardToChoices(size_t slot) {
		if (cardsInHandSelectors[slot]->isSelected())
			return;
		cardsInHandSelectors[slot]->select();
		cardsInHandSelectors[slot]->childImage.set_alignment(0.0, 0.0);
		choices.push_back(players.front()->cardsInHand[slot]); 
		updateBorders();
		update();
	}

	void addPairToChoices(size_t slot) {
		Commodity chosen = players.front()->cardsInHand[slot].commodity;
		addSingleCardToChoices(slot);
		for (auto i = 0; i < players.front()->cardsInHand.size(); ++i) {
			if (i == slot)
				continue;
			if (players.front()->cardsInHand[i].commodity == chosen) {
				addSingleCardToChoices(i);
				return;
			}
		}
		//TODO: check this line
		//meant to fire if we have no real card that matches a pair
		addWildToChoices();
	}

	void addWildToChoices() {
		playerGetsNewCard(wildTileCard);
		cardsInHandSelectors.back()->setAsWildTile();
		cardsInHandSelectors.back()->select();
		cardsInHandSelectors.back()->childImage.set_alignment(0.0, 0.0);
		choices.push_back(wildTileCard);
		--players.front()->wildCommodityTile.amount;
		players.front()->queue_draw();
		showConfirmAndCancelButtons();
		update();
	}

	bool onMouseOverCardInHand(GdkEventCrossing* e, CommodityCardSelector* selector) {
		if (e->type == GDK_ENTER_NOTIFY) {
			selector->childImage.set_alignment(0.0, 0.0);
		}
		else if (!selector->isSelected()) {
			selector->childImage.set_alignment(0.0, 1.0);
		}
		return true;
	}

	bool playerHasAtLeastOnePair() const {
		if (currentPlayer->wildCommodityTile.amount >= 2)
			return true;
		if (currentPlayer->wildCommodityTile.amount == 1 && currentPlayer->cardsInHand.size() >= 1) 
			return true;
		
		if (currentPlayer->cardsInHand.empty())
			return false;

		for (auto i = 0; i < currentPlayer->cardsInHand.size() - 1; ++i) {
			for (auto j = i + 1; j < currentPlayer->cardsInHand.size(); ++j) {
				if (currentPlayer->cardsInHand[i] == currentPlayer->cardsInHand[j]) 
					return true;
			}
		}
		return false;
	}

	bool playerHasPairOfThisType(const CommodityCard& c) const {
		if (!c.isWild() && currentPlayer->hasWildCommodityTile())
			return true;
		if (c.isWild() && !currentPlayer->cardsInHand.empty())
			return true;
		if (c.isWild() && currentPlayer->wildCommodityTile.amount >= 2)
			return true;
	
		size_t typeCount = 0;
		for (auto i = 0; i < currentPlayer->cardsInHand.size(); ++i) {
			if (currentPlayer->cardsInHand[i] == c)
				++typeCount;
			if (typeCount == 2)
				return true;
		}
		return false;
	}

	bool isValidChoiceForTopBoat(const CommodityCard& c) {
		if (!playerHasPairOfThisType(c))
			return false;
		if (choices.size() >= 6) //3 pairs already chosen
			return false;
		for (auto i = 0; i < choices.size(); ++i) {
			if (!choices[i].isWild() && choices[i] == c) //can't match a pair already chosen to ship 
				return false;
		}
		return true;
	}

	bool isValidChoiceForMiddleBoat(const CommodityCard& c) {
		if (choices.size() >= 4)
			return false;
		if (c.isWild())
			return true;
		for (auto i = 0; i < choices.size(); ++i) {
			if (choices[i] == c)
				return false;
		}
		return true; 
	}

	bool isValidChoiceForBottomBoat(const CommodityCard& c) {
		if (choicesHasOnlyWildsOrIsEmpty())
			return true;
		if (choices.size() >= 4)
			return false;
		if (c.isWild())
			return true;
		for (int i = 0; i < choices.size(); ++i) {
			if (choices[i].isWild())
				continue;
			if (choices[i] == c)
				return true;
			else
				return false;
		}
	}

	bool choicesHasOnlyWildsOrIsEmpty() {
		for (int i = 0; i < choices.size(); ++i) {
			if (!choices[i].isWild())
				return false;
		}
		return true;
	}

	bool shipping() const {
		return actionState == SHIPPING_TOP || actionState == SHIPPING_MIDDLE || actionState == SHIPPING_BOTTOM;
	}

	void showCancelButtonOnly() {
		confirmButton.remove();
		confirmButton.set_sensitive(false);
		confirmButton.show_all();
		cancelShippingButton.show_all();
	}

	void showConfirmAndCancelButtons() {
		if (!confirmButtonLabel.get_parent())
			confirmButton.add(confirmButtonLabel);

		confirmButton.set_sensitive(true);
		confirmButton.show_all();
		cancelShippingButton.show_all();
	}

	bool shipWithTop()    {
		if (actionState != AWAITING_CHOICE)
			return true;
		if (!playerHasAtLeastOnePair())
			return true;
		actionState = SHIPPING_TOP;
		textSignal.emit("Choose cards to ship");
		invalidateAll();
		for (auto i = 0; i < players.front()->cardsInHand.size(); ++i) {
			if (isValidChoiceForTopBoat(players.front()->cardsInHand[i]) && !cardsInHandSelectors[i]->isSelected()) 
				cardsInHandSelectors[i]->validate();
		}
		players.front()->setWildCommodityActive(players.front()->wildCommodityTile.amount >= 2);
		selectedBoat.set(topBoat.getPixbuf());
		updateBorders();
		showCancelButtonOnly();
		return true; 
	}

	bool shipWithMiddle() {
		if (actionState != AWAITING_CHOICE)
			return true;
		if (players.front()->cardsInHand.empty() && !players.front()->hasWildCommodityTile())
			return true;
		actionState = SHIPPING_MIDDLE;
		textSignal.emit("Choose cards to ship");
		players.front()->setWildCommodityActive(players.front()->hasWildCommodityTile());
		selectedBoat.set(middleBoat.getPixbuf());
		updateBorders();
		showCancelButtonOnly();
		return true;
	}

	bool shipWithBottom() {
		if (actionState != AWAITING_CHOICE)
			return true;
		if (players.front()->cardsInHand.empty() && !players.front()->hasWildCommodityTile())
			return true;
		actionState = SHIPPING_BOTTOM;
		textSignal.emit("Choose cards to ship");
		players.front()->setWildCommodityActive(players.front()->hasWildCommodityTile());
		selectedBoat.set(bottomBoat.getPixbuf());
		updateBorders();
		showCancelButtonOnly();
		return true; 
	}

	void computerPlayerShips(vector<CommodityCard>& cards, size_t ship) {
		//TODO: AI here?
		//maybe just a "helper function" that determines best score, but do the actually shipping from Game
		//top == 0
		//middle == 1
		//bottom == 2
	}

	bool submitCardAsChoice(GdkEventButton* e, size_t slot) {
		if (e->type != GDK_BUTTON_PRESS || e->button != 1 || cardsInHandSelectors[slot]->isSelected())
			return false;
		if (actionState == DISCARDING_FROM_HAND) {
			addSingleCardToChoices(slot);
			textSignal.emit("Choose pile to discard into.");
			actionState = DISCARDING_TO_PILE; 
			invalidateAll();
			return true;
		}
		if (actionState == AWAITING_CHOICE) //etc
		{
			addSingleCardToChoices(slot);
			actionState = PLAYING;
			showConfirmAndCancelButtons();
			validateAll();
			return true;
		}
		if (actionState == PLAYING && choices.size() < 2) {
			addSingleCardToChoices(slot);
			invalidateAll();
		}

		if (shipping()) 
		{
			invalidateAll();

			switch(actionState) {
			case SHIPPING_TOP:
				if (isValidChoiceForTopBoat(players.front()->cardsInHand[slot])) {
					addPairToChoices(slot);
				}
				for (auto i = 0; i < players.front()->cardsInHand.size(); ++i) {
					if (isValidChoiceForTopBoat(players.front()->cardsInHand[i]) && !cardsInHandSelectors[i]->isSelected())
						cardsInHandSelectors[i]->validate();
				}
				players.front()->setWildCommodityActive(players.front()->wildCommodityTile.amount >= 2 && choices.size() < 6);
				break;
			case SHIPPING_MIDDLE:
				if (isValidChoiceForMiddleBoat(players.front()->cardsInHand[slot])) { 
					addSingleCardToChoices(slot);
				}
				for (auto i = 0; i < players.front()->cardsInHand.size(); ++i) {
					if (isValidChoiceForMiddleBoat(players.front()->cardsInHand[i]) && !cardsInHandSelectors[i]->isSelected())
						cardsInHandSelectors[i]->validate();
				}
				players.front()->setWildCommodityActive(players.front()->wildCommodityTile.amount >= 1 && choices.size() < 4);
				break;
			case SHIPPING_BOTTOM:
				if (isValidChoiceForBottomBoat(players.front()->cardsInHand[slot])) {
					addSingleCardToChoices(slot);
				}
				for (auto i = 0; i < players.front()->cardsInHand.size(); ++i) {
					if (isValidChoiceForBottomBoat(players.front()->cardsInHand[i]) && !cardsInHandSelectors[i]->isSelected())
						cardsInHandSelectors[i]->validate();
				}
				players.front()->setWildCommodityActive(players.front()->wildCommodityTile.amount >= 1 && choices.size() < 4);
				break;
			}
			if (!choices.empty()) {
				showConfirmAndCancelButtons();
			}
			return true;
		}
		return false;
	}

	void confirm() {
		if (actionState == PLAYING) {
			int count = choices.size();
			int historySignalDrawCount = 0;
			while (count > 0 && !deck.empty()) {
				playerGetsNewCard(deck.drawCard());
				--count;
				++historySignalDrawCount;
			}
			selectedBoat.clear();
			confirmButton.hide();
			cancelShippingButton.hide();
			updateBorders();
			Gtk::HBox* rightHBox = Gtk::manage(new Gtk::HBox(false, 2));
			for (int i = 0; i < choices.size(); ++i) {
				rightHBox->pack_start(*Gtk::manage(new Gtk::Image(choices[i])), Gtk::PACK_SHRINK);
			}
			string message;
			if (choices.size() == 2)
				message = "PUTS TWO COMMODITY CARDS DIRECTLY IN PLAY";
			else 
				message = "PUTS ONE COMMODITY CARD DIRECTLY IN PLAY";
			historySignal.emit(*currentPlayer, message, rightHBox, false);
			
			rightHBox = Gtk::manage(new Gtk::HBox(false, 2));
			if (historySignalDrawCount == 2) {
				rightHBox->pack_start(*Gtk::manage(new Gtk::Image(CommodityCardDrawDeck::cardBackPixbuf)), Gtk::PACK_SHRINK);
				rightHBox->pack_start(*Gtk::manage(new Gtk::Image(CommodityCardDrawDeck::cardBackPixbuf)), Gtk::PACK_SHRINK);
				message = "DRAWS TWO COMMODITY CARDS"; 
			}
			else {
				rightHBox->pack_start(*Gtk::manage(new Gtk::Image(CommodityCardDrawDeck::cardBackPixbuf)), Gtk::PACK_SHRINK);
				message = "DRAWS ONE COMMODITY CARD";
			}
			if (historySignalDrawCount > 0)
				historySignal.emit(*currentPlayer, message, rightHBox, false);
			moveAllChoicesToInPlay();
			invalidateAll();
			actionCompleteSignal.emit(); //check this change won't screw everything up
		}
		else if (shipping()) {
			Gtk::HBox* rightHBox = Gtk::manage(new Gtk::HBox(false, 2));
			Gtk::Image* shipImage = Gtk::manage(new Gtk::Image);
			rightHBox->pack_start(*shipImage, Gtk::PACK_SHRINK);
			for (int i = 0; i < choices.size(); ++i) {
				rightHBox->pack_start(*Gtk::manage(new Gtk::Image(choices[i])), Gtk::PACK_SHRINK);
			}

			switch(actionState) {
			case SHIPPING_TOP:
				players.front()->earnPoints(topBoat.getScore(choices.size() / 2));
				shipImage->set(topBoat.getPixbuf());
				historySignal.emit(*currentPlayer, "SHIPS COMMODITIES (" + to_string(long long(topBoat.getScore(choices.size() / 2))) + " VP)", rightHBox, true);
				topBoat.flipDown();
				break;
			case SHIPPING_MIDDLE:
				players.front()->earnPoints(middleBoat.getScore(choices.size()));
				shipImage->set(middleBoat.getPixbuf());
				historySignal.emit(*currentPlayer, "SHIPS COMMODITIES (" + to_string(long long(middleBoat.getScore(choices.size()))) + " VP)", rightHBox, true);
				middleBoat.flipDown();
				break;
			case SHIPPING_BOTTOM:
				players.front()->earnPoints(bottomBoat.getScore(choices.size()));
				shipImage->set(bottomBoat.getPixbuf());
				historySignal.emit(*currentPlayer, "SHIPS COMMODITIES (" + to_string(long long(bottomBoat.getScore(choices.size()))) + " VP)", rightHBox, true);
				bottomBoat.flipDown();
				break;
			}
			invalidateAll();
			updateBorders();
			selectedBoat.clear();
			confirmButton.hide();
			cancelShippingButton.hide();
			clearWildTilesFromCardsInHandSelectors();
			moveAllChoicesToInPlay();
			actionCompleteSignal.emit();
		}
	}

	void playerTakesNoAction() {
		actionState = NONE; 
		updateBorders();
		invalidateAll();
		noActionTakenSignal.emit(*currentPlayer);
		actionCompleteSignal.emit();
	}

	void nextPlayer() {
		if (currentPlayer != players.back())
			++currentPlayer;
		else
			currentPlayer = players.front();
	}

	void resetAllBoats() {
		topBoat.flipUp();
		middleBoat.flipUp();
		bottomBoat.flipUp();
	}

	void update() {
		if (players.empty())
			return;
		double scale = 1;
		sort(players.front()->cardsInHand.begin(), players.front()->cardsInHand.end(), lessThan); //computer cards are face down -- don't need sorting

		for (auto i = 0; i < players.front()->cardsInHand.size(); ++i) {
			cardsInHandSelectors[i]->set_size_request(min(CARD_WIDTH, SHEET_WIDTH / players.front()->cardsInHand.size()), players.front()->cardsInHand[i]->get_height() + 12); 
			//cardsInHandSelectors[i]->              set_size_request(min(playerHand[i]->get_width(), SHEET_WIDTH / int(playerHand.size())), playerHand[i]->get_height() + 10); 
			cardsInHandSelectors[i]->setCard(players.front()->cardsInHand[i]);
			cardsInHandSelectors[i]->update();
		}

		if (!cardsInHandSelectors.empty()) {
			cardsInHandSelectors.back()->set_size_request(cardsInHandSelectors.back()->childImage.get_pixbuf()->get_width(), CARD_HEIGHT + 12);
		}
		else
			players.front()->cardsInHand_HBox.set_size_request(SHEET_WIDTH, CARD_HEIGHT + 12);

		for (auto i = 1; i < players.size(); ++i) {
			for (auto j = 0; j < players[i]->cardsInHand.size(); ++j) {
				cardsInHandImageVectors[i][j]->set_size_request(min(CARD_WIDTH, SHEET_WIDTH / players[i]->cardsInHand.size()), CARD_HEIGHT + 12); 
				cardsInHandImageVectors[i][j]->set(CommodityCardDrawDeck::cardBackPixbuf); //opponents' cards are face down 
			}
			if (!cardsInHandImageVectors[i].empty()) {
				cardsInHandImageVectors[i].back()->set_size_request(CARD_WIDTH, CARD_HEIGHT + 12);
			}
			else
				players[i]->cardsInHand_HBox.set_size_request(SHEET_WIDTH, CARD_HEIGHT + 12);
		}
				
		for (auto i = 0; i < players.size(); ++i) {
			sort(players[i]->cardsInPlay.begin(), players[i]->cardsInPlay.end(), lessThan);
			for (auto j = 0; j < players[i]->cardsInPlay.size(); ++j) {
				cardsInPlayImageVectors[i][j]->set_size_request(min(CARD_WIDTH, SHEET_WIDTH / players[i]->cardsInPlay.size()), CARD_HEIGHT + 10); 
				cardsInPlayImageVectors[i][j]->set(players[i]->cardsInPlay[j]);
			}
			if (!cardsInPlayImageVectors[i].empty())
				cardsInPlayImageVectors[i].back()->set_size_request(CARD_WIDTH, CARD_HEIGHT);
			else
				players[i]->cardsInPlay_HBox.set_size_request(SHEET_WIDTH, CARD_HEIGHT);
		}
		
		deck.update();
		rightSideVBox.show_all();
	}

	void updateBorders() {
		updateBordersSignal.emit();
	}

	void validateAll() {
		for (auto i = 0; i < cardsInHandSelectors.size(); ++i) {
			if (!cardsInHandSelectors[i]->isSelected())
				cardsInHandSelectors[i]->validate();
		}
		if (shipping()) {
			if (actionState == SHIPPING_TOP) {
				if (choices.size() < 6)
					players.front()->setWildCommodityActive(players.front()->wildCommodityTile.amount >= 2);
			}
			else
				players.front()->setWildCommodityActive(players.front()->wildCommodityTile.amount >= 1);
			players.front()->queue_draw();
		}
	}


	void invalidateAll() {
		for (auto i = 0; i < cardsInHandSelectors.size(); ++i) {
			cardsInHandSelectors[i]->invalidate();
		}
		players.front()->setWildCommodityActive(false);
		players.front()->queue_draw();
	}



};

//Notebook of Players

class TimerLight
	: public Gtk::Image
{
	Glib::RefPtr<Gdk::Pixbuf> _greenPix;
	Glib::RefPtr<Gdk::Pixbuf> _redPix;
	Glib::RefPtr<Gdk::Pixbuf> _halfPix;
public:
	TimerLight(bool isStarter = false)
	{
		_greenPix = Gdk::Pixbuf::create_from_file(RootDirectory + (isStarter ? "edtG1.png" : "edtG.png" ));
		_redPix   = Gdk::Pixbuf::create_from_file(RootDirectory + "edtR.png");
		_halfPix  = Gdk::Pixbuf::create_from_file(RootDirectory + "edtV.png");
		//if (isStarter) 
		//	_greenPix = _greenPix->rotate_simple(Gdk::PIXBUF_ROTATE_COUNTERCLOCKWISE);
		set(_greenPix);
	}
	void setAsStarter() {
		_greenPix = Gdk::Pixbuf::create_from_file(RootDirectory + "edtG1.png");
		//_greenPix = _greenPix->rotate_simple(Gdk::PIXBUF_ROTATE_COUNTERCLOCKWISE);
	}
	void turnGreen()    { set(_greenPix); }
	void turnRed()      { set(_redPix)  ; }
	void turnHalf()     { set(_halfPix) ; }

};

class Timer
	:public Gtk::HBox
{
	size_t _step;
	size_t _partialStep; //half lights when waiting for player input, and on game log showing number of pegs moved
	size_t _stepMax;
	size_t _round;
	size_t _quarter;
	Gtk::Table _table;
	Gtk::TextView _quarterText;
	Gtk::TextView _roundText;
	Gtk::HBox _textHBox;
	vector< vector< TimerLight* > > _timerLights;

public:
	sigc::signal<void> roundEndSignal;
	sigc::signal<void> quarterEndSignal;
	sigc::signal<void> gameEndSignal;
	sigc::signal<void, Glib::RefPtr<Gdk::Pixbuf> > timerStepSignal;
	Timer()
		: _step(1), _partialStep(0), _round(1), _quarter(1)
	{
		Pango::FontDescription font;
		font.set_family(defaultFont);
		font.set_size(PANGO_SCALE * 8);
		font.set_weight(Pango::WEIGHT_SEMIBOLD);
		modify_font(font);
		modify_text(Gtk::STATE_NORMAL, Gdk::Color("#FAEBD7"));
		modify_base(Gtk::STATE_NORMAL, Gdk::Color("#4F4F4F"));
		 
		_timerLights.resize(4);

		_quarterText.set_editable(false);
		_quarterText.set_cursor_visible(false);
		_quarterText.modify_font(font);
		_quarterText.modify_text(Gtk::STATE_NORMAL, Gdk::Color("#FAEBD7"));
		_quarterText.modify_base(Gtk::STATE_NORMAL, Gdk::Color("#4F4F4F"));
		_roundText.set_editable(false);
		_roundText.set_cursor_visible(false);
		_roundText.modify_font(font);
		_roundText.modify_text(Gtk::STATE_NORMAL, Gdk::Color("#FAEBD7"));
		_roundText.modify_base(Gtk::STATE_NORMAL, Gdk::Color("#4F4F4F"));
		_quarterText << "QUARTER " << _quarter << "/4";
		_roundText << "ROUND "   << _round   << "/4";
		_textHBox.pack_start(_quarterText, Gtk::PACK_SHRINK, 5);
		_textHBox.pack_start(_roundText, Gtk::PACK_SHRINK, 5);

		pack_start(_textHBox);
		pack_start(_table);
		_quarterText.set_pixels_above_lines(30);
		_roundText.set_pixels_above_lines(30);
				
		show_all();
		
	}

	void setNumberOfPlayers(size_t n) {
		if (n < 2)
			n = 2;
		if (n > 4)
			n = 4; 
		switch(n) {
		case 2:
			_stepMax = 11;
			break;
		case 3:
			_stepMax = 16;
			break;
		case 4:
			_stepMax = 21;
			break;
		}
		_table.resize(4, _stepMax); //horizontal
		//_table.resize(_stepMax, 4); //vertical
		
		for (auto i = 0; i < 4; ++i) {
			for (auto j = 0; j < _stepMax; ++j) {
				_timerLights[i].push_back(Gtk::manage(new TimerLight(j == 0)));
				_table.attach(*_timerLights[i][j], j, j + 1, i, i + 1, Gtk::SHRINK, Gtk::SHRINK, 1, 1);
				//_table.attach(*_timerLights[i][j], i, i + 1, _stepMax - (j + 1), _stepMax - j, Gtk::SHRINK, Gtk::SHRINK, 1, 1);
			}
		}
		_timerLights[0][0]->turnRed();
	}

	void partialAdvance(size_t amount) {
		_partialStep = amount;
		update();
		timerStepSignal.emit(Gdk::Pixbuf::create(Glib::RefPtr<Gdk::Drawable>(_table.get_snapshot()), 0, 0, _table.get_width(), _table.get_height()));
	}

	void cancelAdvance() {
		_partialStep = 0;
		update();
	}

	void advance(size_t amount) {
		
		_step +=amount; //_step += _partialStep; 
		_partialStep = 0;

		while (_step > _stepMax) {
			++_round;
			_step -= _stepMax;
			roundEndSignal.emit();
		}
		
		while (_round > 4) {
			++_quarter;
			_round -= 4;
			quarterEndSignal.emit();
			if (_quarter > 4) {
				gameEndSignal.emit();
				setAllAsRed();
				return;
			}
		}
		update();
	}

	void update() { //TODO: this could be way faster and more efficient
		            //maybe a "set all as green" once new quarter begins
		_quarterText.get_buffer()->set_text("");
		_roundText.get_buffer()->set_text("");
		_quarterText << "QUARTER " << _quarter << "/4";
		_roundText << "ROUND "   << _round   << "/4";
		size_t floatCount = _partialStep;
		for (auto i = 0; i < _timerLights.size(); ++i) {
			for (auto j = 0; j < _timerLights[i].size(); ++j) {
				if (i < _round - 1)
					_timerLights[i][j]->turnRed();
				else if (i == _round - 1 && j <  _step)
					_timerLights[i][j]->turnRed();
				else if (floatCount > 0) {
					_timerLights[i][j]->turnHalf();
					--floatCount;
				}
				else
					_timerLights[i][j]->turnGreen();
			}
		}
	}

	void setAllAsRed() {
		for (auto i = 0; i < _timerLights.size(); ++i) {
			for (auto j = 0; j < _timerLights[i].size(); ++j) {
				_timerLights[i][j]->turnRed();
			}
		}
	}

	size_t getStep()    const { return _step;}
	size_t getRound()   const { return _round;}
	size_t getQuarter() const { return _quarter;}

};

class Demand
	:public Glib::RefPtr<Gdk::Pixbuf>
{
	DemandType type;
public:
	Demand(DemandType _type)
		: type(_type)
	{ 
		switch(type) {
		case BREAD:
			Glib::RefPtr<Gdk::Pixbuf>::operator=(Gdk::Pixbuf::create_from_file(RootDirectory + "ddp2.png"));
			break;
		case FIRE:
			Glib::RefPtr<Gdk::Pixbuf>::operator=(Gdk::Pixbuf::create_from_file(RootDirectory + "ddp0.png"));
			break;
		case HELMET:
			Glib::RefPtr<Gdk::Pixbuf>::operator=(Gdk::Pixbuf::create_from_file(RootDirectory + "ddp1.png"));
			break;
		default:
			cout << "error " << endl;
		} 
	//catch (Glib::Error& e) {
	//	cout << e.what() << endl;
	//}
	}
	DemandType getType() const { return type; }
	
};

class DemandDisplay
	:public vector<Demand>
{
	Gtk::Image image1;
	Gtk::Image image2;
	Gtk::Image image3;
	vector<Gtk::Image*> images;
	vector<Demand> deck;
	Glib::RefPtr<Gdk::Pixbuf> emptyPixbuf;
public:
	Gtk::Table table;
	DemandDisplay()
		: emptyPixbuf(Gdk::Pixbuf::create_from_file(RootDirectory + "ddpvide.png"))
	     //image1(emptyPixbuf),
		 //image2(emptyPixbuf),
		 //image3(emptyPixbuf)
	{
		for (auto i = 0; i < 5; ++i) {
			deck.push_back(Demand(BREAD));
			deck.push_back(Demand(FIRE));
			deck.push_back(Demand(HELMET));
		}
		random_shuffle(deck.begin(), deck.end());
		
		table.attach(*Gtk::manage(new Gtk::Image(Gdk::Pixbuf::create_from_file(RootDirectory + "ddpdos.png"))), 0, 1, 0, 1, Gtk::SHRINK, Gtk::SHRINK);
		
		images.push_back(&image1);
		images.push_back(&image2);
		images.push_back(&image3);
		for (auto i = 0; i < images.size(); ++i) {
			table.attach(*images[i], i + 1, i + 2, 0, 1, Gtk::SHRINK, Gtk::SHRINK);
			images[i]->set(emptyPixbuf);
		}
		table.set_size_request((CARD_WIDTH * 3) + 12, -1);
		table.set_col_spacings(18);
		table.show_all();
	}

	void nextRound() {
		if (size() < 3) {
			push_back(deck.back());
			deck.pop_back();
		}
		else
			clear();
		for (auto i = 0; i < images.size(); ++i) {
			if (i < size())
				images[i]->set(at(i));
			else
				images[i]->set(emptyPixbuf);
		}
	}

	size_t getNumberOfNeeded(DemandType type) const {
		size_t result = 0;
		for (auto i = 0; i < size(); ++i) {
			if (at(i).getType() == type)
				++result;
		}
		return result;
	}

	multiset<DemandType> getDemandsList() const {
		multiset<DemandType> result;
		result.insert(at(0).getType());
		result.insert(at(1).getType());
		result.insert(at(2).getType());
		return result;
	}

	Glib::RefPtr<Gdk::Pixbuf> getDemandPixbuf(size_t number) const {
		if (number < 1 || 3 < number) {
			cout << "No demand numbered " << number << endl;
			exit(EXIT_FAILURE);
		}
		return images[number - 1]->get_pixbuf();
	}

};

class History
	:public Gtk::Window
{
public:
	Gtk::ScrolledWindow scrolledWindow;
	Gtk::EventBox mainEventBox;
	Gtk::VBox mainVBox;
	Glib::RefPtr<Gdk::Pixbuf> timerPixbuf;
	size_t forumTileSize;
	Pango::FontDescription font;
	Pango::FontDescription nameFont;

	Gtk::ScrolledWindow miniScroll;
	Gtk::Image miniImage;

	vector <Glib::RefPtr<Gdk::Pixbuf> > actionPixbufs;
	
	History()
		:forumTileSize(30)
	{
		//mainVBox.signal_add().connect(sigc::mem_fun(*this, &History::onAdd), false);
		//scrolledWindow.signal_add().connect(sigc::mem_fun(*this, &History::onAdd), false);
		actionPixbufs.push_back(Gdk::Pixbuf::create_from_file(RootDirectory + "action_0.png"));
		actionPixbufs.push_back(Gdk::Pixbuf::create_from_file(RootDirectory + "action_1.png"));
		actionPixbufs.push_back(Gdk::Pixbuf::create_from_file(RootDirectory + "action_2.png"));
		actionPixbufs.push_back(Gdk::Pixbuf::create_from_file(RootDirectory + "action_3.png"));
		actionPixbufs.push_back(Gdk::Pixbuf::create_from_file(RootDirectory + "action_4.png"));
		actionPixbufs.push_back(Gdk::Pixbuf::create_from_file(RootDirectory + "action_5.png"));
		
		font.set_family(defaultFont);
		font.set_size(PANGO_SCALE * 8);
		nameFont = font;
		nameFont.set_weight(Pango::WEIGHT_BOLD);
		modify_bg(Gtk::STATE_NORMAL, Gdk::Color("#4F4F4F"));
		mainEventBox.modify_bg(Gtk::STATE_NORMAL, Gdk::Color("#4F4F4F"));
		scrolledWindow.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_ALWAYS);
		scrolledWindow.set_shadow_type(Gtk::SHADOW_NONE);
		mainEventBox.add(mainVBox);
		scrolledWindow.add(mainEventBox);
		add(scrolledWindow);
		set_title("Game log");
		set_icon_from_file(RootDirectory + "icon.png");
		set_border_width(0);
		scrolledWindow.show_all();
		//set_decorated(false);
		//miniScroll.add(miniImage);
		//miniScroll.show_all();
		
		
	}



	Gtk::Label* createLabel() {
		Gtk::Label* label = Gtk::manage(new Gtk::Label);
		label->set_padding(2, 5);
		label->modify_fg(Gtk::STATE_NORMAL, Gdk::Color("#FAEBD7"));
		label->modify_font(font);
		//font, etc
		return label;
	}

	void addEntry(Gtk::HBox* rightHbox, const string& name = "") {
		Gtk::Frame* leftFrame = Gtk::manage(new Gtk::Frame);
		Gtk::Frame* rightFrame = Gtk::manage(new Gtk::Frame);
		Gtk::EventBox *leftEventBox = Gtk::manage(new Gtk::EventBox);
		Gtk::EventBox *rightEventBox = Gtk::manage(new Gtk::EventBox);
		leftEventBox->modify_bg(Gtk::STATE_NORMAL, Gdk::Color("#4F4F4F"));
		rightEventBox->modify_bg(Gtk::STATE_NORMAL, Gdk::Color("#4F4F4F"));

		leftFrame-> set_shadow_type(Gtk::SHADOW_IN);
		rightFrame->set_shadow_type(Gtk::SHADOW_IN);

		if (!name.empty()) {
			Gtk::Label* leftLabel = createLabel();
			leftLabel->set_text(name);
			leftLabel->modify_fg(leftLabel->get_state(), Gdk::Color("#FAEBD7"));
			leftLabel->modify_font(nameFont);
			leftFrame->add(*leftLabel);
		}
		rightFrame->add(*rightHbox);
		rightHbox->set_border_width(3);

		Gtk::HBox *mainHBox = Gtk::manage(new Gtk::HBox);

		leftEventBox->add(*leftFrame);
		rightEventBox->add(*rightFrame);
		leftEventBox->set_size_request(100, -1);
		rightEventBox->set_size_request(500, -1);
		mainHBox->pack_end(*rightEventBox, Gtk::PACK_SHRINK); 
		mainHBox->pack_end(*leftEventBox, Gtk::PACK_SHRINK); 

		mainVBox.pack_end(*mainHBox, Gtk::PACK_SHRINK);
				
		mainVBox.show_all();
	}

	void addEntry(const Player& player, Gtk::HBox* rightHbox) {
		addEntry(rightHbox, player.getString());
	}

	void printMessage(const Player& player, const string& message) {
		Gtk::HBox* rightHbox = Gtk::manage(new Gtk::HBox);
		Gtk::Label* rightLabel = createLabel();
		rightLabel->set_text(message);
		rightHbox->pack_start(*rightLabel, Gtk::PACK_SHRINK);
		addEntry(player, rightHbox);
	}

	void startGame() {
		Gtk::HBox* rightHbox = Gtk::manage(new Gtk::HBox);
		addEntry(rightHbox);
		Gtk::Label* rightLabel = createLabel();
		rightLabel->set_text("GAME START");
		rightHbox->pack_start(*rightLabel, Gtk::PACK_SHRINK);
		printQuarter(1);
		printRound(1);
	}

	void printQuarter(unsigned int quarter) {
		Gtk::HBox* rightHbox = Gtk::manage(new Gtk::HBox);
		Gtk::Label* rightLabel = createLabel();
		rightHbox->pack_start(*rightLabel, Gtk::PACK_SHRINK);
		ostringstream oss;
		oss << "QUARTER #" << quarter;
		rightLabel->set_text(oss.str());
		addEntry(rightHbox);
	}

	void printRound(unsigned int round) {
		Gtk::HBox* rightHbox = Gtk::manage(new Gtk::HBox);
		Gtk::Label* rightLabel = createLabel();
		rightHbox->pack_start(*rightLabel, Gtk::PACK_SHRINK);
		ostringstream oss;
		oss << "ROUND #" << round;
		rightLabel->set_text(oss.str());
		addEntry(rightHbox);
	}

	void printDemands(const DemandDisplay& display) {
		Gtk::HBox* rightHbox = Gtk::manage(new Gtk::HBox);
		rightHbox->pack_start(*Gtk::manage(new Gtk::Image(display.getDemandPixbuf(1)->scale_simple(30, 30, Gdk::INTERP_HYPER))), Gtk::PACK_SHRINK);
		rightHbox->pack_start(*Gtk::manage(new Gtk::Image(display.getDemandPixbuf(2)->scale_simple(30, 30, Gdk::INTERP_HYPER))), Gtk::PACK_SHRINK);
		rightHbox->pack_start(*Gtk::manage(new Gtk::Image(display.getDemandPixbuf(3)->scale_simple(30, 30, Gdk::INTERP_HYPER))), Gtk::PACK_SHRINK);
		addEntry(rightHbox);
	}

	void printTimer(const Player& player, size_t action) {
		Gtk::HBox* rightHbox = Gtk::manage(new Gtk::HBox);
		rightHbox->pack_start(*Gtk::manage(new Gtk::Image(timerPixbuf)), Gtk::PackOptions::PACK_SHRINK);
		rightHbox->pack_end(*Gtk::manage(new Gtk::Image(actionPixbufs[action])), Gtk::PackOptions::PACK_SHRINK);
		addEntry(player, rightHbox);
		//miniImage.set(Gdk::Pixbuf::create(Glib::RefPtr<Gdk::Drawable> (mainVBox.get_snapshot()), 0, 0, mainVBox.get_width(), mainVBox.get_height()));
	}

	void receiveTimerSnapshot(Glib::RefPtr<Gdk::Pixbuf> pixbuf) {
		timerPixbuf = pixbuf->scale_simple(pixbuf->get_width() * .75, pixbuf->get_height() * .75, Gdk::INTERP_HYPER);
	}

	void printSeaportAction(const Player& player, const string& message, Gtk::HBox* cardBox, bool hasShip = false) {
		vector<Gtk::Widget*> v = cardBox->get_children();
		cardBox->set_spacing(4);
		for (int i = 0; i < v.size(); ++i) {
			Gtk::Image* img = dynamic_cast<Gtk::Image*>(v[i]);
			if (i == 0 && hasShip)
				img->set(img->get_pixbuf()->scale_simple(65, 48, Gdk::INTERP_HYPER));
			else
				img->set(img->get_pixbuf()->scale_simple(31, 48, Gdk::INTERP_HYPER));
		}
		
		Gtk::HBox* rightHbox = Gtk::manage(new Gtk::HBox(false, 4));
		Gtk::Label* rightLabel = createLabel();
		rightLabel->set_text(message);
		rightHbox->pack_start(*rightLabel, Gtk::PACK_SHRINK);
		rightHbox->pack_start(*cardBox);

		addEntry(player, rightHbox);
	}

	void printNoShippingTaken(const Player& player) {
		printMessage(player, "NO SEAPORT ACTION POSSIBLE");
	}

	void printForumAction(const Player& player, const Glib::RefPtr<Gdk::Pixbuf> tile) {
		Gtk::HBox* rightHbox = Gtk::manage(new Gtk::HBox);
		Gtk::Label* rightLabel = createLabel();
		rightLabel->set_text("DRAWS A FORUM TILE");
		rightHbox->pack_start(*rightLabel, Gtk::PACK_SHRINK);
		rightHbox->pack_start(*Gtk::manage(new Gtk::Image(tile)), Gtk::PACK_SHRINK);
		addEntry(player, rightHbox);
	}

	void printMilitaryAction(const Player& player, const string& message, const Tile* tile = NULL) {
		Gtk::HBox* rightHbox = Gtk::manage(new Gtk::HBox);
		Gtk::Label* rightLabel = createLabel();
		rightHbox->pack_start(*rightLabel, Gtk::PACK_SHRINK);
		rightLabel->set_text(message);
		if (tile) {
			rightHbox->pack_start(*Gtk::manage(new Gtk::Image((*tile))), Gtk::PACK_SHRINK);
		}
		addEntry(player, rightHbox);
	}

	void printSenateAction(const Player& player, size_t points) {
		Gtk::HBox* rightHbox = Gtk::manage(new Gtk::HBox);
		Gtk::Label* rightLabel = createLabel();
		rightHbox->pack_start(*rightLabel, Gtk::PACK_SHRINK);
		if (points > 0) {
			ostringstream oss;
			oss << "SENATE ACTION, LEVEL " << points << " REACHED (" << points << " VP)";
			rightLabel->set_text(oss.str());
		}
		else {
			rightLabel->set_text("SENATE ACTION, ALREADY AT FINAL LEVEL (0 VP)");
		}
		addEntry(player, rightHbox);
	}

	void printTrajanTakenAction(const Player& player, size_t slot, Glib::RefPtr<Gdk::Pixbuf> pixbuf) {
		Gtk::HBox* rightHbox = Gtk::manage(new Gtk::HBox);
		Gtk::Label* rightLabel = createLabel();
		string message = "PLACES A TRAJAN TILE ON ";
		switch (slot) {
		case 0: message.append("'I'");   break;
		case 1: message.append("'II'");  break;
		case 2: message.append("'III'"); break;
		case 3: message.append("'IV'");  break;
		case 4: message.append("'V'");   break;
		case 5: message.append("'VI'");  break;
		default: 
			cout << "Slot too high. Parameter passed: " << slot << endl;
			exit(EXIT_FAILURE);
		}
		rightLabel->set_text(message);
		rightHbox->pack_start(*rightLabel, Gtk::PACK_SHRINK);
		rightHbox->pack_start(*Gtk::manage(new Gtk::Image(pixbuf->scale_simple(48, 48, Gdk::INTERP_HYPER))), Gtk::PACK_SHRINK);
		addEntry(player, rightHbox);
	}

	void printTrajanWon(const Player& player, Glib::RefPtr<Gdk::Pixbuf> pixbuf, const string& message) {
		Gtk::HBox* rightHbox = Gtk::manage(new Gtk::HBox);
		Gtk::Label* rightLabel = createLabel();
		rightLabel->set_text(message);
		rightHbox->pack_start(*Gtk::manage(new Gtk::Image(pixbuf->scale_simple(48, 48, Gdk::INTERP_HYPER))), Gtk::PACK_SHRINK);
		rightHbox->pack_start(*rightLabel, Gtk::PACK_SHRINK);
		addEntry(player, rightHbox);
	}

	void printArchMoved(const Player& player, size_t slot) {
		Gtk::HBox* rightHbox = Gtk::manage(new Gtk::HBox);
		Gtk::Label* rightLabel = createLabel();
		string message = "ARCH OF TRAJAN MOVES ";
		switch (slot) {
		case 0: message.append("TO 'I'");   break;
		case 1: message.append("TO 'II'");  break;
		case 2: message.append("TO 'III'"); break;
		case 3: message.append("TO 'IV'");  break;
		case 4: message.append("TO 'V'");   break;
		case 5: message.append("TO 'VI'");  break;
		case 6: message.append("OFF BOARD"); break;
		default: 
			cout << "Slot too high. Parameter passed: " << slot << endl;
			exit(EXIT_FAILURE);
		}
		rightLabel->set_text(message);
		rightHbox->pack_start(*rightLabel, Gtk::PACK_SHRINK);
		addEntry(player, rightHbox);
	}

	void printConstructionAction(const Player& player, const string& message, Glib::RefPtr<Gdk::Pixbuf> pixbuf) {
		Gtk::HBox* rightHbox = Gtk::manage(new Gtk::HBox);
		Gtk::Label* rightLabel = createLabel();
		rightLabel->set_text(message);
		rightHbox->pack_start(*rightLabel, Gtk::PACK_SHRINK);
		if (pixbuf) {
			rightHbox->pack_start(*Gtk::manage(new Gtk::Image(pixbuf)), Gtk::PACK_SHRINK, 2);
		}
		addEntry(player, rightHbox);
	}

	void printExtraAction (const Player& player, Glib::RefPtr<Gdk::Pixbuf> pixbuf, bool plusTwo = false) {
		Gtk::HBox* rightHbox = Gtk::manage(new Gtk::HBox);
		Gtk::Label* rightLabel = createLabel();
		rightLabel->set_text("SPENDS EXTRA ACTION TILE");
		rightHbox->pack_start(*rightLabel, Gtk::PACK_SHRINK);
		rightHbox->pack_start(*Gtk::manage(new Gtk::Image(pixbuf)), Gtk::PACK_SHRINK, 2);
		if (plusTwo) {
			Gtk::Label* rightLabel2 = createLabel();
			rightLabel2->set_text("(+2 ACTIONS)");
			rightHbox->pack_start(*rightLabel2, Gtk::PACK_SHRINK, 2);
		}
		addEntry(player, rightHbox);
	}

	void printPlusTwoChoice(const Player& player, Glib::RefPtr<Gdk::Pixbuf> pixbuf) {
		Gtk::HBox* rightHbox = Gtk::manage(new Gtk::HBox);
		Gtk::Label* rightLabel = createLabel();
		rightLabel->set_text("PLACES '+2' MARKER >>");
		rightHbox->pack_start(*rightLabel, Gtk::PACK_SHRINK);
		rightHbox->pack_start(*Gtk::manage(new Gtk::Image(pixbuf)), Gtk::PACK_SHRINK, 2);
		addEntry(player, rightHbox);
	}

	void printDemandsMet(const Player& player, vector<Glib::RefPtr<Gdk::Pixbuf> >pixbufs) {
		Gtk::HBox* rightHbox = Gtk::manage(new Gtk::HBox(false, 2));
		Gtk::Label* rightLabel = createLabel();
		string message = "MEETING THE PEOPLE'S DEMANDS: ";
		switch (pixbufs.size()) {
		case 3:
			message.append("(PERFECT)");
			break;
		case 2:
			message.append("(-4 VP)");
			break;
		case 1:
			message.append("(-9 VP)");
			break;
		case 0:
			message.append("(-15 VP)");
			break;
		}

		rightLabel->set_text(message);
		rightHbox->pack_start(*rightLabel, Gtk::PACK_SHRINK);

		for (int i = 0; i < pixbufs.size(); ++i)
			rightHbox->pack_start(*Gtk::manage(new Gtk::Image(pixbufs[i]->scale_simple(FORUM_TILE_WIDTH, FORUM_TILE_HEIGHT, Gdk::INTERP_HYPER))), Gtk::PACK_SHRINK);
		
		addEntry(player, rightHbox);
	}
	
	void printSenateResults(std::map<double, Player*> results) {
		Gtk::VBox* mainVBox = Gtk::manage(new Gtk::VBox());
		Gtk::Label* header = createLabel();
		header->set_text("BALANCE OF POWER IN THE SENATE");
		
		Gtk::Table* table = Gtk::manage(new Gtk::Table());
		table->set_border_width(0);
		int row = 0;
		for (auto i = results.rbegin(); i != results.rend(); ++i) {
			table->attach(*createVoteResultRow(*i).first, 0, 1, row, row + 1);
			table->attach(*createVoteResultRow(*i).second, 1, 2, row, row + 1);
			++row;
		}
		
		Gtk::Frame* mainFrame = Gtk::manage(new Gtk::Frame());
		mainFrame->set_shadow_type(Gtk::SHADOW_IN);
		mainFrame->add(*table);
		mainFrame->set_border_width(4);
		
		Gtk::HBox* tableBox = Gtk::manage(new Gtk::HBox());
		tableBox->pack_start(*mainFrame, Gtk::PACK_SHRINK);

		mainVBox->pack_start(*header);
		mainVBox->pack_start(*tableBox, Gtk::PACK_SHRINK);

		Gtk::HBox* box = Gtk::manage(new Gtk::HBox());
		box->pack_start(*mainVBox, Gtk::PACK_SHRINK);
		addEntry(box);
	}

    pair<Gtk::Frame*, Gtk::Frame*> createVoteResultRow(pair<const double, Player*>& entry) {
	
		Gtk::HBox* rightHBox = Gtk::manage(new Gtk::HBox);
		Gtk::Frame* leftFrame = Gtk::manage(new Gtk::Frame);
		Gtk::Frame* rightFrame = Gtk::manage(new Gtk::Frame);

		leftFrame->set_shadow_type(Gtk::SHADOW_IN);
		rightFrame->set_shadow_type(Gtk::SHADOW_IN);
		Gtk::Label* nameLabel = createLabel();
		nameLabel->set_text(entry.second->getString());
		leftFrame->add(*nameLabel);

		int votes = int(floor(entry.first * 10)) % 10;
		
		Gtk::Label* rightLabel = createLabel();
		rightLabel->set_text(to_string(long long(votes)) + " VOTES" + (entry.second->senateTiles.empty() ? "" : " + " ));
		rightHBox->pack_start(*rightLabel, Gtk::PACK_SHRINK);
		for (int i = 0; i < entry.second->senateTiles.size(); ++i) {
			rightHBox->pack_start(*Gtk::manage(new Gtk::Image(entry.second->senateTiles[i].pixbuf)), Gtk::PACK_SHRINK);
		}
		rightFrame->add(*rightHBox);
		
		return make_pair<Gtk::Frame*, Gtk::Frame*>(leftFrame, rightFrame);
	}

	void printSenateCardChoices(const Player& firstPlace, const Player& secondPlace) {
		Gtk::VBox* left = Gtk::manage(new Gtk::VBox());
		Gtk::VBox* right = Gtk::manage(new Gtk::VBox());
		left->set_border_width(5);
		right->set_border_width(5);

		Gtk::Label* leftLabel = createLabel();
		Gtk::Label* rightLabel = createLabel();
		leftLabel->set_text(firstPlace.getString());
		rightLabel->set_text(secondPlace.getString());

		left->pack_start(*Gtk::manage(new Gtk::Image(firstPlace.senateCards.back().getPixbuf()->scale_simple(34, 60, Gdk::INTERP_HYPER))), Gtk::PACK_SHRINK);
		left->pack_start(*leftLabel, Gtk::PACK_SHRINK);
		right->pack_start(*Gtk::manage(new Gtk::Image(secondPlace.senateCards.back().getPixbuf()->scale_simple(34, 60, Gdk::INTERP_HYPER))), Gtk::PACK_SHRINK);
		right->pack_start(*rightLabel, Gtk::PACK_SHRINK);
		Gtk::HBox* box = Gtk::manage(new Gtk::HBox(false, 5));
		box->pack_start(*left, Gtk::PACK_SHRINK, 5);
		box->pack_start(*right, Gtk::PACK_SHRINK, 5);
		addEntry(box);
	}

	void addTestEntry() {
		Gtk::Frame *leftFrame  = Gtk::manage(new Gtk::Frame);
		Gtk::Frame *rightFrame = Gtk::manage(new Gtk::Frame);
		Gtk::EventBox *leftEventBox = Gtk::manage(new Gtk::EventBox);
		Gtk::EventBox *rightEventBox = Gtk::manage(new Gtk::EventBox);
		leftEventBox->modify_bg(Gtk::STATE_NORMAL , Gdk::Color("#4F4F4F"));
		rightEventBox->modify_bg(Gtk::STATE_NORMAL , Gdk::Color("#4F4F4F"));

		leftFrame-> set_shadow_type(Gtk::SHADOW_IN);
		rightFrame->set_shadow_type(Gtk::SHADOW_IN);

		Gtk::Label *leftLabel = Gtk::manage(new Gtk::Label);

		Gtk::Label *rightLabel = Gtk::manage(new Gtk::Label);

		
		leftLabel->modify_fg(leftLabel->get_state(), Gdk::Color("#FAEBD7"));
		leftFrame->add(*leftLabel);

		Gtk::HBox *rightHBox = Gtk::manage(new Gtk::HBox);
		rightFrame->add(*rightHBox);
	
		Gtk::HBox *mainHBox = Gtk::manage(new Gtk::HBox);
		
		leftEventBox->add(*leftFrame);
		rightEventBox->add(*rightFrame);
		leftEventBox->set_size_request(100, -1);
		rightEventBox->set_size_request(600, -1);
		mainHBox->pack_end(*rightEventBox, Gtk::PACK_SHRINK); 
		mainHBox->pack_end(*leftEventBox, Gtk::PACK_SHRINK); 

		mainVBox.pack_end(*mainHBox, Gtk::PACK_SHRINK);
		
		switch(rand() % 5) {
		case 0:
			leftLabel->set_text("Blue");

			break;

		case 1:
			leftLabel->set_text("Blue");

			break;
		case 2:

			break;
		case 3:
			leftLabel->set_text("Red");
			
			break;
		case 4:
			leftLabel->set_text("Red");


			break;
		}
		time_t now;
		time(&now);
		char* timeChar = ctime(&now);

		leftLabel->set_text(leftLabel->get_text() + "\n" + string(timeChar));
		mainVBox.show_all();
	}
};

class NumberLabel
	:public Gtk::Label
{
	int _value;
	
	
public:
	static Pango::FontDescription font;

	NumberLabel()
		:_value(0)
	{
		modify_fg(Gtk::STATE_NORMAL, Gdk::Color("#FAEBD7"));
		modify_font(font);
		update();
	}

	void setValue(int value) {
		_value = value;
		 update();
	}

	int getValue() const {return _value;}

	void update() {
		set_text(to_string(long long (_value)));
	}

	void operator=(int value) {
		setValue(value);
	}
};

Pango::FontDescription NumberLabel::font;


class ControlButton
	:public Gtk::EventBox
{
	Gtk::Label _label;
public:
	ControlButton()
	{
		Pango::FontDescription font;
		font.set_family(defaultFont);
		font.set_size(PANGO_SCALE * 12);
		font.set_weight(Pango::WEIGHT_SEMIBOLD);
		_label.modify_font(font);
		modify_bg(Gtk::STATE_NORMAL, Gdk::Color("#4F4F4f"));
		add(_label);
		_label.modify_fg(Gtk::STATE_NORMAL, Gdk::Color("#FAEBD7"));
		signal_enter_notify_event().connect(sigc::mem_fun(*this, &ControlButton::onMouseOver));
		signal_leave_notify_event().connect(sigc::mem_fun(*this, &ControlButton::onMouseLeave));
	}

	void setLabel(const string& s) {
		_label.set_markup(s);
	}

	bool onMouseOver(GdkEventCrossing* e) {
		_label.modify_fg(Gtk::STATE_NORMAL, Gdk::Color("#FF001F"));
		return true;
	}
	bool onMouseLeave(GdkEventCrossing* e) {
		_label.modify_fg(Gtk::STATE_NORMAL, Gdk::Color("#FAEBD7"));
		return true;
	}
};

class SimulatedGame;


class Game
	:public Gtk::Window
{
	Pango::FontDescription mainFont;
	Pango::FontDescription scoreFont;
	Gtk::Image logoImage;
	Gtk::TextView messageText;
	Gtk::Button passButton;
	Gtk::Label  passButtonLabel;
	Gtk::Button endTurnButton; //only needed to pass on extra actions
	Gtk::Label  endTurnButtonLabel; 

	Gtk::Table scoresTable;
	vector<Gtk::Label*> scoreLabels; //emit to/from this

	Gtk::VBox drawDeckVBox;
	Gtk::VBox playerVBox;
	Gtk::VBox choicesVBox;

	Gtk::Table mainTable;
	//can use references for member objects' members
	
	const CommodityCardDrawDeck& drawdeck;
	CardManager cardManager;
	Viewer viewer;
	Timer timer;
	bool endOfRound;
	bool endOfQuarter;
	bool endOfGame;

	bool extraActionPrompted;
	bool extraActionUsedThisTurn;
	size_t extraActionsRemaining;
	bool constructionFinished;

	Gtk::EventBox board;
	Gtk::Image backgroundImage;
	Glib::RefPtr<Gdk::GC> borderGC; 

	Hotzone trajanTileZone1;
	Hotzone trajanTileZone2;
	Hotzone trajanTileZone3;
	Hotzone trajanTileZone4;
	Hotzone trajanTileZone5;
	Hotzone trajanTileZone6;
	TrajanTileDeck trajanTileDeck;

	Hotzone topBoatZone;
	Hotzone middleBoatZone;
	Hotzone bottomBoatZone;

	Gtk::HBox shippingHBox;
	
	vector<Hotzone> forumZones;
	vector<Hotzone> constructionZones;
	Hotzone constructionCampZone;
	
	Gtk::Image senateTitleImage;
	Gtk::VBox senateCardsVBox;
	SenateCardDeck senateCardDeck;
	vector<const SenateCard*> senateCards;
	Hotzone senateCardLeftZone;
	Hotzone senateCardRightZone;
	
	DemandDisplay demandDisplay;

	DebugWindow debug;

	Player& darkbluePlayer;
	Player& redPlayer;
	Player& greenPlayer;
	Player& brownPlayer;
	Player& humanPlayer;
	vector<Player*> players;
	Player* currentPlayer;
	vector < vector <NumberLabel*> > subscores;

	ForumTileDeck forumTileDeck;
	vector<const ForumTile*>& extraActionDeck;

	vector<const ForumTile*> forum; //use NULL pointers for blanks

	ConstructionTileDeck constructionTileDeck;
	vector< vector <PlayerColor> > constructionField;
	vector< vector <Coordinate> >  constructionFieldAnchors;
	vector <size_t> constructionCamp; //eg, constructionCitizens[RED] = 3 for red to have 3 builders
	vector <Coordinate> constructionCampAnchors;

	vector <Glib::RefPtr <Gdk::Pixbuf> > numeralPixbufs;
	
	enum Phase {
		MOVE_PEGS = -1,
		SEAPORT,
		FORUM,
		MILITARY,
		SENATE,
		TRAJAN,
		CONSTRUCTION,
		CHOOSE_PLACE_PLUS_TWO,
		CHOOSE_SENATE_CARD,
		COMPUTER_TURN
	} currentPhase;

	Continent continent;
	
	Glib::RefPtr<Gdk::Pixbuf> generalOff;
	Glib::RefPtr<Gdk::Pixbuf> generalOn;
	Glib::RefPtr<Gdk::Pixbuf> legionnaireOff;
	Glib::RefPtr<Gdk::Pixbuf> legionnaireOn;

	vector< vector< PlayerColor > > senate;
	vector< vector< Coordinate > > senateAnchors;

	Gtk::Alignment alignment;
	
	Gtk::VBox controlBox;
	ControlButton scoringControlButton;
	ControlButton historyControlButton;
	
	History history;

	enum subscoreName {
		BEFORE_BONUS,
		CARDS_IN_HAND,
		WORK_CAMP,
		LEGION_CAMP,
		TRAJAN_TILES,
		CONSTR_BONUS,
		SENATE_TILES,
		TOTAL_SCORE
	};

	Gtk::Window scoringWindow;
	Gtk::Table subScoringTable;

	SimulatedGame* simGamePtr;
	
public:
	friend class SenateCard;
	friend class SimulatedGame;
	Game()
		:logoImage(RootDirectory + "logo_trj.png"),
		 backgroundImage(Gdk::Pixbuf::create_from_file(RootDirectory + "board.png", BOARD_WIDTH * SCALE, BOARD_HEIGHT * SCALE, true)),
		 trajanTileZone1(TRAJAN_ANCHOR_1, TRAJAN_TILE_WIDTH, TRAJAN_TILE_HEIGHT),
		 trajanTileZone2(TRAJAN_ANCHOR_2, TRAJAN_TILE_WIDTH, TRAJAN_TILE_HEIGHT),
		 trajanTileZone3(TRAJAN_ANCHOR_3, TRAJAN_TILE_WIDTH, TRAJAN_TILE_HEIGHT),
		 trajanTileZone4(TRAJAN_ANCHOR_4, TRAJAN_TILE_WIDTH, TRAJAN_TILE_HEIGHT),
		 trajanTileZone5(TRAJAN_ANCHOR_5, TRAJAN_TILE_WIDTH, TRAJAN_TILE_HEIGHT),
		 trajanTileZone6(TRAJAN_ANCHOR_6, TRAJAN_TILE_WIDTH, TRAJAN_TILE_HEIGHT),
		 topBoatZone   (   TOP_BOAT_ANCHOR, BOAT_WIDTH, BOAT_HEIGHT),
		 middleBoatZone(MIDDLE_BOAT_ANCHOR, BOAT_WIDTH, BOAT_HEIGHT),
		 bottomBoatZone(BOTTOM_BOAT_ANCHOR, BOAT_WIDTH, BOAT_HEIGHT),
		 senateCardLeftZone(LEFT_SENATE_CARD_ANCHOR, SENATE_CARD_WIDTH, SENATE_CARD_HEIGHT),
		 senateCardRightZone(RIGHT_SENATE_CARD_ANCHOR, SENATE_CARD_WIDTH, SENATE_CARD_HEIGHT),
		 constructionCampZone(Coordinate(312 * SCALE, 500 * SCALE), 40 * SCALE, 40 * SCALE),
	     drawdeck(cardManager.deck),
		 darkbluePlayer (viewer.darkbluePlayer),
		 redPlayer      (viewer.redPlayer),
		 greenPlayer    (viewer.greenPlayer),
		 brownPlayer    (viewer.brownPlayer),
		 humanPlayer(viewer.darkbluePlayer),
		 extraActionDeck(forumTileDeck.extraActionDeck),
		 currentPhase(COMPUTER_TURN),
		 endOfRound(false),
		 endOfQuarter(false),
		 endOfGame(false),
		 extraActionUsedThisTurn (false),
		 extraActionPrompted(false),
		 extraActionsRemaining (0),
		 constructionFinished(true), 
		 constructionField(20),
		 generalOn     (Gdk::Pixbuf::create_from_file(RootDirectory + "deplG1.png",     40 * SCALE, 40 * SCALE, true)),
		 generalOff    (Gdk::Pixbuf::create_from_file(RootDirectory + "deplG1over.png", 40 * SCALE, 40 * SCALE, true)),
		 legionnaireOn (Gdk::Pixbuf::create_from_file(RootDirectory + "deplP1.png",     40 * SCALE, 40 * SCALE, true)),
		 legionnaireOff(Gdk::Pixbuf::create_from_file(RootDirectory + "deplP1over.png", 40 * SCALE, 40 * SCALE, true)),
		 simGamePtr(NULL)
	{
		set_icon_from_file(RootDirectory + "icon.png");
		set_title("Trajan v0.1");
		
		board.add(backgroundImage);
		board.set_border_width(1);
		backgroundImage.set_alignment(0.5, 1.0);
		
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 3; ++j) {
				forumZones.push_back(Hotzone((Coordinate ((TOP_LEFT_FORUM_ANCHOR.first + (FORUM_STEP_RIGHT * i)), (TOP_LEFT_FORUM_ANCHOR.second + (FORUM_STEP_DOWN * j)))), 
					                           FORUM_TILE_WIDTH, FORUM_TILE_HEIGHT));
			}
		}

		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 5; ++j) {
				constructionZones.push_back(Hotzone(Coordinate((TOP_LEFT_CONSTRUCTION_ANCHOR.first + (CONSTRUCTION_TILE_STEP_RIGHT * j)), (TOP_LEFT_CONSTRUCTION_ANCHOR.second + (CONSTRUCTION_TILE_STEP_DOWN * i))), CONSTRUCTION_TILE_WIDTH, CONSTRUCTION_TILE_HEIGHT));
			}
		}

		constructionCampAnchors.push_back(Coordinate((322 +  0) * SCALE, (490 +  0) * SCALE));
		constructionCampAnchors.push_back(Coordinate((322 + 24) * SCALE, (490 +  0) * SCALE));
		constructionCampAnchors.push_back(Coordinate((322 +  0) * SCALE, (490 - 32) * SCALE));
		constructionCampAnchors.push_back(Coordinate((322 + 24) * SCALE, (490 - 32) * SCALE));

		constructionFieldAnchors.resize(constructionField.size());
		for (auto i = 0; i < constructionField.size(); ++i) {
			constructionFieldAnchors[i].push_back(Coordinate(((435 + (CONSTRUCTION_TILE_STEP_RIGHT * (i % 5))) * SCALE), ((325 + (CONSTRUCTION_TILE_STEP_DOWN * (i / 5))) * SCALE)));
			while (constructionFieldAnchors[i].size() < 4) {
				constructionFieldAnchors[i].push_back(constructionFieldAnchors[i].back());
			}
			constructionFieldAnchors[i][1].first  += 15 * SCALE;
			constructionFieldAnchors[i][2].second -= 24 * SCALE;
			constructionFieldAnchors[i][3].first  += 15 * SCALE;
			constructionFieldAnchors[i][3].second -= 24 * SCALE;
		}

		senateAnchors.resize(8);
		senateAnchors[0].push_back(Coordinate( 98 * SCALE, 844 * SCALE));
		senateAnchors[1].push_back(Coordinate(172 * SCALE, 844 * SCALE));
		senateAnchors[2].push_back(Coordinate(221 * SCALE, 844 * SCALE));
		senateAnchors[3].push_back(Coordinate(270 * SCALE, 844 * SCALE));
		senateAnchors[4].push_back(Coordinate(320 * SCALE, 844 * SCALE));
		senateAnchors[5].push_back(Coordinate(370 * SCALE, 844 * SCALE));
		senateAnchors[6].push_back(Coordinate(419 * SCALE, 844 * SCALE));
		senateAnchors[7].push_back(Coordinate(468 * SCALE, 844 * SCALE));

		for (auto i = 0; i < senateAnchors.size(); ++i) {
			while (senateAnchors[i].size() < 4) {
				senateAnchors[i].push_back(senateAnchors[i].back());
				senateAnchors[i].back().second -= 9 * SCALE;
			}
		}
		
		players.push_back(&darkbluePlayer);
		players.push_back(&redPlayer);
		players.push_back(&greenPlayer);
		players.push_back(&brownPlayer);
				
		mainFont.set_size(PANGO_SCALE * 12);
		mainFont.set_family(defaultFont);
		mainFont.set_weight(Pango::WEIGHT_SEMIBOLD);
		scoreFont = mainFont;
		scoreFont.set_size(PANGO_SCALE * 10);

		//get number of players, etc
		Gtk::MessageDialog numberOfPlayersDialog(*this, "Number of players?", false, Gtk::MESSAGE_OTHER, Gtk::ButtonsType::BUTTONS_NONE, true);
		numberOfPlayersDialog.set_icon_from_file(RootDirectory + "icon.png");
		numberOfPlayersDialog.add_action_widget(*new Gtk::Button("2"), 2);
		numberOfPlayersDialog.add_action_widget(*new Gtk::Button("3"), 3);
		numberOfPlayersDialog.add_action_widget(*new Gtk::Button("4"), 4);
		numberOfPlayersDialog.set_position(Gtk::WIN_POS_CENTER_ALWAYS);
		
		numberOfPlayersDialog.show_all();
		players.resize(numberOfPlayersDialog.run());
		numberOfPlayersDialog.hide();
		timer.setNumberOfPlayers(players.size());
		cardManager.setPlayersVector(players);
		while (viewer.notebook.get_n_pages() > players.size()) {
			viewer.notebook.remove_page(-1);
		}
		constructionCamp.resize(players.size());
		continent.setNumberOfPlayers(players.size());

		//subscoring window needs to be made before much else, since other functions signal to it
		subscores.resize(players.size(), vector<NumberLabel*>(8));
		subScoringTable.attach(*Gtk::manage(new Gtk::Label("")),               0, 1, 0, 1, Gtk::SHRINK, Gtk::SHRINK, 10, 5); //need dummy label for frame
		subScoringTable.attach(*Gtk::manage(new Gtk::Label("BEFORE\nBONUS")),  1, 2, 0, 1, Gtk::SHRINK, Gtk::SHRINK, 10, 5);
		subScoringTable.attach(*Gtk::manage(new Gtk::Label("CARDS\nIN HAND")), 2, 3, 0, 1, Gtk::SHRINK, Gtk::SHRINK, 10, 5);
		subScoringTable.attach(*Gtk::manage(new Gtk::Label("WORK\nCAMP")),     3, 4, 0, 1, Gtk::SHRINK, Gtk::SHRINK, 10, 5);
		subScoringTable.attach(*Gtk::manage(new Gtk::Label("LEGION\nCAMP")),   4, 5, 0, 1, Gtk::SHRINK, Gtk::SHRINK, 10, 5);
		subScoringTable.attach(*Gtk::manage(new Gtk::Label("TRAJAN\nTILES")),  5, 6, 0, 1, Gtk::SHRINK, Gtk::SHRINK, 10, 5);
		subScoringTable.attach(*Gtk::manage(new Gtk::Label("CONSTR.\nBONUS")), 6, 7, 0, 1, Gtk::SHRINK, Gtk::SHRINK, 10, 5);
		subScoringTable.attach(*Gtk::manage(new Gtk::Label("SENATE\nTILES")),  7, 8, 0, 1, Gtk::SHRINK, Gtk::SHRINK, 10, 5);
		subScoringTable.attach(*Gtk::manage(new Gtk::Label("TOTAL")),          8, 9, 0, 1, Gtk::SHRINK, Gtk::SHRINK, 10, 5);
		
		for (auto i = 0; i < players.size(); ++i) {
			subScoringTable.attach(*Gtk::manage(new Gtk::Label(players[i]->getString())),      0, 1, i + 1, i + 2, Gtk::FILL, Gtk::FILL, 5, 5);
			for (auto j = 0; j < subscores[i].size(); ++j) {
				NumberLabel* nLabel = Gtk::manage(new NumberLabel);
				subscores[i][j] = nLabel;
				subScoringTable.attach(*nLabel, j + 1, j + 2, i + 1, i + 2);
			}
			for (auto j = 0; j < subscores[i].size() - 1; ++j) { //no need to do total, so size - 1
				calculateSubscore(i, j);
			}
		}
		vector<Gtk::Widget*> v = subScoringTable.get_children();
		for (int i = 0; i < v.size(); ++i) {
			v[i]->modify_font(NumberLabel::font);
		}
		
		
		scoringWindow.set_decorated(false);
		scoringWindow.set_border_width(10);
		scoringWindow.add(*Gtk::manage(new Gtk::EventBox));
		dynamic_cast<Gtk::EventBox*>(scoringWindow.get_child())->modify_bg(Gtk::STATE_NORMAL, Gdk::Color("#4F4F4F"));
		dynamic_cast<Gtk::EventBox*>(scoringWindow.get_child())->add(subScoringTable);
		dynamic_cast<Gtk::EventBox*>(scoringWindow.get_child())->set_border_width(5);
		scoringWindow.set_transient_for(*this);
		scoringWindow.modify_bg(Gtk::STATE_NORMAL, Gdk::Color("#FFFFFF"));

		vector<Gtk::Widget*> labels = subScoringTable.get_children();
		
		for (auto i = 0; i < labels.size(); ++i) {
			labels[i]->modify_fg(Gtk::STATE_NORMAL, Gdk::Color("#FAEBD7"));
			dynamic_cast<Gtk::Label*>(labels[i])->set_justify(Gtk::JUSTIFY_CENTER);
		}

		//put each child in its own frame
		guint r, c;
		subScoringTable.get_size(r, c);
		v = subScoringTable.get_children();
		reverse(v.begin(), v.end());
		for (int i = 0 ; i < r; ++i) {
			for (int j = 0; j < c ; ++j) {
				
				Gtk::Frame* frame = Gtk::manage(new Gtk::Frame);
				frame->set_shadow_type(Gtk::SHADOW_IN);
				subScoringTable.remove(*v[ j + (i * c) ]);
				if (i == 0) 
					v[ j + (i * c) ]->set_size_request(56, 25 * 1.5);
				else
					v[ j + (i * c) ]->set_size_request(56, 25);
				
				frame->add(*v[j + (i * c)]);
				subScoringTable.attach(*frame, j, j + 1, i, i + 1);
			}
		}
		
		
		scoringWindow.move(270, 337);
		scoringWindow.get_child()->show_all();
		//end of scoring window construction
		
		numeralPixbufs.push_back(Glib::RefPtr<Gdk::Pixbuf>());
		for (auto i = 1; i <= 9; ++i) {
			numeralPixbufs.push_back(Gdk::Pixbuf::create_from_file(RootDirectory + "leg" + to_string(long long(i)) + ".png"));
		}
		while (numeralPixbufs.size() < 15) {
			numeralPixbufs.push_back(Gdk::Pixbuf::create_from_file(RootDirectory + "leg9.png"));
		}

		currentPlayer = players[rand() % players.size()]; 
		while (cardManager.currentPlayer != currentPlayer)
			cardManager.nextPlayer();
		senate.push_back(vector<PlayerColor>(players.size()));

		for (auto i = 0; i < players.size(); ++i) {
			scoreLabels.push_back(Gtk::manage(new Gtk::Label));
			scoreLabels[i]->modify_font(scoreFont);
			scoreLabels[i]->set_justify(Gtk::JUSTIFY_LEFT);
			scoreLabels[i]->modify_fg(scoreLabels[i]->get_state(), Gdk::Color("#FAEBD7"));
			Gtk::Label* tempLabel = Gtk::manage(new Gtk::Label(players[i]->getString()));
			tempLabel->modify_fg(scoreLabels[i]->get_state(), Gdk::Color("#FAEBD7"));
			tempLabel->modify_font(scoreFont);
			tempLabel->set_size_request(70, -1);
			scoresTable.attach(*Gtk::manage(new Gtk::Image(players[i]->citizenMarker)), 0, 1, i, i + 1, Gtk::SHRINK, Gtk::SHRINK, 40);
			scoresTable.attach(*tempLabel,      1, 2, i, i + 1, Gtk::SHRINK, Gtk::SHRINK);
			scoresTable.attach(*scoreLabels[i], 2, 3, i, i + 1, Gtk::SHRINK, Gtk::SHRINK);
			players[i]->pointsChangedSignal.connect(sigc::bind<0>(sigc::mem_fun(*this, &Game::updateScore), i));
			players[i]->trajanTakenSignal.connect(sigc::mem_fun(history, &History::printTrajanTakenAction));
			players[i]->archMovedSignal.connect(sigc::mem_fun(history, &History::printArchMoved));
			players[i]->extraActionSignal.connect(sigc::mem_fun(history, &History::printExtraAction));
			players[i]->demandsMetSignal.connect(sigc::mem_fun(history, &History::printDemandsMet));
			players[i]->earnPoints(0);
			playerAddToConstructionCamp(*players[i]);
			continent.at(MILITARY_CAMP).addGeneral(players[i]->getColor());
			playerAddToMilitaryCamp(*players[i]);
			playerTakesSenateCard(*players[i], *senateCardDeck.back());
			senateCardDeck.pop_back();
			senate[0][i] = currentPlayer->getColor();
			nextPlayer();
		}
		
		senate.resize(8);
				
		modify_bg(Gtk::STATE_NORMAL, Gdk::Color("#4F4F4F"));
		senateTitleImage.set(RootDirectory + "en_tuilessenatJ-crop.png");
		senateTitleImage.set_alignment(0.0, 1.0);
		
		messageText.modify_text(Gtk::STATE_NORMAL, Gdk::Color("#FAEBD7"));
		messageText.modify_base(Gtk::STATE_NORMAL, Gdk::Color("#4F4F4F"));
		messageText.modify_fg(Gtk::STATE_NORMAL, Gdk::Color("#FAEBD7"));
		messageText.modify_bg(Gtk::STATE_NORMAL, Gdk::Color("#4F4F4F"));
		
		messageText.set_wrap_mode(Gtk::WRAP_WORD);
		messageText.modify_font(mainFont);
		messageText.set_size_request(SHEET_WIDTH, -1); 
		messageText.set_cursor_visible(false); 
		messageText.set_editable(false);
		messageText.set_justification(Gtk::JUSTIFY_CENTER);

		scoringControlButton.setLabel("[SCORING]");
		historyControlButton.setLabel("[GAME LOG]");
		scoringControlButton.signal_button_press_event().connect(sigc::bind_return(sigc::mem_fun(*this, &Game::onScoringClick), false));
		historyControlButton.signal_button_press_event().connect(sigc::bind_return(sigc::mem_fun(*this, &Game::onHistoryClick), false));

		controlBox.pack_start(scoringControlButton, Gtk::PACK_SHRINK, 20);
		controlBox.pack_start(historyControlButton, Gtk::PACK_SHRINK, 20);
		
		drawDeckVBox.pack_start(scoresTable, Gtk::PACK_SHRINK);
		drawDeckVBox.pack_start(cardManager.drawDeckHBox, Gtk::PACK_SHRINK, 20);
		drawDeckVBox.pack_start(demandDisplay.table, Gtk::PACK_SHRINK, 20);
		drawDeckVBox.pack_start(controlBox, Gtk::PACK_SHRINK, 10);
		
		senateCardsVBox.pack_end(humanPlayer.senateCards_HBox, Gtk::PACK_SHRINK);
		playerVBox.pack_end(senateCardsVBox, Gtk::PACK_SHRINK);
		playerVBox.pack_end(senateTitleImage, Gtk::PACK_SHRINK);
		playerVBox.pack_end(cardManager.rightSideVBox, Gtk::PACK_SHRINK);
		playerVBox.pack_start(viewer, Gtk::PACK_SHRINK);
		
		
		passButton.set_relief(Gtk::RELIEF_NONE);
		passButton.set_can_focus(false); 
		passButton.modify_base(Gtk::STATE_ACTIVE, Gdk::Color("#362F2D"));
		passButton.modify_bg(Gtk::STATE_ACTIVE, Gdk::Color("#362F2D"));
		passButtonLabel.set_use_markup(true);
		passButtonLabel.set_markup("<span font_family = \"" + defaultFont + "\" size=\"9216\" foreground=\"#FAEBD7\" weight=\"600\">Pass</span>");
		passButton.add(passButtonLabel);
		passButton.signal_clicked().connect(sigc::mem_fun(*this, &Game::onPassClick));
		
		endTurnButton.set_relief(Gtk::RELIEF_NONE);
		endTurnButton.set_can_focus(false); 
		endTurnButton.modify_base(Gtk::STATE_ACTIVE, Gdk::Color("#362F2D"));
		endTurnButton.modify_bg(Gtk::STATE_ACTIVE, Gdk::Color("#362F2D"));
		endTurnButtonLabel.set_use_markup(true);
		endTurnButtonLabel.set_markup("<span font_family = \"" + defaultFont + "\" size=\"9216\" foreground=\"#FAEBD7\" weight=\"600\">End Turn</span>");
		endTurnButton.add(endTurnButtonLabel);
		endTurnButton.signal_clicked().connect(sigc::mem_fun(*this, &Game::onEndTurnClick));
		
		mainTable.attach(logoImage,    0, 1, 0, 1, Gtk::SHRINK, Gtk::SHRINK);
		mainTable.attach(timer,        1, 2, 0, 1, Gtk::SHRINK, Gtk::SHRINK);
		mainTable.attach(messageText,  2, 3, 0, 1, Gtk::SHRINK, Gtk::SHRINK);
		mainTable.attach(drawDeckVBox, 0, 1, 1, 2, Gtk::SHRINK, Gtk::FILL );
		mainTable.attach(board,        1, 2, 1, 2, Gtk::SHRINK, Gtk::SHRINK);
		mainTable.attach(playerVBox,   2, 3, 1, 2, Gtk::SHRINK, Gtk::FILL);
		mainTable.set_col_spacing(0, 90);
		mainTable.set_col_spacing(1, 90);
		mainTable.set_row_spacing(0, 10);
				
		refreshForumTiles();
		refreshContinentTiles();
		refreshSenateCards();

		add(alignment);
		alignment.add(mainTable);
		set_border_width(20);
		alignment.set(0.2, 0.1, 0, 0);
		fullscreen();
		show_all();

		borderGC = Gdk::GC::create(board.get_window());
		borderGC->set_rgb_fg_color(Gdk::Color("#FFFF00")); //yellow
		borderGC->set_line_attributes(2, Gdk::LineStyle::LINE_ON_OFF_DASH, Gdk::CapStyle::CAP_ROUND, Gdk::JoinStyle::JOIN_ROUND);
		
		cardManager.borderGC = borderGC;

		viewer.startOfGame();
						
		signal_key_press_event().connect(sigc::mem_fun(*this, &Game::closeGame), false);

		viewer.pageSignal.connect(sigc::mem_fun(*this, &Game::switchPlayerView));

		debug.set_transient_for(*this);
		debug.button1.signal_clicked().connect(sigc::mem_fun(*this, &Game::printSomeFunction));
		//debug.button2.signal_clicked().connect(sigc::hide_return(sigc::mem_fun(*this, &Game::removeSimTile)));
		//debug.button3.signal_clicked().connect(sigc::hide_return(sigc::mem_fun(*this, &Game::hideEndTurnButton)));
		debug.show_all();
		debug.raise();
		debug.move(100, 700);
		
		viewer.timerSignal.connect(sigc::mem_fun(*this, &Game::printTimer));
		viewer.mainActionSignal.connect(sigc::mem_fun(*this, &Game::commenceMainAction));
		viewer.textSignal.connect(sigc::mem_fun(*this, &Game::receiveMessage));
		viewer.partialAdvanceSignal.connect(sigc::mem_fun(timer, &Timer::partialAdvance));
		viewer.resetSignal.connect(sigc::mem_fun(timer, &Timer::cancelAdvance));
		cardManager.textSignal.connect(sigc::mem_fun(*this, &Game::receiveMessage));
		cardManager.actionCompleteSignal.connect(sigc::mem_fun(*this, &Game::seaportComplete));
		cardManager.updateBordersSignal.connect(sigc::mem_fun(*this, &Gtk::Window::queue_draw));
		cardManager.historySignal.connect(sigc::mem_fun(history, &History::printSeaportAction));
		cardManager.noActionTakenSignal.connect(sigc::mem_fun(history, &History::printNoShippingTaken));
		timer.roundEndSignal.connect(sigc::mem_fun(*this, &Game::setEndOfRound));
		timer.quarterEndSignal.connect(sigc::mem_fun(*this, &Game::setEndOfQuarter));
		timer.gameEndSignal.connect(sigc::mem_fun(*this, &Game::setEndOfGame));
		timer.timerStepSignal.connect(sigc::mem_fun(history, &History::receiveTimerSnapshot));
		
		board.set_has_tooltip(true);
		board.signal_expose_event().connect(sigc::mem_fun(*this, &Game::onExpose));
		board.signal_button_press_event().connect(sigc::mem_fun(*this, &Game::onBoardClick));
		board.signal_query_tooltip().connect(sigc::mem_fun(*this, &Game::onTooltip));
		

		for (auto i = 0; i < trajanTileDeck.deck1.size(); ++i) {
			trajanTileDeck.deck1[i]->awardedSignal.connect(sigc::mem_fun(*this, &Game::playerWinsTwoCards));
			trajanTileDeck.deck1[i]->historySignal.connect(sigc::mem_fun(history, &History::printTrajanWon));
		}
		for (auto i = 0; i < trajanTileDeck.deck2.size(); ++i) {
			trajanTileDeck.deck2[i]->awardedSignal.connect(sigc::mem_fun(*this, &Game::calculateForTrajanTileWon));
			trajanTileDeck.deck2[i]->historySignal.connect(sigc::mem_fun(history, &History::printTrajanWon));
		}
		for (auto i = 0; i < trajanTileDeck.deck3.size(); ++i) {
			trajanTileDeck.deck3[i]->awardedSignal.connect(sigc::mem_fun(*this, &Game::playerAddToConstructionCamp));
			trajanTileDeck.deck3[i]->historySignal.connect(sigc::mem_fun(history, &History::printTrajanWon));
			if (trajanTileDeck.deck3[i]->VP == 2)
				trajanTileDeck.deck3[i]->awardedSignal.connect(sigc::mem_fun(*this, &Game::playerAddToConstructionCamp)); //added a second time for 2 workers
		}

		for (auto i = 0; i < trajanTileDeck.deck4.size(); ++i) {
			trajanTileDeck.deck4[i]->awardedSignal.connect(sigc::mem_fun(*this, &Game::playerAddToMilitaryCamp));
			trajanTileDeck.deck4[i]->historySignal.connect(sigc::mem_fun(history, &History::printTrajanWon));
			if (trajanTileDeck.deck4[i]->VP == 2)
				trajanTileDeck.deck4[i]->awardedSignal.connect(sigc::mem_fun(*this, &Game::playerAddToMilitaryCamp)); 
		}

		for (auto i = 0; i < trajanTileDeck.deck5.size(); ++i) {
			trajanTileDeck.deck5[i]->historySignal.connect(sigc::mem_fun(history, &History::printTrajanWon));
			trajanTileDeck.deck5[i]->awardedSignal.connect(sigc::mem_fun(*this, &Game::playerChoosesPlusTwoSlot));
		}

		for (auto i = 0; i < trajanTileDeck.deck6.size(); ++i) {
			trajanTileDeck.deck6[i]->awardedSignal.connect(sigc::mem_fun(*this, &Game::calculateForTrajanTileWon));
			trajanTileDeck.deck6[i]->historySignal.connect(sigc::mem_fun(history, &History::printTrajanWon));
		}

		
		for (auto i = 0; i < constructionTileDeck.size(); ++i) {
			constructionTileDeck[i]->firstConstructionSignal.connect(sigc::mem_fun(*this, &Game::bonusConstructionAction));
		}


		
		viewer.plusTwoSignal.connect(sigc::mem_fun(*this, &Game::placePlusTwoTile));
		viewer.wildCommoditySignal.connect(sigc::mem_fun(cardManager, &CardManager::onWildCommodityTileClicked));
		viewer.extraActionSignal.connect(sigc::mem_fun(*this, &Game::playerChoosesExtraAction));
		viewer.wildActionSignal.connect(sigc::mem_fun(*this, &Game::playerChoosesWildAction));

		
		//messageText.get_buffer()->set_text("");
		//messageText.set_pixels_above_lines(10);
		//messageText.get_buffer()->insert_at_cursor("Click         ");
		////Glib::RefPtr<Gtk::TextChildAnchor> anchor = messageText.get_buffer()->create_child_anchor(messageText.get_buffer()->end());
		//messageText.set_size_request(SHEET_WIDTH, 42);
//		//messageText.get_buffer()->insert_child_anchor(messageText.get_buffer()->end(), anchor);
		////messageText.add_child_at_anchor(*Gtk::manage(new Gtk::Image(humanPlayer.seaportExtraActionTile.pixbuf->scale_simple(35, 35, Gdk::INTERP_HYPER))), anchor);
		////messageText.add_child_in_window(*Gtk::manage(new Gtk::Image(humanPlayer.seaportExtraActionTile.pixbuf)), Gtk::TextWindowType::TEXT_WINDOW_TEXT, 90, 0);
		//
		//messageText.get_buffer()->insert_at_cursor(" or ");
		////messageText.get_buffer()->insert_child_anchor(messageText.get_buffer()->end(), anchor);
		//messageText.get_buffer()->insert_at_cursor(" to use an extra action, or click End Turn");
		//messageText.show_all();
		//	Glib::RefPtr<Gdk::Pixbuf> pix = Gdk::Pixbuf::create(Glib::RefPtr<Gdk::Drawable>(timer.get_snapshot()), 0, 0, timer.get_width(), timer.get_height());
	

		history.startGame();
		history.resize(300, 900);
		history.move(1920 * .33, 20);
		history.set_transient_for(*this);

		if (currentPlayer != players.front()) {
			computerTurns();
		}
		else {
			currentPhase = MOVE_PEGS;
			viewer.startTurn(); 
		}
		
	}

	void printSomeFunction();
		

			/*
		cout << "       Real  Simulated    \n";
		cout << "       ----  ---------    \n";
		for (int i = 0; i < continent.size(); ++i) {
			cout << "string " << continent[i].getString() << "  " << simulatedContinent[i].getString()  << endl;
			cout << "vp " << continent[i].getVP() << "  " << simulatedContinent[i].getVP() << endl;
			cout << "tileptr " << continent[i].tilePtr << "  " << simulatedContinent[i].tilePtr  << endl;
			cout << endl;
			for (int j = 0; j < continent[i].adjacents.size(); ++j) {
				cout << j << " " << continent[i].adjacents[j] << "  " << simulatedContinent[i].adjacents[j] << endl;
				
			}
		}
		for (int j = 0; j < continent[0].campAmounts.size(); ++j) {
			cout << players[j]->getString() << " "<< continent[0].campAmounts[j] << "  " << simulatedContinent[0].campAmounts[j] << endl;
		}

	
		for (int i = 0; i < players.size(); ++i) {
			ostringstream oss;
			oss << players[i]->getString() << ": " << findSenateRankAsDouble(*players[i]);
			debugInsert(oss.str());
		}
		auto chart = getSenateStandingsMap();
		for (auto i = chart.begin(); i != chart.end(); ++i) {
			ostringstream oss;
			oss << i->first << ": " << i->second->getString();
			debugInsert(oss.str());
		}
		auto p = findSenateLeaders();
		debugInsert(p.first->getString());
		debugInsert(p.second->getString());
		*/
		
	

	

	void printSenateResults() {
		history.printSenateResults(getSenateStandingsMap());
		history.printSenateCardChoices(*players[0], *players[1]);
	}
	
	void onScoringClick(GdkEventButton* e) {
		if (e->button != 1 || e->type != GDK_BUTTON_PRESS) 
			return;
		scoringWindow.set_visible(!scoringWindow.get_visible());
	}

	void calculateSubscore(size_t player, size_t column) {
		switch(column) {
		case BEFORE_BONUS:
			subscores[player][column]->setValue(players[player]->getPoints()); 
			break;
		case CARDS_IN_HAND:
			subscores[player][column]->setValue(players[player]->cardsInHand.size());
			break;
		case WORK_CAMP:
			subscores[player][column]->setValue(constructionCamp[player]);
			break;
		case LEGION_CAMP:
			subscores[player][column]->setValue(continent[MILITARY_CAMP].campAmounts[player]);
			break;
		case TRAJAN_TILES:
			subscores[player][column]->setValue(players[player]->getNumberOfTrajanTiles());
			break;
		case CONSTR_BONUS:
			subscores[player][column]->setValue(players[player]->getConstructionBonus());
			break;
		case SENATE_TILES:
			subscores[player][column]->setValue(getSenateScoreForPlayer(*players[player]));
			break;
		}
		int total = 0;
		for (int i = 0; i < subscores[0].size() - 1; ++i) { // -1 so we do NOT add in final column in total
			total += subscores[player][i]->getValue();
		}
		
		subscores[player][TOTAL_SCORE]->setValue(total);
	}

	void calculateForTrajanTileWon(Player& player) {
		calculateSubscore(currentPlayer->getColor(), subscoreName::TRAJAN_TILES);
	}

	void onHistoryClick(GdkEventButton* e) {
		if (e->button != 1 || e->type != GDK_BUTTON_PRESS) 
			return;
		history.set_visible(!history.get_visible());
	}

	bool onTooltip(int x, int y, bool, const Glib::RefPtr<Gtk::Tooltip>& tooltip) {
		ostringstream oss;
		
		if (trajanTileZone1.contains(x, y) && !trajanTileDeck.deck1.empty()) {
			oss << trajanTileDeck.deck1.size() << " tile" << (trajanTileDeck.deck1.size() == 1 ? "" : "s") << " remaining";
			tooltip->set_text(oss.str());
			return true;
		}

		if (trajanTileZone2.contains(x, y) && !trajanTileDeck.deck2.empty()) {
			oss << trajanTileDeck.deck2.size() << " tile" << (trajanTileDeck.deck2.size() == 1 ? "" : "s") << " remaining";
			tooltip->set_text(oss.str());
			return true;
		}

		if (trajanTileZone3.contains(x, y) && !trajanTileDeck.deck3.empty()) {
			oss << trajanTileDeck.deck3.size() << " tile" << (trajanTileDeck.deck3.size() == 1 ? "" : "s") << " remaining";
			tooltip->set_text(oss.str());
			return true;
		}

		if (trajanTileZone4.contains(x, y) && !trajanTileDeck.deck4.empty()) {
			oss << trajanTileDeck.deck4.size() << " tile" << (trajanTileDeck.deck4.size() == 1 ? "" : "s") << " remaining";
			tooltip->set_text(oss.str());
			return true;
		}

		if (trajanTileZone5.contains(x, y) && !trajanTileDeck.deck5.empty()) {
			oss << trajanTileDeck.deck5.size() << " tile" << (trajanTileDeck.deck5.size() == 1 ? "" : "s") << " remaining";
			tooltip->set_text(oss.str());
			return true;
		}

		if (trajanTileZone6.contains(x, y) && !trajanTileDeck.deck6.empty()) {
			oss << trajanTileDeck.deck6.size() << " tile" << (trajanTileDeck.deck6.size() == 1 ? "" : "s") << " remaining";
			tooltip->set_text(oss.str());
			return true;
		}

		return false;
	}

	void nextPlayer() {
		if (currentPlayer != players.back())
			++currentPlayer;
		else
			currentPlayer = players.front();
		cardManager.nextPlayer();
		if (endOfRound) {
			if (!endOfQuarter) {
				demandDisplay.nextRound();
				history.printRound(timer.getRound()); 
				history.printDemands(demandDisplay);
			}
			endOfRound = false;
			
		}
		if (endOfQuarter) {
			multiset<DemandType> list = demandDisplay.getDemandsList();
			for (auto i = 0; i < players.size(); ++i) 
				players[i]->endOfRoundDemands(list);

			pair<Player*, Player*> leaders = findSenateLeaders();
			Player* firstPlace = leaders.first;
			Player* secondPlace = leaders.second;
			
			history.printSenateResults(getSenateStandingsMap());

			if (players.front() == firstPlace) {
				currentPhase = CHOOSE_SENATE_CARD;
				board.queue_draw();
				messageText.get_buffer()->set_text("");
				messageText << "Choose your senate card";
				Gtk::Main::run();
			}
			else {
				if (rand() % 2 == 0) { //computer mulls choice here
					//computer chooses winning card
					firstPlace->takeSenateCard(*senateCards.front());
					senateCards.front() = NULL;
				}
				else {
					firstPlace->takeSenateCard(*senateCards.back());
					senateCards.back() = NULL;
				}
			}
			secondPlace->takeSenateCard(senateCards.front() != NULL ? *senateCards.front() : *senateCards.back(), false);
			
			history.printSenateCardChoices(*firstPlace, *secondPlace);
			
			history.printQuarter(timer.getQuarter());
			history.printRound(timer.getRound());
			if (!endOfGame) {
				refreshForumTiles();
				refreshContinentTiles();
				refreshSenateCards();
				demandDisplay.nextRound();
				cardManager.resetAllBoats();
				senateReset();
				board.queue_draw();
				viewer.queue_draw();
				endOfQuarter = false;
			
			} 
			else {
				currentPlayer = NULL;                         cout << __LINE__ << endl;
				currentPhase = COMPUTER_TURN;                 cout << __LINE__ << endl;
				Player* winner = NULL;                        cout << __LINE__ << endl;
				double highScore = 0;                         cout << __LINE__ << endl;
				for (int i = 0; i < players.size(); ++i) {
					for (int j = 0; j < subscoreName::TOTAL_SCORE; ++j) {
						calculateSubscore(i, j);              cout << __LINE__ << endl;
					}
					double modifiedScore = findSenateRankAsDouble(*players[i]);       cout << __LINE__ << endl;
					modifiedScore -= floor(modifiedScore);                            cout << __LINE__ << endl;//leave just the decimal (senate position) as tiebreaker
					modifiedScore += subscores[i][TOTAL_SCORE]->getValue();           cout << __LINE__ << endl;
					cout << i << " Mod = " << modifiedScore << endl;
					if (modifiedScore > highScore) {
						highScore = modifiedScore;                                    cout << __LINE__ << endl;
						winner = players[i];                                          cout << __LINE__ << endl;
					}
				}
				Gtk::HBox* finalBox = Gtk::manage(new Gtk::HBox());                   cout << __LINE__ << endl;
				history.printMessage(*winner, "WINS WITH " + to_string(long long(floor(highScore))) + " POINTS");         cout << __LINE__ << endl;
																													      
				for (int i = 0; i < players.size(); ++i) {															      
					scoreLabels[i]->set_text(to_string(long long(subscores[i][TOTAL_SCORE]->getValue())) + " points");    cout << __LINE__ << endl;
				}
				messageText.get_buffer()->set_text("");                                                                   cout << __LINE__ << endl;
				messageText << "Game over";                                                                               cout << __LINE__ << endl;

				Gtk::Main::run();
			}
		}
	}

	bool onExpose_Military(GdkEventExpose* e) {
		int x, y;
		board.get_pointer(x, y);
		if (humanPlayer.getCitizens() > 0) {
			if (continent[MILITARY_CAMP].legionnaireHotzone.contains(x, y)) {
				board.get_window()->draw_pixbuf(legionnaireOn, 0, 0, continent[MILITARY_CAMP].legionnaireHotzone.anchor.first, continent[MILITARY_CAMP].legionnaireHotzone.anchor.second, legionnaireOn->get_width(), legionnaireOn->get_height(), Gdk::RGB_DITHER_MAX, 0, 0);
			}
			else {
				board.get_window()->draw_pixbuf(legionnaireOff, 0, 0, continent[MILITARY_CAMP].legionnaireHotzone.anchor.first, continent[MILITARY_CAMP].legionnaireHotzone.anchor.second, legionnaireOff->get_width(), legionnaireOff->get_height(), Gdk::RGB_DITHER_MAX, 0, 0);
			}
		}

		Province& generalsProvince = continent.findGeneral(currentPlayer->getColor());
		vector<Province*> adjacentToGeneral = generalsProvince.adjacents;
		if (continent[MILITARY_CAMP].campAmounts[players.front()->getColor()] > 0) {
			if (generalsProvince.name != MILITARY_CAMP && !generalsProvince.hasLegionnaireOfColor(players.front()->getColor())) {
				if (generalsProvince.legionnaireHotzone.contains(x, y)) {
					board.get_window()->draw_pixbuf(legionnaireOn, 0, 0, generalsProvince.legionnaireHotzone.anchor.first, generalsProvince.legionnaireHotzone.anchor.second, legionnaireOn->get_width(), legionnaireOn->get_height(), Gdk::RGB_DITHER_MAX, 0, 0);
				}
				else {
					board.get_window()->draw_pixbuf(legionnaireOff, 0, 0, generalsProvince.legionnaireHotzone.anchor.first, generalsProvince.legionnaireHotzone.anchor.second, legionnaireOff->get_width(), legionnaireOff->get_height(), Gdk::RGB_DITHER_MAX, 0, 0);
				}
			}
		}

		for (auto i = 0; i < adjacentToGeneral.size(); ++i) { 
			if (adjacentToGeneral[i]->generalHotzone.contains(x, y)) {
				board.get_window()->draw_pixbuf(generalOn, 0, 0, adjacentToGeneral[i]->generalHotzone.anchor.first, adjacentToGeneral[i]->generalHotzone.anchor.second, generalOn->get_width(), generalOn->get_height(), Gdk::RGB_DITHER_MAX, 0, 0);
			}
			else {
				board.get_window()->draw_pixbuf(generalOff, 0, 0, adjacentToGeneral[i]->generalHotzone.anchor.first, adjacentToGeneral[i]->generalHotzone.anchor.second, generalOn->get_width(), generalOn->get_height(), Gdk::RGB_DITHER_MAX, 0, 0);
			}
		}
		
		board.queue_draw();
		return false;
	}
	
	void drawBorder(Hotzone hotzone) {
		board.get_window()->draw_rectangle(borderGC, false, hotzone.anchor.first, hotzone.anchor.second, hotzone.width, hotzone.height);
		board.queue_draw();
	}

	void drawConstructionTileBorder(Hotzone hotzone) {
		Gdk::Point points[5] = {
			Gdk::Point(hotzone.anchor.first                                , hotzone.anchor.second +  (CONSTRUCTION_TILE_HEIGHT / 5)), 
			Gdk::Point(hotzone.anchor.first + (CONSTRUCTION_TILE_WIDTH / 2), hotzone.anchor.second                                  ), 
			Gdk::Point(hotzone.anchor.first + CONSTRUCTION_TILE_WIDTH,       hotzone.anchor.second +  (CONSTRUCTION_TILE_HEIGHT / 5)), 
			Gdk::Point(hotzone.anchor.first + CONSTRUCTION_TILE_WIDTH,       hotzone.anchor.second +   CONSTRUCTION_TILE_HEIGHT     ), 
			Gdk::Point(hotzone.anchor.first                                , hotzone.anchor.second +   CONSTRUCTION_TILE_HEIGHT     ),
		};
		vector<Gdk::Point> v(points, points + 5);
		board.get_window()->draw_polygon(borderGC, false, v);
	}

	void drawSenateBorders() {
		int offset = senateCardRightZone.anchor.first - senateCardLeftZone.anchor.first;
		board.get_window()->draw_arc(borderGC, false, 926 - board.get_allocation().get_x(), 913 - board.get_allocation().get_y(), 84, 84, 2600, (180 * 64) - (2600 * 2));
		Gdk::Point points[4] = {
			Gdk::Point(senateCardLeftZone.anchor.first, senateCardLeftZone.anchor.second + 16), 
			Gdk::Point(senateCardLeftZone.anchor.first, senateCardLeftZone.anchor.second + senateCardLeftZone.height), 
			Gdk::Point(senateCardLeftZone.anchor.first + senateCardLeftZone.width, senateCardLeftZone.anchor.second + senateCardLeftZone.height), 
			Gdk::Point(senateCardLeftZone.anchor.first + senateCardLeftZone.width, senateCardLeftZone.anchor.second + 16)
		};
		vector<Gdk::Point> v(points, points + 4);
		board.get_window()->draw_lines(borderGC, v);

		board.get_window()->draw_arc(borderGC, false, 926 + offset - board.get_allocation().get_x(), 913 - board.get_allocation().get_y(), 84, 84, 2600, (180 * 64) - (2600 * 2));
		for (auto i = 0; i < v.size(); ++i)
			v[i].set_x(v[i].get_x() + offset);
		board.get_window()->draw_lines(borderGC, v);
	}

	bool onExpose(GdkEventExpose* e) {
		board.get_window()->draw_pixbuf(cardManager.topBoat.getPixbuf(), 0, 0, TOP_BOAT_ANCHOR.first, TOP_BOAT_ANCHOR.second, cardManager.topBoat.getPixbuf()->get_width(), cardManager.topBoat.getPixbuf()->get_height(), Gdk::RGB_DITHER_MAX, 0, 0);
		board.get_window()->draw_pixbuf(cardManager.middleBoat.getPixbuf(), 0, 0, MIDDLE_BOAT_ANCHOR.first, MIDDLE_BOAT_ANCHOR.second, cardManager.middleBoat.getPixbuf()->get_width(), cardManager.middleBoat.getPixbuf()->get_height(), Gdk::RGB_DITHER_MAX, 0, 0);
		board.get_window()->draw_pixbuf(cardManager.bottomBoat.getPixbuf(), 0, 0, BOTTOM_BOAT_ANCHOR.first, BOTTOM_BOAT_ANCHOR.second, cardManager.bottomBoat.getPixbuf()->get_width(), cardManager.bottomBoat.getPixbuf()->get_height(), Gdk::RGB_DITHER_MAX, 0, 0);
				
		//board.get_window()->draw_lines(borderGC, points);
		
		for (auto i = 0; i < constructionTileDeck.size(); ++i) {
			if (constructionTileDeck[i] && constructionField[i].empty()) //to correct graphics glitch: don't show tile if worker just got placed but we're waiting for player's "use extra action?" input
				board.get_window()->draw_pixbuf(*constructionTileDeck[i], 0, 0, constructionZones[i].anchor.first, constructionZones[i].anchor.second, CONSTRUCTION_TILE_WIDTH, CONSTRUCTION_TILE_HEIGHT, Gdk::RGB_DITHER_MAX, 0, 0);
			for (auto j = 0; j < constructionField[i].size(); ++j) {
				board.get_window()->draw_pixbuf(players[constructionField[i][j]]->citizenMarker, 0, 0, constructionFieldAnchors[i][j].first, constructionFieldAnchors[i][j].second, players[constructionField[i][j]]->citizenMarker->get_width(), players[constructionField[i][j]]->citizenMarker->get_height(), Gdk::RGB_DITHER_MAX, 0, 0);
			}
		}
		
		for (auto i = 0; i < constructionCamp.size(); ++i) {
			if (constructionCamp[i] > 0) {
				board.get_window()->draw_pixbuf(players[i]->citizenMarker, 0, 0,  constructionCampAnchors[i].first, constructionCampAnchors[i].second, players[i]->citizenMarker->get_width(), players[i]->citizenMarker->get_height(), Gdk::RGB_DITHER_MAX, 0, 0);
				board.get_window()->draw_pixbuf(numeralPixbufs[constructionCamp[i]], 0, 0,  constructionCampAnchors[i].first, constructionCampAnchors[i].second, numeralPixbufs[constructionCamp[i]]->get_width(), numeralPixbufs[constructionCamp[i]]->get_height(), Gdk::RGB_DITHER_MAX, 0, 0);
			}
		}

	

		for (auto i = 0; i < senate.size(); ++i) {
			for (auto j = 0; j < senate[i].size(); ++j) {
				board.get_window()->draw_pixbuf(players[senate[i][j]]->senateMarker, 0, 0, senateAnchors[i][j].first, senateAnchors[i][j].second, players[senate[i][j]]->senateMarker->get_width(), players[senate[i][j]]->senateMarker->get_height(), Gdk::RGB_DITHER_MAX, 0, 0);
			}
		}
		
		if (!trajanTileDeck.deck1.empty())
			board.get_window()->draw_pixbuf(*trajanTileDeck.deck1.back(), 0, 0, TRAJAN_ANCHOR_1.first, TRAJAN_ANCHOR_1.second, TRAJAN_TILE_WIDTH, TRAJAN_TILE_HEIGHT, Gdk::RGB_DITHER_MAX, 0, 0);
		if (!trajanTileDeck.deck2.empty())
			board.get_window()->draw_pixbuf(*trajanTileDeck.deck2.back(), 0, 0, TRAJAN_ANCHOR_2.first, TRAJAN_ANCHOR_2.second, TRAJAN_TILE_WIDTH, TRAJAN_TILE_HEIGHT, Gdk::RGB_DITHER_MAX, 0, 0);
		if (!trajanTileDeck.deck3.empty())
			board.get_window()->draw_pixbuf(*trajanTileDeck.deck3.back(), 0, 0, TRAJAN_ANCHOR_3.first, TRAJAN_ANCHOR_3.second, TRAJAN_TILE_WIDTH, TRAJAN_TILE_HEIGHT, Gdk::RGB_DITHER_MAX, 0, 0);
		if (!trajanTileDeck.deck4.empty())
			board.get_window()->draw_pixbuf(*trajanTileDeck.deck4.back(), 0, 0, TRAJAN_ANCHOR_4.first, TRAJAN_ANCHOR_4.second, TRAJAN_TILE_WIDTH, TRAJAN_TILE_HEIGHT, Gdk::RGB_DITHER_MAX, 0, 0);
		if (!trajanTileDeck.deck5.empty())
			board.get_window()->draw_pixbuf(*trajanTileDeck.deck5.back(), 0, 0, TRAJAN_ANCHOR_5.first, TRAJAN_ANCHOR_5.second, TRAJAN_TILE_WIDTH, TRAJAN_TILE_HEIGHT, Gdk::RGB_DITHER_MAX, 0, 0);
		if (!trajanTileDeck.deck6.empty())
			board.get_window()->draw_pixbuf(*trajanTileDeck.deck6.back(), 0, 0, TRAJAN_ANCHOR_6.first, TRAJAN_ANCHOR_6.second, TRAJAN_TILE_WIDTH, TRAJAN_TILE_HEIGHT, Gdk::RGB_DITHER_MAX, 0, 0);
				

		for (auto i = 0; i < continent.size(); ++i) {
			if (continent[i].tilePtr) {
				board.get_window()->draw_pixbuf(*continent[i].tilePtr, 0, 0, continent[i].tileAnchor.first, continent[i].tileAnchor.second, 
					(*continent[i].tilePtr)->get_width(), (*continent[i].tilePtr)->get_height(), Gdk::RGB_DITHER_MAX, 0, 0);
			}
			if (continent[i].name == MILITARY_CAMP) {
				for (auto j = 0; j < players.size(); ++j) {
					if (continent[i].campAmounts[j] > 0) {
						board.get_window()->draw_pixbuf(players[j]->citizenMarker, 0, 0, continent[i].legionnaireAnchors[j].first, continent[i].legionnaireAnchors[j].second, 
							players.front()->citizenMarker->get_width(), players.front()->citizenMarker->get_height(), Gdk::RGB_DITHER_MAX, 0, 0);
						board.get_window()->draw_pixbuf(numeralPixbufs[continent[i].campAmounts[j]], 0, 0, continent[i].legionnaireAnchors[j].first, continent[i].legionnaireAnchors[j].second, 
							numeralPixbufs[continent[i].campAmounts[j]]->get_width(), numeralPixbufs[continent[i].campAmounts[j]]->get_height(), Gdk::RGB_DITHER_MAX, 0, 0);
					}
				}
			}
			else {
				for (auto j = 0; j < continent[i].legionnaires.size(); ++j) {
					board.get_window()->draw_pixbuf(players[continent[i].legionnaires[j]]->citizenMarker, 0, 0, continent[i].legionnaireAnchors[j].first, continent[i].legionnaireAnchors[j].second, 
						players.front()->citizenMarker->get_width(), players.front()->citizenMarker->get_height(), Gdk::RGB_DITHER_MAX, 0, 0);
				}
			}
			for (auto j = 0; j < continent[i].generals.size(); ++j) {
				board.get_window()->draw_pixbuf(players[continent[i].generals[j]]->generalMarker, 0, 0, continent[i].generalAnchors[j].first, continent[i].generalAnchors[j].second, 
					players.front()->generalMarker->get_width(), players.front()->generalMarker->get_height(), Gdk::RGB_DITHER_MAX, 0, 0);
			}
		}

		if (senateCards.front())
			board.get_window()->draw_pixbuf(senateCards.front()->getPixbuf(), 0, 0, LEFT_SENATE_CARD_ANCHOR.first, LEFT_SENATE_CARD_ANCHOR.second, SENATE_CARD_WIDTH, SENATE_CARD_HEIGHT, Gdk::RGB_DITHER_MAX, 0, 0);
		if (senateCards.back())
			board.get_window()->draw_pixbuf(senateCards.back()->getPixbuf(), 0, 0, RIGHT_SENATE_CARD_ANCHOR.first, RIGHT_SENATE_CARD_ANCHOR.second, SENATE_CARD_WIDTH, SENATE_CARD_HEIGHT, Gdk::RGB_DITHER_MAX, 0, 0);

		/*

		may use a slightly different set-up: during decision phase, draw all the "off" guys necessary,
		then the "if contains" says draw/redraw that area with "on" guy

		
		*/


		for (auto i = 0; i < forum.size(); ++i) {
			if (forum[i]) {
				board.get_window()->draw_pixbuf(*forum[i], 0, 0, forumZones[i].anchor.first, forumZones[i].anchor.second, FORUM_TILE_WIDTH, FORUM_TILE_HEIGHT, Gdk::RGB_DITHER_MAX, 0, 0);
				if (currentPhase == FORUM && !extraActionPrompted) {
					drawBorder(forumZones[i]);
				}
			}
		}

		if (extraActionPrompted)
			return false;

		if (currentPhase == SEAPORT) {
			if (cardManager.actionState == CardManager::AWAITING_CHOICE) {
				if (cardManager.playerHasAtLeastOnePair()) {
					drawBorder(topBoatZone);
				}
				if (!cardManager.cardsInHandSelectors.empty() || humanPlayer.hasWildCommodityTile()) {
					drawBorder(middleBoatZone);
					drawBorder(bottomBoatZone);
				}
			}
		}

		if (currentPhase == MILITARY) 
			onExpose_Military(e);
		
		if (currentPhase == TRAJAN) {
			if (!trajanTileDeck.deck1.empty())
				drawBorder(trajanTileZone1);
			if (!trajanTileDeck.deck2.empty()) 
				drawBorder(trajanTileZone2);
			if (!trajanTileDeck.deck3.empty()) 
				drawBorder(trajanTileZone3);
			if (!trajanTileDeck.deck4.empty()) 
				drawBorder(trajanTileZone4);
			if (!trajanTileDeck.deck5.empty()) 
				drawBorder(trajanTileZone5);
			if (!trajanTileDeck.deck6.empty()) 
				drawBorder(trajanTileZone6);
		}

		if (currentPhase == CONSTRUCTION) {
			if (humanPlayer.getCitizens() > 0) {
				int x, y;
				board.get_pointer(x, y);
				if (constructionCampZone.contains(x, y)) {
					board.get_window()->draw_pixbuf(legionnaireOn, 0, 0, constructionCampZone.anchor.first, constructionCampZone.anchor.second, legionnaireOn->get_width(), legionnaireOn->get_height(), Gdk::RGB_DITHER_MAX, 0, 0);
				}
				else {
					board.get_window()->draw_pixbuf(legionnaireOff, 0, 0, constructionCampZone.anchor.first, constructionCampZone.anchor.second, legionnaireOn->get_width(), legionnaireOn->get_height(), Gdk::RGB_DITHER_MAX, 0, 0);
				}
				board.queue_draw_area(constructionCampZone.anchor.first, constructionCampZone.anchor.second, constructionCampZone.width, constructionCampZone.height); 
			}

			if (constructionCamp[humanPlayer.getColor()] > 0) {
				for (auto i = 0; i < constructionZones.size(); ++i) {
					if (constructionSiteValid(i)) {
						drawConstructionTileBorder(constructionZones[i]);
					}
				}
			}
		}

		if (currentPhase == CHOOSE_SENATE_CARD) {
			drawSenateBorders(); 
		}

		return false;
    }

	bool onBoardClick(GdkEventButton* e) {
		if (e->type != GDK_BUTTON_PRESS)
			return false;
		
		if (currentPhase == MOVE_PEGS || currentPhase == COMPUTER_TURN || currentPlayer == NULL || extraActionPrompted)
			return false;

		if (currentPhase == SEAPORT) {
			if (topBoatZone.   contains(e->x, e->y)) { cardManager.shipWithTop();    }
			if (middleBoatZone.contains(e->x, e->y)) { cardManager.shipWithMiddle(); }
			if (bottomBoatZone.contains(e->x, e->y)) { cardManager.shipWithBottom(); }
		}
		if (currentPhase == FORUM) {
			for (auto i = 0; i < forumZones.size(); ++i) {
				if (forum[i] && forumZones[i].contains(e->x, e->y)) {
					forum[i]->awardTo(humanPlayer);
					history.printForumAction(*currentPlayer, *forum[i]);
					forum[i] = NULL;
					calculateSubscore(currentPlayer->getColor(), SENATE_TILES);
					calculateSubscore(currentPlayer->getColor(), CONSTR_BONUS); //wildConstructionTile
					endTurn();
				}
			}
		}
		if (currentPhase == MILITARY) {
			Province& generalsProvince = continent.findGeneral(humanPlayer.getColor());
			for (auto i = 0; i < generalsProvince.adjacents.size(); ++i) {
				if (generalsProvince.adjacents[i]->generalHotzone.contains(e->x, e->y)) {
					string movedFrom = generalsProvince.getString();
					continent.moveGeneral(humanPlayer.getColor(), generalsProvince.adjacents[i]->name);
					string movedTo = continent.findGeneral(humanPlayer.getColor()).getString();
					const Tile* tileTaken = generalsProvince.adjacents[i]->tilePtr; //will be NULL if province was empty
					if (generalsProvince.adjacents[i]->tilePtr) {
						humanPlayer.takeTile(*generalsProvince.adjacents[i]->tilePtr);
						generalsProvince.adjacents[i]->tilePtr = NULL;
					}
					history.printMilitaryAction(*currentPlayer, "MOVES GENERAL FROM '" + movedFrom + "' TO '" + movedTo + "' ", tileTaken); 
					calculateSubscore(currentPlayer->getColor(), SENATE_TILES);
					calculateSubscore(currentPlayer->getColor(), CONSTR_BONUS); 
					endTurn();
				}
			}

			if (continent[MILITARY_CAMP].legionnaireHotzone.contains(e->x, e->y)) {
				if (humanPlayer.getCitizens() == 0)
					return false;
				humanPlayer.sendCitizens(1);
				continent[MILITARY_CAMP].addLegionnaire(humanPlayer.getColor());
				history.printMilitaryAction(*currentPlayer, "SENDS A CITIZEN TO MILITARY CAMP"); 
				calculateSubscore(currentPlayer->getColor(), LEGION_CAMP);
				endTurn();
			}
			else if (generalsProvince.legionnaireHotzone.contains(e->x, e->y)) {
				if (continent[MILITARY_CAMP].campAmounts[humanPlayer.getColor()] == 0 || generalsProvince.hasLegionnaireOfColor(humanPlayer.getColor()))
					return false;
				ostringstream oss;
				oss << "SENDS A LEGIONNAIRE TO '" << generalsProvince.getString() << "' (" << generalsProvince.getVP() << " VP)";
				history.printMilitaryAction(*currentPlayer, oss.str()); 
				humanPlayer.earnPoints(generalsProvince.getVP());
				generalsProvince.addLegionnaire(humanPlayer.getColor());
				continent[MILITARY_CAMP].removeLegionnaire(humanPlayer.getColor());
				calculateSubscore(currentPlayer->getColor(), LEGION_CAMP);
				calculateSubscore(currentPlayer->getColor(), SENATE_TILES);
				endTurn();
			}
		}
		if (currentPhase == TRAJAN) {
			if (trajanTileZone1.contains(e->x, e->y)) {
				humanPlayer.placeTrajanTileOnWheel(trajanTileDeck.deck1); 
				endTurn(); 
			}
			if (trajanTileZone2.contains(e->x, e->y)) {
				humanPlayer.placeTrajanTileOnWheel(trajanTileDeck.deck2); 
				endTurn(); 
			}
			if (trajanTileZone3.contains(e->x, e->y)) {	
				humanPlayer.placeTrajanTileOnWheel(trajanTileDeck.deck3);
				endTurn();
			}
			if (trajanTileZone4.contains(e->x, e->y)) {
				humanPlayer.placeTrajanTileOnWheel(trajanTileDeck.deck4); 
				endTurn(); 
			}
			if (trajanTileZone5.contains(e->x, e->y)) {
				humanPlayer.placeTrajanTileOnWheel(trajanTileDeck.deck5); 
				endTurn();
			}
			if (trajanTileZone6.contains(e->x, e->y)) {
				humanPlayer.placeTrajanTileOnWheel(trajanTileDeck.deck6); 
				endTurn();
			}
		}
		if (currentPhase == CONSTRUCTION) {

			if (constructionCampZone.contains(e->x, e->y) && humanPlayer.getCitizens() > 0) {
				playerAddToConstructionCamp(humanPlayer);
				calculateSubscore(currentPlayer->getColor(), WORK_CAMP);
				string message = "SENDS CITIZEN TO WORKER CAMP";
				history.printConstructionAction(*currentPlayer, message, Glib::RefPtr<Gdk::Pixbuf>());
				endTurn();
			}
		
			for (auto i = 0; i < constructionZones.size(); ++i) {
				if (constructionZones[i].contains(e->x, e->y) && constructionCamp[humanPlayer.getColor()] > 0) { 
					if (constructionSiteValid(i)) {
						constructionField[i].push_back(humanPlayer.getColor());
						--constructionCamp[humanPlayer.getColor()];
						calculateSubscore(currentPlayer->getColor(), WORK_CAMP);
						string message = "SENDS WORKER TO LINE " + to_string(long long((i / 5) + 1)) +  ", COLUMN " + to_string(long long((i % 5) + 1));
						Glib::RefPtr<Gdk::Pixbuf> constructionPixbuf;
						if (constructionTileDeck[i]) {
							constructionPixbuf = *constructionTileDeck[i];
							message.append(" (" + to_string(long long(constructionTileDeck[i]->getVP())) + " VP)");
							history.printConstructionAction(*currentPlayer, message, constructionPixbuf);
							calculateSubscore(currentPlayer->getColor(), CONSTR_BONUS);
							calculateSubscore(currentPlayer->getColor(), SENATE_TILES);
							constructionTileDeck[i]->awardTo(humanPlayer); //now goes and does bonus action, if first tile
							constructionTileDeck[i] = NULL;
						}

						if (constructionFinished) {
							endTurn();
						}
						else if (currentPhase == SENATE && !extraActionUsedThisTurn) {
							endTurn();
						}
						else if (currentPhase == SENATE) {
							currentPhase = CONSTRUCTION;
							endTurn();
						}
					}
				}
			}
		}

		if (currentPhase == CHOOSE_SENATE_CARD) {
			if (senateCardLeftZone.contains(e->x, e->y)) {
				humanPlayer.takeSenateCard(*senateCards.front());
				senateCards.front() = NULL;
				if (currentPlayer == players.front())
					currentPhase = MOVE_PEGS;
				else
					currentPhase = COMPUTER_TURN;
				Gtk::Main::quit();
			}
			if (senateCardRightZone.contains(e->x, e->y)) {
				humanPlayer.takeSenateCard(*senateCards.back());
				senateCards.back() = NULL;
				if (currentPlayer == players.front())
					currentPhase = MOVE_PEGS;
				else
					currentPhase = COMPUTER_TURN;
				Gtk::Main::quit();
			}
		}

		

		board.queue_draw();
		viewer.queue_draw();
		
		
		return false;
	}

	bool allTrajanDecksEmpty() {
		if (!trajanTileDeck.deck1.empty())
			return false;
		if (!trajanTileDeck.deck2.empty())
			return false;
		if (!trajanTileDeck.deck3.empty())
			return false;
		if (!trajanTileDeck.deck4.empty())
			return false;
		if (!trajanTileDeck.deck5.empty())
			return false;
		if (!trajanTileDeck.deck6.empty())
			return false;
		return true;
	}

	void debugInsert(const string& s) {
		debug._textView.get_buffer()->insert(debug._textView.get_buffer()->begin(), s + '\n');
		//debug._textView.get_buffer()->set_text(debug._textView.get_buffer()->get_text() + s + '\n');
		//debug.scrollToEnd();
	}

	void printTimer(size_t mainAction) {
		history.printTimer(*currentPlayer, mainAction);
	}

	void commenceMainAction(size_t action) {
		messageText.get_buffer()->set_text("");
		switch (action) {
		case MAIN_SEAPORT:
			seaportAction();
			break;
		case MAIN_FORUM:
			messageText << "Choose a forum tile."; 
			forumAction();
			break;
		case MAIN_MILITARY:
			messageText << "Choose a military action."; 
			militaryAction();
			break;
		case MAIN_SENATE:
			messageText << "";  
			senateAction();
			break;
		case MAIN_TRAJAN:
			messageText << "Choose a trajan tile.";  
			trajanAction();
			break;
		case MAIN_CONSTRUCTION:
			messageText << "Choose a construction action.";  
			constructionAction();
			break;
		}
		board.queue_draw();
	}

	void bonusConstructionAction(size_t type) {
		constructionFinished = false;
		string message = "FREE ACTION >> ";
		switch(type) {
		case MAIN_SEAPORT: 
			message.append("SEAPORT"); 
			break;
		case MAIN_FORUM: 
			message.append("FORUM"); 
			break;
		case MAIN_MILITARY: 
			message.append("MILITARY"); 
			break;
		case MAIN_SENATE: 
			message.append("SENATE"); 
			break;
		case MAIN_TRAJAN: 
			message.append("TRAJAN"); 
			break;
		case MAIN_CONSTRUCTION: 
			message.append("CONSTRUCTION"); 
			break;
		}
		history.printMessage(*currentPlayer, message);
		commenceMainAction(type);
	}

	void seaportAction() {
		currentPhase = SEAPORT;
		viewer.remove(viewer.hButtonBox);
		viewer.remove(viewer.handTable);
		viewer.pack_start(cardManager.boatAndButtonsTable);
		cardManager.startAction();
	}

	void seaportComplete() {
		viewer.remove(cardManager.boatAndButtonsTable);
		viewer.pack_start(viewer.handTable);
		viewer.pack_start(viewer.hButtonBox);
		messageText.get_buffer()->set_text("");
		calculateSubscore(currentPlayer->getColor(), BEFORE_BONUS);
		calculateSubscore(currentPlayer->getColor(), CARDS_IN_HAND);
		calculateSubscore(currentPlayer->getColor(), SENATE_TILES);
		endTurn();
	}

	void forumAction() {
		currentPhase = FORUM;
		for (auto i = 0; i < forum.size(); ++i) {
			if (forum[i]) {
				return; //valid tile found -- take turn as normal
			}
		}
		//if at this point in code, no forum tiles left
		history.printMessage(*currentPlayer, "NO FORUM TILES REMAINING");
		if (constructionFinished) 
			endTurn(); //TODO: test this ends turn ONLY ONCE even when done as bonus construction action
		else 
			constructionFinished = true;
	}

	void militaryAction() {
		currentPhase = MILITARY;
		board.queue_draw();
		showEndTurnButton();
	}

	void senateAction() {
		currentPhase = SENATE; 
		size_t points = senateAdvance(*currentPlayer);
		currentPlayer->earnPoints(points);
		history.printSenateAction(*currentPlayer, points);
		if (constructionFinished)
			endTurn(); //TODO: check this works for all bonus actions

	}

	void trajanAction() {
		currentPhase = TRAJAN;
		//if all tiles gone OR all 6 slots on tray filled.. go to next turn / phase
		if (!currentPlayer->spaceForTrajanTileAvailable()) {
			history.printMessage(*currentPlayer, "ALL SIX TRAJAN SPACES FILLED");
			if (constructionFinished) 
				endTurn();
			else
				constructionFinished = true;
		}
		else if (allTrajanDecksEmpty()) {
			history.printMessage(*currentPlayer, "NO TRAJAN TILES REMAINING");
			if (constructionFinished) 
				endTurn();
			else
				constructionFinished = true;
		}
	}

	void constructionAction() {
		currentPhase = CONSTRUCTION;
		board.queue_draw();
		if (currentPlayer->getCitizens() == 0 && constructionCamp[currentPlayer->getColor()] == 0) {
			history.printMessage(*currentPlayer, "NO CONSTRUCTION ACTION POSSIBLE");
			endTurn();
		}
		else
			showEndTurnButton();
		//TODO: test end turn conditions
	}
		
	void playerAddToConstructionCamp(Player& player) {
		if (player.getCitizens() == 0)
			return;
		player.sendCitizens(1);
		++constructionCamp[player.getColor()];
		calculateSubscore(player.getColor(), WORK_CAMP);
		calculateSubscore(player.getColor(), TRAJAN_TILES);
		board.queue_draw();
		player.queue_draw();
	}

	void playerAddToMilitaryCamp(Player& player) {
		if (player.getCitizens() == 0)
			return;
		player.sendCitizens(1);
		continent.addLegionnaire(player.getColor(), MILITARY_CAMP);
		calculateSubscore(player.getColor(), LEGION_CAMP);
		calculateSubscore(player.getColor(), TRAJAN_TILES);
		board.queue_draw();
		player.queue_draw();
	}

	void receiveMessage(const string& s) {
		messageText.get_buffer()->set_text("");
		messageText << s;
		/*
		ostringstream oss;
		int bufferX, bufferY, windowX, windowY;
		Gdk::Rectangle rect;
		messageText.get_iter_location(messageText.get_buffer()->begin(), rect);
		oss << "X " << rect.get_x() << "   Y " << rect.get_y() << endl;
		oss << "Height " << rect.get_height() << "   width " << rect.get_width() << endl;
		messageText.buffer_to_window_coords(Gtk::TextWindowType::TEXT_WINDOW_TEXT, rect.get_x(), rect.get_y(), windowX, windowY);
		oss << "WindowX " << windowX << "   windowY " << windowY << endl;
		debugInsert(oss.str());
		oss.str("");

		messageText.get_iter_location(messageText.get_buffer()->end(), rect);
		oss << "X " << rect.get_x() << "   Y " << rect.get_y() << endl;
		oss << "Height " << rect.get_height() << "   width " << rect.get_width() << endl;
		messageText.buffer_to_window_coords(Gtk::TextWindowType::TEXT_WINDOW_TEXT, rect.get_x(), rect.get_y(), windowX, windowY);
		oss << "WindowX " << windowX << "   windowY " << windowY << endl;
		debugInsert(oss.str());
		oss.str("");
		*/
	}

	void switchPlayerView(size_t n) {
		cardManager.cardsInHandMainBox.foreach(sigc::mem_fun(cardManager.cardsInHandMainBox, &Gtk::HBox::remove));
		cardManager.cardsInHandMainBox.pack_start(players[n]->cardsInHand_HBox, Gtk::PACK_SHRINK);
		cardManager.cardsInHandMainBox.show_all();
		cardManager.cardsInPlayMainBox.foreach(sigc::mem_fun(cardManager.cardsInPlayMainBox, &Gtk::HBox::remove));
		cardManager.cardsInPlayMainBox.pack_start(players[n]->cardsInPlay_HBox, Gtk::PACK_SHRINK);
		cardManager.cardsInPlayMainBox.show_all();
		senateCardsVBox.foreach(sigc::mem_fun(senateCardsVBox, &Gtk::VBox::remove));
		senateCardsVBox.pack_end(players[n]->senateCards_HBox, Gtk::PACK_SHRINK);
		senateCardsVBox.show_all();
		queue_draw();

		//switch(n) {
		//case 0:
		//	
		//	cardManager.cardsInHandMainBox.foreach(sigc::mem_fun(cardManager.cardsInHandMainBox, &Gtk::HBox::remove));
		//	//cardManager.cardsInHandMainBox.remove(*cardManager.cardsInHandBoxPtrs[1]);
		//	cardManager.cardsInHandMainBox.pack_start(players[n]->cardsInHand_HBox, Gtk::PACK_SHRINK);
		//	cardManager.cardsInHandMainBox.show_all(); 
		//	//cardManager.cardsInHandBoxPtrs[0]->show_all();
		//	break;
		//case 1:
		//	
		//	cardManager.cardsInHandMainBox.foreach(sigc::mem_fun(cardManager.cardsInHandMainBox, &Gtk::HBox::remove));
		//	cardManager.cardsInHandMainBox.pack_start(players[n]->cardsInHand_HBox, Gtk::PACK_SHRINK);
		//	cardManager.cardsInHandMainBox.show_all();
		//	break;
		//}
	}

	void playerTakesSenateCard(Player& player, const SenateCard& card) {
		player.senateCards.push_back(card);
		player.senateCards_HBox.pack_start(*Gtk::manage(new Gtk::Image(player.senateCards.back().getPixbuf())), Gtk::PACK_SHRINK);
	}

	bool constructionSiteValid(size_t site) {
		//if worker of current player color is already at that site, it's not a valid site
		if (find(constructionField[site].begin(), constructionField[site].end(), currentPlayer->getColor()) != constructionField[site].end()) {
			return false;
		}
		bool workerInField = false;
		for (auto i = 0; i < constructionField.size(); ++i) {
			if (find(constructionField[i].begin(), constructionField[i].end(), currentPlayer->getColor()) != constructionField[i].end()) 
				workerInField = true;
		}

		if (!workerInField) {
			return true;
		}
		
		set<size_t> adjacents;
		if (site > 4)            { adjacents.insert(site - 5); } //not top edge
		if (site < 15)           { adjacents.insert(site + 5); } //not bottom edge
		if (site % 5 != 0)       { adjacents.insert(site - 1); } //not left edge
		if ((site + 1) % 5 != 0) { adjacents.insert(site + 1); } //not right edge
		for (auto i = adjacents.begin(); i != adjacents.end(); ++i) {
			if (find(constructionField[*i].begin(), constructionField[*i].end(), currentPlayer->getColor()) != constructionField[*i].end()) {
				return true;
			}
		}
		return false;
	}

	size_t findSenatePosition(const Player& p) const {
		for (auto i = 0; i < senate.size(); ++i) {
			for (auto j = 0; j < senate[i].size(); ++j) {
				if (senate[i][j] == p.getColor())
					return i;
			}
		}
		cout << "findSenatePosition: player " << p.getString() << " not found\n";
		exit(EXIT_FAILURE);
	}

	double findSenateRankAsDouble(const Player& p) const {
		double result = p.getVotes();
		for (auto i = 0; i < senate.size(); ++i) {
			for (auto j = 0; j < senate[i].size(); ++j) {
				if (senate[i][j] == p.getColor()) {
					if (i != 0)
						result += double(i + 1) + (double(i + 1) / 10.0);
					result += double(j + 1) / 100.0;
				}
			}
		}
		if (result == 0) { //if result isn't at least .01 for being somewhere in space 0
			cout << "findSenatePosition: player " << p.getString() << " not found\n";
			exit(EXIT_FAILURE);
		}
		return result;
	}

	size_t getPlayerTotalVotes(const Player& p) const {
		size_t result = findSenatePosition(p.getColor());
		if (result != 0)
			result += 1;
		return result + p.getVotes();
	}

	pair<Player*, Player*> findSenateLeaders() const {
		std::map<double, Player*> chart = getSenateStandingsMap();
		auto it = chart.rbegin();
		
		pair<Player*, Player*> result;
		result.first = it->second;
		++it;
		result.second = it->second;
		return result;

		/*
		
		pair<PlayerColor, PlayerColor> result;
		vector<entry> entries;
		for (auto i = 0; i < players.size(); ++i) {
			voteCount v = make_pair(getPlayerTotalVotes(*players[i]), findSenatePosition(*players[i]));
			entries.push_back(entry(v, players[i]->getColor())); 
		}
		sort(entries.begin(), entries.end());
		return pair<PlayerColor, PlayerColor>((entries.end() - 1)->second, (entries.end() - 2)->second);
		*/
	}

	std::map<double, Player*> getSenateStandingsMap() const {
		std::map<double, Player*> chart;
		for (int i = 0; i < players.size(); ++i) {
			chart.insert(make_pair(findSenateRankAsDouble(*players[i]), players[i]));
		}
		return chart;
	}

	size_t senateAdvance(const Player& p) { 
		if (findSenatePosition(p) == 7)
			return 0; 
		size_t position = findSenatePosition(p);
		senate[position].erase(find(senate[position].begin(), senate[position].end(), p.getColor()));
		senate[position + 1].push_back(p.getColor());
		board.queue_draw();
		return position + 2; //points for new position
	}

	void senateReset() {
		auto chart = getSenateStandingsMap();
		for (auto i = 0; i < senate.size(); ++i) {
			senate[i].clear();
		}
		for (auto i = chart.begin(); i != chart.end(); ++i) {
			senate[0].push_back(i->second->getColor());
		}
		for (auto i = 0; i < players.size(); ++i) 
			players[i]->clearVotes();
			
		board.queue_draw();
	}

	void playerWinsTwoCards(Player& p) {
		//trajan win message
		Gtk::HBox* rightHbox = Gtk::manage(new Gtk::HBox(false, 2));
		if (cardManager.deck.size() >= 2) {
			rightHbox->pack_start(*Gtk::manage(new Gtk::Image(CommodityCardDrawDeck::cardBackPixbuf)), Gtk::PACK_SHRINK);
			rightHbox->pack_start(*Gtk::manage(new Gtk::Image(CommodityCardDrawDeck::cardBackPixbuf)), Gtk::PACK_SHRINK);
			history.printSeaportAction(p, "WINS TWO COMMODITY CARDS", rightHbox, false);
		}
		else if (cardManager.deck.size() == 1) {
			rightHbox->pack_start(*Gtk::manage(new Gtk::Image(CommodityCardDrawDeck::cardBackPixbuf)), Gtk::PACK_SHRINK);
			history.printSeaportAction(p, "WINS ONE COMMODITY CARD", rightHbox, false);
		}
		cardManager.playerGetsNewCard(cardManager.deck.drawCard());
		cardManager.playerGetsNewCard(cardManager.deck.drawCard());
		
		calculateSubscore(p.getColor(), CARDS_IN_HAND);
		calculateSubscore(p.getColor(), TRAJAN_TILES);
		calculateSubscore(p.getColor(), SENATE_TILES);

	}

	/*
	void playerChoosesExtraAction() {
		if (!humanPlayer.hasWildActionTile())
			return;
		//check we have nonwild matching action
		//commence main action?
		ostringstream oss;
		oss << "Action " << action << " chosen";
		debugInsert(oss.str());
		cout << oss.str();
		Gtk::Main::quit(); 
		
	}
	*/


	void playerChoosesExtraAction(size_t action) {
		
		if (!extraActionPrompted) 
			return;
		if (!humanPlayer.hasExtraActionFor(action))
			return;
		
		extraActionPrompted = false;
		extraActionUsedThisTurn = true;
		humanPlayer.spendsExtraActionTileFor(action); 
		humanPlayer.setExtraActionActive(false);

		extraActionsRemaining = humanPlayer.hasPlusTwoTileFor(action) ? 2 : 1;
		hideEndTurnButton();
		Gtk::Main::quit(); 
	}

	void playerChoosesWildAction() {
		if (!extraActionPrompted) 
			return;
		if (!humanPlayer.hasWildActionTile())
			return;
		if (humanPlayer.hasExtraActionFor(currentPhase)) //if player has the matching extra action tile, he can't use the wild action
			return;
		extraActionPrompted = false;
		extraActionUsedThisTurn = true;
		humanPlayer.spendsWildActionTile(currentPhase);
		humanPlayer.setExtraActionActive(false);

		extraActionsRemaining = humanPlayer.hasPlusTwoTileFor(currentPhase) ? 2 : 1;
		hideEndTurnButton();
		Gtk::Main::quit(); 
	}

	void playerChoosesPlusTwoSlot(Player& p) {
		calculateSubscore(p.getColor(), TRAJAN_TILES);
		if (currentPlayer->plusTwoTiles.count() == 6) {
			history.printMessage(p, "HAS '+2' MARKERS IN EVERY SLOT");
			return;
		}
		if (currentPlayer == players.front()) {
			currentPhase = CHOOSE_PLACE_PLUS_TWO;
			clearMessageText();
			messageText << "Place your +2 tile";
			humanPlayer.setPlusTwosActive(true);
			humanPlayer.queue_draw();
			Gtk::Main::run();
		}
		else {
			//computer mulls
		}

	}

	void placePlusTwoTile(size_t action) {
		if (currentPhase != CHOOSE_PLACE_PLUS_TWO) 
			return;
		if (humanPlayer.plusTwoTiles[action])
			return;
		humanPlayer.plusTwoTiles[action] = true;
		humanPlayer.setPlusTwosActive(false);
		humanPlayer.queue_draw();
		Glib::RefPtr<Gdk::Pixbuf> pixbuf;
		switch(action) {
		case MAIN_SEAPORT:
			pixbuf = currentPlayer->seaportExtraActionTile.pixbuf;
			break;
		case MAIN_FORUM:
			pixbuf = currentPlayer->forumExtraActionTile.pixbuf;
			break;
		case MAIN_MILITARY:
			pixbuf = currentPlayer->militaryExtraActionTile.pixbuf;
			break;
		case MAIN_SENATE:
			pixbuf = currentPlayer->senateExtraActionTile.pixbuf;
			break;
		case MAIN_TRAJAN:
			pixbuf = currentPlayer->trajanExtraActionTile.pixbuf;
			break;
		case MAIN_CONSTRUCTION:
			pixbuf = currentPlayer->constructionExtraActionTile.pixbuf;
			break;
		}
		history.printPlusTwoChoice(*currentPlayer, pixbuf);
		Gtk::Main::quit();
	}

	void computerTurns() {
		while (currentPlayer && currentPlayer != players.front()) {
			size_t r;
			do {
				r = rand() % 6;
			} while (!currentPlayer->computerCanTakeAction(MainActionType(r)));
			//TODO: replace random action with AI

			//also need code and AI to deal with extra action choices
			size_t advancement = currentPlayer->computerPlacePegsForAction(MainActionType(r)); 
			timer.partialAdvance(advancement);
			timer.advance(advancement);
			history.printTimer(*currentPlayer, r);
			//print actual turn info next

			//AI on turn's decisions (which forum tile to pick, etc)

			for (auto i = 0; i < subscores[i].size(); ++i) {
				calculateSubscore(currentPlayer->getColor(), i);
			}
			
			currentPlayer->queue_draw();
			nextPlayer();
		}
		if (currentPlayer) { //i.e., if game hasn't ended
			currentPhase = MOVE_PEGS;
			viewer.startTurn();
		}
	}
		
	void updateScore(size_t playerNumber, string& s) {
		if (players[playerNumber]->getPoints() != 1)
			scoreLabels[playerNumber]->set_text(s + " points" );
		else												 
			scoreLabels[playerNumber]->set_text(s + " point"); 
		calculateSubscore(playerNumber, BEFORE_BONUS);
	}

	void refreshForumTiles() {
		forum.resize(15, NULL);
		for (auto i = 0; i < 3; ++i) {
			forum[i] = (extraActionDeck.back());
			extraActionDeck.pop_back();
		}
		for (auto i = 3; i < (3 * players.size()) + 3 && !forumTileDeck.empty(); ++i) {
			forum[i] = (forumTileDeck.back());
			forumTileDeck.pop_back();
		}
	}

	void refreshContinentTiles() {
		for (auto i = 0; i < continent.size() && !forumTileDeck.empty(); ++i) {
			if (continent[i].needsTile()) {
				continent[i].tilePtr = forumTileDeck.back();
				forumTileDeck.pop_back();
			}
		}
	}

	void refreshSenateCards() {
		senateCards.resize(2, NULL);
		senateCards.front() = senateCardDeck.back();
		senateCardDeck.pop_back();
		senateCards.back() = senateCardDeck.back();
		senateCardDeck.pop_back();
		for (auto i = 0; i < players.size(); ++i) {
			calculateSubscore(players[i]->getColor(), SENATE_TILES);
		}
	}

	void setEndOfRound()   { endOfRound   = true; }
	void setEndOfQuarter() { endOfQuarter = true; }
	void setEndOfGame()    { endOfGame    = true; }

	void promptForExtraAction(int type) {
		
		if (type < 0 || 5 < type) {
			cout << "ERROR: promptForExtraAction: " << type << " out of range\n";
			exit(EXIT_FAILURE);
		}
		clearMessageText();
		messageText.get_buffer()->insert_at_cursor("Click ");
		Glib::RefPtr<Gdk::Pixbuf> actionPixbuf;
		if (!humanPlayer.hasExtraActionFor(type)) {
			actionPixbuf = humanPlayer.wildActionTile.pixbuf;
		}
		else {
			switch(type) {
			case MAIN_SEAPORT:
				actionPixbuf = humanPlayer.seaportExtraActionTile.pixbuf;
				break;
			case MAIN_FORUM:
				actionPixbuf = humanPlayer.forumExtraActionTile.pixbuf;
				break;
			case MAIN_MILITARY:
				actionPixbuf = humanPlayer.militaryExtraActionTile.pixbuf;
				break;
			case MAIN_SENATE:
				actionPixbuf = humanPlayer.senateExtraActionTile.pixbuf;
				break;
			case MAIN_TRAJAN:
				actionPixbuf = humanPlayer.trajanExtraActionTile.pixbuf;
				break;
			case MAIN_CONSTRUCTION:
				actionPixbuf = humanPlayer.constructionExtraActionTile.pixbuf;
				break;
			}
		}
		messageText.get_buffer()->insert_pixbuf(messageText.get_buffer()->end(), actionPixbuf);
		messageText << " to take an extra action, or press ";

		//different message (not "end of turn") for bonus construction actions
		//if (!constructionFinished && (humanPlayer.hasExtraActionFor(CONSTRUCTION) || humanPlayer.hasWildActionTile())) .....

		//Glib::RefPtr<Gtk::TextChildAnchor> buttonAnchor = messageText.get_buffer()->create_child_anchor(messageText.get_buffer()->end());
		//messageText.add_child_at_anchor(endTurnButton, buttonAnchor);

		if (!constructionFinished && !extraActionUsedThisTurn && (humanPlayer.hasExtraActionFor(CONSTRUCTION) || humanPlayer.hasWildActionTile())) {
			showPassButton();
			messageText << "Pass";
		}
		else {
			showEndTurnButton();
			messageText << "End Turn";
		}
		
		humanPlayer.setExtraActionActive(type);
		
		Gtk::Main::run();

		
		
	}
	
	void endTurn() {
		hideEndTurnButton();
		board.queue_draw();
		viewer.queue_draw();
		calculateSubscore(currentPlayer->getColor(), TRAJAN_TILES); //so many variables, we'll just do it every turn
		
		if (extraActionUsedThisTurn && extraActionsRemaining > 0) {
			//if ( !(currentPhase == SENATE && constructionFinished) )
			if (currentPhase != SENATE)
				Gtk::Main::quit(); 
			return;
		}
		
	
		if (currentPlayer == &humanPlayer && currentPhase != MOVE_PEGS && (humanPlayer.hasExtraActionFor(currentPhase) || humanPlayer.hasWildActionTile()) && !extraActionUsedThisTurn) {
			
			extraActionPrompted = true;
			promptForExtraAction(currentPhase);

			while (extraActionUsedThisTurn && extraActionsRemaining > 0) { //extra actions take place inside this loop
				commenceMainAction(currentPhase);
				if (currentPhase != SENATE)
					Gtk::Main::run();
				--extraActionsRemaining;
			}
		}

		if (!constructionFinished) {
			currentPhase = CONSTRUCTION;
			constructionFinished = true;
			if (currentPlayer == &humanPlayer && currentPhase != MOVE_PEGS && (humanPlayer.hasExtraActionFor(currentPhase) || humanPlayer.hasWildActionTile()) && !extraActionUsedThisTurn) {
				extraActionPrompted = true;
				promptForExtraAction(currentPhase);

				while (extraActionUsedThisTurn && extraActionsRemaining > 0) {
					commenceMainAction(currentPhase);
					if (currentPhase != SENATE)
						Gtk::Main::run();
					--extraActionsRemaining;
				}
			}
		}

		extraActionUsedThisTurn = false;
		extraActionsRemaining = 0;
		constructionFinished = true;
		currentPhase = COMPUTER_TURN;
		timer.advance(viewer.getTimeAdvancedThisTurn());
		ostringstream oss;
		oss << "Human advances " << viewer.getTimeAdvancedThisTurn() << " spaces";
		debugInsert(oss.str());
		nextPlayer();
		computerTurns();
	}

	
	bool closeGame (GdkEventKey* e) {
		if (e->keyval == GDK_q || e->keyval == GDK_Escape) {
            Gtk::MessageDialog quitForReal(*this, "Do you really want to exit the game?", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO, true);
            if (quitForReal.run() == Gtk::RESPONSE_YES) {
                Gtk::Main::quit();
                return true;
            }
			else {
                quitForReal.hide();
                return true;
            }
        }
		else
            return false;
    }
	
	
	void clearMessageText() { messageText.get_buffer()->set_text(""); }

	void showPassButton() {
		hideEndTurnButton();
		if (passButton.get_parent() == NULL) {
			viewer.hButtonBox.pack_start(passButton);
			passButton.show_all();
		}
	}

	void hidePassButton() {
		if (passButton.get_parent())
			viewer.hButtonBox.remove(passButton);
	}
	
	void showEndTurnButton() {
		hidePassButton();
		if (endTurnButton.get_parent() == NULL) {
			viewer.hButtonBox.pack_start(endTurnButton);
			endTurnButton.show_all();
		}
	}

	void hideEndTurnButton() {
		if (endTurnButton.get_parent())
			viewer.hButtonBox.remove(endTurnButton);
	}

	void onPassClick() {
		humanPlayer.setExtraActionActive(false);
		extraActionPrompted = false;
		hidePassButton();
		Gtk::Main::quit();
	}

	void onEndTurnClick() {
		if (extraActionPrompted) {
			humanPlayer.setExtraActionActive(false);
			extraActionPrompted = false;
			hideEndTurnButton();
			Gtk::Main::quit();
		}
		else {
			history.printMessage(*currentPlayer, "TAKES NO ACTION");
			endTurn();
		}
	}

	int getSenateScoreForPlayer(const Player& player) const {
		int result = 0;

		for (int i = 0; i < player.senateCards.size(); ++i)
		{
			result += player.senateCards[i].getScore(*this, player);
		}
		result += player.getWildCommodityBonusValue() * player.wildCommodityTile.amount;
		result += player.getTotalWildDemandBonus();
		return result;
	}

	/* Simulation helper functions   */

	vector<CommodityCard> getLeftDiscardPile() { return cardManager.deck.leftDiscardPile; }
	vector<CommodityCard> getRightDiscardPile() { return cardManager.deck.rightDiscardPile; }

	Boat getTopBoat()    const { return cardManager.topBoat;}
	Boat getMiddleBoat() const { return cardManager.middleBoat;}
	Boat getBottomBoat() const { return cardManager.bottomBoat;}

	//void setUpSimGame();

};



size_t SenateCard::getSenateCardScore00(const Game& game, const Player& player) const { 
	if (player.breadForumTile.amount > 0)  
		return isGoldSideUp() ? 9 : 6; 
	else return 0;
}
size_t SenateCard::getSenateCardScore01(const Game& game, const Player& player) const {
	if (player.helmetForumTile.amount > 0) 
		return isGoldSideUp() ? 9 : 6; 
	else return 0;
}
size_t SenateCard::getSenateCardScore02(const Game& game, const Player& player) const {
	if (player.fireForumTile.amount > 0) 
		return isGoldSideUp() ? 9 : 6; 
	else return 0;
}
size_t SenateCard::getSenateCardScore03(const Game& game, const Player& player) const
{
	size_t count = 0;
	for (auto i = 0; i < game.constructionField.size(); ++i)
		for (auto j = 0; j <  game.constructionField[i].size(); ++j)
			if (game.constructionField[i][j] == player.getColor())
				++count;
	return isGoldSideUp() ? count : ceil(count / 2.0); 
}
size_t SenateCard::getSenateCardScoreCommodity(const Game& game, const Player& player) const
{ 
	size_t count = 0;
	for (auto i = 0; i < player.cardsInPlay.size(); ++i) {
		if (player.cardsInPlay[i].commodity == getCommodityBonuses().first || player.cardsInPlay[i].commodity == getCommodityBonuses().second) {
			++count;
		}
	}
	return isGoldSideUp() ? count * 3 : count * 2;
}
size_t SenateCard::getSenateCardScore10(const Game& game, const Player& player) const
{
	size_t count = 0;
	for (auto i = 1; i < game.continent.size(); ++i) //i = 1, skip MILITARY_CAMP
		if (game.continent[i].hasLegionnaireOfColor(player.getColor()))
				++count;
	return isGoldSideUp() ? count * 2 : count; 
}
size_t SenateCard::getSenateCardScore11(const Game& game, const Player& player) const
{
	size_t count = 0;
	for (auto i = 0; i < player.senateCards.size(); ++i) 
		if (player.senateCards[i].isGoldSideUp())
				++count;
	return isGoldSideUp() ? count * 3 : count * 2; 
}
size_t SenateCard::getScore(const Game& game, const Player& player) const {
	
	return (this->*scoreFunctionPtr)(game, player);
}

class SimulatedGame
{
public:
	vector<Player> players;
	Player* currentPlayer;

	Game::Phase currentPhase;
	
	size_t timeInOneQuarter;
	size_t timeAdvanced; //could have getTimeRemaining as function
	size_t quarter;

	vector<CommodityCard> leftDiscardPile;
	vector<CommodityCard> rightDiscardPile;
	size_t cardsInDrawPileRemaining;

	size_t extraActionsRemaining;
	bool constructionFinished;

	size_t neededBread;
	size_t neededHelmet;
	size_t neededFire;

	TrajanTileDeck trajanTileDeck;
	vector<const ForumTile*> forum;
	Continent continent;
	ConstructionTileDeck constructionTileDeck;
	vector< vector <PlayerColor> > constructionField;
	vector <size_t> constructionCamp;
	vector< vector< PlayerColor > > senate;
	vector<const SenateCard*> senateCards;


	Boat topBoat;
	Boat middleBoat;
	Boat bottomBoat;


	

	SimulatedGame(const Game& game) :
		topBoat(game.getTopBoat()), middleBoat(game.getMiddleBoat()), bottomBoat(game.getBottomBoat()),
		trajanTileDeck(game.trajanTileDeck), forum(game.forum), continent(game.continent), constructionTileDeck(game.constructionTileDeck),
		constructionField(game.constructionField), constructionCamp(game.constructionCamp), senate(game.senate), cardsInDrawPileRemaining(game.cardManager.deck.size()),
		senateCards(game.senateCards), currentPhase(Game::COMPUTER_TURN),
		neededBread(game.demandDisplay.getNumberOfNeeded(BREAD)),
		neededHelmet(game.demandDisplay.getNumberOfNeeded(HELMET)),
		neededFire(game.demandDisplay.getNumberOfNeeded(FIRE))
	{
		
		cout << players.size() << "  " << game.players.size() << endl;
		for (int i = 0; i < game.players.size(); ++i) {
			players.push_back(Player(*game.players[i]));
			cout << players.size() << "  " << game.players.size() << endl;
		}
		currentPlayer = &players.front();
		//disconnect signals?
		
	}

	void player2TakesTurn() {
		int r = rand() % 6;cout << __LINE__ << endl;
		cout << "taking turn " << players.size() << endl;cout << __LINE__ << endl;
		if (players[1].computerCanTakeAction(MainActionType(r))) {
			cout << "Computer can take action " << r << endl;cout << __LINE__ << endl;
			players[1].computerPlacePegsForAction(MainActionType(r));cout << __LINE__ << endl;
			for (int j = 0; j < 6; ++j) {
				cout << "Tray " << j << " pegs:  " << players[1].getWheel()[j].size() << endl;cout << __LINE__ << endl;
			}
		}
		else {
			cout << "Computer can NOT take action " << r << endl;cout << __LINE__ << endl;
		}
	}


};

void Game::printSomeFunction() {
	

	if (simGamePtr == NULL)
		simGamePtr = new SimulatedGame(*this);
		//simGamePtr = new SimulatedGame(*this);
	
	
	
}

int main() {
	srand(time(NULL));
	Gtk::Main kit(0,0); 
	CommodityCardDrawDeck::cardBackPixbuf = Gdk::Pixbuf::create_from_file(RootDirectory + "cdos.png");
	CommodityCardSelector::border = Gdk::Pixbuf::create_from_file(RootDirectory + "cardBorder.png");
	CommodityCardSelector::yellowBorder = Gdk::Pixbuf::create_from_file(RootDirectory + "yellowBorder.png");
	CommodityCardSelector::wildTileBorderPixbuf = Gdk::Pixbuf::create_from_file(RootDirectory + "cardBorderWild.png");

	Player::arch023Pixbuf = Gdk::Pixbuf::create_from_file(RootDirectory + "arcg.png");
	Player::arch145Pixbuf = Gdk::Pixbuf::create_from_file(RootDirectory + "arcd.png");
	Player::plusTwoPixbuf = Gdk::Pixbuf::create_from_file(RootDirectory + "plus2.png", 42, 42, true);

	NumberLabel::font.set_size(PANGO_SCALE * 8);
	NumberLabel::font.set_family(defaultFont);
	NumberLabel::font.set_weight(Pango::WEIGHT_NORMAL);

	Game test;
	Gtk::Main::run(test);
	

}

