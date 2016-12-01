#include <iostream>
#include <unordered_map>
#include <memory>

class Component
{
public:
	typedef std::unordered_map<std::string, void*> registry_map;

	virtual ~Component() = default;

	static registry_map & registry()
	{
		static registry_map impl;
		return impl;
	}
	template<typename ...T>
	static Component * instantiate(std::string const & name, T&&...args)
	{
		auto it = registry().find(name);
		if (it == registry().end()) return 0;
		typedef Component* (*create_type)(T...);
		auto create_fun = reinterpret_cast<create_type>(it->second);
		return create_fun(args...);
	}
	template<typename T>
	static Component* instantiateJSON(std::string const &name, const std::string& json)
	{
		auto it = registry().find(name);
		if (it == registry().end()) return 0;
		typedef Component* (*create_type)(json);
		auto create_fun = reinterpret_cast<create_type>(it->second);
		return create_fun(args...);
	}
	virtual void doSomething() = 0;
};

struct Registry
{
	template<typename F>
	Registry(std::string name, F func)
	{
		Component::registry()[name] = reinterpret_cast<void*>(func);
	}
};

#define REGISTRY_COMPONENT(className) Registry className##::registry(""#className"", ##className##::create);
#define CLASS_REGISTRY_COMPONENT static Registry registry;

class ComponentOne : public Component
{
	CLASS_REGISTRY_COMPONENT
public:
	static Component * create() { return new ComponentOne; }
	virtual void doSomething() override { std::cout << "I am class one" << std::endl; }
};

REGISTRY_COMPONENT(ComponentOne)

class ComponentTwo : public Component
{
	CLASS_REGISTRY_COMPONENT
	int a;
	const char *b;
public:
	ComponentTwo(int a, const char *b) : a(a), b(b) {}
	static Component * create(int a, const char *b) { return new ComponentTwo(a, b); }
	virtual void doSomething() { std::cout << "I am class two with params: " << a << " and " << b << std::endl; }
};
REGISTRY_COMPONENT(ComponentTwo)


int main()
{
	auto instanceOne = Component::instantiate("ComponentOne");
	auto instanceTwo = Component::instantiate("ComponentTwo", 1, "hello");

	instanceOne->doSomething();
	instanceTwo->doSomething();

	return 0;
}