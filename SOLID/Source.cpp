#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<string>
#include<chrono>
class Reload
{
public:
	Reload(std::int32_t period):period(period){}
	Reload() {};
protected:
	virtual void reload() = 0;
	std::int32_t period = 0;
};
class Atack
{
public:
	Atack(std::int32_t damage, std::int32_t delay_between_shots) : damage(damage), delay_between_shots(delay_between_shots){};
	Atack() {};
protected:
	virtual void atack() = 0;
	std::int32_t damage = 0;
	std::int32_t delay_between_shots=0;	
};
class MeleeWeapons: public Atack
{
protected:
	MeleeWeapons(std::int32_t damage,std::int32_t delay_between_shots) :Atack(damage, delay_between_shots) {}
	MeleeWeapons() {};
	friend class Entity;
};
class Punch:public MeleeWeapons
{
public:
	Punch():MeleeWeapons(5,200){}
protected:
	void atack() override
	{
		std::cout << "On punch: -" << this->damage << "\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(this->delay_between_shots));
	}
};
class Knif:public MeleeWeapons
{
public:
	Knif(std::int32_t damage,std::int32_t delay_between_shots) :MeleeWeapons(damage, delay_between_shots) {}
protected:
	void atack() override
	{
		std::cout << "Knif Atack: -" << this->damage << "\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(this->delay_between_shots));
	}
};

class Gun: public Reload,public Atack
{
public:
	Gun(std::int32_t total_bulet, std::int32_t bullet_serise,std::int32_t damage, std::int32_t reload,std::int32_t delay_between_shots) :Reload(reload),Atack(damage, delay_between_shots), total_bulet(total_bulet), bullet_serise(bullet_serise), bullet_serise_copy(bullet_serise){};
	Gun() {};
protected:
	void reload() override 
	{
		if((this->bullet_serise_copy-this->bullet_serise>0)&&this->total_bulet!=0)
		{
			std::int32_t temporar = this->bullet_serise_copy - this->bullet_serise;
			this->total_bulet -= temporar;
			this->bullet_serise += temporar;
			std::this_thread::sleep_for(std::chrono::milliseconds(this->period));
			std::cout << "Reloaded Successfully\n";
			std::cout << "Total Bullets: " << this->total_bulet << "\n";
		}
	}
	std::int32_t bullet_serise_copy=0;
	std::int32_t bullet_serise=0;
	std::int32_t total_bulet=0;
	friend class Entity;
};
class Handguns: public Gun
{
public:
	Handguns(std::int32_t total_bulet, std::int32_t bullet_serise, std::int32_t damage, std::int32_t reload,std::int32_t delay_between_shots) :Gun(total_bulet, bullet_serise, damage, reload, delay_between_shots) {}
	void atack() override
	{
		if (this->bullet_serise > 0 && this->total_bulet > 0) {
			std::cout << "Atack with Hangun: -" << this->damage << "\n";
			this->bullet_serise--;
			std::cout << "Bulets: " << this->bullet_serise << "\n";
			std::this_thread::sleep_for(std::chrono::milliseconds(this->delay_between_shots));
		}
		if (this->bullet_serise == 0)
		{
			this->reload();
		}
	}

};
class Shotgun:public Gun
{
public:
	Shotgun(std::int32_t total_bulet, std::int32_t bullet_serise, std::int32_t damage, std::int32_t reload,std::int32_t delay_between_shots) :Gun(total_bulet, bullet_serise, damage, reload, delay_between_shots) {}
	void atack() override
	{
		if (this->bullet_serise > 0 && this->total_bulet > 0) {
			this->bullet_serise--;
			std::cout << "Atack with Shotgun: -" << this->damage << "\n";
			std::cout << "Bulets: " << this->bullet_serise << "\n";
			std::this_thread::sleep_for(std::chrono::milliseconds(this->delay_between_shots));
		}
		if (this->bullet_serise == 0)
		{
			this->reload();
		}
	}
};
class Sniper:public Gun
{
public:
	Sniper(std::int32_t total_bulet, std::int32_t bullet_serise, std::int32_t damage, std::int32_t reload,std::int32_t delay_between_shots) :Gun(total_bulet, bullet_serise, damage, reload, delay_between_shots) {}
	void atack() override
	{
		if (this->bullet_serise > 0 && this->total_bulet > 0) {
			std::cout << "Atack with Sniper: -" << this->damage << "\n";
			this->bullet_serise--;
			std::cout << "Bulets: " << this->bullet_serise << "\n";
			std::this_thread::sleep_for(std::chrono::milliseconds(this->delay_between_shots));
		}
		if (this->bullet_serise == 0)
		{
			this->reload();
		}
	}
};
class Assault_Rifles:public Gun
{
public:
	Assault_Rifles(std::int32_t total_bulet, std::int32_t bullet_serise, std::int32_t damage, std::int32_t reload,std::int32_t delay_between_shots) :Gun(total_bulet, bullet_serise, damage, reload, delay_between_shots) {}
	void atack() override
	{
		if (this->bullet_serise > 0 && this->total_bulet > 0) {
			std::cout << "Atack with Assault_Rifles: -" << this->damage << "\n";
			this->bullet_serise--;
			std::cout << "Bulets: " << this->bullet_serise << "\n";
			std::this_thread::sleep_for(std::chrono::milliseconds(this->delay_between_shots));
		}
		if (this->bullet_serise == 0)
		{
			this->reload();
		}
	}
};
class PickUpWeapon
{
protected:
	PickUpWeapon() :first_gun(nullptr),second_gun(nullptr),melle_weapon(new Punch) {};
	void pick_up_first_gun(Gun* pick_up_gun)
	{
		
		if (typeid(*pick_up_gun) != typeid(Handguns) && typeid(*pick_up_gun) != typeid(MeleeWeapons) && this->first_gun == nullptr )
		{
			this->first_gun = pick_up_gun;
			std::cout << "first gun raised\n";
		}
		else
		{
			std::cout << "Can't rise gun\n";
			
		}
	}
	void pick_up_second_gun(Gun* pick_up_gun)
	{
		if( typeid(*pick_up_gun) == typeid(Handguns) && this->second_gun == nullptr )
		{
			this->second_gun = pick_up_gun;
			std::cout << "Second gun raised\n";
		}
		else
		{
			std::cout << "Can't rise gun\n";
		}
	}
	void pick_up_knif(MeleeWeapons* knif)
	{
		if ( typeid(*this->melle_weapon) == typeid(Punch) )
			delete this->melle_weapon;
		this->melle_weapon = knif;
		std::cout << "Knife raised\n";
	}
	Gun* first_gun;
	Gun* second_gun;
	MeleeWeapons* melle_weapon;
};
class ChangeWapon : public PickUpWeapon
{
public: 
	ChangeWapon() :select_gun(nullptr) {};
protected:
	void select_weapon(int selector)
	{
		if (selector == 1)
		{
			if (this->first_gun != nullptr) {
				this->select_gun = this->first_gun;
				std::cout << "Has been selected first gun\n";
			}
			else
			{
				std::cout << "don't have a first gun\n";
			}
		}
		if (selector == 2)
		{
			if (this->second_gun != nullptr) {
				this->select_gun = this->second_gun;
				std::cout << "Has been selected second gun\n";
			}
			else
			{
				std::cout << "don't have a second gun\n";
			}
		}
	}
	Gun* select_gun;
};

class DropAngPickUpWapon : public ChangeWapon
{
protected:
	void drop_gun()
	{
		if(this->select_gun == this->first_gun && this->select_gun != nullptr)
		{
			this->first_gun = nullptr;
			if(this->second_gun != nullptr)
			{
				this->select_gun = this->second_gun;
			}
			else
			{
				this->select_gun = nullptr;
			}
			std::cout << "Thrown first gun\n";
			return;
		}
		if (this->select_gun == this->second_gun && this->select_gun != nullptr)
		{
			this->second_gun = nullptr;
			if (this->first_gun != nullptr)
			{
				this->select_gun = this->first_gun;
			}
			else
			{
				this->select_gun = nullptr;
			}
			std::cout << "Thrown second gun\n";
			return;
		}
	}
	void drop_knif()
	{
		if(typeid(*this->melle_weapon) == typeid(Knif) )
		{
			this->melle_weapon = new Punch;
			std::cout << "Thrown knif\n";
		}
	}
};

class Move
{
protected:
	Move():move_forward_velocity(20),move_back_velocity(15), move_left_right_velocity(10){}
	void move_forward()
	{
		std::cout << "Move forward: " << this->move_forward_velocity << "\n";
	}
	void move_back()
	{
		std::cout << "Move back: " << this->move_back_velocity << "\n";
	}
	void move_left()
	{
		std::cout << "Move left: "<<this->move_left_right_velocity <<"\n";
	}
	void move_right()
	{
		std::cout << "Move right: "<<this->move_left_right_velocity <<"\n";
	}
private:
	std::int32_t move_forward_velocity;
	std::int32_t move_back_velocity;
	std::int32_t move_left_right_velocity;
};
class Entity :public DropAngPickUpWapon, public Move
{
public:
	void atack()
	{
		if (DropAngPickUpWapon::select_gun != nullptr) {
			DropAngPickUpWapon::select_gun->atack();
		}
	}
	void atack_melee_weapon()
	{
		DropAngPickUpWapon::melle_weapon->atack();
	}
	void chamge_weapon(std::int32_t i)
	{
		DropAngPickUpWapon::select_weapon(i);
	}
	void reload()
	{
		DropAngPickUpWapon::first_gun->reload();
	}
	void pick_up_first_gun(Gun *gun)
	{
		DropAngPickUpWapon::pick_up_first_gun(gun);
	}
	void pick_up_second_gun(Gun* gun)
	{

		DropAngPickUpWapon::pick_up_second_gun(gun);
	}
	void pick_up_knif(MeleeWeapons*wapom)
	{
		DropAngPickUpWapon::pick_up_knif(wapom);
	}
	void drop_gun()
	{
		DropAngPickUpWapon::drop_gun();
	}
	void drop_knif()
	{
		DropAngPickUpWapon::drop_knif();	
	}
	void move_forward()
	{
		Move::move_forward();
	}
	void move_back()
	{
		Move::move_back();
	}
	void move_left()
	{
		Move::move_left();
	}
	void move_right()
	{
		Move::move_right();
	}
};

int main()
{
	Entity en;
	Gun* Glock = new Handguns(21, 7, 15, 1500, 200);
	Gun* Kinber = new Handguns(27, 7, 15, 2000, 200);
	Gun* Winchester = new Shotgun(14, 3, 50, 5000, 400);
	Gun* SakoTRG = new Sniper(5, 15, 100, 3000, 600);
	Gun* Ak47 = new Assault_Rifles(90, 30, 25, 2000, 100);
	
} 