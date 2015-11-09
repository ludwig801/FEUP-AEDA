/*
 * strings.h
 *
 *  Created on: Oct 11, 2013
 *      Author: kevin
 */

#ifndef STRINGS_H_
#define STRINGS_H_

#include <string>

using namespace std;

const string TITLES[] = {
						"  IMPRIMIR  ",
						"  CRIAR  ",
						"  PROCURAR  ",
						"  REMOVER  ",
						"  PAGAR  ",
						"  RECEBER  ",
						"  SIMULAR  " };


const string professions_list[6] = {
		"Alvenaria",
		"Eletricista",
		"Infra-estruturas",
		"Espacos Comuns",
		"Pintura",
		"Limpeza" };

/* MENU OPTIONS */
const string EDIT_NAME_1 =				"  [1] - Editar nome";
const string EDIT_BALANCE_2 =			"  [2] - Editar saldo";
const string RESET_DATE_3 =				"  [3] - Reiniciar data";
const string EDIT_PROFESSION_2 = 		"  [2] - Editar profissao";
const string EDIT_SALARY_3 =			"  [3] - Editar salario";
const string REMOVE_TECH_4 =			"  [4] - Remover tecnico";
const string REMOVE_OWNER_2 =			"  [2] - Remover proprietario";
const string REMOVE_PROPERTIES_1 =		"  [1] - Remover propriedades";
const string REMOVE_CONDO_2 =			"  [2] - Remover condominio";
const string CALL_EXT_INSPEC_3 =		"  [3] - Chamar Inspeccao Externa";
const string MAKE_RESERVATION_4 =		"  [4] - Marcar Reserva para o Salao de Eventos";
const string REACTIVATE_CONDO_1 =		"  [1] - Reativar Condominio";
const string REMOVE_OLD_CONDO_2 =		"  [2] - Remover condominio antigo";
const string REMOVE_OWNER_1 =			"  [1] - Remover proprietario";
const string REMOVE_PROPERTY_2 =		"  [2] - Remover propriedade";
const string EDIT_TYPE_2 =				"  [2] - Editar tipo";
const string EDIT_PRICE_3 =				"  [3] - Editar preco";
const string EDIT_LOCALIZATION_4 =		"  [4] - Editar localizacao";
const string REMOVE_5 =					"  [5] - Remover";
const string PRINT_ALL_EXT_INSPEC_6 =	"  [6] - Listar todas as Inspeccoes Externas";

const string ESC_INFO =					"     [ESC] - Sair";
const string ESC_INFO_2 =				" [ESC] - Gravar e Sair. ";
const string EXIT_CMD_INFO =			"     'exit' - Sair";

const string PRINT_YEAR = 				"Ano: ";
const string PRINT_MONTH =				" Mes: ";

/* WARNINGS */
const string REMOVE_ALL_CONTRACTS =		"        (esta opcao remove todas os contratos associados)";
const string REMOVE_ALL_PROP_CONTR =	"        (esta opcao remove todas as propriedades e contratos associados)";
const string REMOVE_ONLY_CONTRACT =		"        (esta opcao remove apenas o contrato)";
const string REMOVE_CONTRACT_ALSO =		"        (esta opcao remove tambem o contrato associado)";
const string CONTRACT_ALREADY_EXISTS = 	"  A propriedade ja tem um contrato associado.";
const string NO_EXT_INSPECTION_FOUND =  "Nenhuma inspeccao externa que cumpra os requisitos foi encontrada.";



/* STRINGS */
const string IMPRIME_EMPRESA = 			"Empresa";
const string IMPRIME_CONDOMINIO = 		"Condominio";
const string IMPRIME_TECNICOS = 		"Tecnicos";
const string IMPRIME_PROPRIETARIOS = 	"Proprietarios";
const string IMPRIME_PROPRIEDADES = 	"Propriedades";

const string CRIA_CONDOMINIO = 			"Condominio";
const string CRIA_PROPRIEDADE = 		"Propriedade";
const string CRIA_CONTRATO = 			"Contrato";
const string CRIA_TECNICO = 			"Tecnico";
const string CRIA_PROPRIETARIO = 		"Proprietario";

const string PROCURAR_PROPRIETARIO = 	"Proprietario";

const string REMOVE_CONDOMINIO = 		"Condominio";

const string PAGAR_TECNICOS = 			"Tecnicos";

const string RECEBER_PARCELAS = 		"Parcelas";

const string SIMULAR_MES = 				"Mes";
const string SIMULAR_ANO = 				"Ano";

/* USER ERRORS */
const string INVALID_DATE =				"DATA INVALIDA!";

/* PRINT MENUS */
const string PRINT_EXT_INSPECTION =		"  Ver Inspeccoes Externas";
const string BY_INSPEC_TYPE =			"  Por tipo de inspeccao";
const string BY_PRICE =					"  Por preco";
const string CLOSEST = 					"Mais perto";
const string CHEAPEST =					"Mais barato";
const string PRINT_PROPS =				"  Imprimir Propriedades";

/* CREATE MENUS */
const string CREATE_CONDO =				"  Criar Condominio";
const string CREATE_TECH =				"  Criar Tecnico";
const string CREATE_OWNER =				"  Criar Proprietario";
const string CREATE_PROP =				"  Criar Propriedade";
const string ASSOCIATE_CONTRACT =		"  Associar Contrato";
const string CREATE_EXT_INSPECTION =	"  Criar Inspeccao Externa ";
const string MAKE_RESERVATION =			"  Marcar Reserva ";
const string INSERT =					"  Inserir ";

/* REMOVE MENUS */

const string NO_CONDOS =				"  Nao ha condominios.";
const string NO_OWNERS =				"  Nao ha proprietarios.";
const string NO_PROPS =					"  Nao ha propriedades.";


/* EDIT MENUS */
const string EDIT_COMPANY =				"  Editar Empresa ";
const string EDIT_TECH = 				"  Editar Tecnico ";
const string EDIT_OWNER =				"  Editar Proprietario ";
const string EDIT_EXT_INSPECTION =		"  Editar Inspeccao Externa ";
const string INSERT_NAME = 				"  Inserir nome: ";
const string INSERT_BALANCE =			"  Inserir saldo: ";
const string INSERT_SALARY =			"  Inserir salario: ";
const string INSERT_PRICE =				"  Inserir preco: ";
const string INSERT_LOCALIZATION =		"  Inserir localizacao: ";
const string RESTART_DATE =				"  Reiniciar data ";
const string YES =						"  SIM";
const string NO =						"  NAO";
const string REMOVE_PROPERTY =			"  Remover Propriedade";
const string REMOVE_PROPERTIES = 		"  Remover Propriedades ";
const string REMOVE_CONDO =				"  Remover Condominio ";
const string REMOVE_TECH =				"  Remover Tecnico ";
const string REMOVE_OWNER =				"  Remover Proprietario ";
const string REMOVE_CONTRACT =			"  Remover Proprietario (Contrato) ";
const string REMOVE_EXT_INSPECTION =	"  Remover Inspeccao Externa ";
const string REACTIVATE_OLD_CONDO =		"  Reativar Condominio Antigo ";
const string CALL_EXT_INSPECTION =		"  Chamar Inspeccao Externa ";

/* SEARCH MENUS */
const string SEARCH_TECH =				"  Procurar Tecnico";
const string NO_TECHS =					"  Nao ha Tecnicos.";
const string SEARCH_BY =				"  Procurar por: ";
const string BY_PROFESSION =			"  Profissao: ";
const string SEARCH_RESULTS =			"' - Resultados da procura";
const string NO_RESULTS =				"Nao ha resultados que coincidam com os parametros pedidos.";
const string INSERT_MIN_SALARY =		"  Inserir teto minimo (enter para ignorar): ";
const string INSERT_MAX_SALARY =		"  Inserir teto maximo (enter para ignorar): ";

/* MISCELLANEOUS */
const string UP_ARROW =						"  ^";
const string DOWN_ARROW =					"  v";
const string RIGHT_ARROW =					"-> ";
const string UP_ARROW_MORE_SPACE =			"              ^";
const string DOWN_ARROW_MORE_SPACE =		"              v";
const string BORDER_VERTICAL = 				"|";
const string BORDER_HORIZONTAL_UP = 		"-";
const string BORDER_HORIZONTAL_DOWN = 		"_";
const string BORDER_ELBOW_UPPER_LEFT = 		"#";
const string BORDER_ELBOW_UPPER_RIGHT = 	"#";
const string BORDER_ELBOW_LOWER_LEFT = 		"#";
const string BORDER_ELBOW_LOWER_RIGHT = 	"#";

/* PATHS */
const string COMPANY_CSV = 				"Company.csv";
const string CONDOS_CSV = 				"Condos.csv";
const string PROPERTIES_CSV = 			"Properties.csv";
const string OWNERS_CSV = 				"Owners.csv";
const string TECHNICIANS_CSV = 			"Technicians.csv";
const string LOG_CSV =					"Log.csv";
const string LOG =						"Log"; /* Sem extensão */
const string EXT_INSPECTIONS_CSV =		"ExtInspections.csv";
const string RESERVATIONS_CSV = 		"Reservations.csv";
const string OLD_CONDOS_CSV =			"OldCondos.csv";
const string FREE_IDS_CSV =					"FreeIDs.csv";


/* HEADERS */
const string COMPANY_HEADER =			"Name; Balance; Month; Year; ConfirmationLimit";
const string CONDOS_HEADER =			"ID; Localization; TotalProperties";
const string OLD_CONDOS_HEADER =		"ID; Localization; TotalProperties";
const string PROPERTIES_HEADER =		"ID_Condo; PropertyType; Area; Floor; Owner; ContractType; RemainingMonths";
const string OWNERS_HEADER = 			"Name";
const string TECHNICIANS_HEADER = 		"Name; Profession; Wage; Disponibility";
const string EXT_INSPECTIONS_HEADER = 	"Name; Localization; Type; Price";
const string RESERVATIONS_HEADER =		"ID_Condo; Year; Month; State";
const string FREE_IDS_HEADER = 			"ID";

/* CHARS */
const string DELIMITER = 				";";

#endif /* STRINGS_H_ */
