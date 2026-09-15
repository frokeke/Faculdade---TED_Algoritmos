#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

void delaynaMsg(string texto, int ms = 40) {
    for (char c : texto) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(ms));
    }
}


struct Personagem {
    string nome;
    string classe;
    int nivel;
    int HP;
    int HPMax;
    int dano;
    int defesa;
    int MP;
    int MPMax;
	int FOR;
	int DEX;
	int CON;
	int INT;

    vector<string> inventario;
};


Personagem criarPersonagem() {
    Personagem p;

    cout << "Digite o nome do seu personagem: ";
    getline(cin, p.nome);

    cout << "\nEscolha sua classe:\n";
    cout << "1. Guerreiro\n2. Mago\n3. Bárbaro\n> ";
    int op;
    cin >> op;

    p.nivel = 1;

    switch (op) {
        case 1:
            p.classe = "Guerreiro";

            p.FOR = 2;
			p.DEX = 3;
			p.CON = 2;
			p.INT = 2;

            p.HP = p.HPMax = 100 + (p.CON * 2) + rand() % 20;
            p.MP = p.MPMax = 20;
            p.dano = 10 + p.FOR + (p.DEX * 2) ;
            p.defesa = 10 + p.DEX;


            break;

        case 2:
            p.classe = "Mago";

            p.FOR = 0;
			p.DEX = 2;
			p.CON = 1;
			p.INT = 4;

            p.HP = p.HPMax = 50 + (p.CON * 2) + rand() % 20;;
            p.MP = p.MPMax = 60 + (p.INT * 2) + p.nivel;
            p.dano = 10 + p.FOR + (p.DEX * 2);
            p.defesa = 10 + p.DEX;


            break;

        case 3:
            p.classe = "Barbaro";

            p.FOR = 4;
			p.DEX = 2;
			p.CON = 4;
			p.INT = 0;

            p.HP = p.HPMax = 120 + (p.CON * 2) + rand() % 20;;
            p.MP = p.MPMax = 10 + (p.INT * 2);
            p.dano = 10 + p.FOR + (p.DEX * 2);
            p.defesa = 10 + p.DEX;


            break;

    }



    p.inventario.push_back("Pocao de Cura");
    p.inventario.push_back("Espada quebrada");

    return p;
}

Personagem gerarInimigo(int nivel) {
    Personagem i;
    string nomes[] = {"Globin", "Unicornio Jeremias", "Aranha gigante"};
    i.nome = nomes[rand() % 3];
    i.classe = "Monstro";
    i.nivel = nivel;
    i.HP = i.HPMax = 40 + rand() % 40 + nivel * 5;
    i.MP = i.MPMax = 0;
    i.dano = 10 + rand() % 10 + nivel * 2;
    i.defesa = 8 + rand() % 5 + nivel;

    return i;
}

string gerarItem() {
    vector<string> itens = {
        "Broadsword",
        "Pocao de Cura",
        "Anel de Proteçao",
        "Escudo de Madeira",
        "Pocao de Mana",
        "Pergaminho Arcano"
    };
    return itens[rand() % itens.size()];
}

void mostrarInventario(Personagem &p) {
    cout << "\n==== INVENTARIO ====\n";

    sort(p.inventario.begin(), p.inventario.end());

    for (auto &item : p.inventario) {
        cout << "- " << item << "\n";
    }

    cout << "\nBuscar item (digite nome exato): ";
    cin.ignore();
    string busca;
    getline(cin, busca);

    if (binary_search(p.inventario.begin(), p.inventario.end(), busca))
        cout << "Item encontrado!\n";
    else
        cout << "Nao encontrado.\n";

    cout << "=========================\n";
}

int usarMagia(Personagem &mago, Personagem &alvo) {

    if (mago.classe != "Mago") {
        cout << "\nVocê nao sabe usar magia!\n";
        return 0;
    }

    cout << "\n=== MAGIAS ===\n";
    cout << "1. Bola de Fogo (custa 25 MP e causa " << 25 + mago.nivel * 2 + mago.INT << " de dano)\n";
    cout << "2. Raio Arcano (custa 10 MP e causa " << 15 + mago.nivel + mago.INT << " de dano)\n";
    cout << "3. Explosao Arcana (custa 40 MP e causa " << 40 + mago.nivel * 3 + mago.INT<< " de dano)\n";
    cout << "Escolha uma magia: ";
    int m;
    cin >> m;

    int dano = 0;
    int custo = 0;

    switch (m) {
        case 1:
            custo = 25;
            dano = 25 + mago.nivel * 2 + mago.INT;
            break;
        case 2:
            custo = 10;
            dano = 15 + mago.nivel + mago.INT;
            break;
        case 3:
            custo = 40;
            dano = 40 + mago.nivel * 3 + mago.INT;
            break;
        default:
            cout << "Magia invalida.\n";
            return 0;
    }

    if (mago.MP < custo) {
        cout << "\nMP insuficiente\n";
        return 0;
    }

    mago.MP -= custo;

    delaynaMsg("\nVoce conjura uma magia!\n", 30);

    return dano;
}


bool batalha(Personagem &j, Personagem i) {
    delaynaMsg("\nUm " + i.nome + " apareceu\n\n");

    while (j.HP > 0 && i.HP > 0) {

        cout << j.nome << " HP: " << j.HP << "/" << j.HPMax
             << " | MP: " << j.MP << "/" << j.MPMax << "\n";
        cout << i.nome << " HP: " << i.HP << "/" << i.HPMax << "\n";

        cout << "\n1. Atacar\n2. Defender\n3. Fugir\n4. Inventario\n5. Usar Magia\n> ";
        int acao;
        cin >> acao;

        int ataqueJog = 10 + j.FOR + j.DEX * 2;
        int ataqueIni = 10 + (rand() % 8) ;

        if (acao == 1) {
            delaynaMsg("Voce ataca!\n", 30);
			if(ataqueJog > i.defesa){
				i.HP -= j.dano;
			}
			else{
				delaynaMsg("...Mas erra\n", 30);
			}
        }
        else if (acao == 2) {
            delaynaMsg("Voce se defende!\n", 30);
            i.dano /= 2;
        }
        else if (acao == 3) {
            if (rand() % 100 < 40) {
                delaynaMsg("Voce fugiu!\n");
                return false;
            } else {
                delaynaMsg("Falhou em fugir!\n");
            }
        }
        else if (acao == 4) {
            mostrarInventario(j);
            continue;
        }
        else if (acao == 5) {
            int dano = usarMagia(j, i);
            i.HP -= dano;
        }

        if (i.HP > 0) {
            delaynaMsg("O " + i.nome + " ataca\n", 30);
			if(ataqueIni > j.defesa){
				j.HP -= i.dano;
			}
			else{
				delaynaMsg("...Mas erra\n", 30);
			}
        }

        cout << "---------------------\n";
    }

    if (j.HP <= 0) {
        delaynaMsg("Voce morreu :(\n");
        return false;
    }

    delaynaMsg("Vitoria!\n");


    string loot = gerarItem();
    delaynaMsg("Voce encontrou: " + loot + "!\n");
    j.inventario.push_back(loot);

    j.nivel++;
    j.HP = min(j.HP + j.CON, j.HPMax);
    j.MP = min(j.MP + j.INT, j.MPMax);
    j.dano += 5;
    j.defesa += 3;

    return true;
}

int main() {
    srand(time(0));

    delaynaMsg("=== TED sobre RPG :) ===\n\n");
    cin.ignore();

    Personagem jogador = criarPersonagem();

    bool jogando = true;
    while (jogando && jogador.HP > 0) {

        Personagem inimigo = gerarInimigo(jogador.nivel);

        bool venceu = batalha(jogador, inimigo);
        if (!venceu) break;

        cout << "\nContinuar? (1 = sim / 0 = não): ";
        int op;
        cin >> op;
        if (!op) jogando = false;
    }

    delaynaMsg("\nObrigado por jogar :)\n");
    return 0;
}
