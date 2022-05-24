#include <iostream>     // std::cout
#include <algorithm>    // std::shuffle
#include <array>        // std::array
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include <utility>
#include <vector>
#include <fstream> 
#include <iomanip>
#include <string>

using namespace std;

/*------- PALHETA DE CORES --------*/
#define ANSI_COLOR_RED      "\x1b[31m" 
#define ANSI_COLOR_GRAY     "\e[0;37m"
#define ANSI_COLOR_RESET   "\x1b[0m" 
#define ANSI_COLOR_GREEN	"\e[0;32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_BLACK "\033[30m"
/*--------------------------------*/
/*--------- BACKGROUNDS----------*/
#define BG_BLACK    "\033[40m"
#define BG_RED      "\033[41m"
#define BG_GREEN    "\033[42m"
#define BG_YELLOW   "\033[43m"
#define BG_BLUE     "\033[44m"
#define BG_MAGENTA  "\033[45m"
#define BG_CYAN     "\033[46m"
#define BG_GRAY     "\033[47m"
#define BG_RESET    "\033[0m"
/*-------------------------------*/

/*---- "Objeto Player" -------*/
struct Player{
  string name;
  vector<char> cards;
};

/*-------- FUNÇÃO DA BUSCA SEQUENCIAL ------------*/

bool buscaSequencia(vector<char> cartas, int n){
  int tem_trinca = 0;
  
  for(int i = 0; i < n; i++){
    if(i > 0){
      if(cartas[i] == cartas[i - 1]){
        tem_trinca++;
      }
    }
  }
  if(tem_trinca == 2){
      return true;
  } else {
      return false;
  }
}
/*-------- BUSCA SEQUÊNCIAL ----------*/
pair<bool, int> buscaDescart(vector<char> cartas, char carta_descart){
  pair<bool, int> position_card_status;
  
  for(int i = 0; i < cartas.size(); i++){
    if(cartas[i] == carta_descart){
      position_card_status.second = i;
      position_card_status.first = true;
      break;
    }
  }
  return position_card_status;
}

/*------- AGREGAR NOVOS DADOS AO SCORES ----------*/
/*void atribuirScores(Player player_scores){
  auto now = chrono::system_clock::now();
  time_t t = chrono::system_clock::to_time_t(now);
  cout<<"Hora atual: "<<put_time(localtime(&t), "%c")<<endl;
  
  std::ifstream arquivo_scores;
  arquivo_scores.open("scores", std::ios::out | std::ios::in);
  if(!arquivo_scores){
    std::cout<< ANSI_COLOR_RED "ARQUIVO scores.txt NÃO ENCONTRADO!, por favor criar arquivo txt chamado scores.txt" ANSI_COLOR_RESET << std::endl;
  } else {
    string trinca = std::to_string(player_scores.cards[0]);
    string name = std::to_string(player_scores.name[0]);
    string linha = " Vencedor: "+=name;
  
    arquivo_scores << "\n Vencedor: "+=name;
    Valor da trinca: "+=trinca;
    arquivo_scores = name;
  }
  arquivo_scores.close();
}*/


int main() {
  /*-------- TESTE COM BARALHO ESTÁTICO ----------*/
  vector<char> chosen_cards {'4','4','4','5','5','5','6','6','6','1'};
  Player player[3];
  int cont = 0;
  /*------- NOME E SORTEIO DE CARTAS POR JOGADOR ----------*/
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  shuffle (chosen_cards.begin(), chosen_cards.end(), default_random_engine(seed));

  for(int i = 0; i < 3; i++){
    string name_dinamic;
    cout<<"Digite seu nome: ";
    cin >> name_dinamic;
    player[i].name = name_dinamic;
  }
  
  int a = 0, b = 0, c = 0;
  for(char card_for_player : chosen_cards){ //using iterator to separate letters
      if(cont <= 3){
        player[0].cards.push_back(card_for_player);
        a++;
      }
      else if(cont > 3 && cont <= 6){
        player[1].cards.push_back(card_for_player);
        b++;
      } else if(cont > 6 && cont < 10){
        player[2].cards.push_back(card_for_player);
        c++;
      }
    cont++;
  }
  /*------ AMOSTRA DO TABULEIRO ATUAL --------*/
  for(Player play : player){
    cout<< ANSI_COLOR_BLUE "-------------------------------------------" ANSI_COLOR_RESET<<endl;
    cout<<"Jogador "<<play.name << " | Cartas atuais: ";
    for(char cards : play.cards){
      cout<<cards<<" ";
      
    }
    cout<< ANSI_COLOR_BLUE "\n-------------------------------------------" ANSI_COLOR_RESET<<endl;
  }

  char carta_adiante;
  
  cout<<"Tudo bem, vamos começar!\n"<<endl;
  cout<< BG_BLACK ANSI_COLOR_MAGENTA " B E M   V I N D O(A)!! " ANSI_COLOR_RESET BG_RESET <<endl;

  char carta_descart;
  /*----- INICIO DO JOGO ------*/
  while(true){
    cont = 0;

    for(int contJog = 0; contJog < 3; contJog++){
      if(player[contJog].cards.size() != 4){
        player[contJog].cards.push_back(carta_descart);
      }
      cout<<player[contJog].name<<" Com suas cartas atuais: ";
      for(char cards : player[contJog].cards){
        cout<<cards;
      }
      cout<<" Escolha a carta que quer descartar: "<<endl;
      cin>>carta_descart;
      
      pair<bool, int> procurando_carta_descart = buscaDescart(player[contJog].cards, carta_descart);
      if(procurando_carta_descart.first == true){
        vector<char> vetor_dinamico;
        int carta_sera_excluida = 0;
        
        for(int proc = 0; proc < player[contJog].cards.size(); proc++){
          if(player[contJog].cards[proc] != player[contJog].cards[procurando_carta_descart.second]){
            vetor_dinamico.push_back(player[contJog].cards[proc]);
          } else {
            if(carta_sera_excluida == 1){ //então uma ja foi excluida, então essa que é repetira irá estar no novo baralho.
              vetor_dinamico.push_back(player[contJog].cards[proc]);
            } else
              if(carta_sera_excluida < 1){
                carta_sera_excluida++;
              }
          }
        }
        
        player[contJog].cards.erase(player[contJog].cards.begin(), player[contJog].cards.end());
        player[contJog].cards = vetor_dinamico;

        cout<<"Novo baralho do jogador: "<<endl;
        for(char vet : player[contJog].cards){
          cout<<vet;
        }
      } else {
        cout<< ANSI_COLOR_RED "ERROR CARTA NÃO ACHADA! >:(" ANSI_COLOR_RESET <<endl;
        cout<< ANSI_COLOR_RED "Terminando jogo..." ANSI_COLOR_RESET <<endl;
        return -1;
      }
      
      bool result_busca =  buscaSequencia(player[contJog].cards, player[contJog].cards.size());
      if(result_busca == true){
        cout<< ANSI_COLOR_GREEN " \nJOGADOR "<<player[contJog].name <<" ACHOU TRINCA! " ANSI_COLOR_RESET <<endl;
        return -1;
      } else {
        cout<<"\nPróximo..."<<endl;
      } 
      
      cont++;
    }
  } 
}