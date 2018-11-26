#include "CatanNetworking/CatanNetworking.h"
#include "CatanGame/CatanGame.h"
#include "CatanGame/Coord.h"

#include <vector>

using namespace std;

#define CONSOLE(x) cout << "[CatanGame v1.0] " << x << endl

int main(int argc, char** argv) {

	vector<Coord> coords = {
		Coord("EFJ", Coord::Type::DOT),
		Coord('E', Coord::Type::LAND),
		Coord('F', Coord::Type::LAND),
		Coord('C', Coord::Type::LAND),
		Coord('0', Coord::Type::SEA),
		Coord("EF", Coord::Type::EDGE),
		Coord("FK", Coord::Type::EDGE),
		Coord("FJ", Coord::Type::EDGE),
		Coord("A0", Coord::Type::DOT),
		Coord("FJK", Coord::Type::DOT),
		Coord("OPS", Coord::Type::DOT)
	};

	cout << "EFJ es vertice de E? " << coords[0].isVertexOf(coords[1]) << endl;
	cout << "EFJ es vertice de C? " << coords[0].isVertexOf(coords[3]) << endl;
	cout << "EFJ es vertice de 0? " << coords[0].isVertexOf(coords[4]) << endl;

	cout << "EF es linea de EFJ? " << coords[5].isEdgeOf(coords[0]) << endl;
	cout << "EF es linea de E? " << coords[5].isEdgeOf(coords[1]) << endl;
	cout << "EF es linea de C? " << coords[5].isEdgeOf(coords[3]) << endl;
	cout << "EF es linea de FJK? " << coords[5].isEdgeOf(coords[9]) << endl;

	cout << "EF es continua con FK? " << coords[5].edgeContinuity(coords[6]) << endl;
	cout << "EF es continua con FJ? " << coords[5].edgeContinuity(coords[7]) << endl;
	cout << "EF es continua con A0? " << coords[5].edgeContinuity(coords[8]) << endl;

	cout << "EFJ es adyacente a OPS? " << coords[0].isAdjacentDot(coords[10]) << endl;
	cout << "EFJ es adyacente a FJK? " << coords[0].isAdjacentDot(coords[9]) << endl;

	for (Coord c : coords) {
		cout << "Coordenada: " << c.getCoords() << endl;
		cout << "Es mar? " << c.isSea() << endl;
		cout << "Es tierra? " << c.isLand() << endl;
		cout << "Es punto? " << c.isDot() << endl;
		cout << "Es linea? " << c.isEdge() << endl;
		cout << "Es costa? " << c.nearCoast() << endl;
	}
}