class Player
{
public:

private:
	int energy;
	int bank;
	
};

/*
	terrain:
		0 = meadow
		1 = forest
		2 = water
		3 = wall
		4 = bog
		5 = swamp
	visible:
		0 = not visible
		1 = visible
*/
class Tile
{
public:

private:
	Content * content;
	int terrain;
	bool visibile;
}

class Map
{
public:

private:
	int size;
	Tile ** tiles;
}

class Content
{
public:
	
private:
}
