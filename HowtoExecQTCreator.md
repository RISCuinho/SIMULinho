Como Criar no QTCreator
=======================

Apesar do QTCreator ter uma forma de compartilhar configurações do projeto, não estou conseguindo compartilhar as estapas de execução para se ter sucesso nos testes do projeto.

Para tal sucesso, faça os seguintes passos:


## Build

Depois de abrir o projeto no QTCreator, vá em *Projects* ja barra lateral e escolha o projeto *SIMULinho* como sendo o projeto ativo, em seguida em *Build and Run* selecione as configurações para *build*, em *Build Settings* na lista de *Edit build configuration* clone a configuração *Profile* e a nomeie como *Profile-vpi* não use espaço nos nomes. Certifique-se que a opção _Shadow build_ esteja marcado.

Abaixo, em *Build Steps*, clique no botão *Add Build Step*, clique em detalhes e na caixa de texto *Make arguments* do novo passo adicionado, escreva `verilognize_vpp`.

## Exec

Sertifique-se que o projeto ativo é o *SIMULinho*, então clique *Run* nas opções de *Build & Run* a esquerda. Em *Run Settings* na tela principal, clique *Add*  para adicioonar um novo método de *Deployment* (Deployment Configuration), a seguir clique no botão *Add Deploy Step*, selecione _Make_, faça isso duas vezes, para adicionar dois passos. Em detalhes para o segundo novo passo na caixa de texto de *Make arguments* escreva `verilognize`, deixe o primeiro passo vázio ele vai executar todas as demais `targets` (all).
