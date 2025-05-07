# DeepsickSumoRobot

# 🥋🤖 AESSBOT - Robot Sumo Autónomo

Este es un proyecto de robot sumo autónomo desarrollado en Arduino. El robot es capaz de buscar al oponente, atacarlo y evitar salirse del ring gracias a sensores ultrasónicos y sensores de línea (TCRT5000L).

## 🔧 Hardware utilizado 🚗

- 1x **Arduino Nano**
- 2x **Motores DC con caja reductora** 🚗
- 1x **Driver de motores** (como el L298N o TB6612FNG)
- 1x **Sensor ultrasónico** HC-SR04
- 2x **Sensores de línea** TCRT5000L
- 1x **Chasis minisumo** impreso en 3D 🥋
- 2x **Ruedas de goma** 🚗
- 1x **Batería** recargable (Li-Po o pack de pilas)
- Cables de conexión
- 1x **Placa PCB** personalizada

## 🧠 Comportamiento del robot 🥋

El robot sigue una máquina de estados simple:

- `STATE_SEARCH`: Busca al oponente girando sobre su eje.
- `STATE_ATTACK`: Avanza hacia el enemigo cuando es detectado.
- `STATE_AVOID`: Retrocede y gira si detecta el borde blanco del ring.

También puede activarse mediante un control remoto IR (opcional).

## 📂 Archivos incluidos

- `aessbot.ino`: Código principal del robot.
- Archivos `.stl`, `.glb`, `.step` del modelo 3D para impresión de la base y las ruedas (ver carpeta de modelos).

## 📌 Pines usados (Arduino Nano)

| Componente          | Pin Arduino     |
|---------------------|-----------------|
| Motor A (ENA, IN1, IN2) | 6, 7, 8        |
| Motor B (ENB, IN3, IN4) | 11, 9, 10      |
| Sensor ultrasónico (Trig, Echo) | 3, 2      |
| Sensor línea izquierdo (TCRT5000L) | A1     |
| Sensor línea derecho (TCRT5000L)  | A2     |
| Sensor IR (opcional) | 12 (ejemplo)    |

## 🧪 Simulación

El código puede probarse en Tinkercad si se colocan correctamente:
- Sensores IR
- Sensor ultrasónico
- Motores simulados 🚗
- Sensores TCRT5000 en A1 y A2

## 📜 Licencia

Este proyecto se distribuye bajo la licencia MIT. Eres libre de copiar, modificar y compartir siempre que se dé crédito al equipo original.

---

Desarrollado por el equipo **Deepsick** para AESSBOT UPC 2025 🥋.
