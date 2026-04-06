#include "doctest.h"
#include "Enemy.h"
#include "Drop.h"

TEST_CASE("Enemy without a drop has no drop") {
	Enemy e{ "Dummy", 100, 50 };
	CHECK(!e.hasDrop());
}
TEST_CASE("Enemy with a drop reports it correctly") {
	Drop d{ "Iron Shard", 10 };
	Enemy e{ "Golem", 200, 100, d };
	SUBCASE("hasDrop returns true") {
		CHECK(e.hasDrop());
	}
	SUBCASE("getDrop returns correct name") {
		CHECK(e.getDrop()->name == "Iron Shard");
	}
	SUBCASE("getDrop returns correct gold value") {
		CHECK(e.getDrop()->goldValue == 10);
	}
}
TEST_CASE("Enemy drop is accessible after enemy dies") {
	Drop d{ "Iron Shard", 10 };
	Enemy e{ "Golem", 200, 100, d };
	e.takeDamage(999);
	CHECK(!e.isAlive());
	CHECK(e.hasDrop());
	CHECK(e.getDrop()->name == "Iron Shard");
}
TEST_CASE("Drop with empty name is still valid") {
	Drop d{ "", 5 };
	Enemy e{ "Golem", 200, 100, d };
	CHECK(e.hasDrop());
	CHECK(e.getDrop()->goldValue == 5);
}
TEST_CASE("Drop can have zero gold value") {
	Drop d{ "Broken Sword", 0 };
	Enemy e{ "Golem", 200, 100, d };
	CHECK(e.hasDrop());
	CHECK(e.getDrop()->goldValue == 0);
}