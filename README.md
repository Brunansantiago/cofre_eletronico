# cofre_eletronico
Neste repositório, apresento um protótipo funcional de um cofre digital inteligente que desenvolvi, com senha totalmente customizável pelo usuário.

# Sobre o Projeto
Eu criei este sistema de segurança do zero, com a lógica de controle implementada em um Arduino Uno e todo o circuito prototipado e validado na plataforma Autodesk Tinkercad. Meu objetivo principal foi desenvolver um projeto base para atestar meus conhecimentos fundamentais em eletrônica digital e programação de sistemas embarcados, demonstrando um ciclo de desenvolvimento completo, da concepção à simulação funcional.

O sistema possui um mecanismo de trava físico, operado por um Servo Motor, e uma interface de usuário que construí utilizando 3 botões e feedback audiovisual.

# Tecnologias que Utilizei
Plataforma de Controle: Arduino Uno
Linguagem: C++ (Arduino IDE)
Ambiente de Simulação: Autodesk Tinkercad
Atuadores: Servo Motor SG90, LEDs (Verde e Vermelho), Buzzer Piezoelétrico
Entradas: Pushbuttons com configuração de pull-down

# Funcionalidades que Implementei
Senha Customizável: Na inicialização do sistema, implementei um "Modo de Cadastro" que permite ao usuário definir sua própria senha numérica de 3 dígitos. A entrada da senha é feita de forma criativa, baseada na contagem de toques em cada um dos três botões.

Feedback Multissensorial: Desenvolvi um sistema de feedback completo para o usuário:

Visual: LEDs de status indicam o estado atual (Verde para "Aberto", Vermelho para "Trancado"). Em caso de erro de senha, o LED vermelho pisca.

Auditivo: O buzzer emite tons sonoros distintos que programei para cada tipo de interação: um beep curto para cada toque de botão, uma melodia de sucesso ao abrir o cofre e um som de erro em caso de senha incorreta.

Mecanismo de Trava Físico: A trava é operada por um Servo Motor, que programei para se mover para posições angulares precisas para trancar e destrancar o cofre de forma confiável.

# Montagem

![Montagem do Circuito do Cofre Eletrônico](README.mdimg\cofreeletro.png)

# Como usar

Faça o upload do código do arquivo src/cofreeletronico.ino para o seu Arduino.
Ligue o sistema.
O sistema pedirá para criar uma senha para o seu cofre eletrônico. 