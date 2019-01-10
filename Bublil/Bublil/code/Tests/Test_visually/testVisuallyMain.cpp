#define OLC_PGE_APPLICATION

#include"olc.h"

#include"PHYSICS\physics.h"

#include"LOGGER\logger.h"

#include<vector>

#include<ctime>

#include<cmath>

lg::fout fout;

class TestVisually :public olc::PixelGameEngine
{
public:
	TestVisually()
	{
		sAppName = "Testing visually.";
	}
	~TestVisually()
	{
		fout.logResults("Num jumps: " + std::to_string(sumJumps) + ".\n" 
						"Num Explosions: " + std::to_string(sumExplosions) + ".\n" 
						"Num sucktions: " + std::to_string(sumSucks) + ".\n");

	}
public:
	std::vector<std::pair<phy::PhysicalEntity, olc::Pixel>> circles;

	int size;

	bool jump, explosion;

	int screenMid;

	bool activeExplosion;
	int explosionStart;
	glm::vec2 mouseWhenExplosion;

	bool suck;

	int SCW;
	int SCH;

	int sumExplosions, sumSucks, sumJumps;

	bool OnUserCreate() override
	{
		sumExplosions = 0, sumSucks = 0, sumJumps = 0;
		SCW = ScreenWidth();
		SCH = ScreenHeight();
		suck = false;
		activeExplosion = false;
		explosion = false;
		screenMid = SCW / 2;
		jump = false;
		srand(time(0));
		size = 2500;
		float xPos, yPos;
		int mass;
		// Called once at the start, so create things here
		for (int i = 0; i < size; ++i)
		{
			mass = rand()%10+5;
			xPos = rand() % SCW;//(SCW - 20) / size * i + 20;
			yPos = SCH - mass - 1;
			olc::Pixel colour = getPixelByPosition(glm::vec3(xPos, yPos, 0));
			circles.push_back(
				{
				phy::PhysicalEntity(
								phy::PhysicalUnit(glm::vec3(xPos, yPos, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), mass),
								phy::col::CollisionBody(phy::col::CBT_SPHERE, false, new glm::vec3(xPos, yPos, 0), new float(mass), nullptr, nullptr, nullptr, nullptr)),
				colour
				});
		}


		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override
	{
		FillRect(0, 0, SCW, SCH, olc::BLACK);

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
			{
				sumJumps++;
				fout.logRuntimeEvent("JUMP", "Balls jumped");
				phy::PhysicalUnit::applyForce(c.first.unit, glm::vec3(0000, phy::literals::kilo(-250), 0));
			}
			//Explosions.
			if (explosion)
			{
				sumExplosions++;
				mouseWhenExplosion = glm::vec2(GetMouseX(), GetMouseY());
				fout.logRuntimeEvent("EXPLOSION", "Balls exploaded at (" + std::to_string(mouseWhenExplosion.x) + ',' + std::to_string(mouseWhenExplosion.y) + ')');

				activeExplosion = true;
				explosionStart =  30;
				float dist = 0.5f*phy::distanceSquared(c.first.unit.position, glm::vec3(mouseWhenExplosion.x, mouseWhenExplosion.y, 0));
				glm::vec2 explosionFactor(phy::literals::giga(0.5), phy::literals::giga(1.5));
				phy::PhysicalUnit::applyForce(c.first.unit, glm::vec3(- explosionFactor.x/ dist * (dir.x), - explosionFactor.y/ dist * (dir.y), 0));
			}
			
			//Explosions.
			if (suck)
			{
				sumSucks++;
				glm::vec2 mp(GetMouseX(), GetMouseY());
				fout.logRuntimeEvent("SUCKTION", "Balls sucked in at (" + std::to_string(mp.x) + ',' + std::to_string(mp.y) + ')');
				FillCircle(mp.x, mp.y, 10, olc::GREEN);
				phy::PhysicalUnit::applyForce(c.first.unit, glm::vec3(phy::literals::kilo(100*dir.x), phy::literals::kilo(100*dir.y), 0));
			}

			//Gravity.
			phy::PhysicalUnit::applyForce(c.first.unit, glm::vec3(0, phy::literals::kilo(c.first.unit.mass), 0));

			if (c.first.unit.position.x - *c.first.body.radius <= 0 || c.first.unit.position.x + *c.first.body.radius >= SCW)
			{
				c.first.unit.velocity.x *= -1.f;
				if (c.first.unit.position.x - *c.first.body.radius <= 0)
					c.first.unit.position.x = *c.first.body.radius;
				else
					c.first.unit.position.x = SCW - *c.first.body.radius;
			}
		

			if (c.first.unit.position.y + *c.first.body.radius >= SCH-1)
			{
				c.first.unit.velocity.y *= -1 / 3.f;

				//Friction.
				c.first.unit.velocity.x /= 3;
				//phy::PhysicalUnit::applyForce(c.first.unit, glm::vec3(c.first.unit.velocity.x * -0.05 * c.first.unit.mass, 0, 0));

				//if (c.first.unit.velocity.x < 0.005)
				//	c.first.unit.velocity.x = 0;
				//if (c.first.unit.velocity.y < 0.005)
				//	c.first.unit.velocity.y = 0;
				c.first.unit.position.y = SCH - *c.first.body.radius;
			}

			phy::PhysicalUnit::updatePosition(c.first.unit, fElapsedTime);

		//	if (c.first.unit.position.y + *c.first.body.radius >= SCH - 1)
		//		c.first.unit.position.y = SCH - *c.first.body.radius;


			*c.first.body.centre = c.first.unit.position;
		}
		return true;
	}
	olc::Pixel getPixelByPosition(const glm::vec3 &pos)
	{
		float wf,hf;
		wf = 100 / 255;
		//wf = pos.x / SCW;
		hf = pos.y / SCH*100;
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

	return 0;
}