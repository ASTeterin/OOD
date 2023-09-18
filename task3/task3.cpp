#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

using Strategy = function<void()>;

class Duck
{
public:
	Duck(Strategy&& flyBehavior,
		Strategy&& quackBehavior,
		Strategy&& danceBehavior) : m_quackBehavior(quackBehavior)
		, m_danceBehavior(danceBehavior)
	{
		assert(quackBehavior);
		assert(danceBehavior);
		SetFlyBehavior(flyBehavior);
	}
	void Quack() const
	{
		m_quackBehavior();
	}
	void Fly() const
	{
		m_flyBehavior();
	}
	void Dance() const
	{
		m_danceBehavior();
	}
	void SetFlyBehavior(Strategy& flyBehavior)
	{
		assert(flyBehavior);
		m_flyBehavior = flyBehavior;
	}

	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	Strategy m_flyBehavior;
	Strategy m_quackBehavior;
	Strategy m_danceBehavior;
};

void FlyWithWings()
{
	cout << "I'm flying with wings" << endl;
}

void FlyNoWay() 
{}

void QuackBehavior()
{
	cout << "Quack Quack!" << endl;
};

void DanceTheWaltz()
{
	cout << "I'm dancing waltz!" << endl;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(FlyWithWings, QuackBehavior, DanceTheWaltz)
	{}

	void Display() const override
	{
		cout << "I'm mallard duck!" << endl;
	}
};

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck& duck)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Fly();
	duck.Dance();
	cout << endl;
}

int main()
{
	MallardDuck mallardDuck;
	PlayWithDuck(mallardDuck);
	PlayWithDuck(mallardDuck);
}
