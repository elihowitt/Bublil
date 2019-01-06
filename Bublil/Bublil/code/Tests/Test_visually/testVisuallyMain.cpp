#define OLC_PGE_APPLICATION

#include"olc.h"

#include"../../physicsCollisionNS.h"
#include"../../physicsUnit_EntityNS.h"

#include<vector>

#include<ctime>

class TestVisually :public olc::PixelGameEngine
{
public:
	TestVisually()
	{
		sAppName = "Testing visually.";
	}
public:
	//phy::PhysicalEntity circleA = phy::PhysicalEntity(phy::PhysicalUnit(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 10), phy::col::CollisionBody(phy::col::CBT_SPHERE, false, new glm::vec3(0, 0, 0), new float(25), nullptr, nullptr, nullptr, nullptr));
	//phy::PhysicalEntity circleB = phy::PhysicalEntity(phy::PhysicalUnit(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 10), phy::col::CollisionBody(phy::col::CBT_SPHERE, false, new glm::vec3(0, 0, 0), new float(25), nullptr, nullptr, nullptr, nullptr));

	std::vector<std::pair<phy::PhysicalEntity, olc::Pixel>> circles;

	int size;

	olc::Pixel colours[10]{ olc::RED, olc::DARK_RED, olc::GREEN, olc::DARK_GREEN, olc::BLUE, olc::DARK_BLUE, olc::YELLOW, olc::DARK_YELLOW, olc::MAGENTA, olc::DARK_MAGENTA };

	bool jump, explosion;

	int screenMid;

	bool activeExplosion;
	int explosionStart;
	glm::vec2 mouseWhenExplosion;

	bool OnUserCreate() override
	{
		activeExplosion = false;
		explosion = false;
		screenMid = ScreenWidth() / 2;
		jump = false;
		srand(time(0));
		size = 50;
		int xPos, yPos;
		int mass;
		// Called once at the start, so create things here
		for (int i = 0; i < size; ++i)
		{
			mass = rand() % 26 + 5;
			xPos = (ScreenWidth() - 20) / size * i + 20;
			yPos = ScreenHeight() - mass - 1;
			circles.push_back(
				{
				phy::PhysicalEntity(
								phy::PhysicalUnit(glm::vec3(xPos, yPos, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), mass),
								phy::col::CollisionBody(phy::col::CBT_SPHERE, false, new glm::vec3(xPos, yPos, 0), new float(mass), nullptr, nullptr, nullptr, nullptr)),
				colours[(int)((10 * i / size) * 3.5) % 10]
				});
		}

		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override
	{
		//*circleA.body.centre = circleA.unit.position;
		//*circleB.body.centre = circleB.unit.position;

		// called once per frame, draws random coloured pixels
		//for (int x = 0; x < ScreenWidth(); x++)
		//	for (int y = 0; y < ScreenHeight(); y++)

		//if (phy::col::doCollideSimple(circleA.body, circleB.body))
		//	FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::GREEN);
		/*else*/ FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::BLACK);

		//if (phy::col::doCollideSimple(circleA.body, circleB.body))
		//	DrawString(50,50,"Hit!", olc::WHITE, 5U);
		if (GetKey(olc::Key::UP).bReleased)
			jump = true;
		else jump = false;

		if (GetMouse(0).bReleased)
			explosion = true;
		else explosion = false;

		if (activeExplosion)
		{
			if (--explosionStart > 0)
			{
				FillCircle(mouseWhenExplosion.x, mouseWhenExplosion.y, 10);
				FillCircle(mouseWhenExplosion.x, mouseWhenExplosion.y, 3, olc::RED);
			}
			else activeExplosion = false;
		}

		for (std::pair<phy::PhysicalEntity, olc::Pixel>& c : circles)
		{
			DrawCircle(c.first.unit.position.x, c.first.unit.position.y, *c.first.body.radius, c.second);
			glm::vec3 dir = glm::normalize(glm::vec3(GetMouseX(), GetMouseY(), 0) - c.first.unit.position);
			//Jumping.
			if (jump)
				phy::PhysicalUnit::applyForce(c.first.unit, glm::vec3(0000, -250000, 0));
			//phy::PhysicalUnit::applyForce(c.first.unit, glm::vec3(dir.x * -1000, dir.y * -49900/(c.first.unit.mass/4), 0));


		//Explosions.
			if (explosion)
			{
				activeExplosion = true;
				explosionStart =  30;
				mouseWhenExplosion = glm::vec2(GetMouseX(), GetMouseY());
				float dist = 0.5f*distanceSquared(c.first.unit.position, glm::vec3(GetMouseX(), GetMouseY(), 0));
				phy::PhysicalUnit::applyForce(c.first.unit, glm::vec3(-50000000 / dist * (dir.x), -150000000 / dist * (dir.y), 0));
			}

			//Gravity.
			phy::PhysicalUnit::applyForce(c.first.unit, glm::vec3(0, 10000, 0));

			if (c.first.unit.position.x - *c.first.body.radius <= 0 || c.first.unit.position.x + *c.first.body.radius >= ScreenWidth())
			{
				c.first.unit.velocity.x *= -1.f;
				if (c.first.unit.position.x - *c.first.body.radius <= 0)
					c.first.unit.position.x = *c.first.body.radius;
				else
					c.first.unit.position.x = ScreenWidth() - *c.first.body.radius;
			}

			if (c.first.unit.position.y + *c.first.body.radius >= ScreenHeight())
			{
				c.first.unit.velocity.y *= -1 / 3.f;


				//Friction.
				c.first.unit.velocity.x /= 3;
				//phy::PhysicalUnit::applyForce(c.first.unit, glm::vec3(c.first.unit.velocity.x * -0.05 * c.first.unit.mass, 0, 0));

				//if (c.first.unit.velocity.x < 0.005)
				//	c.first.unit.velocity.x = 0;
				//if (c.first.unit.velocity.y < 0.005)
				//	c.first.unit.velocity.y = 0;

				c.first.unit.position.y = ScreenHeight() - *c.first.body.radius;
			}


			phy::PhysicalUnit::updatePosition(c.first.unit, fElapsedTime);
			*c.first.body.centre = c.first.unit.position;
		}

		//DrawCircle(circleA.unit.position.x, circleA.unit.position.y, *circleA.body.radius, olc::RED);
		//DrawCircle(circleB.unit.position.x, circleB.unit.position.y, *circleB.body.radius, olc::BLUE);

		//if (GetKey(olc::Key::DOWN).bReleased)
		//	phy::PhysicalUnit::applyForce(circleA.unit, glm::vec3(0000, -100000, 0));

		//phy::PhysicalUnit::applyForce(circleA.unit, glm::vec3(0, 5000, fElapsedTime));

		//if ((circleB.unit.position.x - *circleB.body.radius <= 0) || (circleB.unit.position.x + *circleB.body.radius >= ScreenWidth()))
		//{
		//	circleB.unit.velocity *= -1;
		//}
		//phy::PhysicalUnit::updatePosition(circleB.unit, fElapsedTime);

		//if (circleA.unit.position.y + *circleA.body.radius >= ScreenHeight())
		//{
		//	circleA.unit.velocity *= -1/2.f;
		//	//circleA.unit.velocity = glm::vec3(0, 0, 0);
		//	circleA.unit.position.y = ScreenHeight() - *circleA.body.radius;
		//}
		//phy::PhysicalUnit::updatePosition(circleA.unit, fElapsedTime);

		return true;
	}
};

int main()
{
	TestVisually test;
	if (test.Construct(400, 200, 3, 3))
		test.Start();

	return 1;
}