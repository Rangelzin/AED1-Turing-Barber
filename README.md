# AED-Turing-Barber

## 📋 Sobre o Projeto

O **Turing Barber** é um sistema de gerenciamento de barbearia desenvolvido como projeto acadêmico para a disciplina de Algoritmos e Estruturas de Dados I (AED1) da Universidade Federal de Goiás (UFG). O projeto implementa um sistema completo de controle de clientes, barbeiros e agendamentos, utilizando estruturas de dados fundamentais e boas práticas de programação em linguagem C.

Este sistema permite o cadastro e gerenciamento de clientes e barbeiros, controle de agendamentos, validação de datas e horários, além de fornecer uma interface interativa via menu para todas as operações.

## 🎯 Funcionalidades

O sistema oferece as seguintes funcionalidades principais:

- **Gerenciamento de Clientes**
    - Cadastro de novos clientes
    - Consulta de informações de clientes
    - Atualização de dados cadastrais
    - Remoção de clientes do sistema
- **Gerenciamento de Barbeiros**
    - Cadastro de barbeiros
    - Consulta de informações de barbeiros
    - Atualização de dados profissionais
    - Controle de disponibilidade
- **Sistema de Agendamentos**
    - Criação de novos agendamentos
    - Validação de datas e horários
    - Verificação de conflitos de horários
    - Histórico de atendimentos
- **Validação e Utilidades**
    - Validação automática de datas
    - Verificação de dados de entrada
    - Funções utilitárias para manipulação de dados


## 🏗️ Estrutura do Projeto

```
AED-Turing-Barber/
│
├── include/                    # Arquivos de cabeçalho (.h)
│   ├── contexto.h             # Definições do contexto da aplicação
│   ├── controle_barbeiro.h    # Interface de controle de barbeiros
│   ├── controle_cliente.h     # Interface de controle de clientes
│   ├── estruturas.h           # Definições das estruturas de dados
│   ├── menu.h                 # Interface do menu principal
│   ├── utils.h                # Funções utilitárias
│   └── validacao_data.h       # Funções de validação de datas
│
├── src/                       # Arquivos de implementação (.c)
│   ├── contexto.c             # Implementação do contexto
│   ├── controle_barbeiro.c    # Lógica de controle de barbeiros
│   ├── controle_cliente.c     # Lógica de controle de clientes
│   ├── main.c                 # Ponto de entrada do programa
│   ├── menu.c                 # Implementação do menu interativo
│   ├── utils.c                # Implementação de utilidades
│   └── validacao_data.c       # Implementação de validações
│
├── CMakeLists.txt             # Configuração de compilação CMake
├── LICENSE                    # Licença MIT
├── README.md                  # Este arquivo
└── .gitignore                # Arquivos ignorados pelo Git
```


## 🔧 Tecnologias Utilizadas

- **Linguagem:** C (padrão C11)
- **Sistema de Build:** CMake
- **Controle de Versão:** Git
- **Licença:** MIT


## 📦 Pré-requisitos

Para compilar e executar o projeto, você precisará ter instalado:

- **GCC** (GNU Compiler Collection) versão 7.0 ou superior
- **CMake** versão 3.10 ou superior
- **Make** (geralmente incluído em sistemas Unix-like)


### Instalação no Linux (Ubuntu/Debian)

```bash
sudo apt-get update
sudo apt-get install build-essential cmake
```


### Instalação no macOS

```bash
brew install cmake gcc
```


### Instalação no Windows

Recomenda-se usar o MinGW ou WSL (Windows Subsystem for Linux) para compilar o projeto.

## 🚀 Como Compilar

### Usando CMake

1. Clone o repositório:
```bash
git clone https://github.com/Rangelzin/AED1-Turing-Barber.git
cd AED1-Turing-Barber
```

2. Crie um diretório de build:
```bash
mkdir build
cd build
```

3. Configure o projeto com CMake:
```bash
cmake ..
```

4. Compile o projeto:
```bash
make
```


### Compilação Manual

Alternativamente, você pode compilar manualmente:

```bash
gcc -I include src/*.c -o turing_barber -std=c11 -Wall -Wextra
```


## ▶️ Como Executar

Após a compilação, execute o programa:

```bash
./turing_barber
```

Ou, se estiver no diretório build:

```bash
./turing_barber
```

O sistema iniciará com um menu interativo que guiará você através das opções disponíveis.

## 📚 Estruturas de Dados

O projeto implementa e utiliza diversas estruturas de dados clássicas:

- **Listas encadeadas** para gerenciamento dinâmico de clientes e barbeiros
- **Estruturas personalizadas** para representação de entidades (Cliente, Barbeiro, Agendamento)
- **Validadores** para garantir integridade dos dados


## 🧪 Exemplos de Uso

### Cadastrar um Cliente

1. Execute o programa
2. Selecione a opção "Gerenciar Clientes"
3. Escolha "Cadastrar Novo Cliente"
4. Insira as informações solicitadas (nome, telefone, etc.)
5. O sistema confirmará o cadastro

### Criar um Agendamento

1. Execute o programa
2. Selecione a opção "Agendamentos"
3. Escolha "Novo Agendamento"
4. Selecione o cliente e o barbeiro
5. Informe data e horário desejados
6. O sistema validará e confirmará o agendamento

## 🤝 Contribuindo

Contribuições são bem-vindas! Para contribuir com o projeto:

1. Faça um Fork do projeto
2. Crie uma branch para sua feature (`git checkout -b feature/NovaFuncionalidade`)
3. Commit suas mudanças (`git commit -m 'Adiciona nova funcionalidade'`)
4. Push para a branch (`git push origin feature/NovaFuncionalidade`)
5. Abra um Pull Request

### Diretrizes de Contribuição

- Mantenha o código limpo e bem documentado
- Siga o padrão de codificação existente
- Adicione comentários quando necessário
- Teste suas alterações antes de submeter
- Atualize a documentação se necessário


## 📝 Licença

Este projeto está licenciado sob a Licença MIT - veja o arquivo [LICENSE](LICENSE) para mais detalhes.

## 👥 Autores

- **Rangelzin** - [GitHub](https://github.com/Rangelzin)
- **Tiagosalesr** - [GitHub](https://github.com/Tiagosalesr)
- **Jose-borges47** - [GitHub](https://github.com/Jose-borges47)

## 🎓 Contexto Acadêmico

Este projeto foi desenvolvido como parte do curso de **Algoritmos e Estruturas de Dados I (AED1)** da **Universidade Federal de Goiás (UFG)**. O objetivo é aplicar os conceitos aprendidos em sala de aula em um projeto prático e funcional.

### Objetivos de Aprendizagem

- Implementação de estruturas de dados fundamentais
- Gerenciamento de memória em C
- Modularização e organização de código
- Validação e tratamento de entrada de dados
- Desenvolvimento de interfaces de usuário em modo texto
- Uso de sistemas de build (CMake)
- Controle de versão com Git


## 📞 Contato

Para dúvidas, sugestões ou reportar problemas, por favor:

- Abra uma [Issue](https://github.com/Rangelzin/AED1-Turing-Barber/issues) no GitHub
- Entre em contato com o desenvolvedor através do perfil do GitHub


## 🔄 Histórico de Versões

- **v1.0** - Versão inicial com funcionalidades básicas
    - Sistema de cadastro de clientes e barbeiros
    - Sistema de agendamentos
    - Menu interativo
    - Validação de datas


## 🙏 Agradecimentos

- Professores e monitores da disciplina AED1-UFG
- Colegas de turma pelas discussões e ideias
- Comunidade open-source pelas ferramentas utilizadas

***

**Nota:** Este é um projeto acadêmico em desenvolvimento. Sugestões e contribuições são sempre bem-vindas!

