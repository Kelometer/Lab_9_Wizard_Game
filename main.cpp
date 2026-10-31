#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

// outputs a spell and it's information to the screen
void displaySpellBanner(string spellName, string tier = "novice", int chargeLevel = 1);
// partially displays spell, but manages the math for basePower and multiplier
double castSpell(string spellName = "Light Flashbang", int basePower = 10, double multiplier = 1);
// math for generating the player shield
double calculateShield(double baseShield = 15, double absorptionRate = 0.2);
// increments on true
int registerCombo(bool hitSuccessful);
// displays the mana amount for a skill
void consumeMana(int cost = 5);
// bool that pairs with conditionals for the boss rage mechanic
bool processBossRage(double damageDealt);
// handles the wizard XP system with static and constant integers
int gainWizardXP(int expGained = 25, static int totalXP = 0, static int playerLevel = 1);

// container for attack moves
class spellInfo {
	public:
		string ID;
		string name;
		string tier;
		double basePower;
		double chargeLevel;
};
// container for defensive moves
class defenseInfo {
	public:
		string ID;
		string name;
		string tier;
		double baseShield;
		double absorptionRate;
};

int main() {
	// establishes spells and stats
	spellInfo light0 = { "atk_0","Toxic Mist", "Novice", 15, 1 };
	spellInfo heavy0 = { "atk_1","Whirlwind", "Adept", 20, 2 };
	defenseInfo def0 = { "def_0","Cobalt Barrier", "Novice", 20.0, 0.50 };
	spellInfo miss0 = { "sp_0", "Miss Attack", "Novice", 0, 0 };

	int spellReq,
		expGained = 25;
	double damageDealt = 0,
		damageMitigated;

	static int comboCount = 0.0,
		totalXP = 0,
		wizardLevel = 1;
	static double totalDamageDealt = 0.0;

	char continueBattle = 'y';
	int turn = 1;

	bool validReq = false,
		isBossEnraged = false,
		successfulHit = false;

	cout << "==============================\n"
		<< "Wizard Academy Battle Simulator" 
		<< "\n==============================\n" << endl;

	displaySpellBanner(light0.name, light0.tier, light0.chargeLevel);
	displaySpellBanner(heavy0.name, heavy0.tier, heavy0.chargeLevel);
	displaySpellBanner(def0.name, def0.tier, 1);
	displaySpellBanner(miss0.name, miss0.tier, miss0.chargeLevel);

	cout << "\nPick an option from 1 to 4" << endl;

	while (continueBattle == 'y') {
		validReq = false;
		cout << "Enter: ";

		while (!validReq) {
			if (cin >> spellReq) {
				if (spellReq >= 1 && spellReq <= 4) {
					validReq = true;
				}
				else {
					cout << "Please enter a value between 1 and 4." << endl;
				}
				// avoids a weird buffer error
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			else {
				// activates on string input
				cout << "Invalid input, please enter an integer between 1 and 4." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}

		switch (spellReq) {
		case 1:
			consumeMana();
			damageDealt = castSpell(light0.name, light0.basePower);
			successfulHit = true;
			break;
		case 2:
			consumeMana(15);
			damageDealt = castSpell(heavy0.name, heavy0.basePower, 2);
			successfulHit = true;
			break;
		case 3:
			consumeMana(8);
			damageMitigated = calculateShield(def0.baseShield, def0.absorptionRate);
			successfulHit = true;
			break;
		case 4:
			cout << "Your attack missed completely!\n" << endl;
			successfulHit = false;
			break;
		}
		totalDamageDealt += damageDealt;

		if (successfulHit) {
			comboCount += registerCombo(successfulHit);
			expGained = gainWizardXP(30,totalXP,wizardLevel);
		}
		else {
			cout <<"Lost Combo!" << endl;
			comboCount = 1;
		}
		cout << "Current Combo Streak: " << comboCount << "x" << endl;

		gainWizardXP(expGained,totalXP,wizardLevel);
		isBossEnraged = processBossRage(totalDamageDealt);

		if (isBossEnraged) {
			cout << "\n!!! WARNING: THE BOSS IS ENRAGED !!!\n" << endl;
		}

		turn++;

		cout << "End turn? or Continue Fighting? (y/n) : ";
		cin >> continueBattle;
		continueBattle = tolower(continueBattle);
		cout << endl;
	}
	cout << "=======================\n"
		<< "Wizard Battle Sim Over!"
		<< "\n=======================\n" << endl;;
	return 0;
}

void displaySpellBanner(string spellName, string tier, int chargeLevel ) {
	cout << left << setw(6) << "Cast:" << setw(15) << spellName << setw(9) << "|| Tier:" 
		<< setw(8) << tier << setw(11) << "|| Charge Lvl: " << chargeLevel << endl;
}
double castSpell(string spellName, int basePower, double multiplier) {
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
int registerCombo(bool hitSuccessful) {
	if (hitSuccessful)
		return 1;
	else
		return 0;
}
void consumeMana(int cost) {
	cout << "-" << cost << " mana!" << endl;
}
bool processBossRage(double damageDealt) {
	if (damageDealt >= 100.0) {
		return true;
	}
	else
		return false;
}
int gainWizardXP(int expGained, static int totalXP, static int playerLevel) {
	totalXP += expGained;
	if (totalXP >= playerLevel * 100) {
		playerLevel++;
		cout << "\nYou leveled up!\nNew Wizard Level = " << playerLevel;
	}
	return playerLevel;
}
