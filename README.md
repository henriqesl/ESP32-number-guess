# 🎯 Jogo de Adivinhação com ESP32

Este é um **jogo de adivinhação numérica** desenvolvido com **ESP32**, botões, buzzer, LEDs e display OLED.  
O jogador deve adivinhar um número aleatório entre **0 e 60**, com direito a **5 tentativas** e um **dica opcional**.

- Use os botões para aumentar/diminuir o número.
- Confirme o palpite e veja se precisa ir para cima ou para baixo.
- Use a dica para saber se o número é **par ou ímpar** (disponível a partir da 3ª tentativa).
- Se acertar, você vence! Se errar 5 vezes, o jogo termina.

---

## 📂 Código

- `setup()` – Inicializa os pinos, display OLED e configurações iniciais.
- `loop()` – Controla o andamento do jogo: leitura dos botões, exibição de dicas, vitória ou derrota.
- Funções auxiliares:
  - `startGame()` – Exibe a tela inicial.
  - `numberDraw()` – Gera o número aleatório entre 0 e 60.
  - `buttons()` – Lê os botões UP, DOWN e CONFIRM para definir o número do jogador.
  - `tries()` – Exibe o número de tentativas restantes.
  - `hint()` – Fornece uma dica se o número é par ou ímpar.
  - `win()` – Mostra a tela de vitória e efeitos com LED/buzzer.
  - `gameOver()` – Exibe a tela de derrota com sinal sonoro.
  - `resetGame()` – Reinicia o jogo.
  - `waitToStart()` / `waitForRestart()` – Aguarda interação do jogador para começar/reiniciar.

---

## 🚀 Como Jogar?

1. Conecte os botões e LEDs nos pinos definidos no código.
2. Carregue o código usando a **Arduino IDE** ou **PlatformIO**.
3. A tela mostrará as instruções iniciais.
4. Pressione o botão **verde (UP)** para começar.
5. Use os botões para escolher seu número:
   - **Verde (UP)** = Aumenta
   - **Vermelho (DOWN)** = Diminui
   - **Branco (CONFIRM)** = Confirma palpite
   - **Azul (HINT)** = Pede dica (par ou ímpar)
6. Tente adivinhar o número correto em até 5 tentativas!

---

## 💡 Extras

- LED verde acende ao vencer, com som de vitória no buzzer.
- LED vermelho pisca ao perder, com som de derrota.
- O display OLED mostra mensagens claras a cada etapa.
- O número sorteado é baseado na leitura de um pino analógico para gerar aleatoriedade.

---

## 💻 Autor

**Henrique Silva**  
Estudante de Sistemas de Informação / Técnico em Eletrônica  
📍 Recife - PE  
🔗 [LinkedIn](https://www.linkedin.com/in/henrique-silva-b8583932a/)

---

> Esse projeto é livre para uso educacional. Sinta-se à vontade para modificar e aprimorar! 🚀

https://github.com/user-attachments/assets/e1449ae0-e75c-4857-81ee-0c7eb09e063b
