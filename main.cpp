#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

void displaySpellBanner(string spellName, string tier, int chargeLevel);
double castSpell(string spellName, int basePower, double multiplier);
double calculateShield(double baseShield, double absorptionRate);

class spellInfo {
	public:
		string ID;
		string name;
		string tier;
		double basePower;
		double chargeLevel;
};
class defenseInfo {
	public:
		string ID;
		string name;
		string tier;
		double baseShield;
		double absorptionRate;
};

int main() {
	spellInfo light0 = { "atk_0","Toxic Mist", "Novice", 15, 1 };
	spellInfo heavy0 = { "atk_1","Whirlwind", "Adept", 35, 1 };
	defenseInfo def0 = { "def_0","Cobalt Barrier", "Novice", 20.0, 0.50 };
	spellInfo miss0 = { "sp_0", "Miss Attack", "Novice", 0, 0 };

	int spellReq;
	double damageDealt, damageMitigated;
	bool running = true,
		validReq = false;

	cout << string('*', 30) << "\nWizard Academy Simulator\n" << string('*', 30) << endl;

	displaySpellBanner(light0.name, light0.tier, light0.chargeLevel);
	displaySpellBanner(heavy0.name, heavy0.tier, heavy0.chargeLevel);
	displaySpellBanner(def0.name, def0.tier, 1);
	displaySpellBanner(miss0.name, miss0.tier, miss0.chargeLevel);

	cout << string('-', 20) << endl;

	cout << "Pick an option from 1 to 4" << endl;
	while (running) {
		validReq = false;
		cout << "Enter: ";
		while (!validReq) {
			if (cin >> spellReq) {
				if (spellReq >= 1&& spellReq <= 4) {
					validReq = true;
				}
				else {
					cout << "Please enter a value between 1 and 4." << endl;
				}

				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			else {
				cout << "Invalid input, please enter an integer between 1 and 4." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}

		switch (spellReq) {
		case 1:
			damageDealt = castSpell(light0.name, light0.basePower, light0.chargeLevel);
			break;
		case 2:
			damageDealt = castSpell(heavy0.name, heavy0.basePower, heavy0.chargeLevel);
			break;
		case 3:
			damageMitigated = calculateShield(def0.baseShield, def0.absorptionRate);
			break;
		case 4:
			damageDealt = castSpell(miss0.name, miss0.basePower, miss0.chargeLevel);
			break;
		}
				
	}
	return 0;
}

void displaySpellBanner(string spellName, string tier = "Novice", int chargeLevel = 1) {
	cout << left << setw(6) << "Cast:" << setw(15) << spellName << setw(9) << "|| Tier:" 
		<< setw(8) << tier << setw(11) << "|| Charge Lvl: " << chargeLevel << endl;
}


double castSpell(string spellName, int basePower, double multiplier = 1) {
	double damage = basePower * multiplier;

	cout << "You chose: " << spellName << "!" << endl;
	cout << "It did " << damage << " damage.\n" << endl;

	return damage;
}

double calculateShield(double baseShield, double absorptionRate) {
	double shield = baseShield * (1 + absorptionRate);
	
	cout << "You put up a shield!" << endl;
	cout << "You mitigated " << shield << " damage.\n" << endl;

	return shield;
}
