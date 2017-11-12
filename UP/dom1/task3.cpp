#include <iostream>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main() {
	const int DEF_P_HEALTH = 100;
	int p_health = DEF_P_HEALTH;
	const int DEF_P_DAMAGE = 10;
	int p_damage = DEF_P_DAMAGE;
	const int DEF_P_ARMOR = 25;
	int p_armor = DEF_P_ARMOR;
	const int DEF_P_LUCK = 5;
	int p_luck = DEF_P_LUCK;
	const int DEF_POTION = 5;
	int magic_potion = DEF_POTION;

	const int DEF_M_HEALTH = 50;
	int m_health = DEF_M_HEALTH;
	const int DEF_M_DAMAGE = 5;
	int m_damage = DEF_M_DAMAGE;
	const int DEF_M_ARMOR = 5;
	int m_armor = DEF_M_ARMOR;
	const int DEF_M_LUCK = 0;
	int m_luck = DEF_M_LUCK;
	const int DEF_M_LEVEL = 0;
	int m_level = DEF_M_LEVEL;

	int skill_points = 0;
	int health_skill_points = 0;
	int damage_skill_points = 0;
	int armor_skill_points = 0;
	int luck_skill_points = 0;
	int token = 0;

	float curr_p_damage;
	float curr_m_damage;
	bool m_attack = false;
	cout << "Welcome to the epic game for knights and monsters in the wonderful world!!!!" << endl;
	cout << "Trantantaaaaaaa" << endl;

	while(true) {
		cout << "----------------------------------------" << endl;
		cout << "What is your choise?" << endl;
		cout << "[i]nformation" << endl;
		cout << "[a]ttack" << endl;
		cout << "[d]efence" << endl;
		cout << "[p]otion" << endl;
		cout << "e[x]it" << endl;

		srand(time(NULL));
		float p_chance_percentage = p_luck*0.5;
		bool p_hit_crit = ((rand()%100 + 1) <= (int)p_chance_percentage) ? true : false;
		bool p_success_defence = ((rand()%100 + 1) <= (int)p_chance_percentage) ? true : false;

		float m_chance_percentage = m_luck*0.5;
		bool m_hit_crit = ((rand()%100 + 1) <= (int)m_chance_percentage) ? true : false;
		bool m_success_defence = ((rand()%100 + 1) <= (int)m_chance_percentage) ? true : false;

		int m_option = rand()%2;
		bool drop_magic_potion = (rand()%2) ? true : false;

		switch(m_option) {
			case 0: // Mosnter attack
				curr_m_damage = m_damage-(m_damage*(((p_armor/10)*5)/(float)100));
				if (m_hit_crit) {
					curr_m_damage*=2;
				}
				m_attack = true;
				break;
			case 1: // Monster defence
				curr_m_damage = 0;
				m_attack = false;
				break;

		}
		char option;

		while (true) {		
			cin >> option;
			if (option == 'i' || option == 'a' || option == 'd' || option == 'p' || option == 'x') {
				break;
			} else {
				cout << "Are you drunk? No battle with monsters for drunk knight! GO 127.0.0.1" << endl;
			}
		}
		
		for (int i = 0; i < 20; i++) { cout << endl; }
		
		switch(tolower(option)) {	
			case 'i': {
				curr_m_damage = 0;
				curr_p_damage = 0;
				cout << "Player health: " << p_health << endl <<
				 		"Player damage: " << p_damage << endl <<
						"Player armor: " << p_armor << endl <<
						"Player luck: " << p_luck << endl <<
						"Potion: " << magic_potion << endl << endl;
				
				cout << "Monster level: " << m_level << endl <<
						"Monster health: " << m_health << endl <<
				 		"Monster damage: " << m_damage << endl <<
						"Monster armor: " << m_armor << endl <<
						"Monster luck: " << m_luck << endl;

				break;
			}
			case 'a': {
				cout << "Player attack the monster!" << endl;
				curr_p_damage = p_damage-(p_damage*(((m_armor/10)*5)/(float)100));
				if (p_hit_crit) {
					curr_p_damage*=2;
				}	
				break;
			}
			case 'd': { // Player defence
				curr_p_damage = 0;
				if (p_success_defence) {
					curr_m_damage = 0;
					cout << "Player defence successfully from monster!" << endl;
				} else {
					curr_m_damage /= 2;
					cout << "Player defence from monster!" << endl;
				}
				break;
			}
			case 'p': {
				curr_p_damage = 0;
				if (magic_potion > 0) {
					p_health = DEF_P_HEALTH + health_skill_points;
					cout << "Congratulations! Your health is up to max!" << endl;
				} else {
					cout << "Sorry, you don't have any magic potion for drink :/" << endl;
				}
				break;
			}
			case 'x': {
				cout << "Are you sure to want to exit?[y/n]" << endl;
				char exit_option;
				while (true) {
					cin >> exit_option;
					if (exit_option == 'y') {
						cout << "GOODBYE!" << endl;
						return 0;
					} else if (exit_option == 'n') {
						cout << "I know you want to play :)" << endl;
						break;
					} else {
						cout << "Are you sure to want to exit?[y/n]" << endl;
					}
				}
				break;
			}
		}

		if(option != 'i') {
			if (!m_attack) {
				if (m_success_defence) {
					curr_p_damage = 0;
					cout << "Moster defence seccessfully!" << endl;
				} else {
					curr_p_damage/=2;
					cout << "Monster defence!" << endl;
				}
			} else {
				cout << "Monster attack!" << endl;
			}
			m_health -= (int)curr_p_damage;
			p_health -= (int)curr_m_damage;
			if (p_health > 0 && m_health > 0) {		
				cout << "Player health: " << p_health << endl <<
					 	"Player damage on monster: " << (int)curr_p_damage << endl << endl << 
						"Monster health: " << m_health << endl <<
						"Monster damage on player: " << (int)curr_m_damage << endl << endl;
			} else {
				if (p_health <= 0) {
					cout << "You're dead!" << endl;
					cout << "You have " << token << "token for free game!" << endl;
					cout << "Do you want to play again?[y/n]" << endl;
							
					char play_again_option;
					while (true) {
						cin >> play_again_option;
						tolower(play_again_option);
						if (play_again_option == 'n') {
							cout << "GOODBYE! :)" << endl;
							return 0;
						} else if (play_again_option == 'y') {
							if (token > 0) {
								cout << "I know you want to play :)" << endl;
								token--;
							
								p_health = DEF_P_HEALTH;
								p_damage = DEF_P_DAMAGE;
								p_armor = DEF_P_ARMOR;
								p_luck = DEF_P_LUCK;
								magic_potion = DEF_POTION;

								m_health = DEF_M_HEALTH;
								m_damage = DEF_M_DAMAGE;
								m_armor = DEF_M_ARMOR;
								m_luck = DEF_M_LUCK;
								m_level = DEF_M_LEVEL;

								skill_points = 0;
								health_skill_points = 0;
								damage_skill_points = 0;
								armor_skill_points = 0;
								luck_skill_points = 0;
								break;
							} else {
								cout << "You don't have token for free game :( Sorry" << endl;
							}
						} else {
							cout << "Do you want to play again?[y/n]" << endl;
						}
					}
				} else if (m_health <= 0) {
					cout << "Monster is dead! You have 5 skill points!" << endl;
					m_level++;	
					if (m_level%5 == 0) {
						token++;
					}
					if (drop_magic_potion) {
						magic_potion++;
					}
					skill_points = 5;
					while (skill_points > 0) {
						for (int i = 0; i < 20; i++) { cout << endl; }
						cout << "Skill points left: " << skill_points << endl;
						cout << "Which indicator you want to boost?" << endl;
						cout << "[h]ealth: " << health_skill_points << endl;
						cout << "[d]amage: " << damage_skill_points << endl;
						cout << "[a]rmor: " << armor_skill_points << endl;
						cout << "[l]uck: " << luck_skill_points << endl;

						char indicator;
						while (true) {		
							cin >> indicator;
							tolower(indicator);
							if (indicator == 'h' || indicator == 'd' || indicator == 'a' || indicator == 'l') {
								break;
							} else {
								cout << "I don't know what skill you want to boost :/" << endl;
							}
						}

						switch(tolower(indicator)) {
							case 'h':
								health_skill_points++;
								break;
							case 'd':
								damage_skill_points++;
								break;
							case 'a':
								armor_skill_points++;
								break;
							case 'l':
								luck_skill_points++;
								break;
						}
						skill_points--;
					}
					p_health = DEF_P_HEALTH + health_skill_points;
					p_damage = DEF_P_DAMAGE + damage_skill_points;
					p_armor = DEF_P_ARMOR + armor_skill_points;
					p_luck = DEF_P_LUCK + luck_skill_points;
					m_health = DEF_M_HEALTH + (m_level*2);
					m_damage = DEF_M_DAMAGE + (m_level*2);
					m_armor = DEF_M_ARMOR + (m_level*2);
					m_luck = DEF_M_LUCK + (m_level*2);
				}
			}
		}
	}

	return 0;
}

