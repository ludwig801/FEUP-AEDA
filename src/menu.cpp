/*
// * menu.cpp
 *
 *  Created on: 31 de Out de 2013
 *      Author: ei12054
 */

#include "menu.h"

#define foreach(v,it)	for(typeof((v).begin()) it = v.begin(); it != v.end(); ++it)
#define BORDER_SIZE	70

/**
 * Main Menu options bar.
 */
enum mainOptions {
	VER,
	CRIAR,
	PROCURAR,
	SIMULAR,
};

/**
 * Struct containing the keycode for pressed keys.
 */
struct keys {
	const static size_t esc = 27;			/**< Esc key code. */
	const static size_t backspace = 8; 		/**< Backspace key code. */
	const static size_t enter = 13;			/**< Enter key code. */

	const static size_t arrow = 224;		/**< Arrow key code. */
	const static size_t left = 75;			/**< Left arrow key code. */
	const static size_t right = 77;			/**< Right arrow key code. */
	const static size_t up = 72;			/**< Up arrow key code. */
	const static size_t down = 80;			/**< Down arrow key code. */

	const static size_t number0 = 48;		/**< Down arrow key code. */
	const static size_t number1 = 49;		/**< Down arrow key code. */
	const static size_t number2 = 50;		/**< Down arrow key code. */
	const static size_t number3 = 51;		/**< Down arrow key code. */
	const static size_t number4 = 52;		/**< Down arrow key code. */
	const static size_t number5 = 53;		/**< Down arrow key code. */
	const static size_t number6 = 54;		/**< Down arrow key code. */
	const static size_t number7 = 55;		/**< Down arrow key code. */
	const static size_t number8 = 56;		/**< Down arrow key code. */
	const static size_t number9 = 57;		/**< Down arrow key code. */

} key;

/**
 * Struct containing the maps associated with options - these maps are inicialized in OptionsInit().
 */
struct opcoes {
	map<size_t,string> mainOpt;				/**< Main menu options. */
	map<size_t,vector<string> > subOpt;		/**< Sub-menus options. */
} opcao;

/**
 * Struct containing the vector associated with professions - this vector is inicialized in ProfessInit().
 */
struct profissoes {
	vector<string> profs;					/**< Possible professions. */
} profissao;

/**
 *  Struct containing the colors used in the console.
 *  COLORS ARE CODIFIED:
 *
 *	 bit 7: BACKGROUND INTENSITY
 *	 bit 6: BACKGROUND RED
 *	 bit 5: BACKGROUND GREEN
 *	 bit 4: BACKGROUND BLUE
 *
 *	 bit 3: FOREGROUND INTENSITY
 *	 bit 2: FOREGROUND RED
 *	 bit 1: FOREGROUND GREEN
 *	 bit 0: FOREGROUND BLUE
 *
 */
struct colors {

	const static int GOLD_BLACK = 0x06;		/**< 0000 0110 */
	const static int WHITE_BLACK = 0xF;		/**< 0000 1111 */
	const static int GREY_BLACK = 0x07;		/**< 0000 0111 */
	const static int GREYER_BLACK = 0x08;	/**< 0000 1000 */
	const static int RED_BLACK = 0x0C;		/**< 0000 1100 */
	const static int RED_GREY = 0x04;		/**< 0000 0100 */
} color;

/* 								AUXILIAR									*/
void OptionsInit() {
	opcao.mainOpt[VER] = "VER";
	opcao.mainOpt[CRIAR] = "CRIAR";
	opcao.mainOpt[PROCURAR] = "PROCURAR";
	opcao.mainOpt[SIMULAR] = "SIMULAR";

	opcao.subOpt[VER].push_back("Empresa");
	opcao.subOpt[VER].push_back("Tecnicos");
	opcao.subOpt[VER].push_back("Proprietarios");
	opcao.subOpt[VER].push_back("Condominios");
	opcao.subOpt[VER].push_back("Condominios Antigos");
	opcao.subOpt[VER].push_back("Propriedades");
	opcao.subOpt[VER].push_back("Inspeccoes Externas");
	opcao.subOpt[VER].push_back("Reservas do Salao de Eventos");

	opcao.subOpt[CRIAR].push_back("Tecnico");
	opcao.subOpt[CRIAR].push_back("Proprietario");
	opcao.subOpt[CRIAR].push_back("Condominio");
	opcao.subOpt[CRIAR].push_back("Propriedade");
	opcao.subOpt[CRIAR].push_back("Contrato");
	opcao.subOpt[CRIAR].push_back("Inspeccao Externa");

	opcao.subOpt[PROCURAR].push_back("Tecnicos");
	opcao.subOpt[PROCURAR].push_back("Proprietarios");
	opcao.subOpt[PROCURAR].push_back("Propriedades");

	opcao.subOpt[SIMULAR].push_back("Mes");
	opcao.subOpt[SIMULAR].push_back("Semestre");
	opcao.subOpt[SIMULAR].push_back("Ano");

}

void ProfessInit() {
	profissao.profs.push_back("Alvenaria");
	profissao.profs.push_back("Eletricista");
	profissao.profs.push_back("Infra-estruturas");
	profissao.profs.push_back("Espacos Comuns");
	profissao.profs.push_back("Pintura");
	profissao.profs.push_back("Limpeza");
}

void ScreenInit() {

	changeTextColor(color.GREY_BLACK);
	removeCursor();
	clearScreen();
}

size_t coutUPDATE(const size_t subOP) {
	cout << endl;
	cout << "  Escolha a opcao premindo o numero correspondente no teclado.";
	cout << endl << endl;
	switch(subOP) {
	case 0:
		// Empresa
		cout << EDIT_NAME_1 << endl;
		cout << EDIT_BALANCE_2 << endl;
		cout << RESET_DATE_3 << endl;
		break;
	case 1:
		// Tecnicos
		cout << EDIT_NAME_1 << endl;
		cout << EDIT_PROFESSION_2 << endl;
		cout << EDIT_SALARY_3 << endl;
		changeTextColor(color.RED_BLACK);
		cout << REMOVE_TECH_4 << endl;
		changeTextColor(color.GREY_BLACK);
		break;
	case 2:
		// Proprietarios
		cout << EDIT_NAME_1 << endl;
		changeTextColor(color.RED_BLACK);
		cout << REMOVE_OWNER_2 << endl;
		changeTextColor(color.GOLD_BLACK);
		cout << REMOVE_ALL_CONTRACTS << endl;
		changeTextColor(color.GREY_BLACK);
		break;
	case 3:
		// Condominios
		cout << REMOVE_PROPERTIES_1 << endl;
		changeTextColor(color.GOLD_BLACK);
		cout << REMOVE_ALL_CONTRACTS << endl;
		changeTextColor(color.RED_BLACK);
		cout << REMOVE_CONDO_2 << endl;
		changeTextColor(color.GOLD_BLACK);
		cout << REMOVE_ALL_PROP_CONTR << endl;
		changeTextColor(color.GREY_BLACK);
		cout << CALL_EXT_INSPEC_3 << endl;
		cout << MAKE_RESERVATION_4 << endl;
		break;
	case 4:
		// Old Condos
		cout << REACTIVATE_CONDO_1 << endl;
		changeTextColor(color.RED_BLACK);
		cout << REMOVE_OLD_CONDO_2 << endl;
		changeTextColor(color.GREY_BLACK);
		break;
	case 5:
		// Propriedade
		cout << REMOVE_OWNER_1 << endl;
		changeTextColor(color.GOLD_BLACK);
		cout << REMOVE_ONLY_CONTRACT << endl;
		changeTextColor(color.RED_BLACK);
		cout << REMOVE_PROPERTY_2 << endl;
		changeTextColor(color.GOLD_BLACK);
		cout << REMOVE_CONTRACT_ALSO << endl;
		changeTextColor(color.GREY_BLACK);
		break;
	case 6:
		// External Inspections
		cout << EDIT_NAME_1 << endl;
		cout << EDIT_TYPE_2 << endl;
		cout << EDIT_PRICE_3 << endl;
		cout << EDIT_LOCALIZATION_4 << endl;
		changeTextColor(color.RED_BLACK);
		cout << REMOVE_5 << endl;
		changeTextColor(color.GREY_BLACK);
		cout << endl;
		cout << PRINT_ALL_EXT_INSPEC_6 << endl;
		break;
	}

	return 0;
}

size_t handleUPDATE(const size_t subOP, const size_t ch) {
	switch(subOP) {
	case 0: // Company
		if(ch == key.number1) return 1;
		if(ch == key.number2) return 2;
		if(ch == key.number3) return 3;
		break;
	case 1:
		if(ch == key.number1) return 1;
		if(ch == key.number2) return 2;
		if(ch == key.number3) return 3;
		if(ch == key.number4) return 4;
		break;
	case 2:
		if(ch == key.number1) return 1;
		if(ch == key.number2) return 2;
		break;
	case 3: // Condo
		if(ch == key.number1) return 1;
		if(ch == key.number2) return 2;
		if(ch == key.number3) return 3;
		if(ch == key.number4) return 4;
		break;
	case 4: // Old Condos
		if(ch == key.number1) return 1; /* Reactivate */
		if(ch == key.number2) return 2; /* Delete */
		break;
	case 5: // Properties
		if(ch == key.number1) return 1;
		if(ch == key.number2) return 2;
		break;
	case 6: // Ext Inspection
		if(ch == key.number1) return 1;
		if(ch == key.number2) return 2;
		if(ch == key.number3) return 3;
		if(ch == key.number4) return 4;
		if(ch == key.number5) return 5;
		if(ch == key.number6) return 6; /* Prints all ext inspections. */
		break;
	}
	return 0;
}

/* 							IMPRIMIR MENUS									*/
void printTitleMenu(const string toShow, const bool toClearScreen) {
	if(toClearScreen) clearScreen();
	cout << endl;
	cout << toShow;
	cout << endl << endl;
	for(size_t i = 0; i <= BORDER_SIZE; i++) cout << BORDER_HORIZONTAL_UP;
	cout << endl;
}

void printSubMenu(const string toShow, const bool text, const bool toClearScreen) {
	if(toClearScreen) clearScreen();
	cout << endl;
	if(!text)cout << toShow << ESC_INFO;
	if(text)cout << toShow << EXIT_CMD_INFO;
	cout << endl << endl;
	for(size_t i = 0; i <= BORDER_SIZE; i++) cout << BORDER_HORIZONTAL_UP;
	cout << endl;
}

void printMenu(const size_t op, const bool faded, Company &e1) {

	if(faded)
		changeTextColor(color.GREYER_BLACK);
	else
		changeTextColor(color.GREY_BLACK);

	cout << endl;
	foreach(opcao.mainOpt,it) {
		if(op == (*it).first) changeTextColor(color.WHITE_BLACK);
		cout << "  " << (*it).second;

		if(faded)
			changeTextColor(color.GREYER_BLACK);
		else
			changeTextColor(color.GREY_BLACK);
	}
	cout << endl;
	cout << setw(60) << PRINT_YEAR << e1.getYear() << PRINT_MONTH << e1.getMonth();
	cout << endl;

	if (faded)
		changeTextColor(color.RED_GREY);
	else
		changeTextColor(color.RED_BLACK);

	cout << setw(70) << ESC_INFO_2;
	changeTextColor(color.GREY_BLACK);
	cout << endl;
	for(size_t i = 0; i <= BORDER_SIZE; i++) cout << BORDER_HORIZONTAL_UP;
	cout << endl << endl;
}

void printMenu(const size_t op, const size_t subOP) {

	size_t index = 0;

	changeTextColor(color.GREY_BLACK);

	foreach(opcao.subOpt[op], it) {
		if(index == subOP) changeTextColor(color.WHITE_BLACK);
		cout << "  " << (*it) << endl;

		changeTextColor(color.GREY_BLACK);
		index++;
	}
	cout << endl << endl;
}

void printMenu(const size_t op) {
	size_t index = 0;
	string options[] = {" Criar nova empresa "," Carregar empresa "};

	const size_t numOptions = 2;

	changeTextColor(color.GREY_BLACK);

	for (size_t i = 0; i < numOptions; i++) {
		if(index == op) changeTextColor(color.WHITE_BLACK);
		cout << "  " << options[i] << endl;

		changeTextColor(color.GREY_BLACK);
		index++;
	}
	cout << endl << endl;
}

void printAllExtInspections(const Company & c) {

	vector<string> vars;
	string varTemp;
	size_t index = 0,ch, op = 0;
	string type;

	const size_t numVars = 2;
	const size_t numSlideVar = 1;

	bool byType = true;

	do {

		printSubMenu(PRINT_EXT_INSPECTION, false, true);
		cout << endl;

		if(index == 0) {
			if(byType) changeTextColor(color.WHITE_BLACK);
			cout << BY_INSPEC_TYPE;
			changeTextColor(color.GREY_BLACK);

			cout << endl;

			if(!byType) changeTextColor(color.WHITE_BLACK);
			cout << BY_PRICE;
			changeTextColor(color.GREY_BLACK);

			ch = readkey();
			if(key.arrow == ch) {
				ch = readkey();
				if(key.up == ch) {
					if(!byType) {
						byType = true;
					}
				}
				else if(key.down == ch) {
					if(byType) {
						byType = false;
					}
				}
			}
			else if(key.enter == ch) {
				if(byType) index++;
				else index = numVars;
			}
		}

		else if(index == numSlideVar && byType) {
			cout << UP_ARROW << endl;
			cout << "  " <<profissao.profs[op] << endl;
			cout << DOWN_ARROW << endl;

			ch = readkey();
			if(key.arrow == ch) {
				ch = readkey();
				if(key.down == ch) {
					if(0 < op) {
						op -= 1;
					}
				}
				else if(key.up == ch) {
					if(op < (profissao.profs.size() - 1)) {
						op += 1;
					}
				}
			}
			else if(key.enter == ch) {
				type = profissao.profs[op];
				index++;
				op = 0;
			}
			else if(key.esc == ch) {
				return;
			}
		}

	} while(index < numVars);

	printSubMenu(PRINT_EXT_INSPECTION, false, true);
	cout << endl;

	if(byType) {

		if(c.isExtInspectionsEmpty()) return;
		else {

			BSTItrIn<ExtInspection> itr = c.getBSTIteratorIn();

			while(!itr.isAtEnd()) {

				if(itr.retrieve().getInspectionType() == type) {
					cout << itr.retrieve() << endl;
				}

				itr.advance();

			}

		}

	}

	else if(!byType) {

		c.printExtInspections();

	}

	return;

}

/* 								CRIAR										*/
bool createNewCondo(Company &e1) {
	string varTemp;
	ostringstream varTempStream;
	size_t ch;

	bool create = false;

	do {
		printSubMenu(CREATE_CONDO, false, true);
		cout << endl;

		if(create) changeTextColor(color.WHITE_BLACK);
		cout << YES;
		changeTextColor(color.GREY_BLACK);

		if(!create) changeTextColor(color.WHITE_BLACK);
		cout << NO;
		changeTextColor(color.GREY_BLACK);

		ch = readkey();
		if(key.arrow == ch) {
			ch = readkey();
			if(key.left == ch) {
				if(!create) {
					create = true;
				}
			}
			else if(key.right == ch) {
				if(create) {
					create = false;
				}
			}
		}
		else if(key.enter == ch) {
			if(create) {
				do {

					printSubMenu(CREATE_CONDO, true, true);
					cout << endl;
					cout << INSERT_LOCALIZATION;
					getline(cin,varTemp);
					if(IsStringExit(varTemp)) {
						return false;
					}

					if(IsStringNumber(varTemp)) {
						if( e1.isLocalizationValid(atoi(varTemp.c_str())) )

							if(!e1.getFreeIDs().empty()) {

								int condo_id = e1.getFreeIDs().top();
								size_t total = 0;
								int localization = atoi(varTemp.c_str());

								e1.createCondo(condo_id, localization, total);
								e1.removeFreeID();

							} else {

								e1.createCondo(atoi(varTemp.c_str()), 0);
							}

						else {

							cout << endl;
							cout << "Localizacao ja ocupada. Por favor, escolha outra localizacao."
									<< endl << endl;
							waitForUser();

							continue;
						}
						return true;
					}

				} while(true);
				e1.createCondo();
				return true;
			}
			return false;
		}
	}while(ch != key.esc);

	return false;
}

bool createNewTec(Company &e1) {
	vector<string> vars;
	string varTemp;
	size_t index = 0,ch, op = 0;
	string str[] = {"profissao","nome","salario"};

	const size_t numVars = 3;
	const size_t numVarsTypeName = 2;
	const size_t numSlideVars = 1;

	do {
		if(index < numSlideVars) {
			printSubMenu(CREATE_TECH, false, true);
			cout << endl;
			cout << UP_ARROW << endl;
			cout << "  " <<profissao.profs[op] << endl;
			cout << DOWN_ARROW << endl;

			ch = readkey();
			if(key.arrow == ch) {
				ch = readkey();
				if(key.down == ch) {
					if(0 < op) {
						op -= 1;
					}
				}
				else if(key.up == ch) {
					if(op < (profissao.profs.size() - 1)) {
						op += 1;
					}
				}
			}
			else if(key.enter == ch) {
				vars.push_back(profissao.profs[op]);
				index++;
				op = 0;
			}
			else if(key.esc == ch) {
				return false;
			}
		}
		else {
			printSubMenu(CREATE_TECH, true, true);
			cout << endl;
			cout << INSERT << str[index] << ": ";

			getline(cin,varTemp);
			if(IsStringExit(varTemp)) {
				return false;
			}
			if(index < numVarsTypeName) {
				if(IsStringName(varTemp)) {
					vars.push_back(varTemp);
					index++;
				}
			}
			else {
				if(IsStringNumber(varTemp)) {
					vars.push_back(varTemp);
					index++;
				}
			}
		}

	}while(index < numVars);

	e1.createTechnician(vars[1],vars[0],atoi(vars[2].c_str()));

	return true;
}

bool createNewPropriet(Company &e1) {
	vector<string> vars;
	string varTemp;
	size_t index = 0;
	string str[] = {"nome"};

	const size_t numVars = 1;

	do {
		printSubMenu(CREATE_OWNER, true, true);
		cout << endl;

		cout << INSERT << str[index] << ": ";

		getline(cin,varTemp);
		if(IsStringExit(varTemp)) {
			return false;
		}
		if(IsStringName(varTemp)) {
			vars.push_back(varTemp);
			index++;
		}

	}while(index < numVars);

	e1.addOwner(vars[0]);

	return true;
}

bool createNewProp(Company &e1) {
	vector<string> vars;
	string varTemp;
	ostringstream varTempStream;
	size_t ch, op = 0, index = 0;
	string options[] = {"  Condominio  ","        Tipo  ","  Inserir area: ","  Inserir andar: "};
	string types[] = {"Residencial","Loja","Escritorio"};

	const size_t numVars = 4;
	const size_t numSlideVars = 2;

	do {
		if(index < numSlideVars) {
			printSubMenu(CREATE_PROP, false, true);
			cout << endl;
			cout << UP_ARROW_MORE_SPACE << endl;

			if(1 > index)
				cout << options[index] << (op + 1) << endl;
			else
				cout << options[index] << types[op] << endl;

			cout << DOWN_ARROW_MORE_SPACE << endl;

			ch = readkey();
			if(key.arrow == ch) {
				ch = readkey();
				if(key.down == ch) {
					if(0 < op) {
						op -= 1;
					}
				}
				else if(key.up == ch) {
					if(1 > index) {
						if(op < (e1.getCondos().size() - 1)) {
							op += 1;
						}
					}
					else {
						if(op < 2) {
							op += 1;
						}
					}
				}
			}
			else if(key.enter == ch) {
				varTempStream << op;
				vars.push_back(varTempStream.str());
				varTempStream.str("");
				index++;
				op = 0;
			}
			else if(key.esc == ch) {
				return false;
			}
		}
		else {
			printSubMenu(CREATE_PROP, true, true);
			cout << endl;
			cout << options[index];

			getline(cin,varTemp);
			if(IsStringExit(varTemp)) {
				return false;
			}
			if(index == (numVars-2)) {
				if(IsStringNumber(varTemp) && (varTemp != "0")) {
					vars.push_back(varTemp);
					index++;
				}
			}
			else if(IsStringNumber(varTemp)) {
				vars.push_back(varTemp);
				index++;
			}
		}

	}while(index < numVars);

	e1.addProperty(atoi(vars[0].c_str()),atoi(vars[2].c_str()),atoi(vars[3].c_str()),atoi(vars[1].c_str()));

	return true;
}

bool createNewContr(Company &e1) {
	vector<string> vars;
	string varTemp;
	ostringstream varTempStream;
	size_t ch, opCondo, op = 0, index = 0;
	string options[] = {"  Condominio  "," Propriedade  ","Proprietario: ","  Contrato: "};
	string types[] = {"Mensal","Semestral","Anual"};

	const size_t numVars = 4;
	enum size_t {CONDO,PROP,PROPRIET,CONTRAT};

	if(e1.getCondos().size() == 0) {
		printSubMenu(ASSOCIATE_CONTRACT, false, true);
		cout << NO_CONDOS;
		return false;
	}

	if(e1.getOwners().size() == 0) {
		printSubMenu(ASSOCIATE_CONTRACT, false, true);
		cout << NO_OWNERS;
		return false;
	}

	do {
		printSubMenu(ASSOCIATE_CONTRACT, false, true);
		cout << endl;

		cout << UP_ARROW_MORE_SPACE << endl;
		if(index == CONDO) {
			cout << options[index] << (op + 1)
				 << " (" << e1.getCondos()[op]->getPropriedades().size() << " propriedades)" << endl;
		}
		else if(index == PROP) {
			cout << options[index] << (op + 1)
				 << (e1.getCondos()[opCondo]->getPropriedades()[op]->existsOwner() ? " (Tem ":" (Nao tem ") << "proprietario)" << endl;
		}
		else if(index == PROPRIET) {
			cout << options[index] << e1.getOwners()[op]->getNome() << endl;
		}
		else //CONTRAT
			cout << options[index] << types[op] << endl;
		cout << DOWN_ARROW_MORE_SPACE << endl << endl;

		ch = readkey();
		if(key.arrow == ch) {
			ch = readkey();
			if(key.down == ch) {
				if(0 < op) {
					op -= 1;
				}
			}
			else if(key.up == ch) {
				if(index == CONDO) {
					if(op < (e1.getCondos().size() - 1)) {
						op += 1;
					}
				}
				else if(index == PROP) {
					if(op < (e1.getCondos()[opCondo]->getPropriedades().size() - 1)) {
						op += 1;
					}
				}
				else if(index == PROPRIET) {
					if(op < (e1.getOwners().size() - 1)) {
						op += 1;
					}
				}
				else { //CONTRAT
					if(op < 2) {
						op += 1;
					}
				}
			}
		}
		else if(key.enter == ch) {
			if(index != PROPRIET) {
				varTempStream << op;
				if(index == CONDO) {
					if (e1.getCondos()[op]->getPropriedades().size() != 0) {
						opCondo = op; //Gravar o ID do condominio selecionado
						vars.push_back(varTempStream.str());
					}
					else {
						printTitleMenu(ASSOCIATE_CONTRACT, true);
						cout << NO_PROPS;
						readkey();
						vars.clear();
						index--;
					}
				}
				if(index == PROP) {
					if (!e1.getCondos()[opCondo]->getPropriedades()[op]->existsOwner()) {
						vars.push_back(varTempStream.str());
					}
					else {
						printTitleMenu(ASSOCIATE_CONTRACT, true);
						cout << CONTRACT_ALREADY_EXISTS;
						readkey();
						vars.clear();
						index -=2;
					}
				}
				if(index == CONTRAT) {
					vars.push_back(varTempStream.str());
				}
			}
			else { //NOME vs ID (IDs pertencem a classe Pessoa', portanto um ID pode identificar tanto um Tecnico como um Proprietario )
				varTempStream << op;
				vars.push_back(varTempStream.str());
			}

			varTempStream.str("");
			index++;
			op = 0;
		}
		else if(key.esc == ch) {
			return false;
		}

	}while(index < numVars);

	e1.createContract(atoi(vars[0].c_str()),atoi(vars[1].c_str()),atoi(vars[2].c_str()),atoi(vars[3].c_str()));

	return true;
}

bool createNewExtInspection(Company & c) {

	vector<string> vars;
	string varTemp;
	ostringstream varTempStream;
	size_t ch, op = 0, index = 0;
	string options[] = {"Tipo", "Nome","Localizacao", "Preco"};

	const size_t numVars = 4;
	const size_t numVarsTypeName = 2;
	const size_t numSlideVars = 1;

	enum size_t { NAME, LOCALIZATION, TYPE, PRICE };

	do {

		if(index < numSlideVars) {

			printSubMenu(CREATE_EXT_INSPECTION, false, true);
			cout << endl;
			cout << UP_ARROW << endl;
			cout << "  " << profissao.profs[op] << endl;
			cout << DOWN_ARROW << endl;

			ch = readkey();

			if(key.arrow == ch) {
				ch = readkey();
				if(key.down == ch) {
					if(0 < op) {
						op -= 1;
					}
				}
				else if(key.up == ch) {
					if(op < (profissao.profs.size() - 1)) {
						op += 1;
					}
				}
			}
			else if(key.enter == ch) {
				vars.push_back(profissao.profs[op]);
				index++;
				op = 0;
			}
			else if(key.esc == ch) {
				return false;
			}
		}

		else {

			printSubMenu(CREATE_EXT_INSPECTION, true, true);
			cout << endl;
			cout << INSERT << options[index] << ": ";

			getline(cin,varTemp);

			if(IsStringExit(varTemp)) {
				return false;
			}

			if(index < numVarsTypeName) {
				if(IsStringName(varTemp)) {
					vars.push_back(varTemp);
					index++;
				}
			}

			else {

				if(IsStringNumber(varTemp)) {
					vars.push_back(varTemp);
					index++;
				}

			}
		}

	} while(index < numVars);

	ExtInspection e(vars[1], atoi(vars[2].c_str()), vars[0], atoi(vars[3].c_str()));
	c.addExtInspectionToBST(e);

	return true;
}

bool createNewReservation(Company & c, int & condo_id) {

	vector<string> vars;
	string varTemp;
	ostringstream varTempStream;
	size_t index = 0;
	string options[] = {"Mes", "Ano"};

	const size_t numVars = 2;

	enum size_t { NAME, LOCALIZATION, TYPE, PRICE };

	do {

		printSubMenu(MAKE_RESERVATION, true, true);
		cout << endl;
		cout << INSERT << options[index] << ": ";

		getline(cin,varTemp);

		if(IsStringExit(varTemp)) {
			return false;
		}


		if(IsStringNumber(varTemp)) {
			vars.push_back(varTemp);
			index++;

		}

	} while(index < numVars);

	try {

		Condo * condo = c.searchCondoByID(condo_id);

		int month = atoi(vars[0].c_str()), year = atoi(vars[1].c_str());

		if(!c.validDate(year, month)) {

			cout << endl << endl << INVALID_DATE << endl;
			waitForUser();

			return false;

		}

		Reservation r(condo, month, year);

		c.addReservation(r);

	} catch (Company_Error<string, int> & e) {

		cout << e.error << "ID: " << e.value << endl;
		waitForUser();

		return false;

	}


	return true;

}

/* 						 REMOVE EXT INSPECTION								*/
void removeExtInspection(Company & c) {

	if(c.isExtInspectionsEmpty()) return;

	BSTItrIn<ExtInspection> itr = c.getBSTIteratorIn();

	size_t ch;

	do {

		if(itr.isAtEnd()) {
			itr = c.getBSTIteratorIn();
		}

		printSubMenu(REMOVE_EXT_INSPECTION, false, true);
		cout << endl;
		cout << RIGHT_ARROW << itr.retrieve().getName() << endl;

		ch = readkey();

		if(key.arrow == ch) {
			ch = readkey();
			if(key.down == ch) {
				itr.advance();
			}
		}

		else if(key.esc == ch) {
			return;
		}

		else if(key.enter == ch) {
			c.removeExtInspectionFromBST(itr.retrieve());
		}

	} while(key.enter != ch);
}

/* 								EDITAR										*/
int editEmpresa(const size_t toDo, Company &e1) {
	string varTemp;
	size_t ch;
	bool reset = false;

	switch(toDo) {
	case 1:
		// Editar o nome
		do {
			printSubMenu(EDIT_COMPANY, true, true);
			cout << INSERT_NAME;

			getline(cin,varTemp);
			if(IsStringExit(varTemp)) {
				return false;
			}
			else if(IsStringName(varTemp)) {
				e1.setName(varTemp);
				return true;
			}

		}while(true);
		break;
	case 2:
		// Editar o saldo
		do {
			printSubMenu(EDIT_COMPANY, true, true);
			cout << INSERT_BALANCE;

			getline(cin,varTemp);
			if(IsStringExit(varTemp)) {
				return false;
			}
			else if(IsStringNumber(varTemp)) {
				e1.setBalance(atoi(varTemp.c_str()));
				return true;
			}

		}while(true);
		break;
	case 3:
		// Reset Data
		do {

			printSubMenu(RESTART_DATE, false, true);

			if(reset) changeTextColor(color.WHITE_BLACK);
			cout << YES;
			changeTextColor(color.GREY_BLACK);

			if(!reset) changeTextColor(color.WHITE_BLACK);
			cout << NO;
			changeTextColor(color.GREY_BLACK);

			ch = readkey();
			if(key.arrow == ch) {
				ch = readkey();
				if(key.left == ch) {
					if(!reset) {
						reset = true;
					}
				}
				else if(key.right == ch) {
					if(reset) {
						reset = false;
					}
				}
			}
			else if(key.enter == ch) {
				if(reset) {
					e1.setYear(1);
					e1.setMonth(1);
					return true;
				}
				return false;
			}
		}while(ch != key.esc);
		break;
	default:
		break;
	}
	return false;
}

bool editCondo(const size_t & toDo, const int & condo_id, Company & e1) {
	string varTemp;
	size_t ch;
	bool remove = false;

	switch(toDo) {
	case 1:
		// Remover Propriedades
		do {

			printSubMenu(REMOVE_PROPERTIES, false, true);

			if(remove) changeTextColor(color.WHITE_BLACK);
			cout << YES;
			changeTextColor(color.GREY_BLACK);

			if(!remove) changeTextColor(color.WHITE_BLACK);
			cout << NO;
			changeTextColor(color.GREY_BLACK);

			ch = readkey();
			if(key.arrow == ch) {
				ch = readkey();
				if(key.left == ch) {
					if(!remove) {
						remove = true;
					}
				}
				else if(key.right == ch) {
					if(remove) {
						remove = false;
					}
				}
			}
			else if(key.enter == ch) {
				if(remove) {
					Condo * condo = e1.searchCondoByID(condo_id);
					e1.removeAllPropertiesFromCondo(condo);
					return true;
				}
				return false;
			}
		}while(ch != key.esc);
		break;
	case 2:
		// REMOVER CONDOMINIO
		do {

			printSubMenu(REMOVE_CONDO, false, true);

			if(remove) changeTextColor(color.WHITE_BLACK);
			cout << YES;
			changeTextColor(color.GREY_BLACK);

			if(!remove) changeTextColor(color.WHITE_BLACK);
			cout << NO;
			changeTextColor(color.GREY_BLACK);

			ch = readkey();
			if(key.arrow == ch) {
				ch = readkey();
				if(key.left == ch) {
					if(!remove) {
						remove = true;
					}
				}
				else if(key.right == ch) {
					if(remove) {
						remove = false;
					}
				}
			}
			else if(key.enter == ch) {
				if(remove) {
					e1.removeCondo(condo_id);
					return true;
				}
				return false;
			}
		}while(ch != key.esc);
		break;
	default:
		break;
	}
	return false;
}

bool editOldCondo(const size_t toDo, Condo & co, Company & c) {
	string varTemp;
	size_t ch;
	bool remove = false;

	switch(toDo) {
	case 1:
		//Reactivate Old Condo
		do {

			printSubMenu(REACTIVATE_OLD_CONDO, false, true);

			if(remove) changeTextColor(color.WHITE_BLACK);
			cout << YES;
			changeTextColor(color.GREY_BLACK);

			if(!remove) changeTextColor(color.WHITE_BLACK);
			cout << NO;
			changeTextColor(color.GREY_BLACK);

			ch = readkey();
			if(key.arrow == ch) {
				ch = readkey();
				if(key.left == ch) {
					if(!remove) {
						remove = true;
					}
				}
				else if(key.right == ch) {
					if(remove) {
						remove = false;
					}
				}
			}
			else if(key.enter == ch) {
				if(remove) {
					c.createCondo(co.getLocalization(), co.getTotalProperties());
					c.removeCondoFromOldCondos(co);
					return true;
				}
				return false;
			}
		}while(ch != key.esc);
		break;
	case 2:
		// REMOVER CONDOMINIO
		do {

			printSubMenu(REMOVE_CONDO, false, true);

			if(remove) changeTextColor(color.WHITE_BLACK);
			cout << YES;
			changeTextColor(color.GREY_BLACK);

			if(!remove) changeTextColor(color.WHITE_BLACK);
			cout << NO;
			changeTextColor(color.GREY_BLACK);

			ch = readkey();
			if(key.arrow == ch) {
				ch = readkey();
				if(key.left == ch) {
					if(!remove) {
						remove = true;
					}
				}
				else if(key.right == ch) {
					if(remove) {
						remove = false;
					}
				}
			}
			else if(key.enter == ch) {
				if(remove) {
					c.removeCondoFromOldCondos(co);
					return true;
				}
				return false;
			}
		}while(ch != key.esc);
		break;
	default:
		break;
	}
	return false;
}

bool editTec(const size_t toDo, const size_t index, Company &e1) {
	string varTemp;
	size_t ch, op = 0;
	bool remove = false;

	switch(toDo) {
	case 1:
		// Editar o nome
		do {
			printSubMenu(EDIT_TECH, true, true);
			cout << INSERT_NAME;

			getline(cin,varTemp);
			if(IsStringExit(varTemp)) {
				return false;
			}
			else if(IsStringName(varTemp)) {
				if(!e1.technicianExists(varTemp)) {
					e1.setNameTechnician(index,varTemp);
					return true;
				}
			}

		}while(true);
		break;
	case 2:
		// Editar a profissao
		do {
			printSubMenu(EDIT_TECH, false, true);
			cout << endl;
			cout << UP_ARROW << endl;
			cout << "  " << profissao.profs[op] << endl;
			cout << DOWN_ARROW << endl;

			ch = readkey();
			if(key.arrow == ch) {
				ch = readkey();
				if(key.down == ch) {
					if(0 < op) {
						op -= 1;
					}
				}
				else if(key.up == ch) {
					if(op < (profissao.profs.size() - 1)) {
						op += 1;
					}
				}
			}
			else if(key.enter == ch) {
				e1.setProfessionTechnician(index,profissao.profs[op]);
				return true;
			}
			else if(key.esc == ch) {
				return false;
			}

		}while(true);
		break;
	case 3:
		// Editar o salario
		do {
			printSubMenu(EDIT_TECH,true,true);
			cout << INSERT_SALARY;

			getline(cin,varTemp);
			if(IsStringExit(varTemp)) {
				return false;
			}
			else if(IsStringNumber(varTemp)) {
				e1.setSalaryTechnician(index,atoi(varTemp.c_str()));
				return true;
			}

		}while(true);
		break;
	case 4:
		// REMOVER TECNICO
		do {

			printSubMenu(REMOVE_TECH, false, true);

			if(remove) changeTextColor(color.WHITE_BLACK);
			cout << YES;
			changeTextColor(color.GREY_BLACK);

			if(!remove) changeTextColor(color.WHITE_BLACK);
			cout << NO;
			changeTextColor(color.GREY_BLACK);

			ch = readkey();
			if(key.arrow == ch) {
				ch = readkey();
				if(key.left == ch) {
					if(!remove) {
						remove = true;
					}
				}
				else if(key.right == ch) {
					if(remove) {
						remove = false;
					}
				}
			}
			else if(key.enter == ch) {
				if(remove) {
					e1.removeTechnician(index);
					return true;
				}
				return false;
			}
		}while(ch != key.esc);
		break;
	default:
		break;
	}
	return false;
}

bool editPropriet(const size_t toDo, const size_t index, Company &e1) {
	string varTemp;
	size_t ch;
	bool remove = false;

	switch(toDo) {
	case 1:
		// Editar o nome
		do {
			printSubMenu(EDIT_OWNER, true, true);
			cout << INSERT_NAME;

			getline(cin,varTemp);
			if(IsStringExit(varTemp)) {
				return false;
			}
			else if(IsStringName(varTemp)) {
				e1.setNameOwner(index,varTemp);
				return true;
			}

		}while(true);
		break;
	case 2:
		do {
			// REMOVER PROPRIETARIO
			printSubMenu(REMOVE_OWNER, true, true);

			if(remove) changeTextColor(color.WHITE_BLACK);
			cout << YES;
			changeTextColor(color.GREY_BLACK);

			if(!remove) changeTextColor(color.WHITE_BLACK);
			cout << NO;
			changeTextColor(color.GREY_BLACK);

			ch = readkey();
			if(key.arrow == ch) {
				ch = readkey();
				if(key.left == ch) {
					if(!remove) {
						remove = true;
					}
				}
				else if(key.right == ch) {
					if(remove) {
						remove = false;
					}
				}
			}
			else if(key.enter == ch) {
				if(remove) {
					e1.removeOwner(index);
					return true;
				}
				return false;
			}
		}while(ch != key.esc);

		return true;
		break;
	default:
		break;
	}
	return false;
}

bool editProp(const size_t toDo, const size_t indexCondo, const size_t indexProp, Company &e1) {
	string varTemp;
	size_t ch;
	bool remove = false;

	switch(toDo) {
	case 1:
		// Remover Proprietario
		do {
			// REMOVER PROPRIEDADE
			printSubMenu(REMOVE_CONTRACT, false, true);

			if(remove) changeTextColor(color.WHITE_BLACK);
			cout << YES;
			changeTextColor(color.GREY_BLACK);

			if(!remove) changeTextColor(color.WHITE_BLACK);
			cout << NO;
			changeTextColor(color.GREY_BLACK);

			ch = readkey();
			if(key.arrow == ch) {
				ch = readkey();
				if(key.left == ch) {
					if(!remove) {
						remove = true;
					}
				}
				else if(key.right == ch) {
					if(remove) {
						remove = false;
					}
				}
			}
			else if(key.enter == ch) {
				if(remove) {
					e1.removePropertyContract(indexCondo,indexProp);
					return true;
				}
				return false;
			}
		}while(ch != key.esc);
		break;
	case 2:
		do {
			// REMOVER PROPRIEDADE
			printSubMenu(REMOVE_PROPERTY, false, true);

			if(remove) changeTextColor(color.WHITE_BLACK);
			cout << YES;
			changeTextColor(color.GREY_BLACK);

			if(!remove) changeTextColor(color.WHITE_BLACK);
			cout << NO;
			changeTextColor(color.GREY_BLACK);

			ch = readkey();
			if(key.arrow == ch) {
				ch = readkey();
				if(key.left == ch) {
					if(!remove) {
						remove = true;
					}
				}
				else if(key.right == ch) {
					if(remove) {
						remove = false;
					}
				}
			}
			else if(key.enter == ch) {
				if(remove) {
					e1.removeProperty(indexCondo,indexProp);
					return true;
				}
				return false;
			}
		}while(ch != key.esc);

		return true;
		break;
	default:
		break;
	}
	return false;
}

void editExtInspection(const size_t toDo, ExtInspection & e, Company & c) {

	string varTemp;
	size_t ch, op = 0;
	bool remove = false;

	switch(toDo) {
	case 1:
		// Edit name
		do {
			printSubMenu(EDIT_EXT_INSPECTION, true, true);
			cout << INSERT_NAME;

			getline(cin,varTemp);
			if(IsStringExit(varTemp)) {
				return;
			}
			else if(IsStringName(varTemp)) {
				e.setName(varTemp);
				return;
			}

		}while(true);
		break;
	case 2:
		// Edit type
		do {
			printSubMenu(EDIT_EXT_INSPECTION, false, true);
			cout << endl;
			cout << UP_ARROW << endl;
			cout << "  " << profissao.profs[op] << endl;
			cout << DOWN_ARROW << endl;

			ch = readkey();
			if(key.arrow == ch) {
				ch = readkey();
				if(key.down == ch) {
					if(0 < op) {
						op -= 1;
					}
				}
				else if(key.up == ch) {
					if(op < (profissao.profs.size() - 1)) {
						op += 1;
					}
				}
			}
			else if(key.enter == ch) {
				e.setInspectionType(profissao.profs[op]);
				return;
			}
			else if(key.esc == ch) {
				return;
			}

		}while(true);
		break;
	case 3:
		// Edit price
		do {
			printSubMenu(EDIT_EXT_INSPECTION, true, true);
			cout << INSERT_PRICE;

			getline(cin,varTemp);
			if(IsStringExit(varTemp)) {
				return;
			}
			else if(IsStringNumber(varTemp)) {
				size_t new_price = atoi(varTemp.c_str());
				e.setPrice(new_price);
				return;
			}

		}while(true);
		break;
	case 4:
		// Edit localization
		do {
			printSubMenu(EDIT_EXT_INSPECTION,true,true);
			cout << INSERT_LOCALIZATION;

			getline(cin,varTemp);
			if(IsStringExit(varTemp)) {
				return;
			}
			else if(IsStringNumber(varTemp)) {
				int new_localization = atoi(varTemp.c_str());
				e.setLocalization(new_localization);
				return;
			}

		}while(true);
		break;

	case 5:
		// Remove
		do {

			printSubMenu(REMOVE_EXT_INSPECTION, false, true);

			if(remove) changeTextColor(color.WHITE_BLACK);
			cout << YES;
			changeTextColor(color.GREY_BLACK);

			if(!remove) changeTextColor(color.WHITE_BLACK);
			cout << NO;
			changeTextColor(color.GREY_BLACK);

			ch = readkey();
			if(key.arrow == ch) {
				ch = readkey();
				if(key.left == ch) {
					if(!remove) {
						remove = true;
					}
				}
				else if(key.right == ch) {
					if(remove) {
						remove = false;
					}
				}
			}
			else if(key.enter == ch) {
				if(remove) {
					c.removeExtInspectionFromBST(e);
				}
				return;
			}
		}while(ch != key.esc);
		break;
	default:
		break;
	}

	return;

}

void callExtInspection(Company & c, int condo_id) {

	size_t ch, op = 0;
	string type;

	vector<string> criteria; criteria.push_back(CLOSEST); criteria.push_back(CHEAPEST);

	do {
		printSubMenu(CALL_EXT_INSPECTION, false, true);
		cout << endl;
		cout << UP_ARROW << endl;
		cout << "  " << profissao.profs[op] << endl;
		cout << DOWN_ARROW << endl;

		ch = readkey();
		if(key.arrow == ch) {
			ch = readkey();
			if(key.down == ch) {
				if(0 < op) {
					op -= 1;
				}
			}
			else if(key.up == ch) {
				if(op < (profissao.profs.size() - 1)) {
					op += 1;
				}
			}
		}
		else if(key.enter == ch) {

			type = profissao.profs[op];
			break;

		}
		else if(key.esc == ch) {
			return;
		}

	}while(true);

	op = 0;

	do {
		printSubMenu(CALL_EXT_INSPECTION, false, true);
		cout << endl;
		cout << UP_ARROW << endl;
		cout << "  " << criteria[op] << endl;
		cout << DOWN_ARROW << endl;

		ch = readkey();
		if(key.arrow == ch) {
			ch = readkey();
			if(key.down == ch) {
				if(0 < op) {
					op -= 1;
				}
			}
			else if(key.up == ch) {
				if(op < (criteria.size() - 1)) {
					op += 1;
				}
			}
		}
		else if(key.enter == ch) {
			try {

				Condo * condo = c.searchCondoByID(condo_id);
				ExtInspection * e = condo->searchBestExtInspection(c, type, op);

				printSubMenu(CALL_EXT_INSPECTION, false, true);
				cout << endl << endl << "A empresa " << e->getName() << " foi chamada, com um custo de "
						<< c.callExtInspection(e) << "." << endl << endl;

				waitForUser();

			} catch (Company_Error<string, int> & e) {

				cout << e.error << " ID: " << e.value << endl;
				waitForUser();
				return;

			} catch (ExtInspection_Error & e) {

				printSubMenu(CALL_EXT_INSPECTION, false, true);
				cout << endl << endl << NO_EXT_INSPECTION_FOUND
						<< endl << endl;

				waitForUser();

				return;
			}

		}
		else if(key.esc == ch) {
			return;
		}

	}while(true);


}

/* 								IMPRIMIR									*/
size_t selectCondo(Company &e1) {
	string varTemp;
	ostringstream varTempStream;
	size_t ch;
	size_t op = 0;

	do {
		printSubMenu(PRINT_PROPS, false, true);

		cout << UP_ARROW_MORE_SPACE << endl;
		cout << "  Condominio: " << (op + 1) << "  (" << e1.getCondos()[op]->getPropriedades().size() << " propriedades"
			 << " - " << e1.getCondos()[op]->getNumPropriedadesLivres() << " livres)" << endl;
		cout << DOWN_ARROW_MORE_SPACE << endl;

		ch = readkey();
		if(key.arrow == ch) {
			ch = readkey();
			if(key.down == ch) {
				if(0 < op) {
					op -= 1;
				}
			}
			else if(key.up == ch) {
				if(op < (e1.getCondos().size() - 1)) {
					op += 1;
				}

			}
		}
		else if(key.enter == ch) {
			return op;
		}
	}while(key.esc != ch);
	return e1.getCondos().size();
}

/* 								PROCURAR									*/
bool searchTec(Company &e1) {
	string varTemp;
	Technician * toPrint;
	ostringstream varTempStream;
	string str[] = {"Profissao","Nome","Salario"};

	bool found = false, ignore = false;

	size_t index = 0, op = 0, ch;
	size_t salarioMin = 0, salarioMax = 0, valueTemp = 0;

	const size_t numSlideVars = 3;

	if(e1.getTechinicians().size() == 0) {
		printSubMenu(SEARCH_TECH, false, true);
		cout << NO_TECHS;
		return false;
	}

	do {
		// get opcao
		printSubMenu(SEARCH_TECH, false, true);
		cout << endl;
		cout << UP_ARROW_MORE_SPACE << endl;
		cout << SEARCH_BY <<str[index] << endl;
		cout << DOWN_ARROW_MORE_SPACE << endl;

		ch = readkey();
		if(key.arrow == ch) {
			ch = readkey();
			if(key.up == ch) {
				if(index < (numSlideVars - 1)) {
					index++;
				}
				else {
					index = 0;
				}
			}
			else if(key.down == ch) {
				if(0 < index) {
					index--;
				}
				else {
					index = (numSlideVars - 1);
				}
			}
		}
		else if(key.enter == ch) {
			break;
		}
	}while(ch != key.esc);
	if(ch != key.esc) {
		switch(index) {
		case 0:
			/*******************************************************************************************/
			// PROFISSAO
			// get opcao
			op = 0;
			do {
				printSubMenu(SEARCH_TECH, false, true);
				cout << endl;
				cout << UP_ARROW_MORE_SPACE << endl;
				cout << BY_PROFESSION << profissao.profs[op] << endl;
				cout << DOWN_ARROW_MORE_SPACE << endl;

				ch = readkey();
				if(key.arrow == ch) {
					ch = readkey();
					if(key.up == ch) {
						if(op < (profissao.profs.size() - 1)) {
							op++;
						}
						else {
							op = 0;
						}
					}
					else if(key.down == ch) {
						if(0 < op) {
							op--;
						}
						else {
							op = (profissao.profs.size() - 1);
						}
					}
				}
				else if(key.enter == ch) {
					printTitleMenu(SEARCH_TECH + profissao.profs[op] + SEARCH_RESULTS,true);
					for(size_t i = 0; i < e1.getTechinicians().size() ; i++) {
						if(e1.getTechinicians()[i]->getProfissao() == profissao.profs[op]) {
							found = true;
							cout << "  " << e1.getTechinicians()[i]->getNome() << "  - Salario: " << e1.getTechinicians()[i]->getSalario() << endl;
						}
					}
					if(!found) {
						printTitleMenu(SEARCH_TECH, true);
						cout << NO_RESULTS;
					}
					else {
						found = false;
					}
					return true;
				}
			}while(ch != key.esc);
			break;
		case 1:
			/*******************************************************************************************/
			// NOME
			do {
				printSubMenu(SEARCH_TECH, true, true);

				cout << INSERT_NAME;

				getline(cin,varTemp);
				if(IsStringExit(varTemp)) {
					return false;
				}
				if(IsStringEmpty(varTemp)) {
					return false;
				}
				else if(IsStringName(varTemp)) {
					try {
						toPrint = e1.searchTechnician(varTemp);
						printTitleMenu("  Nome: " + toPrint->getNome(),true);
						printTitleMenu("  Profissao: " + toPrint->getProfissao(),false);
						varTempStream << toPrint->getSalario();
						printTitleMenu("  Salario: " + varTempStream.str(),false);
						varTempStream.str("");
						printSubMenu("",false,false);
						return true;
					}
					catch(Company_Error<string,int> &error) {
						printTitleMenu(error.error,true);
						readkey();
						return false;
					}
				}

			}while(true);
			break;
		case 2:
			/*******************************************************************************************/
			// SALARIO
			do {
				printSubMenu(SEARCH_TECH, true, true);

				cout << INSERT_MIN_SALARY;

				getline(cin,varTemp);
				if(IsStringExit(varTemp)) {
					return false;
				}
				if(IsStringEmpty(varTemp)) {
					break;
				}
				else if(IsStringNumber(varTemp)) {
					salarioMin = atoi(varTemp.c_str());
					break;
				}

			}while(true);
			do {
				printSubMenu(SEARCH_TECH, true, true);

				cout << INSERT_MAX_SALARY;

				getline(cin,varTemp);
				if(IsStringExit(varTemp)) {
					return false;
				}
				if(IsStringEmpty(varTemp)) {

					break;
				}
				else if(IsStringNumber(varTemp)) {
					salarioMax = atoi(varTemp.c_str());
					if(salarioMax == salarioMin) {
						ignore = true;
					}
					break;
				}

			}while(true);
			if((!salarioMin) && (!ignore)) {
				if(!salarioMax) {
					printTitleMenu("  Procurar Tecnico com qualquer salario - Resultados da procura",true);
					for(size_t i = 0; i < e1.getTechinicians().size() ; i++) {
						found = true;
						cout << "  " << e1.getTechinicians()[i]->getNome() << "  - Profissao: " << e1.getTechinicians()[i]->getProfissao() << endl;
					}
				}
				else {
					varTempStream << "  Procurar Tecnico com salario menor ou igual a: " << salarioMax << " - Resultados da procura";
					printTitleMenu(varTempStream.str(),true);
					varTempStream.str("");
					for(size_t i = 0; i < e1.getTechinicians().size() ; i++) {
						if(e1.getTechinicians()[i]->getSalario() <= salarioMax) {
							found = true;
							cout << "  " << e1.getTechinicians()[i]->getNome() << "  - Profissao: " << e1.getTechinicians()[i]->getProfissao() << endl;
						}
					}
				}
			}
			else {
				if((!salarioMax) && (!ignore)) {
					varTempStream << "  Procurar Tecnico com salario maior ou igual a: " << salarioMin << " - Resultados da procura";
					printTitleMenu(varTempStream.str(),true);
					varTempStream.str("");
					for(size_t i = 0; i < e1.getTechinicians().size() ; i++) {
						if(e1.getTechinicians()[i]->getSalario() >= salarioMin) {
							found = true;
							cout << "  " << e1.getTechinicians()[i]->getNome() << "  - Profissao: " << e1.getTechinicians()[i]->getProfissao() << endl;
						}
					}
				}
				else {
					if(salarioMax > salarioMin) {
						valueTemp = salarioMax;
						salarioMax = salarioMin;
						salarioMin = valueTemp;
					}
					varTempStream << "  Procurar Tecnico com salario entre: " << salarioMin << " e " << salarioMax << " - Resultados da procura";
					printTitleMenu(varTempStream.str(),true);
					varTempStream.str("");
					for(size_t i = 0; i < e1.getTechinicians().size() ; i++) {
						if((e1.getTechinicians()[i]->getSalario() >= salarioMin) &&
								(e1.getTechinicians()[i]->getSalario() <= salarioMax)) {
							found = true;
							cout << "  " << e1.getTechinicians()[i]->getNome() << "  - Profissao: " << e1.getTechinicians()[i]->getProfissao() << endl;
						}
					}
				}
			}
			if(!found) {
				printTitleMenu("  Procurar Tecnico",true);
				cout << "Nao ha resultados que coincidam com os parametros pedidos.";
			}
			else {
				found = false;
			}
			ignore = false;

			return true;
			break;
		default:
			break;
		}
	}

	return false;
}

bool searchPropriet(Company &e1) {
	Owner * toPrint;
	string varTemp;
	size_t index = 0;
	ostringstream varTempStream;

	if(e1.getOwners().size() == 0) {
		printSubMenu("  Procurar Proprietario",false,true);
		cout << "  Nao ha proprietarios.";
		return false;
	}

	do {
		printSubMenu("  Procurar Proprietario",true,true);

		cout << "  Inserir nome: ";

		getline(cin,varTemp);
		if(IsStringExit(varTemp)) {
			return false;
		}
		if(IsStringEmpty(varTemp)) {
			return false;
		}
		else if(IsStringName(varTemp)) {
			try {
				toPrint = e1.getOwner(varTemp);
				printTitleMenu("  Procurar Proprietario '" + toPrint->getNome() + "' - Resultados da procura",true);
				printTitleMenu("  Propriedades",false);
				for(size_t i = 0; i < toPrint->getPropriedades().size(); i++) {
					varTempStream << " Condominio: " << (toPrint->getPropriedades()[i]->getID_Condo() + 1)
								  << " --------- Propriedade: " << (toPrint->getPropriedades()[i]->getID() + 1);
					switch(toPrint->getPropriedades()[i]->getType()) {
					case 0:
						varTempStream << " (Residencia)";
						break;
					case 1:
						varTempStream << " (Loja)";
						break;
					case 2:
						varTempStream << " (Escritorio)";
						break;
					default:
						break;
					}
					cout << varTempStream.str() << endl;
					varTempStream.str("");
				}
				return true;
			}
			catch(Company_Error<string,int> &error) {
				printTitleMenu(error.error,true);
				readkey();
				return false;
			}
			index++;
		}

	}while(true);

	return false;
}

bool searchProp(Company &e1) {
	string varTemp;
	ostringstream varTempStream;
	string str[] = {"Tipo","Area","Andar"};
	string type[] = {"Residencia","Loja","Escritorio"};

	size_t index = 0, op = 0, ch;
	size_t valueMin = 0, valueMax = 0, valueTemp = 0;

	bool found = false, ignore = false, first = true;

	const size_t numSlideVars = 3;
	const size_t numTypes = 3;

	if(e1.getCondos().size() == 0) {
		printSubMenu("  Procurar Propriedade",false,true);
		cout << "  Nao ha Condominios.";
		return false;
	}

	do {
		// get opcao
		printSubMenu("  Procurar Propriedade",false,true);
		cout << endl;
		cout << "                ^" << endl;
		cout << "  Procurar por: " <<str[index] << endl;
		cout << "                v" << endl;

		ch = readkey();
		if(key.arrow == ch) {
			ch = readkey();
			if(key.up == ch) {
				if(index < (numSlideVars - 1)) {
					index++;
				}
				else {
					index = 0;
				}
			}
			else if(key.down == ch) {
				if(0 < index) {
					index--;
				}
				else {
					index = (numSlideVars - 1);
				}
			}
		}
		else if(key.enter == ch) {
			break;
		}
	}while(ch != key.esc);
	if(ch != key.esc) {
		switch(index) {
		case 0:
			/*******************************************************************************************/
			// TIPO
			// get opcao
			op = 0;
			do {
				printSubMenu("  Procurar Propriedade",false,true);
				cout << endl;
				cout << "        ^" << endl;
				cout << "  Tipo: " << type[op] << endl;
				cout << "        v" << endl;

				ch = readkey();
				if(key.arrow == ch) {
					ch = readkey();
					if(key.up == ch) {
						if(op < (numTypes - 1)) {
							op++;
						}
						else {
							op = 0;
						}
					}
					else if(key.down == ch) {
						if(0 < op) {
							op--;
						}
						else {
							op = (numTypes - 1);
						}
					}
				}
				else if(key.enter == ch) {
					printTitleMenu("  Procurar Propriedade do tipo: '" + type[op] + "' - Resultados da procura",true);
					for(size_t i = 0; i < e1.getCondos().size(); i++) {
						for(size_t j = 0; j  < e1.getCondos()[i]->getPropriedades().size() ; j++) {
							if(e1.getCondos()[i]->getPropriedades()[j]->getType() == op) {
								found = true;
								if(first) {
									cout << "    Condominio: " << (i + 1) << "   ";
									cout << "  Propriedades:  ";
									first = false;
								}
								cout << (j + 1) << "  ";
							}
						}
						if(!first) cout << endl << endl;
						first = true;
					}
					if(!found) {
						printTitleMenu("  Procurar Tecnico",true);
						cout << "Nao ha resultados que coincidam com os parametros pedidos.";
					}
					else {
						found = false;
					}
					return true;
				}
			}while(ch != key.esc);
			break;
		case 1:
			/*******************************************************************************************/
			// AREA
			do {
				printSubMenu("  Procurar Propriedade",true,true);

				cout << "  Inserir area minima (enter para ignorar): ";

				getline(cin,varTemp);
				if(IsStringExit(varTemp)) {
					return false;
				}
				if(IsStringEmpty(varTemp)) {
					break;
				}
				else if(IsStringNumber(varTemp)) {
					valueMin = atoi(varTemp.c_str());
					break;
				}

			}while(true);
			do {
				printSubMenu("  Procurar Propriedade",true,true);

				cout << "  Inserir area maxima (enter para ignorar): ";

				getline(cin,varTemp);
				if(IsStringExit(varTemp)) {
					return false;
				}
				if(IsStringEmpty(varTemp)) {
					break;
				}
				else if(IsStringNumber(varTemp)) {
					valueMax = atoi(varTemp.c_str());
					if(valueMax == valueMin) {
						ignore = true;
					}
					break;
				}
			}while(true);
			if((!valueMin) && (!ignore)) {
				if(!valueMax) {
					printTitleMenu("  Procurar propriedade com qualquer area - Resultados da procura",true);
					for(size_t i = 0; i < e1.getCondos().size(); i++) {

						for(size_t j = 0; j  < e1.getCondos()[i]->getPropriedades().size() ; j++) {
							found = true;
							if(first) {
								cout << "    Condominio: " << (i + 1) << "   ";
								cout << "  Propriedades:  ";
								first = false;
							}
							cout << (j + 1) << "  ";
						}
						if(!first) cout << endl << endl;
						first = true;
					}
				}
				else {
					varTempStream << "  Procurar propriedade com area menor ou igual a: " << valueMax << " - Resultados da procura";
					printTitleMenu(varTempStream.str(),true);
					varTempStream.str("");
					for(size_t i = 0; i < e1.getCondos().size(); i++) {
						for(size_t j = 0; j  < e1.getCondos()[i]->getPropriedades().size() ; j++) {
							if(e1.getCondos()[i]->getPropriedades()[j]->getArea() <= valueMax) {
								found = true;
								if(first) {
									cout << "    Condominio: " << (i + 1) << "   ";
									cout << "  Propriedades:  ";
									first = false;
								}
								cout << (j + 1) << "  ";
							}
						}
						if(!first) cout << endl << endl;
						first = true;
					}
				}
			}
			else {
				if((!valueMax) && (!ignore)) {
					varTempStream << "  Procurar propriedade com area maior ou igual a: " << valueMin << " - Resultados da procura";
					printTitleMenu(varTempStream.str(),true);
					varTempStream.str("");
					for(size_t i = 0; i < e1.getCondos().size(); i++) {
						for(size_t j = 0; j  < e1.getCondos()[i]->getPropriedades().size() ; j++) {
							if(e1.getCondos()[i]->getPropriedades()[j]->getArea() >= valueMin) {
								found = true;
								if(first) {
									cout << "    Condominio: " << (i + 1) << "   ";
									cout << "  Propriedades:  ";
									first = false;
								}
								cout << (j + 1) << "  ";
							}
						}
						if(!first) cout << endl << endl;
						first = true;
					}
				}
				else {
					varTempStream << "  Procurar propriedade com area entre: " << valueMin << " e " << valueMax << " - Resultados da procura";
					printTitleMenu(varTempStream.str(),true);
					varTempStream.str("");
					for(size_t i = 0; i < e1.getCondos().size(); i++) {
						for(size_t j = 0; j  < e1.getCondos()[i]->getPropriedades().size() ; j++) {
							if((e1.getCondos()[i]->getPropriedades()[j]->getArea() >= valueMin) &&
									(e1.getCondos()[i]->getPropriedades()[j]->getArea() <= valueMax)) {
								found = true;
								if(first) {
									cout << "    Condominio: " << (i + 1) << "   ";
									cout << "  Propriedades:  ";
									first = false;
								}
								cout << (j + 1) << "  ";
							}
						}
						if(!first) cout << endl << endl;
						first = true;
					}
				}
			}
			if(!found) {
				printTitleMenu("  Procurar Tecnico",true);
				cout << "Nao ha resultados que coincidam com os parametros pedidos.";
			}
			else {
				found = false;
			}
			ignore = false;

			return true;
			break;
		case 2:
			/*******************************************************************************************/
			// ANDAR
			do {
				printSubMenu("  Procurar Propriedade",true,true);

				cout << "  Inserir andar minimo (enter para ignorar): ";

				getline(cin,varTemp);
				if(IsStringExit(varTemp)) {
					return false;
				}
				if(IsStringEmpty(varTemp)) {
					break;
				}
				else if(IsStringNumber(varTemp)) {
					valueMin = atoi(varTemp.c_str());
					break;
				}

			}while(true);
			do {
				printSubMenu("  Procurar Propriedade",true,true);

				cout << "  Inserir andar maximo (enter para ignorar): ";

				getline(cin,varTemp);
				if(IsStringExit(varTemp)) {
					return false;
				}
				if(IsStringEmpty(varTemp)) {
					break;
				}
				else if(IsStringNumber(varTemp)) {
					valueMax = atoi(varTemp.c_str());
					if(valueMax == valueMin) {
						ignore = true;
					}
					break;
				}
			}while(true);
			if((!valueMin) && (!ignore)) {
				if(!valueMax) {
					printTitleMenu("  Procurar propriedade com qualquer andar - Resultados da procura",true);
					for(size_t i = 0; i < e1.getCondos().size(); i++) {
						for(size_t j = 0; j  < e1.getCondos()[i]->getPropriedades().size() ; j++) {
							found = true;
							if(first) {
								cout << "    Condominio: " << (i + 1) << "   ";
								cout << "  Propriedades:  ";
								first = false;
							}
							cout << (j + 1) << "  ";
						}
						if(!first) cout << endl << endl;
						first = true;
					}
				}
				else {
					varTempStream << "  Procurar propriedade com andar inferior ou igual a: " << valueMax << " - Resultados da procura";
					printTitleMenu(varTempStream.str(),true);
					varTempStream.str("");
					for(size_t i = 0; i < e1.getCondos().size(); i++) {
						for(size_t j = 0; j  < e1.getCondos()[i]->getPropriedades().size() ; j++) {
							if(e1.getCondos()[i]->getPropriedades()[j]->getFloor() <= valueMax) {
								found = true;
								if(first) {
									cout << "    Condominio: " << (i + 1) << "   ";
									cout << "  Propriedades:  ";
									first = false;
								}
								cout << (j + 1) << "  ";
							}
						}
						if(!first) cout << endl << endl;
						first = true;
					}
				}
			}
			else {
				if((!valueMax) && (!ignore)) {
					varTempStream << "  Procurar propriedade com andar superior ou igual a: " << valueMin << " - Resultados da procura";
					printTitleMenu(varTempStream.str(),true);
					varTempStream.str("");
					for(size_t i = 0; i < e1.getCondos().size(); i++) {
						for(size_t j = 0; j  < e1.getCondos()[i]->getPropriedades().size() ; j++) {
							if(e1.getCondos()[i]->getPropriedades()[j]->getFloor() >= valueMin) {
								found = true;
								if(first) {
									cout << "    Condominio: " << (i + 1) << "   ";
									cout << "  Propriedades:  ";
									first = false;
								}
								cout << (j + 1) << "  ";
							}
						}
						if(!first) cout << endl << endl;
						first = true;
					}
				}
				else {
					if(valueMax < valueMin) {
						valueTemp = valueMax;
						valueMax = valueMin;
						valueMin = valueTemp;
					}
					varTempStream << "  Procurar propriedade com andar entre o: " << valueMin << " e o " << valueMax << " - Resultados da procura";
					printTitleMenu(varTempStream.str(),true);
					varTempStream.str("");
					for(size_t i = 0; i < e1.getCondos().size(); i++) {
						for(size_t j = 0; j  < e1.getCondos()[i]->getPropriedades().size() ; j++) {
							if((e1.getCondos()[i]->getPropriedades()[j]->getFloor() >= valueMin) &&
									(e1.getCondos()[i]->getPropriedades()[j]->getFloor() <= valueMax)) {
								found = true;
								if(first) {
									cout << "    Condominio: " << (i + 1) << "   ";
									cout << "  Propriedades:  ";
									first = false;
								}
								cout << (j + 1) << "  ";
							}
						}
						if(!first) cout << endl << endl;
						first = true;
					}
				}
			}
			if(!found) {
				printTitleMenu("  Procurar Tecnico",true);
				cout << "Nao ha resultados que coincidam com os parametros pedidos.";
			}
			else {
				found = false;
			}
			ignore = false;

			return true;
			break;
		default:
			break;
		}
	}

	return false;
}

/* 								MENUS										*/
bool confirmReservation(const Reservation & r) {

	string varTemp;
	ostringstream varTempStream;
	size_t ch;

	bool confirm = false;

	do {
		printSubMenu("  Confirmar Reserva",false,true);
		cout << endl;

		cout << "E necessario confirmar a reserva: " << endl
				<< "  Condominio: " << r.getCondo()->getID() << endl
				<< "         Mes: " << r.getMonth() << endl << endl
				<< "( Se nao confirmar a reserva sera cancelada )." << endl << endl;

		if(confirm) changeTextColor(color.WHITE_BLACK);
		cout << "  CONFIRMAR";
		changeTextColor(color.GREY_BLACK);

		if(!confirm) changeTextColor(color.WHITE_BLACK);
		cout << "  CANCELAR";
		changeTextColor(color.GREY_BLACK);

		ch = readkey();
		if(key.arrow == ch) {
			ch = readkey();
			if(key.left == ch) {
				if(!confirm) {
					confirm = true;
				}
			}
			else if(key.right == ch) {
				if(confirm) {
					confirm = false;
				}
			}
		}
		else if(key.enter == ch) {
			return confirm;
		}
	}while(ch != key.esc);

	return false;

}
bool menu4(const size_t subOP, Company &e1) {
	ostringstream oss;
	vector<string> vars;
	size_t toDo = 0, ch = 0, condoToPrint = 0;
	size_t index = 0;

	BSTItrIn<ExtInspection> itr = e1.getBSTIteratorIn();

	clearScreen();
	switch(subOP) {
	case 0:

		do{
			oss << "  Empresa: " << e1.getName() << endl << endl
				<< "    Saldo: " << e1.getBalance() << endl << endl
				<< "      Mes: " << e1.getMonth() << endl << endl
				<< "      Ano: " << e1.getYear();

			printTitleMenu(oss.str(),true);
			printSubMenu("",false,false);
			oss.str("");

			coutUPDATE(subOP);

			ch = readkey();
			if (ch >= key.number0 && ch <= key.number9) {
				toDo = handleUPDATE(subOP, ch);
				if(editEmpresa(toDo, e1) == 2) {
					return true;
				}
			}
		}while(ch != key.esc);
		break;
		/**********************************************************************************************************************/
	case 1:
		if(e1.getTechinicians().size()) {
			do {
				oss << "           ^" << endl << "  Tecnico: " << e1.getTechinicians()[index]->getNome()
					<< " (" << (index + 1) << " / " << e1.getTechinicians().size() << ")"
					<< endl << "           v" << endl << endl
					<< "  Profissao: " << e1.getTechinicians()[index]->getProfissao() << endl << endl
					<< "    Salario: " << e1.getTechinicians()[index]->getSalario();

				printTitleMenu(oss.str(),true);
				printSubMenu("",false,false);
				oss.str("");

				coutUPDATE(subOP);

				ch = readkey();
				if(ch == key.arrow) {
					ch = readkey();
					if(ch == key.down) {
						if(index < (e1.getTechinicians().size() - 1)) {
							index++;
						}
						else {
							index = 0;
						}
					}
					else if(ch == key.up){
						if(0 < index) {
							index--;
						}
						else {
							index = (e1.getTechinicians().size() - 1);
						}
					}
				}
				else if(ch >= key.number0 && ch <= key.number9) {
					// searchPoint2
					toDo = handleUPDATE(subOP,ch);
					editTec(toDo, index, e1);
					index = 0;
					if(!e1.getTechinicians().size()) break;
				}
			}while(ch != key.esc);
		}
		else {
			printTitleMenu("  Ver Tecnicos.", true);
			printTitleMenu("  Nao ha tecnicos.", false);
			readkey();
		}
		break;
		/**********************************************************************************************************************/
	case 2:
		if(e1.getOwners().size()) {
			do{
				oss << "                ^" << endl << "  Proprietario: " << e1.getOwners()[index]->getNome()
					<< " (" << (index + 1) << " / " << e1.getOwners().size() << ")"
					<< endl << "                v";

				printTitleMenu(oss.str(),true);
				oss.str("");
				oss << "  Propriedades" << endl << endl;
				for(size_t i = 0; i < e1.getOwners()[index]->getPropriedades().size(); i++) {
					oss << " Condominio: " << (e1.getOwners()[index]->getPropriedades()[i]->getID_Condo() + 1)
						<< " --------- Propriedade: " << (e1.getOwners()[index]->getPropriedades()[i]->getID() + 1);
					switch(e1.getOwners()[index]->getPropriedades()[i]->getType()) {
					case 0:
						oss << " (Residencia)";
						break;
					case 1:
						oss << " (Loja)";
						break;
					case 2:
						oss << " (Escritorio)";
						break;
					default:
						break;
					}
					oss << endl;
				}
				printTitleMenu(oss.str(),false);
				printSubMenu("",false,false);

				oss.str("");
				coutUPDATE(subOP);

				ch = readkey();
				if(ch == key.down) {
					if(index < (e1.getOwners().size() - 1)) {
						index++;
					}
					else {
						index = 0;
					}
				}
				else if(ch == key.up){
					if(0 < index) {
						index--;
					}
					else {
						index = (e1.getOwners().size() - 1);
					}
				}
				else if (ch >= key.number0 && ch <= key.number9) {
					toDo = handleUPDATE(subOP, ch);
					editPropriet(toDo, index, e1);
					index = 0;
					if(!e1.getOwners().size()) break;
				}
			}while(ch != key.esc);
		}
		else {
			printTitleMenu("  Ver Proprietarios.", true);
			printTitleMenu("  Nao ha proprietarios", false);
			readkey();
		}
		break;
		/************************************************** CONDOMINIOS *****************************************************/
	case 3:
		if(e1.getCondos().size()) {
			do{
				oss << "                ^" << endl << "    Condominio: " << (index + 1) << " / " << e1.getCondos().size() << endl
						<< "                v" << endl << endl
						<< "  Propriedades: " << e1.getCondos()[index]->getPropriedades().size()
						<< " (" << e1.getCondos()[index]->getNumPropriedadesLivres() << " livres)" << endl << endl
						<< "  Localizacao: " << e1.getCondos()[index]->getLocalization() << endl << endl;
				printTitleMenu(oss.str(),true);
				printSubMenu("",false,false);

				oss.str("");
				coutUPDATE(subOP);

				ch = readkey();
				if(ch == key.up) {
					if(0 < index) {
						index--;
					}
					else {
						index = (e1.getCondos().size() - 1);
					}
				}
				else if(ch == key.down){
					if(index < (e1.getCondos().size() - 1)) {
						index++;
					}
					else {
						index = 0;
					}
				}
				else if (ch >= key.number0 && ch <= key.number9){
					int condo_id = e1.getCondos()[index]->getID();
					toDo = handleUPDATE(subOP, ch);
					if(toDo == 3) // Call Ext Inspection
						callExtInspection(e1, condo_id);
					else if(toDo == 4)
						createNewReservation(e1, condo_id);
					else
						editCondo(toDo, condo_id, e1);
					index = 0;
					if(!e1.getCondos().size()) break;
				}
			}while(ch != key.esc);
		}
		else {
			printTitleMenu("  Ver Condominios.", true);
			printTitleMenu("  Nao ha condominios", false);
			readkey();
		}
		break;
		/*********************************************** CONDOMINIOS ANTIGOS***************************************************/
	case 4:

		if(e1.getOldCondosHashTable().size()) {

			HashCondos oldCondos = e1.getOldCondosHashTable();
			HashCondos::iterator it = oldCondos.begin();


			do{
				oss << "    Condominio: " << (index + 1) << " / "
						<< oldCondos.size() << endl
						<< "                v" << endl
						<< "  Localizacao: " << (*it)->getLocalization() << endl << endl;
				printTitleMenu(oss.str(),true);
				printSubMenu("",false,false);

				oss.str("");
				coutUPDATE(subOP);

				ch = readkey();
				if(ch == key.down){
					if((index < (oldCondos.size() - 1)) &&
							(it != oldCondos.end())) {
						index++;
						++it;
					}
					else {
						index = 0;
						it = oldCondos.begin();
					}
				}
				else if (ch >= key.number0 && ch <= key.number9){
					Condo c = **it;
					toDo = handleUPDATE(subOP, ch);
					editOldCondo(toDo, c, e1);
					oldCondos = e1.getOldCondosHashTable();
					it = oldCondos.begin();
					index = 0;
					if(!e1.getOldCondosHashTable().size()) break;
				}
			}while(ch != key.esc);

		} else {
			printTitleMenu("  Ver Condominios Antigos.", true);
			printTitleMenu("  Nao ha condominios antigos", false);
			readkey();
		}


		break;

		/************************************************** PROPRIEDADES *****************************************************/
	case 5:
		if(e1.getCondos().size()) {
			condoToPrint = selectCondo(e1);
			if(condoToPrint != e1.getCondos().size()) {
				// vars[0] = condominio
				if(e1.getCondos()[condoToPrint]->getPropriedades().size()) {
					do {

						oss << "   Condominio: " << (condoToPrint + 1) << endl << endl
							<< "               ^" << endl << "  Propriedade: " << (index + 1) << " / "
							<< e1.getCondos()[condoToPrint]->getPropriedades().size()
							<< (e1.getCondos()[condoToPrint]->getPropriedades()[index]->
										existsOwner() ? " (Tem " :" (Nao tem ")
							<< "proprietario)" << endl
							<< "               v" << endl << endl;

						oss	<< "         Tipo: ";
						if(0 == e1.getCondos()[condoToPrint]->getPropriedades()[index]->getType()) {
							oss << "Residencia" << endl;
						}
						else if(1 == e1.getCondos()[condoToPrint]->getPropriedades()[index]->getType()) {
							oss << "Loja" << endl;
						}
						else {
							oss << "Escritorio" << endl;
						}

						if (e1.getCondos()[condoToPrint]->getPropriedades()[index]->
								existsOwner()) {

							oss << " Proprietario: " << e1.getCondos()[condoToPrint]->
									getPropriedades()[index]->
									getOwner()->getNome() << endl;

							oss << "     Contrato: ";
							if(0 == e1.getCondos()[condoToPrint]->getPropriedades()[index]->getContractType()) {
								oss << "Mensal" << endl;
							}
							else if(1 == e1.getCondos()[condoToPrint]->getPropriedades()[index]->getContractType()) {
								oss << "Semestral" << endl;
							}
							else {
								oss << "Anual" << endl;
							}
						}
						oss << "         Area: " << e1.getCondos()[condoToPrint]->getPropriedades()[index]->getArea() << endl
								<< "        Andar: " << e1.getCondos()[condoToPrint]->getPropriedades()[index]->getFloor();

						printTitleMenu(oss.str(),true);
						printSubMenu("",false,false);

						oss.str("");
						coutUPDATE(subOP);

						ch = readkey();
						if(ch == key.down) {
							if(index < (e1.getCondos()[condoToPrint]->getPropriedades().size() - 1)) {
								index++;
							}
							else {
								index = 0;
							}
						}
						else if(ch == key.up){
							if(0 < index) {
								index--;
							}
							else {
								index = (e1.getCondos()[condoToPrint]->getPropriedades().size() - 1);
							}
						}
						else if (ch >= key.number0 && ch <= key.number9) {
							toDo = handleUPDATE(subOP, ch);
							editProp(toDo, condoToPrint, index, e1);
							index = 0;
							if(!e1.getCondos()[condoToPrint]->getPropriedades().size()) break;
						}
					}while(ch != key.esc);
				}
				else {
					printTitleMenu("  Nao ha Propriedades", true);
					readkey();
				}
			}
		}
		else {
			printTitleMenu("  Ver Propriedades.", true);
			printTitleMenu("  Nao ha Condominios.", false);
			readkey();
		}
		break;
		/********************************************* EXT. INSPECTIONS *****************************************************/
	case 6:

		if(!itr.isAtEnd()) {
			do {
				oss << "         Nome: " << itr.retrieve().getName() << "   < " << itr.retrieve().getEmail() << " >"
					<< endl << "           v" << endl << endl
					<< "         Tipo: " << itr.retrieve().getInspectionType() << endl << endl
					<< "        Preco: " << itr.retrieve().getPrice() << endl << endl
					<< "  Localizacao: " << itr.retrieve().getLocalization();

				printTitleMenu(oss.str(),true);
				printSubMenu("",false,false);
				oss.str("");

				coutUPDATE(subOP);

				ch = readkey();
				if(ch == key.arrow) {
					ch = readkey();
					if(ch == key.down){

						itr.advance();

						if(itr.isAtEnd()) {
							itr = e1.getBSTIteratorIn();
						}
					}

				}
				else if(ch >= key.number0 && ch <= key.number9) {
					toDo = handleUPDATE(subOP,ch);

					// Prints all external inspections.
					if(toDo == 6) {
						printAllExtInspections(e1);
						waitForUser();
					}

					editExtInspection(toDo, itr.retrieve(), e1);
					if(e1.isExtInspectionsEmpty()) break;
					else itr = e1.getBSTIteratorIn();
					index = 0;
				}
			}while(ch != key.esc);
		}
		else {
			printTitleMenu("  Ver Inspeccoes Externas.", true);
			printTitleMenu("  Nao existem inspeccoes externas.", false);
			readkey();
		}
		break;
	case 7:

		if(e1.getSaloonReservations().size()) {

			do {

				HEAP_SALOON tmp = e1.getSaloonReservations();

				while(!tmp.empty()) {

					Reservation r = tmp.top();

					oss << " Ano: " << r.getYear() << ", Mes: " << r.getMonth()
							<< ", Condo. " << r.getCondo()->getID();

					if(r.getState()) {
						oss << setw(30) << "CONFIRMADO";
					} else {
						oss << setw(30) << "POR CONFIRMAR";
					}

					oss << endl;

					tmp.pop();
				}

				printTitleMenu(oss.str(),true);
				printSubMenu("",false,false);
				oss.str("");

				ch = readkey();

			}while(ch != key.esc);

		} else {
			printTitleMenu("  Ver Reservas do Salao de Eventos.", true);
			printTitleMenu("  Nao ha Resevas.", false);
			readkey();
		}
		break;

	default:
		break;
	}

	return false;
}

bool menu3(const size_t op, Company &e1) {
	vector<string> vars;
	size_t ch, subOP = 0;

	do {
		clearScreen();
		printMenu(op, true,e1);
		printMenu(op, subOP);
		vars.clear();

		ch = readkey();

		if(ch == key.arrow) {

			ch = readkey();
			if(key.up == ch) {
				if(0 < subOP) {
					subOP--;
				}
				else {
					subOP = (opcao.subOpt[op].size() - 1);
				}
			}
			else if(key.down == ch) {
				if(subOP < (opcao.subOpt[op].size() - 1)) {
					subOP++;
				}
				else {
					subOP = 0;
				}
			}
		}
		else if(ch == key.enter) {
			/****************************************************************************************************
			 * 											IMPRIMIR												*
			 ****************************************************************************************************/
			if(opcao.mainOpt[VER] == opcao.mainOpt[op]) {
				if(menu4(subOP,e1)) return true;
			}
			/****************************************************************************************************
			 * 												CRIAR												*
			 ****************************************************************************************************/
			else if(opcao.mainOpt[CRIAR] == opcao.mainOpt[op]) {
				clearScreen();
				switch(subOP) {
				case 0:
					createNewTec(e1);
					break;
				case 1:
					createNewPropriet(e1);
					break;
				case 2:
					createNewCondo(e1);
					break;
				case 3:
					createNewProp(e1);
					break;
				case 4:
					createNewContr(e1);
					break;
				case 5:
					createNewExtInspection(e1);
					break;
				default:
					break;
				}
			}
			/****************************************************************************************************
			 * 											PROCURAR												*
			 ****************************************************************************************************/
			else if(opcao.mainOpt[PROCURAR] == opcao.mainOpt[op]) {
				clearScreen();
				switch(subOP) {
				case 0:
					if (searchTec(e1)) {
						readkey();
					}
					break;
				case 1:
					if (searchPropriet(e1)) {
						readkey();
					}
					break;
				case 2:
					if (searchProp(e1)) {
						readkey();
					}
					break;
				default:
					break;
				}
			}
			/****************************************************************************************************
			 * 											SIMULAR												    *
			 ****************************************************************************************************/
			else if(opcao.mainOpt[SIMULAR] == opcao.mainOpt[op]) {
				clearScreen();
				switch(subOP) {
				case 0:
					// 1 MES
					e1.simulate(1);
					break;
				case 1:
					// 1 SEMESTRE (6 meses)
					e1.simulate(6);
					break;
				case 2:
					// 1 ANO (6 meses)
					e1.simulate(12);
					break;
				default:
					break;
				}

			}
		}
	}while(key.esc != ch);

	return false;
}

bool menu2(Company &e1) {
	size_t ch;
	size_t op = 0;

	do {
		clearScreen();
		printMenu(op,false,e1);

		ch = readkey();

		if(ch == key.arrow) {

			ch = readkey();
			if(key.left == ch) {
				if(0 < op) {
					op--;
				}
				else {
					op = (opcao.mainOpt.size() - 1);
				}
			}
			else if(key.right == ch) {
				if(op < (opcao.mainOpt.size() - 1)) {
					op++;
				}
				else {
					op = 0;
				}
			}
		}
		else if(ch == key.enter) {
			if(menu3(op, e1)) return true;
		}
	}while(key.esc != ch);

	/* Saves everything before exit. */
	e1.saveLog();
	gravaTecnicos(e1);
	gravaProprietarios(e1);
	gravaPropriedades(e1);
	gravaCondominios(e1);
	saveOldCondos(e1);
	saveFreeIDs(e1);
	saveExtInspections(e1);
	saveReservations(e1);
	gravaEmpresa(e1);

	cout << endl; waitForUser();

	return false;
}

void menu1() {
	string varTemp;
	vector<string> vars;
	map<string, pair<size_t, size_t> > toSend;
	map<string, size_t> periodicity_default;
	string options[] = {"  Nome: ", "  Saldo (enter para iniciar a zero): ",
			"  Limite para confirmacao de reservas (meses antes): ",
			"  Servico: "};

	size_t op = 0, index = 0, ch, subIndex = 0, custoTemp = 0;

	const size_t numVars = 7;
	const size_t numSlideVars = 2;

	Company e1;

	//setConsoleBigger();
	ScreenInit();
	OptionsInit();
	ProfessInit();

	do {
		if(index < numSlideVars) {
			printSubMenu("  Gestor de Condominios \n\n  Escolha uma opcao",false,true);
			printMenu(op);

			ch = readkey();
			if(key.arrow == ch) {
				ch = readkey();
				if(key.down == ch) {
					if(0 < op) {
						op -= 1;
					}
					else {
						op = numSlideVars - 1;
					}
				}
				else if(key.up == ch) {
					if(op < (numSlideVars - 1)) {
						op += 1;
					}
					else {
						op = 0;
					}
				}
			}
			else if(key.enter == ch) {
				if (1 > op) {
					index += 2;
				}
				else {
					try {

						e1 = loadCompany();

						index = numVars;
					}
					catch(FileError & e) {

						cout << "O programa vai terminar devido ao erro no ficheiro: "
								<< e.getFilename() << endl << endl;

						waitForUser();

						return;

					}
					catch(Erro_Menu<string,size_t> &error) {
						printTitleMenu("  Gestor de Condominios - ERRO", true);
						cerr << error.erro;
						readkey();
					}
					catch(Company_Error<string,int> &error) {
						printTitleMenu("  Gestor de Condominios - ERRO", true);
						cerr << error.error;
						readkey();
					}
				}
				op = 0;
			}
			else if(key.esc == ch) {
				return;
			}
		}
		else {
			printSubMenu("  Gestor de Condominios \n\n  Criar Empresa",true,true);
			if(options[op] == "  Servico: ") {
				printTitleMenu(options[op] + ":  " + profissao.profs[subIndex],false);
				cout << endl;
				if(index == 5) cout << "  Inserir custo das inspecoes (vazio = 100): ";
				else cout 			<< "  Inserir periodicidade (vazio = 1 mes): ";
			}
			else {
				cout << options[op];
			}

			getline(cin,varTemp);
			if(IsStringExit(varTemp)) {
				index = 0;
				op = 0;
				vars.clear();
			}
			// NOME
			else if(index == 2) {
				if(!IsStringEmpty(varTemp)) {
					vars.push_back(varTemp);
					index++;
					op++;
				}
			}
			// SALDO
			else if(index == 3){
				if(IsStringEmpty(varTemp)) {
					vars.push_back("0");
					index++;
					op++;
				}
				else if(IsStringNumber(varTemp)) {
					vars.push_back(varTemp);
					index++;
					op++;
				}
			}
			// CONFIRMACAO
			else if(index == 4) {
				if(IsStringEmpty(varTemp)) {
					vars.push_back("1");
					index++;
					op++;
				}
				else if(IsStringNumber(varTemp)) {
					vars.push_back(varTemp);
					index++;
					op++;
				}
			}
			// TECNICOS: CUSTO INSPECOES
			else if(index == 5) {
				if(IsStringEmpty(varTemp)) {
					custoTemp = 100;
					index++;
				}
				else if(IsStringNumber(varTemp)) {
					custoTemp = atoi(varTemp.c_str());
					index++;
				}
			}
			// TECNICOS: PERIODICIDADE INSPECOES
			else if(index == 6) {
				if(IsStringEmpty(varTemp)) {
					toSend[profissao.profs[subIndex]] = make_pair(atoi(varTemp.c_str()), custoTemp);
					periodicity_default[profissao.profs[subIndex]] = atoi(varTemp.c_str());
					subIndex++;
					index = 5;
				}
				else if(IsStringNumber(varTemp)) {
					toSend[profissao.profs[subIndex]] = make_pair(atoi(varTemp.c_str()), custoTemp);
					periodicity_default[profissao.profs[subIndex]] = atoi(varTemp.c_str());
					subIndex++;
					index = 5;
				}
			}
			if(subIndex >= profissao.profs.size()) {

				e1 = Company(vars[0],atoi(vars[1].c_str()), 1, 1, toSend, periodicity_default, atoi(vars[2].c_str()));
				index = numVars;

			}
		}
	}while(index < numVars);

	menu2(e1);

}



