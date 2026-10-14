#include <Arduino.h>

#include <string.h> // strlen, strcpy, strcat, strcmp, strchr.
#include <stdlib.h> // atoi

void textoChar();
void textoString();

void setup() 
{
  Serial.begin(9600);
  Serial.println();
  textoChar();
  textoString();
}

void loop() 
{
  
}

void textoChar()
{
  //texto literal.
  //use const char* quando o texto nao sera alterado.
  const char cidade[] = "Sao Paulo";
  Serial.println(cidade);

  //descobrindo o tamanho do texto.
  //strlen conta quantos caracteres antes do '\0'.
  int tamanhoTextoCidade = strlen(cidade);
  Serial.print("Comprimento do texto: ");
  Serial.println(tamanhoTextoCidade);

  //descobrindo o tamanho ocupado.
  //o sizeof() retornara um byte a mais que o comprimento por causa do '\0'
  int tamanhoVariavelCidade = sizeof(cidade);
  Serial.print("Espaço utilizado: ");
  Serial.println(tamanhoVariavelCidade);

  //o caractere \0 e colocado automaticamente quando escrevemos um texto entre " ".
  char vetorTexto[7] = {'R', 'a', 'f', 'a', 'e', 'l', '\0'};
  Serial.println(vetorTexto);

  //comparar texto
  const char* cidade1 = "Sao Caetano";
  const char* cidade2 = "Sao Caetano ";

  //strcmp analiza a ordem lexica das palavras, se a primeira palavra vem antes
  //que a segunda, o valor retornado sera menos que zero, se a primeira palavra
  //vem apos a segunda, o retorno sera maior que zero.
  if(strcmp(cidade1, cidade2) == 0)
    Serial.println("Os textos sao iguais");

  else
    Serial.println("Os textos sao diferentes");

  //===========================
  // TEXTO EDITAVEL COM char[]
  //===========================

  char nomeAluno[20] = "Rafail"; //comeca a contagem do zero: 0, 1, 2... .
  Serial.println(nomeAluno);

  //alterando caracteres individualmente.
  nomeAluno[4] = 'e';
  Serial.println(nomeAluno);

  //copiando outro texto para dentro do vetor.
  //cuidado: o vetor precisa ter espaco suficiente.
  strcpy(nomeAluno, "Eduardo");
  Serial.println(nomeAluno);

  //concatenando de texto ao final, juntar dois textos.
  char frase[40] = "Ola ";
  strcat(frase, "Mundo!");
  Serial.println(frase);

  //procurando um caractere no texto.
  char* posicaoLetra = strchr(frase, 'M'); // retorna a posicao memoria, ira imprimir ate achar \0. 

  if (posicaoLetra != NULL) //NULL = \0
  {
    Serial.print("Letra encontrada - ");
    Serial.println(posicaoLetra);
  }

  else
  {
    Serial.println("Letra nao encontrada");
  }

  //convertendo texto numerico para inteiro.
  char idadeTexto[] = "45"; //52, 53, \0.
  int idade = atoi(idadeTexto);
  Serial.println(idade);

  //montando texto
  char buffer[100];
  char* local = "Sala de aula";
  float temperatura = 26.4;
  int umidade = 58;

  // \n = mudanca de linha.
  // \r = retorno ao comeco da linha.
  sniprintf(buffer, sizeof(buffer), "%s | Temp.: %f | Umid.: %d %% \n\r", local, temperatura, umidade);
  // %s = string(formatar texto), %f = float(numero decimal), %d = int(numero inteiro), %% = porcento.
  Serial.print(buffer);
  Serial.println("Senai");

  /*
  snprintf = monta um texto dentro de um vetor de char.
  sintaxe: snprintf(variavelOndeSeraMontadoOTexto, tamanhoMaximoDoTexto, textoComEspecificadores, itensDeFormato)
  isso e muito util quando depois voce quer:
   - salvar o texto em uma variavel;
   - mandar para o display;
   - imprimir na serial;
   - enviar por MQTT(IoT);
  */

  /*ESPECIFICADORES:

  %d ou %i = int
  %u       = unsigned int 
  %ld      = long
  %lu      = unsigned long
  %f       = float
  %e       = notacao cientifica
  %g       = float, formato mais curto
  %c       = char
  %s       = char*(string)
  %x ou %X = hexadecimal minusculo/maiusculo
  %o       = octal
  %p       = ponteiro
  %%       = porcento(%)

  */

  /*
  FLAG, LARGURA E PRECISAO

  %5d    - imprime com largura minima de 5, alinhado a direita [    3], [  100], [10000000]
  %.4d   - imprime com largura minima de 4, alinhado a esquerda [3   ], [100 ], [123456]
  %03d   - completa com zeros a esquerda, [003]
  %+d    - sempre mostra o sinal [+3], [-3]
  %.2f   - 2 casas decimais num float
  %4.2f  - largura minima 4 a direita com 2 casas decimais
  %02X   - hexadecimal com 2 digitos [OF] [3A]
  %#x    - imprime o prefixo 0x [0x2a] [0xF]
  %.3s   - somente os 3 primeiros caracteres da string
  %*d    - largura passada como argumento ex.:
                                      int largura = 3;
                                      int numero = 9;
                                      snprintf(buffer,sizeof(buffer), "numero %*d", largura, numero)
                                      Serial.print(buffer) -> [  9]
  */
}

void textoString()
{
  //===================
  //   USANDO String
  //===================
  
  String nome = "Rafael";
  String curso = "Logica de programacao";
  String mensagem = "Ola";

  //concatenando string.
  mensagem = mensagem + ", " + nome + "! Bem-vindo ao curso de " + curso + ".";
  Serial.println(mensagem);

  //tamanho da String
  int tamanhoMensagem = mensagem.length();
  Serial.print("Tamanho da String em letras: ");
  Serial.println(tamanhoMensagem);

  //acessando um caracter em uma posicao especifica.
  char primeiraLetra = mensagem.charAt(0);
  Serial.print("Primeira letra: ");
  Serial.println(primeiraLetra);

  //tambem e possivel acessar com conchetes.
  char segundaLetra = mensagem[1];
  Serial.print("Segunda letra: ");
  Serial.println(segundaLetra);

  //procurando um texto dentro da String.
  int posicaoTextoProcurado = mensagem.indexOf("curso");
  Serial.println(posicaoTextoProcurado);

  //extraindo um texto dentro da String.
  int inicioNomeCurso = posicaoTextoProcurado + 9; //posicao da palavra curso + 9 caracteres
  Serial.println(mensagem.substring(inicioNomeCurso, tamanhoMensagem - 1)); // -1 tira o ponto final.

  //substituindo um texto dentro da string.
  mensagem.replace("Ola, ", "Oi, tudo bom? ");
  Serial.println(mensagem);

  //convertendo para maiusculas.
  mensagem.toUpperCase();
  Serial.println(mensagem);

  //convertendo pra minusculas.
  mensagem.toLowerCase();
  Serial.println(mensagem);

  //convertendo texto numerico pra inteiro.
  String textoNumero = "123";
  int numero = textoNumero.toInt();
  Serial.println(numero * 2);

  //verificando se a string esta vazia.
  String textoVazio = "";
  if(textoVazio.length() == 0)
    Serial.println("O texto esta vazio");

  //convertendo String para const char.
  //isso e util quando alguma biblioteca espera texto estilo c.
  const char* textoComoChar = mensagem.c_str();
  Serial.println(textoComoChar);

}