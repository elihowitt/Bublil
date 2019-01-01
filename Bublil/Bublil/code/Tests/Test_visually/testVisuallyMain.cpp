#define OLC_PGE_APPLICATION

#include"olc.h"

#include"../../physicsNS.h"
#include"../../physicsUnit_EntityNS.h"

class TestVisually:public olc::PixelGameEngine
{
public:
	TestVisually()
	{
		sAppName = "Testing visually.";
	}
public:
	phy::PhysicalEntity circleA = phy::PhysicalEntity(phy::PhysicalUnit(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 10), phy::col::CollisionBody(phy::col::CBT_SPHERE, false, new glm::vec3(0, 0, 0), new float(25), nullptr, nullptr, nullptr, nullptr));
	phy::PhysicalEntity circleB = phy::PhysicalEntity(phy::PhysicalUnit(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 10), phy::col::CollisionBody(phy::col::CBT_SPHERE, false, new glm::vec3(0, 0, 0), new float(25), nullptr, nullptr, nullptr, nullptr));
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		circleA.unit.position = glm::vec3(40, 40, 0);

		circleB.unit.position = glm::vec3(100, 100, 0);
		circleB.unit.velocity = glm::vec3(200, 0, 0);

		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override
	{
		*circleA.body.centre = circleA.unit.position;
		*circleB.body.centre = circleB.unit.position;
		// called once per frame, draws random coloured pixels
		//for (int x = 0; x < ScreenWidth(); x++)
		//	for (int y = 0; y < ScreenHeight(); y++)
		
		//if (phy::col::doCollideSimple(circleA.body, circleB.body))
		//	FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::GREEN);
		/*else*/ FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::BLACK);
		
		if (phy::col::doCollideSimple(circleA.body, circleB.body))
			std::cout << "Hit!\n";

		DrawCircle(circleA.unit.position.x, circleA.unit.position.y, *circleA.body.radius, olc::RED);
		DrawCircle(circleB.unit.position.x, circleB.unit.position.y, *circleB.body.radius, olc::BLUE);

		if (GetKey(olc::Key::DOWN).bReleased)
			phy::PhysicalUnit::applyForce(circleA.unit, glm::vec3(0000, -200000, 0));

		phy::PhysicalUnit::applyForce(circleA.unit, glm::vec3(0, 1000, fElapsedTime));

		if ((circleB.unit.position.x - *circleB.body.radius <= 0) || (circleB.unit.position.x + *circleB.body.radius >= ScreenWidth()))
		{
			circleB.unit.velocity *= -1;
		}
		phy::PhysicalUnit::updatePosition(circleB.unit, fElapsedTime);

		if (circleA.unit.position.y + *circleA.body.radius >= ScreenHeight())
		{
			circleA.unit.velocity *= -1/2.f;
			//circleA.unit.velocity = glm::vec3(0, 0, 0);
			circleA.unit.position.y = ScreenHeight() - *circleA.body.radius;
		}
		if (GetKey(olc::Key::UP).bReleased)
			phy::PhysicalUnit::updatePosition(circleA.unit, fElapsedTime);

		return true;
	}
};

int main()
{
	TestVisually test;
	if (test.Construct(480, 240, 3, 3))
		test.Start();

	return 1;
}