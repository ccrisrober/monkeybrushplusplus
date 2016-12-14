#include <mb/mb.h>
#include <vector>

struct NodeMat
{
	std::string name;
	mb::Material* material;
};

int main( void )
{
	mb::GLContext context(3, 3, 1024, 768, "Hello SceneGraph");
	std::vector<NodeMat> materials;
	materials.push_back({ "nodo3", new mb::NormalMaterial() });
	materials.push_back({ "nodo1", new mb::SimpleShadingMaterial() });
	materials.push_back({ "nodo2", new mb::NormalMaterial() });

	std::sort(materials.begin(), materials.end(), [](NodeMat n1, NodeMat n2) {
		return n1.name.compare(n2.name) < 0;
	});

	return 0;
}
