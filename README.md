# SystemIndexBinaryTree

Um sistema de indexação de produtos eficiente implementado em C, utilizando **Árvores Binárias de Busca (BST)**. O projeto permite gerenciar produtos com indexação dupla simultânea (por ID e por Preço), facilitando buscas rápidas e operações complexas como busca por faixa de preço.

## 🚀 Funcionalidades

O sistema oferece as seguintes operações:

- **Inserção Sincronizada:** Adiciona um produto em duas árvores simultaneamente para manter os índices atualizados.
- **Busca por ID:** Localização direta de um produto através do seu identificador único.
- **Busca por Faixa de Preço:** Lista todos os produtos cujos preços estejam dentro de um intervalo definido (mínimo e máximo).
- **Busca de Vizinho Próximo:** Encontra o produto com o preço mais próximo de um valor alvo especificado.
- **Remoção Coordenada:** Remove um produto de ambos os índices (ID e Preço) garantindo a integridade dos dados.
- **Exibição Ordenada:**
  - Listagem de produtos ordenada por ID.
  - Listagem de produtos ordenada por Preço.

## 📁 Estrutura do Projeto

- `main.c`: Ponto de entrada do programa com exemplos de uso das funcionalidades.
- `arvore.h` / `arvore.c`: Implementação da lógica das Árvores Binárias de Busca e do Gerenciador de índices.
- `produto.h`: Definição da estrutura de dados do Produto.
- `CMakeLists.txt`: Arquivo de configuração para compilação via CMake.

## Perguntas

### 1. Qual a complexidade das operações em:
- **Melhor Caso:** $O(\log n)$ — Ocorre quando a árvore está balanceada, permitindo que cada comparação descarte metade dos nós restantes.
- **Pior Caso:** $O(n)$ — Ocorre quando os elementos são inseridos em ordem (crescente ou decrescente), fazendo com que a árvore se degenere em uma "lista ligada" (árvore zigue-zague ou linear).

### 2. Por que usar duas árvores pode ser melhor que uma só?
O uso de dois índices (ID e Preço) permite **otimizar diferentes tipos de consulta**:
- Se tivéssemos apenas a árvore de **ID**, uma busca por uma faixa de **preços** exigiria percorrer todos os produtos do sistema ($O(n)$).
- Com uma árvore dedicada para **Preço**, podemos realizar buscas por intervalo e encontrar o "vizinho mais próximo" de forma muito mais eficiente

### 3. Quais problemas podem ocorrer se as árvores ficarem desbalanceadas?
- **Degradação de Performance:** As operações que deveriam ser rápidas ($O(\log n)$) tornam-se lentas ($O(n)$).
- **Eficiência Perdida:** O propósito de usar uma estrutura de árvore é perdido, pois o tempo de resposta para buscar um produto em um sistema com milhares de itens aumentaria drasticamente.
- Em casos extremos de árvores muito profundas em sistemas com memória limitada, poderia ocorrer um estouro de pilha (*stack overflow*) devido à recursão excessiva.
