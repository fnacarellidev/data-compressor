# Labs 4º Edição

## Desafio

O desafio consiste no desenvolvimento de uma aplicação de análise e compressão de dados. Essa aplicação utilizará o algoritmo de compressão Huffman e poderá receber múltiplos dados onde, uma vez que comprimido deve ser descomprimido e coletar informações pertinentes para a análise do processo e dado.

Para isso, você criará dois programas: `encoder` e `decoder`. O encoder receberá o dado a ser comprimido e exibirá suas informações vindas do decoder. Já, o ```decoder``` descomprimirá o dado e irá enviá-lo ao ```encoder``` com suas informações, onde será exibido. Os programas devem se comunicar utilizando *shared memory operations*.

A linguagem C será utilizada para o desenvolvimento e não há bibliotecas externas permitidas.

## O que eu aprendi no projeto
Pela primeira vez vi a estrutura de dado de árvore binária, não fazia ideia de como funcionava uma árvore binária e agora ja tenho algumas noções básicas, aprendi muito sobre memoria compartilhada também, eu utilizei bastante no projeto, também aprendi sobre semáforos pra fazer com que um programa aguarde que o outro leia a informação antes de fechar os segmentos de memória.

## Como navegar pelo projeto
[`ENCODER_DEPENDENCIES`](./encoder_dependencies) - arquivos exclusivos do programa encoder

[`STD_DEPENDENCIES`](./std_dependencies) - arquivos que ambos os programas dependem

[`DECODER_DEPENDENCIES`](./decoder_dependencies) - arquivos exclusivos do programa decoder


---
## Tecnologias utilizadas no desenvolvimento do projeto
- **C**: o projeto foi desenvolvido inteiro na linguagem C.
- [**git**](https://git-scm.com/): para o versionamento dos arquivos do projeto;
- [**github**](https://github.com/): para hospedagem dos arquivos;
---

## Conceitos
### A codificação de Huffman
Trata-se de uma codificação de caracteres que permite compactar arquivos de texto, ou seja, representar um arquivo de texto A por um arquivo de bits B bem menor. O algoritmo de Huffman calcula uma tabela de códigos sob medida para o arquivo A de modo que o arquivo B seja o menor possível, e também não tem perda alguma de conteúdo.
### Memória Compartilhada
Memória compartilhada é um endereço que pode ser acessado simultaneamente por multiplos processos, para que tenha uma comunicação entre esses processos, e também pode vir a evitar redundância de código.
#### SHM
>ftok(char *filename, int proj_id) : Gera uma chave única com base no *filename* e *proj_id* especificado<br />

>shmget(key_t key, size_t size, int shmflg) : Retorna um *shmid* com base na chave *key* e de tamanho *size*<br />

>shmat(int shmid, const void *shmaddr, int shmflg) : Retorna um *void contendo o endereço identificado por *shmid*<br />

>int shmdt(const void *shmaddr) : Desacopla o endereço passado, retorna -1 caso falhe.<br />

## Semáforos
Os semáforos são uma ótima ferramenta para sincronização de processos e multithreading, os semáforos tem 2 operações possiveis (sem_wait() e sem_post()), agora o que elas fazem?

>sem_wait() : Tenta decrementar o valor do semáforo caso ele seja maior que zero, se ele for igual a zero, o processo espera até que a variável passe a ter um valor maior que zero, quando tiver, ele decrementa esse valor e deixa de esperar, o processo volta a sua execução.

>sem_post() : Incrementa o valor do semáforo, é basicamente uma maneira de dizer para um semáforo parar de esperar, quando o valor for incrementado, ele poderá ser decrementado e o wait() cessará.

---

## Como utilizar os programas
Primeiro execute o ```encoder``` e passe para ele via linha de comando o dado que você deseja comprimir, por enquanto apenas no formato de texto, arquivos não são suportados.<br />
Depois disso o ```encoder``` irá codificar e compactar o dado recebido e aguardar até que o ```decoder``` seja executado e consuma as informações que foram passadas para ele, então logo em seguida execute o ```decoder``` que ele irá decodificar e descompactar a informação que foi enviada para ele.<br />
Depois disso o ```encoder``` irá escrever na tela informações a respeito do processo de compactação/descompactação como o número de bytes da informação original e da comprimida, e também o tempo que levou pra realizar a descompactação, e então ambos os processos irão finalizar e você terá dois arquivos no diretório local, um chamado ```compact.fabin``` que é o dado comprimido, e outro arquivo chamado ```decompressed.fabin``` com o conteúdo total, sem perda nenhuma.

---
## Como compilar o programa
1. Clone o repositório
```shell
git clone https://github.com/42sp/42labs-selection-process-v4-fnacarellidev.git
```
2. Entre no diretório e rode ```make``` e dois executáveis serão gerados, um chamado de encoder, e um de decoder.

---
## Meu Projeto
![bla](https://github.com/42sp/42labs-selection-process-v4-fnacarellidev/blob/master/info/img01.jpeg)
<br />
O meu programa funciona da seguinte maneira: É esperado que o encoder seja executado primeiro com as informações sendo passadas para ele, depois de receber as informações ele irá extrair seus caractéres e suas respectivas frequencias, o próximo passo é construir a [Árvore de Huffman](https://pt.wikipedia.org/wiki/Codifica%C3%A7%C3%A3o_de_Huffman), depois que a Árvore é criada o ```encoder``` decodifica e comprime a informação recebida, e então ele envia as informações para o ```decoder``` e a partir desse momento o ```encoder``` fica esperando o ```decoder``` fazer a parte dele.

O ```decoder``` depois de recebidas as informações do ```encoder``` ele decodifica e descompacta as informações, cria um arquivo com o conteúdo descompactado e envia informações-chave para o ```encoder``` (Informação que foi descomprimida, Bytes totais da informação descomprimida, Bytes totais da informação comprimida, e o tempo de execução da descompactação em microssegundos(μs), e então sinaliza ao ```encoder``` para voltar a processar e seu processo acaba.

O ```encoder``` imprime todas as informações que foram tratadas pelo decoder e finaliza o programa, liberando a memória alocada.

---
## Funções chave do projeto
>t_min_heap_node \*get_huffman_tree(\*uniq_chars, \*freqs) : Essa função recebe como parâmetro um array de caracteres e um array de frequências (as posições devem corresponder) e retorna a Árvore de Huffman pronta.

>void \*attach_memory_block(char \*filename, int size, int key_val) : Essa função é uma forma mais simples de criar um segmento de memória, ao invés de criar varias variáveis como a chave e shmid ela simplesmente omite essas etapas e retorna o ponteiro para o bloco compartilhado.

>char \*init_decoded_msg(t_min_heap_node \*\*root, unsigned char \*encoded_msg, int size) : Essa função recebe nos argumentos o ponteiro para a raiz de uma Árvore de Huffman, uma mensagem codificada, e o tamanho da mensagem decodificada, então decodifica a mensagem codificada e retorna um ponteiro para a string decodificada.

>void send_info_to_encoder(t_wrap_info \*wrapper) : Essa função envia toda a informação para o encoder, Informação descomprimida, Tamanho em bytes dessa informação descomprimida, Tamanho em bytes da informação comprimida, e o tempo que levou para realizar a decodificação e descompactação.

>void init_wrapper(t_wrap_info \*wrapper) : Recebe todas as informações enviadas pelo decoder via memória compartilhada, recebe o tamanho do array de frequencias, o tamanho da string codificada, o array de frequencias, o array de caractéres únicos e a mensagem codificada, tudo em segmentos de memoria diferentes, mas usando o mesmo filename como parâmetro.

>unsigned int is_bit(unsigned char byte, int i) : Retorna true se o byte for 1, se não retorna false.

>char \*unpack_message(t_min_heap_node \*\*root, unsigned char \*encoded_msg, int len_decoded) : Recebe como parâmetro o endereço de um ponteiro para a raíz de uma Árvore de Huffman, uma mensagem codificada, e o tamanho da string decodificada, decodifica lendo bit a bit e traduzindo iterando pela Árvore, no final retorna um ponteiro para a mensagem descomprimida.

>void decode_and_unpack(t_wrap_info \*wrapper) : Minhas sinceras desculpas por essa função, fiquei sem tempo e realmente não consegui refatorar ela, ela além de decodificar e descompactar ela também chama a função que envia as informações pro encoder.

>void compact(unsigned char \*encoded_str) : Essa função recebe uma string codificada, cria um arquivo ```compact.fabin``` e escreve a compactação dentro desse arquivo, a compactação é feita da seguinte maneira: o código pega cada 8 caracteres codificados e escreve em formato de bit em um caractere, e depois escreve esse caractere dentro do arquivo que foi criado.

>char \*chars_found_in_str(char \*str) : Essa função retorna um array de caracteres unicos, recebendo a string a analisar como parametro, por exemplo, a string "foo baar arrrr beeearr beerrr" traria o retorno "fobare", o retorno dessa função é utilizado para criar a tabela de frequência de cada caractere.

>int \*set_frequencies(char \*uniq_chars, char \*std_data, size_t size) : O primeiro parâmetro dessa função seria o retorno de ```chars_found_int_str()``` e ela cria uma tabela de frequencia, com as posições correspondendo as posições de uniq_chars.

>char \*merge_args(int argc, char \*\*argv) : Essa função retorna uma string que é a combinação de todos os argvs (exceto o 0), não coloca espaço entre as concatenações.

>void send_infos_to_decoder(int \*freqs, char \*uniq_chars, unsigned char \*encoded_str) : Essa função disponibiliza as informações no segmento de memória compartilhada que mais tarde será acessado pelo ```decoder```, primeiro envia o número de posições que precisarão ser disponibilizadas no array \*freqs, depois o tamanho da string codificada, depois envia as frequencias, depois o array de caracteres unicos, e por ultimo envia a string codificada.

>void set_dict(t_min_heap_node \*root, char \*\*dict, char str\[100\], int top) : Essa função recebe o ponteiro para a raiz de uma Árvore de Huffman, e a partir da Árvore de Huffman monta um dicionário, onde a representação do caractere em codigo Huffman será armazenado na posição de valor numérico desse caractere, por exemplo, suponhamos que temos um caractere 'A', a representação numérica dele é 65, logo na posição dict\[65\] terá a representação de 'A' em código de Huffman.

>unsigned char \*get_encoded_string(char \*str_to_encode, char \*\*dict, int size) : Essa função recebe uma string para codificar, um dicionário com os valores de cada caractere em Huffman e o tamanho da string a ser codificada, o primeiro passo dessa função é criar um \*\* onde cada posição terá a correspondência do caractere em Huffman Coding, depois disso é alocado espaço suficiente em uma string e todas essas strings são concatenadas em encoded_str.
