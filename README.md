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
