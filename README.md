# STM32 UART LED Controller

A simple STM32 embedded systems project that demonstrates **UART-based command control of an LED** using the STM32 HAL library.

The system provides a serial command interface through **USART1**. Users can send commands from a serial terminal to turn an LED ON or OFF. The project also demonstrates how to redirect standard C `printf()` and `scanf()` functions through UART.

---

## Overview

This project was developed for the **STM32F103VET6** microcontroller and demonstrates:

* UART/USART serial communication
* `printf()` redirection through USART
* `scanf()` input through USART
* GPIO output control
* Command-based embedded control
* STM32 HAL programming
* Modular C project structure

The controller continuously waits for a command received through USART1:

| Command           | Action                    |
| ----------------- | ------------------------- |
| `open`            | Turns LED2 ON             |
| `close`           | Turns LED2 OFF            |
| Any other command | Displays an error message |

---

## Features

* **STM32F103VET6** microcontroller support
* **USART1** serial communication
* **115200 baud rate**
* **8 data bits, 1 stop bit, no parity**
* Command-line LED control
* `printf()` UART output redirection
* `scanf()` UART input redirection
* Active-low LED control
* Modular source/header organization
* Error handling through `Error_Handler()`
* 72 MHz system clock configuration

---

## Hardware Configuration

### Microcontroller

**STM32F103VET6**

### GPIO / UART Pin Configuration

| Peripheral | Pin  | Function      |
| ---------- | ---- | ------------- |
| LED2       | PE6  | LED output    |
| USART1 TX  | PA9  | UART transmit |
| USART1 RX  | PA10 | UART receive  |

LED2 is configured as **active-low**:

* `GPIO_PIN_RESET` → LED ON
* `GPIO_PIN_SET` → LED OFF

The LED definitions and control macros are implemented in `inc/gpio.h`.

---

## UART Configuration

USART1 is configured with the following parameters:

```text
Baud Rate:       115200
Data Bits:       8
Stop Bits:       1
Parity:          None
Mode:            TX + RX
Flow Control:    None
Oversampling:    16
```

The UART configuration is implemented in `src/usart.c`.

---

## How It Works

The program follows this basic flow:

```text
        ┌─────────────────────┐
        │   STM32F103VET6     │
        │                     │
        │      USART1         │
        │     PA9 / PA10      │
        └──────────┬──────────┘
                   │
                   │ UART
                   ▼
          ┌─────────────────┐
          │  Serial Terminal│
          └────────┬────────┘
                   │
             User Command
             ┌─────┴─────┐
             │           │
           "open"      "close"
             │           │
             ▼           ▼
          LED ON       LED OFF
             │           │
             └─────┬─────┘
                   ▼
                  PE6
```

At startup, the firmware initializes the HAL, system clock, GPIO, and USART1.

It then displays the available commands and continuously waits for user input.

The main command-processing logic is implemented in `src/main.c`.

---

## Serial Commands

### Turn LED ON

Send:

```text
open
```

Expected response:

```text
>>> LED2 is open!
```

### Turn LED OFF

Send:

```text
close
```

Expected response:

```text
>>> LED2 is close!
```

### Invalid Command

For example:

```text
hello
```

The controller responds with an error message and displays the received command.

---

## Example Terminal Output

```text
========================================
  STM32 UART LED Controller
========================================
  Commands: 'open'  → LED ON
           'close' → LED OFF
========================================
Waiting for command...

Enter command: open
>>> LED2 is open!

Enter command: close
>>> LED2 is close!
```

---

## Project Structure

```text
stm32-uart-led-controller/
│
├── inc/
│   ├── gpio.h
│   ├── main.h
│   └── usart.h
│
├── src/
│   ├── gpio.c
│   ├── main.c
│   └── usart.c
│
├── docs/
│
├── .gitignore
├── LICENSE
└── README.md
```

The repository separates application/source files from header files, making the project easier to understand and maintain.

---

## Software Requirements

To build or modify this project, you will need:

* STM32 development environment
* ARM GCC or compatible ARM compiler
* STM32F1 HAL library
* Serial terminal application
* ST-LINK or another compatible programming/debugging interface

A serial terminal such as **Tera Term, PuTTY, RealTerm, or a similar UART terminal** can be used for testing.

---

## Setup

1. Connect the STM32F103VET6 development board to your computer.
2. Connect USART1 to a compatible USB-to-UART interface if required.
3. Connect:

   * PA9 → UART RX
   * PA10 → UART TX
   * GND → GND
4. Configure the serial terminal for:

```text
Baud Rate: 115200
Data Bits: 8
Parity: None
Stop Bits: 1
Flow Control: None
```

5. Program the STM32.
6. Open the serial terminal.
7. Reset the microcontroller.
8. Send `open` or `close`.

> **Note:** UART TX and RX are connected crosswise when using an external USB-to-UART adapter: MCU TX → Adapter RX and MCU RX → Adapter TX.

---

## Implementation Details

### UART `printf()` Redirection

The project redirects `printf()` to USART1 using:

```c
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}
```

This allows normal C `printf()` calls to send text through the UART interface.

### UART `scanf()` Input

`scanf()` input is redirected through USART1 using:

```c
int fgetc(FILE *f)
{
    uint8_t ch;
    HAL_UART_Receive(&huart1, &ch, 1, HAL_MAX_DELAY);
    return ch;
}
```

This allows commands to be received directly from a serial terminal.

### LED Control

LED2 is controlled using macros:

```c
LED2_ON();
LED2_OFF();
LED2_TOGGLE();
```

The LED is configured as active-low on PE6.

---

## Learning Objectives

This project demonstrates practical understanding of:

* Embedded C programming
* STM32 HAL
* GPIO configuration
* UART communication
* Serial command interfaces
* Standard I/O redirection
* Microcontroller clock configuration
* Modular firmware organization
* Hardware/software communication

---

## Possible Improvements

Future versions could include:

* Non-blocking UART communication using interrupts
* DMA-based UART communication
* Multiple LED control
* Additional commands such as `toggle`, `status`, and `help`
* Command parser with safer input handling
* UART receive buffer with configurable command length
* Command acknowledgement protocol
* Error/status codes
* Hardware abstraction for multiple LED outputs

---

## Author

**Muhammad Sarim Amir**

Embedded Systems / IoT Developer

GitHub: [sarimamirdev](https://github.com/sarimamirdev)

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
