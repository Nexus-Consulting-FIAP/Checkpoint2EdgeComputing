## Estação de Monitoramento - Nexus Group

**Integrantes**
|Nome|RM|
|--|--|
|Lucas de Almeida Pires | RM: 562757 |
|Daniel Oliveira de Souza | RM: 566284 |
|João Pedro Raimundo Marcilio | RM: 561603 |
|Lucas Zanella Clemente | RM: 563880 |
|João Pedro Ribeiro Palermo | RM: 562077 |

Este projeto foi desenvolvido pelo Nexus Group, especialmente para atender às necessidades da Vinheria Agnello, com o objetivo de proteger a qualidade e longevidade dos vinhos armazenados. Vinhos são produtos sensíveis que exigem condições ambientais específicas para sua conservação ideal: pequenas variações em temperatura, umidade e luminosidade podem comprometer seus aromas, sabores e estrutura.

Pensando nisso, este dispositivo realiza um monitoramento ambiental completo, em tempo real, medindo os três principais fatores que influenciam diretamente na integridade do vinho:
-  Temperatura
-  Umidade relativa do ar
-  Luminosidade do ambient

Link para o Wokwi: https://wokwi.com/projects/431438950003733505
Link para o vídeo: ADD DPS.

## 🎯 Objetivo

Evitar variações ambientais que possam comprometer o armazenamento correto de vinhos, utilizando sensores, alertas e registros automáticos com precisão.

---

## 🛠 Tecnologias e Componentes

- **Arduino UNO** (ou equivalente)
- **Display LCD 16x2**
- **Joystick analógico** (controle de menu)
- **Sensor DHT11** (temperatura e umidade)
- **LDR** (luminosidade)
- **RTC DS3231** (relógio de tempo real)
- **EEPROM interna** (armazenamento de backlog)
- **Buzzer** (alerta sonoro)
- **Fonte 5V ou USB**
- Jumpers e Protoboard

---

## 📦 Funcionalidades

### Monitoramento de Temperatura (🌡️)
Mede continuamente a temperatura do ambiente onde os vinhos estão armazenados. Caso a temperatura ultrapasse ou fique abaixo de uma faixa segura previamente calibrada, o sistema dispara um alerta sonoro (buzzer) e exibe uma mensagem de “ALTA” ou “BAIXA” no visor LCD.

### Monitoramento de Umidade (💧)
Verifica constantemente a umidade relativa do ar. Se a umidade estiver muito alta ou muito baixa, o sistema alerta da mesma forma que a temperatura, com aviso no visor e som de alarme.

### Monitoramento de Luminosidade (☀️)
Mede a intensidade da luz no ambiente por meio de um sensor LDR. Se a claridade estiver acima do nível configurado, o sistema exibe "CLARO" ou “MUITO CLARO!” no visor, alertando que o ambiente pode estar prejudicando os vinhos por excesso de luz. Para ambientes escuros ou com iluminação controlada, essa medição serve como segurança extra.

### Alerta Sonoro (🔊 Buzzer)
Quando qualquer um dos três parâmetros (temperatura, umidade ou luminosidade) estiver fora dos limites definidos, o aparelho emite um som de alerta automático, indicando que alguma ação deve ser tomada para proteger os vinhos.

### Navegação por Joystick (🕹️)
O sistema possui um controle por joystick analógico, facilitando a navegação entre os menus do visor LCD. Com movimentos simples (cima, baixo, esquerda, direita e botão central), o usuário pode consultar dados em tempo real ou acessar registros antigos.

### Menu com Ícones Personalizados (📺 LCD)
A interface apresenta símbolos personalizados no display para identificar claramente cada função (como temperatura, umidade, luz, histórico etc.). Isso torna o uso mais intuitivo e rápido, mesmo para usuários que não têm familiaridade com tecnologia.

### Registro de Dados com Hora (🕒 RTC + EEPROM)
Toda vez que um valor fica fora do padrão, o sistema salva automaticamente a data, hora e os valores dos sensores em uma memória interna (EEPROM). Essa função utiliza um relógio de tempo real (RTC), garantindo precisão nos horários.

### Visualização de Histórico (📚 Backlog)
Através do menu, é possível acessar os registros salvos anteriormente. Cada entrada mostra a hora exata do evento, a temperatura, umidade e luminosidade detectadas naquele momento, ajudando na análise posterior do ambiente da adega.

---

## 📋 Navegação no Menu

Utiliza joystick analógico em um único pino para:

- `▲`, `◀`, `▶`, `●` = controle intuitivo
- Exibe ícones personalizados:
  - `🌡️` Temperatura
  - `💧` Umidade
  - `☀️` Luminosidade
  - `📦` Backlog

---

## 🔔 Alertas

- ⚠️ **Buzzer** é acionado quando algum dos valores ultrapassa limites definidos.
- 💡 O LCD também pisca ícones para indicar o tipo de alerta visualmente.
- 📜 Cada alerta gera um **registro** com data e hora no backlog.

---

## 🧾 Backlog

- Armazena os últimos eventos de alerta
- Mostra **data, hora, temperatura, umidade e luminosidade**
- Lido diretamente no menu usando o joystick

---

## 🚀 Como Usar

1. Carregue o código no Arduino
2. Ligue o sistema — ele fará a **calibração inicial**
3. Use o joystick para navegar pelas opções
4. O sistema monitora automaticamente e avisa em tempo real

---

📍 Projeto criado para a **Vinheria Agnello**  
