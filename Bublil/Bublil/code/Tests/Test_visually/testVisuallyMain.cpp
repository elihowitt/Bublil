#define OLC_PGE_APPLICATION

#include"olc.h"

#include"PHYSICS\physics.h"

#include"LOGGER\logger.h"

#include<vector>

#include<ctime>

#include<cmath>

using namespace phy::literals;

class TestVisually :public olc::PixelGameEngine
{
public:
	TestVisually()
	{
		sAppName = "Testing visually.";
	}
public:
	std::vector<std::pair<phy::PhysicalEntity, olc::Pixel>> circles;

	int size;

	olc::Pixel colours[10]{ olc::RED, olc::DARK_RED, olc::GREEN, olc::DARK_GREEN, olc::BLUE, olc::DARK_BLUE, olc::YELLOW, olc::DARK_YELLOW, olc::MAGENTA, olc::DARK_MAGENTA };

	bool jump, explosion;

	int screenMid;

	bool activeExplosion;
	int explosionStart;
	glm::vec2 mouseWhenExplosion;

	bool suck;

	bool OnUserCreate() override
	{
		suck = false;
		activeExplosion = false;
		explosion = false;
		screenMid = ScreenWidth() / 2;
		jump = false;
		srand(time(0));
		size = 10;
		float xPos, yPos;
		int mass;
		// Called once at the start, so create things here
		for (int i = 0; i < size; ++i)
		{
			mass = rand() % 46 + 5;
			xPos = (ScreenWidth() - 20) / size * i + 20;
			yPos = ScreenHeight() - mass - 1;
			olc::Pixel colour = getPixelByPosition(glm::vec3(xPos, yPos, 0));
			circles.push_back(
				{
				phy::PhysicalEntity(
								phy::PhysicalUnit(glm::vec3(xPos, yPos, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), mass),
								phy::col::CollisionBody(phy::col::CBT_SPHERE, false, new glm::vec3(xPos, yPos, 0), new float(mass), nullptr, nullptr, nullptr, nullptr)),
				colour
				//colours[(int)((10 * i / size) * 3.5) % 10]
				});
		}

		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override
	{
		FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::BLACK);

		if (GetKey(olc::Key::UP).bReleased)
			jump = true;
		else jump = false;

		if (GetMouse(0).bReleased)
			explosion = true;
		else explosion = false;

		if (GetMouse(1).bHeld)
			suck = true;
		else suck = false;

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
				phy::PhysicalUnit::applyForce(c.first.unit, glm::vec3(0000, kilo(-250), 0));

		//Explosions.
			if (explosion)
			{
				//typedef giga giga
				//#define giga giga
				activeExplosion = true;
				explosionStart =  30;
				mouseWhenExplosion = glm::vec2(GetMouseX(), GetMouseY());
				float dist = 0.5f*phy::distanceSquared(c.first.unit.position, glm::vec3(GetMouseX(), GetMouseY(), 0));
				glm::vec2 explosionFactor(giga(0.5), giga(1.5));
				phy::PhysicalUnit::applyForce(c.first.unit, glm::vec3(- explosionFactor.x/ dist * (dir.x), - explosionFactor.y/ dist * (dir.y), 0));
			}
			
			//Explosions.
			if (suck)
			{
				FillCircle(GetMouseX(), GetMouseY(), 10, olc::GREEN);
				phy::PhysicalUnit::applyForce(c.first.unit, glm::vec3(kilo(100*dir.x), kilo(100*dir.y), 0));
			}

			//Gravity.
			phy::PhysicalUnit::applyForce(c.first.unit, glm::vec3(0, kilo(c.first.unit.mass), 0));

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
		return true;
	}
	olc::Pixel getPixelByPosition(const glm::vec3 &pos)
	{
		float wf,hf;
		wf = 100 / 255;
		//wf = pos.x / ScreenWidth();
		hf = pos.y / ScreenHeight()*100;
		//wf = cos(pos.x) > 0 ? cos(pos.x) : cos(pos.x);
		return olc::Pixel(rand() % 255, rand() % 255, rand() % 255);
		//return olc::Pixel(wf*255, hf*255, 100);
	}
};

int main()
{
	TestVisually test;
	if (test.Construct(1200, 600, 1, 1))
		test.Start();

	return 1;
}